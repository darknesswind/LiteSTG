#pragma once
class LPlayerModle
{
public:
	LPlayerModle();
	~LPlayerModle();

	virtual void Load(LGraphHandle texture) = 0;
};

class LTHPlayerModle : LPlayerModle
{
public:
	using LPlayerModle::LPlayerModle;

	virtual void Load(LGraphHandle texture) override;

protected:
	LGraphHandles m_playerImgs;
	LGraphHandle m_privateImg;
};
