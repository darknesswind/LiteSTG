#include "stdafx.h"
#include "LAssets.h"
#include "LHandle.h"
#include <QTextStream>

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

void LAssets::LoadAssetsList(LPCWSTR lpPath, LNamedAssetMap& map)
{
	enum param { argPath, argName };
	static QRegExp reg("\\\\?([^\\/:*?\"|\\.]+)");
	LCsvTablePtr pTable = LAssets::LoadCSV(lpPath);
	// 第一行标题
	for (size_t i = 1; i < pTable->getRowCount(); ++i)
	{
		QString path = pTable->getString(i, argPath);
		if (path.isEmpty())
			continue;

		QString name = pTable->getString(i, argName);
		if (name.isEmpty())
		{
			int nBegin = path.lastIndexOf(QRegExp("[\\\\/]"));
			if (nBegin < 0)
				nBegin = 0;
			else
				++nBegin;

			int nEnd = path.indexOf('.', nBegin);
			if (nEnd < 0)
				nEnd = path.size();

			if (nBegin >= path.size() || nBegin > nEnd)
			{
				static QString msg(R"(%1(%2): Can not auto alloc name for "%3".)");
				LLogger::PrintError(msg.arg(W2QSTR(lpPath)).arg(i).arg(path));
				continue;
			}

			name = path.mid(nBegin, nEnd - nBegin);
		}

		auto iter = map.find(name);
		if (iter != map.end())
		{
			static QString msg(R"(%1(%2): Name "%3" conflicted.)");
			LLogger::PrintWarning(msg.arg(W2QSTR(lpPath)).arg(i).arg(name));
		}
		else
		{
			map[name].path = path;
		}
	}
}

void LAssets::LoadTextureList(LPCWSTR lpPath)
{
	LoadAssetsList(lpPath, m_textureMap);
}

void LAssets::LoadSoundEffectList(LPCWSTR lpPath)
{
	LoadAssetsList(lpPath, m_seMap);
}

void LAssets::LoadSubGraphicsList(LPCWSTR lpPath)
{
	enum param { cName, cRef, cSrcX, cSrcY, cAllNum, cRowNum, cColNum, cWidth, cHeight, ParamCount };
	LCsvTablePtr pTable = LAssets::LoadCSV(lpPath);
	// 第一行标题
	for (size_t i = 1; i < pTable->getRowCount(); ++i)
	{
		auto& rowDat = pTable->getRow(i);
		if (rowDat.size() != ParamCount)
		{
			static QString msg(R"(%1(%2): Param number Error.)");
			LLogger::PrintError(msg.arg(W2QSTR(lpPath)).arg(i));
			continue;
		}
		LAssert(!rowDat[cName].isEmpty());
		LSubGraphData& datas = m_subGraphics[rowDat[cName]];

		datas.infos.emplace_back(LSubGraphInfo());
		LSubGraphInfo& d = datas.infos.back();

		bool bOk = false;
#define AssignIntData(name, idx) { d.name = rowDat[idx].toInt(&bOk); LAssert(bOk); }
		d.ref = rowDat[cRef];
		AssignIntData(xSrc, cSrcX);
		AssignIntData(ySrc, cSrcY);
		AssignIntData(allNum, cAllNum);
		AssignIntData(xNum, cRowNum);
		AssignIntData(yNum, cColNum);
		AssignIntData(width, cWidth);
		AssignIntData(height, cHeight);
#undef AssignIntData
	}
}

LGraphHandle LAssets::GetTexture(QString sName)
{
	auto iter = m_textureMap.find(sName);
	if (iter == m_textureMap.end())
	{
		static QString msg(R"(Texture "%1" not found.)");
		LLogger::PrintError(msg.arg(sName));
		return LGraphHandle();
	}
	else
	{
		LAssetData& data = iter.value();
		if (data.handle.empty())
			data.handle = DxLib::LoadGraph(Q2WSTR(data.path));
		return data.handle;
	}
}

LSoundHandle LAssets::GetSoundEffect(LPCWSTR name)
{
	QString sName = W2QSTR(name);
	auto iter = m_seMap.find(sName);
	if (iter == m_seMap.end())
	{
		static QString msg(R"(SE "%1" not found.)");
		LLogger::PrintError(msg.arg(sName));
		return LGraphHandle();
	}
	else
	{
		LAssetData& data = iter.value();
		if (data.handle.empty())
			data.handle = DxLib::LoadGraph(Q2WSTR(data.path));
		return data.handle;
	}
}

const LGraphHandles& LAssets::GetSubGraphGroup(LPCWSTR name)
{
	QString sName = W2QSTR(name);
	auto iter = m_subGraphics.find(sName);
	if (iter == m_subGraphics.end())
	{
		static QString msg(R"(SubGraphicGroup "%1" not found.)");
		LLogger::PrintError(msg.arg(sName));
		return s_emptyGraphHandles;
	}
	else
	{
		LSubGraphData& data = iter.value();
		if (data.handles.empty())
			LoadDivGraphics(data);
		return data.handles;
	}
}

void LAssets::LoadDivGraphics(LSubGraphData& data)
{
	for each (const LSubGraphInfo& info in data.infos)
	{
		LGraphHandle hSrcGraph = GetTexture(info.ref);
		for (int i = 0; i < info.allNum; ++i)
		{
			int srcX = info.xSrc + info.width * (i % info.xNum);
			int srcY = info.ySrc + info.height * (i / info.xNum);
			LGraphHandle hDivGraph = DxLib::DerivationGraph(
				srcX, srcY, info.width, info.height, hSrcGraph);

			data.handles.push_back(hDivGraph);
		}
	}
}

QByteArray LAssets::LoadRawData(LPCWSTR lpPath)
{
	LHandle hFile = DxLib::FileRead_fullyLoad(lpPath);
	long long size = DxLib::FileRead_fullyLoad_getSize(hFile);
	QByteArray res((char*)DxLib::FileRead_fullyLoad_getImage(hFile), size);
	return res;
}

LCsvTablePtr LAssets::LoadCSV(LPCWSTR lpPath)
{
	LCsvTablePtr pTable = std::make_shared<LCsvTable>();

	QTextStream stream(LoadRawData(lpPath));
	stream.setCodec("GBK");
	stream.setAutoDetectUnicode(true);
	while (!stream.atEnd())
	{
		pTable->insertRow(stream.readLine().split(","));
	}

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

QString LCsvTable::getString(int row, int col) const
{
	if ((size_t)row >= m_data.size())
		return QString();

	const LCsvRowData& rowDat = m_data[row];
	if (col >= rowDat.size())
		return QString();
	else
		return rowDat[col];
}

int LCsvTable::getInt(int row, int col, int def /*= 0*/) const
{
	QString str = getString(row, col);
	if (str.isEmpty())
		return def;
	
	bool bOk = false;
	int res = str.toInt(&bOk);
	return (bOk ? res : def);
}
