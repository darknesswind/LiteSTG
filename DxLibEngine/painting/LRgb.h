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
		Transparent				= 0x000000, // Í¸Ã÷
		AliceBlue				= 0xF0F8FF, // °®ÀöË¿À¶
		AlizarinCrimson			= 0xE32636, // Üçºì
		Amber					= 0xFFBF00, // çúçêÉ«
		Amethyst				= 0x6633CC, // ×ÏË®¾§É«
		AntiqueWhite			= 0xFAEBD7, // ¹Å¶­°×
		AppleGreen				= 0x8CE600, // Æ»¹ûÂÌ
		Apricot					= 0xE69966, // ÐÓ»Æ
		Aqua					= 0xAFDFE4, // Ë®É«
		AquaBlue				= 0x66FFE6, // Ë®À¶
		Aquamarine				= 0x7FFFD4, // ±ÌÀ¶É«
		Azure					= 0x007FFF, // Õ¿À¶
		BabyBlue				= 0xE0FFFF, // Ç³À¶
		BabyPink				= 0xFFD9E6, // Ç³·Ûºì
		Beige					= 0xF5F5DC, // Ã×»ÆÉ«
		Bisque					= 0xFFE4C4, // ÌÕÅ÷»Æ
		Black					= 0x000000, // ºÚÉ«
		BlanchedAlmond			= 0xFFEBCD, // ÐÓÈÊ°×
		Blue					= 0x0000FF, // À¶É«
		BlueViolet				= 0x8A2BE2, // À¶×Ï
		BrightGreen				= 0x66FF00, // Ã÷ÂÌ
		Bronze					= 0xB87333, // ¹ÅÍ­É«
		Brown					= 0xA52A2A, // ºÖÉ«
		Burgundy				= 0x470024, // ²ªôÞµÚ¾Æºì
		BurlyWood				= 0xDEB887, // Ó²Ä¾É«
		BurntOrange				= 0xCC5500, // È¼³È
		CadetBlue				= 0x5F9EA0, // ¾ü·þÀ¶
		Camel					= 0xA16B47, // ÍÕÉ«
		Camellia				= 0xE63995, // É½²èºì
		CanaryYellow			= 0xFFFF00, // ÏÊ»Æ
		CardinalRed				= 0x990036, // Êà»úºì
		Carmine					= 0xE6005C, // ëÙÖ¬ºì
		CeladonGreen			= 0x73E68C, // Çà´ÉÂÌ
		Cerise					= 0xDE3163, // Ó£ÌÒºì
		Ceruleanblue			= 0x2A52BE, // ÎµÀ¶
		ChampagneYellow			= 0xFFFF99, // ÏãéÄ»Æ
		Chartreuse				= 0x7FFF00, // ²éÌØ¾ÆÂÌ
		Chocolate				= 0xD2691E, // ÇÉ¿ËÁ¦É«
		ChromeYellow			= 0xE6B800, // ¸õ»Æ
		Clematis				= 0xCCA3CC, // ÌúÏßÁ«×Ï
		CobaltBlue				= 0x0047AB, // îÜÀ¶
		CobaltGreen				= 0x66FF59, // îÜÂÌ
		CoconutBrown			= 0x4D1F00, // Ò¬ºÖ
		Coffee					= 0x4D3900, // ¿§·ÈÉ«
		Coral					= 0xFF7F50, // Éºº÷ºì
		CoralPink				= 0xFF80BF, // Ç³Éºº÷ºì
		CornflowerBlue			= 0x6495ED, // Ê¸³µ¾ÕÀ¶
		Cornsilk				= 0xFFF8DC, // ÓñÃ×Ë¿É«
		Cream					= 0xFFFDD0, // ÄÌÓÍÉ«
		Crimson					= 0xDC143C, // ç³ºì
		Cyan					= 0x00FFFF, // ÇàÉ«
		CyanBlue				= 0x0DBF8C, // ÇàÀ¶
		DarkBlue				= 0x00008B, // °µÀ¶
		DarkCyan				= 0x008B8B, // °µÇà
		DarkGoldenrod			= 0xB8860B, // °µ½ð¾ÕÉ«
		DarkGray				= 0xA9A9A9, // °µ»Ò
		DarkGreen				= 0x006400, // °µÂÌ
		DarkKhaki				= 0xBDB76B, // °µ¿¨ÆäÉ«
		DarkMagenta				= 0x8B008B, // °µÑóºì
		DarkMineralBlue			= 0x24367D, // °µ¿óÀ¶
		DarkOliveGreen			= 0x556B2F, // °µéÏé­ÂÌ
		DarkOrange				= 0xFF8C00, // °µ³È
		DarkOrchid				= 0x9932CC, // °µÀ¼×Ï
		DarkPowderBlue			= 0x003399, // °µÓ¤¶ù·ÛÀ¶
		DarkRed					= 0x8B0000, // °µºì
		DarkSalmon				= 0xE9967A, // °µöÙºì
		DarkSeaGreen			= 0x8FBC8F, // °µº£ÂÌ
		DarkSlateBlue			= 0x483D8B, // °µÑÒÀ¶
		DarkSlateGray			= 0x2F4F4F, // °µÑÒ»Ò
		DarkTurquoise			= 0x00CED1, // °µÂÌËÉÊ¯É«
		DarkViolet				= 0x9400D3, // °µ×Ï
		DeepPink				= 0xFF1493, // Éî·Ûºì
		DeepSkyBlue				= 0x00BFFF, // ÉîÌìÀ¶
		Dimgray					= 0x696969, // »è»Ò
		DodgerBlue				= 0x1E90FF, // µÀÆæÀ¶
		Emerald					= 0x50C878, // ±ÌÂÌ
		FireBrick				= 0xB22222, // ÄÍ»ð×©ºì
		Flamingo				= 0xE68AB8, // »ðº×ºì
		FloralWhite				= 0xFFFAF0, // »¨»Ü°×
		FoliageGreen			= 0x73B839, // Ò¶ÂÌ
		ForestGreen				= 0x228B22, // É­ÁÖÂÌ
		FreshLeaves				= 0x99FF4D, // ÄÛÂÌ
		Fuchsia					= 0xF400A1, // Æ·ºì
		Gainsboro				= 0xDCDCDC, // ¸ýË¹²©ÂÞ»Ò
		GhostWhite				= 0xF8F8FF, // ÓÄÁé°×
		Golden					= 0xFFD700, // ½ðÉ«
		Goldenrod				= 0xDAA520, // ½ð¾ÕÉ«
		GrassGreen				= 0x99E64D, // ²ÝÂÌ
		Gray					= 0x808080, // »ÒÉ«
		GrayishPurple			= 0x8674A1, // Ç³»Ò×Ïºì
		Green					= 0x008000, // ÂÌÉ«
		GreenYellow				= 0xADFF2F, // ÂÌ»Æ
		Heliotrope				= 0x5000B8, // çÓ²Ý×Ï
		HoneyOrange				= 0xFFB366, // ÃÛ³È
		Honeydew				= 0xF0FFF0, // ÃÛ¹ÏÂÌ
		HorizonBlue				= 0xA6FFCC, // ²ÔÉ«
		HotPink					= 0xFF69B4, // Å¯·Ûºì
		IndianRed				= 0xCD5C5C, // Ó¡¶Èºì
		Indigo					= 0x4B0080, // µåÉ«
		InternationalKleinBlue	= 0x002FA7, // ¹ú¼ÊÆæÁ¬À¶
		IronGray				= 0x625B57, // Ìú»ÒÉ«
		Ivory					= 0xFFFFF0, // ÏóÑÀÉ«
		IvyGreen				= 0x36BF36, // ³£´ºÌÙÂÌ
		Jasmine					= 0xE6C35C, // ÜÔÀò»Æ
		Khaki					= 0x996B1F, // ¿¨ÆäÉ«
		LapisLazuli				= 0x0D33FF, // ÌìÇàÊ¯À¶
		Lavender				= 0xE6E6FA, // Þ¹ÒÂ²Ý×Ï
		LavenderBlush			= 0xFFF0F5, // Þ¹ÒÂ²Ý×Ïºì
		LawnGreen				= 0x7CFC00, // ²ÝÆºÂÌ
		LemonChiffon			= 0xFFFACD, // ÄûÃÊ³ñÉ«
		LightBlue				= 0xADD8E6, // ÁÁÀ¶
		LightCoral				= 0xF08080, // ÁÁÉºº÷É«
		LightCyan				= 0xE0FFFF, // ÁÁÇà
		LightGoldenrodYellow	= 0xFAFAD2, // ÁÁ½ð¾Õ»Æ
		LightGray				= 0xD3D3D3, // ÁÁ»ÒÉ«
		LightGreen				= 0x90EE90, // ÁÁÂÌ
		LightKhaki				= 0xF0E68C, // ÁÁ¿¨ÆäÉ«
		LightLime				= 0xCCFF00, // ÁÁÄûÃÊÂÌ
		LightPink				= 0xFFB6C1, // ÁÁ·Ûºì
		LightSalmon				= 0xFFA07A, // ÁÁöÙºì
		LightSeaGreen			= 0x20B2AA, // ÁÁº£ÂÌ
		LightSkyBlue			= 0x87CEFA, // ÁÁÌìÀ¶
		LightSlateGray			= 0x778899, // ÁÁÑÒ»Ò
		LightSteelBlue			= 0xB0C4DE, // ÁÁ¸ÖÀ¶
		LightViolet				= 0xEE82EE, // ÁÁ×Ï
		LightYellow				= 0xFFFFE0, // ÁÁ»Æ
		Lilac					= 0xB399FF, // ×Ï¶¡ÏãÉ«
		Lime					= 0x00FF00, // ÏÊÂÌÉ«
		LimeGreen				= 0x32CD32, // ÄûÃÊÂÌ
		Linen					= 0xFAF0E6, // ÑÇÂéÉ«
		Magenta					= 0xFF00FF, // Ñóºì
		MagentaRose				= 0xFF0DA6, // ÑóÃµ¹åºì
		Malachite				= 0x22C32E, // ¿×È¸Ê¯ÂÌ
		Mallow					= 0xD94DFF, // ½õ¿û×Ï
		Marigold				= 0xFF9900, // ÍòÊÙ¾Õ»Æ
		MarineBlue				= 0x00477D, // Ë®ÊÖÀ¶
		Maroon					= 0x800000, // ÀõÉ«
		Mauve					= 0x6640FF, // Ä¾éÈ×Ï
		MediumAquamarine		= 0x66CDAA, // ÖÐ±ÌÀ¶É«
		MediumBlue				= 0x0000CD, // ÖÐÀ¶
		MediumOrchid			= 0xBA55D3, // ÖÐÀ¼×Ï
		MediumPurple			= 0x9370DB, // ÖÐ×Ïºì
		MediumSeaGreen			= 0x3CB371, // ÖÐº£ÂÌ
		MediumSlateBlue			= 0x7B68EE, // ÖÐÑÒÀ¶
		MediumSpringGreen		= 0x00FA9A, // ÖÐ´ºÂÌÉ«
		MediumTurquoise			= 0x48D1CC, // ÖÐÂÌËÉÊ¯É«
		MediumVioletRed			= 0xC71585, // ÖÐÇà×Ïºì
		MidnightBlue			= 0x191970, // ÎçÒ¹À¶
		Mimosa					= 0xE6D933, // º¬Ðß²Ý»Æ
		MineralBlue				= 0x004D99, // ¿óÀ¶
		MineralViolet			= 0xB8A1CF, // ¿ó×Ï
		Mint					= 0x16982B, // ±¡ºÉÂÌ
		MintCream				= 0xF5FFFA, // ±¡ºÉÄÌÓÍÉ«
		MistyRose				= 0xFFE4E1, // ÎíÃµ¹åÉ«
		Moccasin				= 0xFFE4B5, // Â¹Æ¤Ð¬É«
		MoonYellow				= 0xFFFF4D, // ÔÂ»Æ
		MossGreen				= 0x697723, // Ì¦ÞºÂÌ
		Mustard					= 0xCCCC4D, // ½æÄ©»Æ
		NavajoWhite				= 0xFFDEAD, // ÄÇÍß»ô°×
		NavyBlue				= 0x000080, // ²ØÇà
		Ocher					= 0xCC7722, // ô÷É«
		OldLace					= 0xFDF5E6, // ¾ÉÀÙË¿É«
		OldRose					= 0xB85798, // ³ÂÃµºì
		Olive					= 0x808000, // éÏé­É«
		OliveDrab				= 0x6B8E23, // éÏé­¾ü·þÂÌ
		OperaMauve				= 0xE680FF, // ÓÅÆ·×Ïºì
		Orange					= 0xFFA500, // ³ÈÉ«
		OrangeRed				= 0xFF4500, // ³Èºì
		Orchid					= 0xDA70D6, // À¼×Ï
		PailLilac				= 0xE6CFE6, // µ­×Ï¶¡ÏãÉ«
		PaleBlue				= 0x7AB8CC, // »ÒÀ¶
		PaleDenim				= 0x5E86C1, // »Ò¶¡ÄþÀ¶
		PaleGoldenrod			= 0xEEE8AA, // »Ò½ð¾ÕÉ«
		PaleGreen				= 0x98FB98, // »ÒÂÌ
		PaleOcre				= 0xCCB38C, // »ÒÍÁÉ«
		PaleTurquoise			= 0xAFEEEE, // »ÒÂÌËÉÊ¯É«
		PaleVioletRed			= 0xDB7093, // »Ò×Ïºì
		Pansy					= 0x7400A1, // ÈýÉ«ÝÀ×Ï
		PapayaWhip				= 0xFFEFD5, // Þ¬Ä¾¹ÏÉ«
		Peach					= 0xFFE5B4, // ÌÒÉ«
		PeachPuff				= 0xFFDAB9, // ·ÛÆËÌÒÉ«
		PeacockBlue				= 0x00808C, // ¿×È¸À¶
		PeacockGreen			= 0x00A15C, // ¿×È¸ÂÌ
		PearlPink				= 0xFFB3E6, // Ç³ÕäÖéºì
		Periwinkle				= 0xCCCCFF, // ³¤´º»¨É«
		Persimmon				= 0xFF4D40, // ÊÁ×Ó³È
		Peru					= 0xCD853F, // ÃØÂ³É«
		Pink					= 0xFFC0CB, // ·Ûºì
		Plum					= 0xDDA0DD, // Ã·ºìÉ«
		PowderBlue				= 0xB0E0E6, // Ó¤¶ù·ÛÀ¶
		Prussianblue			= 0x003153, // ÆÕÂ³Ê¿À¶
		Purple					= 0x800080, // ×ÏÉ«
		Red						= 0xFF0000, // ºìÉ«
		Rose					= 0xFF007F, // Ãµ¹åºì
		RosePink				= 0xFF66CC, // Ç³Ãµ¹åºì
		RosyBrown				= 0xBC8F8F, // Ãµ¹åºÖ
		RoyalBlue				= 0x4169E1, // Æ·À¶
		Ruby					= 0xCC0080, // ºì±¦Ê¯É«
		SaddleBrown				= 0x8B4513, // °°ºÖ
		Salmon					= 0xFA8072, // öÙºì
		SalmonPink				= 0xFF8099, // Ç³öÙºì
		SalviaBlue				= 0x4D80E6, // ÊóÎ²²ÝÀ¶
		SandBeige				= 0xE6C3C3, // É³×Ø
		SandBrown				= 0xF4A460, // É³ºÖ
		Sapphire				= 0x082567, // À¶±¦Ê¯É«
		SaxeBlue				= 0x4798B3, // Èø¿ËË¹À¶
		Scarlet					= 0xFF2400, // ÐÈºì
		SeaGreen				= 0x2E8B57, // º£ÂÌ
		Seashell				= 0xFFF5EE, // º£±´É«
		Sepia					= 0x704214, // ÎÚÔôÄ«É«
		ShellPink				= 0xFFB3BF, // ¿Ç»Æºì
		Sienna					= 0xA0522D, // ô÷»Æ
		Silver					= 0xC0C0C0, // ÒøÉ«
		SkyBlue					= 0x87CEEB, // ÌìÀ¶
		SlateBlue				= 0x6A5ACD, // ÑÒÀ¶
		SlateGray				= 0x708090, // ÑÒ»Ò
		Snow					= 0xFFFAFA, // Ñ©É«
		SpinelRed				= 0xFF73B3, // ¼â¾§Ê¯ºì
		SpringGreen				= 0x00FF80, // ´ºÂÌ
		SteelBlue				= 0x4682B4, // ¸ÖÇàÉ«
		StrongBlue				= 0x006374, // Å¨À¶
		StrongRed				= 0xE60000, // ÏÊºì
		SunOrange				= 0xFF7300, // Ñô³È
		Tan						= 0xD2B48C, // ÈÕÉ¹É«
		Tangerine				= 0xF28500, // éÙÉ«
		Teal					= 0x008080, // ÙìÂÌ
		Thistle					= 0xD8BFD8, // ¼»×Ï
		Tomato					= 0xFF6347, // Þ¬ÇÑºì
		TropicalOrange			= 0xFF8033, // ÈÈ´ø³È
		Turquoise				= 0x30D5C8, // ÂÌËÉÊ¯É«
		TurquoiseBlue			= 0x33E6CC, // ÂÌËÉÊ¯À¶
		TurquoiseGreen			= 0x4DE680, // ÂÌËÉÊ¯ÂÌ
		Ultramarine				= 0x0033FF, // ¼«Å¨º£À¶
		Veridian				= 0x127436, // ¸õÂÌ
		Vermilion				= 0xFF4D00, // Öìºì
		Violet					= 0x8B00FF, // ×ÏÂÞÀ¼É«
		WedgwoodBlue			= 0x5686BF, // Î¤ÆæÎéµÂ´ÉÀ¶
		Wheat					= 0xF5DEB3, // Ð¡ÂóÉ«
		White					= 0xFFFFFF, // °×É«
		WhiteSmoke				= 0xF5F5F5, // °×ÑÌÉ«
		Wisteria				= 0x5C50E6, // ×ÏÌÙÉ«
		Yellow					= 0xFFFF00, // »ÆÉ«
		YellowGreen				= 0x9ACD32, // »ÆÂÌ
	};
};


#endif // !__LRGB_H__
