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
	static void Print(const QString& msg, LogLevel level);
	static void PrintInfo(const QString& msg);
	static void PrintWarning(const QString& msg);
	static void PrintError(const QString& msg);

private:

};

#endif	// !__LLOGGER_H__