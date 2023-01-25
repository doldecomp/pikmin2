#ifndef _EFX2D_ARG_H
#define _EFX2D_ARG_H

#include "Game/enemyInfo.h"
#include "JSystem/JUT/TColor.h"
#include "types.h"
#include "Vector2.h"

namespace efx2d {
struct Arg : Vector2f {
	Arg(f32 x, f32 y)
	{
		this->x = x;
		this->y = y;
	}

	Arg(Vector2f vec) { (Vector2f)(*this) = vec; }

	virtual const char* getName() // _08 (weak)
	{
		return "Arg";
	}

	// _00-_08	= Vector2f
	// _08 		= VTBL
};

struct ArgColor : public Arg {

	virtual const char* getName() // _08 (weak)
	{
		return "ArgColor";
	}

	// _00-_08	= Vector2f
	// _08 		= VTBL
	JUtility::TColor mColor;
};

struct ArgScale : public Arg {

	ArgScale(Vector2f* pos, f32 scale)
	    : Arg(pos->x, pos->y)
	{
		mScale = scale;
	}

	virtual const char* getName() // _08 (weak)
	{
		return "ArgScale";
	}

	// _00-_08	= Vector2f
	// _08 		= VTBL
	f32 mScale; // _0C
};

struct ArgScaleColorColor : public Arg {

	inline ArgScaleColorColor(Vector2f* pos, f32 scale, JUtility::TColor col1, JUtility::TColor col2)
	    : Arg(pos->x, pos->y)
	{
		mScale = scale;
		mColor1.set(col1);
		mColor2.set(col2);
	}

	virtual const char* getName() // _08 (weak)
	{
		return "ArgScaleColorColor";
	}

	// _00-_08	= Vector2f
	// _08 		= VTBL
	f32 mScale;               // _0C
	JUtility::TColor mColor1; // _10
	JUtility::TColor mColor2; // _14
};
} // namespace efx2d

#endif
