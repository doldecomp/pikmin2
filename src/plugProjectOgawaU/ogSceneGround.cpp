#include "Morimura/DayEndCount.h"
#include "Morimura/HurryUp.h"
#include "og/newScreen/Ground.h"
#include "Game/GameSystem.h"
#include "PSSystem/PSScene.h"
#include "PSSystem/PSGame.h"
#include "PSM/Scene.h"

namespace og {
namespace newScreen {

bool sGameFlag_MainBgm_Evening;

/*
 * --INFO--
 * Address:	8030DA00
 * Size:	00000C
 */
void initGround() { sGameFlag_MainBgm_Evening = false; }

/*
 * __ct
 * --INFO--
 * Address:	8030DA0C
 * Size:	000054
 */
Ground::Ground()
{
	mDoStartCountdown        = false;
	mDoStartSunsetBgm        = false;
	mDoStartFadeInSunsetBgm  = false;
	mDoStartFadeOutMainBgm   = false;
	mDoStartFadeOutSunsetBgm = false;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000074
 */
Ground::~Ground() { }

/*
 * --INFO--
 * Address:	8030DA60
 * Size:	000004
 */
void Ground::doUserCallBackFunc(Resource::MgrCommand*) { }

/*
 * --INFO--
 * Address:	8030DA64
 * Size:	0000C0
 */
void Ground::doCreateObj(JKRArchive* archive)
{
	::Screen::ObjBase* obj = new ObjGround("ground screen");
	registObj(obj, archive);
	obj = new Morimura::THurryUp2D;
	registObj(obj, archive);
	obj = new Morimura::TDayEndCount;
	registObj(obj, archive);
	setColorBG(0, 0, 0, 0);
}

/*
 * --INFO--
 * Address:	8030DB24
 * Size:	00004C
 */
bool Ground::doStart(::Screen::StartSceneArg* arg)
{
	searchObj("ground screen")->start(arg);
	return true;
}

/*
 * --INFO--
 * Address:	8030DB70
 * Size:	000310
 */
void Ground::doUpdateActive()
{
	if (Game::gameSystem) {
		PSSystem::SceneMgr* mgr = PSSystem::getSceneMgr();
		PSSystem::checkSceneMgr(mgr);
		PSM::Scene_Ground* scene = static_cast<PSM::Scene_Ground*>(mgr->getChildScene());

		Game::TimeMgr* timemgr = Game::gameSystem->mTimeMgr;
		f32 sunRatio           = timemgr->getSunGaugeRatio();

		f32 totalTime, startTime, countTime;
		startTime = timemgr->mParms.parms.mDayStartTime.mValue;
		countTime = timemgr->mParms.parms.mCountdownTime.mValue - startTime;
		totalTime = timemgr->mParms.parms.mDayEndTime.mValue - startTime;

		og::Screen::DispMemberGround* disp = static_cast<og::Screen::DispMemberGround*>(mDispMember);
		disp->mDayEndCount.mCurrSunRatio   = sunRatio;

		f32 startCountdownDayRatio   = (countTime) / totalTime;
		disp->mDayEndCount.mDuration = startCountdownDayRatio;
		if (sunRatio >= startCountdownDayRatio) {
			if (!mDoStartCountdown) {
				mDoStartCountdown = true;
				searchObj("DayEndCount")->start(nullptr);
			}
		} else {
			mDoStartCountdown = false;
		}

		if (sunRatio >= startCountdownDayRatio && (sunRatio - startCountdownDayRatio) / (1.0f - startCountdownDayRatio) >= 0.9f) {
			if (!mDoStartFadeOutSunsetBgm) {
				mDoStartFadeOutSunsetBgm = true;
				scene->fadeMainBgm(0.0f, 0, PSM::Scene_Ground::GroundTime_Off);
			}
		}

		f32 startWarningDayRatio     = (timemgr->mParms.parms.mSundownAlertTime.mValue - startTime) / totalTime;
		disp->mHurryUp.mDuration     = startWarningDayRatio;
		disp->mHurryUp.mCurrSunRatio = sunRatio;
		if (sunRatio >= startWarningDayRatio) {
			if (!mDoStartSunsetBgm) {
				mDoStartSunsetBgm = true;
				searchObj("HurryUp2D")->start(nullptr);
				if (!sGameFlag_MainBgm_Evening) {
					sGameFlag_MainBgm_Evening = true;
					scene->jumpMainBgm(1);
				}
			}
		} else {
			mDoStartSunsetBgm = false;
		}

		f32 cTime = timemgr->getRealDayTime();
		u32 out   = PSM::Scene_Ground::cEvenning_fadeOuTime;
		u32 in    = PSM::Scene_Ground::cEvenning_fadeInTime;
		cTime     = sys->mDeltaTime / cTime;

		f32 timeToWarning = -(cTime * out - startWarningDayRatio);
		f32 timeSeconds   = cTime * in + startWarningDayRatio;

		if (sunRatio < startWarningDayRatio && sunRatio > timeToWarning) {
			if (!mDoStartFadeInSunsetBgm) {
				mDoStartFadeInSunsetBgm = true;
				scene->fadeMainBgm(0.0f, out, PSM::Scene_Ground::GroundTime_On);
			}
		}

		if (sunRatio > startWarningDayRatio && sunRatio > timeSeconds) {
			if (!mDoStartFadeOutMainBgm) {
				mDoStartFadeOutMainBgm = true;
				scene->fadeMainBgm(1.0f, in, PSM::Scene_Ground::GroundTime_On);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	8030DE80
 * Size:	00000C
 */
const char* Ground::getResName() const { return "res_ground.szs"; }

/*
 * --INFO--
 * Address:	8030DE8C
 * Size:	000008
 */
SceneType Ground::getSceneType() { return SCENE_GROUND; }

/*
 * --INFO--
 * Address:	8030DE94
 * Size:	00000C
 */
ScreenOwnerID Ground::getOwnerID() { return OWNER_OGA; }

/*
 * --INFO--
 * Address:	8030DEA0
 * Size:	000010
 */
ScreenMemberID Ground::getMemberID() { return MEMBER_GROUND; }

/*
 * --INFO--
 * Address:	8030DEB0
 * Size:	000008
 */
bool Ground::isDrawInDemo() const { return false; }
} // namespace newScreen
} // namespace og
