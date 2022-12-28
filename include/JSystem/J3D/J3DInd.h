#ifndef _JSYSTEM_J3D_J3DIND_H
#define _JSYSTEM_J3D_J3DIND_H

#include "Dolphin/gx.h"
#include "JSystem/J3D/J3DTypes.h"
#include "types.h"

struct J3DIndTexCoordScale {
	J3DIndTexCoordScale();
	~J3DIndTexCoordScale() { }

	u8 _00;    // _00
	u8 _01;    // _01
	u8 _02[2]; // _02
};

struct J3DIndTexMtxInfo {
	f32 _00;
	f32 _04;
	f32 _08;
	f32 _0C;
	f32 _10;
	f32 _14;
	u8 _18;
};

extern const J3DIndTexMtxInfo j3dDefaultIndTexMtxInfo;

/**
 * @size{0x1C}
 */
struct J3DIndTexMtx {
	J3DIndTexMtx()
	    : _00(j3dDefaultIndTexMtxInfo._00)
	    , _04(j3dDefaultIndTexMtxInfo._04)
	    , _08(j3dDefaultIndTexMtxInfo._08)
	    , _0C(j3dDefaultIndTexMtxInfo._0C)
	    , _10(j3dDefaultIndTexMtxInfo._10)
	    , _14(j3dDefaultIndTexMtxInfo._14)
	    , _18(j3dDefaultIndTexMtxInfo._18)
	{
	}

	/** @fabricated */
	J3DIndTexMtx(const J3DIndTexMtxInfo& info)
	    : _00(info._00)
	    , _04(info._04)
	    , _08(info._08)
	    , _0C(info._0C)
	    , _10(info._10)
	    , _14(info._14)
	    , _18(info._18)
	{
	}

	~J3DIndTexMtx() { }

	f32 _00;
	f32 _04;
	f32 _08;
	f32 _0C;
	f32 _10;
	f32 _14;
	u8 _18;
};

/** @fabricated */
struct J3DIndTexOrderInfo {
	u8 m_texCoordID; // _00
	u8 m_texMapID;   // _01
	u8 _02;          // _02
	u8 _03;          // _03
};

extern const J3DIndTexOrderInfo j3dDefaultIndTexOrderNull;
// extern const struct J3DIndTexOrder j3dDefaultIndTexOrderNull;

/**
 * @size{0x4}
 */
struct J3DIndTexOrder {
	J3DIndTexOrder()
	    : m_texCoordID(j3dDefaultIndTexOrderNull.m_texCoordID)
	    , m_texMapID(j3dDefaultIndTexOrderNull.m_texMapID)
	{
	}

	/** @fabricated */
	inline J3DIndTexOrder(const J3DIndTexOrderInfo& info)
	    : m_texCoordID(info.m_texCoordID)
	    , m_texMapID(info.m_texMapID)
	    , _02(info._02)
	    , _03(info._03)
	{
	}

	// /** @fabricated */
	// inline J3DIndTexOrder(_GXTexCoordID coordID, GXTexMapID mapID)
	//     : m_texCoordID(coordID)
	//     , m_texMapID(mapID)
	// {
	// }

	// /** @fabricated */
	// inline J3DIndTexOrder(u8 coordID, u8 mapID, u8 p3, u8 p4)
	//     : m_texCoordID(coordID)
	//     , m_texMapID(mapID)
	//     , _02(p3)
	//     , _03(p4)
	// {
	// }

	u8 m_texCoordID; // _00
	u8 m_texMapID;   // _01
	u8 _02;          // _02
	u8 _03;          // _03
};

struct J3DIndBlock {
	virtual void reset(J3DIndBlock*);                                            // _08 (weak)
	virtual void diff(unsigned long) = 0;                                        // _0C
	virtual void load()              = 0;                                        // _10
	virtual u32 countDLSize();                                                   // _14 (weak)
	virtual JBlockType getType() = 0;                                            // _18
	virtual void setIndTexStageNum(unsigned char);                               // _1C (weak)
	virtual u8 getIndTexStageNum() const;                                        // _20 (weak)
	virtual void setIndTexOrder(unsigned long, J3DIndTexOrder);                  // _24 (weak)
	virtual void setIndTexOrder(unsigned long, const J3DIndTexOrder*);           // _28 (weak)
	virtual J3DIndTexOrder* getIndTexOrder(unsigned long);                       // _2C (weak)
	virtual void setIndTexMtx(unsigned long, const J3DIndTexMtx*);               // _30 (weak)
	virtual void setIndTexMtx(unsigned long, J3DIndTexMtx);                      // _34 (weak)
	virtual J3DIndTexMtx* getIndTexMtx(unsigned long);                           // _38 (weak)
	virtual void setIndTexCoordScale(unsigned long, const J3DIndTexCoordScale*); // _3C (weak)
	virtual void setIndTexCoordScale(unsigned long, J3DIndTexCoordScale);        // _40 (weak)
	virtual J3DIndTexCoordScale* getIndTexCoordScale(unsigned long);             // _44 (weak)
	virtual ~J3DIndBlock() { }                                                   // _48 (weak)
};

struct J3DIndBlockFull : public J3DIndBlock {
	inline J3DIndBlockFull() { initialize(); }

	virtual void reset(J3DIndBlock*);                                            // _08
	virtual void diff(unsigned long);                                            // _0C
	virtual void load();                                                         // _10
	virtual u32 countDLSize();                                                   // _14
	virtual JBlockType getType();                                                // _18 (weak)
	virtual void setIndTexStageNum(unsigned char);                               // _1C (weak)
	virtual u8 getIndTexStageNum() const;                                        // _20 (weak)
	virtual void setIndTexOrder(unsigned long, J3DIndTexOrder);                  // _24 (weak)
	virtual void setIndTexOrder(unsigned long, const J3DIndTexOrder*);           // _28 (weak)
	virtual J3DIndTexOrder* getIndTexOrder(unsigned long);                       // _2C (weak)
	virtual void setIndTexMtx(unsigned long, const J3DIndTexMtx*);               // _30 (weak)
	virtual void setIndTexMtx(unsigned long, J3DIndTexMtx);                      // _34 (weak)
	virtual J3DIndTexMtx* getIndTexMtx(unsigned long);                           // _38 (weak)
	virtual void setIndTexCoordScale(unsigned long, const J3DIndTexCoordScale*); // _3C (weak)
	virtual void setIndTexCoordScale(unsigned long, J3DIndTexCoordScale);        // _40 (weak)
	virtual J3DIndTexCoordScale* getIndTexCoordScale(unsigned long);             // _44 (weak)
	virtual ~J3DIndBlockFull();                                                  // _48 (weak)

	void initialize();

	u8 m_indTexStageNum;        // _04
	J3DIndTexOrder m_orders[4]; // _05
	u32 : 0;
	J3DIndTexMtx m_texMtxs[3];            // _18
	J3DIndTexCoordScale m_coordScales[4]; // _6C
};

struct J3DIndBlockNull : public J3DIndBlock {
	virtual void reset(J3DIndBlock*) { }                 // _08 (weak)
	virtual void diff(unsigned long) { }                 // _0C (weak)
	virtual void load() { }                              // _10 (weak)
	virtual JBlockType getType() { return JBT_IndNull; } // _18 (weak)
	virtual ~J3DIndBlockNull() { }                       // _48 (weak)
};

#endif
