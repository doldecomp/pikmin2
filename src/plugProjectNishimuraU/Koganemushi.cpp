#include "Game/Entities/Koganemushi.h"
#include "Game/Entities/PelletNumber.h"
#include "Game/Entities/ItemHoney.h"
#include "Game/gamePlayData.h"

#include "JSystem/J3D/J3DMaterial.h"
#include "JSystem/J3D/J3DTevBlock.h"
#include "JSystem/JUT/JUTNameTab.h"

namespace Game {
/*
 * --INFO--
 * Address:	8029DD44
 * Size:	000090
 */
Koganemushi::Obj::Obj() { }

/*
 * --INFO--
 * Address:	8029DDD4
 * Size:	0001F0
 */
void Koganemushi::Obj::changeMaterial()
{
	J3DModelData* modelData;
	J3DModel* j3dModel;
	ResTIMG* changeTexture;
	ResTIMG* newTexture;
	J3DTexture* j3dTexture;

	j3dModel      = mModel->mJ3dModel;
	modelData     = j3dModel->mModelData;
	changeTexture = static_cast<Mgr*>(mMgr)->getChangeTexture();

	u16 idx                = modelData->mMaterialTable._0C->getIndex("karada");
	J3DMaterial* karadaMat = modelData->mMaterialTable.mMaterials1[idx];
	karadaMat->mTevBlock->setTevKColor(0, J3DGXColor(0x3C, 0x3C, 0x3C, 0xFF));

	j3dModel->calcMaterial();

	j3dTexture = mModel->mJ3dModel->mModelData->mMaterialTable.mTexture;
	newTexture = j3dTexture->_04;

	changeTexture->copyTo(newTexture);

	j3dTexture->setImageOffset((u32)changeTexture);
	j3dTexture->setPaletteOffset((u32)changeTexture);

	for (u16 i = 0; i < modelData->mMaterialTable.mCount1; i++) {
		J3DMatPacket* packet  = &j3dModel->mMatPackets[i];
		j3dSys.mMatPacket     = packet;
		J3DMaterial* material = modelData->mMaterialTable.mMaterials1[i];
		material->diff(packet->_2C->_34);
	}
}

/*
 * --INFO--
 * Address:	8029DFC4
 * Size:	00011C
 */
void Koganemushi::Obj::createItem()
{
	if (createTreasureItem()) {
		return;
	}

	bool createPelletItem = true;
	u32 initArg           = 0;
	u32 amount            = 0;

	switch (mHitCount) {
	case 0: // initial flip
		if (gameSystem && gameSystem->mIsInCave) {
			createPelletItem = false;
			initArg          = HONEY_Y;
			amount           = 1;
		} else {
			initArg = PELLET_NUMBER_ONE;
			amount  = 1;
		}

		break;
	case 1: // second flip
		createPelletItem = false;
		initArg          = HONEY_Y;
		amount           = 2;
		break;
	case 2: // third flip
		createPelletItem = false;

		if (playData && playData->isDemoFlag(DEMO_First_Spicy_Spray_Made)) {
			initArg = HONEY_R;
			amount  = 1;
		} else {
			initArg = HONEY_Y;
			amount  = 3;
		}

		mAppearTimer = 12800.0f;
		break;
	default:
		break;
	}

	if (createPelletItem) {
		createPellet(initArg, amount);
	} else {
		createDoping(initArg, amount);
	}

	mHitCount++;
}

/*
 * --INFO--
 * Address:	8029E0E0
 * Size:	000044
 */
void Koganemushi::Obj::createPressSENormal() { getJAIObject()->startSound(PSSE_EN_KOGANE_HIT, 0); }
} // namespace Game
