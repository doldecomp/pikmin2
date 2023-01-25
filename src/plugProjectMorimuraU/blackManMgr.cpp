#include "Game/Entities/BlackMan.h"
#include "Game/generalEnemyMgr.h"
#include "LoadResource.h"
#include "JSystem/JUT/JUTNameTab.h"

namespace Game {
namespace BlackMan {

static const char blackManMgrName[] = "blackManMgr";

/*
 * --INFO--
 * Address:	803A53C8
 * Size:	000050
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBase(objLimit, modelType)
{
	mName = "�����l�}�l�[�W��"; // black man manager
}

/*
 * --INFO--
 * Address:	803A5418
 * Size:	000048
 */
void Mgr::doAlloc() { init(new Parms); }

/*
 * --INFO--
 * Address:	803A58B4
 * Size:	000020
 */
EnemyBase* Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/*
 * --INFO--
 * Address:	803A58D4
 * Size:	000094
 */
void Mgr::loadModelData()
{
	EnemyMgrBase::loadModelData();
	J3DShape* shape;
	for (u16 j = 0; j < mModelData->getShapeCount(); j++) {
		shape = mModelData->mShapeTable.mItems[j];
		P2ASSERTLINE(56, shape);
		shape->mFlags = (shape->mFlags & (~0xF000)) | 0x2000;
	}
}

/*
 * --INFO--
 * Address:	803A5968
 * Size:	0000BC
 */
void Mgr::loadTexData()
{
	SysShape::Model::enableMaterialAnim(mModelData, 0);
	void* btkFile = nullptr;
	LoadResource::Arg loadArgBtk("/enemy/data/BlackMan/kagebozu_model.btk");
	LoadResource::Node* resourceBtk = gLoadResourceMgr->load(loadArgBtk);
	if (resourceBtk) {
		btkFile = resourceBtk->mFile;
	}
	P2ASSERTLINE(83, btkFile);

	mTexAnimation = new Sys::MatTexAnimation;
	mTexAnimation->attachResource(btkFile, mModelData);
}

/*
 * --INFO--
 * Address:	803A5A24
 * Size:	00002C
 */
J3DModelData* Mgr::doLoadBmd(void* filename) { return J3DModelLoaderDataBase::load(filename, 0x21300030); }

/*
 * --INFO--
 * Address:	803A5A50
 * Size:	000124
 */
SysShape::Model* Mgr::createModel()
{
	SysShape::Model* model = new SysShape::Model(mModelData, 0x80000, mModelType);
	P2ASSERTLINE(128, model != nullptr);

	for (u16 i = 0; i < mModelData->getMaterialCount1(); i++) {
		const char* name = mModelData->mMaterialTable._0C->getName(i);
		if (!strcmp(name, "kage_mat")) {
			model->mJ3dModel->mMatPackets[i]._2C->newDifferedDisplayList(0x05021200);
		}
	}

	model->updateModel();
	return model;
}

} // namespace BlackMan
} // namespace Game
