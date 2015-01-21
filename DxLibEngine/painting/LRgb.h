#ifndef __LRGB_H__
#define __LRGB_H__
#pragma once
#include "typedef.h"

#define make_rgb(r, g, b) (uint)(((r) << 24) | ((g) << 16) | ((b) << 8) | 0xFF)

class LRgb32;
typedef LRgb32 LRgb;

class LRgb32
{
	union RgbUnion32
	{
		struct RgbStruct32
		{
			uchar alpha;
			uchar red;
			uchar green;
			uchar blue;
		} rgbMap;
		uint uColor;
		int nColor;
		char channel[4];
	};

public:
	LRgb32(uint color = LRgb32::White)	{ m_color.uColor = color; }
	LRgb32(int color)	{ m_color.nColor = color; }
	LRgb32(uchar red, uchar green, uchar blue, uchar alpha = 255) { setRgb(red, green, blue, alpha); }
	
	void operator=(const LRgb32& other) { m_color = other.m_color; }
	bool operator==(const LRgb32& other) const { return m_color.nColor == other.m_color.nColor; }
	bool operator!=(const LRgb32& other) const { return m_color.nColor != other.m_color.nColor; }

	operator uint()	{ return m_color.uColor; }
	operator int()	{ return m_color.nColor; }

public:
	int	red() const		{ return m_color.rgbMap.red; }
	int	green() const	{ return m_color.rgbMap.green; }
	int	blue() const	{ return m_color.rgbMap.blue; }
	int	alpha() const	{ return m_color.rgbMap.alpha; }
	void	setRed(uchar red)		{ m_color.rgbMap.red = red; }
	void	setGreen(uchar green)	{ m_color.rgbMap.green = green; }
	void	setBlue(uchar blue)		{ m_color.rgbMap.blue = blue; }
	void	setAlpha(uchar alpha)	{ m_color.rgbMap.alpha = alpha; }
	void	setRgb(uchar red, uchar green, uchar blue, uchar alpha = 255)
	{
		m_color.rgbMap.red = red;
		m_color.rgbMap.green = green;
		m_color.rgbMap.blue = blue;
		m_color.rgbMap.alpha = alpha;
	}

private:
	RgbUnion32 m_color;

public:
	enum StaticColorTable : uint
	{
		Transparent				= 0x000000, // ͸��
		AliceBlue				= 0xF0F8FF, // ����˿��
		AlizarinCrimson			= 0xE32636, // ���
		Amber					= 0xFFBF00, // ����ɫ
		Amethyst				= 0x6633CC, // ��ˮ��ɫ
		AntiqueWhite			= 0xFAEBD7, // �Ŷ���
		AppleGreen				= 0x8CE600, // ƻ����
		Apricot					= 0xE69966, // �ӻ�
		Aqua					= 0xAFDFE4, // ˮɫ
		AquaBlue				= 0x66FFE6, // ˮ��
		Aquamarine				= 0x7FFFD4, // ����ɫ
		Azure					= 0x007FFF, // տ��
		BabyBlue				= 0xE0FFFF, // ǳ��
		BabyPink				= 0xFFD9E6, // ǳ�ۺ�
		Beige					= 0xF5F5DC, // �׻�ɫ
		Bisque					= 0xFFE4C4, // ������
		Black					= 0x000000, // ��ɫ
		BlanchedAlmond			= 0xFFEBCD, // ���ʰ�
		Blue					= 0x0000FF, // ��ɫ
		BlueViolet				= 0x8A2BE2, // ����
		BrightGreen				= 0x66FF00, // ����
		Bronze					= 0xB87333, // ��ͭɫ
		Brown					= 0xA52A2A, // ��ɫ
		Burgundy				= 0x470024, // ���޵ھƺ�
		BurlyWood				= 0xDEB887, // Ӳľɫ
		BurntOrange				= 0xCC5500, // ȼ��
		CadetBlue				= 0x5F9EA0, // ������
		Camel					= 0xA16B47, // ��ɫ
		Camellia				= 0xE63995, // ɽ���
		CanaryYellow			= 0xFFFF00, // �ʻ�
		CardinalRed				= 0x990036, // �����
		Carmine					= 0xE6005C, // ��֬��
		CeladonGreen			= 0x73E68C, // �����
		Cerise					= 0xDE3163, // ӣ�Һ�
		Ceruleanblue			= 0x2A52BE, // ε��
		ChampagneYellow			= 0xFFFF99, // ���Ļ�
		Chartreuse				= 0x7FFF00, // ���ؾ���
		Chocolate				= 0xD2691E, // �ɿ���ɫ
		ChromeYellow			= 0xE6B800, // ����
		Clematis				= 0xCCA3CC, // ��������
		CobaltBlue				= 0x0047AB, // ����
		CobaltGreen				= 0x66FF59, // ����
		CoconutBrown			= 0x4D1F00, // Ҭ��
		Coffee					= 0x4D3900, // ����ɫ
		Coral					= 0xFF7F50, // ɺ����
		CoralPink				= 0xFF80BF, // ǳɺ����
		CornflowerBlue			= 0x6495ED, // ʸ������
		Cornsilk				= 0xFFF8DC, // ����˿ɫ
		Cream					= 0xFFFDD0, // ����ɫ
		Crimson					= 0xDC143C, // 糺�
		Cyan					= 0x00FFFF, // ��ɫ
		CyanBlue				= 0x0DBF8C, // ����
		DarkBlue				= 0x00008B, // ����
		DarkCyan				= 0x008B8B, // ����
		DarkGoldenrod			= 0xB8860B, // �����ɫ
		DarkGray				= 0xA9A9A9, // ����
		DarkGreen				= 0x006400, // ����
		DarkKhaki				= 0xBDB76B, // ������ɫ
		DarkMagenta				= 0x8B008B, // �����
		DarkMineralBlue			= 0x24367D, // ������
		DarkOliveGreen			= 0x556B2F, // �������
		DarkOrange				= 0xFF8C00, // ����
		DarkOrchid				= 0x9932CC, // ������
		DarkPowderBlue			= 0x003399, // ��Ӥ������
		DarkRed					= 0x8B0000, // ����
		DarkSalmon				= 0xE9967A, // ���ٺ�
		DarkSeaGreen			= 0x8FBC8F, // ������
		DarkSlateBlue			= 0x483D8B, // ������
		DarkSlateGray			= 0x2F4F4F, // ���һ�
		DarkTurquoise			= 0x00CED1, // ������ʯɫ
		DarkViolet				= 0x9400D3, // ����
		DeepPink				= 0xFF1493, // ��ۺ�
		DeepSkyBlue				= 0x00BFFF, // ������
		Dimgray					= 0x696969, // ���
		DodgerBlue				= 0x1E90FF, // ������
		Emerald					= 0x50C878, // ����
		FireBrick				= 0xB22222, // �ͻ�ש��
		Flamingo				= 0xE68AB8, // ��׺�
		FloralWhite				= 0xFFFAF0, // ���ܰ�
		FoliageGreen			= 0x73B839, // Ҷ��
		ForestGreen				= 0x228B22, // ɭ����
		FreshLeaves				= 0x99FF4D, // ����
		Fuchsia					= 0xF400A1, // Ʒ��
		Gainsboro				= 0xDCDCDC, // ��˹���޻�
		GhostWhite				= 0xF8F8FF, // �����
		Golden					= 0xFFD700, // ��ɫ
		Goldenrod				= 0xDAA520, // ���ɫ
		GrassGreen				= 0x99E64D, // ����
		Gray					= 0x808080, // ��ɫ
		GrayishPurple			= 0x8674A1, // ǳ���Ϻ�
		Green					= 0x008000, // ��ɫ
		GreenYellow				= 0xADFF2F, // �̻�
		Heliotrope				= 0x5000B8, // �Ӳ���
		HoneyOrange				= 0xFFB366, // �۳�
		Honeydew				= 0xF0FFF0, // �۹���
		HorizonBlue				= 0xA6FFCC, // ��ɫ
		HotPink					= 0xFF69B4, // ů�ۺ�
		IndianRed				= 0xCD5C5C, // ӡ�Ⱥ�
		Indigo					= 0x4B0080, // ��ɫ
		InternationalKleinBlue	= 0x002FA7, // ����������
		IronGray				= 0x625B57, // ����ɫ
		Ivory					= 0xFFFFF0, // ����ɫ
		IvyGreen				= 0x36BF36, // ��������
		Jasmine					= 0xE6C35C, // �����
		Khaki					= 0x996B1F, // ����ɫ
		LapisLazuli				= 0x0D33FF, // ����ʯ��
		Lavender				= 0xE6E6FA, // ޹�²���
		LavenderBlush			= 0xFFF0F5, // ޹�²��Ϻ�
		LawnGreen				= 0x7CFC00, // ��ƺ��
		LemonChiffon			= 0xFFFACD, // ���ʳ�ɫ
		LightBlue				= 0xADD8E6, // ����
		LightCoral				= 0xF08080, // ��ɺ��ɫ
		LightCyan				= 0xE0FFFF, // ����
		LightGoldenrodYellow	= 0xFAFAD2, // ����ջ�
		LightGray				= 0xD3D3D3, // ����ɫ
		LightGreen				= 0x90EE90, // ����
		LightKhaki				= 0xF0E68C, // ������ɫ
		LightLime				= 0xCCFF00, // ��������
		LightPink				= 0xFFB6C1, // ���ۺ�
		LightSalmon				= 0xFFA07A, // ���ٺ�
		LightSeaGreen			= 0x20B2AA, // ������
		LightSkyBlue			= 0x87CEFA, // ������
		LightSlateGray			= 0x778899, // ���һ�
		LightSteelBlue			= 0xB0C4DE, // ������
		LightViolet				= 0xEE82EE, // ����
		LightYellow				= 0xFFFFE0, // ����
		Lilac					= 0xB399FF, // �϶���ɫ
		Lime					= 0x00FF00, // ����ɫ
		LimeGreen				= 0x32CD32, // ������
		Linen					= 0xFAF0E6, // ����ɫ
		Magenta					= 0xFF00FF, // ���
		MagentaRose				= 0xFF0DA6, // ��õ���
		Malachite				= 0x22C32E, // ��ȸʯ��
		Mallow					= 0xD94DFF, // ������
		Marigold				= 0xFF9900, // ���پջ�
		MarineBlue				= 0x00477D, // ˮ����
		Maroon					= 0x800000, // ��ɫ
		Mauve					= 0x6640FF, // ľ����
		MediumAquamarine		= 0x66CDAA, // �б���ɫ
		MediumBlue				= 0x0000CD, // ����
		MediumOrchid			= 0xBA55D3, // ������
		MediumPurple			= 0x9370DB, // ���Ϻ�
		MediumSeaGreen			= 0x3CB371, // �к���
		MediumSlateBlue			= 0x7B68EE, // ������
		MediumSpringGreen		= 0x00FA9A, // �д���ɫ
		MediumTurquoise			= 0x48D1CC, // ������ʯɫ
		MediumVioletRed			= 0xC71585, // �����Ϻ�
		MidnightBlue			= 0x191970, // ��ҹ��
		Mimosa					= 0xE6D933, // ���߲ݻ�
		MineralBlue				= 0x004D99, // ����
		MineralViolet			= 0xB8A1CF, // ����
		Mint					= 0x16982B, // ������
		MintCream				= 0xF5FFFA, // ��������ɫ
		MistyRose				= 0xFFE4E1, // ��õ��ɫ
		Moccasin				= 0xFFE4B5, // ¹ƤЬɫ
		MoonYellow				= 0xFFFF4D, // �»�
		MossGreen				= 0x697723, // ̦޺��
		Mustard					= 0xCCCC4D, // ��ĩ��
		NavajoWhite				= 0xFFDEAD, // ���߻���
		NavyBlue				= 0x000080, // ����
		Ocher					= 0xCC7722, // ��ɫ
		OldLace					= 0xFDF5E6, // ����˿ɫ
		OldRose					= 0xB85798, // ��õ��
		Olive					= 0x808000, // ���ɫ
		OliveDrab				= 0x6B8E23, // ��魾�����
		OperaMauve				= 0xE680FF, // ��Ʒ�Ϻ�
		Orange					= 0xFFA500, // ��ɫ
		OrangeRed				= 0xFF4500, // �Ⱥ�
		Orchid					= 0xDA70D6, // ����
		PailLilac				= 0xE6CFE6, // ���϶���ɫ
		PaleBlue				= 0x7AB8CC, // ����
		PaleDenim				= 0x5E86C1, // �Ҷ�����
		PaleGoldenrod			= 0xEEE8AA, // �ҽ��ɫ
		PaleGreen				= 0x98FB98, // ����
		PaleOcre				= 0xCCB38C, // ����ɫ
		PaleTurquoise			= 0xAFEEEE, // ������ʯɫ
		PaleVioletRed			= 0xDB7093, // ���Ϻ�
		Pansy					= 0x7400A1, // ��ɫ����
		PapayaWhip				= 0xFFEFD5, // ެľ��ɫ
		Peach					= 0xFFE5B4, // ��ɫ
		PeachPuff				= 0xFFDAB9, // ������ɫ
		PeacockBlue				= 0x00808C, // ��ȸ��
		PeacockGreen			= 0x00A15C, // ��ȸ��
		PearlPink				= 0xFFB3E6, // ǳ�����
		Periwinkle				= 0xCCCCFF, // ������ɫ
		Persimmon				= 0xFF4D40, // ���ӳ�
		Peru					= 0xCD853F, // ��³ɫ
		Pink					= 0xFFC0CB, // �ۺ�
		Plum					= 0xDDA0DD, // ÷��ɫ
		PowderBlue				= 0xB0E0E6, // Ӥ������
		Prussianblue			= 0x003153, // ��³ʿ��
		Purple					= 0x800080, // ��ɫ
		Red						= 0xFF0000, // ��ɫ
		Rose					= 0xFF007F, // õ���
		RosePink				= 0xFF66CC, // ǳõ���
		RosyBrown				= 0xBC8F8F, // õ���
		RoyalBlue				= 0x4169E1, // Ʒ��
		Ruby					= 0xCC0080, // �챦ʯɫ
		SaddleBrown				= 0x8B4513, // ����
		Salmon					= 0xFA8072, // �ٺ�
		SalmonPink				= 0xFF8099, // ǳ�ٺ�
		SalviaBlue				= 0x4D80E6, // ��β����
		SandBeige				= 0xE6C3C3, // ɳ��
		SandBrown				= 0xF4A460, // ɳ��
		Sapphire				= 0x082567, // ����ʯɫ
		SaxeBlue				= 0x4798B3, // ����˹��
		Scarlet					= 0xFF2400, // �Ⱥ�
		SeaGreen				= 0x2E8B57, // ����
		Seashell				= 0xFFF5EE, // ����ɫ
		Sepia					= 0x704214, // ����īɫ
		ShellPink				= 0xFFB3BF, // �ǻƺ�
		Sienna					= 0xA0522D, // ����
		Silver					= 0xC0C0C0, // ��ɫ
		SkyBlue					= 0x87CEEB, // ����
		SlateBlue				= 0x6A5ACD, // ����
		SlateGray				= 0x708090, // �һ�
		Snow					= 0xFFFAFA, // ѩɫ
		SpinelRed				= 0xFF73B3, // �⾧ʯ��
		SpringGreen				= 0x00FF80, // ����
		SteelBlue				= 0x4682B4, // ����ɫ
		StrongBlue				= 0x006374, // Ũ��
		StrongRed				= 0xE60000, // �ʺ�
		SunOrange				= 0xFF7300, // ����
		Tan						= 0xD2B48C, // ��ɹɫ
		Tangerine				= 0xF28500, // ��ɫ
		Teal					= 0x008080, // ����
		Thistle					= 0xD8BFD8, // ����
		Tomato					= 0xFF6347, // ެ�Ѻ�
		TropicalOrange			= 0xFF8033, // �ȴ���
		Turquoise				= 0x30D5C8, // ����ʯɫ
		TurquoiseBlue			= 0x33E6CC, // ����ʯ��
		TurquoiseGreen			= 0x4DE680, // ����ʯ��
		Ultramarine				= 0x0033FF, // ��Ũ����
		Veridian				= 0x127436, // ����
		Vermilion				= 0xFF4D00, // ���
		Violet					= 0x8B00FF, // ������ɫ
		WedgwoodBlue			= 0x5686BF, // Τ����´���
		Wheat					= 0xF5DEB3, // С��ɫ
		White					= 0xFFFFFF, // ��ɫ
		WhiteSmoke				= 0xF5F5F5, // ����ɫ
		Wisteria				= 0x5C50E6, // ����ɫ
		Yellow					= 0xFFFF00, // ��ɫ
		YellowGreen				= 0x9ACD32, // ����
	};
};


#endif // !__LRGB_H__
