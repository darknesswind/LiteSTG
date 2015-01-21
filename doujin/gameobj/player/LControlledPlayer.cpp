#include "stdafx.h"
#include "LControlledPlayer.h"
#include "Globle.h"
#include "Input.h"
#include "resource.h"
#include "Factory/EntityFactory.h"
#include "CollideEntity/RoundEntity.h"
#include "LPainter.h"
#include "LImage.h"
#include "move/LWalker.h"

LControlledPlayer::LControlledPlayer(int x, int y)
{
	m_spWalker.reset(LWalker::CreateWalker(WalkerType::Controlled));
	m_phyData.position.Init(x, y);

	m_actionState = 5;
	m_nStarImg = 0;
	m_nEndImg = 7;
	m_CharacterID = 0;

	m_imgCount = 0;
	m_bCanShot = true;

	m_entity = EntityFactory::getPlayerEntity(m_CharacterID);
	m_renderArg.uDepth = DepthCharacter;
}


LControlledPlayer::~LControlledPlayer(void)
{
}

void LControlledPlayer::Update()
{
	m_spWalker->nextStep(m_phyData);

	m_phyData.position.rx() = max(min(m_phyData.position.x(), 408), 40);
	m_phyData.position.ry() = max(min(m_phyData.position.y(), 448), 32);

	if ((m_counter & 0x1) == 0x1)
		m_phyData.radian += Radian(.02f);

#pragma region ImgControl
	switch (m_actionState)
	{	
	case 4:
		if (!Input.isKeyDown(Keys::Left) || Input.isKeyDown(Keys::Right))	
		{
			m_actionState += 1;
			m_imgCount = 0;
			m_nStarImg = 0;
			m_nEndImg = 7;
		}
		break;
	case 5:
		if (Input.isKeyDown(Keys::Left)) 
		{
			m_actionState -= 1;
			m_imgCount = 8;
			m_nStarImg = 11;
			m_nEndImg = 15;
		}
		if (Input.isKeyDown(Keys::Right))
		{
			m_actionState += 1;
			m_imgCount = 16;
			m_nStarImg = 19;
			m_nEndImg = 23;
		}
		break;
	case 6:
		if (!Input.isKeyDown(Keys::Right) || Input.isKeyDown(Keys::Left))	
		{
			m_actionState -= 1;
			m_imgCount = 0;
			m_nStarImg = 0;
			m_nEndImg = 7;
		}
		break;
	}
	m_imgCount += (m_counter % 5 == 0);
	if (m_imgCount>m_nEndImg)	m_imgCount = m_nStarImg;

#pragma endregion ImgControl

	m_counter++;
}

void LControlledPlayer::Draw()
{
	Painter.drawRotaGraphF(m_phyData.position, 1, Radian0, LImage(GetGraphHandle()), true);
	if (Input.isKeyDown(Keys::LShift))
	{
		Painter.setDrawMode(DxDrawMode::Bilinear);
		Painter.drawRotaGraphF(m_phyData.position, 1, -m_phyData.radian, LImage(Resource::hitBox()), true);
		Painter.drawRotaGraphF(m_phyData.position, 1, m_phyData.radian, LImage(Resource::hitBox()), true);
		Painter.setDrawMode(DxDrawMode::Nearest);
	}
}

void LControlledPlayer::DrawHitBox()
{
	m_entity->draw(m_phyData.position, Radian0);
}

const LGraphHandle LControlledPlayer::GetGraphHandle() const
{
	return Resource::player(m_imgCount);
}