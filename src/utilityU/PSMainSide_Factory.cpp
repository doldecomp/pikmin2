#include "PSGame/EnvSe.h"
#include "PSGame/PikScene.h"
#include "PSM/BossSeq.h"
#include "PSM/ObjBase.h"
#include "PSM/Scene.h"
#include "JSystem/JAudio/JALCalc.h"
#include "PSM/Se.h"
#include "PSM/ObjCalc.h"
#include "PSSystem/PSSystemIF.h"
#include "PSSystem/EnvSeBase.h"
#include "PSAutoBgm/AutoBgm.h"
#include "PSSystem/PSSeq.h"
#include "Game/Navi.h"
#include "PSM/DirectorMgr.h"
#include "PSSystem/PSMainSide_Scene.h"
#include "PSAutoBgm/MeloArr.h"
#include "nans.h"

static const u32 padding[] = { 0, 0, 0 };

/*
    Generated from dpostproc

    .section .ctors, "wa"  # 0x80472F00 - 0x804732C0
        .4byte __sinit_PSMainSide_Factory_cpp

    .section .rodata  # 0x804732E0 - 0x8049E220
    .global lbl_8049CE68
    lbl_8049CE68:
        .4byte 0x00000000
        .4byte 0x00000000
        .4byte 0x00000000
    .global lbl_8049CE74
    lbl_8049CE74:
        .4byte 0x50534D61
        .4byte 0x696E5369
        .4byte 0x64655F46
        .4byte 0x6163746F
        .4byte 0x72792E63
        .4byte 0x70700000
    .global lbl_8049CE8C
    lbl_8049CE8C:
        .asciz "P2Assert"
        .skip 3
        .4byte 0x50534761
        .4byte 0x6D652E68
        .4byte 0x00000000
        .4byte 0x50535363
        .4byte 0x656E652E
        .4byte 0x68000000
        .4byte 0x67657420
        .4byte 0x736F756E
        .4byte 0x64207363
        .4byte 0x656E6520
        .4byte 0x61740A69
        .4byte 0x6E76616C
        .4byte 0x69642074
        .4byte 0x696D6D69
        .4byte 0x6E670A00
        .4byte 0x50534D61
        .4byte 0x696E5369
        .4byte 0x64655F53
        .4byte 0x63656E65
        .4byte 0x2E680000
        .4byte 0x6B75726F
        .4byte 0x5F706F73
        .4byte 0x742E626D
        .4byte 0x73000000
        .4byte 0x5053436F
        .4byte 0x6D6D6F6E
        .4byte 0x2E680000
        .4byte 0x6D5F626F
        .4byte 0x73732E62
        .4byte 0x6D730000
        .4byte 0x6C5F626F
        .4byte 0x73732E62
        .4byte 0x6D730000
        .4byte 0x62617474
        .4byte 0x6C655F74
        .4byte 0x2E626D73
        .4byte 0x00000000
        .4byte 0x44BB8000
        .4byte 0x43EF8000
        .4byte 0x4430C000
        .4byte 0x444A0000
        .float 1.0
        .4byte 0x44BB8000
        .4byte 0x43EF8000
        .4byte 0x4430C000
        .4byte 0x444A0000
        .float 1.0
        .4byte 0x44BB8000
        .4byte 0x43BD8000
        .4byte 0x4410C000
        .4byte 0x4480E000
        .4byte 0x3F666666
        .4byte 0x44BB8000
        .4byte 0x43EF8000
        .4byte 0x4430C000
        .4byte 0x444A0000
        .float 1.0
        .4byte 0x44BB8000
        .4byte 0x43BD8000
        .4byte 0x43EF8000
        .4byte 0x448D6000
        .float 1.0
        .4byte 0x97909094
        .4byte 0x88CA9275
        .4byte 0x41766F69
        .4byte 0x64000000

    .section .data, "wa"  # 0x8049E220 - 0x804EFC20
    .global lbl_804EE158
    lbl_804EE158:
        .4byte 0x00000000
        .4byte 0x00000000
        .4byte 0x00000000
    .global lbl_804EE164
    lbl_804EE164:
        .4byte lbl_8045A578
        .4byte lbl_8045A5CC
        .4byte lbl_8045A5CC
        .4byte lbl_8045A5CC
        .4byte lbl_8045A5CC
        .4byte lbl_8045A618
        .4byte lbl_8045A618
        .4byte lbl_8045A618
        .4byte lbl_8045A618
        .4byte lbl_8045A618
        .4byte lbl_8045A618
        .4byte lbl_8045A5F4
        .4byte lbl_8045A5F4
        .4byte lbl_8045A5A0
        .4byte lbl_8045A618
        .4byte lbl_8045A618
        .4byte lbl_8045A618
        .4byte lbl_8045A618
        .4byte lbl_8045A618
        .4byte lbl_8045A618
        .4byte lbl_8045A5CC
    .global lbl_804EE1B8
    lbl_804EE1B8:
        .4byte lbl_8045AB94
        .4byte lbl_8045AC24
        .4byte lbl_8045ACB4
        .4byte lbl_8045AD88
        .4byte lbl_8045AE5C
        .4byte lbl_8045AF30
        .4byte lbl_8045B004
        .4byte lbl_8045B0D8
        .4byte lbl_8045B1AC
        .4byte lbl_8045B280
        .4byte lbl_8045B354
        .4byte lbl_8045B428
        .4byte lbl_8045B4FC
        .4byte lbl_8045B5D0
        .4byte lbl_8045B6A4
    .global lbl_804EE1F4
    lbl_804EE1F4:
        .4byte lbl_8045C8C8
        .4byte lbl_8045C820
        .4byte lbl_8045C8C8
        .4byte lbl_8045C898
        .4byte lbl_8045C8C8
        .4byte lbl_8045C898
        .4byte lbl_8045C898
        .4byte lbl_8045C898
        .4byte lbl_8045C838
        .4byte lbl_8045C850
        .4byte lbl_8045C868
        .4byte lbl_8045C880
        .4byte lbl_8045C8C8
    .global __vt__Q23PSM10BigBossSeq
    __vt__Q23PSM10BigBossSeq:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM10BigBossSeqFv
        .4byte init__Q28PSSystem11DirectedBgmFv
        .4byte scene1st__Q28PSSystem7SeqBaseFPQ28PSSystem11TaskChecker
        .4byte startSeq__Q28PSSystem10JumpBgmSeqFv
        .4byte stopSeq__Q28PSSystem11DirectedBgmFUl
        .4byte pauseOn__Q28PSSystem7SeqBaseFQ38PSSystem7SeqBase9PauseMode
        .4byte pauseOff__Q28PSSystem7SeqBaseFv
        .4byte getCastType__Q28PSSystem10JumpBgmSeqFv
        .4byte getSeqType__Q28PSSystem6BgmSeqFv
        .4byte exec__Q23PSM13MiddleBossSeqFv
        .4byte onPlayingFrame__Q28PSSystem10JumpBgmSeqFv
        .4byte isPlaying__Q28PSSystem7SeqBaseFv
        .4byte seqLoadAfter__Q28PSSystem7SeqBaseFv
        .4byte getHandleP__Q28PSSystem6BgmSeqFv
        .4byte setConfigVolume__Q28PSSystem7SeqBaseFv
        .4byte newSeqTrackRoot__Q28PSSystem10JumpBgmSeqFv
        .4byte
   newSeqTrackChild__Q28PSSystem11DirectedBgmFUcRQ28PSSystem12SeqTrackRoot
        .4byte getSeqStartPoint__Q28PSSystem10JumpBgmSeqFv
        .4byte requestJumpBgmQuickly__Q23PSM13MiddleBossSeqFUs
        .4byte requestJumpBgmOnBeat__Q23PSM13MiddleBossSeqFUs
        .4byte requestJumpBgmEveryBeat__Q23PSM13MiddleBossSeqFUs
        .4byte outputJumpRequest__Q28PSSystem10JumpBgmSeqFv
        .4byte onJump__Q23PSM10BigBossSeqFUs
        .4byte jumpCheck__Q23PSM10BigBossSeqFUs
    .global __vt__Q23PSM13MiddleBossSeq
    __vt__Q23PSM13MiddleBossSeq:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM13MiddleBossSeqFv
        .4byte init__Q28PSSystem11DirectedBgmFv
        .4byte scene1st__Q28PSSystem7SeqBaseFPQ28PSSystem11TaskChecker
        .4byte startSeq__Q28PSSystem10JumpBgmSeqFv
        .4byte stopSeq__Q28PSSystem11DirectedBgmFUl
        .4byte pauseOn__Q28PSSystem7SeqBaseFQ38PSSystem7SeqBase9PauseMode
        .4byte pauseOff__Q28PSSystem7SeqBaseFv
        .4byte getCastType__Q28PSSystem10JumpBgmSeqFv
        .4byte getSeqType__Q28PSSystem6BgmSeqFv
        .4byte exec__Q23PSM13MiddleBossSeqFv
        .4byte onPlayingFrame__Q28PSSystem10JumpBgmSeqFv
        .4byte isPlaying__Q28PSSystem7SeqBaseFv
        .4byte seqLoadAfter__Q28PSSystem7SeqBaseFv
        .4byte getHandleP__Q28PSSystem6BgmSeqFv
        .4byte setConfigVolume__Q28PSSystem7SeqBaseFv
        .4byte newSeqTrackRoot__Q28PSSystem10JumpBgmSeqFv
        .4byte
   newSeqTrackChild__Q28PSSystem11DirectedBgmFUcRQ28PSSystem12SeqTrackRoot
        .4byte getSeqStartPoint__Q28PSSystem10JumpBgmSeqFv
        .4byte requestJumpBgmQuickly__Q23PSM13MiddleBossSeqFUs
        .4byte requestJumpBgmOnBeat__Q23PSM13MiddleBossSeqFUs
        .4byte requestJumpBgmEveryBeat__Q23PSM13MiddleBossSeqFUs
        .4byte outputJumpRequest__Q28PSSystem10JumpBgmSeqFv
        .4byte onJump__Q23PSM13MiddleBossSeqFUs
        .4byte jumpCheck__Q23PSM13MiddleBossSeqFUs
    .global __vt__Q23PSM8SceneMgr
    __vt__Q23PSM8SceneMgr:
        .4byte 0
        .4byte 0
        .4byte exec__Q28PSSystem8SceneMgrFv
        .4byte
   newAndSetCurrentScene__Q26PSGame11PikSceneMgrFRQ26PSGame9SceneInfo .4byte
   newAndSetGlobalScene__Q26PSGame11PikSceneMgrFv .4byte
   newMainBgm__Q23PSM8SceneMgrFPCcRQ27JAInter9SoundInfo .4byte
   newDirectedBgm__Q23PSM8SceneMgrFPCcRQ27JAInter9SoundInfo .4byte
   newAutoBgm__Q23PSM8SceneMgrFPCcPCcRQ27JAInter9SoundInfoQ210JADUtility10AccessModeRQ26PSGame9SceneInfoPQ28PSSystem15DirectorMgrBase
        .4byte curSceneIsBigBossFloor__Q23PSM8SceneMgrFv
        .4byte newGameScene__Q23PSM8SceneMgrFUcPQ26PSGame9SceneInfo
    .global __vt__Q28PSSystem8SceneMgr
    __vt__Q28PSSystem8SceneMgr:
        .4byte 0
        .4byte 0
        .4byte exec__Q28PSSystem8SceneMgrFv
    .global __vt__Q23PSM15EnvSeObjBuilder
    __vt__Q23PSM15EnvSeObjBuilder:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM15EnvSeObjBuilderFv
        .4byte onBuild__Q23PSM15EnvSeObjBuilderFPQ28PSSystem9EnvSeBase
        .4byte newSeObj__Q23PSM15EnvSeObjBuilderFUlf3Vec
    .global __vt__Q23PSM24EnvSe_Perspective_AvoidY
    __vt__Q23PSM24EnvSe_Perspective_AvoidY:
        .4byte 0
        .4byte 0
        .4byte exec__Q28PSSystem9EnvSeBaseFv
        .4byte play__Q23PSM24EnvSe_Perspective_AvoidYFv
        .4byte getCastType__Q23PSM24EnvSe_Perspective_AvoidYFv
        .4byte setPanAndDolby__Q28PSSystem9EnvSeBaseFP8JAISound
    .global __vt__Q23PSM12Env_Pollutin
    __vt__Q23PSM12Env_Pollutin:
        .4byte 0
        .4byte 0
        .4byte exec__Q28PSSystem9EnvSeBaseFv
        .4byte play__Q23PSM12Env_PollutinFv
        .4byte getCastType__Q23PSM12Env_PollutinFv
        .4byte setPanAndDolby__Q26PSGame13EnvSe_AutoPanFP8JAISound

    .section .sbss # 0x80514D80 - 0x80516360
    .global lbl_80516308
    lbl_80516308:
        .skip 0x4
    .global lbl_8051630C
    lbl_8051630C:
        .skip 0x4

    .section .sdata2, "a"     # 0x80516360 - 0x80520E40
    .global lbl_80520C20
    lbl_80520C20:
        .float 1.0
    .global lbl_80520C24
    lbl_80520C24:
        .4byte 0x00000000
    .global lbl_80520C28
    lbl_80520C28:
        .4byte 0x43C80000
    .global lbl_80520C2C
    lbl_80520C2C:
        .4byte 0x43EF8000
    .global lbl_80520C30
    lbl_80520C30:
        .4byte 0x3AF330E5
    .global lbl_80520C34
    lbl_80520C34:
        .4byte 0x3A603CEC
    .global lbl_80520C38
    lbl_80520C38:
        .float 0.5
    .global lbl_80520C3C
    lbl_80520C3C:
        .4byte 0x43BD8000
    .global lbl_80520C40
    lbl_80520C40:
        .4byte 0x3E8F5C29
    .global lbl_80520C44
    lbl_80520C44:
        .4byte 0x3F19999A
    .global lbl_80520C48
    lbl_80520C48:
        .4byte 0x461C4000
        .4byte 0x00000000
*/

