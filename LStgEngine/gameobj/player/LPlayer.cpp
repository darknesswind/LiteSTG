#include "stdafx.h"
#include "LPlayer.h"
#include "move/LWalker.h"
#include "LHandle.h"
#include "LPlayerModel.h"
#include "Input.h"
#include "LAssets.h"

LPlayer::LPlayer(InputType type)
	: m_inputType(type)
{
	m_phyData.position.reset(220, 400);
	m_renderArg.uDepth = DepthBackground;

	m_pInput = LStgEngine::input();
	switch (m_inputType)
	{
	case LPlayer::UserInput:
		m_spWalker = LWalker::CreateControlledWalker();
		break;
	default:
		m_spWalker = LWalker::CreateStableWalker();
		break;
	}

	m_renderArg.uDepth = DepthCharacter;
	m_hitboxClr = LRgb::Lime;
	m_hitBoxImg = LStgEngine::assets()->GetSubGraphGroup(__T("ÅÐ¶¨µã"))[0];
}

LPlayer::~LPlayer(void)
{
}

void LPlayer::setCharacter(uint id, const PlayerCharaData& chara)
{
	UNUSED(id);
	m_character = chara;
	m_spModel = std::make_unique<LTHPlayerModel>();
	m_spModel->load(LStgEngine::assets()->GetTexture(m_character.texture));
}

void LPlayer::Update()
{
	m_spWalker->nextStep(m_phyData);

	m_phyData.position.rx() = max(min(m_phyData.position.x(), 408), 40);
	m_phyData.position.ry() = max(min(m_phyData.position.y(), 448), 32);

	if ((++m_counter & 0x1) == 0x1)
		m_phyData.radian += Radian(.02f);

	if (m_spModel)
	{
		uint state = LPlayerModel::stNormal;
		if (m_phyData.speed.x() > 0)
			state = LPlayerModel::stRight;
		else if (m_phyData.speed.x() < 0)
			state = LPlayerModel::stLeft;
		m_spModel->update(state);
	}
}

void LPlayer::draw(LPainter& painter)
{
	if (m_spModel)
	{
		painter.drawRotaGraphF(m_phyData.position, 1, Radian0, m_spModel->anime().graph(), true);
	}
	if (m_pInput->isLogicKeyDown(StgKey::Slow))
	{
		painter.setDrawMode(DxDrawMode::Bilinear);
		painter.drawRotaGraphF(m_phyData.position, 1, -m_phyData.radian, m_hitBoxImg, true);
		painter.drawRotaGraphF(m_phyData.position, 1, m_phyData.radian, m_hitBoxImg, true);
		painter.setDrawMode(DxDrawMode::Nearest);
	}
	DrawHitBox(painter);
}
