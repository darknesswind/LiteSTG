#pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <codecvt>
#ifdef max
#	undef max
#endif
#ifdef min
#	undef min
#endif
#pragma warning( push )
#pragma warning( disable: 4100 )
#include "GeneratedFiles/datadef.pb.h"
#pragma warning( pop )

typedef const wchar_t* LPCWSTR;
typedef std::vector<unsigned char> ByteArray;
typedef google::protobuf::MessageLite ProtoMsg;

class ProtoBufBase
{
public:
	ProtoBufBase();
	virtual ~ProtoBufBase();

	bool save(LPCWSTR lpFilePath);

	bool load(LPCWSTR lpFilePath);
	bool load(const ByteArray& bytes);

protected:
	std::unique_ptr<ProtoMsg> m_spMsg;
};
//////////////////////////////////////////////////////////////////////////
class TextureBuf : public ProtoBufBase
{
public:
	TextureBuf();

	void insert(LPCWSTR lpPath, LPCWSTR lpName);
	inline proto::Textures* textures() { return static_cast<proto::Textures*>(m_spMsg.get()); }

};
//////////////////////////////////////////////////////////////////////////
struct SubGraphRaw
{
	int xSrc, ySrc;
	int allNum;
	int xNum, yNum;
	int width, height;
};

class SubGraphicsBuf : public ProtoBufBase
{
public:
	SubGraphicsBuf();

	void insert(LPCWSTR pName, LPCWSTR refTexture, const SubGraphRaw* info);
	proto::SubGraphics* subgraphics() { return static_cast<proto::SubGraphics*>(m_spMsg.get()); }
};
//////////////////////////////////////////////////////////////////////////
class BulletSyltesBuf : public ProtoBufBase
{
public:
	BulletSyltesBuf();

	proto::BulletStyles* bulletStyles() { return static_cast<proto::BulletStyles*>(m_spMsg.get()); }

	typedef proto::BulletStyle_BulletType Type;
};
//////////////////////////////////////////////////////////////////////////
class PathSetBuf : public ProtoBufBase
{
public:
	PathSetBuf();

	proto::PathSet* pathset() { return static_cast<proto::PathSet*>(m_spMsg.get()); }

};
