#ifndef __ENUMATIONS_H__
#define __ENUMATIONS_H__

#include "DxLib.h"

enum class WalkerType
{
	Stable,
	Physic,
	Path,
	Controlled,
	Follow,
};

enum class DxBlendMode
{
	NoBlend				= 0,	// 无混合
	Alpha				= 1,	// α混合
	Add					= 2,	// 加法混合
	Sub					= 3,	// 减法混合
	Mul					= 4,	// 乘法混合
	// (内部処理用)
	Sub2				= 5,	// 内部处理用减法混合2
	Xor					= 6,	// 异或混合( 仅软件渲染模式有效 )
	//	BlineAlpha		= 7,	// 边界模糊
	DestColor			= 8,	// 颜色不更新
	InvDestColor		= 9,	// 把绘制目标的颜色翻转
	InvSrc				= 10,	// 把绘制源的颜色翻转
	Mula				= 11,	// 同时考虑Alpha通道的乘法混合
	Alpha_X4			= 12,	// 4倍亮度α混合
	Add_X4				= 13,	// 4倍亮度加法混合
	SrcColor			= 14,	// 绘制源的颜色不变
	Half_Add			= 15,	// 半加法混合
	Sub1				= 16,	// 内部处理用减法混合
	Pma_Alpha			= 17,	// 预乘α混合
	PMA_Add				= 18,	// 预乘加法混合
	PMA_Sub				= 19,	// 预乘减法混合
	PMA_InvSrc			= 20,	// 预乘绘制源反色混合
	PMA_Alpha_X4		= 21,	// 预乘4倍亮度α混合
	PMA_Add_X4			= 22,	// 预乘4倍亮度加法混合
	Num					= 23,	// 混合模式总数
};

enum class DxDrawMode
{
	Nearest		= 0,	// 最邻近插值
	Bilinear	= 1,	// 双线性插值
	Anisotropic	= 2,	// 各向异性过滤
	Other		= 3,	// 其他
};

// 图元类型
enum class PrimitiveType
{
	PointList		= DX_PRIMTYPE_POINTLIST,			// 点集
	LineList		= DX_PRIMTYPE_LINELIST,			// 线段集
	LineStrip		= DX_PRIMTYPE_LINESTRIP,			// 连续线段
	TriangleList	= DX_PRIMTYPE_TRIANGLELIST,		// 三角形集
	TriangleStrip	= DX_PRIMTYPE_TRIANGLESTRIP,		// 连续三角形
	TriangleFan		= DX_PRIMTYPE_TRIANGLEFAN,		// 
};

enum RenderDepthBase
{
	DepthBackground	= 0x00000000,
	DepthCharacter	= 0x01000000,
	DepthBullet		= 0x10000000,
	DepthHitBox		= 0x20000000,
	DepthFrame		= 0x30000000,
	DepthUI			= 0x40000000,
	DepthDebug		= 0xF0000000,
};

#endif
