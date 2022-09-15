#ifndef _J2DANMTEXTURESRTKEY_H
#define _J2DANMTEXTURESRTKEY_H

/*
    __vt__19J2DAnmTextureSRTKey:
    .4byte 0
    .4byte 0
    .4byte __dt__19J2DAnmTextureSRTKeyFv
    .4byte searchUpdateMaterialID__19J2DAnmTextureSRTKeyFP9J2DScreen
*/

struct J2DAnmTextureSRTKey {
	virtual ~J2DAnmTextureSRTKey();                  // _08 (weak)
	virtual void searchUpdateMaterialID(J2DScreen*); // _0C

	void calcTransform(float, unsigned short, J3DTextureSRTInfo*) const;
};

#endif
