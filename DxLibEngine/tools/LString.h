#pragma once
#include <string>
#include <sstream>

class LString : public std::wstring
{
	typedef std::wstring Base;
public:
	LString() = default;
	LString(LPCWSTR wcstr) : Base(wcstr) {}
	LString(Base&& base) : Base(base) {}

	LString& assign(const char* pcstr);

	LString& setNum(int val, int base = 10);
	LString& setNum(float val, int prec = 6);

	std::string toUtf8() const;

	int toInt(bool* pOk) const;
	double toNumber(bool* pOk) const;

public:
	static LString number(int val, int base = 10) { return LString().setNum(val, base); }
	static LString fromUtf8(const std::string& bytes);
};

class LStrBuilder
{
public:
	LStrBuilder(LPCWSTR pPattern);
	LStrBuilder(LPCSTR pPattern);
	~LStrBuilder();

	void resetPattern(LPCWSTR pPattern);
	LString apply();

	LStrBuilder& arg(LPCWSTR val);
	LStrBuilder& arg(int val);
	LStrBuilder& arg(float val);

	LStrBuilder& arg(const std::wstring& val) { return arg(val.c_str()); }

private:
	void analyzePattern();
	bool isFull();

private:
	LString m_pattern;

	struct ChpxInfo
	{
		size_t begin	= 0;
		size_t len		= 0;
		uint argID		= 0;
	};
	std::vector<ChpxInfo> m_chpxes;
	std::vector<LString> m_args;
	uint m_argCount = 0;
};
