#pragma once

class LAnimePart
{
public:
	LAnimePart() = default;
	~LAnimePart() = default;

	void EnterCut();
	void Update();

protected:
	uint m_curIdx;
	uint m_loopPos;
	std::vector<LGraphHandle> m_graphs;
};