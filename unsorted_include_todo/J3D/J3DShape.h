#ifndef _J3DSHAPE_H
#define _J3DSHAPE_H

/*
    __vt__8J3DShape:
    .4byte 0
    .4byte 0
    .4byte draw__8J3DShapeCFv
    .4byte drawFast__8J3DShapeCFv
    .4byte simpleDraw__8J3DShapeCFv
    .4byte simpleDrawCache__8J3DShapeCFv
*/

struct J3DShape {
	virtual void draw() const;            // _08
	virtual void drawFast() const;        // _0C
	virtual void simpleDraw() const;      // _10
	virtual void simpleDrawCache() const; // _14

	void initialize();
	void calcNBTScale(const Vec&, float (*)[3][3], float (*)[3][3]);
	void countBumpMtxNum() const;
	void isSameVcdVatCmd(J3DShape*);
	void makeVtxArrayCmd();
	void makeVcdVatCmd();
	void loadPreDrawSetting() const;
};

#endif
