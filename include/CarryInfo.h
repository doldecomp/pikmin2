#ifndef _CARRYINFO_H
#define _CARRYINFO_H

#include "CNode.h"
#include "InfoList.h"
#include "JSystem/JUT/JUTTexture.h"
#include "types.h"
#include "Vector3.h"

#define MAX_POKOINFO 5

struct CarryInfoList;

enum cCarryInfoState {
	CINFO_Appear = 0,
	CINFO_1      = 1,
	CINFO_Hidden = 2,
};

struct CarryInfo {
	void disappear();
	void draw(struct Graphics&, struct CarryInfoParam&);
	f32 drawNumber(Graphics&, f32, f32, int, struct Color4&, f32);
	void drawNumberPrim(Graphics&, f32, f32, int, Color4&, f32);
	void update(const CarryInfoParam&);

	f32 mGrowRate; // _00
	f32 mYOffset;  // _04
	f32 mScale;    // _08
	u8 mHidden;    // _0C
	u8 mAlpha;     // _0D
	u8 mCounter;   // _0E
};

struct CarryInfoParam {
	u32 mUseType;         // _00, 1 means color by scale, 0 means color by coded table
	Vector3f mPosition;   // _04
	f32 mYOffsetMax;      // _10
	u8 _14;               // _14
	u8 mColor;            // _15
	short mValue1;        // _16
	short mValue2;        // _18
	BOOL mIsTopFirst;     // _1C, 0 means value1 on bottom, 1 means value2 on bottom
	int mValue;           // _20
	CarryInfo mCarryInfo; // _24
};

struct CarryInfoOwner {
	virtual void getCarryInfoParam(CarryInfoParam&) = 0; // _08

	// _00 VTBL
};

/**
 * @size{0x34}
 */
struct PokoInfoOwner : public CarryInfoOwner, public CNode {
	PokoInfoOwner();

	// vtable 1 (CarryInfoOwner)
	virtual void getCarryInfoParam(CarryInfoParam&); // _08
	// vtable 2 (CNode)
	virtual ~PokoInfoOwner(); // _1C (thunked at _14) (weak)

	f32 mTimer;           // _1C
	CarryInfoList* mList; // _20
	Vector3f mPosition;   // _24
	int mValue;           // _30
};

/**
 * @size(0x58)
 */
struct CarryInfoList : public InfoListBase<CarryInfoOwner, CarryInfoList> {
	virtual ~CarryInfoList();     // _08 (weak)
	virtual void init();          // _0C
	virtual void update();        // _10
	virtual void draw(Graphics&); // _14
	virtual bool isFinish();      // _18 (weak)

	CarryInfoParam mParam; // _24
};

/**
 * @size(0xEC)
 */
struct CarryInfoMgr : public InfoMgr<CarryInfoOwner, CarryInfoList> {
	CarryInfoMgr(int);

	virtual ~CarryInfoMgr();                         // _08
	virtual void loadResource();                     // _0C
	virtual void update();                           // _10
	virtual void draw(Graphics&);                    // _14
	virtual CarryInfoList* regist(CarryInfoOwner*);  // _18 (weak)
	virtual CarryInfoList* scratch(CarryInfoOwner*); // _1C (weak)

	CarryInfoList* appear(CarryInfoOwner*);
	void appearPoko(const Vector3f&, int);
	void updatePokoInfoOwners();

	JUTTexture* mTexture; // _B8
	CNode mNode1;         // _BC
	CNode mPoko_node;     // _D4
};

extern CarryInfoMgr* carryInfoMgr;

#endif
