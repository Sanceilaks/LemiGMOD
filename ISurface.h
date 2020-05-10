#pragma once
#include "color.h"

//Check https://github.com/danielga/sourcesdk-minimal/
enum FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

struct IntRect
{
	int x0;
	int y0;
	int x1;
	int y1;
};

typedef unsigned long HFont;
typedef unsigned int VPANEL;

enum class FontDrawType 
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

class ISurface
{
public:			//Surface draw funcs == screen will grabbed
	void UnlockCursor()
	{
		using orig_fn = void(__thiscall*)(ISurface*);										
		return (*(orig_fn**)this)[61](this);
	}

	void LockCursor()
	{
		using orig_fn = void(__thiscall*)(ISurface*);
		return (*(orig_fn**)this)[62](this);
	}

	//void SetCursorAlwaysVisible(bool state)
	//{
	//	using orig_fn = void(__thiscall*)(ISurface*);		//49  52
	//	return(*(orig_fn**)this)[57](this);
	//}
};