#include "stdafx.h"
#include "LTcc.h"
#include "../TinyCC/libtcc.h"

LTcc::LTcc()
	: m_pContext(nullptr)
{
	m_pContext = tcc_new();
	LAssert(m_pContext);
}


LTcc::~LTcc()
{
	tcc_delete(m_pContext);
}
