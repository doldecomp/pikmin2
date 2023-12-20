#include "PSM/Demo.h"
#include "SoundID.h"
#include "utilityU.h"
#include "PSM/Scene.h"
#include "PSSystem/PSGame.h"
#include "PSM/ObjCalc.h"
#include "PSSystem/PSMainSide_Scene.h"
#include "PSSystem/PSSystemIF.h"

static inline bool streq(const char* a, const char* b)
{
	if (a == nullptr || b == nullptr)
		return false;
	if (strcmp(a, b) == 0)
		return true;
	else
		return false;
}

namespace PSM {

inline DemoInitiator::DemoInitiator(u8* byte, const char* name, u32& astID, char* buf)
    : mASTid(astID)
{
	P2ASSERTLINE(256, name);

	mName   = name;
	mASTid  = astID;
	mBuffer = buf;
	mByte   = byte;

	mSongChosen = false;
}

inline void DemoInitiator::setDefaultValues()
{
	P2ASSERTLINE(41, isInitialized());

	mASTid = -1;
	strcpy(mBuffer, "");
	*mByte = -1;
}

inline bool DemoInitiator::isInitialized() { return mByte && mName; }

/*
 * --INFO--
 * Address:	........
 * Size:	000078
 */
void DemoInitiator::equalSet(const char*, const char*, u8)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000074
 */
void DemoInitiator::equalSetStream(const char* buffer, u32 AST_ID, u8 byte)
{
	mSongChosen = false;
	bool check  = false;
	if (mByte && mName) {
		check = true;
	}
	P2ASSERTLINE(41, check);

	mASTid = AST_ID;
	strcpy((char*)buffer, "");
	*mByte = byte;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000080
 */
void DemoInitiator::equalSetEx(const char*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00007C
 */
void DemoInitiator::equalSetExStream(const char*, bool, u32, u8)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000058
 */
void DemoInitiator::is(const char*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00007C
 */
void DemoInitiator::numberSet(const char*, const char*, u8)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00004C
 */

inline void DemoInitiator::setDefault(const char* comp, u32 id, bool extraCondition)
{
	if (extraCondition && !mSongChosen && strcmp(mName, comp) == 0) {
		mSongChosen = true;
		mASTid      = id;
		*mByte      = -1;
		// OSReport("demo_arg is value: %lu\n", demo_arg);
	}
}

/*
 * --INFO--
 * Address:	80463FE8
 * Size:	00005C
 */
Demo::Demo()
{
	_18               = 0;
	mDoStartWithAudio = 1;
	mMovieStartSE     = (SoundID)-1;
	mMovieEndSE       = (SoundID)-1;
	mFuncptr          = nullptr;
};

/*
 * --INFO--
 * Address:	80464044
 * Size:	00020C
 */
void Demo::init(Vec* cam1pos, Vec* cam2pos, Mtx mtx, DemoArg arg)
{
	PSGame::SceneInfo* info = new PSGame::SceneInfo;
	info->setStageFlag(PSGame::SceneInfo::SCENEFLAG_Unk1, PSGame::SceneInfo::SFBS_2);
	info->mCameras         = 1;
	info->mCam1Position[0] = (Vector3f*)cam1pos;
	info->mCam2Position[0] = (Vector3f*)cam2pos;
	info->mCameraMtx[0]    = (Matrixf*)mtx;
	info->mSceneType       = 255;

	u8 unk                = 255;
	PSSystem::BgmSeq* seq = initiate(arg, &unk);
	mCurrentDemoName      = new char[strlen(arg.mName) + 1];
	strcpy(mCurrentDemoName, arg.mName);

	Scene_Demo* scene = new Scene_Demo(unk, info);
	P2ASSERTLINE(199, scene);

	PSSystem::SceneMgr* mgr = PSSystem::getSceneMgr();
	PSSystem::checkSceneMgr(mgr);
	PSM::Scene_Game* scene2 = static_cast<PSM::Scene_Game*>(mgr->getChildScene());
	scene2->adaptChildScene(scene);
	P2ASSERTLINE(203, scene);

	if (seq) {
		scene->appendSeq(seq);
	}

	initDemoScene(arg, scene);
	_18 = 1;
	demo1stLoadSync();
}

/*
 * --INFO--
 * Address:	80464250
 * Size:	0000EC
 */
void Demo::demo1stLoadSync()
{
	PSSystem::SceneMgr* mgr = PSSystem::getSceneMgr();
	PSSystem::checkSceneMgr(mgr);
	PSM::Scene_Game* scene = static_cast<PSM::Scene_Game*>(mgr->getChildScene());
	PSSystem::checkChildScene2(scene);
	scene->mChild->scene1stLoadSync();
}

/*
 * --INFO--
 * Address:	8046433C
 * Size:	000048
 */
void Demo::initDemoScene(PSM::DemoArg& arg, PSM::Scene_Demo* scene)
{
	if (!strcmp(arg.mName, "s21_dayend_takeoff")) {
		scene->mGate = 1;
	}
}

/*
 * --INFO--
 * Address:	80464384
 * Size:	001DA4
 */
PSSystem::BgmSeq* Demo::initiate(DemoArg demoArg, u8* unk)
{
	PSSystem::BgmSeq* seq;
	u32 AST_ID;
	char buffer[32];
	JAInter::SoundInfo audio_info = { 0x00000000, 0x7F, 0x03, 0, 0x3F800000, 0x3C000000 };

	seq       = nullptr;
	buffer[0] = '\0';
	AST_ID    = -1;

	DemoInitiator init = DemoInitiator(unk, demoArg.mName, AST_ID, buffer);
	init.setDefaultValues();

	init.setDefault("s02_dayend_result", 0xc0011012);
	init.setDefault("s01_dayend", demoArg.mBgmID);
	init.setDefault("s03_orimadown", 0xc0011005);
	init.setDefault("s05_pikminzero", 0xc0011006);
	init.setDefault("s11_dope_first_b", 0xc0011001);
	init.setDefault("s11_dope_first_r", 0xc0011001);
	init.setDefault("s11_dopebin_first_b", 0xc0011008);
	init.setDefault("s11_dopebin_first_r", 0xc0011008);

	if (!streq("s01_dayend", init.mName)) {
		bool is_key = demoArg.mCameraName && streq(demoArg.mCameraName, "key");

		init.setDefault("s17_suck_equipment", demoArg.mBgmID, !is_key);
		init.setDefault("s17_suck_equipment", 0xc0011007, is_key);

		init.setDefault("s22_cv_suck_equipment", demoArg.mBgmID, !is_key);
		init.setDefault("s22_cv_suck_equipment", 0xc0011007, is_key);

		init.setDefault("s10_suck_treasure", 0xc0011001, !is_key);
		init.setDefault("s10_suck_treasure", 0xc0011007, is_key);

		init.setDefault("s22_cv_suck_treasure", 0xc0011007, is_key);
		init.setDefault("s22_cv_suck_treasure", 0xc0011001, !is_key);
	}

	init.setDefault("s04_dayend_orimadown", 0xc001101d);
	init.setDefault("s06_dayend_pikminzero", 0xc001101d);

	init.setDefault("g1A_red_doping", 0xc0011009);
	init.setDefault("g1A_red_doping", 0xc0011009);
	init.setDefault("g1B_black_doping", 0xc0011047);
	init.setDefault("g02_boot_onyonR", 0xc001100c);
	init.setDefault("g1E_boot_onyonY", 0xc001100c);
	init.setDefault("g20_boot_onyonB", 0xc001100c);
	init.setDefault("g03_meet_redpikmin", 0xc001100d);
	init.setDefault("g1F_meet_yellowpikmin", 0xc001100d);
	init.setDefault("g21_meet_bluepikmin", 0xc001100d);
	init.setDefault("g24_meet_blackpikmin", 0xc001100d);
	init.setDefault("g27_meet_whitepikmin", 0xc001100d);
	init.setDefault("g33_camera_demo", 0xc0011024);

	if (PSMGetGameSceneA()->isCave()) {
		init.setDefault("s09_holein", 0xc0011046);
	} else {
		init.setDefault("s09_holein", 0xc0011026);
	}

	init.setDefault("s16_find_item_00", 0xc0011027);
	init.setDefault("s16_find_item_01", 0xc0011027);
	init.setDefault("s16_find_item_02", 0xc0011027);
	init.setDefault("s16_find_item_03", 0xc0011027);
	init.setDefault("s16_find_item_04", 0xc0011027);
	init.setDefault("s16_find_item_05", 0xc0011027);
	init.setDefault("s16_find_item_06", 0xc0011027);
	init.setDefault("s16_find_item_07", 0xc0011027);
	init.setDefault("s16_find_item_08", 0xc0011027);
	init.setDefault("s16_find_item_09", 0xc0011027);
	init.setDefault("s16_find_item_10", 0xc0011027);
	init.setDefault("s16_find_item_11", 0xc0011027);
	init.setDefault("s16_find_item_12", 0xc0011027);

	init.setDefault("s0C_cv_escape", 0xc0011028);

	init.setDefault("g01_pick_me", 0xc0011029);

	init.setDefault("g04_find_treasure", 0xc0011027);

	init.setDefault("g05_find_cave_f_01", 0xc0011029);
	init.setDefault("g05_find_cave_f_02", 0xc0011029);
	init.setDefault("g05_find_cave_f_03", 0xc0011029);
	init.setDefault("g05_find_cave_f_04", 0xc0011029);
	init.setDefault("g05_find_cave_l_01", 0xc0011029);
	init.setDefault("g05_find_cave_l_02", 0xc0011029);
	init.setDefault("g05_find_cave_l_03", 0xc0011029);
	init.setDefault("g05_find_cave_t_01", 0xc0011029);
	init.setDefault("g05_find_cave_t_02", 0xc0011029);
	init.setDefault("g05_find_cave_t_03", 0xc0011029);
	init.setDefault("g05_find_cave_y_01", 0xc0011029);
	init.setDefault("g05_find_cave_y_02", 0xc0011029);
	init.setDefault("g05_find_cave_y_03", 0xc0011029);
	init.setDefault("g05_find_cave_y_04", 0xc0011029);

	init.setDefault("g0A_cv_find_hole", 0xc0011029);
	init.setDefault("g0B_cv_find_fountain", 0xc0011029);

	init.setDefault("g18_find_gate", 0xc001102a);
	init.setDefault("g19_find_rock", 0xc0011029);
	init.setDefault("g2D_red_extract", 0xc0011027);
	init.setDefault("g2E_black_extract", 0xc0011027);
	init.setDefault("g34_yellow_extract", 0xc001102b);
	init.setDefault("g37_get_louie", 0xc0011027);
	init.setDefault("g38_find_whitepom", 0xc0011029);
	init.setDefault("g39_find_blackpom", 0xc0011029);

	init.setDefault("x01_gamestart", 0xc001102c);
	init.setDefault("x02_watch_red_pikmin", 0xc001102d);
	init.setDefault("x06_join", 0xc001102e);
	init.setDefault("x12_drain_water", 0xc001102a);
	init.setDefault("x10_find_yellow_onyon", 0xc001102f);
	init.setDefault("x11_find_blue_onyon", 0xc0011030);
	init.setDefault("x16_hiba", 0xc0011031);
	init.setDefault("x13_exp_leafchappy", 0xc001102a);
	init.setDefault("x20_blackman", 0xc0011032);

	init.setDefault("s13_pikmin_supply", 0xc0011033);
	init.setDefault("s0B_cv_coursein", 0xc0011036);
	init.setDefault("s0E_return_cave", 0xc0011037);

	init.setDefault("e00_E3_cavestart", 0xc0011039);

	init.setDefault("g07_cv_gamestart", 0xc001103a);
	init.setDefault("g08_first_return", 0xc001103b);
	init.setDefault("g09_first_sunset", 0xc0011033);
	init.setDefault("g16_100_pikmin", 0xc0011033);
	init.setDefault("g16_95_pikmin", 0xc0011033);
	init.setDefault("g26_inout_black", 0xc001104a);
	init.setDefault("g29_inout_white", 0xc0011048);
	init.setDefault("g2B_white_poison", 0xc0011031);
	init.setDefault("g2C_inout_red", 0xc0011033);
	init.setDefault("g36_find_louie", 0xc0011031);

	init.setDefault("x01_coursein_forest", 0xc0011034);
	init.setDefault("x01_coursein_yakushima", 0xc0011034);
	init.setDefault("x01_coursein_last", 0xc0011034);
	init.setDefault("x04_exp_y", 0xc0011049);
	init.setDefault("x05_louiestart", 0xc0011035);
	init.setDefault("x07_first_recovery", 0xc0011049);
	init.setDefault("x08_cv_suck_carcass", 0xc0011033);
	init.setDefault("x09_exp_detector", 0xc0011033);
	init.setDefault("x14_white_dig", 0xc0011033);

	init.setDefault("g32_get_map", 0xc0011048);
	init.setDefault("g35_president_gamestart", 0xc0011033);

	init.setDefault("x15_exp_x", 0xc0011033);
	init.setDefault("x17_join_guide", 0xc0011033);
	init.setDefault("x18_exp_pellet", 0xc0011033);

	init.setDefault("x03_find_red_onyon", 0xc001103c);

	if (streq("s02_dayend_result", init.mName)) {
		audio_info.mVolume.c -= 0xf;
	}
	// clang-format off
	if (streq("s10_suck_treasure",        init.mName) ||
		streq("s11_dope_first_b",         init.mName) ||
		streq("s11_dope_first_r",         init.mName) ||
		streq("s11_dopebin_first_b",      init.mName) ||
		streq("s11_dopebin_first_r",      init.mName) ||
		streq("s17_suck_equipment",       init.mName) ||
		streq("s22_cv_suck_equipment",    init.mName) ||
		streq("s22_cv_suck_treasure",     init.mName) ||
		streq("x19_vs_bedama",            init.mName))
	// clang-format on
	{
		mDoStartWithAudio = false;
		mMovieStartSE     = PSSE_EV_HOME_PELLET_BACUUM;
	} else if (streq("g2F_appear_hole", init.mName)) { // change BGM in challenge mode when hole/fountain appear
		mMovieStartSE = PSSE_SY_WORK_FINISH;
		mFuncptr      = PSChangeBgm_ChallengeGame;
	} else if (streq("g30_appear_fountain", init.mName)) {
		mFuncptr = PSChangeBgm_ChallengeGame;
	} else if (streq("x20_blackman", init.mName) || streq("x03_find_red_onyon", init.mName)) {
		mDoStartWithAudio = false;
	} else if (streq("s01_dayend", init.mName)) {
		switch ((u32)demoArg.mCameraName) {
		case 1:
			mMovieStartSE = PSSE_PL_DAYEND_KAISAN_LUI;
			break;
		case 2:
			mMovieStartSE = PSSE_PL_DAYEND_KAISAN_SHA;
			break;
		default:
		case 0:
			mMovieStartSE = PSSE_PL_DAYEND_KAISAN_ORI;
			break;
		}
	}

	if (streq("x20_blackman", init.mName)) {
		mMovieStartSE = PSSE_EN_TIRE_FALL;
	}

	if (AST_ID != -1) {
		PSGame::PikSceneMgr* scene_mgr = (PSGame::PikSceneMgr*)PSSystem::getSceneMgr();
		PSSystem::checkSceneMgr(scene_mgr);

		seq  = scene_mgr->newStreamBgm(AST_ID, audio_info);
		*unk = -1;
	} else if (buffer[0] != '\0') {
		PSGame::PikSceneMgr* scene_mgr = (PSGame::PikSceneMgr*)PSSystem::getSceneMgr();
		PSSystem::checkSceneMgr(scene_mgr);

		seq = scene_mgr->newBgmSeq(buffer, audio_info);
		P2ASSERTLINE(632, seq);
	}
	return seq;
}

/*
 * --INFO--
 * Address:	80466128
 * Size:	000184
 */
Demo::~Demo()
{
	becomeSceneCamera();
	PSSystem::Scene* scene = PSMGetSceneMgrCheck()->getChildScene();
	PSSystem::checkChildScene(scene);
	scene = scene->getChildScene();

	PSMGetSceneMgrCheck()->deleteScene(scene);

	delete mCurrentDemoName;
	delete scene;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000124
 */
void Demo::becomeDemoCamera()
{
	// not quite right but needs the checkGameScene inline for rodata purposes
	PSM::Scene_Game* scene = static_cast<PSM::Scene_Game*>(PSMGetChildScene());
	PSSystem::checkGameScene(scene);
	scene->becomeSceneCamera();
	PSSystem::SingletonBase<ObjCalcBase>::getInstance()->setMode(ObjCalcBase::OBJCALC_0);
}

/*
 * --INFO--
 * Address:	804662AC
 * Size:	0006C0
 */
void Demo::onDemoTop()
{
	Scene_Game* scene = static_cast<Scene_Game*>(PSMGetChildScene());
	PSSystem::checkChildScene2(scene);
	static_cast<Scene_Game*>(scene->getChildScene())->becomeSceneCamera();

	PSSystem::SingletonBase<ObjCalcBase>::getInstance()->setMode(ObjCalcBase::OBJCALC_1);

	static_cast<Scene_Game*>(PSMGetChildScene())->pauseOn_Demo();

	scene                     = static_cast<Scene_Game*>(PSMGetChildScene());
	PSSystem::EnvSeMgr* envse = scene->getEnvSe();
	if (envse) {
		envse->mReservator.mState = 0;
	}

	scene = static_cast<PSM::Scene_Game*>(PSMGetChildScene());
	PSSystem::checkGameScene(scene);
	char* name = mCurrentDemoName;
	if (!strcmp(name, "s01_dayend") || !strcmp(name, "s02_dayend_result") || !strcmp(name, "s04_dayend_orimadown")
	    || !strcmp(name, "s05_pikminzero") || !strcmp(name, "s06_dayend_pikminzero") || !strcmp(name, "s09_holein")
	    || !strcmp(name, "s0C_cv_escape") || !strcmp(name, "s12_cv_giveup") || !strcmp(name, "s21_dayend_takeoff")) {
		scene->mSeqMgr.stopAllSound(15);
		if (envse) {
			envse->off();
			if (scene->isCave() && !scene->isPollutUp()) {
				envse->on(PSSE_EV_POLUTION_MIX01, true);
				envse->on(PSSE_EV_POLUTION_MIX02, true);
			}
			envse->off(PSSE_MP_BIRD_NIGHT01_MIX, true);
			envse->off(PSSE_MP_BIRD_NIGHT02_MIX, true);
		}
	} else {
		scene->mSeqMgr.pauseOnAllSeq(PSSystem::SeqBase::MODE1);
		if (envse) {
			envse->setAllPauseFlag(2);
		}
	}

	if (!strcmp(name, "x19_vs_bedama")) {
		scene->mSeqMgr.stopAllSound(15);
	} else if (!strcmp(name, "x06_join")) {
		PSSystem::SceneMgr* mgr = PSMGetSceneMgrCheck();
		PSSystem::SeqBase* seq  = PSSystem::getSeqDataCheck(mgr, 1);
		P2ASSERTLINE(731, seq);
		seq->stopSeq(5);
	} else if (!strcmp(name, "x01_gamestart")) {
		PSGame::SoundTable::CategoryMgr* cat              = PSSystem::SingletonBase<PSGame::SoundTable::CategoryMgr>::getInstance();
		PSSystem::getSoundCategoryInfo(cat, 5)->mDisabled = true;
		PSSystem::getSoundCategoryInfo(cat, 2)->mDisabled = true;
	}

	if (mMovieStartSE != 0xffffffff) {
		PSSystem::spSysIF->playSystemSe(mMovieStartSE, 0);
	}

	PSSystem::checkChildScene2(scene);
	PSSystem::SeqBase* seq = scene->mChild->mSeqMgr.getFirstSeq();
	if (seq && mDoStartWithAudio) {
		PSSystem::checkChildScene2(scene);
		scene->mChild->startMainSeq();
	}
}

/*
 * --INFO--
 * Address:	8046696C
 * Size:	000104
 */
void Demo::becomeSceneCamera()
{
	static_cast<PSM::Scene_Game*>(PSMGetChildScene())->becomeSceneCamera();
	PSSystem::SingletonBase<ObjCalcBase>::getInstance()->setMode(ObjCalcBase::OBJCALC_0);
}

/*
 * --INFO--
 * Address:	80466A70
 * Size:	0000FC
 */
void Demo::onDemoFadeoutStart(u32 flag)
{
	PSSystem::SceneMgr* mgr = PSSystem::getSceneMgr();
	PSSystem::checkSceneMgr(mgr);
	PSM::Scene_Game* scene = static_cast<PSM::Scene_Game*>(mgr->getChildScene());
	PSSystem::stopChildSeq(scene, flag - 2);
}

/*
 * --INFO--
 * Address:	80466B6C
 * Size:	000664
 */
void Demo::onDemoEnd()
{
	becomeSceneCamera();

	static_cast<PSM::Scene_Game*>(PSMGetChildScene())->pauseOff_Demo();

	SceneBase* scene = static_cast<PSM::SceneBase*>(PSMGetSceneMgrCheck()->getChildScene());
	PSSystem::checkGameScene(scene);
	const char* name          = mCurrentDemoName;
	PSSystem::EnvSeMgr* envse = scene->getEnvSe();
	if (envse) {
		if (!strcmp(name, "s01_dayend") || !strcmp(name, "s02_dayend_result") || !strcmp(name, "s04_dayend_orimadown")
		    || !strcmp(name, "s05_pikminzero") || !strcmp(name, "s06_dayend_pikminzero") || !strcmp(name, "s09_holein")
		    || !strcmp(name, "s0C_cv_escape") || !strcmp(name, "s12_cv_giveup") || !strcmp(name, "s21_dayend_takeoff")) {
			envse->off();
			if (static_cast<Scene_Game*>(scene)->isCave() && !static_cast<Scene_Cave*>(scene)->isPollutUp()) {
				envse->on(PSSE_EV_POLUTION_MIX01, true);
				envse->on(PSSE_EV_POLUTION_MIX02, true);
			}
			envse->setAllPauseFlag(false);
		} else {
			envse->reservePauseOff();
		}
	}

	if (!strcmp(name, "x06_join")) {
		static_cast<PSM::Scene_Game*>(PSMGetChildScene())->startMainSeq();
	} else if (!strcmp(name, "g03_meet_redpikmin")) {
		PSSystem::SceneMgr* mgr = PSMGetSceneMgrCheck();
		PSSystem::SeqBase* seq  = PSSystem::getSeqDataCheck(mgr, 1);
		P2ASSERTLINE(834, seq);
		seq->startSeq();
	} else if (!strcmp(name, "x20_blackman")) {
		PSSystem::SceneMgr* mgr = PSMGetSceneMgrCheck();
		PSSystem::SeqBase* seq  = PSSystem::getSeqDataCheck(mgr, 1);
		P2ASSERTLINE(838, seq);
		seq->startSeq();
	}
	scene->mSeqMgr.reservePauseOffAllSeq();

	if (mFuncptr) {
		mFuncptr();
	}

	if (mMovieEndSE != 0xffffffff) {
		PSSystem::spSysIF->playSystemSe(mMovieEndSE, 0);
	}

	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, lbl_8049D080@ha
	stw      r0, 0x24(r1)
	stmw     r27, 0xc(r1)
	mr       r29, r3
	addi     r31, r4, lbl_8049D080@l
	lwz      r0, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_80466BA8
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1d3
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466BA8:
	lwz      r28, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r28, 0
	bne      lbl_80466BC8
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1dc
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466BC8:
	lwz      r0, 4(r28)
	cmplwi   r0, 0
	bne      lbl_80466BE8
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x14
	li       r4, 0xcf
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466BE8:
	lwz      r3, 4(r28)
	lwz      r28, 4(r3)
	cmplwi   r28, 0
	bne      lbl_80466C0C
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x38
	li       r4, 0xd1
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466C0C:
	mr       r3, r28
	lwz      r12, 0(r28)
	lwz      r12, 0x3c(r12)
	mtctr    r12
	bctrl
	lwz      r0,
"sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13) cmplwi
r0, 0 bne      lbl_80466C40 addi     r3, r31, 0x86c addi     r5, r31, 0x14 li
r4, 0x89 crclr    6 bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466C40:
	lwz      r3,
"sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13) li r4, 0
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	lwz      r0, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_80466C78
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1d3
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466C78:
	lwz      r28, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r28, 0
	bne      lbl_80466C98
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1dc
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466C98:
	lwz      r0, 4(r28)
	cmplwi   r0, 0
	bne      lbl_80466CB8
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x14
	li       r4, 0xcf
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466CB8:
	lwz      r3, 4(r28)
	lwz      r28, 4(r3)
	cmplwi   r28, 0
	bne      lbl_80466CDC
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x38
	li       r4, 0xd1
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466CDC:
	mr       r3, r28
	lwz      r12, 0(r28)
	lwz      r12, 0x50(r12)
	mtctr    r12
	bctrl
	lwz      r0, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_80466D10
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1d3
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466D10:
	lwz      r28, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r28, 0
	bne      lbl_80466D30
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1dc
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466D30:
	lwz      r0, 4(r28)
	cmplwi   r0, 0
	bne      lbl_80466D50
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x14
	li       r4, 0xcf
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466D50:
	lwz      r3, 4(r28)
	lwz      r30, 4(r3)
	cmplwi   r30, 0
	bne      lbl_80466D74
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x38
	li       r4, 0xd1
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466D74:
	lwz      r12, 0(r30)
	mr       r3, r30
	lwz      r12, 0x40(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80466DA4
	addi     r3, r31, 0x858
	addi     r5, r31, 0x14
	li       r4, 0x177
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466DA4:
	lwz      r12, 0(r30)
	mr       r3, r30
	lwz      r28, 0x28(r29)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	or.      r27, r3, r3
	beq      lbl_80466EF0
	mr       r3, r28
	addi     r4, r31, 0x94
	bl       strcmp
	cmpwi    r3, 0
	beq      lbl_80466E78
	mr       r3, r28
	addi     r4, r31, 0x80
	bl       strcmp
	cmpwi    r3, 0
	beq      lbl_80466E78
	mr       r3, r28
	addi     r4, r31, 0x168
	bl       strcmp
	cmpwi    r3, 0
	beq      lbl_80466E78
	mr       r3, r28
	addi     r4, r31, 0xb0
	bl       strcmp
	cmpwi    r3, 0
	beq      lbl_80466E78
	mr       r3, r28
	addi     r4, r31, 0x180
	bl       strcmp
	cmpwi    r3, 0
	beq      lbl_80466E78
	mr       r3, r28
	addi     r4, r31, 0x26c
	bl       strcmp
	cmpwi    r3, 0
	beq      lbl_80466E78
	mr       r3, r28
	addi     r4, r31, 0x37c
	bl       strcmp
	cmpwi    r3, 0
	beq      lbl_80466E78
	mr       r3, r28
	addi     r4, r31, 0x878
	bl       strcmp
	cmpwi    r3, 0
	beq      lbl_80466E78
	mr       r3, r28
	addi     r4, r31, 0x5c
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_80466EE8

lbl_80466E78:
	mr       r3, r27
	bl       off__Q28PSSystem8EnvSeMgrFv
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x58(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80466ED8
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x6c(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80466ED8
	mr       r3, r27
	li       r4, 0x3079
	li       r5, 1
	bl       on__Q28PSSystem8EnvSeMgrFUlb
	mr       r3, r27
	li       r4, 0x307a
	li       r5, 1
	bl       on__Q28PSSystem8EnvSeMgrFUlb

lbl_80466ED8:
	mr       r3, r27
	li       r4, 0
	bl       setAllPauseFlag__Q28PSSystem8EnvSeMgrFUc
	b        lbl_80466EF0

lbl_80466EE8:
	mr       r3, r27
	bl       reservePauseOff__Q28PSSystem8EnvSeMgrFv

lbl_80466EF0:
	mr       r3, r28
	addi     r4, r31, 0x5a8
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_80466FA0
	lwz      r0, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_80466F24
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1d3
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466F24:
	lwz      r28, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r28, 0
	bne      lbl_80466F44
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1dc
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466F44:
	lwz      r0, 4(r28)
	cmplwi   r0, 0
	bne      lbl_80466F64
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x14
	li       r4, 0xcf
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466F64:
	lwz      r3, 4(r28)
	lwz      r28, 4(r3)
	cmplwi   r28, 0
	bne      lbl_80466F88
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x38
	li       r4, 0xd1
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466F88:
	mr       r3, r28
	lwz      r12, 0(r28)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_80467184

lbl_80466FA0:
	mr       r3, r28
	addi     r4, r31, 0x1ec
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_80467094
	lwz      r0, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_80466FD4
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1d3
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466FD4:
	lwz      r28, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r28, 0
	bne      lbl_80466FF4
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1dc
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80466FF4:
	lwz      r0, 4(r28)
	cmplwi   r0, 0
	bne      lbl_80467014
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x14
	li       r4, 0xc7
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80467014:
	lwz      r3, 4(r28)
	lwz      r28, 4(r3)
	cmplwi   r28, 0
	bne      lbl_80467038
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1e5
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80467038:
	addi     r3, r28, 0x10
	li       r4, 1
	bl       getSeq__Q28PSSystem6SeqMgrFUl
	or.      r28, r3, r3
	bne      lbl_80467060
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1e7
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80467060:
	cmplwi   r28, 0
	bne      lbl_8046707C
	addi     r3, r31, 0
	addi     r5, r31, 0x14
	li       r4, 0x342
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8046707C:
	mr       r3, r28
	lwz      r12, 0x10(r28)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	b        lbl_80467184

lbl_80467094:
	mr       r3, r28
	addi     r4, r31, 0x610
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_80467184
	lwz      r0, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_804670C8
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1d3
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_804670C8:
	lwz      r28, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r28, 0
	bne      lbl_804670E8
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1dc
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_804670E8:
	lwz      r0, 4(r28)
	cmplwi   r0, 0
	bne      lbl_80467108
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x14
	li       r4, 0xc7
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80467108:
	lwz      r3, 4(r28)
	lwz      r28, 4(r3)
	cmplwi   r28, 0
	bne      lbl_8046712C
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1e5
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8046712C:
	addi     r3, r28, 0x10
	li       r4, 1
	bl       getSeq__Q28PSSystem6SeqMgrFUl
	or.      r28, r3, r3
	bne      lbl_80467154
	addi     r3, r31, 0x20
	addi     r5, r31, 0x14
	li       r4, 0x1e7
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80467154:
	cmplwi   r28, 0
	bne      lbl_80467170
	addi     r3, r31, 0
	addi     r5, r31, 0x14
	li       r4, 0x346
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80467170:
	mr       r3, r28
	lwz      r12, 0x10(r28)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl

lbl_80467184:
	addi     r3, r30, 0x10
	bl       reservePauseOffAllSeq__Q28PSSystem6SeqMgrFv
	lwz      r12, 0x24(r29)
	cmplwi   r12, 0
	beq      lbl_804671A0
	mtctr    r12
	bctrl

lbl_804671A0:
	lwz      r4, 0x20(r29)
	addis    r0, r4, 1
	cmplwi   r0, 0xffff
	beq      lbl_804671BC
	lwz      r3, spSysIF__8PSSystem@sda21(r13)
	li       r5, 0
	bl       playSystemSe__Q28PSSystem5SysIFFUlUl

lbl_804671BC:
	lmw      r27, 0xc(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	804671D0
 * Size:	000268
 */
void Demo::onMessageEnd(int id)
{
	char* name = mCurrentDemoName;
	if (!strcmp(name, "x01_gamestart")) {
		// Unmute enemies and pikmin after first text box of opening cutscene
		PSGame::SoundTable::CategoryMgr* cat              = PSSystem::SingletonBase<PSGame::SoundTable::CategoryMgr>::getInstance();
		PSSystem::getSoundCategoryInfo(cat, 5)->mDisabled = false;
		PSSystem::getSoundCategoryInfo(cat, 2)->mDisabled = false;

		PSSystem::SceneMgr* mgr = PSSystem::getSceneMgr();
		PSSystem::checkSceneMgr(mgr);
		PSM::Scene_Game* scene = static_cast<PSM::Scene_Game*>(mgr->getChildScene());
		PSSystem::checkChildScene(scene);
		scene->mChild->stopMainSeq(5);
	} else if (!strcmp(name, "x03_find_red_onyon") && id == 0) {
		// After the first text box of find red onion cutscene, let the music start playing
		PSSystem::SceneMgr* mgr = PSSystem::getSceneMgr();
		PSSystem::checkSceneMgr(mgr);
		PSM::Scene_Game* scene = static_cast<PSM::Scene_Game*>(mgr->getChildScene());
		PSSystem::checkChildScene(scene);
		scene->mChild->startMainSeq();
	}
}

} // namespace PSM

/*
 * --INFO--
 * Address:	80467438
 * Size:	0000E4
 */
void PSMCancelToPauseOffMainBgm()
{
	PSSystem::SceneMgr* mgr = PSSystem::getSceneMgr();
	PSSystem::checkSceneMgr(mgr);
	PSM::Scene_Game* scene = static_cast<PSM::Scene_Game*>(mgr->getChildScene());
	scene->mSeqMgr.cancelPauseOffAllSeq();
	PSSystem::EnvSeMgr* se = scene->getEnvSe();
	if (se) {
		se->mReservator.mState = 0;
	}
}

/*
 * --INFO--
 * Address:	8046751C
 * Size:	0000EC
 */
PSM::Scene_Game* PSMGetGameSceneA()
{
	PSSystem::SceneMgr* mgr = PSSystem::getSceneMgr();
	PSSystem::checkSceneMgr(mgr);
	PSM::Scene_Game* scene = static_cast<PSM::Scene_Game*>(mgr->getChildScene());
	PSSystem::checkGameScene(scene);
	return scene;
}
