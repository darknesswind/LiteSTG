#include "protobuf.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/text_format.h"
#include <fstream>

typedef std::wstring_convert<std::codecvt_utf8<wchar_t>> Utf8Convert;

typedef google::protobuf::Map<std::string, std::string> TextureMap;
typedef TextureMap::value_type TexturePair;

typedef google::protobuf::Map<std::string, proto::SubGraphics_SubInfos> SubGraphMap;
typedef SubGraphMap::value_type SubGraphPair;

typedef google::protobuf::TextFormat TextFormat;

ProtoBufBase::ProtoBufBase()
{
}

ProtoBufBase::~ProtoBufBase()
{
}

bool ProtoBufBase::saveBinary(LPCWSTR lpFilePath)
{
	std::fstream fs;
	fs.open(lpFilePath, std::ios::out | std::ios::binary);
	if (!fs.is_open())
		return false;

	fs << m_spMsg->SerializeAsString();
	fs.close();

	return !fs.bad();
}

bool ProtoBufBase::saveText(LPCWSTR lpFilePath)
{
	std::fstream fs;
	fs.open(lpFilePath, std::ios::out | std::ios::binary);
	if (!fs.is_open())
		return false;

	fs << m_spMsg->Utf8DebugString();
	fs.close();

	return !fs.bad();
}

bool ProtoBufBase::load(LPCWSTR lpFilePath)
{
	std::fstream fs;
	fs.open(lpFilePath, std::ios::in | std::ios::binary);
	if (!fs.is_open())
		return false;

	fs.seekp(0, std::ios::end);
	auto buffSize = fs.tellg();
	std::vector<unsigned char> bytes((unsigned int)buffSize);
	fs.seekp(0, std::ios::beg);
	fs.read((char*)bytes.data(), bytes.size());
	fs.close();

	return m_spMsg->ParseFromArray(bytes.data(), bytes.size());
}

bool ProtoBufBase::load(const ByteArray& bytes)
{
	return m_spMsg->ParseFromArray(bytes.data(), bytes.size());
}

bool ProtoBufBase::loadFromText(LPCWSTR lpFilePath)
{
	std::fstream fs;
	fs.open(lpFilePath, std::ios::in);
	if (!fs.is_open())
		return false;

	fs.seekp(0, std::ios::end);
	auto buffSize = fs.tellg();
	std::string str;
	str.resize(buffSize);
	fs.seekp(0, std::ios::beg);
	fs.read((char*)str.data(), str.size());
	fs.close();

	return TextFormat::ParseFromString(str, m_spMsg.get());
}

//////////////////////////////////////////////////////////////////////////
TextureBuf::TextureBuf()
{
	m_spMsg = std::make_unique<proto::Textures>();
}

void TextureBuf::insert(LPCWSTR lpPath, LPCWSTR lpName)
{
	Utf8Convert conv;
	proto::Textures_Texture* pTexture = textures()->add_texture();
	pTexture->set_name(conv.to_bytes(lpName));
	pTexture->set_path(conv.to_bytes(lpPath));
}

//////////////////////////////////////////////////////////////////////////

SubGraphicsBuf::SubGraphicsBuf()
{
	m_spMsg = std::make_unique<proto::SubGraphics>();
}

void SubGraphicsBuf::insert(LPCWSTR pName, LPCWSTR refTexture, const SubGraphRaw* info)
{
	Utf8Convert cvt;

	auto& infos = subgraphics()->mutable_map()->operator[](cvt.to_bytes(pName));
	proto::SubGraphics_SubGraphInfo* graphinfo = infos.add_info();
	graphinfo->set_texture(cvt.to_bytes(refTexture));
	graphinfo->set_xsrc(info->xSrc);
	graphinfo->set_ysrc(info->ySrc);
	graphinfo->set_allnum(info->allNum);
	graphinfo->set_xnum(info->xNum);
	graphinfo->set_ynum(info->yNum);
	graphinfo->set_width(info->width);
	graphinfo->set_height(info->height);
}

//////////////////////////////////////////////////////////////////////////
BulletSyltesBuf::BulletSyltesBuf()
{
	m_spMsg = std::make_unique<proto::BulletStyles>();
}

//////////////////////////////////////////////////////////////////////////
PathSetBuf::PathSetBuf()
{
	m_spMsg = std::make_unique<proto::PathSet>();
}
