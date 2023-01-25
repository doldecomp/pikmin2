#include "Game/Entities/BigTreasure.h"
#include "LoadResource.h"
#include "JSystem/JUT/JUTNameTab.h"
#include "Sys/MatBaseAnimation.h"

namespace Game {
namespace BigTreasure {

static const char bigTreasureMgrName[] = "246-BigTreasureMgr";

namespace {
static const char cMatAnimBtkTexName[] = "/enemy/data/BigTreasure/oootakara_model.btk";
static const char cMatAnimBrkTexName[] = "/enemy/data/BigTreasure/oootakara_model.brk";
} // namespace

/*
 * --INFO--
 * Address:	802D90E4
 * Size:	000110
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBase(objLimit, modelType)
{
	mName = "�I�I�I�^�J���}�l�[�W��"; // big otakara manager

	char* treasures[] = { "elec", "fire", "gas", "water", "loozy" };
	int treasureCount = sizeof(treasures) / sizeof(char*);

	for (int i = 0; i < treasureCount; i++) {
		PelletInitArg initArg;
		if (pelletMgr->makePelletInitArg(initArg, treasures[i])) {
			pelletMgr->setUse(&initArg);
		}
	}
}

/*
 * --INFO--
 * Address:	802D91F4
 * Size:	000048
 */
void Mgr::doAlloc() { init(new Parms); }

/*
 * --INFO--
 * Address:	802DA27C
 * Size:	000060
 */
void Mgr::createObj(int count) { mObj = new Obj[count]; }

/*
 * --INFO--
 * Address:	802DA398
 * Size:	000010
 */
EnemyBase* Mgr::getEnemy(int index) { return &mObj[index]; }

/*
 * --INFO--
 * Address:	802DA3A8
 * Size:	000068
 */
void Mgr::loadModelData()
{
	EnemyMgrBase::loadModelData();
	J3DShape* shape;
	for (u16 j = 0; j < mModelData->getShapeCount(); j++) {
		shape         = mModelData->mShapeTable.mItems[j];
		shape->mFlags = (shape->mFlags & (~0xF000)) | 0x2000;
	}
}

/*
 * --INFO--
 * Address:	802DA410
 * Size:	00007C
 */
SysShape::Model* Mgr::createModel()
{
	SysShape::Model* model = new SysShape::Model(mModelData, 0x40000, mModelType);
	P2ASSERTLINE(120, model);
	return model;
}

} // namespace BigTreasure
} // namespace Game
