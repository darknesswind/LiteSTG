#include "stdafx.h"
#include "LPathSet.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

#define CheckCurPath()\
{\
	if (nullptr == m_pReadingPath)\
	{\
		qDebug() << QString("line %1: not in a Path Node!").arg(reader.lineNumber());\
	}\
}

LPathSet::LPathSet()
{
	LPathNodes& path = m_paths[0];
	path.setID(0);
	path.setName("NULL");
}

LPathSet::~LPathSet()
{
}

std::map<QString, LPathSet::PathNodeID> LPathSet::s_parser;
void LPathSet::setupParseMap()
{
	if (s_parser.empty())
	{
		s_parser["Path"] = xPath;
		s_parser["EmptyNode"] = xEmptyNode;
		s_parser["LineNode"] = xLineNode;
		s_parser["SineNode"] = xSineNode;
	}
}

bool LPathSet::load(LPCWSTR lpFile)
{
	if (!lpFile)
		return false;
	setupParseMap();

	QString sFile = QString::fromUtf16((const ushort*)lpFile);
	QFile file(sFile);
	if (!file.open(QFile::ReadOnly))
	{
		qDebug() << file.errorString();
		return false;
	}

	QXmlStreamReader reader(&file);
	return parse(reader);
}

const LPathNodes* LPathSet::getPath(uint id)
{
	auto iter = m_paths.find(id);
	if (iter != m_paths.end())
		return &iter->second;
	else
		return nullptr;
}

void LPathSet::clear()
{
	m_paths.clear();
}

bool LPathSet::parse(QXmlStreamReader& reader)
{
	if (s_parser.empty())
		setupParseMap();

	reader.readNextStartElement();
	if ("PathSet" != reader.qualifiedName())
	{
		qDebug() << QString("not a path set file!");
		return false;
	}

	reader.readNextStartElement();
	while (!reader.atEnd())
	{
		QString label = reader.qualifiedName().toString();
		auto iter = s_parser.find(label);
		if (s_parser.end() == iter)
		{
			reader.skipCurrentElement();
		}
		else
		{
			PathNodeID id = s_parser[label];
			switch (id)
			{
			case LPathSet::xPath:
				parsePath(reader);
				break;
			case LPathSet::xEmptyNode:
				parseEmptyNode(reader);
				break;
			case LPathSet::xLineNode:
				parseLineNode(reader);
				break;
			case LPathSet::xSineNode:
				parseSineNode(reader);
				break;
			default:
				break;
			}
		}
		QXmlStreamReader::TokenType type = reader.readNext();
		while (type != QXmlStreamReader::StartElement && !reader.atEnd())
		{
			if (QXmlStreamReader::EndElement == type)
			{
				if ("Path" == reader.name())
					m_pReadingPath = nullptr;
			}
			type = reader.readNext();
		}
	}
	if (reader.hasError())
	{
		qDebug() << reader.errorString();
		return false;
	}
	return true;
}

void LPathSet::parsePath(QXmlStreamReader& reader)
{
	QXmlStreamAttributes& attr = reader.attributes();
	uint id = attr.value("id").toUInt();

	LPathNodes& path = m_paths[id];
	path.setID(id);
	path.setName(attr.value("name").toString());
	m_pReadingPath = &path;
}

void LPathSet::parseEmptyNode(QXmlStreamReader& reader)
{
	CheckCurPath();
	QXmlStreamAttributes& attr = reader.attributes();
	uint time = attr.value("time").toUInt();

	m_pReadingPath->AddEmptyNode(time);
}

void LPathSet::parseLineNode(QXmlStreamReader& reader)
{
	CheckCurPath();
	QXmlStreamAttributes& attr = reader.attributes();
	uint time = attr.value("time").toUInt();

	float dx = getFloatAttr(attr, "dx");
	float dy = getFloatAttr(attr, "dy");

	m_pReadingPath->AddLineNode(Vector2(dx, dy), time);
}

void LPathSet::parseSineNode(QXmlStreamReader& reader)
{
	CheckCurPath();
	QXmlStreamAttributes& attr = reader.attributes();
	uint time = attr.value("time").toUInt();

	float dx = getFloatAttr(attr, "dx");
	float dy = getFloatAttr(attr, "dy");
	float sx = getFloatAttr(attr, "sx", 1);
	float sy = getFloatAttr(attr, "sy", 1);

	m_pReadingPath->AddSineNode(Vector2(dx, dy), Vector2(sx, sy), time);
}

int LPathSet::getIntAttr(QXmlStreamAttributes& attr, const QString& key, int defVal /*= 0*/)
{
	bool bOk = true;
	int res = attr.value(key).toInt(&bOk);
	if (!bOk)
		res = defVal;
	return res;
}

float LPathSet::getFloatAttr(QXmlStreamAttributes& attr, const QString& key, float defVal /*= 0*/)
{
	bool bOk = true;
	float res = attr.value(key).toFloat(&bOk);
	if (!bOk)
		res = defVal;
	return res;
}
