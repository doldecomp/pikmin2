#include "types.h"
#include "Game/Entities/Kabuto.h"
#include "LoadResource.h"

namespace Game {
namespace GreenKabuto {

namespace {
char* cKabutoChangeTexName = "/enemy/data/Kabuto/babykabuto_green_s3tc.bti";
}

/*
 * --INFO--
 * Address:	802FF7CC
 * Size:	000050
 */
Mgr::Mgr(int p1, u8 p2)
    : Kabuto::Mgr(p1, p2)
{
	mName = "グリーンカブトマネージャ"; // green beetle manager
}

/*
 * --INFO--
 * Address:	802FF81C
 * Size:	000048
 */
void Mgr::doAlloc() { init(new Kabuto::Parms); }

/*
 * --INFO--
 * Address:	802FF8BC
 * Size:	000060
 */
void Mgr::createObj(int count) { mObj = new Obj[count]; }

/*
 * --INFO--
 * Address:	802FFA08
 * Size:	000010
 */
EnemyBase* Mgr::getEnemy(int idx) { return &mObj[idx]; }

/*
 * --INFO--
 * Address:	802FFA18
 * Size:	000080
 */
void Mgr::loadTexData()
{
	mChangeTexture = nullptr;

	LoadResource::Arg loadArg(cKabutoChangeTexName);
	LoadResource::Node* resource = gLoadResourceMgr->load(loadArg);

	if (resource) {
		mChangeTexture = static_cast<ResTIMG*>(resource->mFile);
	}

	P2ASSERTLINE(82, mChangeTexture != nullptr);
}

} // namespace GreenKabuto
} // namespace Game
