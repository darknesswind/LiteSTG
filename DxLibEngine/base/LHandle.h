#ifndef __LHANDLE_H__
#define __LHANDLE_H__

#pragma region enum define
enum class DxHandleType
{
	None			= 0,	// ハンドルタイプ０は未使用
	Graph			= 1,	// グラフィックハンドル
	SoftImage		= 2,	// ソフトウエアで扱うイメージハンドル
	Sound			= 3,	// サウンドハンドル
	SoftSound		= 4,	// ソフトサウンドハンドル
	Music			= 5,	// ミュージックハンドル
	Movie			= 6,	// ムービーハンドル
	GMask			= 7,	// マスクハンドル
	Font			= 8,	// フォントハンドル
	KeyInput		= 9,	// 文字列入力ハンドル
	NetWork			= 10,	// ネットワークハンドル
	Light			= 11,	// ライト
	Shader			= 12,	// シェーダーハンドル
	ModelBase		= 13,	// ３Ｄモデル基本データ
	Model			= 14,	// ３Ｄモデル
	VertexBuffer	= 15,	// 頂点バッファハンドル
	IndexBuffer		= 16,	// インデックスバッファハンドル
	File			= 17,	// ファイルハンドル
	ShadowMap		= 18,	// シャドウマップハンドル
};

#pragma endregion

namespace DxLib
{
	struct HANDLEINFO;
	struct IMAGEDATA2;
}
class LHandle
{
	enum DxHandleMask : uint
	{
		IndexMask		= 0x0000ffff,		// handle索引mask
		MaxIndex		= 65536,			// 每分类最大handle数目

		CheckMask		= 0x03ff0000,		// handle正确性检查用
		CheckOffset		= 16,				// 有效值偏移量
		MaxCheck		= 1024,				// 
		
		TypeMask		= 0x7c000000,		// handle类型mask
		TypeOffset		= 26,				// 有效值偏移量
		MaxType			= 32,				// 最大type数
		
		ErrorMask		= 0x80000000,		// Error Check Mask( ０ではなかったらエラー )
	};

public:
	LHandle() : m_handle(0) {}
	LHandle(int hHandle)
		: m_handle(hHandle)
	{
	}
	operator int() const { LAssert(!empty()); return m_handle; }
	bool operator< (const LHandle& rhs) const { return m_handle < rhs.m_handle; }

public:
	bool empty() const { return !m_handle; }
	bool hasError() const { return m_handle & ErrorMask; }
	uint index() const { return m_handle & IndexMask; }
	DxHandleType type() const 
	{
		return (DxHandleType)((m_handle & TypeMask) >> TypeOffset);
	}

	bool checkValidType(DxHandleType targetType) const;
	const DxLib::HANDLEINFO* innerData() const;

protected:
	static const uint hNoneGraph = 0xfffffffb;

protected:
	int m_handle;
};

class LGraphHandle : public LHandle
{
public:
	LGraphHandle()
		: LHandle(hNoneGraph)
	{
	}
	LGraphHandle(int hHandle)
		: LHandle(hHandle)
	{
		LAssert(type() == DxHandleType::Graph);
		if (type() != DxHandleType::Graph)
			m_handle = hNoneGraph;
	}

public:
	const DxLib::IMAGEDATA2* innerData() const { return (DxLib::IMAGEDATA2*)LHandle::innerData(); }

	static LGraphHandle NoneGraph;

private:

};

#endif	// __LHANDLE_H__
