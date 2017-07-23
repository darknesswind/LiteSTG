#ifndef __LASSETS_H__
#define __LASSETS_H__

#pragma once
#include "typedef.h"
#include "LHandle.h"

class LCsvTable
{
	typedef std::vector<std::wstring> LCsvRowData;
	typedef std::vector<LCsvRowData> LCsvData;
public:
	LCsvTable();
	~LCsvTable();

	void insertRow(LCsvRowData row);

	size_t getRowCount() const { return m_data.size(); }
	LCsvRowData& getRow(uint i) { return m_data[i]; }
	std::wstring getString(uint row, uint col) const;
	int getInt(uint row, uint col, int def = 0) const;

private:
	LCsvTable(const LCsvTable&) = delete;
	void operator=(const LCsvTable&) = delete;

private:
	LCsvData m_data;
};
typedef std::shared_ptr<LCsvTable> LCsvTableSPtr;

class LAssets
{
#pragma region Structs
	struct LAssetData
	{
		std::wstring path;
		LHandle handle;
	};
	struct LSubGraphInfo
	{
		LString ref;
		uint xSrc;
		uint ySrc;
		uint allNum;
		uint xNum;
		uint yNum;
		uint width;
		uint height;
	};
	struct LSubGraphData
	{
		std::vector<LSubGraphInfo> infos;
		LGraphHandles handles;
	};
#pragma endregion
	typedef std::unordered_map<LString, LAssetData> LNamedAssetMap;
	typedef std::unordered_map<LString, LSubGraphData> LSubGraphAssetMap;

public:
	LAssets();
	virtual ~LAssets();

public:
	void LoadTextureList(LPCWSTR lpPath);
	void LoadSoundEffectList(LPCWSTR lpPath);
	void LoadSubGraphicsList(LPCWSTR lpPath);

public:
	LGraphHandle GetTexture(LPCWSTR name);
	LSoundHandle GetSoundEffect(LPCWSTR name);
	const LGraphHandles& GetSubGraphGroup(LPCWSTR name);

protected:
// 	void LoadAssetsList(LPCWSTR lpPath, LNamedAssetMap& map);
	void LoadDivGraphics(LSubGraphData& data);

public:
	static LByteArray LoadRawData(LPCWSTR lpPath);
	static LCsvTableSPtr LoadCSV(LPCWSTR lpPath);

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
