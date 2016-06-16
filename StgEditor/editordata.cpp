#include "editordata.h"
#include <QSettings>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <algorithm>
#include <QMessageBox>
#include "protobuf.h"

EditorData::EditorData()
{

}

EditorData* EditorData::instance()
{
	static EditorData s_data;
	return &s_data;
}

QString EditorData::basePath()
{
	return m_basePath;
}

bool EditorData::setBasePath(QString path)
{
	QDir dir(path);
	if (!dir.exists())
		return false;

	m_basePath = path;
	return true;
}

QString EditorData::getTextureFullPath(QString source)
{
	return m_basePath + QDir::separator() + source;
}

QPixmap EditorData::getTexture(QString source)
{
	QPixmap& img = m_textureCache[source];
	if (img.isNull())
	{
		img = QPixmap::fromImage(QImage(getTextureFullPath(source)));
	}
	return img;
}

QPixmap EditorData::getTextureByName(QString name)
{
	for (auto iter = m_textures.begin(); iter != m_textures.end(); ++iter)
	{
		if (iter.value() == name)
			return getTexture(iter.key());
	}
	return QPixmap();
}

SubGraphData* EditorData::getSubGraphByName(QString name)
{
	auto iter = std::find_if(m_subGraphes.begin(), m_subGraphes.end(), [&name](const SubGraphData& dat)
	{
		return dat.name == name;
	});
	if (iter == m_subGraphes.end())
		return nullptr;

	return &(*iter);
}

void EditorData::updateTextureRef(QString srcName, QString dstName)
{
	for (uint i = 0; i < m_subGraphes.size(); ++i)
	{
		if (m_subGraphes[i].texture == srcName)
			m_subGraphes[i].texture = dstName;
	}
}

void EditorData::removeTexture(const QString& source)
{
	QString name = m_textures[source];

	m_textures.remove(source);
	m_textureCache.remove(source);
	for (auto iter = m_subGraphes.begin(); iter != m_subGraphes.end(); ++iter)
	{
		if (iter->texture == name)
			iter->texture.clear();
	}
}

void EditorData::removeSubGraph(int idx)
{
	QString name = m_subGraphes[idx].name;
	m_subGraphes.erase(m_subGraphes.begin() + idx);
	for (auto iter = m_bulletStyles.begin(); iter != m_bulletStyles.end(); ++iter)
	{
		if (iter->subGraph == name)
			iter->subGraph.clear();
	}
}

void EditorData::removeBulletStyle(int idx)
{
	QString name = m_bulletStyles[idx].name;
	m_bulletStyles.erase(m_bulletStyles.begin() + idx);
}

QString EditorData::changeTextureName(const QString& source, const QString& newName)
{
	QString srcName = m_textures[source];
	if (srcName == newName)
		return newName;

	for (auto iter = m_textures.begin(); iter != m_textures.end(); ++iter)
	{
		if (iter.value() == newName && iter.key() != source)
		{
			QMessageBox::warning(nullptr, "conflit name", QString("conflit name with \"%1\"").arg(iter.key()));
			return srcName;
		}
	}

	m_textures[source] = newName;
	updateTextureRef(srcName, newName);
	return newName;
}

bool EditorData::commitSubGraph(int idx, const SubGraphData& data)
{
	if (!canChangeSubGraphName(idx, data.name))
	{
		QMessageBox::warning(nullptr, "conflit name", QString("\"%1\" already exist").arg(data.name));
		return false;
	}

	SubGraphData& origin = m_subGraphes[idx];
	if (origin.name != data.name)
	{
		for (auto iter = m_bulletStyles.begin(); iter != m_bulletStyles.end(); ++iter)
		{
			if (iter->subGraph == origin.name)
				iter->subGraph = data.name;
		}
	}
	origin = data;
	return true;
}

bool EditorData::commitBulletStyle(int idx, const BulletStyle& style)
{
	if (!canChangeBulletStyleName(idx, style.name))
	{
		QMessageBox::warning(nullptr, "conflit name", QString("\"%1\" already exist").arg(style.name));
		return false;
	}

	BulletStyle& dat = m_bulletStyles[idx];
	if (dat.name != style.name)
	{
		// update references;
	}

	dat = style;
	return true;
}

bool EditorData::canChangeSubGraphName(int idx, const QString& newName)
{
// 	for (uint i = 0; i < m_subGraphes.size(); ++i)
// 	{
// 		if (i != idx && m_subGraphes[i].name == newName)
// 			return false;
// 	}
	return true;
}

bool EditorData::canChangeBulletStyleName(int idx, const QString& newName)
{
	for (uint i = 0; i < m_bulletStyles.size(); ++i)
	{
		if (i != idx && m_bulletStyles[i].name == newName)
			return false;
	}
	return true;
}

