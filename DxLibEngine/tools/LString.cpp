#include "stdafx.h"
#include "LString.h"
#include <codecvt>

LString& LString::assign(const char* pcstr)
{
	clear();
	while ('\0' != *pcstr)
		push_back(*pcstr);
	return (*this);
}

LString& LString::setNum(int val, int base /*= 10*/)
{
	const size_t buffsize = 33;
	WCHAR buff[buffsize] = { 0 };
	errno_t err = _itow_s(val, buff, base);
	LAssert(0 == err);
	Base::assign(buff);
	return (*this);
}

LString& LString::setNum(float val, int prec /*= 6*/)
{
	int decimal, sign;
	char buff[_CVTBUFSIZE + 1] = { 0 };
	_fcvt_s(buff, val, prec, &decimal, &sign);
	buff[_CVTBUFSIZE] = 0;
	assign(buff);
	return (*this);
}

std::string LString::toUtf8() const
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(c_str());
}

int LString::toInt(bool* pOk) const
{
	int result = _wtoi(c_str());
#if _DEBUG
	if (ERANGE == errno)
		LLogger::Warning(L"toInt: number overflow");
	else if (EINVAL == errno)
		LLogger::Warning(L"toInt: invalid argument");
#endif
	if (pOk)
		*pOk = (0 == errno);
	return result;
}

double LString::toNumber(bool* pOk) const
{
	double result = _wtof(c_str());
#if _DEBUG
	if (ERANGE == errno)
		LLogger::Warning(L"toInt: number overflow");
	else if (EINVAL == errno)
		LLogger::Warning(L"toInt: invalid argument");
#endif
	if (pOk)
		*pOk = (0 == errno);
	return result;
}

LString LString::fromUtf8(const std::string& bytes)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.from_bytes(bytes);
}

//////////////////////////////////////////////////////////////////////////
LStrBuilder::LStrBuilder(LPCWSTR pPattern)
{
	resetPattern(pPattern);
}

LStrBuilder::~LStrBuilder()
{

}

void LStrBuilder::resetPattern(LPCWSTR pPattern)
{
	m_pattern = pPattern;
	m_argCount = 0;
	m_chpxes.clear();
	m_args.clear();
	analyzePattern();
}

LString LStrBuilder::apply() const
{
	if (m_chpxes.empty() || m_args.empty())
		return m_pattern;

	LString result;
	size_t pos = 0;
	LPCWSTR pBegin = m_pattern.c_str();
	LPCWSTR pPos = pBegin;
	for (auto iter = m_chpxes.begin(); iter != m_chpxes.end(); ++iter)
	{
		const ChpxInfo& info = *iter;

		size_t prevLen = pBegin + info.begin - pPos;
		result.append(pPos, prevLen);
		result.append(m_args[info.argID]);

		pPos = pBegin + info.begin + info.len;
	}

	if (pPos < pBegin + m_pattern.size())
		result.append(pPos);

	return result;
}

void LStrBuilder::analyzePattern()
{
	const WCHAR* pBegin = m_pattern.c_str();
	const WCHAR* pEnd = pBegin + m_pattern.size();

	std::map<uint, uint> idMap;
	for (const WCHAR* pch = pBegin; pch < pEnd; ++pch)
	{
		if (*pch != L'%')
			continue;

		++pch;
		if (pch >= pEnd)
			break;

		const WCHAR ch = *pch;

		int num = ch - L'0';
		if (num <= 0 || num > 9)
			continue;

		const WCHAR* pArgBegin = pch - 1;
		if (pch + 1 < pEnd)
		{
			int num2 = pch[1] - L'0';
			if (num2 >= 0 && num2 <= 9)
			{
				++pch;
				num *= 10;
				num += num2;
			}
		}

		ChpxInfo info;
		info.begin = pArgBegin - pBegin;
		info.len = pch - pArgBegin + 1;
		info.argID = num;
		idMap[num] = 0;
		m_chpxes.push_back(info);
	}
	if (idMap.empty())
		return;

	uint relID = 0;
	for (auto iter = idMap.begin(); iter != idMap.end(); ++iter, ++relID)
		iter->second = relID;

	for (auto iter = m_chpxes.begin(); iter != m_chpxes.end(); ++iter)
		iter->argID = idMap[iter->argID];
}

bool LStrBuilder::isFull()
{
	if (m_args.size() >= m_argCount)
	{
		LAssert(!"Argument number mismatch!");
		return true;
	}
	return false;
}

LStrBuilder& LStrBuilder::arg(LPCWSTR val)
{
	m_args.push_back(val);
	return (*this);
}

LStrBuilder& LStrBuilder::arg(int val)
{
	m_args.push_back(LString().setNum(val));
	return (*this);
}

LStrBuilder& LStrBuilder::arg(float val)
{
	m_args.push_back(LString().setNum(val));
	return (*this);
}
