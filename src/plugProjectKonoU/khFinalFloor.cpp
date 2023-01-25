#include "kh/khFinalFloor.h"
#include "JSystem/JKR/JKRFileLoader.h"
#include "JSystem/JKR/JKRArchive.h"
#include "PSSystem/PSSystemIF.h"
#include "nans.h"
#include "Game/GameSystem.h"
#include "og/newScreen/Challenge.h"
#include "Screen/Game2DMgr.h"
#include "JSystem/J2D/J2DAnmLoader.h"

static const char unused[] = "\0\0\0\0\0\0\0\0";

namespace kh {
namespace Screen {

/*
 * --INFO--
 * Address:	80401D38
 * Size:	00021C
 */
void ObjFinalFloor::doCreate(JKRArchive* arc)
{
	if (!getDispMember()->isID(OWNER_KH, MEMBER_FINAL_FLOOR)) {
		JUT_PANICLINE(57, "disp member err");
	}

	if (static_cast<DispFinalFloor*>(getDispMember())->mIs2Player) {
		mScreenNum  = 2;
		mYOffset[0] = msVal.mYOffsetP1;
		mYOffset[1] = msVal.mYOffsetP2;
	}

	for (int i = 0; i < mScreenNum; i++) {
		mScreen[i] = new P2DScreen::Mgr_tuning;
		mScreen[i]->set("final_floor.blo", 0x40000, arc);
		void* file = JKRFileLoader::getGlbResource("final_floor.bck", arc);
		mAnim1[i]  = static_cast<J2DAnmTransform*>(J2DAnmLoaderDataBase::load(file));

		file      = JKRFileLoader::getGlbResource("final_floor.bpk", arc);
		mAnim2[i] = static_cast<J2DAnmColor*>(J2DAnmLoaderDataBase::load(file));

		mScreen[i]->setAnimation(mAnim1[i]);
		mScreen[i]->setAnimation(mAnim2[i]);
	}
	startBGM();
}

/*
 * --INFO--
 * Address:	80401F54
 * Size:	000020
 */
bool ObjFinalFloor::doUpdate() { return updateAnimation(); }

/*
 * --INFO--
 * Address:	80401F74
 * Size:	0000DC
 */
void ObjFinalFloor::doDraw(Graphics& gfx)
{
	gfx.mOrthoGraph.setPort();

	for (int i = 0; i < mScreenNum; i++) {
		mScreen[i]->search('ROOT')->setOffset(0.0f, mYOffset[i]);
		mScreen[i]->draw(gfx, gfx.mOrthoGraph);
	}
}

/*
 * --INFO--
 * Address:	80402050
 * Size:	000038
 */
bool ObjFinalFloor::doUpdateFadein()
{
	PSSystem::spSysIF->playSystemSe(PSSE_FINALLEVEL_COME, &mSound, 0);
	return true;
}

/*
 * --INFO--
 * Address:	80402088
 * Size:	0001F8
 */
bool ObjFinalFloor::doUpdateFadeout()
{
	bool isCh = Game::gameSystem && Game::gameSystem->isChallengeMode();

	if (!getDispMember()->isID(OWNER_KH, MEMBER_FINAL_FLOOR)) {
		JUT_PANICLINE(151, "disp member err");
	}

	DispFinalFloor* disp = static_cast<DispFinalFloor*>(getDispMember());
	if (isCh) {
		if (disp->mIs2Player) {
			og::newScreen::SArgChallenge2P arg(1.5f);
			::Screen::SceneBase* scene = getOwner();
			if (scene->setBackupScene()) {
				scene = getOwner();
				scene->startScene(&arg);
			}
		} else {
			og::newScreen::SArgChallenge1P arg(1.5f);
			::Screen::SceneBase* scene = getOwner();
			if (scene->setBackupScene()) {
				scene = getOwner();
				scene->startScene(&arg);
			}
		}
	} else {
		// story mode cave is the default
		::Screen::SceneBase* scene = getOwner();
		if (scene->setBackupScene()) {
			scene = getOwner();
			scene->startScene(nullptr);
		}
	}
	return true;
}

/*
 * --INFO--
 * Address:	80402280
 * Size:	000034
 */
void ObjFinalFloor::doUpdateFadeoutFinish() { Game::gameSystem->mSection->startMainBgm(); }

/*
 * --INFO--
 * Address:	804022B4
 * Size:	0001C8
 */
bool ObjFinalFloor::updateAnimation()
{
	bool ret = false;
	for (int i = 0; i < mScreenNum; i++) {
		mAnim1[i]->mCurrentFrame = mAnimTime1[i];
		mAnim2[i]->mCurrentFrame = mAnimTime2[i];
		mScreen[i]->animation();

		if (::Screen::gGame2DMgr && ::Screen::gGame2DMgr->mScreenMgr->mInDemo) {
			mScreen[i]->hide();
			if (mAnimTime1[i] > (mAnim1[i]->mMaxFrame * 3) >> 2) {
				mAnimTime1[i] = mAnim1[i]->mMaxFrame;
				mAnimTime2[i] = mAnim2[i]->mMaxFrame;
			} else {
				mAnimTime2[i] = 0.0f;
				mAnimTime1[i] = 0.0f;
			}
		} else {
			mScreen[i]->show();
		}
		mAnimTime1[i] += msVal.mAnimSpeed;
		mAnimTime2[i] += msVal.mAnimSpeed;

		if (mAnimTime1[i] >= mAnim1[i]->mMaxFrame || mAnimTime2[i] >= mAnim2[i]->mMaxFrame) {
			ret = true;
		}
	}
	return ret;
}

/*
 * --INFO--
 * Address:	8040247C
 * Size:	000040
 */
void ObjFinalFloor::stopSound()
{
	if (mSound) {
		mSound->stop(0);
	}
	PSStop2DStream();
}

/*
 * --INFO--
 * Address:	804024BC
 * Size:	00015C
 */
void ObjFinalFloor::restartSound()
{
	if (mAnimTime1[0] <= (mAnim1[0]->mMaxFrame * 3) >> 2) {
		PSSystem::spSysIF->playSystemSe(PSSE_FINALLEVEL_COME, &mSound, 0);
		startBGM();
	}
}

/*
 * --INFO--
 * Address:	80402618
 * Size:	000040
 */
bool SceneFinalFloor::doConfirmSetScene(::Screen::SetSceneArg& arg) { return arg.getSceneType() != SCENE_PAUSE_MENU; }

ObjFinalFloor::StaticValues ObjFinalFloor::msVal;

} // namespace Screen
} // namespace kh
