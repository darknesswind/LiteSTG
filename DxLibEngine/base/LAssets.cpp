#include "stdafx.h"
#include "LAssets.h"
#include "LHandle.h"
#include "protobuf.h"
#include "gsl/span"

LGraphHandles LAssets::s_emptyGraphHandles;

enum DXAPriority
{
	dxap_PackFirst = 0,
	dxap_FileFirst = 1
};

LAssets::LAssets()
{
	DxLib::SetUseDXArchiveFlag(TRUE);
	DxLib::SetDXArchivePriority(DXAPriority::dxap_PackFirst);	// 文件优先
}

LAssets::~LAssets()
{

}

void LAssets::LoadTextureList(LPCWSTR lpPath)
{
	TextureBuf buff;
	if (!buff.load(LoadRawData(lpPath)))
	{
		LStrBuilder msg(LR"(Load "%1" failed!)");
		LLogger::Error(msg.arg(lpPath).apply());
		return;
	}
	
	LString dir(L"resource/");
	for (const auto& texture : buff.msg()->texture())
	{
		LString path = LString::fromUtf8(texture.path());
		if (path.empty())
			continue;

		LString name = LString::fromUtf8(texture.name());
		if (name.empty())
		{
			size_t nBegin = path.find_last_of(L'/');
			if (nBegin < 0)
				nBegin = 0;
			else
				++nBegin;

			size_t nEnd = path.find_last_of(L'.', nBegin);
			if (nEnd > path.size())
				nEnd = path.size();

			if (nBegin >= path.size() || nBegin > nEnd)
			{
				LStrBuilder msg(LR"(%1: Can not auto alloc name for "%2".)");
				LLogger::Error(msg.arg(lpPath).arg(path).apply());
				continue;
			}

			name = path.substr(nBegin, nEnd - nBegin);
		}

		auto iterator = m_textureMap.find(name);
		if (iterator != m_textureMap.end())
		{
			LStrBuilder msg(LR"(%1: Name "%3" conflicted.)");
			LLogger::Warning(msg.arg(lpPath).arg(name).apply());
		}
		else
		{
			m_textureMap[name].path = dir + path;
		}
	}
}

void LAssets::LoadSoundEffectList(LPCWSTR lpPath)
{
// 	LoadAssetsList(lpPath, m_seMap);
}

void LAssets::LoadSubGraphicsList(LPCWSTR lpPath)
{
	enum param { cSrcX, cSrcY, cAllNum, cRowNum, cColNum, cWidth, cHeight, ParamCount };

	SubGraphicsBuf buff;
	if (!buff.load(LoadRawData(lpPath)))
	{
		LStrBuilder msg(LR"(Load "%1" failed!)");
		LLogger::Error(msg.arg(lpPath).apply());
		return;
	}

	for (const auto& subgraph : buff.msg()->subgraphs())
	{
		LString name = LString::fromUtf8(subgraph.name());
		auto& infos = subgraph.infos();
		for (const auto& info : infos)
		{
			LSubGraphData& datas = m_subGraphics[name];
			datas.infos.emplace_back(LSubGraphInfo());
			LSubGraphInfo& dat = datas.infos.back();

			dat.ref = LString::fromUtf8(info.texture());
			dat.xSrc = info.xsrc();
			dat.ySrc = info.ysrc();
			dat.allNum = info.allnum();
			dat.xNum = info.xnum();
			dat.yNum = info.ynum();
			dat.width = info.width();
			dat.height = info.height();
		}
	}
}

LGraphHandle LAssets::GetTexture(LPCWSTR pName)
{
	auto iter = m_textureMap.find(pName);
	if (iter == m_textureMap.end())
	{
		LStrBuilder msg(LR"(Texture "%1" not found.)");
		LLogger::Error(msg.arg(pName).apply());
		return LGraphHandle();
	}
	else
	{
		LAssetData& data = iter->second;
		if (data.handle.empty())
			data.handle = DxLib::LoadGraph(data.path.c_str());
		return data.handle;
	}
}

LSoundHandle LAssets::GetSoundEffect(LPCWSTR pName)
{
	auto iter = m_seMap.find(pName);
	if (iter == m_seMap.end())
	{
		LStrBuilder msg(LR"(SE "%1" not found.)");
		LLogger::Error(msg.arg(pName).apply());
		return LGraphHandle();
	}
	else
	{
		LAssetData& data = iter->second;
		if (data.handle.empty())
			data.handle = DxLib::LoadGraph(data.path.c_str());
		return data.handle;
	}
}

const LGraphHandles& LAssets::GetSubGraphGroup(LPCWSTR pName)
{
	auto iter = m_subGraphics.find(pName);
	if (iter == m_subGraphics.end())
	{
		LStrBuilder msg(LR"(SubGraphicGroup "%1" not found.)");
		LLogger::Error(msg.arg(pName).apply());
		return s_emptyGraphHandles;
	}
	else
	{
		LSubGraphData& data = iter->second;
		if (data.handles.empty())
			LoadDivGraphics(data);
		return data.handles;
	}
}

void LAssets::LoadDivGraphics(LSubGraphData& data)
{
	for (const LSubGraphInfo& info : data.infos)
	{
		LGraphHandle hSrcGraph = GetTexture(info.ref.c_str());
		data.handles = hSrcGraph.split(
			info.xSrc,
			info.ySrc,
			info.allNum,
			info.xNum,
			info.yNum,
			info.width,
			info.height);
	}
}

ByteArray LAssets::LoadRawData(LPCWSTR lpPath)
{
	LHandle hFile = DxLib::FileRead_fullyLoad(lpPath);
	long long size = DxLib::FileRead_fullyLoad_getSize(hFile);
	if (size < 0)
		LLogger::Error(LStrBuilder(L"Open '%1' failed!").arg(lpPath).apply());

	const uchar* pData = reinterpret_cast<const uchar*>(DxLib::FileRead_fullyLoad_getImage(hFile));
	auto span = gsl::make_span(pData, size);
	ByteArray res(span.begin(), span.end());
	return res;
}

LCsvTableSPtr LAssets::LoadCSV(LPCWSTR lpPath)
{
	LCsvTableSPtr pTable = std::make_shared<LCsvTable>();
	LAssert(false);
// 	QTextStream stream(LoadRawData(lpPath));
// 	stream.setCodec("GBK");
// 	stream.setAutoDetectUnicode(true);
// 	while (!stream.atEnd())
// 	{
// 		pTable->insertRow(stream.readLine().split(","));
// 	}

	return pTable;
}

//////////////////////////////////////////////////////////////////////////
LCsvTable::LCsvTable()
{
}

LCsvTable::~LCsvTable()
{

}

void LCsvTable::insertRow(LCsvRowData row)
{
	m_data.push_back(row);
}

std::wstring LCsvTable::getString(uint row, uint col) const
{
	if (row >= m_data.size())
		return std::wstring();

	const LCsvRowData& rowDat = m_data[row];
	if (col >= rowDat.size())
		return std::wstring();
	else
		return rowDat[col];
}

int LCsvTable::getInt(uint row, uint col, int def /*= 0*/) const
{
	LString str = getString(row, col);
	if (str.empty())
		return def;
	
	bool bOk = false;
	const int res = str.toInt(&bOk);
	return (bOk ? res : def);
}
