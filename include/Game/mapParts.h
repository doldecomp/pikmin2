#ifndef _GAME_MAPPARTS_H
#define _GAME_MAPPARTS_H

#include "BoundBox.h"
#include "CNode.h"
#include "Game/cellPyramid.h"
#include "Dolphin/mtx.h"
#include "Game/pathfinder.h"
#include "Game/routeMgr.h"
#include "Game/MapMgr.h"
#include "Game/seaMgr.h"
#include "MapCollision.h"
#include "Matrixf.h"
#include "ObjectMgr.h"
#include "Sys/Cylinder.h"
#include "Sys/Sphere.h"
#include "types.h"
#include "Vector3.h"
#include "Game/Cave/Info.h"
#include "Game/Cave/ObjectLayout.h"
#include "Game/Entities/BlackMan.h"

struct Graphics;
struct J3DModelData;
struct JUTTexture;
struct ResTIMG;

namespace Sys {
struct MatLoopAnimator;
struct MatTexAnimation;
} // namespace Sys

namespace SysShape {
struct Model;
} // namespace SysShape

namespace Game {
namespace Cave {
struct EditMapUnit;
} // namespace Cave

// Size: 0x24
struct DoorLink : public CNode {
	DoorLink()
	{
		mDistance  = 0.0f;
		mTekiFlags = 1;
	}

	virtual ~DoorLink(); // _08 (weak)

	void read(Stream&);
	void write(Stream&);

	f32 mDistance; // _18
	u32 mDoorID;   // _1C
	u8 mTekiFlags; // _20
};

// Size: 0x50
struct Door : public CNode {
	Door()
	{
		mLinkCount = 0;
		mDir       = 0;
		mOffs      = 0;
	}

	virtual ~Door(); // _08 (weak)

	DoorLink* getLink(int);
	void read(Stream&);
	void write(Stream&);

	inline int getLinkCount() { return mLinkCount; }

	u32 mIndex;         // _18
	int mLinkCount;     // _1C
	DoorLink mRootLink; // _20
	u32 mDir;           // _44
	u32 mOffs;          // _48
	u32 mWpIndex;       // _4C
};

// Size: 0x10
struct RoomDoorInfo {
	RoomDoorInfo();
};

struct RoomLink : public CNode {
	virtual ~RoomLink(); // _08 (weak)
};

// Size: 0xF0
struct MapUnit {
	MapUnit();

	virtual void constructor();                 // _08 (weak)
	virtual void doAnimation();                 // _0C (weak)
	virtual void doEntry();                     // _10 (weak)
	virtual void doSetView(int viewportNumber); // _14 (weak)
	virtual void doViewCalc();                  // _18 (weak)
	virtual void doSimulation(f32);             // _1C (weak)
	virtual void doDirectDraw(Graphics& gfx);   // _20 (weak)

	void load(Stream&);
	void save(Stream&);
	void setupSizeInfo();

	short _04;                         // _04
	char* mName;                       // _08
	J3DModelData* mModelData;          // _0C
	MapCollision mCollision;           // _10
	JUTTexture* mTexture;              // _2C
	ResTIMG* mImgResource;             // _30
	SeaMgr mSeaMgr;                    // _34
	BoundBox mBoundingBox;             // _7C
	Vector2<short> mCellSize;          // _94
	u8 _98[0x10];                      // _98
	u8 _A8;                            // _A8
	EditorRouteMgr mRouteMgr;          // _AC
	int mAnimationCount;               // _E8
	Sys::MatTexAnimation* mAnimations; // _EC
};

struct PartsView : public CNode {
	PartsView();
	PartsView(MapUnit*, u8*);

	virtual ~PartsView() { }                    // _08 (weak)
	virtual void constructor() { }              // _10 (weak)
	virtual void doAnimation();                 // _14
	virtual void doEntry();                     // _18
	virtual void doSetView(int viewportNumber); // _1C
	virtual void doViewCalc();                  // _20
	virtual void doSimulation(f32) { }          // _24 (weak)
	virtual void doDirectDraw(Graphics& gfx);   // _28

	void getHalfX();
	void getOffset();
	void read(Stream&);
	void write(Stream&);

	MapUnit* mMapUnit;       // _018
	SysShape::Model* mModel; // _01C
	Mtx _20;                 // _020
	f32 _50;                 // _050
	f32 _54;                 // _054
	u32 _58;                 // _058
	u32 _5C;                 // _05C
	u32 _60;                 // _060
	u8 _64[8];               // _064

	// 0=dead end, 1=room, 2=hallway ??? NOT SURE
	s16 mUnitKind;               // _06C
	BitFlag<u16> _6E;            // _06E
	EditorRouteMgr mRouteMgr;    // _070
	AStarContext mAStarContext;  // _0AC
	AStarPathfinder mPathFinder; // _110
	int mDoorCount;              // _114
	Door mDoor;                  // _118
	Cave::BaseGen* mBaseGen;     // _168
};

struct MapUnitInterface : public PartsView {
	MapUnitInterface();

	virtual ~MapUnitInterface(); // _08 (weak)

	inline int getDoorCount() { return mDoorCount; }

	Door* getDoor(int);
	void getCellSize(int&, int&);
};

struct MapUnitMgr : public NodeObjectMgr<MapUnit> {
	MapUnitMgr();

	virtual ~MapUnitMgr();       // _08 (weak)
	virtual MapUnit* getAt(int); // _24

