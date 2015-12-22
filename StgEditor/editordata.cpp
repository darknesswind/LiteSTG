#include "editordata.h"
#include <QSettings>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

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

QPixmap EditorData::getTexture(QString source)
{
	QPixmap& img = m_textureCache[source];
	if (img.isNull())
	{
		QString path = m_basePath + QDir::separator() + source;
		img = QPixmap::fromImage(QImage(path));
	}
	return img;
}

void EditorData::updateTextureRef(QString srcName, QString dstName)
{
	for (int i = 0; i < m_subGraphes.size(); ++i)
	{
		if (m_subGraphes[i].texture == srcName)
			m_subGraphes[i].texture = dstName;
	}
}

void EditorData::load()
{
	loadSettings();
	loadTextures();
	loadSubGraphies();
}

void EditorData::save()
{
	saveSettings();
	saveTextures();
	saveSubGraphies();
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
		m_subGraphes.push_back(SubGraphData());
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
