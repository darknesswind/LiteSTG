#include "stdafx.h"
#include "LHandle.h"
#include "DxHandle.h"

LGraphHandle LGraphHandle::NoneGraph;

bool LHandle::checkValid(DxHandleType targetType) const
{
	bool bAsync = true;
	DxLib::HANDLEMANAGE& manage = DxLib::HandleManageArray[(uint)targetType];

	if ((manage.InitializeFlag == FALSE) ||
		hasError() ||
		((m_handle & TypeMask) != manage.HandleTypeMask) ||
		index() >= (uint)manage.MaxNum)
		return false;

	DxLib::HANDLEINFO* pInfo = manage.Handle[m_handle & IndexMask];
	if (!pInfo || ((int)(pInfo->ID << CheckOffset) != (m_handle & CheckMask)))
		return false;

	if (!bAsync && pInfo->ASyncLoadCount != 0)
		return false;

	return true;
}

const DxLib::HANDLEINFO* LHandle::innerData() const
{
	LAssert(checkValid(type()));
	return DxLib::HandleManageArray[(uint)type()].Handle[index()];
}
