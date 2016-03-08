#pragma once

class LUITransferBase
{
public:
	virtual ~LUITransferBase() {};
	virtual void Update() = 0;
};

class LUITransferSet
{
public:
	LUITransferSet() = default;
	~LUITransferSet()
	{
		for each (LUITransferBase* pItem in m_animas)
			delete pItem;
	}
	void Update()
	{
		for each (LUITransferBase* pItem in m_animas)
			pItem->Update();
	}
	void AddChild(LUITransferBase* pChild)
	{
		m_animas.push_back(pChild);
	}
private:
	std::vector<LUITransferBase*> m_animas;
};

template <typename DatType>
class LUICosineTransfer : public LUITransferBase
{
public:
	LUICosineTransfer(DatType* pDat, uint interval, float amplitude)
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
