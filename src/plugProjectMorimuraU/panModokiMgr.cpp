#include "Game/Entities/PanModoki.h"
#include "Game/Entities/OoPanModoki.h"

namespace Game {

static const char panModokiMgrName[] = "panModokiMgr";

namespace PanModoki {

/*
 * --INFO--
 * Address:	8034E9C0
 * Size:	000050
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBase(objLimit, modelType)
{
	mName = "�p�����h�L�}�l�[�W��"; // bread manager
}

/*
 * --INFO--
 * Address:	8034EA10
 * Size:	000048
 */
void Mgr::doAlloc() { init(new PanModokiBase::Parms); }

/*
 * --INFO--
 * Address:	8034ED70
 * Size:	000020
 */
EnemyBase* Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

} // namespace PanModoki

namespace OoPanModoki {
/*
 * --INFO--
 * Address:	8034ED90
 * Size:	000050
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBase(objLimit, modelType)
{
	mName = "��p�����h�L�}�l�[�W��"; // big bread manager
}

/*
 * --INFO--
 * Address:	8034EDE0
 * Size:	000048
 */
void Mgr::doAlloc() { init(new PanModokiBase::Parms); }

/*
 * --INFO--
 * Address:	8034EE28
 * Size:	000020
 */
EnemyBase* Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/*
 * --INFO--
 * Address:	8034EE48
 * Size:	00002C
 */
J3DModelData* Mgr::doLoadBmd(void* filename) { return J3DModelLoaderDataBase::load(filename, 0x00240030); }

/*
 * --INFO--
 * Address:	8034EE74
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
} // namespace OoPanModoki

} // namespace Game
