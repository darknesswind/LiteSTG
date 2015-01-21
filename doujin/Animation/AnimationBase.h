#ifndef __ANIMATION_BASE_H__
#define __ANIMATION_BASE_H__
#pragma once
#include "interfaceDef.h"

template<class DataType>
class AnimationBase : public IAnimateAtom
{
	friend class AnimationManager;

public:
	virtual ~AnimationBase(void)
	{
	}

public: // IAnimateAtom
	virtual void update() PURE;
	virtual bool isValid() const { return m_pDestData; }

public:
	void bind(DataType* pData)
	{
		LAssert(pData);
		m_pDestData = pData;
	}

protected:
	AnimationBase(void)
		: m_pDestData(nullptr)
	{
	}

protected:
	DataType* m_pDestData;
};

template<class DataType>
class SyncAnimationBase : public AnimationBase<DataType>
{
	friend class AnimationManager;
	typedef AnimationBase<DataType> Base;
public:
	virtual ~SyncAnimationBase(void)
	{
	}

public: // IAnimateAtom
	virtual void update()
	{
		if (!isValid())
		{
			m_pSrcHost = nullptr;
			m_pDestData = nullptr;
			m_pSrcData = nullptr;
		}
		else
		{
			*m_pDestData = *m_pSrcData;
		}
	}
	virtual bool isValid() const { return m_pSrcData && m_pSrcHost && m_pSrcHost->isValid() && Base::isValid(); }

public:
	void bind(const IAnimationSrcHost* pSrcHost, const DataType* pSrcData, DataType* pDestData)
	{
		LAssert(pSrcHost && pSrcData && pDestData);
		Base::bind(pDestData);
		m_pSrcData = pSrcData;
		m_pSrcHost = pSrcHost;
	}

private:
	void bind(DataType* pData);

protected:
	SyncAnimationBase(void)
		: Base(), m_pSrcData(nullptr), m_pSrcHost(nullptr)
	{
	}

protected:
	const DataType* m_pSrcData;
	const IAnimationSrcHost* m_pSrcHost;
};

#endif // __ANIMATION_BASE_H__
