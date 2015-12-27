#include "stdafx.h"
#include "LBulletStyles.h"
#include "LAssets.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

LBulletStyles::LBulletStyles()
{

}

LBulletStyles::~LBulletStyles()
{

}

void LBulletStyles::LoadBulletStyles()
{
	QJsonParseError err;
	QJsonDocument doc = doc.fromJson(LAssets::LoadRawData(_T("resource\\bulletstyles.json")), &err);

	QJsonArray array = doc.array();
	for (auto iter = array.begin(); iter != array.end(); ++iter)
	{
		QJsonObject obj = (*iter).toObject();
		QString name = obj["name"].toString();
		LAssert(!name.isEmpty());

		m_styles.emplace_back(LBulletStyle());
		LBulletStyle& style = m_styles.back();
		style.type = (BulletType)obj["type"].toInt();
		style.entity.type = (EntityData::Type)obj["collide"].toInt();

		QString subgraph = obj["subgraph"].toString();
		style.elems = LEngine::assets()->GetSubGraphGroup(Q2WSTR(subgraph));

		QJsonArray rect = obj["rect"].toArray();
		style.entity.center.rx() = rect[0].toDouble();
		style.entity.center.ry() = rect[1].toDouble();
		style.entity.halfWidth = rect[2].toDouble();
		style.entity.halfHeight = rect[3].toDouble();

		m_nameMap[name.toStdWString()] = &style;
	}
}
