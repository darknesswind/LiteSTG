#include "stdafx.h"
#include "LBulletStyles.h"
#include "LAssets.h"
#include "protobuf.h"

LBulletStyles::LBulletStyles()
{

}

LBulletStyles::~LBulletStyles()
{

}

void LBulletStyles::LoadBulletStyles(LPCWSTR path)
{
	BulletSyltesBuf buff;
	if (buff.load(LAssets::LoadRawData(path)))
	{
		auto& map = buff.bulletStyles()->map();
		for (auto iter = map.begin(); iter != map.end(); ++iter)
		{
			m_styles.emplace_back(LBulletStyle());
			LBulletStyle& style = m_styles.back();

			const proto::BulletStyle& bs = iter->second;

			style.type = (BulletType)bs.type();
			style.elems = LEngine::assets()->GetSubGraphGroup(LString::fromUtf8(bs.graphgroup()).c_str());

			style.entity.type = (EntityData::Type)bs.collide().type();
			style.entity.center.rx() = bs.collide().centerx();
			style.entity.center.ry() = bs.collide().centery();
			style.entity.halfWidth = bs.collide().radianx();
			style.entity.halfHeight = bs.collide().radiany();

			m_nameMap[LString::fromUtf8(iter->first)] = m_styles.size() - 1;
			if (!m_defStyles[(uint)style.type])
				m_defStyles[(uint)style.type] = m_styles.size() - 1;
		}
	}
}

LBulletStyle* LBulletStyles::getStyle(LPCWSTR name)
{
	auto iter = m_nameMap.find(name);
	if (iter != m_nameMap.end())
		return getStyle(iter->second);
	else
		return getDefaultStyle(BulletType::Generic);
}