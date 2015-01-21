#include "stdafx.h"
#include "Globle.h"
#include "Graph.h"
#include "Vector2.hpp"

void LoadDivGraphEx(const TCHAR *FileName,
					const int SrcX, const int SrcY, 
					const int AllNum, const int XNum, const int YNum, 
					const int XSize, const int YSize, 
					GraphHandle *HandleBuf, const int NotUse3DFlag)
{
	GraphHandle hTemp = DxLib::LoadGraph(FileName, NotUse3DFlag);
	for (int i=0; i<AllNum; ++i)
	{
		HandleBuf[i] = DxLib::DerivationGraph(SrcX + XSize*(i%XNum), SrcY + YSize*(i / XNum), XSize, YSize, hTemp);
	}
	DxLib::DeleteGraph(hTemp);
}
