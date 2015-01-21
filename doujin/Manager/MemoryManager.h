#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__
#include "LObjectPool.hpp"
#include "bullet/Bullet.h"

#define MemoryMgr MemoryManager::Instance
class MemoryManager
{
	typedef LObjectPool<sizeof(Bullet)> BulletPool;
public:
	MemoryManager();
	~MemoryManager();

public:
	static MemoryManager Instance;

public:
	void* allocBullet() { return m_bulletPool.malloc(); }
	void freeBullet(void* pBullet) { m_bulletPool.free(pBullet); }

private:
	BulletPool m_bulletPool;
};


#endif	// __MEMORY_MANAGER_H__
