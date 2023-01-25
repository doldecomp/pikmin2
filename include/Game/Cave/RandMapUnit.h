#ifndef _GAME_CAVE_RANDMAPUNIT_H
#define _GAME_CAVE_RANDMAPUNIT_H

#include "types.h"
#include "Game/Cave/ObjectLayout.h"
#include "Game/Cave/Node.h"
#include "Game/Cave/Info.h"
#include "Game/Cave/RandMapMgr.h"

namespace Game {
namespace Cave {
struct EditMapUnit {
	f32 mChanceOfUse; // _00
	u32 _04;          // _04
	u32 _08;          // _08
	u32 _0C;          // _0C
	u32 _10;          // _10
	u32 _14;          // _14
	u32 _18;          // _18
	int _1C;          // _1C
};

struct EnemyNode;
struct GateNode;
struct ItemNode;
struct MapNode;

/**
 * @size{0x34}
 */
struct MapUnitGenerator {
	MapUnitGenerator(MapUnitInterface*, int, FloorInfo*, bool, EditMapUnit*);

	void createEditMapInfo(EditMapUnit*);
	void createMemList(MapUnitInterface*, int);
	bool isCreateList(MapUnitInterface*);
	void memMapListSorting();
	void createMapPartsList();
	void createEnemyList();
	void createCapEnemyList();
	bool isPomGroup(TekiInfo*);
	void createGateList();
	void createItemList();
	void createCaveLevel();

	inline MapNode* getPlacedNodes() { return mPlacedMapNodes; }

	inline MapNode* getStartNode() { return mMapNode->getChild(); }

	inline MapNode* getMapNodeItem(int i) { return &mMapNodeArr[i]; }

	bool mIsFinalFloor;        // _00
	bool mHasEscapeFountain;   // _01
	bool mIsVersusMode;        // _02
	u32 mRandItemType;         // _04
	FloorInfo* mFloorInfo;     // _08
	MapNode* mMapNode;         // _0C
	MapNode* mMapNodeArr;      // _10
	EnemyNode* mEnemyNodeA;    // _14
	EnemyNode* mEnemyNodeB;    // _18
	EnemyNode* mEnemyNodeC;    // _1C
	GateNode* mGateNode;       // _20
	ItemNode* mItemNode;       // _24
	MapNode* mPlacedMapNodes;  // _28
	MapNode* mVisitedMapNodes; // _2C
	EditMapUnit* mEditMapUnit; // _30
};

/**
 * @size{0x4}
 */
struct RandMapChecker {
	RandMapChecker(MapNode*);

	bool isPutOnMap(MapNode*);
	bool isPartsOnParts(MapNode*);
	bool isDoorOnParts(MapNode*);
	bool isPartsOnDoor(MapNode*);
	bool isInnerBox(int, int, int, int, int, int, int, int);

	MapNode* mMapNode; // _00
};

/**
 * @size{0x2C}
 */
struct RandMapUnit {
	RandMapUnit(MapUnitGenerator*);

	void addMap(UnitInfo*, int, int, bool);

	void closeDoorCheck();
	void changeCapToRootLoopMapUnit();
	void changeMapPriority(UnitInfo*);
	void changeTwoToOneMapUnit();
	void createLoopMapNodeCheck();

	void deleteMapNode(MapNode*);

	int getAliveMapIndex(MapNode*);
	MapNode* getCalcDoorIndex(int&, int&, int&, int);
	CardinalDirection getDownToLinkDoorDir(int, int, int);
	MapNode* getFirstMapUnit();
	CardinalDirection getLeftToLinkDoorDir(int, int, int);
	CardinalDirection getLinkDoorDirection(MapNode*, int, MapNode*, int);
	MapNode* getLinkDoorNodeFirst(MapNode*, int, int, int, int&);
	MapNode* getLoopEndMapUnit();
	u32 getLoopMapNode(MapNode**);
	MapNode* getLoopRandMapUnit();
	MapNode* getNormalRandMapUnit();
	int getOpenDoorNum();
	int getPartsKindNum(int);
	MapNode* getRandMapUnit();
	CardinalDirection getRightToLinkDoorDir(int, int, int);
	void getTextureSize(int&, int&);
	CardinalDirection getUpToLinkDoorDir(int, int, int);

	bool isInLinkArea(int, int, int, int, int);
	bool isLoopMapNodeCheck(MapNode*, int);

	void moveCentre();

	void setEditorMapUnit();
	void setFirstMapUnit();
	void setMapUnit();
	void setUnitDoorSorting(int);
	void setUnitKindOrder(MapNode*, int*);
	void setRandomDoorIndex(int*, int);

	int mDoorCount;                      // _00
	int mRoomCount;                      // _04
	f32 mRouteRatio;                     // _08
	bool mMapHasDiameter36;              // _0C
	bool mNeedsLoopMapNodeCheck;         // _0D
	int mCapCandidateCount;              // _10
	f32 mCapMax;                         // _14, between 0.0 and 1.0
	MapNode** mCapCandidateNodes;        // _18
	int* mCapCandidateDoorIndices;       // _1C
	MapUnitGenerator* mMapUnitGenerator; // _20
	int* _24;                            // _24
	RandMapChecker* mChecker;            // _28
};
} // namespace Cave
} // namespace Game

#endif
