#include "Game/Entities/SnakeWhole.h"

namespace Game {
namespace SnakeWhole {

static const char snakeWholeMgrName[] = "246-SnakeWholeMgr";

/*
 * --INFO--
 * Address:	802CE2DC
 * Size:	000050
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBase(objLimit, modelType)
{
	mName = "�w�r�K���X�S�g�}�l�[�W��"; // snake crow whole body manager
}

/*
 * --INFO--
 * Address:	802CE32C
 * Size:	000048
 */
void Mgr::doAlloc() { init(new Parms); }

/*
 * --INFO--
 * Address:	802CE4C8
 * Size:	000060
 */
void Mgr::createObj(int count) { mObj = new Obj[count]; }

/*
 * --INFO--
 * Address:	802CE5E4
 * Size:	000010
 */
EnemyBase* Mgr::getEnemy(int index) { return &mObj[index]; }

/*
 * --INFO--
 * Address:	802CE5F4
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

} // namespace SnakeWhole
} // namespace Game
