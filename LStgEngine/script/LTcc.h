#ifndef __LTINYCC_H__
#define __LTINYCC_H__
#pragma once

class LTcc
{
public:
	LTcc();
	~LTcc();

	void init();

private:
	struct TCCState* m_pContext;
};


#endif
