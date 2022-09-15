#ifndef _J3DANMTEVREGKEY_H
#define _J3DANMTEVREGKEY_H

/*
    __vt__15J3DAnmTevRegKey:
    .4byte 0
    .4byte 0
    .4byte __dt__15J3DAnmTevRegKeyFv
    .4byte getKind__15J3DAnmTevRegKeyCFv
*/

struct J3DAnmTevRegKey {
	virtual ~J3DAnmTevRegKey();   // _08 (weak)
	virtual void getKind() const; // _0C (weak)

	void getTevColorReg(unsigned short, _GXColorS10*) const;
	void getTevKonstReg(unsigned short, _GXColor*) const;
	void searchUpdateMaterialID(J3DModelData*);
};

#endif
