#include "Game/Entities/Kurage.h"

namespace Game {
namespace Kurage {

static const char kurageMgrName[] = "246-KurageMgr";

/*
 * --INFO--
 * Address:	802AD104
 * Size:	000050
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBase(objLimit, modelType)
{
	mName = "�N���Q�h�b�N���}�l�[�W��"; // jellyfish manager
}

/*
 * --INFO--
 * Address:	802AD154
 * Size:	000048
 */
void Mgr::doAlloc() { init(new Parms); }

/*
 * --INFO--
 * Address:	802AD420
 * Size:	000060
 */
void Mgr::createObj(int count) { mObj = new Obj[count]; }

/*
 * --INFO--
 * Address:	802AD53C
 * Size:	000010
 */
EnemyBase* Mgr::getEnemy(int index) { return &mObj[index]; }

/*
 * --INFO--
 * Address:	802AD54C
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

} // namespace Kurage
} // namespace Game
