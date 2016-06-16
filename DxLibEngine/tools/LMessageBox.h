#ifndef __LMESSAGEBOX_H__
#define __LMESSAGEBOX_H__

class LMessageBox
{
public:
	LMessageBox();
	~LMessageBox();

public:
	static void message(LPCWSTR lpMsg, LPCWSTR lpTitle);

};


#endif // __LMESSAGEBOX_H__
