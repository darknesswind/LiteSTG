#ifndef __LRGB_H__
#define __LRGB_H__
#pragma once
#include "typedef.h"

#define make_rgb(r, g, b) (uint)(((r) << 16) | ((g) << 8) | (b) | 0xFF000000)

class LRgb32;
typedef LRgb32 LRgb;

class LRgb32
{
	union RgbUnion32
	{
		struct RgbStruct32
		{
			uchar blue;
			uchar green;
			uchar red;
			uchar alpha;
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
	explicit operator int()	{ return m_color.nColor; }

public:
	int	red() const		{ return m_color.rgbMap.red; }
	int	green() const	{ return m_color.rgbMap.green; }
	int	blue() const	{ return m_color.rgbMap.blue; }
	int	alpha() const	{ return m_color.rgbMap.alpha; }
	void	setRed(uchar red)		{ m_color.rgbMap.red = red; }
	void	setGreen(uchar green)	{ m_color.rgbMap.green = green; }
	void	setBlue(uchar blue)		{ m_color.rgbMap.blue = blue; }
	void	setAlpha(uchar alpha)	{ m_color.rgbMap.alpha = alpha; }
	void	setRgb(uchar red, uchar green, uchar blue, uchar alpha = 255) noexcept
	{
		m_color.rgbMap.red = red;
		m_color.rgbMap.green = green;
		m_color.rgbMap.blue = blue;
		m_color.rgbMap.alpha = alpha;
	}

private:
	RgbUnion32 m_color;

public:
	// From https://zh.wikipedia.org/wiki/%E9%A2%9C%E8%89%B2%E5%88%97%E8%A1%A8
	enum StaticColorTable : uint
	{
		Transparent				= 0x00000000, // ͸��
		AliceBlue				= 0xFFF0F8FF, // ����˿��
		AlizarinCrimson			= 0xFFE32636, // ���
		Amber					= 0xFFFFBF00, // ����ɫ
		Amethyst				= 0xFF6633CC, // ��ˮ��ɫ
		AntiqueWhite			= 0xFFFAEBD7, // �Ŷ���
		AppleGreen				= 0xFF8CE600, // ƻ����
		Apricot					= 0xFFE69966, // �ӻ�
		Aqua					= 0xFFAFDFE4, // ˮɫ
		AquaBlue				= 0xFF66FFE6, // ˮ��
		Aquamarine				= 0xFF7FFFD4, // ����ɫ
		Azure					= 0xFF007FFF, // տ��
		BabyBlue				= 0xFFE0FFFF, // ǳ��
		BabyPink				= 0xFFFFD9E6, // ǳ�ۺ�
		Beige					= 0xFFF5F5DC, // �׻�ɫ
		Bisque					= 0xFFFFE4C4, // ������
		Black					= 0xFF000000, // ��ɫ
		BlanchedAlmond			= 0xFFFFEBCD, // ���ʰ�
		Blue					= 0xFF0000FF, // ��ɫ
		BlueViolet				= 0xFF8A2BE2, // ����
		BrightGreen				= 0xFF66FF00, // ����
		Bronze					= 0xFFB87333, // ��ͭɫ
		Brown					= 0xFFA52A2A, // ��ɫ
		Burgundy				= 0xFF470024, // ���޵ھƺ�
		BurlyWood				= 0xFFDEB887, // Ӳľɫ
		BurntOrange				= 0xFFCC5500, // ȼ��
		CadetBlue				= 0xFF5F9EA0, // ������
		Camel					= 0xFFA16B47, // ��ɫ
		Camellia				= 0xFFE63995, // ɽ���
		CanaryYellow			= 0xFFFFFF00, // �ʻ�
		CardinalRed				= 0xFF990036, // �����
		Carmine					= 0xFFE6005C, // ��֬��
		CeladonGreen			= 0xFF73E68C, // �����
		Cerise					= 0xFFDE3163, // ӣ�Һ�
		Ceruleanblue			= 0xFF2A52BE, // ε��
		ChampagneYellow			= 0xFFFFFF99, // ���Ļ�
		Chartreuse				= 0xFF7FFF00, // ���ؾ���
		Chocolate				= 0xFFD2691E, // �ɿ���ɫ
		ChromeYellow			= 0xFFE6B800, // ����
		Clematis				= 0xFFCCA3CC, // ��������
		CobaltBlue				= 0xFF0047AB, // ����
		CobaltGreen				= 0xFF66FF59, // ����
		CoconutBrown			= 0xFF4D1F00, // Ҭ��
		Coffee					= 0xFF4D3900, // ����ɫ
		Coral					= 0xFFFF7F50, // ɺ����
		CoralPink				= 0xFFFF80BF, // ǳɺ����
		CornflowerBlue			= 0xFF6495ED, // ʸ������
		Cornsilk				= 0xFFFFF8DC, // ����˿ɫ
		Cream					= 0xFFFFFDD0, // ����ɫ
		Crimson					= 0xFFDC143C, // 糺�
		Cyan					= 0xFF00FFFF, // ��ɫ
		CyanBlue				= 0xFF0DBF8C, // ����
		DarkBlue				= 0xFF00008B, // ����
		DarkCyan				= 0xFF008B8B, // ����
		DarkGoldenrod			= 0xFFB8860B, // �����ɫ
		DarkGray				= 0xFFA9A9A9, // ����
		DarkGreen				= 0xFF006400, // ����
		DarkKhaki				= 0xFFBDB76B, // ������ɫ
		DarkMagenta				= 0xFF8B008B, // �����
		DarkMineralBlue			= 0xFF24367D, // ������
		DarkOliveGreen			= 0xFF556B2F, // �������
		DarkOrange				= 0xFFFF8C00, // ����
		DarkOrchid				= 0xFF9932CC, // ������
		DarkPowderBlue			= 0xFF003399, // ��Ӥ������
		DarkRed					= 0xFF8B0000, // ����
		DarkSalmon				= 0xFFE9967A, // ���ٺ�
		DarkSeaGreen			= 0xFF8FBC8F, // ������
		DarkSlateBlue			= 0xFF483D8B, // ������
		DarkSlateGray			= 0xFF2F4F4F, // ���һ�
		DarkTurquoise			= 0xFF00CED1, // ������ʯɫ
		DarkViolet				= 0xFF9400D3, // ����
		DeepPink				= 0xFFFF1493, // ��ۺ�
		DeepSkyBlue				= 0xFF00BFFF, // ������
		Dimgray					= 0xFF696969, // ���
		DodgerBlue				= 0xFF1E90FF, // ������
		Emerald					= 0xFF50C878, // ����
		FireBrick				= 0xFFB22222, // �ͻ�ש��
		Flamingo				= 0xFFE68AB8, // ��׺�
		FloralWhite				= 0xFFFFFAF0, // ���ܰ�
		FoliageGreen			= 0xFF73B839, // Ҷ��
		ForestGreen				= 0xFF228B22, // ɭ����
		FreshLeaves				= 0xFF99FF4D, // ����
		Fuchsia					= 0xFFF400A1, // Ʒ��
		Gainsboro				= 0xFFDCDCDC, // ��˹���޻�
		GhostWhite				= 0xFFF8F8FF, // �����
		Golden					= 0xFFFFD700, // ��ɫ
		Goldenrod				= 0xFFDAA520, // ���ɫ
		GrassGreen				= 0xFF99E64D, // ����
		Gray					= 0xFF808080, // ��ɫ
		GrayishPurple			= 0xFF8674A1, // ǳ���Ϻ�
		Green					= 0xFF008000, // ��ɫ
		GreenYellow				= 0xFFADFF2F, // �̻�
		Heliotrope				= 0xFF5000B8, // �Ӳ���
		HoneyOrange				= 0xFFFFB366, // �۳�
		Honeydew				= 0xFFF0FFF0, // �۹���
		HorizonBlue				= 0xFFA6FFCC, // ��ɫ
		HotPink					= 0xFFFF69B4, // ů�ۺ�
		IndianRed				= 0xFFCD5C5C, // ӡ�Ⱥ�
		Indigo					= 0xFF4B0080, // ��ɫ
		InternationalKleinBlue	= 0xFF002FA7, // ����������
		IronGray				= 0xFF625B57, // ����ɫ
		Ivory					= 0xFFFFFFF0, // ����ɫ
		IvyGreen				= 0xFF36BF36, // ��������
		Jasmine					= 0xFFE6C35C, // �����
		Khaki					= 0xFF996B1F, // ����ɫ
		LapisLazuli				= 0xFF0D33FF, // ����ʯ��
		Lavender				= 0xFFE6E6FA, // ޹�²���
		LavenderBlush			= 0xFFFFF0F5, // ޹�²��Ϻ�
		LawnGreen				= 0xFF7CFC00, // ��ƺ��
		LemonChiffon			= 0xFFFFFACD, // ���ʳ�ɫ
		LightBlue				= 0xFFADD8E6, // ����
		LightCoral				= 0xFFF08080, // ��ɺ��ɫ
		LightCyan				= 0xFFE0FFFF, // ����
		LightGoldenrodYellow	= 0xFFFAFAD2, // ����ջ�
		LightGray				= 0xFFD3D3D3, // ����ɫ
		LightGreen				= 0xFF90EE90, // ����
		LightKhaki				= 0xFFF0E68C, // ������ɫ
		LightLime				= 0xFFCCFF00, // ��������
		LightPink				= 0xFFFFB6C1, // ���ۺ�
		LightSalmon				= 0xFFFFA07A, // ���ٺ�
		LightSeaGreen			= 0xFF20B2AA, // ������
		LightSkyBlue			= 0xFF87CEFA, // ������
		LightSlateGray			= 0xFF778899, // ���һ�
		LightSteelBlue			= 0xFFB0C4DE, // ������
		LightViolet				= 0xFFEE82EE, // ����
		LightYellow				= 0xFFFFFFE0, // ����
		Lilac					= 0xFFB399FF, // �϶���ɫ
		Lime					= 0xFF00FF00, // ����ɫ
		LimeGreen				= 0xFF32CD32, // ������
		Linen					= 0xFFFAF0E6, // ����ɫ
		Magenta					= 0xFFFF00FF, // ���
		MagentaRose				= 0xFFFF0DA6, // ��õ���
		Malachite				= 0xFF22C32E, // ��ȸʯ��
		Mallow					= 0xFFD94DFF, // ������
		Marigold				= 0xFFFF9900, // ���پջ�
		MarineBlue				= 0xFF00477D, // ˮ����
		Maroon					= 0xFF800000, // ��ɫ
		Mauve					= 0xFF6640FF, // ľ����
		MediumAquamarine		= 0xFF66CDAA, // �б���ɫ
		MediumBlue				= 0xFF0000CD, // ����
		MediumOrchid			= 0xFFBA55D3, // ������
		MediumPurple			= 0xFF9370DB, // ���Ϻ�
		MediumSeaGreen			= 0xFF3CB371, // �к���
		MediumSlateBlue			= 0xFF7B68EE, // ������
		MediumSpringGreen		= 0xFF00FA9A, // �д���ɫ
		MediumTurquoise			= 0xFF48D1CC, // ������ʯɫ
		MediumVioletRed			= 0xFFC71585, // �����Ϻ�
		MidnightBlue			= 0xFF191970, // ��ҹ��
		Mimosa					= 0xFFE6D933, // ���߲ݻ�
		MineralBlue				= 0xFF004D99, // ����
		MineralViolet			= 0xFFB8A1CF, // ����
		Mint					= 0xFF16982B, // ������
		MintCream				= 0xFFF5FFFA, // ��������ɫ
		MistyRose				= 0xFFFFE4E1, // ��õ��ɫ
		Moccasin				= 0xFFFFE4B5, // ¹ƤЬɫ
		MoonYellow				= 0xFFFFFF4D, // �»�
		MossGreen				= 0xFF697723, // ̦޺��
		Mustard					= 0xFFCCCC4D, // ��ĩ��
		NavajoWhite				= 0xFFFFDEAD, // ���߻���
		NavyBlue				= 0xFF000080, // ����
		Ocher					= 0xFFCC7722, // ��ɫ
		OldLace					= 0xFFFDF5E6, // ����˿ɫ
		OldRose					= 0xFFB85798, // ��õ��
		Olive					= 0xFF808000, // ���ɫ
		OliveDrab				= 0xFF6B8E23, // ��魾�����
		OperaMauve				= 0xFFE680FF, // ��Ʒ�Ϻ�
		Orange					= 0xFFFFA500, // ��ɫ
		OrangeRed				= 0xFFFF4500, // �Ⱥ�
		Orchid					= 0xFFDA70D6, // ����
		PailLilac				= 0xFFE6CFE6, // ���϶���ɫ
		PaleBlue				= 0xFF7AB8CC, // ����
		PaleDenim				= 0xFF5E86C1, // �Ҷ�����
		PaleGoldenrod			= 0xFFEEE8AA, // �ҽ��ɫ
		PaleGreen				= 0xFF98FB98, // ����
		PaleOcre				= 0xFFCCB38C, // ����ɫ
		PaleTurquoise			= 0xFFAFEEEE, // ������ʯɫ
		PaleVioletRed			= 0xFFDB7093, // ���Ϻ�
		Pansy					= 0xFF7400A1, // ��ɫ����
		PapayaWhip				= 0xFFFFEFD5, // ެľ��ɫ
		Peach					= 0xFFFFE5B4, // ��ɫ
		PeachPuff				= 0xFFFFDAB9, // ������ɫ
		PeacockBlue				= 0xFF00808C, // ��ȸ��
		PeacockGreen			= 0xFF00A15C, // ��ȸ��
		PearlPink				= 0xFFFFB3E6, // ǳ�����
		Periwinkle				= 0xFFCCCCFF, // ������ɫ
		Persimmon				= 0xFFFF4D40, // ���ӳ�
		Peru					= 0xFFCD853F, // ��³ɫ
		Pink					= 0xFFFFC0CB, // �ۺ�
		Plum					= 0xFFDDA0DD, // ÷��ɫ
		PowderBlue				= 0xFFB0E0E6, // Ӥ������
		Prussianblue			= 0xFF003153, // ��³ʿ��
		Purple					= 0xFF800080, // ��ɫ
		Red						= 0xFFFF0000, // ��ɫ
		Rose					= 0xFFFF007F, // õ���
		RosePink				= 0xFFFF66CC, // ǳõ���
		RosyBrown				= 0xFFBC8F8F, // õ���
		RoyalBlue				= 0xFF4169E1, // Ʒ��
		Ruby					= 0xFFCC0080, // �챦ʯɫ
		SaddleBrown				= 0xFF8B4513, // ����
		Salmon					= 0xFFFA8072, // �ٺ�
		SalmonPink				= 0xFFFF8099, // ǳ�ٺ�
		SalviaBlue				= 0xFF4D80E6, // ��β����
		SandBeige				= 0xFFE6C3C3, // ɳ��
		SandBrown				= 0xFFF4A460, // ɳ��
		Sapphire				= 0xFF082567, // ����ʯɫ
		SaxeBlue				= 0xFF4798B3, // ����˹��
		Scarlet					= 0xFFFF2400, // �Ⱥ�
		SeaGreen				= 0xFF2E8B57, // ����
		Seashell				= 0xFFFFF5EE, // ����ɫ
		Sepia					= 0xFF704214, // ����īɫ
		ShellPink				= 0xFFFFB3BF, // �ǻƺ�
		Sienna					= 0xFFA0522D, // ����
		Silver					= 0xFFC0C0C0, // ��ɫ
		SkyBlue					= 0xFF87CEEB, // ����
		SlateBlue				= 0xFF6A5ACD, // ����
		SlateGray				= 0xFF708090, // �һ�
		Snow					= 0xFFFFFAFA, // ѩɫ
		SpinelRed				= 0xFFFF73B3, // �⾧ʯ��
		SpringGreen				= 0xFF00FF80, // ����
		SteelBlue				= 0xFF4682B4, // ����ɫ
		StrongBlue				= 0xFF006374, // Ũ��
		StrongRed				= 0xFFE60000, // �ʺ�
		SunOrange				= 0xFFFF7300, // ����
		Tan						= 0xFFD2B48C, // ��ɹɫ
		Tangerine				= 0xFFF28500, // ��ɫ
		Teal					= 0xFF008080, // ����
		Thistle					= 0xFFD8BFD8, // ����
		Tomato					= 0xFFFF6347, // ެ�Ѻ�
		TropicalOrange			= 0xFFFF8033, // �ȴ���
		Turquoise				= 0xFF30D5C8, // ����ʯɫ
		TurquoiseBlue			= 0xFF33E6CC, // ����ʯ��
		TurquoiseGreen			= 0xFF4DE680, // ����ʯ��
		Ultramarine				= 0xFF0033FF, // ��Ũ����
		Veridian				= 0xFF127436, // ����
		Vermilion				= 0xFFFF4D00, // ���
		Violet					= 0xFF8B00FF, // ������ɫ
		WedgwoodBlue			= 0xFF5686BF, // Τ����´���
		Wheat					= 0xFFF5DEB3, // С��ɫ
		White					= 0xFFFFFFFF, // ��ɫ
		WhiteSmoke				= 0xFFF5F5F5, // ����ɫ
		Wisteria				= 0xFF5C50E6, // ����ɫ
		Yellow					= 0xFFFFFF00, // ��ɫ
		YellowGreen				= 0xFF9ACD32, // ����
	};
};


#endif // !__LRGB_H__