namespace PSM {

/**
 * @note Address: 0x80459BD4
 * @note Size: 0x274
 */
JAISound* Env_Pollutin::play()
{
	EnvSeBase::play();
	_28 = 1.0f;
	if (_50 != 1.0f) {
		P2ASSERTLINE(79, _50 < 1.0f);

		MiddleBossSeq* seq = PSMGetMiddleBossSeq();
		if (seq && *seq->getHandleP()) {
			JAISound** se = seq->getHandleP();
			f32 vol       = (*se)->getVolume(0);
			if (vol > 0.0f) {
				_28 = JALCalc::linearTransform(vol, 0.0f, 1.0f, 1.0f, _50, true);
			}
		} else {
			PSM::Scene_Ground* scene = static_cast<PSM::Scene_Ground*>(PSMGetChildScene());
			PSSystem::checkGameScene(scene);
			PSSystem::SeqBase* seq = scene->getSeqMgr()->getSeq(1);
			if (seq && *seq->getHandleP() && !strcmp(seq->mBmsFileName, "kuro_post.bms")) {
				_28 = _50;
			}
		}
	}

	return mSound;
}

/**
 * @note Address: 0x80459E48
 * @note Size: 0x280
 */
JAISound* EnvSe_Perspective_AvoidY::play()
{
	bool hasNavi     = true;
	Game::Navi* navi = Game::naviMgr->getActiveNavi();
	if (!navi) {
		hasNavi = false;
	}
	Scene_Game* scene = PSMGetGameScene();
	if (hasNavi && scene->mPersEnvMgr && scene->mPersEnvMgr->playOk(this)) {
		mVec.y       = _48 + navi->getPosition().y;
		Vector3f pos = navi->getPosition();
		f32 x        = mVec.x - pos.x;
		f32 z        = mVec.z - pos.z;
		f32 dist     = (x * x) + (z * z);
		dist         = _sqrtf(dist);
		int players  = PSSystem::SingletonBase<ObjCalcBase>::getInstance()->getPlayerNo(mVec);
		PSSystem::spSysIF->startSoundVecT(mSoundID, &mSound, &mVec, 0, 0, players);
		f32 calc;
		if (dist < mInfo._08) {
			calc = JALCalc::linearTransform(dist, mInfo._04, mInfo._08, 0.0f, mInfo._0C, true);
		} else if (dist < mInfo._08) {
			calc = mInfo._0C;
		} else {
			calc = JALCalc::linearTransform(dist, mInfo._08, mInfo._00, mInfo._0C, 0.0f, true);
		}
		_28 = calc;
	}

	return mSound;
	/*
	stwu     r1, -0x60(r1)
	mflr     r0
	stw      r0, 0x64(r1)
	stfd     f31, 0x50(r1)
	psq_st   f31, 88(r1), 0, qr0
	stmw     r27, 0x3c(r1)
	mr       r31, r3
	lis      r4, lbl_8049CE68@ha
	lwz      r3, naviMgr__4Game@sda21(r13)
	addi     r30, r4, lbl_8049CE68@l
	li       r28, 1
	bl       getActiveNavi__Q24Game7NaviMgrFv
	or.      r27, r3, r3
	bne      lbl_80459E84
	li       r28, 0

lbl_80459E84:
	lwz      r0, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_80459EA4
	addi     r3, r30, 0x30
	addi     r5, r30, 0x24
	li       r4, 0x1d3
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80459EA4:
	lwz      r29, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r29, 0
	bne      lbl_80459EC4
	addi     r3, r30, 0x30
	addi     r5, r30, 0x24
	li       r4, 0x1dc
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80459EC4:
	lwz      r0, 4(r29)
	cmplwi   r0, 0
	bne      lbl_80459EE4
	addi     r3, r30, 0x3c
	addi     r5, r30, 0x24
	li       r4, 0xcf
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80459EE4:
	lwz      r3, 4(r29)
	lwz      r29, 4(r3)
	cmplwi   r29, 0
	bne      lbl_80459F08
	addi     r3, r30, 0x3c
	addi     r5, r30, 0x48
	li       r4, 0xd1
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80459F08:
	mr       r3, r29
	lwz      r12, 0(r29)
	lwz      r12, 0x40(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80459F28
	b        lbl_80459F2C

lbl_80459F28:
	li       r29, 0

lbl_80459F2C:
	clrlwi.  r0, r28, 0x18
	lwz      r3, 0x58(r29)
	beq      lbl_8045A0A8
	cmplwi   r3, 0
	beq      lbl_8045A0A8
	mr       r4, r31
	bl       playOk__Q23PSM14PersEnvManagerFPQ23PSM24EnvSe_Perspective_AvoidY
	clrlwi.  r0, r3, 0x18
	beq      lbl_8045A0A8
	mr       r4, r27
	addi     r3, r1, 0x20
	lwz      r12, 0(r27)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f1, 0x24(r1)
	mr       r4, r27
	lfs      f0, 0x48(r31)
	addi     r3, r1, 0x14
	fadds    f0, f0, f1
	stfs     f0, 0x40(r31)
	lwz      r12, 0(r27)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f1, 0x14(r1)
	lfs      f0, 0x1c(r1)
	stfs     f1, 8(r1)
	lfs      f4, 0x18(r1)
	stfs     f0, 0x10(r1)
	lwz      r3, 8(r1)
	lwz      r0, 0x10(r1)
	stw      r3, 0x2c(r1)
	lfs      f3, 0x3c(r31)
	stw      r0, 0x34(r1)
	lfs      f2, 0x2c(r1)
	lfs      f1, 0x44(r31)
	lfs      f0, 0x34(r1)
	fsubs    f2, f3, f2
	stfs     f4, 0xc(r1)
	fsubs    f1, f1, f0
	lfs      f0, lbl_80520C24@sda21(r2)
	fmuls    f2, f2, f2
	lwz      r0, 0xc(r1)
	fmuls    f1, f1, f1
	stw      r0, 0x30(r1)
	fadds    f31, f2, f1
	fcmpo    cr0, f31, f0
	ble      lbl_80459FF8
	frsqrte  f0, f31
	fmuls    f31, f0, f31

lbl_80459FF8:
	lwz      r0,
"sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13) cmplwi
r0, 0 bne      lbl_8045A018 addi     r3, r30, 0x90 addi     r5, r30, 0x24 li r4,
0x89 crclr    6 bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045A018:
	lwz      r3,
"sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13) addi r4,
r31, 0x3c lwz      r12, 0(r3) lwz      r12, 0x10(r12) mtctr    r12 bctrl mr r9,
r3 lwz      r3, spSysIF__8PSSystem@sda21(r13) lwz      r4, 0x24(r31) addi r5,
r31, 0x34 addi     r6, r31, 0x3c li       r7, 0 li       r8, 0 bl
"startSoundVecT<8JAISound>__8JAIBasicFUlPP8JAISoundP3VecUlUlUc" lfs      f3,
0x54(r31) fcmpo    cr0, f31, f3 bge      lbl_8045A078 fmr      f1, f31 lfs f2,
0x50(r31) lfs      f4, lbl_80520C24@sda21(r2) li       r3, 1 lfs      f5,
0x5c(r31) bl       linearTransform__7JALCalcFfffffb b        lbl_8045A0A4

lbl_8045A078:
	lfs      f2, 0x58(r31)
	fcmpo    cr0, f31, f2
	bge      lbl_8045A08C
	lfs      f1, 0x5c(r31)
	b        lbl_8045A0A4

lbl_8045A08C:
	fmr      f1, f31
	lfs      f3, 0x4c(r31)
	lfs      f4, 0x5c(r31)
	li       r3, 1
	lfs      f5, lbl_80520C24@sda21(r2)
	bl       linearTransform__7JALCalcFfffffb

lbl_8045A0A4:
	stfs     f1, 0x28(r31)

lbl_8045A0A8:
	lwz      r3, 0x34(r31)
	psq_l    f31, 88(r1), 0, qr0
	lfd      f31, 0x50(r1)
	lmw      r27, 0x3c(r1)
	lwz      r0, 0x64(r1)
	mtlr     r0
	addi     r1, r1, 0x60
	blr
	*/
}

/**
 * @note Address: 0x8045A0C8
 * @note Size: 0xA0
 */
PSGame::EnvSe_Perspective* EnvSeObjBuilder::newSeObj(u32 a1, f32 a2, Vec a3) { return new EnvSe_Perspective_AvoidY(a1, a2, a3); }

/**
 * @note Address: 0x8045A168
 * @note Size: 0x5C
 */
void EnvSeObjBuilder::onBuild(PSSystem::EnvSeBase* se)
{
	PersEnvInfo info                = mPersEnvInfo;
	EnvSe_Perspective_AvoidY* sound = static_cast<EnvSe_Perspective_AvoidY*>(se);
	sound->mInfo                    = info;
}

/**
 * @note Address: 0x8045A1C4
 * @note Size: 0x3C
 */
SceneMgr::SceneMgr()
    : _10(0)
{
	/*
	lis      r4, __vt__Q28PSSystem8SceneMgr@ha
	lis      r5, __vt__Q26PSGame11PikSceneMgr@ha
	addi     r0, r4, __vt__Q28PSSystem8SceneMgr@l
	lis      r4, __vt__Q23PSM8SceneMgr@ha
	stw      r0, 0(r3)
	li       r6, 0
	addi     r5, r5, __vt__Q26PSGame11PikSceneMgr@l
	addi     r0, r4, __vt__Q23PSM8SceneMgr@l
	stw      r6, 4(r3)
	stw      r6, 8(r3)
	stb      r6, 0xc(r3)
	stw      r5, 0(r3)
	stb      r6, 0x10(r3)
	stw      r0, 0(r3)
	blr
	*/
}

/**
 * @note Address: 0x8045A200
 * @note Size: 0xD8
 */
PSSystem::BgmSeq* SceneMgr::newMainBgm(const char* name, JAInter::SoundInfo& info)
{
	DirectorMgr_Scene* director = new DirectorMgr_Scene(nullptr, 8);
	PSSystem::JumpBgmSeq* seq   = new PSSystem::JumpBgmSeq(name, info, director);

	P2ASSERTLINE(349, seq);
	seq->init();
	director->initTrackMap(*seq);
	director->initAndAdaptToBgm(*seq);
	return seq;
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	li       r3, 0x88
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r30, r5
	stw      r29, 0x14(r1)
	mr       r29, r4
	bl       __nw__FUl
	or.      r31, r3, r3
	beq      lbl_8045A240
	li       r4, 0
	li       r5, 8
	bl       __ct__Q23PSM17DirectorMgr_SceneFPQ23PSM17DirectorMgr_SceneUc
	mr       r31, r3

lbl_8045A240:
	li       r3, 0x134
	bl       __nw__FUl
	or.      r0, r3, r3
	beq      lbl_8045A264
	mr       r4, r29
	mr       r5, r30
	mr       r6, r31
	bl
__ct__Q28PSSystem10JumpBgmSeqFPCcRCQ27JAInter9SoundInfoPQ28PSSystem15DirectorMgrBase
	mr       r0, r3

lbl_8045A264:
	cmplwi   r0, 0
	mr       r30, r0
	bne      lbl_8045A28C
	lis      r3, lbl_8049CE74@ha
	lis      r5, lbl_8049CE8C@ha
	addi     r3, r3, lbl_8049CE74@l
	li       r4, 0x15d
	addi     r5, r5, lbl_8049CE8C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045A28C:
	mr       r3, r30
	lwz      r12, 0x10(r30)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	mr       r3, r31
	mr       r4, r30
	bl       initTrackMap__Q23PSM17DirectorMgr_SceneFRQ28PSSystem11DirectedBgm
	mr       r3, r31
	mr       r4, r30
	bl initAndAdaptToBgm__Q28PSSystem15DirectorMgrBaseFRQ28PSSystem11DirectedBgm
	lwz      r0, 0x24(r1)
	mr       r3, r30
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/**
 * @note Address: 0x8045A2D8
 * @note Size: 0x14
 */
bool SceneMgr::curSceneIsBigBossFloor() { return EnemyBigBoss::sBigBoss != nullptr; }

/**
 * @note Address: 0x8045A2EC
 * @note Size: 0x1C0
 */
PSSystem::BgmSeq* SceneMgr::newDirectedBgm(const char* name, JAInter::SoundInfo& info)
{
	PSSystem::DirectedBgm* seq          = nullptr;
	PSSystem::DirectorMgrBase* director = nullptr;

	if (!strcmp(name, "m_boss.bms")) {
		director = new DirectorMgr_Battle;
		seq      = new MiddleBossSeq(name, info, director);
	} else if (!strcmp(name, "l_boss.bms")) {
		director = new DirectorMgr_Battle;
		seq      = new BigBossSeq(name, info, director);
	} else if (!strcmp(name, "battle_t.bms")) {
		director = new DirectorMgr_2PBattle;
		seq      = new PSSystem::DirectedBgm(name, info, director);
	} else {
		JUT_PANICLINE(403, "P2Assert");
	}

	P2ASSERTLINE(406, director);
	P2ASSERTLINE(407, seq);

	seq->init();
	director->initAndAdaptToBgm(*seq);
	return seq;
}

/**
 * @note Address: 0x8045A4AC
 * @note Size: 0x1F4
 */
PSSystem::Scene* SceneMgr::newGameScene(u8 wscene, PSGame::SceneInfo* info)
{
	PSSystem::Scene* scene = nullptr;
	if (info->mSceneType == PSGame::SceneInfo::CHALLENGE_MODE || info->mSceneType == PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		scene = new Scene_Challenge(wscene, info);
	} else {
		if (info->isCaveFloor()) {
			scene = new Scene_Cave(wscene, info);
		} else {
			switch (info->mSceneType) {
			case PSGame::SceneInfo::SCENE_NULL:
				scene = new Scene_Global(wscene, info);
				break;
			case PSGame::SceneInfo::PIKLOPEDIA:
				scene = new Scene_Zukan(wscene, info);
				break;
			case PSGame::SceneInfo::COURSE_TUTORIAL:
			case PSGame::SceneInfo::COURSE_FOREST:
			case PSGame::SceneInfo::COURSE_YAKUSHIMA:
			case PSGame::SceneInfo::COURSE_LAST:
			case PSGame::SceneInfo::COURSE_TUTORIALDAY1:
				scene = new Scene_Ground(wscene, info);
				break;
			case PSGame::SceneInfo::WORLD_MAP_NORMAL:
			case PSGame::SceneInfo::WORLD_MAP_NEWLEVEL:
				scene = new Scene_WorldMap(wscene, info);
				break;
			}
		}
	}

	if (!scene) {
		scene = new Scene_NoObjects(wscene, info);
	}

	P2ASSERTLINE(468, scene);

	scene->init();

	return scene;
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	mr       r31, r5
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r29, 0x14(r1)
	li       r29, 0
	lbz      r0, 6(r5)
	cmplwi   r0, 6
	beq      lbl_8045A4E8
	clrlwi   r0, r0, 0x18
	cmplwi   r0, 7
	bne      lbl_8045A510

lbl_8045A4E8:
	li       r3, 0x68
	bl       __nw__FUl
	or.      r0, r3, r3
	beq      lbl_8045A508
	mr       r4, r30
	mr       r5, r31
	bl       __ct__Q23PSM15Scene_ChallengeFUcPQ26PSGame9SceneInfo
	mr       r0, r3

lbl_8045A508:
	mr       r29, r0
	b        lbl_8045A618

lbl_8045A510:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8045A554
	li       r3, 0x68
	bl       __nw__FUl
	or.      r0, r3, r3
	beq      lbl_8045A54C
	mr       r4, r30
	mr       r5, r31
	bl       __ct__Q23PSM10Scene_CaveFUcPQ26PSGame9SceneInfo
	mr       r0, r3

lbl_8045A54C:
	mr       r29, r0
	b        lbl_8045A618

lbl_8045A554:
	lbz      r0, 6(r31)
	cmplwi   r0, 0x14
	bgt      lbl_8045A618
	lis      r3, lbl_804EE164@ha
	slwi     r0, r0, 2
	addi     r3, r3, lbl_804EE164@l
	lwzx     r0, r3, r0
	mtctr    r0
	bctr

lbl_8045A578:
	li       r3, 0x28
	bl       __nw__FUl
	or.      r0, r3, r3
	beq      lbl_8045A598
	mr       r4, r30
	mr       r5, r31
	bl       __ct__Q23PSM12Scene_GlobalFUcPQ26PSGame9SceneInfo
	mr       r0, r3

lbl_8045A598:
	mr       r29, r0
	b        lbl_8045A618

lbl_8045A5A0:
	li       r3, 0x38
	bl       __nw__FUl
	or.      r29, r3, r3
	beq      lbl_8045A618
	mr       r4, r30
	mr       r5, r31
	bl       __ct__Q23PSM13Scene_ObjectsFUcPQ26PSGame9SceneInfo
	lis      r3, __vt__Q23PSM11Scene_Zukan@ha
	addi     r0, r3, __vt__Q23PSM11Scene_Zukan@l
	stw      r0, 0(r29)
	b        lbl_8045A618

lbl_8045A5CC:

lbl_8045A5CC:

lbl_8045A5CC:

lbl_8045A5CC:

lbl_8045A5CC:
	li       r3, 0x60
	bl       __nw__FUl
	or.      r0, r3, r3
	beq      lbl_8045A5EC
	mr       r4, r30
	mr       r5, r31
	bl       __ct__Q23PSM12Scene_GroundFUcPQ26PSGame9SceneInfo
	mr       r0, r3

lbl_8045A5EC:
	mr       r29, r0
	b        lbl_8045A618

lbl_8045A5F4:

lbl_8045A5F4:
	li       r3, 0x2c
	bl       __nw__FUl
	or.      r0, r3, r3
	beq      lbl_8045A614
	mr       r4, r30
	mr       r5, r31
	bl       __ct__Q23PSM14Scene_WorldMapFUcPQ26PSGame9SceneInfo
	mr       r0, r3

lbl_8045A614:
	mr       r29, r0

lbl_8045A618:
	cmplwi   r29, 0
	bne      lbl_8045A648
	li       r3, 0x28
	bl       __nw__FUl
	or.      r29, r3, r3
	beq      lbl_8045A648
	mr       r4, r30
	mr       r5, r31
	bl       __ct__Q23PSM9SceneBaseFUcPQ26PSGame9SceneInfo
	lis      r3, __vt__Q23PSM15Scene_NoObjects@ha
	addi     r0, r3, __vt__Q23PSM15Scene_NoObjects@l
	stw      r0, 0(r29)

lbl_8045A648:
	cmplwi   r29, 0
	bne      lbl_8045A66C
	lis      r3, lbl_8049CE74@ha
	lis      r5, lbl_8049CE8C@ha
	addi     r3, r3, lbl_8049CE74@l
	li       r4, 0x1d4
	addi     r5, r5, lbl_8049CE8C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045A66C:
	mr       r3, r29
	lwz      r12, 0(r29)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x24(r1)
	mr       r3, r29
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/**
 * @note Address: 0x8045A6A0
 * @note Size: 0x18BC
 */
void SceneMgr::initEnvironmentSe(PSM::Scene_Game* scene)
{
	PSGame::SceneInfo* info = scene->getSceneInfoA();
	PSSystem::EnvSeMgr* mgr = nullptr;
	u8 type                 = info->mSceneType;

	JGeometry::TBox3f bounds(info->mBounds);
	EnvSeObjBuilder builder(bounds);

	switch (type) {
	case PSGame::SceneInfo::CHALLENGE_MODE:
		mgr                = new PSSystem::EnvSeMgr;
		scene->mPersEnvMgr = new PersEnvManager(mgr);
		break;
	}
	/*
	stwu     r1, -0x170(r1)
	mflr     r0
	stw      r0, 0x174(r1)
	stmw     r24, 0x150(r1)
	mr       r27, r4
	lis      r4, lbl_8049CE68@ha
	mr       r3, r27
	addi     r31, r4, lbl_8049CE68@l
	bl       getSceneInfoA__Q23PSM9SceneBaseFv
	mr       r0, r3
	addi     r3, r1, 0x6c
	mr       r28, r0
	li       r29, 0
	lbz      r25, 6(r28)
	addi     r4, r28, 0x20
	bl       "__ct__Q29JGeometry8TBox3<f>FRCQ29JGeometry8TBox3<f>"
	mr       r4, r3
	addi     r3, r1, 0xe8
	bl       "__ct__Q23PSM15EnvSeObjBuilderFQ29JGeometry8TBox3<f>"
	clrlwi   r30, r25, 0x18
	cmpwi    r30, 7
	beq      lbl_8045AAF4
	bge      lbl_8045AAF4
	cmpwi    r30, 6
	bge      lbl_8045A708
	b        lbl_8045AAF4

lbl_8045A708:
	li       r3, 0x18
	bl       __nw__FUl
	or.      r29, r3, r3
	beq      lbl_8045A720
	bl       __ct__Q28PSSystem8EnvSeMgrFv
	mr       r29, r3

lbl_8045A720:
	li       r3, 0x14
	bl       __nw__FUl
	or.      r26, r3, r3
	beq      lbl_8045A73C
	mr       r4, r29
	bl       __ct__Q23PSM14PersEnvManagerFPQ28PSSystem8EnvSeMgr
	mr       r26, r3

lbl_8045A73C:
	stw      r26, 0x58(r27)
	li       r3, 0x14
	li       r5, -4
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045A768
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4016
	stw      r0, 0x10(r24)

lbl_8045A768:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045A77C
	stw      r24, 0x134(r1)

lbl_8045A77C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045A7B0
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4018
	stw      r0, 0x10(r24)

lbl_8045A7B0:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045A7C0
	stw      r24, 0x134(r1)

lbl_8045A7C0:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045A7F4
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401a
	stw      r0, 0x10(r24)

lbl_8045A7F4:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045A804
	stw      r24, 0x134(r1)

lbl_8045A804:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045A838
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401c
	stw      r0, 0x10(r24)

lbl_8045A838:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045A848
	stw      r24, 0x134(r1)

lbl_8045A848:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045A87C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401e
	stw      r0, 0x10(r24)

lbl_8045A87C:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045A88C
	stw      r24, 0x134(r1)

lbl_8045A88C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045A8C0
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4017
	stw      r0, 0x10(r24)

lbl_8045A8C0:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045A8D0
	stw      r24, 0x134(r1)

lbl_8045A8D0:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045A904
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4019
	stw      r0, 0x10(r24)

lbl_8045A904:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045A914
	stw      r24, 0x134(r1)

lbl_8045A914:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045A948
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401b
	stw      r0, 0x10(r24)

lbl_8045A948:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045A958
	stw      r24, 0x134(r1)

lbl_8045A958:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045A98C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401d
	stw      r0, 0x10(r24)

lbl_8045A98C:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045A99C
	stw      r24, 0x134(r1)

lbl_8045A99C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045A9D0
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401f
	stw      r0, 0x10(r24)

lbl_8045A9D0:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045A9E0
	stw      r24, 0x134(r1)

lbl_8045A9E0:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r8, 0xc4(r31)
	addi     r3, r1, 0xe8
	lwz      r7, 0xc8(r31)
	addi     r4, r1, 0x58
	lwz      r6, 0xcc(r31)
	lwz      r5, 0xd0(r31)
	lwz      r0, 0xd4(r31)
	lfs      f0, lbl_80520C2C@sda21(r2)
	stw      r8, 0xd4(r1)
	stfs     f0, 0x10(r26)
	stw      r7, 0xd8(r1)
	stw      r6, 0xdc(r1)
	stw      r5, 0xe0(r1)
	stw      r0, 0xe4(r1)
	stw      r8, 0x58(r1)
	stw      r7, 0x5c(r1)
	stw      r6, 0x60(r1)
	stw      r5, 0x64(r1)
	stw      r0, 0x68(r1)
	bl       setInfo__Q23PSM15EnvSeObjBuilderFQ23PSM11PersEnvInfo
	lfs      f1, lbl_80520C20@sda21(r2)
	mr       r4, r29
	addi     r3, r1, 0xe8
	bl       build__Q26PSGame25Builder_EvnSe_PerspectiveFfPQ28PSSystem8EnvSeMgr
	mr       r3, r29
	bl       SetNoYOfset__3PSMFPQ28PSSystem8EnvSeMgr
	li       r3, 0x54
	bl       __nw__FUl
	or.      r25, r3, r3
	beq      lbl_8045AA98
	lfs      f2, lbl_80520C20@sda21(r2)
	mr       r24, r25
	lfs      f1, lbl_80520C24@sda21(r2)
	li       r4, 0x3079
	fmr      f3, f2
	lfs      f4, lbl_80520C30@sda21(r2)
	lfs      f5, lbl_80520C34@sda21(r2)
	bl       __ct__Q26PSGame13EnvSe_AutoPanFUlfffff
	lis      r3, __vt__Q23PSM12Env_Pollutin@ha
	lfs      f0, lbl_80520C20@sda21(r2)
	addi     r0, r3, __vt__Q23PSM12Env_Pollutin@l
	stw      r0, 0x10(r24)
	stfs     f0, 0x50(r24)

lbl_8045AA98:
	mr       r3, r29
	mr       r4, r25
	bl       append__10JSUPtrListFP10JSUPtrLink
	li       r3, 0x54
	bl       __nw__FUl
	or.      r25, r3, r3
	beq      lbl_8045AAE8
	lfs      f1, lbl_80520C20@sda21(r2)
	mr       r24, r25
	lfs      f2, lbl_80520C24@sda21(r2)
	li       r4, 0x307a
	fmr      f3, f1
	lfs      f4, lbl_80520C30@sda21(r2)
	lfs      f5, lbl_80520C34@sda21(r2)
	bl       __ct__Q26PSGame13EnvSe_AutoPanFUlfffff
	lis      r3, __vt__Q23PSM12Env_Pollutin@ha
	lfs      f0, lbl_80520C20@sda21(r2)
	addi     r0, r3, __vt__Q23PSM12Env_Pollutin@l
	stw      r0, 0x10(r24)
	stfs     f0, 0x50(r24)

lbl_8045AAE8:
	mr       r3, r29
	mr       r4, r25
	bl       append__10JSUPtrListFP10JSUPtrLink

lbl_8045AAF4:
	cmplwi   r29, 0
	bne      lbl_8045BEFC
	mr       r3, r28
	li       r4, 1
	bl       getFlag__Q26PSGame9SceneInfoCFQ36PSGame9SceneInfo12FlagBitShift
	clrlwi   r0, r3, 0x18
	subfic   r0, r0, 1
	cntlzw   r0, r0
	rlwinm.  r0, r0, 0x1b, 0x18, 0x1f
	bne      lbl_8045BEFC
	mr       r3, r28
	lwz      r12, 0(r28)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8045B880
	li       r3, 0x18
	bl       __nw__FUl
	or.      r29, r3, r3
	beq      lbl_8045AB50
	bl       __ct__Q28PSSystem8EnvSeMgrFv
	mr       r29, r3

lbl_8045AB50:
	li       r3, 0x14
	bl       __nw__FUl
	or.      r30, r3, r3
	beq      lbl_8045AB6C
	mr       r4, r29
	bl       __ct__Q23PSM14PersEnvManagerFPQ28PSSystem8EnvSeMgr
	mr       r30, r3

lbl_8045AB6C:
	stw      r30, 0x58(r27)
	lbz      r0, 0x40(r28)
	cmplwi   r0, 0xe
	bgt      lbl_8045B6A4
	lis      r3, lbl_804EE1B8@ha
	slwi     r0, r0, 2
	addi     r3, r3, lbl_804EE1B8@l
	lwzx     r0, r3, r0
	mtctr    r0
	bctr

lbl_8045AB94:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045ABBC
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4018
	stw      r0, 0x10(r24)

lbl_8045ABBC:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045ABD0
	stw      r24, 0x134(r1)

lbl_8045ABD0:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AC04
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401a
	stw      r0, 0x10(r24)

lbl_8045AC04:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045AC14
	stw      r24, 0x134(r1)

lbl_8045AC14:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045AC24:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AC4C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4019
	stw      r0, 0x10(r24)

lbl_8045AC4C:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045AC60
	stw      r24, 0x134(r1)

lbl_8045AC60:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AC94
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401b
	stw      r0, 0x10(r24)

lbl_8045AC94:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045ACA4
	stw      r24, 0x134(r1)

lbl_8045ACA4:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045ACB4:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045ACDC
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4018
	stw      r0, 0x10(r24)

lbl_8045ACDC:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045ACF0
	stw      r24, 0x134(r1)

lbl_8045ACF0:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AD24
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401b
	stw      r0, 0x10(r24)

lbl_8045AD24:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045AD34
	stw      r24, 0x134(r1)

lbl_8045AD34:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AD68
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401c
	stw      r0, 0x10(r24)

lbl_8045AD68:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045AD78
	stw      r24, 0x134(r1)

lbl_8045AD78:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045AD88:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045ADB0
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401a
	stw      r0, 0x10(r24)

lbl_8045ADB0:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045ADC4
	stw      r24, 0x134(r1)

lbl_8045ADC4:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045ADF8
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401d
	stw      r0, 0x10(r24)

lbl_8045ADF8:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045AE08
	stw      r24, 0x134(r1)

lbl_8045AE08:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AE3C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4016
	stw      r0, 0x10(r24)

lbl_8045AE3C:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045AE4C
	stw      r24, 0x134(r1)

lbl_8045AE4C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045AE5C:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AE84
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401c
	stw      r0, 0x10(r24)

lbl_8045AE84:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045AE98
	stw      r24, 0x134(r1)

lbl_8045AE98:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AECC
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4017
	stw      r0, 0x10(r24)

lbl_8045AECC:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045AEDC
	stw      r24, 0x134(r1)

lbl_8045AEDC:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AF10
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401e
	stw      r0, 0x10(r24)

lbl_8045AF10:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045AF20
	stw      r24, 0x134(r1)

lbl_8045AF20:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045AF30:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AF58
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4016
	stw      r0, 0x10(r24)

lbl_8045AF58:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045AF6C
	stw      r24, 0x134(r1)

lbl_8045AF6C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AFA0
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401f
	stw      r0, 0x10(r24)

lbl_8045AFA0:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045AFB0
	stw      r24, 0x134(r1)

lbl_8045AFB0:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045AFE4
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4020
	stw      r0, 0x10(r24)

lbl_8045AFE4:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045AFF4
	stw      r24, 0x134(r1)

lbl_8045AFF4:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045B004:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B02C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x401e
	stw      r0, 0x10(r24)

lbl_8045B02C:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045B040
	stw      r24, 0x134(r1)

lbl_8045B040:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B074
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4021
	stw      r0, 0x10(r24)

lbl_8045B074:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B084
	stw      r24, 0x134(r1)

lbl_8045B084:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B0B8
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x402a
	stw      r0, 0x10(r24)

lbl_8045B0B8:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B0C8
	stw      r24, 0x134(r1)

lbl_8045B0C8:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045B0D8:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B100
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4020
	stw      r0, 0x10(r24)

lbl_8045B100:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045B114
	stw      r24, 0x134(r1)

lbl_8045B114:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B148
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x402b
	stw      r0, 0x10(r24)

lbl_8045B148:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B158
	stw      r24, 0x134(r1)

lbl_8045B158:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B18C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4022
	stw      r0, 0x10(r24)

lbl_8045B18C:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B19C
	stw      r24, 0x134(r1)

lbl_8045B19C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045B1AC:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B1D4
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x402a
	stw      r0, 0x10(r24)

lbl_8045B1D4:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045B1E8
	stw      r24, 0x134(r1)

lbl_8045B1E8:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B21C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4023
	stw      r0, 0x10(r24)

lbl_8045B21C:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B22C
	stw      r24, 0x134(r1)

lbl_8045B22C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B260
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4028
	stw      r0, 0x10(r24)

lbl_8045B260:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B270
	stw      r24, 0x134(r1)

lbl_8045B270:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045B280:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B2A8
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4022
	stw      r0, 0x10(r24)

lbl_8045B2A8:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045B2BC
	stw      r24, 0x134(r1)

lbl_8045B2BC:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B2F0
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4029
	stw      r0, 0x10(r24)

lbl_8045B2F0:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B300
	stw      r24, 0x134(r1)

lbl_8045B300:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B334
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4026
	stw      r0, 0x10(r24)

lbl_8045B334:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B344
	stw      r24, 0x134(r1)

lbl_8045B344:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045B354:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B37C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4029
	stw      r0, 0x10(r24)

lbl_8045B37C:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045B390
	stw      r24, 0x134(r1)

lbl_8045B390:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B3C4
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4027
	stw      r0, 0x10(r24)

lbl_8045B3C4:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B3D4
	stw      r24, 0x134(r1)

lbl_8045B3D4:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B408
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4024
	stw      r0, 0x10(r24)

lbl_8045B408:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B418
	stw      r24, 0x134(r1)

lbl_8045B418:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045B428:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B450
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4029
	stw      r0, 0x10(r24)

lbl_8045B450:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045B464
	stw      r24, 0x134(r1)

lbl_8045B464:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B498
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4027
	stw      r0, 0x10(r24)

lbl_8045B498:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B4A8
	stw      r24, 0x134(r1)

lbl_8045B4A8:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B4DC
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4025
	stw      r0, 0x10(r24)

lbl_8045B4DC:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B4EC
	stw      r24, 0x134(r1)

lbl_8045B4EC:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045B4FC:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B524
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4029
	stw      r0, 0x10(r24)

lbl_8045B524:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045B538
	stw      r24, 0x134(r1)

lbl_8045B538:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B56C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4027
	stw      r0, 0x10(r24)

lbl_8045B56C:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B57C
	stw      r24, 0x134(r1)

lbl_8045B57C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B5B0
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4025
	stw      r0, 0x10(r24)

lbl_8045B5B0:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B5C0
	stw      r24, 0x134(r1)

lbl_8045B5C0:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045B5D0:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B5F8
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4029
	stw      r0, 0x10(r24)

lbl_8045B5F8:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045B60C
	stw      r24, 0x134(r1)

lbl_8045B60C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B640
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4027
	stw      r0, 0x10(r24)

lbl_8045B640:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B650
	stw      r24, 0x134(r1)

lbl_8045B650:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B684
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4025
	stw      r0, 0x10(r24)

lbl_8045B684:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B694
	stw      r24, 0x134(r1)

lbl_8045B694:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045B774

lbl_8045B6A4:
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B6CC
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4029
	stw      r0, 0x10(r24)

lbl_8045B6CC:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045B6E0
	stw      r24, 0x134(r1)

lbl_8045B6E0:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B714
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4027
	stw      r0, 0x10(r24)

lbl_8045B714:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B724
	stw      r24, 0x134(r1)

lbl_8045B724:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045B758
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4025
	stw      r0, 0x10(r24)

lbl_8045B758:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045B768
	stw      r24, 0x134(r1)

lbl_8045B768:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink

lbl_8045B774:
	lwz      r8, 0xd8(r31)
	addi     r3, r1, 0xe8
	lwz      r7, 0xdc(r31)
	addi     r4, r1, 0x44
	lwz      r6, 0xe0(r31)
	lwz      r5, 0xe4(r31)
	lwz      r0, 0xe8(r31)
	lfs      f0, lbl_80520C2C@sda21(r2)
	stw      r8, 0xc0(r1)
	stfs     f0, 0x10(r30)
	stw      r7, 0xc4(r1)
	stw      r6, 0xc8(r1)
	stw      r5, 0xcc(r1)
	stw      r0, 0xd0(r1)
	stw      r8, 0x44(r1)
	stw      r7, 0x48(r1)
	stw      r6, 0x4c(r1)
	stw      r5, 0x50(r1)
	stw      r0, 0x54(r1)
	bl       setInfo__Q23PSM15EnvSeObjBuilderFQ23PSM11PersEnvInfo
	lfs      f1, lbl_80520C20@sda21(r2)
	mr       r4, r29
	addi     r3, r1, 0xe8
	bl       build__Q26PSGame25Builder_EvnSe_PerspectiveFfPQ28PSSystem8EnvSeMgr
	mr       r3, r29
	bl       SetNoYOfset__3PSMFPQ28PSSystem8EnvSeMgr
	li       r3, 0x54
	bl       __nw__FUl
	or.      r25, r3, r3
	beq      lbl_8045B820
	lfs      f2, lbl_80520C20@sda21(r2)
	mr       r24, r25
	lfs      f1, lbl_80520C24@sda21(r2)
	li       r4, 0x3079
	fmr      f3, f2
	lfs      f4, lbl_80520C30@sda21(r2)
	lfs      f5, lbl_80520C34@sda21(r2)
	bl       __ct__Q26PSGame13EnvSe_AutoPanFUlfffff
	lis      r3, __vt__Q23PSM12Env_Pollutin@ha
	lfs      f0, lbl_80520C20@sda21(r2)
	addi     r0, r3, __vt__Q23PSM12Env_Pollutin@l
	stw      r0, 0x10(r24)
	stfs     f0, 0x50(r24)

lbl_8045B820:
	mr       r3, r29
	mr       r4, r25
	bl       append__10JSUPtrListFP10JSUPtrLink
	li       r3, 0x54
	bl       __nw__FUl
	or.      r25, r3, r3
	beq      lbl_8045B870
	lfs      f1, lbl_80520C20@sda21(r2)
	mr       r24, r25
	lfs      f2, lbl_80520C24@sda21(r2)
	li       r4, 0x307a
	fmr      f3, f1
	lfs      f4, lbl_80520C30@sda21(r2)
	lfs      f5, lbl_80520C34@sda21(r2)
	bl       __ct__Q26PSGame13EnvSe_AutoPanFUlfffff
	lis      r3, __vt__Q23PSM12Env_Pollutin@ha
	lfs      f0, lbl_80520C20@sda21(r2)
	addi     r0, r3, __vt__Q23PSM12Env_Pollutin@l
	stw      r0, 0x10(r24)
	stfs     f0, 0x50(r24)

lbl_8045B870:
	mr       r3, r29
	mr       r4, r25
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045BEFC

lbl_8045B880:
	cmpwi    r30, 4
	beq      lbl_8045BD4C
	bge      lbl_8045B8A4
	cmpwi    r30, 2
	beq      lbl_8045B9A0
	bge      lbl_8045BB10
	cmpwi    r30, 1
	bge      lbl_8045B8B0
	b        lbl_8045BEFC

lbl_8045B8A4:
	cmpwi    r30, 0x14
	beq      lbl_8045B8B0
	b        lbl_8045BEFC

lbl_8045B8B0:
	li       r3, 0x18
	bl       __nw__FUl
	or.      r24, r3, r3
	beq      lbl_8045B8C8
	bl       __ct__Q28PSSystem8EnvSeMgrFv
	mr       r24, r3

lbl_8045B8C8:
	mr       r29, r24
	li       r3, 0x50
	bl       __nw__FUl
	or.      r25, r3, r3
	beq      lbl_8045B8FC
	lfs      f1, lbl_80520C24@sda21(r2)
	li       r4, 0x402d
	lfs      f2, lbl_80520C38@sda21(r2)
	lfs      f3, lbl_80520C20@sda21(r2)
	lfs      f4, lbl_80520C30@sda21(r2)
	lfs      f5, lbl_80520C34@sda21(r2)
	bl       __ct__Q26PSGame13EnvSe_AutoPanFUlfffff
	mr       r25, r3

lbl_8045B8FC:
	cmplwi   r25, 0
	bne      lbl_8045B918
	addi     r3, r31, 0xc
	addi     r5, r31, 0x24
	li       r4, 0x30a
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045B918:
	mr       r3, r25
	li       r4, 1
	li       r5, 0
	bl       setDirection__Q26PSGame13EnvSe_AutoPanFbb
	mr       r3, r24
	mr       r4, r25
	bl       append__10JSUPtrListFP10JSUPtrLink
	li       r3, 0x50
	bl       __nw__FUl
	or.      r25, r3, r3
	beq      lbl_8045B964
	lfs      f1, lbl_80520C20@sda21(r2)
	li       r4, 0x402d
	lfs      f2, lbl_80520C38@sda21(r2)
	fmr      f3, f1
	lfs      f4, lbl_80520C30@sda21(r2)
	lfs      f5, lbl_80520C34@sda21(r2)
	bl       __ct__Q26PSGame13EnvSe_AutoPanFUlfffff
	mr       r25, r3

lbl_8045B964:
	cmplwi   r25, 0
	bne      lbl_8045B980
	addi     r3, r31, 0xc
	addi     r5, r31, 0x24
	li       r4, 0x311
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045B980:
	mr       r3, r25
	li       r4, 0
	li       r5, 1
	bl       setDirection__Q26PSGame13EnvSe_AutoPanFbb
	mr       r3, r24
	mr       r4, r25
	bl       append__10JSUPtrListFP10JSUPtrLink
	b        lbl_8045BEFC

lbl_8045B9A0:
	li       r3, 0x18
	bl       __nw__FUl
	or.      r26, r3, r3
	beq      lbl_8045B9B8
	bl       __ct__Q28PSSystem8EnvSeMgrFv
	mr       r26, r3

lbl_8045B9B8:
	mr       r29, r26
	li       r3, 0x14
	bl       __nw__FUl
	or.      r28, r3, r3
	beq      lbl_8045B9D8
	mr       r4, r26
	bl       __ct__Q23PSM14PersEnvManagerFPQ28PSSystem8EnvSeMgr
	mr       r28, r3

lbl_8045B9D8:
	stw      r28, 0x58(r27)
	li       r3, 0x14
	li       r5, -4
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BA04
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4037
	stw      r0, 0x10(r24)

lbl_8045BA04:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045BA18
	stw      r24, 0x134(r1)

lbl_8045BA18:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BA4C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4038
	stw      r0, 0x10(r24)

lbl_8045BA4C:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045BA5C
	stw      r24, 0x134(r1)

lbl_8045BA5C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BA90
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4039
	stw      r0, 0x10(r24)

lbl_8045BA90:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045BAA0
	stw      r24, 0x134(r1)

lbl_8045BAA0:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r8, 0xec(r31)
	addi     r3, r1, 0xe8
	lwz      r7, 0xf0(r31)
	addi     r4, r1, 0x30
	lwz      r6, 0xf4(r31)
	lwz      r5, 0xf8(r31)
	lwz      r0, 0xfc(r31)
	lfs      f0, lbl_80520C3C@sda21(r2)
	stw      r8, 0xac(r1)
	stfs     f0, 0x10(r28)
	stw      r7, 0xb0(r1)
	stw      r6, 0xb4(r1)
	stw      r5, 0xb8(r1)
	stw      r0, 0xbc(r1)
	stw      r8, 0x30(r1)
	stw      r7, 0x34(r1)
	stw      r6, 0x38(r1)
	stw      r5, 0x3c(r1)
	stw      r0, 0x40(r1)
	bl       setInfo__Q23PSM15EnvSeObjBuilderFQ23PSM11PersEnvInfo
	lfs      f1, lbl_80520C20@sda21(r2)
	mr       r4, r26
	addi     r3, r1, 0xe8
	bl       build__Q26PSGame25Builder_EvnSe_PerspectiveFfPQ28PSSystem8EnvSeMgr
	b        lbl_8045BEFC

lbl_8045BB10:
	li       r3, 0x18
	bl       __nw__FUl
	or.      r26, r3, r3
	beq      lbl_8045BB28
	bl       __ct__Q28PSSystem8EnvSeMgrFv
	mr       r26, r3

lbl_8045BB28:
	mr       r29, r26
	li       r3, 0x14
	bl       __nw__FUl
	or.      r28, r3, r3
	beq      lbl_8045BB48
	mr       r4, r26
	bl       __ct__Q23PSM14PersEnvManagerFPQ28PSSystem8EnvSeMgr
	mr       r28, r3

lbl_8045BB48:
	stw      r28, 0x58(r27)
	li       r3, 0x14
	li       r5, -4
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BB74
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x402f
	stw      r0, 0x10(r24)

lbl_8045BB74:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045BB88
	stw      r24, 0x134(r1)

lbl_8045BB88:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BBBC
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4033
	stw      r0, 0x10(r24)

lbl_8045BBBC:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045BBCC
	stw      r24, 0x134(r1)

lbl_8045BBCC:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BC00
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4035
	stw      r0, 0x10(r24)

lbl_8045BC00:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045BC10
	stw      r24, 0x134(r1)

lbl_8045BC10:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BC44
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4030
	stw      r0, 0x10(r24)

lbl_8045BC44:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045BC54
	stw      r24, 0x134(r1)

lbl_8045BC54:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BC88
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4034
	stw      r0, 0x10(r24)

lbl_8045BC88:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045BC98
	stw      r24, 0x134(r1)

lbl_8045BC98:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BCCC
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x4036
	stw      r0, 0x10(r24)

lbl_8045BCCC:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045BCDC
	stw      r24, 0x134(r1)

lbl_8045BCDC:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r8, 0x100(r31)
	addi     r3, r1, 0xe8
	lwz      r7, 0x104(r31)
	addi     r4, r1, 0x1c
	lwz      r6, 0x108(r31)
	lwz      r5, 0x10c(r31)
	lwz      r0, 0x110(r31)
	lfs      f0, lbl_80520C2C@sda21(r2)
	stw      r8, 0x98(r1)
	stfs     f0, 0x10(r28)
	stw      r7, 0x9c(r1)
	stw      r6, 0xa0(r1)
	stw      r5, 0xa4(r1)
	stw      r0, 0xa8(r1)
	stw      r8, 0x1c(r1)
	stw      r7, 0x20(r1)
	stw      r6, 0x24(r1)
	stw      r5, 0x28(r1)
	stw      r0, 0x2c(r1)
	bl       setInfo__Q23PSM15EnvSeObjBuilderFQ23PSM11PersEnvInfo
	lfs      f1, lbl_80520C20@sda21(r2)
	mr       r4, r26
	addi     r3, r1, 0xe8
	bl       build__Q26PSGame25Builder_EvnSe_PerspectiveFfPQ28PSSystem8EnvSeMgr
	b        lbl_8045BEFC

lbl_8045BD4C:
	li       r3, 0x18
	bl       __nw__FUl
	or.      r26, r3, r3
	beq      lbl_8045BD64
	bl       __ct__Q28PSSystem8EnvSeMgrFv
	mr       r26, r3

lbl_8045BD64:
	mr       r29, r26
	li       r3, 0x14
	bl       __nw__FUl
	or.      r28, r3, r3
	beq      lbl_8045BD84
	mr       r4, r26
	bl       __ct__Q23PSM14PersEnvManagerFPQ28PSSystem8EnvSeMgr
	mr       r28, r3

lbl_8045BD84:
	stw      r28, 0x58(r27)
	li       r3, 0x14
	li       r5, -4
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BDB0
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x403a
	stw      r0, 0x10(r24)

lbl_8045BDB0:
	lwz      r0, 0x128(r1)
	addi     r25, r1, 0x128
	cmplwi   r0, 0
	bne      lbl_8045BDC4
	stw      r24, 0x134(r1)

lbl_8045BDC4:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BDF8
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x403b
	stw      r0, 0x10(r24)

lbl_8045BDF8:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045BE08
	stw      r24, 0x134(r1)

lbl_8045BE08:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BE3C
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x403a
	stw      r0, 0x10(r24)

lbl_8045BE3C:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045BE4C
	stw      r24, 0x134(r1)

lbl_8045BE4C:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r4, sCurrentHeap__7JKRHeap@sda21(r13)
	li       r3, 0x14
	li       r5, -4
	bl       __nw__FUlP7JKRHeapi
	or.      r24, r3, r3
	beq      lbl_8045BE80
	mr       r4, r24
	bl       __ct__10JSUPtrLinkFPv
	li       r0, 0x403c
	stw      r0, 0x10(r24)

lbl_8045BE80:
	lwz      r0, 0x128(r1)
	cmplwi   r0, 0
	bne      lbl_8045BE90
	stw      r24, 0x134(r1)

lbl_8045BE90:
	mr       r3, r25
	mr       r4, r24
	bl       append__10JSUPtrListFP10JSUPtrLink
	lwz      r8, 0x114(r31)
	addi     r3, r1, 0xe8
	lwz      r7, 0x118(r31)
	addi     r4, r1, 8
	lwz      r6, 0x11c(r31)
	lwz      r5, 0x120(r31)
	lwz      r0, 0x124(r31)
	lfs      f0, lbl_80520C3C@sda21(r2)
	stw      r8, 0x84(r1)
	stfs     f0, 0x10(r28)
	stw      r7, 0x88(r1)
	stw      r6, 0x8c(r1)
	stw      r5, 0x90(r1)
	stw      r0, 0x94(r1)
	stw      r8, 8(r1)
	stw      r7, 0xc(r1)
	stw      r6, 0x10(r1)
	stw      r5, 0x14(r1)
	stw      r0, 0x18(r1)
	bl       setInfo__Q23PSM15EnvSeObjBuilderFQ23PSM11PersEnvInfo
	lfs      f1, lbl_80520C20@sda21(r2)
	mr       r4, r26
	addi     r3, r1, 0xe8
	bl       build__Q26PSGame25Builder_EvnSe_PerspectiveFfPQ28PSSystem8EnvSeMgr

lbl_8045BEFC:
	cmplwi   r29, 0
	beq      lbl_8045BF30
	lfs      f1, lbl_80520C40@sda21(r2)
	mr       r3, r29
	li       r4, 0x3079
	bl       SetBossBgmMuteVol__3PSMFPQ28PSSystem8EnvSeMgrUlf
	lfs      f1, lbl_80520C40@sda21(r2)
	mr       r3, r29
	li       r4, 0x307a
	bl       SetBossBgmMuteVol__3PSMFPQ28PSSystem8EnvSeMgrUlf
	mr       r3, r27
	mr       r4, r29
	bl       adaptEnvSe__Q23PSM10Scene_GameFPQ28PSSystem8EnvSeMgr

lbl_8045BF30:
	lis      r4, __vt__Q23PSM15EnvSeObjBuilder@ha
	addi     r3, r1, 0xe8
	addi     r0, r4, __vt__Q23PSM15EnvSeObjBuilder@l
	li       r4, 0
	stw      r0, 0xe8(r1)
	bl       __dt__Q26PSGame25Builder_EvnSe_PerspectiveFv
	lmw      r24, 0x150(r1)
	lwz      r0, 0x174(r1)
	mtlr     r0
	addi     r1, r1, 0x170
	blr
	*/
}

/**
 * @note Address: 0x8045BF5C
 * @note Size: 0x8C
 */
void SetBossBgmMuteVol(PSSystem::EnvSeMgr* mgr, u32 id, f32 vol)
{
	for (JSULink<PSSystem::EnvSeBase>* link = mgr->mEnvList.getFirst(); link; link = link->getNext()) {
		EnvSe_Perspective_AvoidY* se = (EnvSe_Perspective_AvoidY*)link->mValue;
		if (se->getCastType() == 'poll' && id == se->mSoundID) {
			se->mInfo._04 = vol;
		}
	}
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stfd     f31, 0x18(r1)
	fmr      f31, f1
	stw      r31, 0x14(r1)
	stw      r30, 0x10(r1)
	stw      r29, 0xc(r1)
	mr       r29, r4
	lwz      r30, 0(r3)
	b        lbl_8045BFC0

lbl_8045BF88:
	lwz      r31, 0(r30)
	mr       r3, r31
	lwz      r12, 0x10(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	addis    r0, r3, 0x8f91
	cmplwi   r0, 0x6c6c
	bne      lbl_8045BFBC
	lwz      r0, 0x24(r31)
	cmplw    r29, r0
	bne      lbl_8045BFBC
	stfs     f31, 0x50(r31)

lbl_8045BFBC:
	lwz      r30, 0xc(r30)

lbl_8045BFC0:
	cmplwi   r30, 0
	bne      lbl_8045BF88
	lwz      r0, 0x24(r1)
	lfd      f31, 0x18(r1)
	lwz      r31, 0x14(r1)
	lwz      r30, 0x10(r1)
	lwz      r29, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/**
 * @note Address: 0x8045BFE8
 * @note Size: 0x74
 */
void SetNoYOfset(PSSystem::EnvSeMgr* mgr)
{
	for (JSULink<PSSystem::EnvSeBase>* link = mgr->mEnvList.getFirst(); link; link = link->getNext()) {
		if (((EnvSe_Perspective_AvoidY*)link->mValue)->getCastType() == 'pers') {
			((EnvSe_Perspective_AvoidY*)link->mValue)->_48 = 0.0f;
		}
	}
}

/**
 * @note Address: 0x8045C05C
 * @note Size: 0x2C
 */
void EnvSeObjBuilder::setInfo(PersEnvInfo info) { mPersEnvInfo = info; }

/**
 * @note Address: 0x8045C088
 * @note Size: 0x70
 */
EnvSeObjBuilder::EnvSeObjBuilder(JGeometry::TBox3f p1)
    : PSGame::Builder_EvnSe_Perspective(p1)
{
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	lfs      f5, 0(r4)
	stw      r0, 0x34(r1)
	lfs      f4, 4(r4)
	stw      r31, 0x2c(r1)
	mr       r31, r3
	lfs      f3, 8(r4)
	lfs      f2, 0xc(r4)
	lfs      f1, 0x10(r4)
	lfs      f0, 0x14(r4)
	addi     r4, r1, 8
	stfs     f5, 8(r1)
	stfs     f4, 0xc(r1)
	stfs     f3, 0x10(r1)
	stfs     f2, 0x14(r1)
	stfs     f1, 0x18(r1)
	stfs     f0, 0x1c(r1)
	bl       "__ct__Q26PSGame25Builder_EvnSe_PerspectiveFQ29JGeometry8TBox3<f>"
	lis      r4, __vt__Q23PSM15EnvSeObjBuilder@ha
	mr       r3, r31
	addi     r0, r4, __vt__Q23PSM15EnvSeObjBuilder@l
	stw      r0, 0(r31)
	lwz      r31, 0x2c(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/**
 * @note Address: 0x8045C12C
 * @note Size: 0x164
 */
PSSystem::BgmSeq* SceneMgr::newAutoBgm(const char* bmsname, const char* cndname, JAInter::SoundInfo& info, JADUtility::AccessMode mode,
                                       PSGame::SceneInfo& sceneinfo, PSSystem::DirectorMgrBase* mgr)
{
	DirectorMgr_Scene* scene = new DirectorMgr_Scene_AutoBgm(mgr, 8);
	PSAutoBgm::AutoBgm* bgm  = new PSAutoBgm::AutoBgm(bmsname, cndname, info, mode, mgr);
	P2ASSERTLINE(1015, bgm);
	bgm->init();
	scene->initTrackMap(*bgm);
	scene->initAndAdaptToBgm(*bgm);

	PSAutoBgm::MeloArr_RandomAvoid* melo = new PSAutoBgm::MeloArr_RandomAvoid("�����ʒuAvoid");
	melo->_18                            = true;
	bgm->mMeloArr.mList.append(melo);
	return bgm;
	/*
	.loc_0x0:
	  stwu      r1, -0x30(r1)
	  mflr      r0
	  lis       r3, 0x804A
	  stw       r0, 0x34(r1)
	  stmw      r25, 0x14(r1)
	  subi      r31, r3, 0x3198
	  mr        r25, r4
	  mr        r26, r5
	  mr        r27, r6
	  mr        r28, r7
	  mr        r29, r9
	  li        r3, 0x88
	  bl        -0x4382B8
	  mr.       r30, r3
	  beq-      .loc_0x5C
	  mr        r4, r29
	  li        r5, 0x8
	  bl        0x1314C
	  lis       r3, 0x804F
	  subi      r3, r3, 0x6E8
	  stw       r3, 0x0(r30)
	  addi      r0, r3, 0x10
	  stw       r0, 0xC(r30)

	.loc_0x5C:
	  li        r3, 0x350
	  bl        -0x4382E8
	  mr.       r29, r3
	  beq-      .loc_0x88
	  mr        r4, r25
	  mr        r5, r26
	  mr        r6, r27
	  mr        r7, r28
	  mr        r8, r30
	  bl        -0x1205A8
	  mr        r29, r3

	.loc_0x88:
	  cmplwi    r29, 0
	  bne-      .loc_0xA4
	  addi      r3, r31, 0xC
	  addi      r5, r31, 0x24
	  li        r4, 0x3F7
	  crclr     6, 0x6
	  bl        -0x431B8C

	.loc_0xA4:
	  mr        r3, r29
	  lwz       r12, 0x10(r29)
	  lwz       r12, 0xC(r12)
	  mtctr     r12
	  bctrl
	  mr        r3, r30
	  mr        r4, r29
	  bl        0x13434
	  mr        r3, r30
	  mr        r4, r29
	  bl        -0x118928
	  li        r3, 0x20
	  bl        -0x43835C
	  mr.       r30, r3
	  beq-      .loc_0x138
	  mr        r25, r30
	  mr        r4, r30
	  bl        -0x435A5C
	  addi      r3, r25, 0x10
	  addi      r4, r31, 0x128
	  bl        -0x3A2034
	  lis       r4, 0x804E
	  lis       r3, 0x804E
	  subi      r4, r4, 0x5218
	  li        r5, 0x1
	  stw       r4, 0x14(r25)
	  addi      r0, r4, 0x8
	  subi      r3, r3, 0x51EC
	  li        r4, 0
	  stw       r0, 0x10(r25)
	  addi      r0, r3, 0x8
	  lfs       f0, 0x28E4(r2)
	  stb       r5, 0x18(r25)
	  stb       r4, 0x19(r25)
	  stw       r3, 0x14(r30)
	  stw       r0, 0x10(r30)
	  stfs      f0, 0x1C(r30)

	.loc_0x138:
	  li        r0, 0x1
	  mr        r4, r30
	  stb       r0, 0x18(r30)
	  addi      r3, r29, 0x340
	  bl        -0x435990
	  mr        r3, r29
	  lmw       r25, 0x14(r1)
	  lwz       r0, 0x34(r1)
	  mtlr      r0
	  addi      r1, r1, 0x30
	  blr
	*/
}

/**
 * @note Address: 0x8045C290
 * @note Size: 0x60
 */
MiddleBossSeq::MiddleBossSeq(const char* p1, const JAInter::SoundInfo& info, PSSystem::DirectorMgrBase* directorMgr)
    : PSSystem::JumpBgmSeq(p1, info, directorMgr)
    , mCurrBossObj(nullptr)
    , _138(0)
    , _13C(3)
    , _13E(-1)
    , _140(0)
{
	/*
	.loc_0x0:
	  stwu      r1, -0x10(r1)
	  mflr      r0
	  stw       r0, 0x14(r1)
	  stw       r31, 0xC(r1)
	  mr        r31, r3
	  bl        -0x129074
	  lis       r4, 0x804F
	  lis       r3, 0x1
	  subi      r0, r4, 0x1D70
	  li        r5, 0
	  stw       r0, 0x10(r31)
	  li        r4, 0x3
	  subi      r0, r3, 0x1
	  mr        r3, r31
	  stw       r5, 0x134(r31)
	  stw       r5, 0x138(r31)
	  sth       r4, 0x13C(r31)
	  sth       r0, 0x13E(r31)
	  stb       r5, 0x140(r31)
	  lwz       r31, 0xC(r1)
	  lwz       r0, 0x14(r1)
	  mtlr      r0
	  addi      r1, r1, 0x10
	  blr
	*/
}

/**
 * @note Address: 0x8045C2F0
 * @note Size: 0x94
 */
void MiddleBossSeq::onJump(u16 track)
{
	switch (track) {
	case 1:
	case 2:
	case 3:
	case 4:
		return;
	case 9:
		_13E = 0;
		break;
	}

	P2ASSERTLINE(1078, mCurrBossObj);
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	clrlwi   r0, r4, 0x10
	cmpwi    r0, 4
	stw      r31, 0xc(r1)
	mr       r31, r3
	beq      lbl_8045C370
	bge      lbl_8045C320
	cmpwi    r0, 3
	bge      lbl_8045C33C
	b        lbl_8045C370

lbl_8045C320:
	cmpwi    r0, 9
	beq      lbl_8045C330
	bge      lbl_8045C370
	b        lbl_8045C33C

lbl_8045C330:
	li       r0, 0
	sth      r0, 0x13e(r31)
	b        lbl_8045C370

lbl_8045C33C:
	lwz      r0, 0x134(r31)
	cmplwi   r0, 0
	bne      lbl_8045C364
	lis      r3, lbl_8049CE74@ha
	lis      r5, lbl_8049CE8C@ha
	addi     r3, r3, lbl_8049CE74@l
	li       r4, 0x436
	addi     r5, r5, lbl_8049CE8C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045C364:
	lwz      r3, 0x134(r31)
	li       r0, 1
	stb      r0, 0xff(r3)

lbl_8045C370:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8045C384
 * @note Size: 0x40
 */
void MiddleBossSeq::exec()
{
	SeqBase::exec();
	if (_13E != 0xffff) {
		_13E++;
	}
}

/**
 * @note Address: 0x8045C3C4
 * @note Size: 0x5C
 */
void MiddleBossSeq::requestJumpBgmQuickly(u16 flag)
{
	u16 flag2 = jumpCheck(flag);
	if (flag2 != 0xffff) {
		JumpBgmSeq::requestJumpBgmQuickly(flag2);
		JumpBgmSeq::setAvoidJumpTimer_Checked(_138);
	}
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r12, 0x10(r3)
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x10
	mr       r4, r3
	cmplwi   r0, 0xffff
	beq      lbl_8045C40C
	mr       r3, r31
	bl       requestJumpBgmQuickly__Q28PSSystem10JumpBgmSeqFUs
	lwz      r4, 0x138(r31)
	mr       r3, r31
	bl       setAvoidJumpTimer_Checked__Q28PSSystem10JumpBgmSeqFUl

lbl_8045C40C:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8045C420
 * @note Size: 0x5C
 */
void MiddleBossSeq::requestJumpBgmOnBeat(u16 flag)
{
	u16 flag2 = jumpCheck(flag);
	if (flag2 != 0xffff) {
		JumpBgmSeq::requestJumpBgmOnBeat(flag2);
		JumpBgmSeq::setAvoidJumpTimer_Checked(_138);
	}
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r12, 0x10(r3)
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x10
	mr       r4, r3
	cmplwi   r0, 0xffff
	beq      lbl_8045C468
	mr       r3, r31
	bl       requestJumpBgmOnBeat__Q28PSSystem10JumpBgmSeqFUs
	lwz      r4, 0x138(r31)
	mr       r3, r31
	bl       setAvoidJumpTimer_Checked__Q28PSSystem10JumpBgmSeqFUl

lbl_8045C468:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8045C47C
 * @note Size: 0x5C
 */
void MiddleBossSeq::requestJumpBgmEveryBeat(u16 flag)
{
	u16 flag2 = jumpCheck(flag);
	if (flag2 != 0xffff) {
		JumpBgmSeq::requestJumpBgmEveryBeat(flag2);
		JumpBgmSeq::setAvoidJumpTimer_Checked(_138);
	}
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r12, 0x10(r3)
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x10
	mr       r4, r3
	cmplwi   r0, 0xffff
	beq      lbl_8045C4C4
	mr       r3, r31
	bl       requestJumpBgmEveryBeat__Q28PSSystem10JumpBgmSeqFUs
	lwz      r4, 0x138(r31)
	mr       r3, r31
	bl       setAvoidJumpTimer_Checked__Q28PSSystem10JumpBgmSeqFUl

lbl_8045C4C4:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8045C4D8
 * @note Size: 0x214
 */
u32 MiddleBossSeq::jumpCheck(u16)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	li       r5, 1
	stw      r0, 0x14(r1)
	mr       r6, r5
	stw      r31, 0xc(r1)
	mr       r31, r4
	addi     r0, r31, -5
	li       r4, 0
	stw      r30, 8(r1)
	mr       r30, r3
	clrlwi   r3, r0, 0x10
	subfic   r0, r3, 1
	stw      r4, 0x138(r30)
	orc      r3, r5, r3
	srwi     r0, r0, 1
	subf     r0, r0, r3
	rlwinm.  r0, r0, 1, 0x1f, 0x1f
	bne      lbl_8045C528
	mr       r6, r4

lbl_8045C528:
	clrlwi.  r0, r6, 0x18
	bne      lbl_8045C540
	clrlwi   r0, r31, 0x10
	cmplwi   r0, 7
	beq      lbl_8045C540
	li       r5, 0

lbl_8045C540:
	clrlwi.  r0, r5, 0x18
	beq      lbl_8045C564
	lis      r3, lbl_8049CE74@ha
	lis      r5, lbl_8049CE8C@ha
	addi     r3, r3, lbl_8049CE74@l
	li       r4, 0x470
	addi     r5, r5, lbl_8049CE8C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045C564:
	lhz      r0, 0x130(r30)
	cmpwi    r0, 5
	bge      lbl_8045C580
	cmpwi    r0, 1
	beq      lbl_8045C598
	bge      lbl_8045C5D0
	b        lbl_8045C5D0

lbl_8045C580:
	cmpwi    r0, 9
	beq      lbl_8045C5D0
	bge      lbl_8045C5D0
	cmpwi    r0, 8
	bge      lbl_8045C5B0
	b        lbl_8045C5D0

lbl_8045C598:
	clrlwi   r0, r31, 0x10
	cmplwi   r0, 1
	bne      lbl_8045C5D0
	lis      r3, 0x0000FFFF@ha
	addi     r3, r3, 0x0000FFFF@l
	b        lbl_8045C6D4

lbl_8045C5B0:
	clrlwi   r0, r31, 0x10
	cmplwi   r0, 1
	beq      lbl_8045C5D0
	cmplwi   r0, 0xa
	beq      lbl_8045C5D0
	lis      r3, 0x0000FFFF@ha
	addi     r3, r3, 0x0000FFFF@l
	b        lbl_8045C6D4

lbl_8045C5D0:
	clrlwi   r0, r31, 0x10
	cmpwi    r0, 9
	beq      lbl_8045C6A8
	bge      lbl_8045C5F8
	cmpwi    r0, 4
	beq      lbl_8045C64C
	bge      lbl_8045C6D0
	cmpwi    r0, 3
	bge      lbl_8045C608
	b        lbl_8045C6D0

lbl_8045C5F8:
	cmpwi    r0, 0xb
	beq      lbl_8045C6C8
	bge      lbl_8045C6D0
	b        lbl_8045C6B4

lbl_8045C608:
	lhz      r3, 0x13c(r30)
	addi     r0, r3, 1
	sth      r0, 0x13c(r30)
	lhz      r0, 0x13c(r30)
	cmplwi   r0, 4
	bne      lbl_8045C62C
	li       r0, 5
	sth      r0, 0x13c(r30)
	b        lbl_8045C63C

lbl_8045C62C:
	cmplwi   r0, 8
	bne      lbl_8045C63C
	li       r0, 3
	sth      r0, 0x13c(r30)

lbl_8045C63C:
	lhz      r31, 0x13c(r30)
	li       r0, 0x32
	stw      r0, 0x138(r30)
	b        lbl_8045C6D0

lbl_8045C64C:
	lwz      r0, 0x134(r30)
	cmplwi   r0, 0
	bne      lbl_8045C674
	lis      r3, lbl_8049CE74@ha
	lis      r5, lbl_8049CE8C@ha
	addi     r3, r3, lbl_8049CE74@l
	li       r4, 0x4b5
	addi     r5, r5, lbl_8049CE8C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045C674:
	lhz      r0, 0x13e(r30)
	cmplwi   r0, 0x190
	blt      lbl_8045C690
	lwz      r3, 0x134(r30)
	lbz      r0, 0xff(r3)
	cmplwi   r0, 0
	bne      lbl_8045C69C

lbl_8045C690:
	lis      r3, 0x0000FFFF@ha
	addi     r3, r3, 0x0000FFFF@l
	b        lbl_8045C6D4

lbl_8045C69C:
	li       r0, 0x5a
	stw      r0, 0x138(r30)
	b        lbl_8045C6D0

lbl_8045C6A8:
	li       r0, 0xb4
	stw      r0, 0x138(r30)
	b        lbl_8045C6D0

lbl_8045C6B4:
	li       r3, 0xb4
	li       r0, 0
	stw      r3, 0x138(r30)
	stw      r0, 0x12c(r30)
	b        lbl_8045C6D0

lbl_8045C6C8:
	li       r0, 0
	stw      r0, 0x12c(r30)

lbl_8045C6D0:
	mr       r3, r31

lbl_8045C6D4:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8045C6EC
 * @note Size: 0x6C
 */
BigBossSeq::BigBossSeq(const char* p1, const JAInter::SoundInfo& info, PSSystem::DirectorMgrBase* directorMgr)
    : MiddleBossSeq(p1, info, directorMgr)
{
	/*
	.loc_0x0:
	  stwu      r1, -0x10(r1)
	  mflr      r0
	  stw       r0, 0x14(r1)
	  stw       r31, 0xC(r1)
	  mr        r31, r3
	  bl        -0x1294D0
	  lis       r3, 0x804F
	  lis       r4, 0x1
	  subi      r0, r3, 0x1D70
	  lis       r3, 0x804F
	  stw       r0, 0x10(r31)
	  li        r6, 0
	  li        r5, 0x3
	  subi      r4, r4, 0x1
	  stw       r6, 0x134(r31)
	  subi      r0, r3, 0x1DD8
	  mr        r3, r31
	  stw       r6, 0x138(r31)
	  sth       r5, 0x13C(r31)
	  sth       r4, 0x13E(r31)
	  stb       r6, 0x140(r31)
	  stw       r0, 0x10(r31)
	  lwz       r31, 0xC(r1)
	  lwz       r0, 0x14(r1)
	  mtlr      r0
	  addi      r1, r1, 0x10
	  blr
	*/
}

/**
 * @note Address: 0x8045C758
 * @note Size: 0x80
 */
MiddleBossSeq::~MiddleBossSeq()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8045C7BC
	lis      r4, __vt__Q23PSM13MiddleBossSeq@ha
	addi     r0, r4, __vt__Q23PSM13MiddleBossSeq@l
	stw      r0, 0x10(r30)
	beq      lbl_8045C7AC
	lis      r4, __vt__Q28PSSystem10JumpBgmSeq@ha
	addi     r0, r4, __vt__Q28PSSystem10JumpBgmSeq@l
	stw      r0, 0x10(r30)
	beq      lbl_8045C7AC
	lis      r5, __vt__Q28PSSystem11DirectedBgm@ha
	li       r4, 0
	addi     r0, r5, __vt__Q28PSSystem11DirectedBgm@l
	stw      r0, 0x10(r30)
	bl       __dt__Q28PSSystem6BgmSeqFv

lbl_8045C7AC:
	extsh.   r0, r31
	ble      lbl_8045C7BC
	mr       r3, r30
	bl       __dl__FPv

lbl_8045C7BC:
	lwz      r0, 0x14(r1)
	mr       r3, r30
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8045C7D8
 * @note Size: 0x1B4
 */
u32 BigBossSeq::jumpCheck(u16)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	li       r0, 0
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	mr       r30, r3
	stw      r0, 0x138(r3)
	lhz      r0, 0x130(r3)
	cmplwi   r0, 0xc
	bgt      lbl_8045C8C8
	lis      r3, lbl_804EE1F4@ha
	slwi     r0, r0, 2
	addi     r3, r3, lbl_804EE1F4@l
	lwzx     r0, r3, r0
	mtctr    r0
	bctr

lbl_8045C820:
	clrlwi   r0, r31, 0x10
	cmplwi   r0, 1
	bne      lbl_8045C8C8
	lis      r3, 0x0000FFFF@ha
	addi     r3, r3, 0x0000FFFF@l
	b        lbl_8045C974

lbl_8045C838:
	clrlwi   r0, r31, 0x10
	cmplwi   r0, 8
	bne      lbl_8045C8C8
	lis      r3, 0x0000FFFF@ha
	addi     r3, r3, 0x0000FFFF@l
	b        lbl_8045C974

lbl_8045C850:
	clrlwi   r0, r31, 0x10
	cmplwi   r0, 9
	bne      lbl_8045C8C8
	lis      r3, 0x0000FFFF@ha
	addi     r3, r3, 0x0000FFFF@l
	b        lbl_8045C974

lbl_8045C868:
	clrlwi   r0, r31, 0x10
	cmplwi   r0, 0xa
	bne      lbl_8045C8C8
	lis      r3, 0x0000FFFF@ha
	addi     r3, r3, 0x0000FFFF@l
	b        lbl_8045C974

lbl_8045C880:
	clrlwi   r0, r31, 0x10
	cmplwi   r0, 0xb
	bne      lbl_8045C8C8
	lis      r3, 0x0000FFFF@ha
	addi     r3, r3, 0x0000FFFF@l
	b        lbl_8045C974

lbl_8045C898:

lbl_8045C898:

lbl_8045C898:

lbl_8045C898:
	clrlwi   r3, r31, 0x10
	cmplwi   r3, 1
	beq      lbl_8045C8C8
	addi     r0, r31, -8
	clrlwi   r0, r0, 0x10
	cmplwi   r0, 3
	ble      lbl_8045C8C8
	cmplwi   r3, 0xd
	beq      lbl_8045C8C8
	lis      r3, 0x0000FFFF@ha
	addi     r3, r3, 0x0000FFFF@l
	b        lbl_8045C974

lbl_8045C8C8:
	clrlwi   r0, r31, 0x10
	cmpwi    r0, 0xc
	beq      lbl_8045C94C
	bge      lbl_8045C8E4
	cmpwi    r0, 4
	beq      lbl_8045C8F0
	b        lbl_8045C970

lbl_8045C8E4:
	cmpwi    r0, 0xe
	bge      lbl_8045C970
	b        lbl_8045C960

lbl_8045C8F0:
	lwz      r0, 0x134(r30)
	cmplwi   r0, 0
	bne      lbl_8045C918
	lis      r3, lbl_8049CE74@ha
	lis      r5, lbl_8049CE8C@ha
	addi     r3, r3, lbl_8049CE74@l
	li       r4, 0x534
	addi     r5, r5, lbl_8049CE8C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045C918:
	lhz      r0, 0x13e(r30)
	cmplwi   r0, 0x320
	blt      lbl_8045C934
	lwz      r3, 0x134(r30)
	lbz      r0, 0xff(r3)
	cmplwi   r0, 0
	bne      lbl_8045C940

lbl_8045C934:
	lis      r3, 0x0000FFFF@ha
	addi     r3, r3, 0x0000FFFF@l
	b        lbl_8045C974

lbl_8045C940:
	li       r0, 0x5a
	stw      r0, 0x138(r30)
	b        lbl_8045C970

lbl_8045C94C:
	li       r3, 0xb4
	li       r0, 0
	stw      r3, 0x138(r30)
	stw      r0, 0x12c(r30)
	b        lbl_8045C970

lbl_8045C960:
	li       r3, 0xb4
	li       r0, 0
	stw      r3, 0x138(r30)
	stw      r0, 0x12c(r30)

lbl_8045C970:
	mr       r3, r31

lbl_8045C974:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8045C98C
 * @note Size: 0x98
 */
void BigBossSeq::onJump(u16)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	clrlwi   r0, r4, 0x10
	cmpwi    r0, 8
	stw      r31, 0xc(r1)
	mr       r31, r3
	bge      lbl_8045C9C4
	cmpwi    r0, 4
	beq      lbl_8045CA10
	bge      lbl_8045C9DC
	cmpwi    r0, 3
	bge      lbl_8045C9DC
	b        lbl_8045CA10

lbl_8045C9C4:
	cmpwi    r0, 0xc
	beq      lbl_8045C9D0
	b        lbl_8045CA10

lbl_8045C9D0:
	li       r0, 0
	sth      r0, 0x13e(r31)
	b        lbl_8045CA10

lbl_8045C9DC:
	lwz      r0, 0x134(r31)
	cmplwi   r0, 0
	bne      lbl_8045CA04
	lis      r3, lbl_8049CE74@ha
	lis      r5, lbl_8049CE8C@ha
	addi     r3, r3, lbl_8049CE74@l
	li       r4, 0x562
	addi     r5, r5, lbl_8049CE8C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045CA04:
	lwz      r3, 0x134(r31)
	li       r0, 1
	stb      r0, 0xff(r3)

lbl_8045CA10:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8045CA24
 * @note Size: 0x58
 */
PersEnvManager::PersEnvManager(PSSystem::EnvSeMgr* mgr)
{
	mEnvSeMgr = mgr;
	_04       = 3;
	_08       = new EnvSe_Perspective_AvoidY*[3];
	_0C       = new f32[3];
	_10       = 0.0f;
}

/**
 * @note Address: 0x8045CA7C
 * @note Size: 0x40
 */
bool PersEnvManager::playOk(EnvSe_Perspective_AvoidY* se)
{
	for (u8 i = 0; i < _04; i++) {
		if (_08[i] == se) {
			return true;
		}
	}
	return false;
}

/**
 * @note Address: 0x8045CABC
 * @note Size: 0x1C4
 */
void PersEnvManager::exec()
{
	/*
	stwu     r1, -0x50(r1)
	mflr     r0
	stw      r0, 0x54(r1)
	stmw     r26, 0x38(r1)
	mr       r26, r3
	lwz      r3, naviMgr__4Game@sda21(r13)
	bl       getActiveNavi__Q24Game7NaviMgrFv
	or.      r29, r3, r3
	beq      lbl_8045CC6C
	lfs      f0, lbl_80520C48@sda21(r2)
	li       r5, 0
	li       r4, 0
	b        lbl_8045CB08

lbl_8045CAF0:
	lwz      r3, 8(r26)
	rlwinm   r0, r5, 2, 0x16, 0x1d
	addi     r5, r5, 1
	stwx     r4, r3, r0
	lwz      r3, 0xc(r26)
	stfsx    f0, r3, r0

lbl_8045CB08:
	lbz      r0, 4(r26)
	clrlwi   r3, r5, 0x18
	cmplw    r3, r0
	blt      lbl_8045CAF0
	li       r28, 0
	b        lbl_8045CC5C

lbl_8045CB20:
	lwz      r3, 0(r26)
	rlwinm   r30, r28, 2, 0x16, 0x1d
	lwz      r27, 0(r3)
	b        lbl_8045CC50

lbl_8045CB30:
	lwz      r31, 0(r27)
	mr       r3, r31
	lwz      r12, 0x10(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	addis    r0, r3, 0x8f9b
	cmplwi   r0, 0x7273
	bne      lbl_8045CC4C
	clrlwi   r0, r28, 0x18
	li       r5, 0
	li       r6, 0
	b        lbl_8045CB84

lbl_8045CB64:
	lwz      r4, 8(r26)
	rlwinm   r3, r6, 2, 0x16, 0x1d
	lwzx     r3, r4, r3
	cmplw    r3, r31
	bne      lbl_8045CB80
	li       r5, 1
	b        lbl_8045CB90

lbl_8045CB80:
	addi     r6, r6, 1

lbl_8045CB84:
	clrlwi   r3, r6, 0x18
	cmplw    r3, r0
	blt      lbl_8045CB64

lbl_8045CB90:
	clrlwi.  r0, r5, 0x18
	bne      lbl_8045CC4C
	mr       r4, r29
	lwz      r6, 0x3c(r31)
	lwz      r12, 0(r29)
	addi     r3, r1, 0x14
	lwz      r5, 0x40(r31)
	lwz      r0, 0x44(r31)
	lwz      r12, 8(r12)
	stw      r6, 0x2c(r1)
	stw      r5, 0x30(r1)
	stw      r0, 0x34(r1)
	mtctr    r12
	bctrl
	lfs      f1, 0x14(r1)
	lfs      f0, 0x1c(r1)
	stfs     f1, 8(r1)
	lfs      f4, 0x18(r1)
	stfs     f0, 0x10(r1)
	lwz      r3, 8(r1)
	lwz      r0, 0x10(r1)
	stw      r3, 0x20(r1)
	lfs      f3, 0x2c(r1)
	stw      r0, 0x28(r1)
	lfs      f2, 0x20(r1)
	lfs      f1, 0x34(r1)
	lfs      f0, 0x28(r1)
	fsubs    f2, f3, f2
	stfs     f4, 0xc(r1)
	fsubs    f1, f1, f0
	lfs      f0, lbl_80520C24@sda21(r2)
	fmuls    f2, f2, f2
	lwz      r0, 0xc(r1)
	fmuls    f1, f1, f1
	stw      r0, 0x24(r1)
	fadds    f1, f2, f1
	fcmpo    cr0, f1, f0
	ble      lbl_8045CC30
	frsqrte  f0, f1
	fmuls    f1, f0, f1

lbl_8045CC30:
	lwz      r0, 0xc(r26)
	lfsx     f0, r30, r0
	fcmpo    cr0, f0, f1
	ble      lbl_8045CC4C
	stfsx    f1, r30, r0
	lwz      r0, 8(r26)
	stwx     r31, r30, r0

lbl_8045CC4C:
	lwz      r27, 0xc(r27)

lbl_8045CC50:
	cmplwi   r27, 0
	bne      lbl_8045CB30
	addi     r28, r28, 1

lbl_8045CC5C:
	lbz      r0, 4(r26)
	clrlwi   r3, r28, 0x18
	cmplw    r3, r0
	blt      lbl_8045CB20

lbl_8045CC6C:
	lmw      r26, 0x38(r1)
	lwz      r0, 0x54(r1)
	mtlr     r0
	addi     r1, r1, 0x50
	blr
	*/
}

} // namespace PSM
