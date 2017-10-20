#include "stdafx.h"
#include "LHandle.h"
#include "DxHandle.h"
#include "tools/LSize.h"

LGraphHandle LGraphHandle::NoneGraph;

bool LHandle::checkValidType(DxHandleType targetType) const
{
	const bool bAsync = true;
	DxLib::HANDLEMANAGE& manage = DxLib::HandleManageArray[static_cast<uint>(targetType)];

	if ((manage.InitializeFlag == FALSE) ||
		hasError() ||
		((m_handle & TypeMask) != manage.HandleTypeMask) ||
		index() >= static_cast<uint>(manage.MaxNum))
		return false;

	const DxLib::HANDLEINFO* pInfo = manage.Handle[m_handle & IndexMask];
	if (!pInfo || (static_cast<int>(pInfo->ID << CheckOffset) != (m_handle & CheckMask)))
		return false;

	if (!bAsync && pInfo->ASyncLoadCount != 0)
		return false;

	return true;
}

const DxLib::HANDLEINFO* LHandle::innerData() const
{
	LAssert(checkValidType(type()));
	return DxLib::HandleManageArray[static_cast<uint>(type())].Handle[index()];
}

void LGraphHandle::getSize(LSize& size)
{
	CheckRes(DxLib::GetGraphSize(m_handle, &size.rwidth(), &size.rheight()));
}

LGraphHandles LGraphHandle::split(int xSrc, int ySrc, int allNum, int xNum, int yNum, int width, int height)
{
	LGraphHandles result;

	int sizeX = 0, sizeY = 0;
	DxLib::GetGraphSize(m_handle, &sizeX, &sizeY);
	for (int i = 0; i < allNum; ++i)
	{
		int srcX = xSrc + width * (i % xNum);
		int srcY = ySrc + height * (i / xNum);
		if (srcX + width > sizeX || srcY + height > sizeY)
			continue;

		LGraphHandle hDivGraph = subGraph(srcX, srcY, width, height);

		result.push_back(hDivGraph);
	}
	return result;
}

LGraphHandle LGraphHandle::subGraph(int xSrc, int ySrc, int width, int height)
{
	return DxLib::DerivationGraph(xSrc, ySrc, width, height, m_handle);
}
