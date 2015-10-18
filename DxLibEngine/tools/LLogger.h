#ifndef __LLOGGER_H__
#define __LLOGGER_H__
#pragma once

class LLogger
{
public:
	enum LogLevel
	{
		Info,
		Warning,
		Error,
	};

public:
	LLogger();
	~LLogger();

public:
	static void Print(LogLevel level, const QString& msg);
	static void PrintInfo(const QString& msg) { Print(Info, msg); };
	static void PrintWarning(const QString& msg) { Print(Warning, msg); };
	static void PrintError(const QString& msg) { Print(Error, msg); };

private:

};

#endif	// !__LLOGGER_H__