#include "Screen/Game2DMgr.h"
#include "og/ogLib2D.h"
#include "og/newScreen/Ground.h"
#include "Game/gamePlayData.h"
#include "Game/Navi.h"
#include "kh/khFinalFloor.h"
#include "kh/khReadyGo.h"
#include "og/newScreen/Challenge.h"
#include "og/Sound.h"
#include "kh/khFinalResult.h"
#include "kh/khCaveResult.h"
#include "kh/khWinLose.h"
#include "Game/Entities/ItemOnyon.h"
#include "Morimura/Zukan.h"
#include "PSSystem/PSSystemIF.h"
#include "Morimura/challengeResult2d.h"
#include "Morimura/challengeSelect2d.h"
#include "Morimura/VsSelect.h"
#include "Morimura/HiScore.h"
#include "og/newScreen/KanteiDemo.h"
#include "Game/GameSystem.h"

namespace Screen {

Game2DMgr* gGame2DMgr;

/**
 * @note Address: 0x803FBEEC
 * @note Size: 0x60
 */
void Game2DMgr::create()
{
	P2ASSERTLINE(486, !gGame2DMgr);
	gGame2DMgr = new Game2DMgr;
}

/**
 * @note Address: 0x803FBF4C
 * @note Size: 0x58
 */
Game2DMgr::Game2DMgr()
    : mScreenMgr(nullptr)
{
	mScreenMgr = newScreen::Mgr::create();
	mScreenMgr->init();
	og::Lib2D::create();
}

/**
 * @note Address: 0x803FBFA4
 * @note Size: 0x68
 */
Game2DMgr::~Game2DMgr() { gGame2DMgr = nullptr; }

/**
 * @note Address: 0x803FC00C
 * @note Size: 0x20
 */
void Game2DMgr::initInCourse() { og::newScreen::initGround(); }

/**
 * @note Address: 0x803FC02C
 * @note Size: 0x24
 */
void Game2DMgr::update() { mScreenMgr->update(); }

/**
 * @note Address: 0x803FC050
 * @note Size: 0x24
 */
void Game2DMgr::draw(Graphics& gfx) { mScreenMgr->draw(gfx); }

/**
 * @note Address: 0x803FC074
 * @note Size: 0x4
 */
void Game2DMgr::drawIndirect(Graphics&) { }

/**
 * @note Address: 0x803FC078
 * @note Size: 0x24
 */
void Game2DMgr::setGamePad(Controller* cont) { mScreenMgr->setGamePad(cont); }

/**
 * @note Address: 0x803FC09C
 * @note Size: 0x34
 */
bool Game2DMgr::setDispMember(og::Screen::DispMemberBase* disp)
{
	if (mScreenMgr) {
		return mScreenMgr->setDispMember(disp);
	} else {
		return nullptr;
	}
}

/**
 * @note Address: 0x803FC0D0
 * @note Size: 0x38
 */
void Game2DMgr::setToumeiBG() { mScreenMgr->mBackupScene->setColorBG(0, 0, 0, 0); }

/**
 * @note Address: 0x803FC108
 * @note Size: 0xBC
 */
bool Game2DMgr::open_GameGround(og::Screen::DispMemberGround& disp)
{
	if (Game::playData->mStoryFlags & Game::STORY_DebtPaid) {
		disp.mPayDebt = true;
	}
	disp.mDataGame.mPokoCount = Game::playData->mPokoCount;

	SetSceneArg arg(SCENE_GROUND, &disp, 0, true);
	if (mScreenMgr->setScene(arg)) {
		mScreenMgr->startScene(nullptr);
	}
	return false;
}

/**
 * @note Address: 0x803FC1C4
 * @note Size: 0x60
 */
bool Game2DMgr::is_GameGround()
{
	bool ret = false;
	if (mScreenMgr->getSceneType() == SCENE_GROUND && mScreenMgr->mBackupScene->mStateID != 1) {
		ret = true;
	}
	return ret;
}

/**
 * @note Address: 0x803FC224
 * @note Size: 0x1B4
 */
bool Game2DMgr::open_GameCave(og::Screen::DispMemberCave& disp, int type)
{
	if (Game::playData->mStoryFlags & Game::STORY_DebtPaid) {
		disp.mPayDebt = true;
	}
	disp.mDataGame.mPokoCount = Game::playData->mCavePokoCount;

	if (type == 0) {
		SetSceneArg arg(SCENE_CAVE, &disp, 0, true);
		if (mScreenMgr->setScene(arg)) {
			mScreenMgr->startScene(nullptr);
		}
	} else if (type & 2) {
		SetSceneArg arg(SCENE_CAVE, &disp, 0, true);
		if (mScreenMgr->setScene(arg)) {
			kh::Screen::DispFinalFloor disp2;
			SetSceneArg arg2(SCENE_FINAL_FLOOR, &disp2, 0, true);
			if (mScreenMgr->setScene(arg2)) {
				mScreenMgr->startScene(nullptr);
			}
		}
	}
	return false;
}

/**
 * @note Address: 0x803FC3D8
 * @note Size: 0x60
 */
bool Game2DMgr::is_GameCave()
{
	bool ret = false;
	if (mScreenMgr->getSceneType() == SCENE_CAVE && mScreenMgr->mBackupScene->mStateID != 1) {
		ret = true;
	}
	return ret;
}

/**
 * @note Address: 0x803FC438
 * @note Size: 0x1A0
 */
bool Game2DMgr::open_GameVs(og::Screen::DispMemberVs& disp, int type)
{
	if (type == 0) {
		SetSceneArg arg(SCENE_VS, &disp, 0, true);
		if (mScreenMgr->setScene(arg)) {
			mScreenMgr->startScene(nullptr);
		}
	} else if (type & 1) {
		SetSceneArg arg(SCENE_VS, &disp, 0, true);
		if (mScreenMgr->setScene(arg)) {
			kh::Screen::DispReadyGo disp2;
			disp2.mIs2Player = true;
			SetSceneArg arg2(SCENE_READY_GO, &disp2, 0, true);
			if (mScreenMgr->setScene(arg2)) {
				mScreenMgr->startScene(nullptr);
			}
		}
	}
	return true;
}

/**
 * @note Address: 0x803FC5D8
 * @note Size: 0x9C
 */
int Game2DMgr::check_VsStatus()
{
	int ret                        = 3;
	og::Screen::DispMemberVs* disp = static_cast<og::Screen::DispMemberVs*>(mScreenMgr->getDispMember());
	if (disp && disp->isID(OWNER_OGA, MEMBER_VS)) {
		switch (disp->mDoneState) {
		case 0:
			ret = 0;
			break;
		case 1:
			ret = 1;
			break;
		case 2:
			ret = 2;
			break;
		}
	}
	return ret;
}

/**
 * @note Address: 0x803FC674
 * @note Size: 0x334
 */
void Game2DMgr::open_GameChallenge2P(og::Screen::DispMemberChallenge2P& disp, int type)
{
	SetSceneArg arg(SCENE_CHALLENGE_2P, &disp, 0, true);
	og::newScreen::SArgChallenge2P sarg(1.5f);

	if (type == 0) {
		if (mScreenMgr->setScene(arg)) {
			mScreenMgr->startScene(&sarg);
		}
	} else if ((type & 3) == 3) {
		if (mScreenMgr->setScene(arg)) {
			kh::Screen::DispReadyGo disp2;
			disp2.mIs2Player    = true;
			disp2.mIsFinalFloor = true;
			disp2.mGameType     = 1;
			SetSceneArg arg2(SCENE_READY_GO, &disp2, 0, true);
			if (mScreenMgr->setScene(arg2)) {
				mScreenMgr->startScene(nullptr);
			}
		}
	} else if (type & 1) {
		if (mScreenMgr->setScene(arg)) {
			kh::Screen::DispReadyGo disp2;
			disp2.mIs2Player = true;
			disp2.mGameType  = 1;
			SetSceneArg arg2(SCENE_READY_GO, &disp2, 0, true);
			if (mScreenMgr->setScene(arg2)) {
				mScreenMgr->startScene(nullptr);
			}
		}
	} else if (type & 2) {
		if (mScreenMgr->setScene(arg)) {
			kh::Screen::DispFinalFloor disp2;
			disp2.mIs2Player = true;
			SetSceneArg arg2(SCENE_FINAL_FLOOR, &disp2, 0, true);
			if (mScreenMgr->setScene(arg2)) {
				mScreenMgr->startScene(nullptr);
			}
		}
	}
}

/**
 * @note Address: 0x803FC9A8
 * @note Size: 0x328
 */
void Game2DMgr::open_GameChallenge1P(og::Screen::DispMemberChallenge1P& disp, int type)
{
	SetSceneArg arg(SCENE_CHALLENGE_1P, &disp, 0, true);
	og::newScreen::SArgChallenge1P sarg(1.5f);

	if (type == 0) {
		if (mScreenMgr->setScene(arg)) {
			mScreenMgr->startScene(&sarg);
		}
	} else if ((type & 3) == 3) {
		if (mScreenMgr->setScene(arg)) {
			kh::Screen::DispReadyGo disp2;
			disp2.mIsFinalFloor = true;
			disp2.mGameType     = 1;
			SetSceneArg arg2(SCENE_READY_GO, &disp2, 0, true);
			if (mScreenMgr->setScene(arg2)) {
				mScreenMgr->startScene(nullptr);
			}
		}
	} else if (type == 1) {
		if (mScreenMgr->setScene(arg)) {
			kh::Screen::DispReadyGo disp2;
			disp2.mGameType = 1;
			SetSceneArg arg2(SCENE_READY_GO, &disp2, 0, true);
			if (mScreenMgr->setScene(arg2)) {
				mScreenMgr->startScene(nullptr);
			}
		}
	} else if (type == 2) {
		if (mScreenMgr->setScene(arg)) {
			kh::Screen::DispFinalFloor disp2;
			SetSceneArg arg2(SCENE_FINAL_FLOOR, &disp2, 0, true);
			if (mScreenMgr->setScene(arg2)) {
				mScreenMgr->startScene(nullptr);
			}
		}
	}
}

/**
 * @note Address: 0x803FCCD0
 * @note Size: 0xB0
 */
bool Game2DMgr::open_SMenu(og::Screen::DispMemberSMenuAll& disp)
{
	if (mScreenMgr->isAnyReservation())
		return false;
	switch (mScreenMgr->getSceneType()) {
	default:
		return false;
	case SCENE_GROUND:
	case SCENE_CAVE:
	case SCENE_VS:
	case SCENE_CHALLENGE_1P:
	case SCENE_CHALLENGE_2P:
		if (!Game::naviMgr->getActiveNavi()) {
			return false;
		} else {
			disp.mSMenuMap.mActiveNavi = true;
			return open_SMenu_Sub(disp);
		}
		break;
	}
}

/**
 * @note Address: 0x803FCD80
 * @note Size: 0x1B0
 */
bool Game2DMgr::open_SMenu_Sub(og::Screen::DispMemberSMenuAll& disp)
{
	bool ret                              = false;
	disp.mSMenuPauseDoukutu.mPreCavePokos = disp.mSMenuPause.mPokoCount;
	if (static_cast<newScreen::Mgr*>(mScreenMgr)->mInCave) {
		disp.mSMenuMap.mInCave = true;
	} else {
		disp.mSMenuMap.mInCave = false;
	}

	// probably want define for poko count
	if (disp.mSMenuPauseDoukutu.mPreCavePokos < 10000) {
		disp.mSMenuPauseDoukutu.mPayDebt = true;
	} else {
		disp.mSMenuPauseDoukutu.mPayDebt = false;
	}
	og::ogSound->setOpen();
	PSPause_StartMenuOn();
	bool set;

	switch (disp.mOpenMode) {
	case og::Screen::DispMemberSMenuAll::Open_StoryMode: {
		SetSceneArg arg(SCENE_PAUSE_MENU_MAP, &disp, 0, true);
		set = mScreenMgr->setScene(arg);
		break;
	}
	case og::Screen::DispMemberSMenuAll::Open_ChallengeMode:
	case og::Screen::DispMemberSMenuAll::Open_Versus: {
		SetSceneArg arg(SCENE_PAUSE_MENU_VS, &disp, 0, true);
		set = mScreenMgr->setScene(arg);
		break;
	}
	default:
		JUT_PANICLINE(969, "SMENU MODE ERR!");
	}
	if (set) {
		if (mScreenMgr->startScene(nullptr)) {
			ret = true;
		}
	}
	return ret;
}

/**
 * @note Address: 0x803FCF30
 * @note Size: 0x128
 */
int Game2DMgr::check_SMenu()
{
	int exit = -1;
	switch (mScreenMgr->getSceneType()) {
	case SCENE_PAUSE_MENU_CONTROLS:
	case SCENE_PAUSE_MENU:
	case SCENE_PAUSE_MENU_DOUKUTU:
	case SCENE_PAUSE_MENU_MAP:
	case SCENE_PAUSE_MENU_ITEMS:
	case SCENE_PAUSE_MENU_VS: {
		if (mScreenMgr->isSceneFinish()) {
			int scene = mScreenMgr->getSceneFinishState();
			switch (scene) {
			case SceneBase::SB_WaitForResourceSync:
				exit = 0;
				break;

			case SceneBase::SB_Unknown2:
				PSPause_StartMenuOff();
				exit = 1;
				break;

			case SceneBase::SB_Started:
				PSPause_StartMenuOff();
				exit = 2;
				break;

			case SceneBase::SB_Unknown4:
				PSPause_StartMenuOff();
				exit = 3;
				break;

			case SceneBase::SB_Unknown5:
				PSPause_StartMenuOff();
				exit = 1;
				break;

			case SceneBase::SB_Unknown6:
				PSPause_StartMenuOff();
				exit = 4;
				break;

			case SceneBase::SB_Unknown7:
				PSPause_StartMenuOff();
				exit = 5;
				break;

			default:
				JUT_PANICLINE(1045, "SMENU FinishStateError %d \n", scene);
				break;
			}
		} else {
			exit = 0;
		}
		break;
	}
	default: {
		exit = -1;
		break;
	}
	}
	return exit;
}

/**
 * @note Address: 0x803FD058
 * @note Size: 0xA8
 */
bool Game2DMgr::open_WorldMapInfoWin0(og::Screen::DispMemberWorldMapInfoWin0& disp)
{
	SetSceneArg arg(SCENE_WORLD_MAP_INFO_WINDOW_0, &disp, 0, true);
	if (mScreenMgr->setScene(arg)) {
		if (mScreenMgr->startScene(nullptr)) {
			return true;
		}
	}
	return false;
}

/**
 * @note Address: 0x803FD100
 * @note Size: 0x7C
 */
int Game2DMgr::check_WorldMapInfoWin0() const
{
	if (mScreenMgr->getSceneType() != SCENE_WORLD_MAP_INFO_WINDOW_0) {
		return 2;
	}
	if (mScreenMgr->isSceneFinish()) {
		int state = mScreenMgr->getSceneFinishState();
		if (state == 0)
			return 0;
		if (state == 1)
			return 1;
	}
	return 3;
}

/**
 * @note Address: 0x803FD17C
 * @note Size: 0xA8
 */
bool Game2DMgr::open_WorldMapInfoWin1(og::Screen::DispMemberWorldMapInfoWin1& disp)
{
	SetSceneArg arg(SCENE_WORLD_MAP_INFO_WINDOW_1, &disp, 0, true);
	if (mScreenMgr->setScene(arg)) {
		if (mScreenMgr->startScene(nullptr)) {
			return true;
		}
	}
	return false;
}

/**
 * @note Address: 0x803FD224
 * @note Size: 0x7C
 */
int Game2DMgr::check_WorldMapInfoWin1() const
{
	if (mScreenMgr->getSceneType() != SCENE_WORLD_MAP_INFO_WINDOW_1) {
		return 2;
	}
	if (mScreenMgr->isSceneFinish()) {
		int state = mScreenMgr->getSceneFinishState();
		if (state == 0)
			return 0;
		if (state == 1)
			return 1;
	}
	return 3;
}

/**
 * @note Address: 0x803FD2A0
 * @note Size: 0x124
 */
void Game2DMgr::open_Kantei(og::Screen::DispMemberKantei& disp)
{
	if (static_cast<newScreen::Mgr*>(mScreenMgr)->mInCave) {
		disp.mInCave = true;
	} else {
		disp.mInCave = false;
	}

	if (disp.mTotalPokos >= 10000) {
		disp._28 = 1;
	} else {
		disp._28 = 0;
	}

	if (disp._28) {
		disp.mKanteiType = 1;
	} else {
		disp.mKanteiType = 0;
	}

	SetSceneArg arg(SCENE_KANTEI_DEMO, &disp, 0, true);
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		PSPause_StartMenuOn();
	} else {
		JUT_PANICLINE(1142, "fail to open Kantei!\n");
	}
}

