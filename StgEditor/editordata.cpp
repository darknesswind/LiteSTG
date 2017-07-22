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

QPixmap EditorData::getTextureByPath(QString source)
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
	if (m_textures.contains(name))
		return getTextureByPath(m_textures[name].path);

	return QPixmap();
}

QPixmap EditorData::getTexture(const SubGraphData* pDat)
{
	if (0 == pDat->iTexture)
		return QPixmap();

	return getTextureByPath(m_textures[pDat->iTexture].path);
}

void EditorData::removeTexture(const QString& name)
{
	m_textureCache.remove(m_textures[name].path);
	m_textures.erase(name);
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

	m_textures.eraseNotify().registerNotify(&m_subGraphes);
	m_subGraphes.eraseNotify().registerNotify(&m_bulletStyles);
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
	QString path = m_basePath + "\\textures.pb.json";
	if (buff.loadFromText((LPCWSTR)path.utf16()))
	{
		auto& list = buff.textures()->texture();
		for (auto iter = list.begin(); iter != list.end(); ++iter)
		{
			m_textures.append(Texture(iter->name(), iter->path()));
		}
	}
}

void EditorData::saveTextures()
{
	TextureBuf buff;

	for (const Texture& texture : m_textures)
	{
		buff.insert((LPCWSTR)texture.path.utf16(), (LPCWSTR)texture.name().utf16());
	}

	QString path = m_basePath + "\\textures.pb";
	buff.saveBinary((LPCWSTR)path.utf16());
	buff.saveText((LPCWSTR)(path + ".json").utf16());
}

void EditorData::loadSubGraphies()
{
	SubGraphicsBuf buff;
	QString path = m_basePath + "/subgraphics.pb.json";
	if (buff.loadFromText((LPCWSTR)path.utf16()))
	{
		auto& map = buff.subgraphics()->map();
		for (auto iter = map.begin(); iter != map.end(); ++iter)
		{
			QString name = QString::fromUtf8(iter->first.c_str());
			auto infos = iter->second.info();
			for (auto itInfo = infos.begin(); itInfo != infos.end(); ++itInfo)
			{
				auto& info = *itInfo;
				SubGraphData dat(name);
	
				dat.iTexture = m_textures.idOfName(QString::fromUtf8(info.texture().c_str()));
				dat.srcX = info.xsrc();
				dat.srcY = info.ysrc();
				dat.allNum = info.allnum();
				dat.numX = info.xnum();
				dat.numY = info.ynum();
				dat.sizeX = info.width();
				dat.sizeY = info.height();
				m_subGraphes.append(dat);
			}
		}
	}
}

void EditorData::saveSubGraphies()
{
	SubGraphicsBuf buff;
	for (auto iter = m_subGraphes.begin(); iter != m_subGraphes.end(); ++iter)
	{
		LPCWSTR lpName = (LPCWSTR)iter->name().utf16();
		LPCWSTR lpTexture = (LPCWSTR)m_textures.nameOfId(iter->iTexture).utf16();
		buff.insert(lpName, lpTexture, (SubGraphRaw*)iter->raw);
	}
	QString path(m_basePath + "/subgraphics.pb");
	buff.saveBinary((LPCWSTR)path.utf16());
	buff.saveText((LPCWSTR)(path + ".json").utf16());
}

void EditorData::loadBulletStyles()
{
	QString path(m_basePath + "/bulletstyles.pb.json");
	BulletSyltesBuf buff;
	if (buff.loadFromText((LPCWSTR)path.utf16()))
	{
		auto& map = buff.bulletStyles()->map();
		for (auto iter = map.begin(); iter != map.end(); ++iter)
		{
			BulletStyle dat(QString::fromUtf8(iter->first.c_str()));

			auto& style = iter->second;

			dat.type = (BulletStyle::BulletType)style.type();
			QString subGraphName = QString::fromUtf8(style.graphgroup().c_str());
			dat.iSubGraph = m_subGraphes.idOfName(subGraphName);
			
			auto& collide = style.collide();
			dat.collide = (BulletStyle::CollideType)collide.type();
			dat.centerX = collide.centerx();
			dat.centerY = collide.centery();
			dat.radianX = collide.radianx();
			dat.radianY = collide.radiany();

			m_bulletStyles.append(dat);
		}
	}
}

void EditorData::saveBulletStyles()
{
	BulletSyltesBuf buff;
	auto& map = *buff.bulletStyles()->mutable_map();
	for (const BulletStyle& style : m_bulletStyles)
	{
		auto& bullet = map[style.name().toUtf8().toStdString()];
		bullet.set_type((BulletSyltesBuf::Type)style.type);

		QString subGraphName = m_subGraphes.nameOfId(style.iSubGraph);
		bullet.set_graphgroup(subGraphName.toUtf8().toStdString());

		auto& collide = *bullet.mutable_collide();
		collide.set_type((proto::Collide_CollideType)style.collide);
		collide.set_centerx(style.centerX);
		collide.set_centery(style.centerY);
		collide.set_radianx(style.radianX);
		collide.set_radianx(style.radianY);
	}

	QString path(m_basePath + "/bulletstyles.pb");
	buff.saveBinary((LPCWSTR)path.utf16());
	buff.saveText((LPCWSTR)(path + ".json").utf16());
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
	buff.saveBinary((LPCWSTR)path.utf16());
	buff.saveText((LPCWSTR)(path + ".json").utf16());
}
