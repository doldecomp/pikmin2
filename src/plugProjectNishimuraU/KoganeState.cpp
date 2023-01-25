#include "Game/Entities/Kogane.h"
#include "Game/EnemyAnimKeyEvent.h"
#include "Game/EnemyFunc.h"
#include "efx/TKogane.h"

namespace Game {
namespace Kogane {

/*
 * --INFO--
 * Address:	8025CD48
 * Size:	0001D4
 */
void FSM::init(EnemyBase* enemy)
{
	create(KOGANE_Count);
	registerState(new StateAppear);
	registerState(new StateDisappear);
	registerState(new StateMove);
	registerState(new StateWait);
	registerState(new StatePress);
}

/*
 * --INFO--
 * Address:	8025CF1C
 * Size:	000098
 */
void StateAppear::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* kogane = static_cast<Obj*>(enemy);
	kogane->setAtari(false);
	kogane->enableEvent(0, EB_IsImmuneBitter);
	kogane->hardConstraintOn();
	kogane->disableEvent(0, EB_IsAnimating);
	kogane->enableEvent(0, EB_IsModelHidden);

	kogane->mTargetVelocity = Vector3f(0.0f);
	kogane->startMotion(0, nullptr);
	kogane->stopMotion();
}

/*
 * --INFO--
 * Address:	8025CFB4
 * Size:	000064
 */
void StateAppear::exec(EnemyBase* enemy)
{
	Obj* kogane = static_cast<Obj*>(enemy);
	if (kogane->isAppear()) {
		transit(kogane, KOGANE_Move, nullptr);
	}
}

/*
 * --INFO--
 * Address:	8025D018
 * Size:	0001A0
 */
void StateAppear::cleanup(EnemyBase* enemy)
{
	Obj* kogane = static_cast<Obj*>(enemy);
	kogane->setAtari(true);

	kogane->disableEvent(0, EB_IsImmuneBitter);
	kogane->enableEvent(0, EB_IsEnemyNotBitter);
	kogane->disableEvent(0, EB_IsCullable);
	kogane->hardConstraintOff();
	kogane->enableEvent(0, EB_IsAnimating);
	kogane->disableEvent(0, EB_IsModelHidden);

	kogane->setEmotionExcitement();
	kogane->startMotion();

	efx::TKoganeDive diveEffect;
	efx::ArgScale scaleArg(kogane->getPosition(), static_cast<Parms*>(kogane->mParms)->mProperParms.mFp40.mValue);
	diveEffect.create(&scaleArg);

	kogane->startBodyEffect();
	kogane->getJAIObject()->startSound(PSSE_EN_TAMAGOMUSHI_APPEAR, 0);
}

/*
 * --INFO--
 * Address:	8025D1BC
 * Size:	000138
 */
void StateDisappear::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* kogane = static_cast<Obj*>(enemy);

	kogane->enableEvent(0, EB_IsImmuneBitter);

	efx::TKoganeDive diveEffect;
	efx::ArgScale scaleArg(kogane->getPosition(), static_cast<Parms*>(kogane->mParms)->mProperParms.mFp40.mValue);
	diveEffect.create(&scaleArg);

	kogane->finishBodyEffect();
	kogane->getJAIObject()->startSound(PSSE_EN_TAMAGOMUSHI_DIVE, 0);
}

/*
 * --INFO--
 * Address:	8025D2F8
 * Size:	00006C
 */
void StateDisappear::exec(EnemyBase* enemy)
{
	Obj* kogane = static_cast<Obj*>(enemy);

	if (kogane->koganeScaleDown()) {
		if (kogane->transitDisappear()) {
			kogane->mInPiklopedia = false;
			kogane->kill(nullptr);
		} else {
			kogane->init(nullptr);
		}
	}
}

/*
 * --INFO--
 * Address:	8025D364
 * Size:	000004
 */
void StateDisappear::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	8025D368
 * Size:	00006C
 */
void StateMove::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* kogane = static_cast<Obj*>(enemy);

	Parms* parms = static_cast<Parms*>(kogane->mParms);
	kogane->resetMoveTimer(parms->mProperParms.mFp10.mValue, parms->mProperParms.mFp11.mValue);
	kogane->setTargetPosition(nullptr);
	kogane->startMotion(0, nullptr);
	kogane->createFartEffect();
}

/*
 * --INFO--
 * Address:	8025D3D8
 * Size:	000138
 */
