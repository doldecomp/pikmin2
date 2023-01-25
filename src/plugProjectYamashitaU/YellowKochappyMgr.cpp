#include "Game/Entities/YellowKochappy.h"
#include "LoadResource.h"

namespace Game {
namespace YellowKochappy {

namespace {
static const char* cKochappyChangeTexName = "/enemy/data/YellowKochappy/kochappy_body_s3tc.2.bti";
} // namespace

/*
 * --INFO--
 * Address:	8012D5E4
 * Size:	000050
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : KochappyBase::Mgr(objLimit, modelType)
{
	mName = "���R�`���b�s�[�}�l�[�W��"; // blue kochappy manager
}

/*
 * --INFO--
 * Address:	8012D634
 * Size:	000048
 */
void Mgr::doAlloc() { init(new KochappyBase::Parms); }

/*
 * --INFO--
 * Address:	8012D67C
 * Size:	000048
 */
void Mgr::loadTexData()
{
	LoadResource::ArgAramOnly loadArg(cKochappyChangeTexName);
	LoadResource::Node* resource = gLoadResourceMgr->load(loadArg);
	mChangeTexture               = static_cast<ResTIMG*>(resource->mFile);
}

} // namespace YellowKochappy
} // namespace Game
