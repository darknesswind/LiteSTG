#include "stdafx.h"
#include "ComManage.h"
#include "Globle.h"
#include "interfaceDef.h"
#include "LRender.h"

void ComManager::Update()
{
	for each(auto *i in thisList)
	{
		i->Update();
	}
}

void ComManager::Draw() const
{	
	for each(auto *i in thisList)
	{
		i->Draw(StgEngine::render()->GetPainter());
	}
}

void ComManager::Remove(IComponent *component)
{
	thisList.remove(component);
}