QString EditorData::enum2String(BulletStyle::BulletType type)
{
#define GetEnumString(name) case BulletStyle::t##name: return #name
	switch (type)
	{
		GetEnumString(General);
		GetEnumString(Ray);
		GetEnumString(Segment);
		GetEnumString(Curve);
	default:
		return QString();
	}
#undef GetEnumString
}

QString EditorData::enum2String(BulletStyle::CollideType type)
{
#define GetEnumString(name) case BulletStyle::c##name: return #name
	switch (type)
	{
		GetEnumString(Circle);
		GetEnumString(Rectangle);
	default:
		return QString();
	}
#undef GetEnumString
}

void EditorData::load()
{
	loadSettings();
	loadTextures();
	loadSubGraphies();
	loadBulletStyles();
}

void EditorData::save()
{
	saveSettings();
	saveTextures();
	saveSubGraphies();
	saveBulletStyles();
	savePathSet();
}

void EditorData::loadSettings()
{
	QSettings setting("setting.ini", QSettings::IniFormat);
	setting.beginGroup("default");
	{
		m_basePath = setting.value("basePath").toString();
	}
	setting.endGroup();
}

void EditorData::saveSettings()
{
	QSettings setting("setting.ini", QSettings::IniFormat);
	setting.beginGroup("default");
	{
		setting.setValue("basePath", m_basePath);
	}
	setting.endGroup();
}

void EditorData::loadTextures()
{
	TextureBuf buff;
	QString path = m_basePath + "\\textures.pb";
	if (buff.load((LPCWSTR)path.utf16()))
	{
		auto& map = buff.textures()->map();
		for (auto iter = map.begin(); iter != map.end(); ++iter)
		{
			m_textures.insert(QString::fromUtf8(iter->first.c_str()), QString::fromUtf8(iter->second.c_str()));
		}
	}
}

void EditorData::saveTextures()
{
	TextureBuf buff;
	for (auto iter = m_textures.begin(); iter != m_textures.end(); ++iter)
	{
		buff.insert((LPCWSTR)iter.key().utf16(), (LPCWSTR)iter.value().utf16());
	}

	QString path = m_basePath + "\\textures.pb";
	buff.save((LPCWSTR)path.utf16());
}

void EditorData::loadSubGraphies()
{
/*
	QFile in(m_basePath + "\\subgraphics.json");
	if (!in.open(QFile::ReadOnly))
		return;

	QJsonParseError err;
	QJsonDocument doc = doc.fromJson(in.readAll(), &err);
	in.close();

	QJsonArray array = doc.array();
	for (auto iter = array.begin(); iter != array.end(); ++iter)
	{
		m_subGraphes.emplace_back(SubGraphData());
		SubGraphData& dat = m_subGraphes.back();

		QJsonObject obj = iter->toObject();
		dat.name = obj["name"].toString();
		dat.texture = obj["texture"].toString();

		QJsonArray params = obj["params"].toArray();
		for (int i = 0; i < SubGraphData::ParamCount; ++i)
			dat.param.raw[i] = params[i].toInt();
	}
*/
	SubGraphicsBuf buff;
	QString path = m_basePath + "/subgraphics.pb";
	if (buff.load((LPCWSTR)path.utf16()))
	{
		auto& map = buff.subgraphics()->map();
		for (auto iter = map.begin(); iter != map.end(); ++iter)
		{
			QString name = QString::fromUtf8(iter->first.c_str());
			auto infos = iter->second.info();
			for (auto itInfo = infos.begin(); itInfo != infos.end(); ++itInfo)
			{
				auto& info = *itInfo;
				m_subGraphes.emplace_back(SubGraphData());
				SubGraphData& dat = m_subGraphes.back();
				dat.name = name;
				dat.texture = QString::fromUtf8(info.texture().c_str());
				dat.param.srcX = info.xsrc();
				dat.param.srcY = info.ysrc();
				dat.param.allNum = info.allnum();
				dat.param.numX = info.xnum();
				dat.param.numY = info.ynum();
				dat.param.sizeX = info.width();
				dat.param.sizeY = info.height();
			}
		}
	}
}

void EditorData::saveSubGraphies()
{
// 	QJsonArray array;
// 	for (auto iter = m_subGraphes.begin(); iter != m_subGraphes.end(); ++iter)
// 	{
// 		QJsonObject obj;
// 
// 		obj.insert("name", iter->name);
// 		obj.insert("texture", iter->texture);
// 		
// 		QJsonArray params;
// 		for (int i = 0; i < SubGraphData::ParamCount; ++i)
// 			params.push_back(iter->param.raw[i]);
// 		obj.insert("params", params);
// 
// 		array.push_back(obj);
// 	}
// 	QJsonDocument doc(array);
// 
// 	QFile out(m_basePath + "\\subgraphics.json");
// 	if (out.open(QFile::WriteOnly))
// 	{
// 		out.write(doc.toJson());
// 		out.close();
// 	}
	SubGraphicsBuf buff;
	for (auto iter = m_subGraphes.begin(); iter != m_subGraphes.end(); ++iter)
	{
		buff.insert((LPCWSTR)iter->name.utf16(), (LPCWSTR)iter->texture.utf16(), (SubGraphRaw*)iter->param.raw);
	}
	QString path(m_basePath + "/subgraphics.pb");
	buff.save((LPCWSTR)path.utf16());
}

