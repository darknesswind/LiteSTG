#include "stdafx.h"
#include "LHandle.h"
#include "DxHandle.h"
#include "LSize.h"

LGraphHandle LGraphHandle::NoneGraph;

bool LHandle::checkValidType(DxHandleType targetType) const
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
	LAssert(checkValidType(type()));
	return DxLib::HandleManageArray[(uint)type()].Handle[index()];
}

void LGraphHandle::getSize(LSize& size)
{
	CheckRes(DxLib::GetGraphSize(m_handle, &size.rwidth(), &size.rheight()));
}
