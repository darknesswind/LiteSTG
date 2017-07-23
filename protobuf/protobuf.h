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
typedef google::protobuf::Message ProtoMsg;

class ProtoBufBase
{
public:
	ProtoBufBase();
	virtual ~ProtoBufBase();

	bool saveBinary(LPCWSTR lpFilePath);
	bool saveText(LPCWSTR lpFilePath);

	bool load(LPCWSTR lpFilePath);
	bool load(const ByteArray& bytes);
	bool loadFromText(LPCWSTR lpFilePath);

protected:
	std::unique_ptr<ProtoMsg> m_spMsg;
};
//////////////////////////////////////////////////////////////////////////
class TextureBuf : public ProtoBufBase
{
public:
	TextureBuf();

	void insert(LPCWSTR lpPath, LPCWSTR lpName);
	inline proto::Textures* msg() { return static_cast<proto::Textures*>(m_spMsg.get()); }

};

//////////////////////////////////////////////////////////////////////////
struct SubGraphRaw
{
	unsigned int xSrc, ySrc;
	unsigned int allNum;
	unsigned int xNum, yNum;
	unsigned int width, height;
};

class SubGraphicsBuf : public ProtoBufBase
{
public:
	class SubInfosRef
	{
	public:
		SubInfosRef(proto::SubGraphics_SubInfos* infos)
			: m_pinfos(infos)
		{}
		void insert(LPCWSTR refTexture, const SubGraphRaw* info);
	private:
		proto::SubGraphics_SubInfos* m_pinfos;
	};
public:
	SubGraphicsBuf();

	SubInfosRef insert(LPCWSTR pName);
	proto::SubGraphics* msg() { return static_cast<proto::SubGraphics*>(m_spMsg.get()); }
};

//////////////////////////////////////////////////////////////////////////
class BulletSyltesBuf : public ProtoBufBase
{
public:
	BulletSyltesBuf();

	proto::BulletStyles* msg() { return static_cast<proto::BulletStyles*>(m_spMsg.get()); }

	typedef proto::BulletStyles::BulletType Type;
};

//////////////////////////////////////////////////////////////////////////
class PathSetBuf : public ProtoBufBase
{
public:
	PathSetBuf();

	proto::PathSet* msg() { return static_cast<proto::PathSet*>(m_spMsg.get()); }

};