/**
 * @note Address: 0x803FD3C4
 * @note Size: 0x84
 */
void Game2DMgr::close_Kantei()
{
	if (mScreenMgr->getSceneType() == SCENE_KANTEI_DEMO) {
		if (mScreenMgr->setBackupScene()) {
			mScreenMgr->startScene(nullptr);
			PSPause_StartMenuOff();
		} else {
			JUT_PANICLINE(1167, "call to OG san");
		}
	}
}

/**
 * @note Address: 0x803FD448
 * @note Size: 0x74
 */
bool Game2DMgr::update_Kantei()
{
	bool ret                           = true;
	og::Screen::DispMemberKantei* disp = static_cast<og::Screen::DispMemberKantei*>(mScreenMgr->getDispMember());
	if (disp && disp->isID(OWNER_OGA, MEMBER_KANTEI) && disp->mIsDone) {
		ret = false;
	}
	return ret;
}

/**
 * @note Address: 0x803FD4BC
 * @note Size: 0x90
 */
void Game2DMgr::open_SpecialItem(og::Screen::DispMemberSpecialItem& disp)
{
	SetSceneArg arg(SCENE_SPECIAL_ITEM, &disp, 0, true);
	mScreenMgr->setScene(arg);
	mScreenMgr->startScene(nullptr);
	PSPause_StartMenuOn();
}

