#include "stdafx.h"
#include "Bullet.h"
#include "Globle.h"
#include "resource.h"
#include "DxLib.h"
#include <cmath>
#include "CollideEntity/Entity.h"
#include "player/player.h"
#include "Engine.h"
#include "LPainter.h"
#include "LImage.h"
#include "move/LPhysicWalker.h"
#include "Manager/MemoryManager.h"

Bullet::Bullet(IGameObject* pParent)
	: LGameObject(pParent)
	, m_life(99 * 60)
	, m_pEntity(nullptr)
{
	m_spWalker.reset(LWalker::CreatePhysicWalker());
	m_pEntity = EntityFactory::getBulletEntity(m_style.type);
#if USE_FASTFUNC
	m_funcList.push_back(timerFunc(this, &Bullet::Fun_test));
	m_funcList.push_back(timerFunc(this, &Bullet::Fun_turnToPlayer));
#endif
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

	mytimer.update();
#ifdef _DEBUG
	if (m_pEntity->isCollideWithPlayer(m_phyData.position, m_phyData.radian))
	{
		// 		PlaySoundMem(Resource::SE(NS_Resource::SE_Miss), DX_PLAYTYPE_BACK);
		// 		Sleep(100);
	}
#endif // _DEBUG
}

void Bullet::Draw( LPainter& painter )
{
	painter.drawRotaGraphF(m_phyData.position, 1, m_phyData.radian + Radian90, LImage(GetGraphHandle()), true);
}

void Bullet::DrawHitBox( LPainter& painter )
{
	m_pEntity->draw(painter, m_phyData.position, m_phyData.radian + Radian90);
}

void Bullet::setData(const PhysicData& data)
{
	m_phyData = data;
	updateRadian();
}

void Bullet::Fun_test(int &_counter)
{
	setAcceleration(0.02f, degreeBetween(*StgEngine::engine()->GetActivePlayer()));
	_counter = 1;
}
void Bullet::Fun_turnToPlayer(int &_counter)
{
	setSpeed(m_phyData.speed.length(), degreeBetween(*StgEngine::engine()->GetActivePlayer()));
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

void Bullet::setWalkerType(WalkerType type)
{
	m_spWalker.reset(LWalker::CreateWalker(type));
}

void Bullet::setBulletClass(const BulletClass type)
{
	m_style.type = type;
	updateEntity();
}

void Bullet::setStyle(const BulletStyle &style)
{
	m_style = style;
	updateEntity();
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
	return Resource::bullet(m_style);
}
