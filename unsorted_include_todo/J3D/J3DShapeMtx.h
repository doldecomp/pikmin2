#ifndef _J3DSHAPEMTX_H
#define _J3DSHAPEMTX_H

/*
    __vt__11J3DShapeMtx:
    .4byte 0
    .4byte 0
    .4byte __dt__11J3DShapeMtxFv
    .4byte getType__11J3DShapeMtxCFv
    .4byte getUseMtxNum__11J3DShapeMtxCFv
    .4byte getUseMtxIndex__11J3DShapeMtxCFUs
    .4byte load__11J3DShapeMtxCFv
    .4byte calcNBTScale__11J3DShapeMtxFRC3VecPA3_A3_fPA3_A3_f
    .4byte 0
*/

struct J3DShapeMtx {
	virtual ~J3DShapeMtx();                                                  // _08 (weak)
	virtual void getType() const;                                            // _0C (weak)
	virtual void getUseMtxNum() const;                                       // _10 (weak)
	virtual void getUseMtxIndex(unsigned short) const;                       // _14 (weak)
	virtual void load() const;                                               // _18
	virtual void calcNBTScale(const Vec&, float (*)[3][3], float (*)[3][3]); // _1C
	virtual void _20() = 0;                                                  // _20

	void resetMtxLoadCache();
	void loadMtxIndx_PNGP(int, unsigned short) const;
	void loadMtxIndx_PCPU(int, unsigned short) const;
	void loadMtxIndx_NCPU(int, unsigned short) const;
	void loadMtxIndx_PNCPU(int, unsigned short) const;
};

#endif
