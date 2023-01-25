#ifndef _J2DTEXGENBLOCK_H
#define _J2DTEXGENBLOCK_H

#include "JSystem/J2D/J2DTypes.h"
#include "JSystem/J2D/J2DTexMtx.h"
#include "types.h"

// NB: TP does this in one struct with private/public
struct _J2DTexGenBlockParent {
	u32 mTexGenNum;            // _00
	J2DTexCoord mTexCoords[8]; // _04
	J2DTexMtx* mTexMtxes[8];   // _24
};

struct J2DTexGenBlock : _J2DTexGenBlockParent {
	virtual ~J2DTexGenBlock(); // _08

	void initialize();
	void setGX();
	void setTexMtx(u32, J2DTexMtx&);
	void getTexMtx(u32, J2DTexMtx&);

	u32 getTexGenNum() const { return mTexGenNum; }

	// _44 VTBL
};

#endif
