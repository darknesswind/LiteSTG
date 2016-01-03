#include "editordata.h"
#include <QSettings>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <algorithm>
#include <QMessageBox>

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

namespace
{
	template<typename T1, typename T2>
	QJsonObject ToJsonObj(const QMap<T1, T2>& map)
	{
		QJsonObject obj;
		return obj;
	}
}

void EditorData::loadTextures()
{
	QFile in(m_basePath + "\\textures.json");
	if (!in.open(QFile::ReadOnly))
		return;

	QJsonParseError err;
	QJsonDocument doc = doc.fromJson(in.readAll(), &err);
	in.close();

	QJsonObject obj = doc.object();
	for (auto iter = obj.begin(); iter != obj.end(); ++iter)
	{
		m_textures[iter.key()] = iter.value().toString();
// 		m_textures[iter.value().toString()] = iter.key();
	}
}

void EditorData::saveTextures()
{
	QJsonObject obj;
	for (auto iter = m_textures.begin(); iter != m_textures.end(); ++iter)
	{
		obj.insert(iter.key(), iter.value());
// 		obj.insert(iter.value(), iter.key());
	}
	QJsonDocument doc(obj);

	QFile out(m_basePath + "\\textures.json");
	if (out.open(QFile::WriteOnly))
	{
		out.write(doc.toJson());
		out.close();
	}
}

void EditorData::loadSubGraphies()
{
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
}

void EditorData::saveSubGraphies()
{
	QJsonArray array;
	for (auto iter = m_subGraphes.begin(); iter != m_subGraphes.end(); ++iter)
	{
		QJsonObject obj;

		obj.insert("name", iter->name);
		obj.insert("texture", iter->texture);
		
		QJsonArray params;
		for (int i = 0; i < SubGraphData::ParamCount; ++i)
			params.push_back(iter->param.raw[i]);
		obj.insert("params", params);

		array.push_back(obj);
	}
	QJsonDocument doc(array);

	QFile out(m_basePath + "\\subgraphics.json");
	if (out.open(QFile::WriteOnly))
	{
		out.write(doc.toJson());
		out.close();
	}
}

void EditorData::loadBulletStyles()
{
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
}

void EditorData::saveBulletStyles()
{
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
}