void StateMove::exec(EnemyBase* enemy)
{
	Obj* kogane = static_cast<Obj*>(enemy);

	kogane->koganeScaleUp();
	Vector3f targetPos = Vector3f(kogane->mTargetPosition);
	Parms* parms       = static_cast<Parms*>(kogane->mParms);
	EnemyFunc::walkToTarget(kogane, targetPos, parms->mGeneral.mMoveSpeed.mValue, parms->mGeneral.mRotationalAccel.mValue,
	                        parms->mGeneral.mRotationalSpeed.mValue);

	if ((kogane->mAppearTimer > static_cast<Parms*>(kogane->mParms)->mProperParms.mFp02.mValue)
	    || (kogane->mMoveTimer > static_cast<Parms*>(kogane->mParms)->mProperParms.mFp11.mValue)) {
		kogane->finishMotion();
	}

	kogane->mAppearTimer += sys->mDeltaTime;
	kogane->mMoveTimer += sys->mDeltaTime;

	if (kogane->mCurAnim->mIsPlaying && (u32)kogane->mCurAnim->mType == KEYEVENT_END) {
		if (kogane->mAppearTimer > static_cast<Parms*>(kogane->mParms)->mProperParms.mFp02.mValue) {
			transit(kogane, KOGANE_Disappear, nullptr);
		} else {
			transit(kogane, KOGANE_Wait, nullptr);
		}
	}
}

/*
 * --INFO--
 * Address:	8025D510
 * Size:	000004
 */
void StateMove::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	8025D514
 * Size:	00005C
 */
void StateWait::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* kogane = static_cast<Obj*>(enemy);

	Parms* parms = static_cast<Parms*>(kogane->mParms);
	kogane->resetMoveTimer(parms->mProperParms.mFp20.mValue, parms->mProperParms.mFp21.mValue);

	kogane->mTargetVelocity = Vector3f(0.0f);
	kogane->startMotion(1, nullptr);
}

/*
 * --INFO--
 * Address:	8025D570
 * Size:	0000BC
 */
void StateWait::exec(EnemyBase* enemy)
{
	Obj* kogane = static_cast<Obj*>(enemy);

	kogane->koganeScaleUp();
	if (kogane->mMoveTimer > static_cast<Parms*>(kogane->mParms)->mProperParms.mFp21.mValue) {
		kogane->finishMotion();
	}

	kogane->mAppearTimer += sys->mDeltaTime;
	kogane->mMoveTimer += sys->mDeltaTime;

	if (kogane->mCurAnim->mIsPlaying && (u32)kogane->mCurAnim->mType == KEYEVENT_END) {
		transit(kogane, KOGANE_Move, nullptr);
	}
}

/*
 * --INFO--
 * Address:	8025D62C
 * Size:	000004
 */
void StateWait::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	8025D630
 * Size:	00011C
 */
void StatePress::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* kogane = static_cast<Obj*>(enemy);

	kogane->disableEvent(0, EB_IsEnemyNotBitter);

	efx::TKoganeHit hitEffect;
	efx::ArgScale scaleArg(kogane->getPosition(), static_cast<Parms*>(kogane->mParms)->mProperParms.mFp40.mValue);
	hitEffect.create(&scaleArg);

	kogane->startMotion(2, nullptr);
	kogane->createPressSENormal();
}

/*
 * --INFO--
 * Address:	8025D750
 * Size:	000130
 */
void StatePress::exec(EnemyBase* enemy)
{
	Obj* kogane = static_cast<Obj*>(enemy);

	kogane->koganeScaleUp();
	kogane->mAppearTimer += sys->mDeltaTime;

	if (kogane->mCurAnim->mIsPlaying) {
		if ((u32)kogane->mCurAnim->mType == KEYEVENT_2) {
			kogane->enableEvent(0, EB_IsEnemyNotBitter);
			kogane->createPressSESpecial();
		} else if ((u32)kogane->mCurAnim->mType == KEYEVENT_3) {
			kogane->createItem();
			kogane->setZukanVisible(false);
		} else if ((u32)kogane->mCurAnim->mType == KEYEVENT_4) {
			kogane->disableEvent(0, EB_IsEnemyNotBitter);
		} else if ((u32)kogane->mCurAnim->mType == KEYEVENT_END) {
			if (kogane->mAppearTimer > 12800.0f) {
				transit(kogane, KOGANE_Disappear, nullptr);
			} else {
				transit(kogane, KOGANE_Move, nullptr);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	8025D888
 * Size:	000010
 */
void StatePress::cleanup(EnemyBase* enemy) { enemy->disableEvent(0, EB_IsEnemyNotBitter); }

} // namespace Kogane
} // namespace Game
