#include "stdafx.h"
#include "LAssets.h"
#include "LHandle.h"
#include <QTextStream>

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
	static QRegExp reg("\\\\?([^\\/:*?\"|\\.]+)");
	LCsvTablePtr pTable = LAssets::LoadCSV(lpPath);
	// 第一行标题
	for (size_t i = 1; i < pTable->getRowCount(); ++i)
	{
		QString path = pTable->getData(i, 0);
		if (path.isEmpty())
			continue;

		QString name = pTable->getData(i, 1);
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
				LLogger::PrintError(QString("%1(%2): Can not auto alloc name for \"%3\"")
					.arg(WQSTR(lpPath)).arg(i).arg(path));
				continue;
			}

			name = path.mid(nBegin, nEnd - nBegin);
			auto iter = map.find(name);
			if (iter != map.end())
			{
				LLogger::PrintWarning(QString("%1(%2): Name \"%3\" conflicted")
					.arg(WQSTR(lpPath)).arg(i).arg(name));
			}
			else
			{
				map[name].path = path;
			}
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

QString LCsvTable::getData(int row, int col) const
{
	if ((size_t)row >= m_data.size())
		return QString();

	const LCsvRowData& rowDat = m_data[row];
	if (col >= rowDat.size())
		return QString();
	else
		return rowDat[col];
}
