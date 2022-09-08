#ifndef _JSYSTEM_J3D_J3DMATERIAL_H
#define _JSYSTEM_J3D_J3DMATERIAL_H

#include "JSystem/J3D/J3DTypes.h"
#include "JSystem/J3D/J3DTexture.h"
#include "types.h"

struct J3DAnmColor;
struct J3DAnmTevRegKey;
struct J3DAnmTextureSRTKey;
struct J3DColorBlock;
struct J3DDisplayListObj;
struct J3DIndBlock;
struct J3DJoint;
struct J3DMaterialAnm;
struct J3DPEBlock;
struct J3DShape;
struct J3DTevBlock;
struct J3DTevColorAnm;
struct J3DTexGenBlock;
struct J3DTexMtxAnm;
struct J3DTexture;
struct JUTNameTab;

/**
 * @size{0x4C}
 */
struct J3DMaterial {
	J3DMaterial();
	~J3DMaterial();

	virtual void calc(const float (*)[4]);           // _00
	virtual void calcDiffTexMtx(const float (*)[4]); // _04
	virtual void makeDisplayList();                  // _08
	virtual void makeSharedDisplayList();            // _0C
	virtual void load();                             // _10
	virtual void loadSharedDL();                     // _14
	virtual void patch();                            // _18
	virtual void diff(u32);                          // _1C
	virtual void reset();                            // _20
	virtual void change();                           // _24

	void calcCurrentMtx();
	u32 calcSizePEBlock(J3DModelLoaderFlags, u32);
	u32 calcSizeTevBlock(int);
	u32 calcSizeTexGenBlock(J3DModelLoaderFlags);
	u32 countDLSize();
	J3DColorBlock* createColorBlock(u32);
	J3DIndBlock* createIndBlock(int);
	J3DPEBlock* createPEBlock(u32, u32);
	J3DTevBlock* createTevBlock(int);
	J3DTexGenBlock* createTexGenBlock(u32);
	void initialize();
	int newSharedDisplayList(u32);
	int newSingleSharedDisplayList(u32);
	void setCurrentMtx();

	// VTBL _00
	J3DMaterial* _04;              // _04
	J3DShape* m_shape;             // _08
	J3DJoint* m_joint;             // _0C
	u32 _10;                       // _10
	short _14;                     // _14
	u32 _18;                       // _18
	u8 _1C[4];                     // _1C
	J3DDisplayListObj* _20;        // _20
	J3DColorBlock* m_colorBlock;   // _24
	J3DTexGenBlock* m_texGenBlock; // _28
	J3DTevBlock* m_tevBlock;       // _2C
	J3DIndBlock* m_indBlock;       // _30
	J3DPEBlock* m_peBlock;         // _34
	J3DMaterial* _38;              // _38
	J3DMaterialAnm* m_anm;         // _3C
	u32 _40;                       // _40
	u32 _44;                       // _44
	J3DDisplayListObj* _48;        // _48
};

/**
 * m_*Block are all the *Null variants of their respective types.
 * @size{0x4C}
 */
struct J3DLockedMaterial : public J3DMaterial {
	virtual void calc(const float (*)[4]); // _00
	virtual void makeDisplayList();        // _08
	virtual void makeSharedDisplayList();  // _0C
	virtual void load();                   // _10
	virtual void loadSharedDL();           // _14
	virtual void patch();                  // _18
	virtual void diff(u32);                // _1C
	virtual void reset();                  // _20
	virtual void change();                 // _24

	void initialize();
};

/**
 * m_texGenBlock and m_tevBlock are the *Patched variants of their respective
 * types.
 * @size{0x4C}
 */
struct J3DPatchedMaterial : public J3DMaterial {
	virtual void makeDisplayList();       // _08
	virtual void makeSharedDisplayList(); // _0C
	virtual void load();                  // _10
	virtual void loadSharedDL();          // _14
	virtual void reset();                 // _20
	virtual void change();                // _24

	void initialize();
};

/**
 * @size{0x20}
 */
struct J3DMaterialTable {
	J3DMaterialTable();

	virtual ~J3DMaterialTable(); // _00

	// virtual void _04(); // _04

	void clear();

	void allocTexMtxAnimator(J3DAnmTextureSRTKey*, J3DTexMtxAnm**);
	void entryTexMtxAnimator(J3DAnmTextureSRTKey*);
	void removeTexMtxAnimator(J3DAnmTextureSRTKey*);

	void allocTevRegAnimator(J3DAnmTevRegKey*, J3DTevColorAnm**);
	void entryTevRegAnimator(J3DAnmTevRegKey*);
	void removeTevRegAnimator(J3DAnmTevRegKey*);

	void entryMatColorAnimator(J3DAnmColor*);

	// VTBL _00
	u16 m_count1;               // _04
	u16 m_count2;               // _06
	J3DMaterial** m_materials1; // _08
	JUTNameTab* _0C;            // _0C
	J3DMaterial* m_materials2;  // _10
	J3DTexture* m_texture;      // _14
	JUTNameTab* _18;            // _18
	u16 _1C;                    // _1C
};

#endif
