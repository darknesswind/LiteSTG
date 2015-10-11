#ifndef __LASSETS_H__
#define __LASSETS_H__

#pragma once
#include "typedef.h"
#include "LHandle.h"
#include <QHash>
#include <QStringList>

class LCsvTable
{
	typedef QStringList LCsvRowData;
	typedef std::vector<LCsvRowData> LCsvData;
public:
	LCsvTable();
	~LCsvTable();

	void insertRow(LCsvRowData row);

	size_t getRowCount() const { return m_data.size(); }
	QString getData(int row, int col) const;

private:
	LCsvTable(const LCsvTable&) = delete;
	void operator=(const LCsvTable&) = delete;

private:
	LCsvData m_data;
};
typedef std::shared_ptr<LCsvTable> LCsvTablePtr;


class LAssets
{
	struct LAssetData
	{
		QString path;
		LHandle handle;
	};
	typedef QHash<QString, LAssetData> LNamedAssetMap;

public:
	LAssets();
	~LAssets();

public:
	void LoadTextureList(LPCWSTR lpPath);
	void LoadSoundEffectList(LPCWSTR lpPath);

protected:
	void LoadAssetsList(LPCWSTR lpPath, LNamedAssetMap& map);

public:
	static QByteArray LoadRawData(LPCWSTR lpPath);
	static LCsvTablePtr LoadCSV(LPCWSTR lpPath);

private:
	LAssets(const LAssets&) = delete;
	void operator=(const LAssets&) = delete;

private:
	LNamedAssetMap m_textureMap;
	LNamedAssetMap m_seMap;
};

#endif // !__LASSETS_H__
