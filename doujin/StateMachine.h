#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_
#pragma once
#include "State.h"
template <class entityType>
class StateMachine
{
public:
	StateMachine(entityType *o) : owner(o), currentState(nullptr), previousState(nullptr), globalState(nullptr)	{}
	virtual ~StateMachine(void){};

	void Update() const
	{
		if (globalState) globalState->Execute(owner);
		if (currentState) currentState->Execute(owner);
	}
	void Draw() const
	{
		if (globalState) globalState->Draw(owner);
		if (currentState) currentState->Draw(owner);
	}
	void setCurrentState(State<entityType>* state)
	{
		currentState = state;
	}
	void setPreviousState(State<entityType>* state)
	{
		previousState = state;
	}
	void setGlobalState(State<entityType>* state)
	{
		globalState = state;
	}
	void ChangeState(State<entityType>* state)
	{
		if (!state) return;
		if (currentState) currentState->Exit(owner);
		previousState = currentState;
		currentState = state;
		currentState->Enter(owner);
	}
private:
	entityType *owner;
	State<entityType> *currentState;
	State<entityType> *previousState;
	State<entityType> *globalState;
};

#endif