	void findMapUnit(char*);
	void load(char*);
	void loadShape(char*);
	void makeUnit(MapUnit*, char*);
	void testConstruct();
};

// Size: 0x1A0
struct MapRoom : public CellObject {
	MapRoom();

	virtual Vector3f getPosition();               // _08 (weak)
	virtual void getBoundingSphere(Sys::Sphere&); // _10 (weak)
	virtual bool collisionUpdatable();            // _14 (weak)
	virtual char* getTypeName();                  // _24 (weak)
	virtual u16 getObjType();                     // _28 (weak)
	virtual void constructor();                   // _2C (weak)
	virtual void doAnimation();                   // _30
	virtual void doEntry();                       // _34
	virtual void doSetView(int);                  // _38
	virtual void doViewCalc();                    // _3C
	virtual void doSimulation(f32);               // _40
	virtual void doDirectDraw(Graphics&);         // _44

	void placeObjects(Cave::FloorInfo*, bool);

	// _00     = VTBL
	// _00-_B8 = CellObject
	MapCollision* mCollision;              // _0B8
	u8 _0BC;                               // _0BC
	MapUnitInterface* mInterface;          // _0C0
	Cave::ObjectLayout* mObjectLayoutInfo; // _0C4
	u8 _0C8[4];                            // _0C8
	Sys::MatLoopAnimator* mAnimators;      // _0CC
	int mDoorNum;                          // _0D0
	RoomDoorInfo* mDoorInfos;              // _0D4
	Matrixf _0D8;                          // _0D8
	Matrixf _108;                          // _108
	MapUnit* mUnit;                        // _138
	SysShape::Model* mModel;               // _13C
	Sys::Sphere mBoundingSphere;           // _140
	Sys::Sphere _150;                      // _150
	Sys::Cylinder _160;                    // _160
	RoomLink* mLink;                       // _180
	s16 _184;                              // _184
	u16 mUnitKind;                         // _186
	u8 _188[2];                            // _188
	int* mWpIndices;                       // _18C
	Sys::Sphere _190;                      // _190
};

struct RoomMapMgr : public MapMgr {
	RoomMapMgr(Cave::CaveInfo*);

	virtual bool hasHiddenCollision();                        // _08
	virtual void constraintBoundBox(Sys::Sphere&);            // _0C
	virtual void getStartPosition(Vector3f&, int);            // _10 (weak)
	virtual void getDemoMatrix();                             // _14 (weak)
	virtual void getBoundBox2d(BoundBox2d&);                  // _18
	virtual void getBoundBox(BoundBox&);                      // _1C
	virtual void findRayIntersection(Sys::RayIntersectInfo&); // _20
	virtual void traceMove(MoveInfo&, f32);                   // _24
	virtual f32 getMinY(Vector3f&);                           // _28
	virtual void getCurrTri(CurrTriInfo&);                    // _2C
	virtual void createTriangles(Sys::CreateTriangleArg&);    // _30
	virtual void setupJUTTextures();                          // _34
	virtual void drawCollision(Graphics&, Sys::Sphere&);      // _44
	virtual void doSimulation(f32);                           // _48 (weak)
	virtual void doDirectDraw(Graphics&);                     // _4C (weak)
	virtual void doAnimation();                               // _50 (weak)
	virtual void doEntry();                                   // _54 (weak)
	virtual void doSetView(int);                              // _58 (weak)
	virtual void doViewCalc();                                // _5C (weak)
	virtual void traceMove_new(MoveInfo&, f32);               // _60
	virtual void traceMove_original(MoveInfo&, f32);          // _64

	void getMapRoom(s16);
	void createRandomMap(int, Cave::EditMapUnit*);
	void completeUnitData();
	void useUnit(char*);
	JUTTexture* getTexture(char*);
	void allocRooms(int);
	void makeRoom(char*, f32, f32, int, int, RoomLink*, ObjectLayoutInfo*);
	void placeObjects();
	void entryToMapRoomCellMgr();
	void findRoomIndex(Sys::Sphere&);
	void createGlobalCollision();
	void makeOneRoom(f32, f32, f32, char*, s16, RoomLink*, ObjectLayoutInfo*);
	void deleteTemp();
	void getMUI(MapUnit*);
	void nishimuraCreateRandomMap(MapUnitInterface*, int, Cave::FloorInfo*, bool, Cave::EditMapUnit*);
	void nishimuraPlaceRooms();
	void nishimuraSetTexture();

	// _00     = GenericObjectMgr
	// _04     = VTBL
	// _00-_24 = MapMgr
	SysShape::Model* _24;                // _24, mModelOrCaveVRBoxOrBothMaybe
	Cave::CaveInfo* mCaveInfo;           // _28
	Cave::FloorInfo* mFloorInfo;         // _2C
	int mSublevel;                       // _30
	MapCollision* mMapCollision;         // _34
	u32 _38;                             // _38
	void* _3C;                           // _3C
	u8 _40[0x60];                        // _40, triangle?
	int mCount;                          // _A0
	void* _A4;                           // _A4
	MapUnitMgr* mMapUnitMgr;             // _A8
	u8 _AC[0x30];                        // _AC, mono?
	BoundBox mBoundbox;                  // _DC
	uint mMapUnitInterfaceCount;         // _F4
	MapUnitInterface* mMapUnitInterface; // _F8
	Vector3f mStartPositions[2];         // _FC
	Game::BlackMan::Obj* mBlackMan;      // _114
	u32* m_118;                          // _118 TODO: rename
	u32 m_11C;                           // _11C TODO: rename
};

struct CaveVRBox {
};
} // namespace Game

#endif