/**
 * @note Address: 0x803FD54C
 * @note Size: 0x84
 */
void Game2DMgr::close_SpecialItem()
{
	if (mScreenMgr->getSceneType() == SCENE_SPECIAL_ITEM) {
		if (mScreenMgr->setBackupScene()) {
			mScreenMgr->startScene(nullptr);
			PSPause_StartMenuOff();
		} else {
			JUT_PANICLINE(1223, "call to OG san");
		}
	}
}

/**
 * @note Address: 0x803FD5D0
 * @note Size: 0x90
 */
void Game2DMgr::open_Floor(og::Screen::DispMemberFloor& disp)
{
	SetSceneArg arg(SCENE_FLOOR, &disp, 0, true);
	arg._08 = 1; // probably proof the last two arguments dont belong in the ctor
	mScreenMgr->setScene(arg);
	mScreenMgr->startScene(nullptr);
}

/**
 * @note Address: 0x803FD660
 * @note Size: 0x70
 */
void Game2DMgr::close_Floor()
{
	if (mScreenMgr->getSceneType() == SCENE_FLOOR) {
		EndSceneArg arg;
		arg._04 = 1;
		mScreenMgr->endScene(&arg);
	}
}

/**
 * @note Address: 0x803FD6D0
 * @note Size: 0x5C
 */
void Game2DMgr::set_FloorVS_LoadEnd()
{
	if (mScreenMgr->getSceneType() == SCENE_FLOOR) {
		og::Screen::DispMemberFloor* disp = static_cast<og::Screen::DispMemberFloor*>(mScreenMgr->getDispMember());
		disp->mEnableButton               = true;
		if (mScreenMgr) {
			mScreenMgr->setDispMember(disp);
		}
	}
}

/**
 * @note Address: 0x803FD72C
 * @note Size: 0x48
 */
void Game2DMgr::startCount_Floor()
{
	if (mScreenMgr->getSceneType() == SCENE_FLOOR) {
		og::Screen::DispMemberFloor* disp = static_cast<og::Screen::DispMemberFloor*>(mScreenMgr->getDispMember());
		disp->mDoEnd                      = true;
	}
}

/**
 * @note Address: 0x803FD774
 * @note Size: 0x48
 */
