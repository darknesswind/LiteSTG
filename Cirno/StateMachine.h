#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_
#pragma once

template <class UserType>
class State
{
public:
	virtual void Enter(UserType*) = 0;
	virtual void Execute(UserType*) = 0;
	// 	virtual void Draw(entityType*) = 0;
	virtual void Exit(UserType*) = 0;
	virtual ~State(void) {}
};

template <class UserType>
class StateMachine
{
public:
	typedef State<UserType> StateType;
	typedef UserType DataType;
public:
	StateMachine(UserType *d)
		: m_pData(d)
		, m_pCurState(nullptr)
		, m_pPrevState(nullptr)
		, m_pGlobalState(nullptr)
	{}
	virtual ~StateMachine(void) {};

	void Update() const
	{
		if (m_pGlobalState) m_pGlobalState->Execute(m_pData);
		if (m_pCurState) m_pCurState->Execute(m_pData);
	}
// 	void Draw() const
// 	{
// 		if (globalState) globalState->Draw(owner);
// 		if (currentState) currentState->Draw(owner);
// 	}
	void SetCurrentState(StateType* state) { m_pCurState = state; }
	void SetPreviousState(StateType* state) { m_pPrevState = state; }
	void SetGlobalState(StateType* state) { m_pGlobalState = state; }
	void ChangeState(StateType* state) 
	{
		if (!state) return;
		if (m_pCurState) m_pCurState->Exit(m_pData);

		m_pPrevState = m_pCurState;
		m_pCurState = state;
		m_pCurState->Enter(m_pData);
	}
private:
	UserType* m_pData;
	StateType* m_pCurState;
	StateType* m_pPrevState;
	StateType* m_pGlobalState;
};

#endif