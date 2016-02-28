#pragma once

class LUIAnimeBase
{
public:
	virtual ~LUIAnimeBase() {};
	virtual void Update() = 0;
};


class LUIAnimation
{
public:
	LUIAnimation() = default;
	~LUIAnimation()
	{
		for each (LUIAnimeBase* pItem in m_animas)
			delete pItem;
	}
	void Update()
	{
		for each (LUIAnimeBase* pItem in m_animas)
			pItem->Update();
	}
	void AddChild(LUIAnimeBase* pChild)
	{
		m_animas.push_back(pChild);
	}
private:
	std::vector<LUIAnimeBase*> m_animas;
};

template <typename DatType>
class LUICosineAnima : public LUIAnimeBase
{
public:
	LUICosineAnima(DatType* pDat, uint interval, float amplitude)
		: m_pData(pDat)
		, m_interval(interval)
		, m_amplitude(amplitude)
	{
		*m_pData = m_amplitude;
		m_step = L_PI2 / m_interval;
	}
	void Update()
	{
		m_phase += m_step;
		*m_pData = m_amplitude * (1 + m_phase.cos()) / 2;
	}

private:
	DatType* m_pData;
	Radian m_phase;
	float m_step;

	uint m_interval;	// 一个周期的间隔
	float m_amplitude;
};
