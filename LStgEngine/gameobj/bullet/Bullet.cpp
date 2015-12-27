#include "stdafx.h"
#include "Bullet.h"
#include "player/player.h"
#include "Engine.h"
#include "LPainter.h"
#include "LImage.h"
#include "move/LPhysicWalker.h"
#include "Manager/MemoryManager.h"
#include "LBulletStyles.h"

Bullet::Bullet(IGameObject* pParent)
	: LCollideObject(pParent)
	, m_life(99 * 60)
{
	m_spWalker = LWalker::CreatePhysicWalker();
	m_renderArg.uDepth = DepthBullet;
	m_renderArg.paintArg.drawMode = DxDrawMode::Bilinear;
}

void Bullet::Update()
{
	if (m_phyData.position.x() < 0.0 ||
		m_phyData.position.x() > 450.0 ||
		m_phyData.position.y() < 0.0 ||
		m_phyData.position.y() > 480.0 ||
		--m_life == 0)	// 消亡检查	
	{
		m_bValid = false;
		return;
	}

	m_spWalker->nextStep(m_phyData);

#ifdef _DEBUG
	if (CollideWith(*StgEngine::engine()->GetActivePlayer()))
	{
		// 		PlaySoundMem(Resource::SE(NS_Resource::SE_Miss), DX_PLAYTYPE_BACK);
		// 		Sleep(100);
	}
#endif // _DEBUG
}

void Bullet::Draw( LPainter& painter )
{
	painter.drawRotaGraphF(m_phyData.position, 1, m_phyData.radian + Radian90, m_visual.hGraph, true);
}

void Bullet::setData(const PhysicData& data)
{
	m_phyData = data;
	updateRadian();
}

void* Bullet::operator new(size_t size)
{
	if (sizeof(Bullet) == size)
		return MemoryMgr.allocBullet();
	else
		return ::operator new(size);
}

void Bullet::operator delete(void* pObject, size_t size)
{
	if (sizeof(Bullet) == size)
		MemoryMgr.freeBullet(pObject);
	else
		return ::operator delete(pObject);
}

void Bullet::setSpeed(const Vector2& speed)
{
	m_phyData.speed = speed;
	updateRadian();
}

void Bullet::setSpeed(float speed, Degree direction)
{
	m_phyData.radian = direction.toRadian();
#if SINE_COSINE_ACCUR_LEVEL == 1
	m_phyData.speed.InitFromPolar(speed, direction);
#else
	m_phyData.speed.InitFromPolar(speed, m_phyData.radian);
#endif
}

void Bullet::setStyle(LBulletStyle* pStyle, uint elem)
{
	if (!pStyle)
		return;

	m_visual.pStyle = pStyle;
	m_visual.hGraph = pStyle->elems[elem];
	m_entity = pStyle->entity;
}

void Bullet::Rotate(Radian rad)	// 矢量旋转
{
	m_phyData.radian += rad;
	m_phyData.speed.rotate(rad);
}

void Bullet::setPosition(const Vector2& pos)
{
	m_phyData.position = pos;
	updateRadian();
}

const LGraphHandle Bullet::GetGraphHandle() const
{
	return m_visual.hGraph;
}