void EditorData::loadBulletStyles()
{
/*
	QFile in(m_basePath + "\\bulletstyles.json");
	if (!in.open(QFile::ReadOnly))
		return;

	QJsonParseError err;
	QJsonDocument doc = doc.fromJson(in.readAll(), &err);
	in.close();

	QJsonArray array = doc.array();
	for (auto iter = array.begin(); iter != array.end(); ++iter)
	{
		m_bulletStyles.emplace_back(BulletStyle());
		BulletStyle& dat = m_bulletStyles.back();

		QJsonObject obj = iter->toObject();
		dat.name = obj["name"].toString();
		dat.type = (BulletStyle::BulletType)obj["type"].toInt();
		dat.collide = (BulletStyle::CollideType)obj["collide"].toInt();
		dat.subGraph = obj["subgraph"].toString();

		QJsonArray params = obj["rect"].toArray();
		dat.centerX = params[0].toDouble();
		dat.centerY = params[1].toDouble();
		dat.radianX = params[2].toDouble();
		dat.radianY = params[3].toDouble();
	}
*/
	QString path(m_basePath + "/bulletstyles.pb");
	BulletSyltesBuf buff;
	if (buff.load((LPCWSTR)path.utf16()))
	{
		auto& map = buff.bulletStyles()->map();
		for (auto iter = map.begin(); iter != map.end(); ++iter)
		{
			m_bulletStyles.emplace_back(BulletStyle());
			BulletStyle& dat = m_bulletStyles.back();
			auto& style = iter->second;

			dat.name = QString::fromUtf8(iter->first.c_str());
			dat.type = (BulletStyle::BulletType)style.type();
			dat.subGraph = QString::fromUtf8(style.graphgroup().c_str());
			
			auto& collide = style.collide();
			dat.collide = (BulletStyle::CollideType)collide.type();
			dat.centerX = collide.centerx();
			dat.centerY = collide.centery();
			dat.radianX = collide.radianx();
			dat.radianY = collide.radiany();
		}
	}
}

void EditorData::saveBulletStyles()
{
/*
	QJsonArray array;
	for (auto iter = m_bulletStyles.begin(); iter != m_bulletStyles.end(); ++iter)
	{
		QJsonObject obj;

		obj.insert("name", iter->name);
		obj.insert("type", iter->type);
		obj.insert("collide", iter->collide);
		obj.insert("subgraph", iter->subGraph);

		QJsonArray rect;
		rect.push_back(iter->centerX);
		rect.push_back(iter->centerY);
		rect.push_back(iter->radianX);
		rect.push_back(iter->radianY);
		obj.insert("rect", rect);


		array.push_back(obj);
	}
	QJsonDocument doc(array);

	QFile out(m_basePath + "\\bulletstyles.json");
	if (out.open(QFile::WriteOnly))
	{
		out.write(doc.toJson());
		out.close();
	}
*/

	BulletSyltesBuf buff;
	auto& map = *buff.bulletStyles()->mutable_map();
	for (auto iter = m_bulletStyles.begin(); iter != m_bulletStyles.end(); ++iter)
	{
		auto& bullet = map[iter->name.toUtf8().toStdString()];
		bullet.set_type((BulletSyltesBuf::Type)iter->type);
		bullet.set_graphgroup(iter->subGraph.toUtf8().toStdString());

		auto& collide = *bullet.mutable_collide();
		collide.set_type((proto::Collide_CollideType)iter->collide);
		collide.set_centerx(iter->centerX);
		collide.set_centery(iter->centerY);
		collide.set_radianx(iter->radianX);
		collide.set_radianx(iter->radianY);
	}

	QString path(m_basePath + "/bulletstyles.pb");
	buff.save((LPCWSTR)path.utf16());
}

void EditorData::savePathSet()
{
	PathSetBuf buff;
	proto::Path* pPath = buff.pathset()->add_path();
	pPath->set_name("test");
	pPath->add_node()->mutable_emptynode()->set_time(100);
	{
		proto::LineNode* node = pPath->add_node()->mutable_linenode();
		node->set_time(200);
		node->set_xdetla(100);
		node->set_ydetla(100);
	}
	{
		proto::SineNode* node = pPath->add_node()->mutable_sinenode();
		node->set_time(400);
		node->set_ydetla(100);
		node->set_xscale(10);
		node->set_yscale(100);
	}

	QString path(m_basePath + "/pathset.pb");
	buff.save((LPCWSTR)path.utf16());
}
