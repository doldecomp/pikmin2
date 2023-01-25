#ifndef _J3DFRAMECTRL_H
#define _J3DFRAMECTRL_H

#include "types.h"

struct J3DFrameCtrl {
	virtual ~J3DFrameCtrl(); // _08 (weak)

	void init(short);
	void update();

	// _00 VTBL
	u8 mAttr; // _04
	u8 _05;   // _05
	// TODO: Rename to mStartFrame
	short _06; // _06
	// TODO: Rename to mEndFrame
	short _08; // _08
	short _0A; // _0A
	f32 _0C;   // _0C
	f32 _10;   // _10
};

#endif
