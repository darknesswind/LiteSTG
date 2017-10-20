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
		Transparent				= 0x00000000, // Í¸Ã÷
		AliceBlue				= 0xFFF0F8FF, // °®ÀöË¿À¶
		AlizarinCrimson			= 0xFFE32636, // Üçºì
		Amber					= 0xFFFFBF00, // çúçêÉ«
		Amethyst				= 0xFF6633CC, // ×ÏË®¾§É«
		AntiqueWhite			= 0xFFFAEBD7, // ¹Å¶­°×
		AppleGreen				= 0xFF8CE600, // Æ»¹ûÂÌ
		Apricot					= 0xFFE69966, // ÐÓ»Æ
		Aqua					= 0xFFAFDFE4, // Ë®É«
		AquaBlue				= 0xFF66FFE6, // Ë®À¶
		Aquamarine				= 0xFF7FFFD4, // ±ÌÀ¶É«
		Azure					= 0xFF007FFF, // Õ¿À¶
		BabyBlue				= 0xFFE0FFFF, // Ç³À¶
		BabyPink				= 0xFFFFD9E6, // Ç³·Ûºì
		Beige					= 0xFFF5F5DC, // Ã×»ÆÉ«
		Bisque					= 0xFFFFE4C4, // ÌÕÅ÷»Æ
		Black					= 0xFF000000, // ºÚÉ«
		BlanchedAlmond			= 0xFFFFEBCD, // ÐÓÈÊ°×
		Blue					= 0xFF0000FF, // À¶É«
		BlueViolet				= 0xFF8A2BE2, // À¶×Ï
		BrightGreen				= 0xFF66FF00, // Ã÷ÂÌ
		Bronze					= 0xFFB87333, // ¹ÅÍ­É«
		Brown					= 0xFFA52A2A, // ºÖÉ«
		Burgundy				= 0xFF470024, // ²ªôÞµÚ¾Æºì
		BurlyWood				= 0xFFDEB887, // Ó²Ä¾É«
		BurntOrange				= 0xFFCC5500, // È¼³È
		CadetBlue				= 0xFF5F9EA0, // ¾ü·þÀ¶
		Camel					= 0xFFA16B47, // ÍÕÉ«
		Camellia				= 0xFFE63995, // É½²èºì
		CanaryYellow			= 0xFFFFFF00, // ÏÊ»Æ
		CardinalRed				= 0xFF990036, // Êà»úºì
		Carmine					= 0xFFE6005C, // ëÙÖ¬ºì
		CeladonGreen			= 0xFF73E68C, // Çà´ÉÂÌ
		Cerise					= 0xFFDE3163, // Ó£ÌÒºì
		Ceruleanblue			= 0xFF2A52BE, // ÎµÀ¶
		ChampagneYellow			= 0xFFFFFF99, // ÏãéÄ»Æ
		Chartreuse				= 0xFF7FFF00, // ²éÌØ¾ÆÂÌ
		Chocolate				= 0xFFD2691E, // ÇÉ¿ËÁ¦É«
		ChromeYellow			= 0xFFE6B800, // ¸õ»Æ
		Clematis				= 0xFFCCA3CC, // ÌúÏßÁ«×Ï
		CobaltBlue				= 0xFF0047AB, // îÜÀ¶
		CobaltGreen				= 0xFF66FF59, // îÜÂÌ
		CoconutBrown			= 0xFF4D1F00, // Ò¬ºÖ
		Coffee					= 0xFF4D3900, // ¿§·ÈÉ«
		Coral					= 0xFFFF7F50, // Éºº÷ºì
		CoralPink				= 0xFFFF80BF, // Ç³Éºº÷ºì
		CornflowerBlue			= 0xFF6495ED, // Ê¸³µ¾ÕÀ¶
		Cornsilk				= 0xFFFFF8DC, // ÓñÃ×Ë¿É«
		Cream					= 0xFFFFFDD0, // ÄÌÓÍÉ«
		Crimson					= 0xFFDC143C, // ç³ºì
		Cyan					= 0xFF00FFFF, // ÇàÉ«
		CyanBlue				= 0xFF0DBF8C, // ÇàÀ¶
		DarkBlue				= 0xFF00008B, // °µÀ¶
		DarkCyan				= 0xFF008B8B, // °µÇà
		DarkGoldenrod			= 0xFFB8860B, // °µ½ð¾ÕÉ«
		DarkGray				= 0xFFA9A9A9, // °µ»Ò
		DarkGreen				= 0xFF006400, // °µÂÌ
		DarkKhaki				= 0xFFBDB76B, // °µ¿¨ÆäÉ«
		DarkMagenta				= 0xFF8B008B, // °µÑóºì
		DarkMineralBlue			= 0xFF24367D, // °µ¿óÀ¶
		DarkOliveGreen			= 0xFF556B2F, // °µéÏé­ÂÌ
		DarkOrange				= 0xFFFF8C00, // °µ³È
		DarkOrchid				= 0xFF9932CC, // °µÀ¼×Ï
		DarkPowderBlue			= 0xFF003399, // °µÓ¤¶ù·ÛÀ¶
		DarkRed					= 0xFF8B0000, // °µºì
		DarkSalmon				= 0xFFE9967A, // °µöÙºì
		DarkSeaGreen			= 0xFF8FBC8F, // °µº£ÂÌ
		DarkSlateBlue			= 0xFF483D8B, // °µÑÒÀ¶
		DarkSlateGray			= 0xFF2F4F4F, // °µÑÒ»Ò
		DarkTurquoise			= 0xFF00CED1, // °µÂÌËÉÊ¯É«
		DarkViolet				= 0xFF9400D3, // °µ×Ï
		DeepPink				= 0xFFFF1493, // Éî·Ûºì
		DeepSkyBlue				= 0xFF00BFFF, // ÉîÌìÀ¶
		Dimgray					= 0xFF696969, // »è»Ò
		DodgerBlue				= 0xFF1E90FF, // µÀÆæÀ¶
		Emerald					= 0xFF50C878, // ±ÌÂÌ
		FireBrick				= 0xFFB22222, // ÄÍ»ð×©ºì
		Flamingo				= 0xFFE68AB8, // »ðº×ºì
		FloralWhite				= 0xFFFFFAF0, // »¨»Ü°×
		FoliageGreen			= 0xFF73B839, // Ò¶ÂÌ
		ForestGreen				= 0xFF228B22, // É­ÁÖÂÌ
		FreshLeaves				= 0xFF99FF4D, // ÄÛÂÌ
		Fuchsia					= 0xFFF400A1, // Æ·ºì
		Gainsboro				= 0xFFDCDCDC, // ¸ýË¹²©ÂÞ»Ò
		GhostWhite				= 0xFFF8F8FF, // ÓÄÁé°×
		Golden					= 0xFFFFD700, // ½ðÉ«
		Goldenrod				= 0xFFDAA520, // ½ð¾ÕÉ«
		GrassGreen				= 0xFF99E64D, // ²ÝÂÌ
		Gray					= 0xFF808080, // »ÒÉ«
		GrayishPurple			= 0xFF8674A1, // Ç³»Ò×Ïºì
		Green					= 0xFF008000, // ÂÌÉ«
		GreenYellow				= 0xFFADFF2F, // ÂÌ»Æ
		Heliotrope				= 0xFF5000B8, // çÓ²Ý×Ï
		HoneyOrange				= 0xFFFFB366, // ÃÛ³È
		Honeydew				= 0xFFF0FFF0, // ÃÛ¹ÏÂÌ
		HorizonBlue				= 0xFFA6FFCC, // ²ÔÉ«
		HotPink					= 0xFFFF69B4, // Å¯·Ûºì
		IndianRed				= 0xFFCD5C5C, // Ó¡¶Èºì
		Indigo					= 0xFF4B0080, // µåÉ«
		InternationalKleinBlue	= 0xFF002FA7, // ¹ú¼ÊÆæÁ¬À¶
		IronGray				= 0xFF625B57, // Ìú»ÒÉ«
		Ivory					= 0xFFFFFFF0, // ÏóÑÀÉ«
		IvyGreen				= 0xFF36BF36, // ³£´ºÌÙÂÌ
		Jasmine					= 0xFFE6C35C, // ÜÔÀò»Æ
		Khaki					= 0xFF996B1F, // ¿¨ÆäÉ«
		LapisLazuli				= 0xFF0D33FF, // ÌìÇàÊ¯À¶
		Lavender				= 0xFFE6E6FA, // Þ¹ÒÂ²Ý×Ï
		LavenderBlush			= 0xFFFFF0F5, // Þ¹ÒÂ²Ý×Ïºì
		LawnGreen				= 0xFF7CFC00, // ²ÝÆºÂÌ
		LemonChiffon			= 0xFFFFFACD, // ÄûÃÊ³ñÉ«
		LightBlue				= 0xFFADD8E6, // ÁÁÀ¶
		LightCoral				= 0xFFF08080, // ÁÁÉºº÷É«
		LightCyan				= 0xFFE0FFFF, // ÁÁÇà
		LightGoldenrodYellow	= 0xFFFAFAD2, // ÁÁ½ð¾Õ»Æ
		LightGray				= 0xFFD3D3D3, // ÁÁ»ÒÉ«
		LightGreen				= 0xFF90EE90, // ÁÁÂÌ
		LightKhaki				= 0xFFF0E68C, // ÁÁ¿¨ÆäÉ«
		LightLime				= 0xFFCCFF00, // ÁÁÄûÃÊÂÌ
		LightPink				= 0xFFFFB6C1, // ÁÁ·Ûºì
		LightSalmon				= 0xFFFFA07A, // ÁÁöÙºì
		LightSeaGreen			= 0xFF20B2AA, // ÁÁº£ÂÌ
		LightSkyBlue			= 0xFF87CEFA, // ÁÁÌìÀ¶
		LightSlateGray			= 0xFF778899, // ÁÁÑÒ»Ò
		LightSteelBlue			= 0xFFB0C4DE, // ÁÁ¸ÖÀ¶
		LightViolet				= 0xFFEE82EE, // ÁÁ×Ï
		LightYellow				= 0xFFFFFFE0, // ÁÁ»Æ
		Lilac					= 0xFFB399FF, // ×Ï¶¡ÏãÉ«
		Lime					= 0xFF00FF00, // ÏÊÂÌÉ«
		LimeGreen				= 0xFF32CD32, // ÄûÃÊÂÌ
		Linen					= 0xFFFAF0E6, // ÑÇÂéÉ«
		Magenta					= 0xFFFF00FF, // Ñóºì
		MagentaRose				= 0xFFFF0DA6, // ÑóÃµ¹åºì
		Malachite				= 0xFF22C32E, // ¿×È¸Ê¯ÂÌ
		Mallow					= 0xFFD94DFF, // ½õ¿û×Ï
		Marigold				= 0xFFFF9900, // ÍòÊÙ¾Õ»Æ
		MarineBlue				= 0xFF00477D, // Ë®ÊÖÀ¶
		Maroon					= 0xFF800000, // ÀõÉ«
		Mauve					= 0xFF6640FF, // Ä¾éÈ×Ï
		MediumAquamarine		= 0xFF66CDAA, // ÖÐ±ÌÀ¶É«
		MediumBlue				= 0xFF0000CD, // ÖÐÀ¶
		MediumOrchid			= 0xFFBA55D3, // ÖÐÀ¼×Ï
		MediumPurple			= 0xFF9370DB, // ÖÐ×Ïºì
		MediumSeaGreen			= 0xFF3CB371, // ÖÐº£ÂÌ
		MediumSlateBlue			= 0xFF7B68EE, // ÖÐÑÒÀ¶
		MediumSpringGreen		= 0xFF00FA9A, // ÖÐ´ºÂÌÉ«
		MediumTurquoise			= 0xFF48D1CC, // ÖÐÂÌËÉÊ¯É«
		MediumVioletRed			= 0xFFC71585, // ÖÐÇà×Ïºì
		MidnightBlue			= 0xFF191970, // ÎçÒ¹À¶
		Mimosa					= 0xFFE6D933, // º¬Ðß²Ý»Æ
		MineralBlue				= 0xFF004D99, // ¿óÀ¶
		MineralViolet			= 0xFFB8A1CF, // ¿ó×Ï
		Mint					= 0xFF16982B, // ±¡ºÉÂÌ
		MintCream				= 0xFFF5FFFA, // ±¡ºÉÄÌÓÍÉ«
		MistyRose				= 0xFFFFE4E1, // ÎíÃµ¹åÉ«
		Moccasin				= 0xFFFFE4B5, // Â¹Æ¤Ð¬É«
		MoonYellow				= 0xFFFFFF4D, // ÔÂ»Æ
		MossGreen				= 0xFF697723, // Ì¦ÞºÂÌ
		Mustard					= 0xFFCCCC4D, // ½æÄ©»Æ
		NavajoWhite				= 0xFFFFDEAD, // ÄÇÍß»ô°×
		NavyBlue				= 0xFF000080, // ²ØÇà
		Ocher					= 0xFFCC7722, // ô÷É«
		OldLace					= 0xFFFDF5E6, // ¾ÉÀÙË¿É«
		OldRose					= 0xFFB85798, // ³ÂÃµºì
		Olive					= 0xFF808000, // éÏé­É«
		OliveDrab				= 0xFF6B8E23, // éÏé­¾ü·þÂÌ
		OperaMauve				= 0xFFE680FF, // ÓÅÆ·×Ïºì
		Orange					= 0xFFFFA500, // ³ÈÉ«
		OrangeRed				= 0xFFFF4500, // ³Èºì
		Orchid					= 0xFFDA70D6, // À¼×Ï
		PailLilac				= 0xFFE6CFE6, // µ­×Ï¶¡ÏãÉ«
		PaleBlue				= 0xFF7AB8CC, // »ÒÀ¶
		PaleDenim				= 0xFF5E86C1, // »Ò¶¡ÄþÀ¶
		PaleGoldenrod			= 0xFFEEE8AA, // »Ò½ð¾ÕÉ«
		PaleGreen				= 0xFF98FB98, // »ÒÂÌ
		PaleOcre				= 0xFFCCB38C, // »ÒÍÁÉ«
		PaleTurquoise			= 0xFFAFEEEE, // »ÒÂÌËÉÊ¯É«
		PaleVioletRed			= 0xFFDB7093, // »Ò×Ïºì
		Pansy					= 0xFF7400A1, // ÈýÉ«ÝÀ×Ï
		PapayaWhip				= 0xFFFFEFD5, // Þ¬Ä¾¹ÏÉ«
		Peach					= 0xFFFFE5B4, // ÌÒÉ«
		PeachPuff				= 0xFFFFDAB9, // ·ÛÆËÌÒÉ«
		PeacockBlue				= 0xFF00808C, // ¿×È¸À¶
		PeacockGreen			= 0xFF00A15C, // ¿×È¸ÂÌ
		PearlPink				= 0xFFFFB3E6, // Ç³ÕäÖéºì
		Periwinkle				= 0xFFCCCCFF, // ³¤´º»¨É«
		Persimmon				= 0xFFFF4D40, // ÊÁ×Ó³È
		Peru					= 0xFFCD853F, // ÃØÂ³É«
		Pink					= 0xFFFFC0CB, // ·Ûºì
		Plum					= 0xFFDDA0DD, // Ã·ºìÉ«
		PowderBlue				= 0xFFB0E0E6, // Ó¤¶ù·ÛÀ¶
		Prussianblue			= 0xFF003153, // ÆÕÂ³Ê¿À¶
		Purple					= 0xFF800080, // ×ÏÉ«
		Red						= 0xFFFF0000, // ºìÉ«
		Rose					= 0xFFFF007F, // Ãµ¹åºì
		RosePink				= 0xFFFF66CC, // Ç³Ãµ¹åºì
		RosyBrown				= 0xFFBC8F8F, // Ãµ¹åºÖ
		RoyalBlue				= 0xFF4169E1, // Æ·À¶
		Ruby					= 0xFFCC0080, // ºì±¦Ê¯É«
		SaddleBrown				= 0xFF8B4513, // °°ºÖ
		Salmon					= 0xFFFA8072, // öÙºì
		SalmonPink				= 0xFFFF8099, // Ç³öÙºì
		SalviaBlue				= 0xFF4D80E6, // ÊóÎ²²ÝÀ¶
		SandBeige				= 0xFFE6C3C3, // É³×Ø
		SandBrown				= 0xFFF4A460, // É³ºÖ
		Sapphire				= 0xFF082567, // À¶±¦Ê¯É«
		SaxeBlue				= 0xFF4798B3, // Èø¿ËË¹À¶
		Scarlet					= 0xFFFF2400, // ÐÈºì
		SeaGreen				= 0xFF2E8B57, // º£ÂÌ
		Seashell				= 0xFFFFF5EE, // º£±´É«
		Sepia					= 0xFF704214, // ÎÚÔôÄ«É«
		ShellPink				= 0xFFFFB3BF, // ¿Ç»Æºì
		Sienna					= 0xFFA0522D, // ô÷»Æ
		Silver					= 0xFFC0C0C0, // ÒøÉ«
		SkyBlue					= 0xFF87CEEB, // ÌìÀ¶
		SlateBlue				= 0xFF6A5ACD, // ÑÒÀ¶
		SlateGray				= 0xFF708090, // ÑÒ»Ò
		Snow					= 0xFFFFFAFA, // Ñ©É«
		SpinelRed				= 0xFFFF73B3, // ¼â¾§Ê¯ºì
		SpringGreen				= 0xFF00FF80, // ´ºÂÌ
		SteelBlue				= 0xFF4682B4, // ¸ÖÇàÉ«
		StrongBlue				= 0xFF006374, // Å¨À¶
		StrongRed				= 0xFFE60000, // ÏÊºì
		SunOrange				= 0xFFFF7300, // Ñô³È
		Tan						= 0xFFD2B48C, // ÈÕÉ¹É«
		Tangerine				= 0xFFF28500, // éÙÉ«
		Teal					= 0xFF008080, // ÙìÂÌ
		Thistle					= 0xFFD8BFD8, // ¼»×Ï
		Tomato					= 0xFFFF6347, // Þ¬ÇÑºì
		TropicalOrange			= 0xFFFF8033, // ÈÈ´ø³È
		Turquoise				= 0xFF30D5C8, // ÂÌËÉÊ¯É«
		TurquoiseBlue			= 0xFF33E6CC, // ÂÌËÉÊ¯À¶
		TurquoiseGreen			= 0xFF4DE680, // ÂÌËÉÊ¯ÂÌ
		Ultramarine				= 0xFF0033FF, // ¼«Å¨º£À¶
		Veridian				= 0xFF127436, // ¸õÂÌ
		Vermilion				= 0xFFFF4D00, // Öìºì
		Violet					= 0xFF8B00FF, // ×ÏÂÞÀ¼É«
		WedgwoodBlue			= 0xFF5686BF, // Î¤ÆæÎéµÂ´ÉÀ¶
		Wheat					= 0xFFF5DEB3, // Ð¡ÂóÉ«
		White					= 0xFFFFFFFF, // °×É«
		WhiteSmoke				= 0xFFF5F5F5, // °×ÑÌÉ«
		Wisteria				= 0xFF5C50E6, // ×ÏÌÙÉ«
		Yellow					= 0xFFFFFF00, // »ÆÉ«
		YellowGreen				= 0xFF9ACD32, // »ÆÂÌ
	};
};


#endif // !__LRGB_H__
