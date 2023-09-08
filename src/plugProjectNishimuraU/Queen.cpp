#include "Game/Entities/Queen.h"
#include "Game/Entities/Baby.h"
#include "Game/generalEnemyMgr.h"
#include "Game/EnemyFunc.h"
#include "Game/Stickers.h"
#include "Game/SingleGameSection.h"
#include "PSM/EnemyBoss.h"
#include "PSSystem/PSMainSide_ObjSound.h"
#include "Dolphin/rand.h"
#include "nans.h"

namespace Game {
namespace Queen {

/*
 * --INFO--
 * Address:	802894D4
 * Size:	00017C
 */
Obj::Obj()
{
	mAnimator = new ProperAnimator;
	setFSM(new FSM);
	mShadowMgr       = new QueenShadowMgr(this);
	mMatLoopAnimator = new Sys::MatLoopAnimator;
	createEffect();
}

/*
 * --INFO--
 * Address:	80289650
 * Size:	000004
 */
void Obj::setInitialSetting(EnemyInitialParamBase*) { }

/*
 * --INFO--
 * Address:	80289654
 * Size:	000100
 */
void Obj::onInit(CreatureInitArg* initArg)
{
	EnemyBase::onInit(initArg);
	disableEvent(0, EB_PlatformCollEnabled);
	disableEvent(0, EB_Cullable);
	mNextState = QUEEN_NULL;
	_2C2       = 0;
	mWaitTimer = 0.0f;
	_2C1       = 0;
	_2CC       = 0.0f;
	_2D0       = 0.0f;
	resetJointShadow();
	mShadowMgr->init();
	setupEffect();
	_2C4 = 0;
	_2C5 = 0;
	resetMidBossAppearBGM();
	mMatLoopAnimator->start(C_MGR->mTexAnimation);

	if (mCanCreateLarva) {
		mFsm->start(this, QUEEN_Wait, nullptr);
	} else {
		mFsm->start(this, QUEEN_Sleep, nullptr);
	}
}

/*
 * --INFO--
 * Address:	80289754
 * Size:	000058
 */
void Obj::onKill(CreatureKillArg* killArg)
{
	finishRollingEffect(false);
	finishDamageEffect();
	finishSleepEffect();
	EnemyBase::onKill(killArg);
}

/*
 * --INFO--
 * Address:	802897AC
 * Size:	0000B8
 */
void Obj::setParameters()
{
	mCanCreateLarva = true;
	_2C3            = 0;

	if (gameSystem) {
		if (gameSystem->mMode == GSM_PIKLOPEDIA) {
			mCanCreateLarva = false;

		} else if (gameSystem->mIsInCave && gameSystem->mMode == GSM_STORY_MODE) {
			SingleGameSection* section = static_cast<SingleGameSection*>(gameSystem->mSection);
			if (section && section->getCaveID() == 'f_01') { // if in Hole of Beasts
				mCanCreateLarva                  = false;
				_2C3                             = 1;
				C_PARMS->mGeneral.mHealth.mValue = C_PROPERPARMS.mHoBHealth.mValue;
			}
		}
	}

	EnemyBase::setParameters();
}

/*
 * --INFO--
 * Address:	80289864
 * Size:	000050
 */
void Obj::doUpdate()
{
	mShadowMgr->update();
	updateCreateBaby();
	mFsm->exec(this);
}

/*
 * --INFO--
 * Address:	802898B4
 * Size:	000034
 */
void Obj::doUpdateCommon()
{
	EnemyBase::doUpdateCommon();
	updateBossBGM();
}

/*
 * --INFO--
 * Address:	802898E8
 * Size:	000054
 */
void Obj::doAnimationCullingOff()
{
	EnemyBase::doAnimationCullingOff();
	if (isAlive()) {
		mMatLoopAnimator->animate(30.0f);
	}
}

/*
 * --INFO--
 * Address:	8028993C
 * Size:	000004
 */
void Obj::doDirectDraw(Graphics&) { }

/*
 * --INFO--
 * Address:	80289940
 * Size:	000020
 */
void Obj::doDebugDraw(Graphics& gfx) { EnemyBase::doDebugDraw(gfx); }

/*
 * --INFO--
 * Address:	80289960
 * Size:	00004C
 */
void Obj::setFSM(FSM* fsm)
{
	mFsm = fsm;
	mFsm->init(this);
	mCurrentLifecycleState = nullptr;
}

/*
 * --INFO--
 * Address:	802899AC
 * Size:	00008C
 */
void Obj::getShadowParam(ShadowParam& shadowParam)
{
	shadowParam.mPosition = getPosition();
	shadowParam.mPosition.y += 15.0f;
	shadowParam.mBoundingSphere.mPosition = Vector3f(0.0f, 1.0f, 0.0f);
	shadowParam.mBoundingSphere.mRadius   = 50.0f;
	shadowParam.mSize                     = 45.0f;
}

/*
 * --INFO--
 * Address:	80289A38
 * Size:	0000B0
 */
bool Obj::damageCallBack(Creature* creature, f32 damage, CollPart* part)
{
	if (part && creature && creature->isPiki()) {
		int stateID = getStateID();
		if (stateID == QUEEN_Sleep) {
			damage *= 0.1f;
		} else if (stateID == QUEEN_Flick) {
			damage *= 0.2f;
		}

		addDamage(damage, 1.0f);
		return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	80289AE8
 * Size:	000008
 */
bool Obj::earthquakeCallBack(Creature* creature, f32 damage) { return false; }

/*
 * --INFO--
 * Address:	80289AF0
 * Size:	00004C
 */
void Obj::doStartStoneState()
{
	EnemyBase::doStartStoneState();
	finishSleepEffect();
	finishDamageEffect();
	forceFinishRollingEffect();
	startStoneStateBossAttackLoopBGM();
}

/*
 * --INFO--
 * Address:	80289B3C
 * Size:	000088
 */
void Obj::doFinishStoneState()
{
	EnemyBase::doFinishStoneState();
	EnemyFunc::flickStickPikmin(this, 1.0f, 10.0f, 0.0f, -1000.0f, nullptr);

	int stateID = getStateID();
	if (stateID == QUEEN_Damage) {
		startDamageEffect();
	} else if (stateID == QUEEN_Rolling && _2C2) {
		startRollingEffect();
	}

	finishStoneStateBossAttackLoopBGM();
}

/*
 * --INFO--
 * Address:	80289BC4
 * Size:	000084
 */
bool Obj::ignoreAtari(Creature* creature)
{
	if (_2C2 && !isEvent(0, EB_Bittered) && (creature->isNavi() || creature->isTeki())) {
		return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	80289C48
 * Size:	000028
 */
void Obj::startCarcassMotion() { startMotion(8, nullptr); }

/*
 * --INFO--
 * Address:	80289C70
 * Size:	000020
 */
void Obj::doStartMovie() { effectDrawOff(); }

/*
 * --INFO--
 * Address:	80289C90
 * Size:	000020
 */
void Obj::doEndMovie() { effectDrawOn(); }

/*
 * --INFO--
 * Address:	80289CB0
 * Size:	0002EC
 */
void Obj::rollingAttack()
{
	Vector3f pos     = getPosition(); // f26, f27, f28
	f32 angle        = getFaceDir();
	f32 attackRadius = C_PARMS->mGeneral.mAttackRadius.mValue;   // f25
	f32 attackAngle  = C_PARMS->mGeneral.mAttackHitAngle.mValue; // f24
	f32 cosTheta     = pikmin2_cosf(angle);                      // f30
	f32 sinTheta     = pikmin2_sinf(angle);                      // f29
	Vector3f forward(cosTheta, 0.0f, sinTheta);
	Vector3f back(-cosTheta, 0.0f, sinTheta); // f31, , f29

	Sys::Sphere sphere(mPosition, 250.0f);
	CellIteratorArg iterArg(sphere);
	iterArg._1C = 1;
	CellIterator iter(iterArg);

	CI_LOOP(iter)
	{
		Creature* creature = static_cast<Creature*>(*iter);
		if (creature->isAlive()) {
			Vector3f creaturePos = creature->getPosition();
			Vector3f sep         = creaturePos - pos;
			if (absVal(sep.y) < 50.0f) {
				if (absVal(back.dot(sep)) < attackAngle) {
					if (absVal(forward.dot(sep)) < attackRadius) {
						InteractPress press(this, C_PARMS->mGeneral.mAttackDamage.mValue, nullptr);
						creature->stimulate(press);
					}
				}
			}
		}
	}
	/*
	stwu     r1, -0x150(r1)
	mflr     r0
	stw      r0, 0x154(r1)
	stfd     f31, 0x140(r1)
	psq_st   f31, 328(r1), 0, qr0
	stfd     f30, 0x130(r1)
	psq_st   f30, 312(r1), 0, qr0
	stfd     f29, 0x120(r1)
	psq_st   f29, 296(r1), 0, qr0
	stfd     f28, 0x110(r1)
	psq_st   f28, 280(r1), 0, qr0
	stfd     f27, 0x100(r1)
	psq_st   f27, 264(r1), 0, qr0
	stfd     f26, 0xf0(r1)
	psq_st   f26, 248(r1), 0, qr0
	stfd     f25, 0xe0(r1)
	psq_st   f25, 232(r1), 0, qr0
	stfd     f24, 0xd0(r1)
	psq_st   f24, 216(r1), 0, qr0
	stw      r31, 0xcc(r1)
	stw      r30, 0xc8(r1)
	mr       r31, r3
	addi     r3, r1, 0x14
	mr       r4, r31
	lwz      r12, 0(r31)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	mr       r3, r31
	lfs      f28, 0x14(r1)
	lwz      r12, 0(r31)
	lfs      f27, 0x18(r1)
	lwz      r12, 0x64(r12)
	lfs      f26, 0x1c(r1)
	mtctr    r12
	bctrl
	fmr      f2, f1
	lwz      r3, 0xc0(r31)
	lfs      f0, lbl_8051B818@sda21(r2)
	lfs      f25, 0x5b4(r3)
	fcmpo    cr0, f2, f0
	lfs      f24, 0x5dc(r3)
	bge      lbl_80289D60
	fneg     f2, f2

lbl_80289D60:
	lfs      f3, lbl_8051B840@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	lfs      f0, lbl_8051B818@sda21(r2)
	addi     r4, r3, sincosTable___5JMath@l
	fmuls    f2, f2, f3
	fcmpo    cr0, f1, f0
	fctiwz   f0, f2
	stfd     f0, 0xa8(r1)
	lwz      r0, 0xac(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r4, r0
	lfs      f30, 4(r3)
	bge      lbl_80289DB8
	lfs      f0, lbl_8051B844@sda21(r2)
	fmuls    f0, f1, f0
	fctiwz   f0, f0
	stfd     f0, 0xb0(r1)
	lwz      r0, 0xb4(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r4, r0
	fneg     f29, f0
	b        lbl_80289DD0

lbl_80289DB8:
	fmuls    f0, f1, f3
	fctiwz   f0, f0
	stfd     f0, 0xb8(r1)
	lwz      r0, 0xbc(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f29, r4, r0

lbl_80289DD0:
	lfs      f1, 0x18c(r31)
	fneg     f31, f30
	lfs      f0, lbl_8051B848@sda21(r2)
	addi     r3, r1, 0x40
	stfs     f1, 0x30(r1)
	addi     r4, r1, 0x30
	lfs      f1, 0x190(r31)
	stfs     f1, 0x34(r1)
	lfs      f1, 0x194(r31)
	stfs     f1, 0x38(r1)
	stfs     f0, 0x3c(r1)
	bl       __ct__Q24Game15CellIteratorArgFRQ23Sys6Sphere
	li       r0, 1
	addi     r3, r1, 0x60
	stb      r0, 0x5c(r1)
	addi     r4, r1, 0x40
	bl       __ct__Q24Game12CellIteratorFRQ24Game15CellIteratorArg
	addi     r3, r1, 0x60
	bl       first__Q24Game12CellIteratorFv
	b        lbl_80289F34

lbl_80289E20:
	addi     r3, r1, 0x60
	bl       __ml__Q24Game12CellIteratorFv
	lwz      r12, 0(r3)
	mr       r30, r3
	lwz      r12, 0xa8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80289F2C
	mr       r4, r30
	addi     r3, r1, 8
	lwz      r12, 0(r30)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f0, 0xc(r1)
	lfs      f2, 0x10(r1)
	fsubs    f3, f0, f27
	lfs      f1, 8(r1)
	lfs      f0, lbl_8051B818@sda21(r2)
	fsubs    f4, f2, f26
	fsubs    f2, f1, f28
	fcmpo    cr0, f3, f0
	ble      lbl_80289E88
	fmr      f1, f3
	b        lbl_80289E8C

lbl_80289E88:
	fneg     f1, f3

lbl_80289E8C:
	lfs      f0, lbl_8051B828@sda21(r2)
	fcmpo    cr0, f1, f0
	bge      lbl_80289F2C
	lfs      f1, lbl_8051B818@sda21(r2)
	fmuls    f3, f1, f3
	fmadds   f0, f31, f2, f3
	fmadds   f0, f29, f4, f0
	fcmpo    cr0, f0, f1
	ble      lbl_80289EB4
	b        lbl_80289EB8

lbl_80289EB4:
	fneg     f0, f0

lbl_80289EB8:
	fcmpo    cr0, f0, f24
	bge      lbl_80289F2C
	fmadds   f1, f29, f2, f3
	lfs      f0, lbl_8051B818@sda21(r2)
	fmadds   f1, f30, f4, f1
	fcmpo    cr0, f1, f0
	ble      lbl_80289ED8
	b        lbl_80289EDC

lbl_80289ED8:
	fneg     f1, f1

lbl_80289EDC:
	fcmpo    cr0, f1, f25
	bge      lbl_80289F2C
	lwz      r5, 0xc0(r31)
	lis      r4, __vt__Q24Game11Interaction@ha
	lis      r3, __vt__Q24Game13InteractPress@ha
	li       r0, 0
	lfs      f0, 0x604(r5)
	addi     r4, r4, __vt__Q24Game11Interaction@l
	addi     r5, r3, __vt__Q24Game13InteractPress@l
	mr       r3, r30
	stw      r4, 0x20(r1)
	addi     r4, r1, 0x20
	stw      r31, 0x24(r1)
	stw      r5, 0x20(r1)
	stfs     f0, 0x28(r1)
	stw      r0, 0x2c(r1)
	lwz      r12, 0(r30)
	lwz      r12, 0x1a4(r12)
	mtctr    r12
	bctrl

lbl_80289F2C:
	addi     r3, r1, 0x60
	bl       next__Q24Game12CellIteratorFv

lbl_80289F34:
	addi     r3, r1, 0x60
	bl       isDone__Q24Game12CellIteratorFv
	clrlwi.  r0, r3, 0x18
	beq      lbl_80289E20
	psq_l    f31, 328(r1), 0, qr0
	lfd      f31, 0x140(r1)
	psq_l    f30, 312(r1), 0, qr0
	lfd      f30, 0x130(r1)
	psq_l    f29, 296(r1), 0, qr0
	lfd      f29, 0x120(r1)
	psq_l    f28, 280(r1), 0, qr0
	lfd      f28, 0x110(r1)
	psq_l    f27, 264(r1), 0, qr0
	lfd      f27, 0x100(r1)
	psq_l    f26, 248(r1), 0, qr0
	lfd      f26, 0xf0(r1)
	psq_l    f25, 232(r1), 0, qr0
	lfd      f25, 0xe0(r1)
	psq_l    f24, 216(r1), 0, qr0
	lfd      f24, 0xd0(r1)
	lwz      r31, 0xcc(r1)
	lwz      r0, 0x154(r1)
	lwz      r30, 0xc8(r1)
	mtlr     r0
	addi     r1, r1, 0x150
	blr
	*/
}

/*
 * --INFO--
 * Address:	80289F9C
 * Size:	0003A8
 */
void Obj::flickPikmin(f32 angle)
{
	f32 bodyAngle = PI + angle;

	Stickers stickers(this);
	Iterator<Creature> iter(&stickers);
	CI_LOOP(iter)
	{
		Creature* stuck = *iter;
		if (stuck->isAlive()) {
			CollPart* stuckPart = stuck->mStuckCollPart;
			if (stuckPart) {
				if (stuckPart->mCurrentID == 'nose' || stuckPart->mCurrentID == 'head' || stuckPart->mCurrentID == 'bod1') {
					InteractFlick flick(this, C_PARMS->mGeneral.mShakeKnockback.mValue, C_PARMS->mGeneral.mShakeDamage.mValue, angle);
					stuck->stimulate(flick);

				} else if (stuckPart->mCurrentID == 'bod5') {
					InteractFlick flick(this, C_PARMS->mGeneral.mShakeKnockback.mValue, C_PARMS->mGeneral.mShakeDamage.mValue, bodyAngle);
					stuck->stimulate(flick);

				} else {
					InteractFlick flick(this, 0.0f, 0.0f, -1000.0f);
					stuck->stimulate(flick);
				}
			}
		}
	}
}

/*
 * --INFO--
 * Address:	8028A344
 * Size:	0001A8
 */
bool Obj::isRollingAttackLeft()
{
	/*
	stwu     r1, -0x60(r1)
	mflr     r0
	stw      r0, 0x64(r1)
	stfd     f31, 0x50(r1)
	psq_st   f31, 88(r1), 0, qr0
	stfd     f30, 0x40(r1)
	psq_st   f30, 72(r1), 0, qr0
	stw      r31, 0x3c(r1)
	stw      r30, 0x38(r1)
	mr       r30, r3
	lbz      r0, 0x2c3(r3)
	cmplwi   r0, 0
	beq      lbl_8028A484
	li       r0, 0
	stb      r0, 0x2c3(r30)
	lwz      r3, naviMgr__4Game@sda21(r13)
	bl       getActiveNavi__Q24Game7NaviMgrFv
	or.      r31, r3, r3
	beq      lbl_8028A47C
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	lfs      f2, lbl_8051B850@sda21(r2)
	lfs      f0, lbl_8051B818@sda21(r2)
	fadds    f3, f2, f1
	fmr      f1, f3
	fcmpo    cr0, f3, f0
	bge      lbl_8028A3C0
	fneg     f1, f3

lbl_8028A3C0:
	lfs      f2, lbl_8051B840@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	lfs      f0, lbl_8051B818@sda21(r2)
	addi     r4, r3, sincosTable___5JMath@l
	fmuls    f1, f1, f2
	fcmpo    cr0, f3, f0
	fctiwz   f0, f1
	stfd     f0, 0x18(r1)
	lwz      r0, 0x1c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r4, r0
	lfs      f31, 4(r3)
	bge      lbl_8028A418
	lfs      f0, lbl_8051B844@sda21(r2)
	fmuls    f0, f3, f0
	fctiwz   f0, f0
	stfd     f0, 0x20(r1)
	lwz      r0, 0x24(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r4, r0
	fneg     f30, f0
	b        lbl_8028A430

lbl_8028A418:
	fmuls    f0, f3, f2
	fctiwz   f0, f0
	stfd     f0, 0x28(r1)
	lwz      r0, 0x2c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f30, r4, r0

lbl_8028A430:
	mr       r4, r31
	addi     r3, r1, 8
	lwz      r12, 0(r31)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f1, 8(r1)
	lfs      f0, 0x18c(r30)
	lfs      f3, 0x10(r1)
	lfs      f2, 0x194(r30)
	fsubs    f0, f1, f0
	lfs      f1, lbl_8051B818@sda21(r2)
	fsubs    f2, f3, f2
	fmadds   f0, f30, f0, f1
	fmadds   f0, f31, f2, f0
	fcmpo    cr0, f0, f1
	ble      lbl_8028A47C
	li       r3, 0
	b        lbl_8028A4C4

lbl_8028A47C:
	li       r3, 1
	b        lbl_8028A4C4

lbl_8028A484:
	bl       rand
	xoris    r3, r3, 0x8000
	lis      r0, 0x4330
	stw      r3, 0x2c(r1)
	lfd      f3, lbl_8051B860@sda21(r2)
	stw      r0, 0x28(r1)
	lfs      f2, lbl_8051B824@sda21(r2)
	lfd      f0, 0x28(r1)
	lfs      f1, lbl_8051B854@sda21(r2)
	fsubs    f3, f0, f3
	lfs      f0, lbl_8051B858@sda21(r2)
	fmuls    f2, f2, f3
	fdivs    f1, f2, f1
	fcmpo    cr0, f1, f0
	mfcr     r0
	srwi     r3, r0, 0x1f

lbl_8028A4C4:
	psq_l    f31, 88(r1), 0, qr0
	lfd      f31, 0x50(r1)
	psq_l    f30, 72(r1), 0, qr0
	lfd      f30, 0x40(r1)
	lwz      r31, 0x3c(r1)
	lwz      r0, 0x64(r1)
	lwz      r30, 0x38(r1)
	mtlr     r0
	addi     r1, r1, 0x60
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028A4EC
 * Size:	0002D4
 */
void Obj::createCrashFallRock()
{
	/*
	stwu     r1, -0x140(r1)
	mflr     r0
	stw      r0, 0x144(r1)
	stfd     f31, 0x130(r1)
	psq_st   f31, 312(r1), 0, qr0
	stfd     f30, 0x120(r1)
	psq_st   f30, 296(r1), 0, qr0
	stfd     f29, 0x110(r1)
	psq_st   f29, 280(r1), 0, qr0
	stfd     f28, 0x100(r1)
	psq_st   f28, 264(r1), 0, qr0
	stfd     f27, 0xf0(r1)
	psq_st   f27, 248(r1), 0, qr0
	stfd     f26, 0xe0(r1)
	psq_st   f26, 232(r1), 0, qr0
	stfd     f25, 0xd0(r1)
	psq_st   f25, 216(r1), 0, qr0
	stfd     f24, 0xc0(r1)
	psq_st   f24, 200(r1), 0, qr0
	stfd     f23, 0xb0(r1)
	psq_st   f23, 184(r1), 0, qr0
	stfd     f22, 0xa0(r1)
	psq_st   f22, 168(r1), 0, qr0
	stfd     f21, 0x90(r1)
	psq_st   f21, 152(r1), 0, qr0
	stfd     f20, 0x80(r1)
	psq_st   f20, 136(r1), 0, qr0
	stfd     f19, 0x70(r1)
	psq_st   f19, 120(r1), 0, qr0
	stmw     r27, 0x5c(r1)
	lwz      r4, gameSystem__4Game@sda21(r13)
	mr       r31, r3
	cmplwi   r4, 0
	beq      lbl_8028A744
	lbz      r0, 0x48(r4)
	cmplwi   r0, 0
	beq      lbl_8028A744
	lwz      r0, 0x44(r4)
	cmpwi    r0, 0
	bne      lbl_8028A744
	lwz      r3, 0x58(r4)
	cmplwi   r3, 0
	beq      lbl_8028A744
	lwz      r12, 0(r3)
	lwz      r12, 0x78(r12)
	mtctr    r12
	bctrl
	addis    r0, r3, 0x93a1
	cmplwi   r0, 0x3032
	bne      lbl_8028A744
	lfs      f3, 0x1fc(r31)
	lfs      f0, lbl_8051B818@sda21(r2)
	fmr      f1, f3
	fcmpo    cr0, f3, f0
	bge      lbl_8028A5CC
	fneg     f1, f3

lbl_8028A5CC:
	lfs      f2, lbl_8051B840@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	lfs      f0, lbl_8051B818@sda21(r2)
	addi     r4, r3, sincosTable___5JMath@l
	fmuls    f1, f1, f2
	fcmpo    cr0, f3, f0
	fctiwz   f0, f1
	stfd     f0, 0x40(r1)
	lwz      r0, 0x44(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r4, r0
	lfs      f24, 4(r3)
	bge      lbl_8028A624
	lfs      f0, lbl_8051B844@sda21(r2)
	fmuls    f0, f3, f0
	fctiwz   f0, f0
	stfd     f0, 0x48(r1)
	lwz      r0, 0x4c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r4, r0
	fneg     f23, f0
	b        lbl_8028A63C

lbl_8028A624:
	fmuls    f0, f3, f2
	fctiwz   f0, f0
	stfd     f0, 0x50(r1)
	lwz      r0, 0x54(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f23, r4, r0

lbl_8028A63C:
	lfs      f2, lbl_8051B868@sda21(r2)
	fneg     f27, f23
	lfs      f1, 0x1a0(r31)
	li       r4, 0x13
	lfs      f0, 0x198(r31)
	fmadds   f25, f2, f24, f1
	lwz      r3, generalEnemyMgr__4Game@sda21(r13)
	fmadds   f26, f2, f23, f0
	bl       getEnemyMgr__Q24Game15GeneralEnemyMgrFi
	or.      r28, r3, r3
	beq      lbl_8028A744
	lfd      f28, lbl_8051B860@sda21(r2)
	li       r27, 0
	lfs      f29, lbl_8051B86C@sda21(r2)
	lis      r29, 0x4330
	lfs      f30, lbl_8051B854@sda21(r2)
	lfs      f31, lbl_8051B828@sda21(r2)
	lfs      f21, lbl_8051B818@sda21(r2)
	lfs      f22, lbl_8051B81C@sda21(r2)

lbl_8028A688:
	bl       rand
	xoris    r3, r3, 0x8000
	xoris    r0, r27, 0x8000
	stw      r3, 0x54(r1)
	addi     r3, r1, 8
	stw      r29, 0x50(r1)
	lfd      f0, 0x50(r1)
	stw      r0, 0x4c(r1)
	fsubs    f0, f0, f28
	stw      r29, 0x48(r1)
	fmuls    f1, f29, f0
	lfd      f0, 0x48(r1)
	fsubs    f0, f0, f28
	fdivs    f20, f1, f30
	fmsubs   f19, f31, f0, f29
	bl       __ct__Q24Game13EnemyBirthArgFv
	fmadds   f1, f23, f20, f26
	li       r0, 0x13
	fmadds   f0, f24, f20, f25
	stw      r0, 0x30(r1)
	mr       r3, r28
	addi     r4, r1, 8
	fmadds   f1, f24, f19, f1
	stfs     f21, 0xc(r1)
	fmadds   f0, f27, f19, f0
	stfs     f1, 8(r1)
	stfs     f0, 0x10(r1)
	lfs      f0, 0x1fc(r31)
	stfs     f0, 0x14(r1)
	stfs     f22, 0x34(r1)
	lwz      r12, 0(r28)
	lwz      r12, 0x70(r12)
	mtctr    r12
	bctrl
	or.      r30, r3, r3
	beq      lbl_8028A738
	li       r4, 0
	bl       init__Q24Game8CreatureFPQ24Game15CreatureInitArg
	lwz      r0, 0x1e0(r30)
	lfs      f0, lbl_8051B870@sda21(r2)
	rlwinm   r0, r0, 0, 0x1a, 0x18
	stw      r0, 0x1e0(r30)
	lwz      r3, 0xc0(r30)
	stfs     f0, 0x3d4(r3)

lbl_8028A738:
	addi     r27, r27, 1
	cmpwi    r27, 7
	blt      lbl_8028A688

lbl_8028A744:
	psq_l    f31, 312(r1), 0, qr0
	lfd      f31, 0x130(r1)
	psq_l    f30, 296(r1), 0, qr0
	lfd      f30, 0x120(r1)
	psq_l    f29, 280(r1), 0, qr0
	lfd      f29, 0x110(r1)
	psq_l    f28, 264(r1), 0, qr0
	lfd      f28, 0x100(r1)
	psq_l    f27, 248(r1), 0, qr0
	lfd      f27, 0xf0(r1)
	psq_l    f26, 232(r1), 0, qr0
	lfd      f26, 0xe0(r1)
	psq_l    f25, 216(r1), 0, qr0
	lfd      f25, 0xd0(r1)
	psq_l    f24, 200(r1), 0, qr0
	lfd      f24, 0xc0(r1)
	psq_l    f23, 184(r1), 0, qr0
	lfd      f23, 0xb0(r1)
	psq_l    f22, 168(r1), 0, qr0
	lfd      f22, 0xa0(r1)
	psq_l    f21, 152(r1), 0, qr0
	lfd      f21, 0x90(r1)
	psq_l    f20, 136(r1), 0, qr0
	lfd      f20, 0x80(r1)
	psq_l    f19, 120(r1), 0, qr0
	lfd      f19, 0x70(r1)
	lmw      r27, 0x5c(r1)
	lwz      r0, 0x144(r1)
	mtlr     r0
	addi     r1, r1, 0x140
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028A7C0
 * Size:	00019C
 */
void Obj::createBabyChappy()
{
	/*
	stwu     r1, -0x70(r1)
	mflr     r0
	li       r4, 0x1f
	stw      r0, 0x74(r1)
	stw      r31, 0x6c(r1)
	stw      r30, 0x68(r1)
	mr       r30, r3
	lwz      r3, generalEnemyMgr__4Game@sda21(r13)
	bl       getEnemyMgr__Q24Game15GeneralEnemyMgrFi
	or.      r31, r3, r3
	beq      lbl_8028A944
	addi     r3, r1, 0x14
	bl       __ct__Q24Game13EnemyBirthArgFv
	lis      r4, lbl_80487FF8@ha
	lwz      r3, 0x174(r30)
	addi     r4, r4, lbl_80487FF8@l
	bl       getJoint__Q28SysShape5ModelFPc
	bl       getWorldMatrix__Q28SysShape5JointFv
	lfs      f2, 0x2c(r3)
	lfs      f1, 0x1c(r3)
	lfs      f0, 0xc(r3)
	mr       r3, r30
	stfs     f0, 0x14(r1)
	stfs     f1, 0x18(r1)
	stfs     f2, 0x1c(r1)
	lwz      r12, 0(r30)
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	lfs      f0, lbl_8051B84C@sda21(r2)
	mr       r3, r31
	addi     r4, r1, 0x14
	fadds    f0, f0, f1
	stfs     f0, 0x20(r1)
	lwz      r12, 0(r31)
	lwz      r12, 0x70(r12)
	mtctr    r12
	bctrl
	or.      r31, r3, r3
	beq      lbl_8028A944
	lfs      f5, 0x20(r1)
	lfs      f0, lbl_8051B818@sda21(r2)
	fmr      f1, f5
	lwz      r5, 0xc0(r30)
	fcmpo    cr0, f5, f0
	bge      lbl_8028A87C
	fneg     f1, f5

lbl_8028A87C:
	lfs      f2, lbl_8051B840@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	lfs      f0, lbl_8051B818@sda21(r2)
	addi     r4, r3, sincosTable___5JMath@l
	fmuls    f1, f1, f2
	lfs      f3, 0x44c(r5)
	fcmpo    cr0, f5, f0
	fctiwz   f0, f1
	stfd     f0, 0x48(r1)
	lwz      r0, 0x4c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r4, r0
	lfs      f0, 4(r3)
	fmuls    f4, f3, f0
	bge      lbl_8028A8DC
	lfs      f0, lbl_8051B844@sda21(r2)
	fmuls    f0, f5, f0
	fctiwz   f0, f0
	stfd     f0, 0x50(r1)
	lwz      r0, 0x54(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r4, r0
	fneg     f0, f0
	b        lbl_8028A8F4

lbl_8028A8DC:
	fmuls    f0, f5, f2
	fctiwz   f0, f0
	stfd     f0, 0x58(r1)
	lwz      r0, 0x5c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r4, r0

lbl_8028A8F4:
	fmuls    f1, f3, f0
	lfs      f0, lbl_8051B818@sda21(r2)
	stfs     f4, 0x10(r1)
	mr       r3, r31
	li       r4, 0
	stfs     f1, 8(r1)
	stfs     f0, 0xc(r1)
	bl       init__Q24Game8CreatureFPQ24Game15CreatureInitArg
	mr       r3, r31
	addi     r4, r1, 8
	lwz      r12, 0(r31)
	lwz      r12, 0x68(r12)
	mtctr    r12
	bctrl
	lfs      f0, 8(r1)
	stfs     f0, 0x1d4(r31)
	lfs      f0, 0xc(r1)
	stfs     f0, 0x1d8(r31)
	lfs      f0, 0x10(r1)
	stfs     f0, 0x1dc(r31)

lbl_8028A944:
	lwz      r0, 0x74(r1)
	lwz      r31, 0x6c(r1)
	lwz      r30, 0x68(r1)
	mtlr     r0
	addi     r1, r1, 0x70
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028A9A8
 * Size:	000274
 */
void Obj::updateCreateBaby()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r30, r3
	lbz      r0, 0x2c0(r3)
	cmplwi   r0, 0
	beq      lbl_8028AC04
	lwz      r3, sys@sda21(r13)
	li       r31, 0
	lfs      f1, 0x2cc(r30)
	li       r4, 0x1f
	lfs      f0, 0x54(r3)
	fadds    f0, f1, f0
	stfs     f0, 0x2cc(r30)
	lwz      r3, generalEnemyMgr__4Game@sda21(r13)
	bl       getEnemyMgr__Q24Game15GeneralEnemyMgrFi
	cmplwi   r3, 0
	beq      lbl_8028ABD4
	beq      lbl_8028AA00
	addi     r3, r3, 4

lbl_8028AA00:
	li       r0, 0
	lis      r4, "__vt__Q24Game31EnemyIterator<Q34Game4Baby3Obj>"@ha
	addi     r4, r4, "__vt__Q24Game31EnemyIterator<Q34Game4Baby3Obj>"@l
	stw      r0, 0x14(r1)
	cmplwi   r0, 0
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8028AA3C
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8028ABB4

lbl_8028AA3C:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8028AAA8

lbl_8028AA54:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8028ABB4
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8028AAA8:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8028AA54
	b        lbl_8028ABB4

lbl_8028AAC8:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	lwz      r12, 0xa8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8028AAF8
	addi     r31, r31, 1

lbl_8028AAF8:
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_8028AB24
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8028ABB4

lbl_8028AB24:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8028AB98

lbl_8028AB44:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8028ABB4
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8028AB98:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8028AB44

lbl_8028ABB4:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_8028AAC8

lbl_8028ABD4:
	lwz      r3, 0xc0(r30)
	lwz      r0, 0x894(r3)
	cmpw     r31, r0
	blt      lbl_8028ABF0
	li       r0, 0
	stb      r0, 0x2c1(r30)
	b        lbl_8028AC04

lbl_8028ABF0:
	lwz      r0, 0x8bc(r3)
	cmpw     r31, r0
	bgt      lbl_8028AC04
	li       r0, 1
	stb      r0, 0x2c1(r30)

lbl_8028AC04:
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028AC1C
 * Size:	00003C
 */
bool Obj::isCreateBaby()
{
	/*
	lbz      r0, 0x2c0(r3)
	cmplwi   r0, 0
	beq      lbl_8028AC50
	lbz      r0, 0x2c1(r3)
	cmplwi   r0, 0
	beq      lbl_8028AC50
	lwz      r4, 0xc0(r3)
	lfs      f1, 0x2cc(r3)
	lfs      f0, 0x844(r4)
	fcmpo    cr0, f1, f0
	ble      lbl_8028AC50
	li       r3, 1
	blr

lbl_8028AC50:
	li       r3, 0
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028AC58
 * Size:	000018
 */
bool Obj::isHitCounterUp()
{
	/*
	lfs      f1, 0x20c(r3)
	lfs      f0, 0x2d0(r3)
	fcmpo    cr0, f1, f0
	mfcr     r0
	rlwinm   r3, r0, 2, 0x1f, 0x1f
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028AC70
 * Size:	000028
 */
void Obj::resetJointShadow()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	mr       r4, r3
	stw      r0, 0x14(r1)
	lwz      r3, shadowMgr__4Game@sda21(r13)
	bl       delNormalShadow__Q24Game9ShadowMgrFPQ24Game8Creature
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028AC98
 * Size:	000040
 */
void Obj::releaseJointShadow()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	mr       r4, r31
	lwz      r3, shadowMgr__4Game@sda21(r13)
	bl       addNormalShadow__Q24Game9ShadowMgrFPQ24Game8Creature
	lwz      r3, shadowMgr__4Game@sda21(r13)
	mr       r4, r31
	bl       delJointShadow__Q24Game9ShadowMgrFPQ24Game8Creature
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028ACD8
 * Size:	0000C8
 */
void Obj::startBossChargeBGM()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	li       r31, 0
	stw      r30, 8(r1)
	lwz      r30, 0x28c(r3)
	lwz      r12, 0x28(r30)
	mr       r3, r30
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 5
	beq      lbl_8028AD48
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 6
	beq      lbl_8028AD48
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 7
	bne      lbl_8028AD4C

lbl_8028AD48:
	li       r31, 1

lbl_8028AD4C:
	clrlwi.  r0, r31, 0x18
	bne      lbl_8028AD70
	lis      r3, lbl_80488004@ha
	lis      r5, lbl_8048801C@ha
	addi     r3, r3, lbl_80488004@l
	li       r4, 0x454
	addi     r5, r5, lbl_8048801C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8028AD70:
	mr       r3, r30
	li       r4, 2
	lwz      r12, 0x28(r30)
	lwz      r12, 0xd4(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028ADA0
 * Size:	0000DC
 */
void Obj::startBossAttackLoopBGM()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	lbz      r0, 0x2c5(r3)
	cmplwi   r0, 0
	bne      lbl_8028AE64
	li       r0, 1
	li       r31, 0
	stb      r0, 0x2c5(r3)
	lwz      r30, 0x28c(r3)
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 5
	beq      lbl_8028AE24
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 6
	beq      lbl_8028AE24
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 7
	bne      lbl_8028AE28

lbl_8028AE24:
	li       r31, 1

lbl_8028AE28:
	clrlwi.  r0, r31, 0x18
	bne      lbl_8028AE4C
	lis      r3, lbl_80488004@ha
	lis      r5, lbl_8048801C@ha
	addi     r3, r3, lbl_80488004@l
	li       r4, 0x454
	addi     r5, r5, lbl_8048801C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8028AE4C:
	mr       r3, r30
	li       r4, 8
	lwz      r12, 0x28(r30)
	lwz      r12, 0xd4(r12)
	mtctr    r12
	bctrl

lbl_8028AE64:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028AE7C
 * Size:	0000D8
 */
void Obj::finishBossAttackLoopBGM()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	lbz      r0, 0x2c5(r3)
	cmplwi   r0, 0
	beq      lbl_8028AF3C
	li       r31, 0
	stb      r31, 0x2c5(r3)
	lwz      r30, 0x28c(r3)
	lwz      r12, 0x28(r30)
	mr       r3, r30
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 5
	beq      lbl_8028AEFC
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 6
	beq      lbl_8028AEFC
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 7
	bne      lbl_8028AF00

lbl_8028AEFC:
	li       r31, 1

lbl_8028AF00:
	clrlwi.  r0, r31, 0x18
	bne      lbl_8028AF24
	lis      r3, lbl_80488004@ha
	lis      r5, lbl_8048801C@ha
	addi     r3, r3, lbl_80488004@l
	li       r4, 0x454
	addi     r5, r5, lbl_8048801C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8028AF24:
	mr       r3, r30
	li       r4, 1
	lwz      r12, 0x28(r30)
	lwz      r12, 0xd4(r12)
	mtctr    r12
	bctrl

lbl_8028AF3C:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028AF54
 * Size:	0000D4
 */
void Obj::startStoneStateBossAttackLoopBGM()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	lbz      r0, 0x2c5(r3)
	cmplwi   r0, 0
	beq      lbl_8028B010
	lwz      r30, 0x28c(r3)
	li       r31, 0
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 5
	beq      lbl_8028AFD0
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 6
	beq      lbl_8028AFD0
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 7
	bne      lbl_8028AFD4

lbl_8028AFD0:
	li       r31, 1

lbl_8028AFD4:
	clrlwi.  r0, r31, 0x18
	bne      lbl_8028AFF8
	lis      r3, lbl_80488004@ha
	lis      r5, lbl_8048801C@ha
	addi     r3, r3, lbl_80488004@l
	li       r4, 0x454
	addi     r5, r5, lbl_8048801C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8028AFF8:
	mr       r3, r30
	li       r4, 1
	lwz      r12, 0x28(r30)
	lwz      r12, 0xd4(r12)
	mtctr    r12
	bctrl

lbl_8028B010:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028B028
 * Size:	0000D4
 */
void Obj::finishStoneStateBossAttackLoopBGM()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	lbz      r0, 0x2c5(r3)
	cmplwi   r0, 0
	beq      lbl_8028B0E4
	lwz      r30, 0x28c(r3)
	li       r31, 0
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 5
	beq      lbl_8028B0A4
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 6
	beq      lbl_8028B0A4
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 7
	bne      lbl_8028B0A8

lbl_8028B0A4:
	li       r31, 1

lbl_8028B0A8:
	clrlwi.  r0, r31, 0x18
	bne      lbl_8028B0CC
	lis      r3, lbl_80488004@ha
	lis      r5, lbl_8048801C@ha
	addi     r3, r3, lbl_80488004@l
	li       r4, 0x454
	addi     r5, r5, lbl_8048801C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8028B0CC:
	mr       r3, r30
	li       r4, 8
	lwz      r12, 0x28(r30)
	lwz      r12, 0xd4(r12)
	mtctr    r12
	bctrl

lbl_8028B0E4:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028B0FC
 * Size:	0000FC
 */
void Obj::updateBossBGM()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	li       r31, 0
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	mr       r29, r3
	lwz      r30, 0x28c(r3)
	lwz      r12, 0x28(r30)
	mr       r3, r30
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 5
	beq      lbl_8028B174
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 6
	beq      lbl_8028B174
	mr       r3, r30
	lwz      r12, 0x28(r30)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 7
	bne      lbl_8028B178

lbl_8028B174:
	li       r31, 1

lbl_8028B178:
	clrlwi.  r0, r31, 0x18
	bne      lbl_8028B19C
	lis      r3, lbl_80488004@ha
	lis      r5, lbl_8048801C@ha
	addi     r3, r3, lbl_80488004@l
	li       r4, 0x454
	addi     r5, r5, lbl_8048801C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8028B19C:
	lwz      r0, 0x1f4(r29)
	cmpwi    r0, 0
	beq      lbl_8028B1C4
	mr       r3, r30
	li       r4, 1
	lwz      r12, 0x28(r30)
	lwz      r12, 0xd8(r12)
	mtctr    r12
	bctrl
	b        lbl_8028B1DC

lbl_8028B1C4:
	mr       r3, r30
	li       r4, 0
	lwz      r12, 0x28(r30)
	lwz      r12, 0xd8(r12)
	mtctr    r12
	bctrl

lbl_8028B1DC:
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028B1F8
 * Size:	0000A8
 */
void Obj::resetMidBossAppearBGM()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	mr       r30, r3
	lwz      r4, gameSystem__4Game@sda21(r13)
	cmplwi   r4, 0
	beq      lbl_8028B288
	lbz      r0, 0x48(r4)
	cmplwi   r0, 0
	beq      lbl_8028B288
	lwz      r31, 0x28c(r30)
	mr       r3, r31
	lwz      r12, 0x28(r31)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 6
	beq      lbl_8028B264
	lis      r3, lbl_80488004@ha
	lis      r5, lbl_8048801C@ha
	addi     r3, r3, lbl_80488004@l
	li       r4, 0x45a
	addi     r5, r5, lbl_8048801C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8028B264:
	mr       r3, r31
	li       r4, 0
	bl       setAppearFlag__Q23PSM9EnemyBossFb
	lbz      r0, 0x2c0(r30)
	cmplwi   r0, 0
	beq      lbl_8028B288
	li       r0, 1
	stb      r0, 0x2c4(r30)
	stb      r0, 0x118(r31)

lbl_8028B288:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028B2A0
 * Size:	000080
 */
void Obj::setMidBossAppearBGM()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	lbz      r0, 0x2c4(r3)
	cmplwi   r0, 0
	bne      lbl_8028B30C
	li       r0, 1
	stb      r0, 0x2c4(r3)
	lwz      r31, 0x28c(r3)
	mr       r3, r31
	lwz      r12, 0x28(r31)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	cmpwi    r3, 6
	beq      lbl_8028B300
	lis      r3, lbl_80488004@ha
	lis      r5, lbl_8048801C@ha
	addi     r3, r3, lbl_80488004@l
	li       r4, 0x45a
	addi     r5, r5, lbl_8048801C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8028B300:
	mr       r3, r31
	li       r4, 1
	bl       setAppearFlag__Q23PSM9EnemyBossFb

lbl_8028B30C:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8028B320
 * Size:	000534
 */
void Obj::createEffect()
{
	mEfxLay       = new efx::TQueenLay;
	mEfxRollCR    = new efx::TQueenRollCR(&mPosition, &mFaceDir);
	mEfxRollCL    = new efx::TQueenRollCL(&mPosition, &mFaceDir);
	mEfxRoll      = new efx::TQueenRoll(&mPosition, &mFaceDir);
	mEfxCrashR    = new efx::TQueenCrashR(&mPosition, &mFaceDir);
	mEfxCrashL    = new efx::TQueenCrashL(&mPosition, &mFaceDir);
	mEfxCrashRock = new efx::TQueenCrashRock(&mPosition, &mFaceDir);
	mEfxDamage    = new efx::TQueenDamage(&mPosition, &mFaceDir);
	mEfxFlick     = new efx::TQueenFlick(&mPosition, &mFaceDir);
	mEfxDead      = new efx::TQueenDead;
	mEfxWakeup    = new efx::TQueenWakeup(&mPosition, &mFaceDir);
	mEfxHanacho   = new efx::TQueenHanacho;
}

/*
 * --INFO--
 * Address:	8028B854
 * Size:	000078
 */
void Obj::setupEffect()
{
	mEfxLay->mMtx = mModel->getJoint("body_end")->getWorldMatrix();
	mEfxDead->setMtxptr(mModel->getJoint("body5")->getWorldMatrix()->mMatrix.mtxView);
	mEfxHanacho->mMtx = mModel->getJoint("head")->getWorldMatrix();
}

/*
 * --INFO--
 * Address:	8028B8CC
 * Size:	000034
 */
void Obj::createBornEffect() { mEfxLay->create(nullptr); }

/*
 * --INFO--
 * Address:	8028B900
 * Size:	000080
 */
void Obj::startRollingEffect()
{
	if (getCurrAnimIndex() == 6) {
		mEfxRollCR->create(nullptr);
	} else {
		mEfxRollCL->create(nullptr);
	}

	mEfxRoll->create(nullptr);
}

/*
 * --INFO--
 * Address:	8028B980
 * Size:	0000E0
 */
void Obj::finishRollingEffect(bool doCrash)
{
	if (getCurrAnimIndex() == 6) {
		if (doCrash) {
			mEfxCrashR->create(nullptr);
		}

		mEfxRollCR->fade();
	} else {
		if (doCrash) {
			mEfxCrashL->create(nullptr);
		}

		mEfxRollCL->fade();
	}

	if (doCrash) {
		mEfxCrashRock->create(nullptr);
	}

	mEfxRoll->fade();
}

/*
 * --INFO--
 * Address:	8028BA60
 * Size:	000064
 */
void Obj::forceFinishRollingEffect()
{
	mEfxRollCR->fade();
	mEfxRollCL->fade();
	mEfxRoll->fade();
}

/*
 * --INFO--
 * Address:	8028BAC4
 * Size:	000034
 */
void Obj::startDamageEffect() { mEfxDamage->create(nullptr); }

/*
 * --INFO--
 * Address:	8028BAF8
 * Size:	000030
 */
void Obj::finishDamageEffect() { mEfxDamage->fade(); }

/*
 * --INFO--
 * Address:	8028BB28
 * Size:	000034
 */
void Obj::createFlickEffect() { mEfxFlick->create(nullptr); }

/*
 * --INFO--
 * Address:	8028BB5C
 * Size:	000034
 */
void Obj::createDeadEffect() { mEfxDead->create(nullptr); }

/*
 * --INFO--
 * Address:	8028BB90
 * Size:	000034
 */
void Obj::createWakeUpEffect() { mEfxWakeup->create(nullptr); }

/*
 * --INFO--
 * Address:	8028BBC4
 * Size:	000034
 */
void Obj::startSleepEffect() { mEfxHanacho->create(nullptr); }

/*
 * --INFO--
 * Address:	8028BBF8
 * Size:	000030
 */
void Obj::finishSleepEffect() { mEfxHanacho->fade(); }

/*
 * --INFO--
 * Address:	8028BC28
 * Size:	000118
 */
void Obj::effectDrawOn()
{
	mEfxLay->endDemoDrawOn();
	mEfxRollCR->endDemoDrawOn();
	mEfxRollCL->endDemoDrawOn();
	mEfxRoll->endDemoDrawOn();
	mEfxCrashR->endDemoDrawOn();
	mEfxCrashL->endDemoDrawOn();
	mEfxCrashRock->endDemoDrawOn();
	mEfxDamage->endDemoDrawOn();
	mEfxFlick->endDemoDrawOn();
	mEfxDead->endDemoDrawOn();
	mEfxWakeup->endDemoDrawOn();
	mEfxHanacho->endDemoDrawOn();
}

/*
 * --INFO--
 * Address:	8028BD40
 * Size:	000118
 */
void Obj::effectDrawOff()
{
	mEfxLay->startDemoDrawOff();
	mEfxRollCR->startDemoDrawOff();
	mEfxRollCL->startDemoDrawOff();
	mEfxRoll->startDemoDrawOff();
	mEfxCrashR->startDemoDrawOff();
	mEfxCrashL->startDemoDrawOff();
	mEfxCrashRock->startDemoDrawOff();
	mEfxDamage->startDemoDrawOff();
	mEfxFlick->startDemoDrawOff();
	mEfxDead->startDemoDrawOff();
	mEfxWakeup->startDemoDrawOff();
	mEfxHanacho->startDemoDrawOff();
}

/*
 * --INFO--
 * Address:	8028C494
 * Size:	000004
 */
void Obj::inWaterCallback(WaterBox*) { }

/*
 * --INFO--
 * Address:	8028C498
 * Size:	000004
 */
void Obj::outWaterCallback() { }

/*
 * --INFO--
 * Address:	8028C49C
 * Size:	000008
 */
f32 Obj::getDamageCoeStoneState() { return 0.25f; }

/*
 * --INFO--
 * Address:	8028C4A4
 * Size:	000008
 */
EnemyTypeID::EEnemyTypeID Obj::getEnemyTypeID() { return EnemyTypeID::EnemyID_Queen; }

} // namespace Queen
} // namespace Game
