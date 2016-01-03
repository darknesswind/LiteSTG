#ifndef _STATE_H_
#define _STATE_H_
#pragma once
template <class entityType>
class State
{
public:
	virtual void Enter(entityType*)=0;
	virtual void Execute(entityType*)=0;
	virtual void Draw(entityType*)=0;
	virtual void Exit(entityType*)=0;
	virtual ~State(void){}
};
#endif