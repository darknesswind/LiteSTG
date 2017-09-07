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

void LBulletStyles::LoadAssets(LPCWSTR path)
{
	BulletSyltesBuf buff;
	if (buff.load(LAssets::LoadRawData(path)))
	{
		for (auto& bs : buff.msg()->styles())
		{
			m_styles.emplace_back(LBulletStyle());
			LBulletStyle& style = m_styles.back();

			style.type = (BulletType)bs.type();
			style.elems = LEngine::assets()->GetSubGraphGroup(LString::fromUtf8(bs.graphgroup()));

			style.entity.fromConfig(bs.collide());

			m_nameMap[LString::fromUtf8(bs.name())] = m_styles.size() - 1;
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