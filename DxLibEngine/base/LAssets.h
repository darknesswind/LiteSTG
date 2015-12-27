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
	LCsvRowData& getRow(int i) { return m_data[i]; }
	QString getString(int row, int col) const;
	int getInt(int row, int col, int def = 0) const;

private:
	LCsvTable(const LCsvTable&) = delete;
	void operator=(const LCsvTable&) = delete;

private:
	LCsvData m_data;
};
typedef std::shared_ptr<LCsvTable> LCsvTablePtr;

class LAssets
{
#pragma region Structs
	struct LAssetData
	{
		QString path;
		LHandle handle;
	};
	struct LSubGraphInfo
	{
		QString ref;
		int xSrc;
		int ySrc;
		int allNum;
		int xNum;
		int yNum;
		int width;
		int height;
	};
	struct LSubGraphData
	{
		std::vector<LSubGraphInfo> infos;
		LGraphHandles handles;
	};
#pragma endregion
	typedef QHash<QString, LAssetData> LNamedAssetMap;
	typedef QHash<QString, LSubGraphData> LSubGraphAssetMap;
// 	typedef std::unordered_map<std::wstring, LAssetData> LNamedAssetMap;

public:
	LAssets();
	~LAssets();

public:
	void LoadTextureList(LPCWSTR lpPath);
	void LoadSoundEffectList(LPCWSTR lpPath);
	void LoadSubGraphicsList(LPCWSTR lpPath);

public:
	LGraphHandle GetTexture(QString name);
	LGraphHandle GetTexture(LPCWSTR name) { return GetTexture(W2QSTR(name)); }
	LSoundHandle GetSoundEffect(LPCWSTR name);
	const LGraphHandles& GetSubGraphGroup(LPCWSTR name);

protected:
	void LoadAssetsList(LPCWSTR lpPath, LNamedAssetMap& map);
	void LoadDivGraphics(LSubGraphData& data);

public:
	static QByteArray LoadRawData(LPCWSTR lpPath);
	static LCsvTablePtr LoadCSV(LPCWSTR lpPath);

private:
	LAssets(const LAssets&) = delete;
	void operator=(const LAssets&) = delete;

private:
	LNamedAssetMap m_textureMap;
	LNamedAssetMap m_seMap;
	LSubGraphAssetMap m_subGraphics;

private:
	static LGraphHandles s_emptyGraphHandles;
};

#endif // !__LASSETS_H__
