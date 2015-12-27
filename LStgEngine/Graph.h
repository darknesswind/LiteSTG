#ifndef _GRAPH_H_
#define _GRAPH_H_
#pragma once
#include "interdef.h"
class Vector2;
extern void LoadDivGraphEx(const TCHAR *FileName,
						const int SrcX, const int SrcY, 
						const int AllNum, const int XNum, const int YNum, 
						const int XSize, const int YSize, 
						int *HandleBuf, const int NotUse3DFlag=0);

#endif

