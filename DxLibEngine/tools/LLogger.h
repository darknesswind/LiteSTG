#ifndef __LLOGGER_H__
#define __LLOGGER_H__
#pragma once

class LLogger
{
public:
	enum LogLevel
	{
		lvInfo,
		lvWarning,
		lvError,
	};

public:
	LLogger();
	~LLogger();

public:
	static void Print(LogLevel level, LPCWSTR msg);
	static void Info(LPCWSTR msg) { Print(lvInfo, msg); };
	static void Warning(LPCWSTR msg) { Print(lvWarning, msg); };
	static void Error(LPCWSTR msg) { Print(lvError, msg); };
	static void Warning(const std::wstring& msg) { Warning(msg.c_str()); };
	static void Error(const std::wstring& msg) { Error(msg.c_str()); };

private:

};

#endif	// !__LLOGGER_H__