#include "Game/Entities/DangoMushi.h"
#include "JSystem/JUT/JUTNameTab.h"
#include "Sys/MatBaseAnimation.h"
#include "Dolphin/rand.h"
#include "LoadResource.h"

namespace Game {
namespace DangoMushi {

static const char dangoMushiMgrName[] = "246-DangoMushiMgr";

namespace {
static const char* cMatAnimBrkTexName = "/enemy/data/DangoMushi/dangomushi.brk";
} // namespace

/*
 * --INFO--
 * Address:	802FBD1C
 * Size:	000050
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBase(objLimit, modelType)
{
	mName = "�_���S���V�}�l�[�W��"; // pill bug manager
}

/*
 * --INFO--
 * Address:	802FBD6C
 * Size:	000048
 */
void Mgr::doAlloc() { init(new Parms); }

/*
 * --INFO--
 * Address:	802FBF08
 * Size:	000060
 */
void Mgr::createObj(int count) { mObj = new Obj[count]; }

/*
 * --INFO--
 * Address:	802FC024
 * Size:	000010
 */
EnemyBase* Mgr::getEnemy(int index) { return &mObj[index]; }

/*
 * --INFO--
 * Address:	802FC034
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
 * Address:	802FC09C
 * Size:	0000B4
 */
void Mgr::loadTexData()
{
	SysShape::Model::enableMaterialAnim(mModelData, 0);
	void* brkFile = nullptr;
	LoadResource::Arg loadArgBrk(cMatAnimBrkTexName);
	LoadResource::Node* resourceBrk = gLoadResourceMgr->load(loadArgBrk);
	if (resourceBrk) {
		brkFile = resourceBrk->mFile;
	}
	P2ASSERTLINE(107, brkFile);

	mTevRegAnimation = new Sys::MatTevRegAnimation;
	mTevRegAnimation->attachResource(brkFile, mModelData);
}

/*
 * --INFO--
 * Address:	802FC150
 * Size:	000130
 */
SysShape::Model* Mgr::createModel()
{
	SysShape::Model* model = new SysShape::Model(mModelData, 0x80000, mModelType);
	P2ASSERTLINE(132, model != nullptr);

	for (u16 i = 0; i < mModelData->getMaterialCount1(); i++) {
		const char* name = mModelData->mMaterialTable._0C->getName(i);
		if (!strcmp(name, "body")) {
			model->mJ3dModel->mMatPackets[i]._2C->newDifferedDisplayList(0x01000000);
		}
	}

	// why is this not inlined here but IS inlined in the other mgrs SMH.
	Matrixf mtx;
	PSMTXIdentity(mtx.mMatrix.mtxView);
	PSMTXCopy(mtx.mMatrix.mtxView, j3dSys._00);
	J3DModel* j3dModel = model->mJ3dModel;
	j3dModel->calc();
	j3dModel->calcMaterial();
	j3dModel->makeDL();
	j3dModel->lock();
	return model;
}

} // namespace DangoMushi
} // namespace Game