void Game2DMgr::startFadeBG_Floor()
{
	if (mScreenMgr->getSceneType() == SCENE_FLOOR) {
		og::Screen::DispMemberFloor* disp = static_cast<og::Screen::DispMemberFloor*>(mScreenMgr->getDispMember());
		disp->mDoForceEnd                 = true;
	}
}

/**
 * @note Address: 0x803FD7BC
 * @note Size: 0x90
 */
bool Game2DMgr::open_CourseName(og::Screen::DispMemberCourseName& disp)
{
	SetSceneArg arg(SCENE_COURSE_NAME, &disp, 0, true);
	arg._08 = 1;
	mScreenMgr->setScene(arg);
	mScreenMgr->startScene(nullptr);
}

/**
 * @note Address: 0x803FD84C
 * @note Size: 0x48
 */
void Game2DMgr::startFadeBG_CourseName()
{
	if (mScreenMgr->getSceneType() == SCENE_COURSE_NAME) {
		og::Screen::DispMemberCourseName* disp = static_cast<og::Screen::DispMemberCourseName*>(mScreenMgr->getDispMember());
		disp->mIsExiting                       = true;
	}
}

/**
 * @note Address: 0x803FD894
 * @note Size: 0x70
 */
void Game2DMgr::close_CourseName()
{
	if (mScreenMgr->getSceneType() == SCENE_COURSE_NAME) {
		EndSceneArg arg;
		arg._04 = 1;
		mScreenMgr->endScene(&arg);
	}
}

/**
 * @note Address: 0x803FD904
 * @note Size: 0x48
 */
void Game2DMgr::startCount_CourseName()
{
	if (mScreenMgr->getSceneType() == SCENE_COURSE_NAME) {
		og::Screen::DispMemberCourseName* disp = static_cast<og::Screen::DispMemberCourseName*>(mScreenMgr->getDispMember());
		disp->mIsCounting                      = true;
	}
}

/**
 * @note Address: 0x803FD94C
 * @note Size: 0x258
 */
void Game2DMgr::open_GameOver(GameOverTitle id)
{
	switch (id) {
	case GOTITLE_Default: {
		SetSceneArg arg(SCENE_GAME_OVER_GENERAL, nullptr, 0, true);
		mScreenMgr->setScene(arg);
		mScreenMgr->startScene(nullptr);
		break;
	}
	case GOTITLE_OlimarDown: {
		SetSceneArg arg(SCENE_ORIMA_DOWN, nullptr, 0, true);
		mScreenMgr->setScene(arg);
		mScreenMgr->startScene(nullptr);
		break;
	}
	case GOTITLE_LouieDown: {
		SetSceneArg arg(SCENE_LUJI_DOWN, nullptr, 0, true);
		mScreenMgr->setScene(arg);
		mScreenMgr->startScene(nullptr);
		break;
	}
	case GOTITLE_PresidentDown: {
		SetSceneArg arg(SCENE_PRESIDENT_DOWN, nullptr, 0, true);
		mScreenMgr->setScene(arg);
		mScreenMgr->startScene(nullptr);
		break;
	}
	case GOTITLE_PikminZero: {
		SetSceneArg arg(SCENE_PIKMIN_DOWN, nullptr, 0, true);
		mScreenMgr->setScene(arg);
		mScreenMgr->startScene(nullptr);
		break;
	}
	}
}

/**
 * @note Address: 0x803FDBA4
 * @note Size: 0xAC
 */
void Game2DMgr::close_GameOver()
{
	switch (mScreenMgr->getSceneType()) {
	case SCENE_GAME_OVER_GENERAL:
	case SCENE_PIKMIN_DOWN: {
		mScreenMgr->endScene(nullptr);
		break;
	}
	case SCENE_ORIMA_DOWN:
	case SCENE_LUJI_DOWN:
	case SCENE_PRESIDENT_DOWN: {
		if (mScreenMgr->setBackupScene()) {
			mScreenMgr->startScene(nullptr);
		} else {
			mScreenMgr->endScene(nullptr);
		}
	}
	}
}

/**
 * @note Address: 0x803FDC50
 * @note Size: 0xE0
 */
bool Game2DMgr::open_CaveInMenu(og::Screen::DispMemberAnaDemo& disp)
{
	if (mScreenMgr->isAnyReservation()) {
		return false;
	}

	if (mScreenMgr->getSceneType() == SCENE_GROUND) {
		SetSceneArg arg(SCENE_CAVE_IN_MENU, &disp, 0, true);
		if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
			PSPause_StartMenuOn();
			return true;
		}
	}
	return false;
}

/**
 * @note Address: 0x803FDD30
 * @note Size: 0x9C
 */
int Game2DMgr::check_CaveInMenu()
{
	int ret;
	og::Screen::DispMemberAnaDemo* disp = static_cast<og::Screen::DispMemberAnaDemo*>(mScreenMgr->getDispMember());
	if (disp) {
		if (disp->isID(OWNER_OGA, MEMBER_ANA_DEMO)) {
			if (disp->_1F) {
				ret = 0;
			} else {
				int ret2 = 2;
				if (disp->mSelected)
					ret2 = 1;
				ret = ret2;
				PSPause_StartMenuOff();
			}
		} else {
			ret = -1;
		}
	} else {
		ret = -2;
	}
	return ret;
}

/**
 * @note Address: 0x803FDDCC
 * @note Size: 0xE0
 */
bool Game2DMgr::open_KanketuMenu(og::Screen::DispMemberKanketuMenu& disp)
{
	if (mScreenMgr->isAnyReservation()) {
		return false;
	}

	if (mScreenMgr->getSceneType() == SCENE_CAVE) {
		SetSceneArg arg(SCENE_KANKETU_MENU, &disp, 0, true);
		if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
			PSPause_StartMenuOn();
			return true;
		}
	}
	return false;
}

/**
 * @note Address: 0x803FDEAC
 * @note Size: 0xF4
 */
bool Game2DMgr::open_ChallengeKanketuMenu(og::Screen::DispMemberKanketuMenu& disp)
{
	if (mScreenMgr->isAnyReservation()) {
		return false;
	}

	if (mScreenMgr->getSceneType() == SCENE_CHALLENGE_1P || mScreenMgr->getSceneType() == SCENE_CHALLENGE_2P) {
		disp.mIsChallenge = true;
		SetSceneArg arg(SCENE_KANKETU_MENU, &disp, 0, true);
		if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
			PSPause_StartMenuOn();
			return true;
		}
	}
	return false;
}

/**
 * @note Address: 0x803FDFA0
 * @note Size: 0x9C
 */
int Game2DMgr::check_KanketuMenu()
{
	int ret;
	og::Screen::DispMemberAnaDemo* disp = static_cast<og::Screen::DispMemberAnaDemo*>(mScreenMgr->getDispMember());
	if (disp) {
		if (disp->isID(OWNER_OGA, MEMBER_KANKETU_MENU)) {
			if (disp->_1F) {
				ret = 0;
			} else {
				int ret2 = 2;
				if (disp->mSelected)
					ret2 = 1;
				ret = ret2;
				PSPause_StartMenuOff();
			}
		} else {
			ret = -1;
		}
	} else {
		ret = -2;
	}
	return ret;
}

