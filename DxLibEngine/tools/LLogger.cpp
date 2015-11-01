#include "stdafx.h"
#include "LLogger.h"
#include <QDebug>

LLogger::LLogger()
{

}

LLogger::~LLogger()
{

}

void LLogger::Print(LogLevel level, const QString& msg)
{
	if (Error == level)
	{
		LAssert(!L"Error happened!");
	}
	qDebug() << msg;
}
