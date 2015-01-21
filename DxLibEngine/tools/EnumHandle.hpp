#ifndef __ENUMHANDLE_H__
#define __ENUMHANDLE_H__
#pragma once
#include <type_traits>

template<typename FlagType, typename HandleType>
class EnumHandle
{
public:
	EnumHandle(FlagType flag)
	{
		data.flag = flag;
	}
	EnumHandle(HandleType handle)
	{
		data.handle = handle;
	}
	~EnumHandle()
	{
		static_assert(std::is_enum<FlagType>::value, "FlagType must be a enum");
	}

	FlagType flag() { return data.flag; }
	HandleType handle() { return data.handle; }

private:
	union tagEnumHandle
	{
		FlagType flag;
		HandleType handle;
	} data;
};

#endif
