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

// 	m_actionState = 5;
// 	m_nStarImg = 0;
// 	m_nEndImg = 7;
// 
// 	m_imgCount = 0;
	m_bCanShot = true;

	m_renderArg.uDepth = DepthCharacter;
	m_hitboxClr = LRgb::Lime;
	m_hitBoxImg = LStgEngine::assets()->GetSubGraphGroup(__T("≈–∂®µ„"))[0];
}

LPlayer::~LPlayer(void)
{
}
/*
void LPlayer::setModel(LPlayerModel* pModel)
{
	if (pModel)
		m_pModel = pModel;
}
*/

void LPlayer::setCharacter(uint id, const PlayerCharaData& chara)
{
	m_character = chara;
// 	m_playerImg = LStgEngine::assets()->GetSubGraphGroup(__T("¡È√Œ"));
	m_spModel = std::make_unique<LTHPlayerModel>();
	m_spModel->load(LStgEngine::assets()->GetTexture(m_character.texture));
}

void LPlayer::Update()
{
	m_spWalker->nextStep(m_phyData);

	m_phyData.position.rx() = max(min(m_phyData.position.x(), 408), 40);
	m_phyData.position.ry() = max(min(m_phyData.position.y(), 448), 32);

	if ((m_counter & 0x1) == 0x1)
		m_phyData.radian += Radian(.02f);

/*
#pragma region ImgControl
	if (m_spModel)
		m_spModel->update();

	switch (m_actionState)
	{
	case 4:
		if (!m_pInput->isLogicKeyDown(StgKey::Left) || m_pInput->isLogicKeyDown(StgKey::Right))
		{
			m_actionState += 1;
			m_imgCount = 0;
			m_nStarImg = 0;
			m_nEndImg = 7;
		}
		break;
	case 5:
		if (m_pInput->isLogicKeyDown(StgKey::Left))
		{
			m_actionState -= 1;
			m_imgCount = 8;
			m_nStarImg = 11;
			m_nEndImg = 15;
		}
		if (m_pInput->isLogicKeyDown(StgKey::Right))
		{
			m_actionState += 1;
			m_imgCount = 16;
			m_nStarImg = 19;
			m_nEndImg = 23;
		}
		break;
	case 6:
		if (!m_pInput->isLogicKeyDown(StgKey::Right) || m_pInput->isLogicKeyDown(StgKey::Left))
		{
			m_actionState -= 1;
			m_imgCount = 0;
			m_nStarImg = 0;
			m_nEndImg = 7;
		}
		break;
	}
	m_imgCount += (m_counter % 5 == 0);
	if (m_imgCount > m_nEndImg)	m_imgCount = m_nStarImg;

#pragma endregion ImgControl
*/

	m_counter++;
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
