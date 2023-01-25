#include "Game/Entities/Fart.h"
#include "LoadResource.h"

namespace Game {
namespace Fart {

namespace {
static const char* cKoganeChangeTexName = "/enemy/data/Fart/babakogane_s3tc.bti";
} // namespace

/*
 * --INFO--
 * Address:	802850F0
 * Size:	000050
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : Kogane::Mgr(objLimit, modelType)
{
	mName = "�o�o�R�K�l�}�l�[�W��"; // baba kogane manager
}

/*
 * --INFO--
 * Address:	80285140
 * Size:	000048
 */
void Mgr::doAlloc() { init(new Kogane::Parms); }

/*
 * --INFO--
 * Address:	80285188
 * Size:	000060
 */
void Mgr::createObj(int count) { mObj = new Obj[count]; }

/*
 * --INFO--
 * Address:	802852D8
 * Size:	000010
 */
EnemyBase* Mgr::getEnemy(int index) { return &mObj[index]; }

/*
 * --INFO--
 * Address:	802852E8
 * Size:	000080
 */
void Mgr::loadTexData()
{
	mChangeTexture = nullptr;
	LoadResource::Arg loadArg(cKoganeChangeTexName);
	LoadResource::Node* resource = gLoadResourceMgr->load(loadArg);
	if (resource) {
		mChangeTexture = static_cast<ResTIMG*>(resource->mFile);
	}
	P2ASSERTLINE(83, mChangeTexture);
}

} // namespace Fart
} // namespace Game
