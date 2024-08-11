#include "Game/Entities/ElecOtakara.h"
#include "LoadResource.h"

namespace Game {
namespace ElecOtakara {

namespace {
static const char* cOtakaraChangeTexName = "/enemy/data/ElecOtakara/otakara_yellow_s3tc.bti";
} // namespace

/**
 * @note Address: 0x802B9780
 * @note Size: 0x50
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : OtakaraBase::Mgr(objLimit, modelType)
{
	mName = "電気オタカラムシマネージャ"; // electric otakara manager
}

/**
 * @note Address: 0x802B97D0
 * @note Size: 0x48
 */
void Mgr::doAlloc() { init(new OtakaraBase::Parms); }

/**
 * @note Address: 0x802B9818
 * @note Size: 0x60
 */
void Mgr::createObj(int count) { mObj = new Obj[count]; }

/**
 * @note Address: 0x802B9968
 * @note Size: 0x10
 */
EnemyBase* Mgr::getEnemy(int index) { return &mObj[index]; }

/**
 * @note Address: 0x802B9978
 * @note Size: 0x80
 */
void Mgr::loadTexData()
{
	mChangeTexture = nullptr;
	LoadResource::Arg loadArg(cOtakaraChangeTexName);
	LoadResource::Node* resource = gLoadResourceMgr->load(loadArg);
	if (resource) {
		mChangeTexture = static_cast<ResTIMG*>(resource->mFile);
	}
	P2ASSERTLINE(83, mChangeTexture);
}

} // namespace ElecOtakara
} // namespace Game