/**
 * @note Address: 0x803FE03C
 * @note Size: 0x100
 */
bool Game2DMgr::open_CaveMoreMenu(og::Screen::DispMemberCaveMore& disp)
{
	if (mScreenMgr->isAnyReservation()) {
		return false;
	}

	if (mScreenMgr->getSceneType() == SCENE_CAVE || mScreenMgr->getSceneType() == SCENE_CHALLENGE_1P
	    || mScreenMgr->getSceneType() == SCENE_CHALLENGE_2P) {
		SetSceneArg arg(SCENE_CAVE_MORE_MENU, &disp, 0, true);
		if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
			PSPause_StartMenuOn();
			return true;
		}
	}
	return false;
}

/**
 * @note Address: 0x803FE13C
 * @note Size: 0x9C
 */
int Game2DMgr::check_CaveMoreMenu()
{
	int ret;
	og::Screen::DispMemberAnaDemo* disp = static_cast<og::Screen::DispMemberAnaDemo*>(mScreenMgr->getDispMember());
	if (disp) {
		if (disp->isID(OWNER_OGA, MEMBER_CAVE_MORE)) {
			if (disp->_1F) {
				ret = 0;
			} else {
				int ret2 = 2;
				if (disp->mSelected)
					ret2 = 1;
				ret = ret2;
				PSPause_StartMenuOff();
			}
		} else {
			ret = -1;
		}
	} else {
		ret = -2;
	}
	return ret;
}

/**
 * @note Address: 0x803FE1D8
 * @note Size: 0xAC
 */
