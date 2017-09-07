#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once
#include "LGameObject.h"

class LPlayerModel;
struct PlayerCharaData
{
	LString name;
	EntityData collide;
	EntityData graze;
	float normalSpeed{ 0 };
	float slowSpeed{ 0 };
	LString texture;
};

class LPlayer : public LCollideObject
{
public:
	enum InputType
	{
		VoidInput,
		UserInput,
	};

public:
	explicit LPlayer(InputType type);
	virtual ~LPlayer(void);

// 	void setModel(LPlayerModel* pModel);
	void setCharacter(uint id, const PlayerCharaData& chara);

public:	// IGameobj
	virtual void Update() override;
	virtual void draw(LPainter& painter) override;

public:	// Player
	virtual InputType GetType() const { return m_inputType; }

protected:
	InputType m_inputType{ VoidInput };
	PlayerCharaData m_character;
	destory_ptr<IWalker> m_spWalker;
	std::unique_ptr<LPlayerModel> m_spModel;

	int m_counter;
// 	int m_imgCount;
// 	int m_actionState;
// 	int m_nStarImg;
// 	int m_nEndImg;
	bool m_bCanShot;

	LGraphHandles m_playerImg;
	LGraphHandle m_hitBoxImg;
	LInput* m_pInput;
};
#endif