bool Game2DMgr::open_FinalResult(kh::Screen::DispFinalResult& disp)
{
	SetSceneArg arg(SCENE_FINAL_RESULT, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	arg._08 = 1;
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FE284
 * @note Size: 0x8C
 */
int Game2DMgr::check_FinalResult() const
{
	if (mScreenMgr->getSceneType() != SCENE_FINAL_RESULT) {
		return -1;
	} else {
		if (!mScreenMgr->getDispMember()->isID(OWNER_KH, MEMBER_FINAL_RESULT)) {
			JUT_PANICLINE(1636, "disp member err");
		}
		return reinterpret_cast<kh::Screen::DispFinalResult*>(mScreenMgr->getDispMember())->mExitStatus;
	}
}

/**
 * @note Address: 0x803FE310
 * @note Size: 0xA8
 */
bool Game2DMgr::open_CaveResult(kh::Screen::DispCaveResult& disp)
{
	SetSceneArg arg(SCENE_CAVE_RESULT, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FE3B8
 * @note Size: 0x8C
 */
int Game2DMgr::check_CaveResult() const
{
	if (mScreenMgr->getSceneType() != SCENE_CAVE_RESULT) {
		return -1;
	} else {
		if (!mScreenMgr->getDispMember()->isID(OWNER_KH, MEMBER_CAVE_RESULT)) {
			JUT_PANICLINE(1656, "disp member err");
		}
		return reinterpret_cast<kh::Screen::DispCaveResult*>(mScreenMgr->getDispMember())->mIsFinished;
	}
}

/**
 * @note Address: 0x803FE444
 * @note Size: 0xAC
 */
bool Game2DMgr::open_DayEndResult(kh::Screen::DispDayEndResult& disp)
{
	SetSceneArg arg(SCENE_DAY_END_RESULT_TITL, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	arg._08 = 1;
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FE4F0
 * @note Size: 0xB0
 */
int Game2DMgr::check_DayEndResult() const
{
	if (mScreenMgr->getSceneType() != SCENE_DAY_END_RESULT_ITEM && mScreenMgr->getSceneType() != SCENE_DAY_END_RESULT_INC_P
	    && mScreenMgr->getSceneType() != SCENE_DAY_END_RESULT_MAIL) {
		return -1;
	}

	if (!mScreenMgr->getDispMember()->isID(OWNER_KH, MEMBER_DAY_END_RESULT)) {
		JUT_PANICLINE(1687, "disp member err");
	}
	return reinterpret_cast<kh::Screen::DispDayEndResult*>(mScreenMgr->getDispMember())->mMail._14;
}

/**
 * @note Address: 0x803FE5A0
 * @note Size: 0xA8
 */
bool Game2DMgr::open_PayDept(kh::Screen::DispPayDept& disp)
{
	SetSceneArg arg(SCENE_PAY_DEPT, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FE648
 * @note Size: 0x5C
 */
int Game2DMgr::check_PayDept() const
{
	int ret = 0;
	if (mScreenMgr->getSceneType() == SCENE_PAY_DEPT && mScreenMgr->isSceneFinish()) {
		ret = 1;
	}
	return ret;
}

/**
 * @note Address: 0x803FE6A4
 * @note Size: 0xA8
 */
bool Game2DMgr::open_Save(og::Screen::DispMemberSave& disp)
{
	SetSceneArg arg(SCENE_SAVE, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FE74C
 * @note Size: 0x5C
 */
int Game2DMgr::check_Save() const
{
	int ret = 0;
	if (mScreenMgr->getSceneType() == SCENE_SAVE && mScreenMgr->isSceneFinish()) {
		ret = 1;
	}
	return ret;
}

/**
 * @note Address: 0x803FE7A8
 * @note Size: 0xA8
 */
bool Game2DMgr::open_FinalMessage(og::Screen::DispMemberFinalMessage& disp)
{
	SetSceneArg arg(SCENE_FINAL_MSG, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FE850
 * @note Size: 0x48
 */
int Game2DMgr::check_FinalMessage() const
{
	int ret = 0;
	if (mScreenMgr->getSceneType() != SCENE_FINAL_MSG) {
		return -10;
	}
	return mScreenMgr->getSceneFinishState();
}

/**
 * @note Address: 0x803FE898
 * @note Size: 0x70
 */
void Game2DMgr::stopFinalFloorSound()
{
	if (mScreenMgr->getSceneType() == SCENE_FINAL_FLOOR) {
		kh::Screen::SceneFinalFloor* scene = static_cast<kh::Screen::SceneFinalFloor*>(mScreenMgr->mBackupScene);
		kh::Screen::finalFloorStopSound(scene);
	}
}

/**
 * @note Address: 0x803FE908
 * @note Size: 0x70
 */
void Game2DMgr::restartFinalFloorSound()
{
	if (mScreenMgr->getSceneType() == SCENE_FINAL_FLOOR) {
		kh::Screen::SceneFinalFloor* scene = static_cast<kh::Screen::SceneFinalFloor*>(mScreenMgr->mBackupScene);
		kh::Screen::finalFloorRestartSound(scene);
	}
}

/**
 * @note Address: 0x803FE978
 * @note Size: 0x90
 */
int Game2DMgr::check_ReadyGo() const
{
	if (mScreenMgr->getSceneType() != SCENE_READY_GO) {
		return -1;
	} else {
		if (!mScreenMgr->getDispMember()->isID(OWNER_KH, MEMBER_READY_GO)) {
			JUT_PANICLINE(1766, "disp member err");
		}
		return reinterpret_cast<kh::Screen::DispReadyGo*>(mScreenMgr->getDispMember())->mStatus;
	}
}

/**
 * @note Address: 0x803FEA08
 * @note Size: 0xA8
 */
bool Game2DMgr::open_WinLoseReason(kh::Screen::DispWinLoseReason& disp)
{
	SetSceneArg arg(SCENE_WIN_LOSE_REASON, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FEAB0
 * @note Size: 0x68
 */
int Game2DMgr::check_WinLoseReason() const
{
	int ret;
	if (mScreenMgr->getSceneType() != SCENE_WIN_LOSE_REASON) {
		ret = 0;
	} else {
		ret                                   = 0;
		kh::Screen::SceneWinLoseReason* scene = reinterpret_cast<kh::Screen::SceneWinLoseReason*>(mScreenMgr->mBackupScene);
		if (scene->mDone[0] && scene->mDone[1]) {
			ret = 1;
		}
	}
	return ret;
}

/**
 * @note Address: 0x803FEB18
 * @note Size: 0xA8
 */
bool Game2DMgr::open_WinLose(kh::Screen::DispWinLose& disp)
{
	SetSceneArg arg(SCENE_WIN_LOSE, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FEBC0
 * @note Size: 0x90
 */
int Game2DMgr::check_WinLose() const
{
	if (mScreenMgr->getSceneType() != SCENE_WIN_LOSE) {
		return -1;
	} else {
		if (!mScreenMgr->getDispMember()->isID(OWNER_KH, MEMBER_WIN_LOSE)) {
			JUT_PANICLINE(1801, "disp member err");
		}
		return reinterpret_cast<kh::Screen::DispWinLose*>(mScreenMgr->getDispMember())->_0C;
	}
}

/**
 * @note Address: 0x803FEC50
 * @note Size: 0xD4
 */
bool Game2DMgr::open_TimeUp1P()
{
	kh::Screen::DispWinLose disp(Timeup1P, 1);
	SetSceneArg arg(SCENE_WIN_LOSE, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FED24
 * @note Size: 0xD4
 */
bool Game2DMgr::open_TimeUp2P()
{
	kh::Screen::DispWinLose disp(Timeup2P, 1);
	SetSceneArg arg(SCENE_WIN_LOSE, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FEDF8
 * @note Size: 0x158
 */
bool Game2DMgr::open_Contena(og::Screen::DispMemberContena& disp)
{
	if (mScreenMgr->isAnyReservation())
		return false;
	if (checkDayEnd(0.08f))
		return false;

	SceneType id = (SceneType)0;
	switch (disp.mOnyonID) {
	case ONYON_TYPE_BLUE:
		id = SCENE_CONTENA_BLUE;
		break;
	case ONYON_TYPE_RED:
		id = SCENE_CONTENA_RED;
		break;
	case ONYON_TYPE_YELLOW:
		id = SCENE_CONTENA_YELLOW;
		break;
	case 4:
		id = SCENE_CONTENA_WHITE;
		break;
	case 3:
		id = SCENE_CONTENA_PURPLE;
		break;
	}
	SetSceneArg arg(id, &disp, 0, true);
	if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
		switch (disp.mOnyonID) {
		case ONYON_TYPE_BLUE:
		case ONYON_TYPE_RED:
		case ONYON_TYPE_YELLOW:
			PSPause_StartMenuOn();
			break;
		}
		return true;
	}
	return false;
}

/**
 * @note Address: 0x803FEF50
 * @note Size: 0xC8
 */
int Game2DMgr::check_Contena()
{
	int ret      = -1;
	SceneType id = mScreenMgr->getSceneType();
	if ((u32)(id + ~SCENE_FLOOR) <= 3 || id == SCENE_CONTENA_PURPLE) {
		og::Screen::DispMemberContena* disp = static_cast<og::Screen::DispMemberContena*>(mScreenMgr->getDispMember());
		if (disp->isID(OWNER_OGA, MEMBER_CONTENA)) {
			switch (disp->mState) {
			case 3:
				ret = 1;
				break;
			case 4:
				ret = 2;
				break;
			default:
				ret = 0;
			}

			if (ret) {
				PSPause_StartMenuOff();
			}
		} else {
			ret = -1;
		}
	}
	return ret;
}

/**
 * @note Address: 0x803FF018
 * @note Size: 0xA8
 */
int Game2DMgr::result_Contena()
{
	int ret      = 0;
	SceneType id = mScreenMgr->getSceneType();
	if ((u32)(id + ~SCENE_FLOOR) <= 3 || id == SCENE_CONTENA_PURPLE) {
		og::Screen::DispMemberContena* disp = static_cast<og::Screen::DispMemberContena*>(mScreenMgr->getDispMember());
		if (disp->isID(OWNER_OGA, MEMBER_CONTENA)) {
			ret = disp->mResult;
		}
	} else {
		JUT_PANICLINE(1937, "Illegal call.\n");
	}
	return ret;
}

/**
 * @note Address: 0x803FF0C0
 * @note Size: 0x244
 */
bool Game2DMgr::open_UfoMenu(og::Screen::DispMemberUfoGroup& disp)
{
	if (mScreenMgr->isAnyReservation())
		return false;
	if (checkDayEnd(0.08f))
		return false;
	if (disp.mHasWhite && disp.mHasPurple) {
		disp.mContena1._2C = 1;
		disp.mContena2._2C = 1;
		SetSceneArg arg(SCENE_UFO_MENU, &disp, 0, true);
		if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
			PSPause_StartMenuOn();
			PSSystem::spSysIF->playSystemSe(PSSE_SY_MENU_OPEN, 0);
			return true;
		}
	} else {
		if (disp.mHasWhite) {
			disp.mContena1._2C         = 0;
			disp.mUfoMenu.mContenaType = 1;
			SetSceneArg arg(SCENE_CONTENA_WHITE, &disp, 0, true);
			if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
				PSPause_StartMenuOn();
				return true;
			}
		} else if (disp.mHasPurple) {
			disp.mContena2._2C         = 0;
			disp.mUfoMenu.mContenaType = 2;
			SetSceneArg arg(SCENE_CONTENA_PURPLE, &disp, 0, true);
			if (mScreenMgr->setScene(arg) && mScreenMgr->startScene(nullptr)) {
				PSPause_StartMenuOn();
				return true;
			}
		}
	}
	return false;
}

/**
 * @note Address: 0x803FF304
 * @note Size: 0x130
 */
int Game2DMgr::check_UfoMenu()
{
	int ret                              = 0;
	og::Screen::DispMemberUfoGroup* disp = static_cast<og::Screen::DispMemberUfoGroup*>(mScreenMgr->getDispMember());
	switch (mScreenMgr->getSceneType()) {
	case SCENE_UFO_MENU: {
		if (!disp->mUfoMenu.mContenaType) {
			ret = 1;
			PSPause_StartMenuOff();
		} else {
			ret = 0;
		}
		break;
	}
	case SCENE_CONTENA_WHITE: {
		switch (disp->mContena1.mState) {
		case 4: {
			ret = 2;
			PSPause_StartMenuOff();
			break;
		}
		case 3: {
			if (disp->mContena1._2C) {
				ret = 0;
			} else {
				ret = 1;
				PSPause_StartMenuOff();
			}
			break;
		}
		default:
			ret = 0;
			break;
		}
		break;
	}
	case SCENE_CONTENA_PURPLE: {
		switch (disp->mContena2.mState) {
		case 4: {
			ret = 2;
			PSPause_StartMenuOff();
			break;
		}
		case 3: {
			if (disp->mContena2._2C) {
				ret = 0;
			} else {
				ret = 1;
				PSPause_StartMenuOff();
			}
			break;
		}
		default:
			ret = 0;
			break;
		}
		break;
	}
	}
	return ret;
}

/**
 * @note Address: 0x803FF434
 * @note Size: 0x98
 */
void Game2DMgr::result_UfoMenu(int* ret1, int* ret2)
{
	og::Screen::DispMemberUfoGroup* disp = static_cast<og::Screen::DispMemberUfoGroup*>(mScreenMgr->getDispMember());
	switch (mScreenMgr->getSceneType()) {
	case SCENE_CONTENA_WHITE: {
		*ret1 = disp->mContena1.mResult;
		*ret2 = 0;
		break;
	}
	case SCENE_CONTENA_PURPLE: {
		*ret1 = 0;
		*ret2 = disp->mContena2.mResult;
		break;
	}
	}
}

/**
 * @note Address: 0x803FF4CC
 * @note Size: 0x9C
 */
bool Game2DMgr::open_ZukanEnemy(Morimura::DispMemberZukanEnemy& disp)
{
	SetSceneArg arg(SCENE_ZUKAN_ENEMY, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg)) {
		return mScreenMgr->startScene(nullptr);
	}
	return false;
}

/**
 * @note Address: 0x803FF568
 * @note Size: 0x9C
 */
bool Game2DMgr::open_ZukanItem(Morimura::DispMemberZukanItem& disp)
{
	SetSceneArg arg(SCENE_ZUKAN_ITEM, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg)) {
		return mScreenMgr->startScene(nullptr);
	}
	return false;
}

/**
 * @note Address: 0x803FF604
 * @note Size: 0x30
 */
bool Game2DMgr::isZukanEnemy() { return (mScreenMgr->getSceneType() == SCENE_ZUKAN_ENEMY); }

/**
 * @note Address: 0x803FF634
 * @note Size: 0x30
 */
bool Game2DMgr::isZukanItem() { return (mScreenMgr->getSceneType() == SCENE_ZUKAN_ITEM); }

/**
 * @note Address: 0x803FF664
 * @note Size: 0x84
 */
int Game2DMgr::check_ZukanItemRequest(int& id)
{
	int ret = 0;
	if (mScreenMgr->getSceneType() == SCENE_ZUKAN_ITEM) {
		Morimura::TDItemScene* scene = static_cast<Morimura::TDItemScene*>(mScreenMgr->mBackupScene);
		if (scene) {
			Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
			ret                       = (obj) ? obj->checkRequest(id) : 0;
		}
	}
	return ret;
}

/**
 * @note Address: 0x803FF6E8
 * @note Size: 0x84
 */
int Game2DMgr::check_ZukanEnemyRequest(int& id)
{
	int ret = 0;
	if (mScreenMgr->getSceneType() == SCENE_ZUKAN_ENEMY) {
		Morimura::TDEnemyScene* scene = static_cast<Morimura::TDEnemyScene*>(mScreenMgr->mBackupScene);
		if (scene) {
			Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
			ret                       = (obj) ? obj->checkRequest(id) : 0;
		}
	}
	return ret;
}

/**
 * @note Address: 0x803FF76C
 * @note Size: 0x90
 */
int Game2DMgr::getZukanEnemyCurrSelectId()
{
	int ret = -1;
	if (mScreenMgr->getSceneType() == SCENE_ZUKAN_ENEMY) {
		Morimura::TDEnemyScene* scene = static_cast<Morimura::TDEnemyScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2195, scene);
		Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
		ret                       = (obj) ? obj->getCurrSelectId() : -1;
	}
	return ret;
}

/**
 * @note Address: 0x803FF7FC
 * @note Size: 0x90
 */
int Game2DMgr::getZukanItemCurrSelectId()
{
	int ret = -1;
	if (mScreenMgr->getSceneType() == SCENE_ZUKAN_ITEM) {
		Morimura::TDItemScene* scene = static_cast<Morimura::TDItemScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2210, scene);
		Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
		ret                       = (obj) ? obj->getCurrSelectId() : -1;
	}
	return ret;
}

/**
 * @note Address: 0x803FF88C
 * @note Size: 0xBC
 */
void Game2DMgr::requireZukanRequest()
{
	SceneType id = mScreenMgr->getSceneType();
	if (id == SCENE_ZUKAN_ITEM) {
		Morimura::TDItemScene* scene = static_cast<Morimura::TDItemScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2227, scene);
		Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
		if (obj) {
			obj->requireRequest();
		}
	} else if (id == SCENE_ZUKAN_ENEMY) {
		Morimura::TDEnemyScene* scene = static_cast<Morimura::TDEnemyScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2233, scene);
		Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
		if (obj) {
			obj->requireRequest();
		}
	}
}

/**
 * @note Address: 0x803FF948
 * @note Size: 0xBC
 */
void Game2DMgr::requireZukanEffectOff()
{
	SceneType id = mScreenMgr->getSceneType();
	if (id == SCENE_ZUKAN_ITEM) {
		Morimura::TDItemScene* scene = static_cast<Morimura::TDItemScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2247, scene);
		Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
		if (obj) {
			obj->requireEffectOff();
		}
	} else if (id == SCENE_ZUKAN_ENEMY) {
		Morimura::TDEnemyScene* scene = static_cast<Morimura::TDEnemyScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2253, scene);
		Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
		if (obj) {
			obj->requireEffectOff();
		}
	}
}

/**
 * @note Address: 0x803FFA04
 * @note Size: 0xE4
 */
bool Game2DMgr::isZukanEnlargedWindow()
{
	bool ret     = false;
	SceneType id = mScreenMgr->getSceneType();
	if (id == SCENE_ZUKAN_ITEM) {
		Morimura::TDItemScene* scene = static_cast<Morimura::TDItemScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2270, scene);
		Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
		ret                       = (obj) ? obj->isEnlargedWindow() : false;

	} else if (id == SCENE_ZUKAN_ENEMY) {
		Morimura::TDEnemyScene* scene = static_cast<Morimura::TDEnemyScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2277, scene);
		Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
		ret                       = (obj) ? obj->isEnlargedWindow() : false;
	}
	return ret;
}

/**
 * @note Address: 0x803FFAE8
 * @note Size: 0xE4
 */
bool Game2DMgr::isZukanMemoWindow()
{
	bool ret     = false;
	SceneType id = mScreenMgr->getSceneType();
	if (id == SCENE_ZUKAN_ITEM) {
		Morimura::TDItemScene* scene = static_cast<Morimura::TDItemScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2298, scene);
		Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
		ret                       = (obj) ? obj->isMemoWindow() : false;

	} else if (id == SCENE_ZUKAN_ENEMY) {
		Morimura::TDEnemyScene* scene = static_cast<Morimura::TDEnemyScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2305, scene);
		Morimura::TZukanBase* obj = static_cast<Morimura::TZukanBase*>(scene->mObject);
		ret                       = (obj) ? obj->isMemoWindow() : false;
	}
	return ret;
}

/**
 * @note Address: 0x803FFBCC
 * @note Size: 0xC4
 */
bool Game2DMgr::isAppearConfirmWindow()
{
	bool ret     = false;
	SceneType id = mScreenMgr->getSceneType();
	if (id == SCENE_ZUKAN_ITEM) {
		Morimura::TDItemScene* scene = static_cast<Morimura::TDItemScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2345, scene);
		ret = scene->isAppearConfirmWindow();
	} else if (id == SCENE_ZUKAN_ENEMY) {
		Morimura::TDEnemyScene* scene = static_cast<Morimura::TDEnemyScene*>(mScreenMgr->mBackupScene);
		P2ASSERTLINE(2352, scene);
		ret = scene->isAppearConfirmWindow();
	}
	return ret;
}

/**
 * @note Address: 0x803FFC90
 * @note Size: 0x9C
 */
bool Game2DMgr::open_ChallengeSelect(Morimura::DispMemberChallengeSelect& disp)
{
	SetSceneArg arg(SCENE_CHALLENGE_SELECT, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg)) {
		return mScreenMgr->startScene(nullptr);
	}
	return false;
}

/**
 * @note Address: 0x803FFD2C
 * @note Size: 0x6C
 */
int Game2DMgr::check_ChallengeSelect(int& ret1, int& ret2)
{
	ret1 = -1;
	ret2 = 0;

	Morimura::DispMemberChallengeSelect* disp = reinterpret_cast<Morimura::DispMemberChallengeSelect*>(mScreenMgr->getDispMember());

	if (disp->_1C == 3) {
		ret1 = disp->mStageNumber;
		ret2 = disp->mPlayType;
	}
	return disp->_1C;
}

/**
 * @note Address: 0x803FFD98
 * @note Size: 0x9C
 */
bool Game2DMgr::open_ChallengeResult(Morimura::DispMemberChallengeResult& disp)
{
	SetSceneArg arg(SCENE_CHALLENGE_RESULT, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg)) {
		return mScreenMgr->startScene(nullptr);
	}
	return false;
}

/**
 * @note Address: 0x803FFE34
 * @note Size: 0x34
 */
bool Game2DMgr::isEndChallengeResult()
{
	Morimura::DispMemberChallengeResult* disp = reinterpret_cast<Morimura::DispMemberChallengeResult*>(mScreenMgr->getDispMember());
	u8 ret                                    = (2 == disp->_10);
	return ret;
}

/**
 * @note Address: 0x803FFE68
 * @note Size: 0x9C
 */
bool Game2DMgr::open_VsSelect(Morimura::DispMemberVsSelect& disp)
{
	SetSceneArg arg(SCENE_VS_SELECT, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg)) {
		return mScreenMgr->startScene(nullptr);
	}
	return false;
}

/**
 * @note Address: 0x803FFF04
 * @note Size: 0x78
 */
u32 Game2DMgr::check_VsSelect(int& ret1, int& ret2, int& ret3)
{
	ret1 = -1;

	Morimura::DispMemberVsSelect* disp = reinterpret_cast<Morimura::DispMemberVsSelect*>(mScreenMgr->getDispMember());

	if (disp->mState == 3) {
		ret1 = disp->mSelectedStageIndex;
		ret2 = disp->mOlimarHandicap;
		ret3 = disp->mLouieHandicap;
	}
	return disp->mState;
}

/**
 * @note Address: 0x803FFF7C
 * @note Size: 0x9C
 */
bool Game2DMgr::open_HighScore(Morimura::DispMemberHighScore& disp)
{
	SetSceneArg arg(SCENE_HIGH_SCORE, reinterpret_cast<og::Screen::DispMemberBase*>(&disp), 0, true);
	if (mScreenMgr->setScene(arg)) {
		return mScreenMgr->startScene(nullptr);
	}
	return false;
}

/**
 * @note Address: 0x80400018
 * @note Size: 0x58
 */
bool Game2DMgr::isEndHighScore()
{
	bool ret;
	SceneType id = mScreenMgr->getSceneType();
	if (id == SCENE_HIGH_SCORE) {
		Morimura::DispMemberHighScore* disp = reinterpret_cast<Morimura::DispMemberHighScore*>(mScreenMgr->getDispMember());
		ret                                 = disp->_0C;
		disp->_0C                           = false;
		return ret;
	}
	return false;
}

/**
 * @note Address: 0x80400070
 * @note Size: 0x6C
 */
bool Game2DMgr::drawKanteiMsg(Graphics& gfx)
{
	bool ret     = false;
	SceneType id = mScreenMgr->getSceneType();
	if (id == SCENE_KANTEI_DEMO) {
		og::newScreen::KanteiDemo* scene = static_cast<og::newScreen::KanteiDemo*>(mScreenMgr->mBackupScene);
		og::newScreen::ObjKantei* obj    = static_cast<og::newScreen::ObjKantei*>(scene->mObjBase);
		if (obj) {
			obj->doDrawMsg(gfx);
		}
		return true;
	}
	return false;
}

/**
 * @note Address: 0x804000DC
 * @note Size: 0x8C
 */
bool Game2DMgr::checkDayEnd(f32 min) const
{
	if (!Game::gameSystem)
		return false;

	Game::TimeMgr* mgr = Game::gameSystem->mTimeMgr;
	f32 ratio          = mgr->getSunGaugeRatio();
	f32 factor         = mgr->mParms.mParms.mDayStartTime;
	return ((1.0f - ratio)
	        / (1.0f - ((mgr->mParms.mParms.mCountdownTime.mValue - factor) / (mgr->mParms.mParms.mDayEndTime.mValue - factor))))
	     < min;
}

} // namespace Screen
