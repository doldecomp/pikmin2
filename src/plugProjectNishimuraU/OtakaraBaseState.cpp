#include "Game/Entities/OtakaraBase.h"
#include "Game/EnemyAnimKeyEvent.h"
#include "Game/EnemyFunc.h"

namespace Game {
namespace OtakaraBase {

const char basestatename[] = "246-OtakaraBaseState";

/*
 * --INFO--
 * Address:	802B37A8
 * Size:	0004D4
 */
void FSM::init(EnemyBase* enemy)
{
	create(14);

	registerState(new StateDead);
	registerState(new StateFlick);
	registerState(new StateWait);
	registerState(new StateMove);
	registerState(new StateTurn);
	registerState(new StateTake);

	registerState(new StateItemWait);
	registerState(new StateItemMove);
	registerState(new StateItemTurn);
	registerState(new StateItemFlick);
	registerState(new StateItemDrop);

	registerState(new StateBombWait);
	registerState(new StateBombMove);
	registerState(new StateBombTurn);
}

/*
 * --INFO--
 * Address:	802B3C7C
 * Size:	00005C
 */
void StateDead::init(EnemyBase* enemy, StateArg* stateArg)
{
	enemy->m_velocity2 = Vector3f(0.0f);
	enemy->deathProcedure();
	enemy->resetEvent(0, EB_Cullable);
	enemy->startMotion(10, nullptr);
}

/*
 * --INFO--
 * Address:	802B3CD8
 * Size:	000044
 */
void StateDead::exec(EnemyBase* enemy)
{
	if (enemy->m_animKeyEvent->m_running && (u32) enemy->m_animKeyEvent->m_type == 1000) {
		enemy->kill(nullptr);
	}
}

/*
 * --INFO--
 * Address:	802B3D1C
 * Size:	000004
 */
void StateDead::cleanup(EnemyBase*) { }

/*
 * --INFO--
 * Address:	802B3D20
 * Size:	00007C
 */
void StateFlick::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->_2C4 = 0.0f;
	ota->m_escapeSfxTimer = 0.0f;
	ota->m_velocity2 = Vector3f(0.0f);

	ota->setEmotionExcitement();
	ota->startMotion(3, nullptr);
	ota->_2D0 = 1;
	ota->startChargeEffect();
}

/*
 * --INFO--
 * Address:	802B3DA0
 * Size:	000290
 */
void StateFlick::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);
	if (ota->_2C4 > static_cast<Parms*>(ota->m_parms)->m_properParms.m_fp10.m_value) {
		ota->finishMotion();
	}
	ota->_2C4 += sys->m_secondsPerFrame;

	if (ota->_2D0) {
		ota->getJAIObject()->startSound(PSSE_EN_OTAKARA_CHARGE, 0);
	}

	EnemyAnimKeyEvent* event = ota->m_animKeyEvent;
	if (event->m_running) {
		if ((u32) event->m_type == 2) {
			Parms* parms = static_cast<Parms*>(ota->m_parms);
			EnemyFunc::flickStickPikmin(ota, parms->m_general.m_shakeRateMaybe.m_value,
											parms->m_general.m_shakeKnockback.m_value,
											parms->m_general.m_shakeDamage.m_value, -1000.0f, nullptr);
			ota->m_toFlick = 0.0f;

		} else if ((u32) event->m_type == 3) {
			ota->_2C8 = 0.0f;
			ota->_2D0 = 0;
			ota->finishChargeEffect();
			ota->createDisChargeEffect();

		} else if ((u32) event->m_type == 1000) {
			if (ota->m_health <= 0.0f) {
				transit(ota, OTA_Dead, nullptr);
				return;
			}

			if (ota->isMovePositionSet(false)) {
				Vector3f movePos = ota->m_movePosition;
				Vector3f pos = ota->getPosition();
				f32 angle = angXZ(movePos.x, movePos.z, pos);
				if (FABS(angDist(angle, ota->getFaceDir())) <= THIRD_PI) {
					transit(ota, OTA_Move, nullptr);
					return;
				}
				transit(ota, OTA_Turn, nullptr);
				return;
			}

			transit(ota, OTA_Wait, nullptr);
		}
	}
}

/*
 * --INFO--
 * Address:	802B4038
 * Size:	000024
 */
void StateFlick::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802B405C
 * Size:	000050
 */
void StateWait::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->m_escapeSfxTimer = 0.0f;
	ota->m_velocity2 = Vector3f(0.0f);
	ota->m_targetCreature = nullptr;
	ota->startMotion(0, nullptr);
}

/*
 * --INFO--
 * Address:	802B40AC
 * Size:	0001CC
 */
void StateWait::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);
	if (ota->isMovePositionSet(false)) {
		Vector3f movePos = ota->m_movePosition;
		Vector3f pos = ota->getPosition();
		f32 angle = angXZ(movePos.x, movePos.z, pos);
		if (FABS(angDist(angle, ota->getFaceDir())) <= THIRD_PI) {
			ota->m_nextState = OTA_Move;
			ota->finishMotion();
			if (ota->isTakeTreasure()) {
				ota->m_nextState = OTA_Take;
				ota->m_velocity2 = Vector3f(0.0f);
				ota->finishMotion();
			}
		} else {
			ota->m_nextState = OTA_Turn;
			ota->finishMotion();
		}
	}

	if (EnemyFunc::isStartFlick(ota, false)) {
		ota->m_nextState = OTA_Flick;
		ota->finishMotion();
	}

	if (ota->m_health <= 0.0f) {
		ota->m_nextState = OTA_Dead;
		ota->finishMotion();
	}

	if (ota->m_animKeyEvent->m_running && (u32) ota->m_animKeyEvent->m_type == 1000) {
		transit(ota, ota->m_nextState, nullptr);
	}
}

/*
 * --INFO--
 * Address:	802B4278
 * Size:	000004
 */
void StateWait::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	802B427C
 * Size:	000048
 */
void StateMove::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->setEmotionExcitement();
	ota->startMotion(1, nullptr);
}

/*
 * --INFO--
 * Address:	802B42C4
 * Size:	000244
 */
void StateMove::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);
	if (ota->isMovePositionSet(false)) {
		Vector3f movePos = Vector3f(ota->m_movePosition);
		Vector3f pos = ota->getPosition();
		f32 angle = angXZ(movePos.x, movePos.z, pos);
		if (FABS(angDist(angle, ota->getFaceDir())) <= THIRD_PI) {
			Parms* parms = static_cast<Parms*>(ota->m_parms);
			EnemyFunc::walkToTarget(ota, movePos, parms->m_general.m_moveSpeed.m_value, parms->m_general.m_rotationalAccel.m_value,
										parms->m_general.m_rotationalSpeed.m_value);
			if (ota->isTakeTreasure()) {
				ota->m_nextState = OTA_Take;
				ota->m_velocity2 = Vector3f(0.0f);
				ota->finishMotion();
			}
		} else {
			ota->m_nextState = OTA_Turn;
			ota->m_velocity2 = Vector3f(0.0f);
			ota->finishMotion();
		}
	} else {
		ota->m_nextState = OTA_Wait;
		ota->m_velocity2 = Vector3f(0.0f);
		ota->finishMotion();
	}

	if (EnemyFunc::isStartFlick(ota, false)) {
		ota->m_nextState = OTA_Flick;
		ota->m_velocity2 = Vector3f(0.0f);
		ota->finishMotion();
	}

	if (ota->m_health <= 0.0f) {
		ota->m_nextState = OTA_Dead;
		ota->m_velocity2 = Vector3f(0.0f);
		ota->finishMotion();
	}

	ota->startEscapeSE();

	if (ota->m_animKeyEvent->m_running && (u32) ota->m_animKeyEvent->m_type == 1000) {
		transit(ota, ota->m_nextState, nullptr);
	}
}

/*
 * --INFO--
 * Address:	802B4508
 * Size:	000024
 */
void StateMove::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802B452C
 * Size:	000058
 */
void StateTurn::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->m_velocity2 = Vector3f(0.0f);
	ota->setEmotionExcitement();
	ota->startMotion(2, nullptr);
}

/*
 * --INFO--
 * Address:	802B4584
 * Size:	000264
 */
void StateTurn::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);
	if (ota->isMovePositionSet(false)) {
		Parms* parms = static_cast<Parms*>(ota->m_parms);

		f32 x = ota->m_movePosition.x;
		f32 z = ota->m_movePosition.z;
		f32 rotSpeed = parms->m_general.m_rotationalSpeed.m_value;
		f32 rotAccel = parms->m_general.m_rotationalAccel.m_value;

		Vector3f pos = ota->getPosition();
		f32 angleDist = angDist(_angXZ(x, z, pos.x, pos.z), ota->getFaceDir());

		f32 approxSpeed = angleDist * rotAccel;
		f32 limit = (DEG2RAD * rotSpeed) * PI;
		if (FABS(approxSpeed) > limit) {
			approxSpeed = (approxSpeed > 0.0f) ? limit : -limit;
		}

		ota->m_faceDir = roundAng(approxSpeed + ota->getFaceDir());
		ota->_1A4.m_matrix[0][1] = ota->m_faceDir;
		
		if (FABS(angleDist) <= THIRD_PI) {
			ota->m_nextState = OTA_Move;
			ota->finishMotion();
			if (ota->isTakeTreasure()) {
				ota->m_nextState = OTA_Take;
				ota->m_velocity2 = Vector3f(0.0f);
				ota->finishMotion();
			}
		}
	} else {
		ota->m_nextState = OTA_Wait;
		ota->finishMotion();
	}

	if (EnemyFunc::isStartFlick(ota, false)) {
		ota->m_nextState = OTA_Flick;
		ota->finishMotion();
	}

	if (ota->m_health <= 0.0f) {
		ota->m_nextState = OTA_Dead;
		ota->finishMotion();
	}

	ota->startEscapeSE();

	if (ota->m_animKeyEvent->m_running && (u32) ota->m_animKeyEvent->m_type == 1000) {
		transit(ota, ota->m_nextState, nullptr);
	}
	/*
	stwu     r1, -0x60(r1)
	mflr     r0
	stw      r0, 0x64(r1)
	stfd     f31, 0x50(r1)
	psq_st   f31, 88(r1), 0, qr0
	stfd     f30, 0x40(r1)
	psq_st   f30, 72(r1), 0, qr0
	stfd     f29, 0x30(r1)
	psq_st   f29, 56(r1), 0, qr0
	stfd     f28, 0x20(r1)
	psq_st   f28, 40(r1), 0, qr0
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r31, r4
	mr       r30, r3
	li       r4, 0
	mr       r3, r31
	bl       isMovePositionSet__Q34Game11OtakaraBase3ObjFb
	clrlwi.  r0, r3, 0x18
	beq      lbl_802B4708
	mr       r4, r31
	lwz      r5, 0xc0(r31)
	lwz      r12, 0(r31)
	addi     r3, r1, 8
	lfs      f31, 0x2d4(r31)
	lwz      r12, 8(r12)
	lfs      f28, 0x2dc(r31)
	lfs      f29, 0x334(r5)
	lfs      f30, 0x30c(r5)
	mtctr    r12
	bctrl
	lfs      f1, 8(r1)
	lis      r3, atanTable___5JMath@ha
	lfs      f0, 0x10(r1)
	addi     r3, r3, atanTable___5JMath@l
	fsubs    f1, f31, f1
	fsubs    f2, f28, f0
	bl       "atan2___Q25JMath18TAtanTable<1024,f>CFff"
	bl       roundAng__Ff
	lwz      r12, 0(r31)
	fmr      f31, f1
	mr       r3, r31
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	fmr      f2, f1
	fmr      f1, f31
	bl       angDist__Fff
	fmr      f31, f1
	lfs      f0, lbl_8051C288@sda21(r2)
	lfs      f1, lbl_8051C284@sda21(r2)
	fmuls    f0, f0, f29
	fmuls    f29, f31, f30
	fmuls    f1, f1, f0
	fabs     f0, f29
	frsp     f0, f0
	fcmpo    cr0, f0, f1
	ble      lbl_802B4684
	lfs      f0, lbl_8051C278@sda21(r2)
	fcmpo    cr0, f29, f0
	ble      lbl_802B4680
	fmr      f29, f1
	b        lbl_802B4684

lbl_802B4680:
	fneg     f29, f1

lbl_802B4684:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	fadds    f1, f29, f1
	bl       roundAng__Ff
	fabs     f3, f31
	stfs     f1, 0x1fc(r31)
	lfs      f0, lbl_8051C280@sda21(r2)
	lfs      f2, 0x1fc(r31)
	frsp     f1, f3
	stfs     f2, 0x1a8(r31)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_802B4718
	li       r0, 3
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv
	mr       r3, r31
	bl       isTakeTreasure__Q34Game11OtakaraBase3ObjFv
	clrlwi.  r0, r3, 0x18
	beq      lbl_802B4718
	li       r0, 5
	lfs      f0, lbl_8051C278@sda21(r2)
	stw      r0, 0x2c0(r31)
	mr       r3, r31
	stfs     f0, 0x1d4(r31)
	stfs     f0, 0x1d8(r31)
	stfs     f0, 0x1dc(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv
	b        lbl_802B4718

lbl_802B4708:
	li       r0, 2
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv

lbl_802B4718:
	mr       r3, r31
	li       r4, 0
	bl       isStartFlick__Q24Game9EnemyFuncFPQ24Game9EnemyBaseb
	clrlwi.  r0, r3, 0x18
	beq      lbl_802B473C
	li       r0, 1
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv

lbl_802B473C:
	lfs      f1, 0x200(r31)
	lfs      f0, lbl_8051C278@sda21(r2)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_802B4760
	li       r0, 0
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv

lbl_802B4760:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x31c(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0x188(r31)
	lbz      r0, 0x24(r3)
	cmplwi   r0, 0
	beq      lbl_802B47B0
	lwz      r0, 0x1c(r3)
	cmplwi   r0, 0x3e8
	bne      lbl_802B47B0
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r6, 0
	lwz      r5, 0x2c0(r31)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_802B47B0:
	psq_l    f31, 88(r1), 0, qr0
	lfd      f31, 0x50(r1)
	psq_l    f30, 72(r1), 0, qr0
	lfd      f30, 0x40(r1)
	psq_l    f29, 56(r1), 0, qr0
	lfd      f29, 0x30(r1)
	psq_l    f28, 40(r1), 0, qr0
	lfd      f28, 0x20(r1)
	lwz      r31, 0x1c(r1)
	lwz      r0, 0x64(r1)
	lwz      r30, 0x18(r1)
	mtlr     r0
	addi     r1, r1, 0x60
	blr
	*/
}

/*
 * --INFO--
 * Address:	802B47E8
 * Size:	000024
 */
void StateTurn::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802B480C
 * Size:	000050
 */
void StateTake::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->m_escapeSfxTimer = 0.0f;
	ota->setEmotionExcitement();
	ota->startMotion(4, nullptr);
}

/*
 * --INFO--
 * Address:	802B485C
 * Size:	000154
 */
void StateTake::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);
	Vector3f movePos = Vector3f(ota->m_movePosition);
	Parms* parms = static_cast<Parms*>(ota->m_parms);
	EnemyFunc::walkToTarget(ota, movePos, parms->m_general.m_moveSpeed.m_value, parms->m_general.m_rotationalAccel.m_value,
								parms->m_general.m_rotationalSpeed.m_value);
	EnemyAnimKeyEvent* event = ota->m_animKeyEvent;
	if (event->m_running) {
		if ((u32) event->m_type == 2) {
			ota->takeTreasure();
		} else if ((u32) event->m_type == 1000) {
			if (ota->m_treasure != nullptr) {
				if (ota->isDropTreasure()) {
					transit(ota, OTA_ItemDrop, nullptr);					
				} else if (EnemyFunc::isStartFlick(ota, false)) {
					transit(ota, OTA_ItemFlick, nullptr);
				} else {
					transit(ota, OTA_ItemMove, nullptr);
				}
			} else {
				transit(ota, OTA_ItemDrop, nullptr);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	802B49B0
 * Size:	000024
 */
void StateTake::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802B49D4
 * Size:	000048
 */
void StateItemWait::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->m_escapeSfxTimer = 0.0f;
	ota->m_velocity2 = Vector3f(0.0f);
	ota->startMotion(5, nullptr);
}

/*
 * --INFO--
 * Address:	802B4A1C
 * Size:	0001D8
 */
void StateItemWait::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);
	if (ota->isMovePositionSet(true)) {
		Vector3f movePos = ota->m_movePosition;
		Vector3f pos = ota->getPosition();
		f32 angle = angXZ(movePos.x, movePos.z, pos);
		if (FABS(angDist(angle, ota->getFaceDir())) <= THIRD_PI) {
			ota->m_nextState = OTA_ItemMove;
			ota->finishMotion();
		} else {
			ota->m_nextState = OTA_ItemTurn;
			ota->finishMotion();
		}
	}

	if (EnemyFunc::isStartFlick(ota, false)) {
		ota->m_nextState = OTA_ItemFlick;
		ota->finishMotion();
	}
	if (ota->isDropTreasure()) {
		ota->m_nextState = OTA_ItemDrop;
		ota->finishMotion();

	} else if (gameSystem != nullptr && gameSystem->m_mode == GSM_VERSUS_MODE) {
		if (ota->m_health <= 0.0f) {
			ota->m_nextState = OTA_ItemDrop;
			ota->finishMotion();
		}
	}

	if (ota->m_animKeyEvent->m_running && (u32) ota->m_animKeyEvent->m_type == 1000) {
		transit(ota, ota->m_nextState, nullptr);
	}
}

/*
 * --INFO--
 * Address:	802B4BF4
 * Size:	000004
 */
void StateItemWait::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	802B4BF8
 * Size:	000048
 */
void StateItemMove::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->setEmotionExcitement();
	ota->startMotion(6, nullptr);
}

/*
 * --INFO--
 * Address:	802B4C40
 * Size:	000260
 */
void StateItemMove::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);

	if (ota->isMovePositionSet(true)) {
		Vector3f movePos = Vector3f(ota->m_movePosition);
		Vector3f pos = ota->getPosition();
		f32 angle = angXZ(movePos.x, movePos.z, pos);
		if (FABS(angDist(angle, ota->getFaceDir())) <= THIRD_PI) {
			Parms* parms = static_cast<Parms*>(ota->m_parms);
			EnemyFunc::walkToTarget(ota, movePos, parms->m_general.m_moveSpeed.m_value, parms->m_general.m_rotationalAccel.m_value,
										parms->m_general.m_rotationalSpeed.m_value);
		} else {
			ota->m_nextState = OTA_ItemTurn;
			ota->m_velocity2 = Vector3f(0.0f);
			ota->finishMotion();
		}

	} else {
		ota->m_nextState = OTA_ItemWait;
		ota->m_velocity2 = Vector3f(0.0f);
		ota->finishMotion();
	}

	if (EnemyFunc::isStartFlick(ota, false)) {
		ota->m_nextState = OTA_ItemFlick;
		ota->m_velocity2 = Vector3f(0.0f);
		ota->finishMotion();
	}

	if (ota->isDropTreasure()) {
		ota->m_nextState = OTA_ItemDrop;
		ota->m_velocity2 = Vector3f(0.0f);
		ota->finishMotion();

	} else if (gameSystem != nullptr && gameSystem->m_mode == GSM_VERSUS_MODE) {
		if (ota->m_health <= 0.0f) {
			ota->m_nextState = OTA_ItemDrop;
			ota->m_velocity2 = Vector3f(0.0f);
			ota->finishMotion();
		}
	}

	ota->startEscapeSE();

	if (ota->m_animKeyEvent->m_running && (u32) ota->m_animKeyEvent->m_type == 1000) {
		transit(enemy, ota->m_nextState, nullptr); // dumb that this fixes regswaps, really should be ota
	}
}

/*
 * --INFO--
 * Address:	802B4EA0
 * Size:	000024
 */
void StateItemMove::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802B4EC4
 * Size:	000058
 */
void StateItemTurn::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->m_velocity2 = Vector3f(0.0f);
	ota->setEmotionExcitement();
	ota->startMotion(7, nullptr);
}

/*
 * --INFO--
 * Address:	802B4F1C
 * Size:	000270
 */
// same regswaps as StateTurn::exec above
void StateItemTurn::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);

	if (ota->isMovePositionSet(true)) {
		Parms* parms = static_cast<Parms*>(ota->m_parms);

		f32 x = ota->m_movePosition.x;
		f32 z = ota->m_movePosition.z;
		f32 rotSpeed = parms->m_general.m_rotationalSpeed.m_value;
		f32 rotAccel = parms->m_general.m_rotationalAccel.m_value;

		Vector3f pos = ota->getPosition();
		f32 angleDist = angDist(_angXZ(x, z, pos.x, pos.z), ota->getFaceDir());

		f32 approxSpeed = angleDist * rotAccel;
		f32 limit = (DEG2RAD * rotSpeed) * PI;
		if (FABS(approxSpeed) > limit) {
			approxSpeed = (approxSpeed > 0.0f) ? limit : -limit;
		}

		ota->m_faceDir = roundAng(approxSpeed + ota->getFaceDir());
		ota->_1A4.m_matrix[0][1] = ota->m_faceDir;
		
		if (FABS(angleDist) <= THIRD_PI) {
			ota->m_nextState = OTA_ItemMove;
			ota->finishMotion();
		}
	} else {
		ota->m_nextState = OTA_ItemWait;
		ota->finishMotion();
	}

	if (EnemyFunc::isStartFlick(ota, false)) {
		ota->m_nextState = OTA_ItemFlick;
		ota->finishMotion();
	}

	if (ota->isDropTreasure()) {
		ota->m_nextState = OTA_ItemDrop;
		ota->finishMotion();

	} else if (gameSystem != nullptr && gameSystem->m_mode == GSM_VERSUS_MODE) {
		if (ota->m_health <= 0.0f) {
			ota->m_nextState = OTA_ItemDrop;
			ota->finishMotion();
		}
	}

	ota->startEscapeSE();

	if (ota->m_animKeyEvent->m_running && (u32) ota->m_animKeyEvent->m_type == 1000) {
		transit(enemy, ota->m_nextState, nullptr); // dumb that this fixes regswaps, really should be ota
	}
	/*
	stwu     r1, -0x60(r1)
	mflr     r0
	stw      r0, 0x64(r1)
	stfd     f31, 0x50(r1)
	psq_st   f31, 88(r1), 0, qr0
	stfd     f30, 0x40(r1)
	psq_st   f30, 72(r1), 0, qr0
	stfd     f29, 0x30(r1)
	psq_st   f29, 56(r1), 0, qr0
	stfd     f28, 0x20(r1)
	psq_st   f28, 40(r1), 0, qr0
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r31, r4
	mr       r30, r3
	li       r4, 1
	mr       r3, r31
	bl       isMovePositionSet__Q34Game11OtakaraBase3ObjFb
	clrlwi.  r0, r3, 0x18
	beq      lbl_802B5070
	mr       r4, r31
	lwz      r5, 0xc0(r31)
	lwz      r12, 0(r31)
	addi     r3, r1, 8
	lfs      f31, 0x2d4(r31)
	lwz      r12, 8(r12)
	lfs      f28, 0x2dc(r31)
	lfs      f29, 0x334(r5)
	lfs      f30, 0x30c(r5)
	mtctr    r12
	bctrl
	lfs      f1, 8(r1)
	lis      r3, atanTable___5JMath@ha
	lfs      f0, 0x10(r1)
	addi     r3, r3, atanTable___5JMath@l
	fsubs    f1, f31, f1
	fsubs    f2, f28, f0
	bl       "atan2___Q25JMath18TAtanTable<1024,f>CFff"
	bl       roundAng__Ff
	lwz      r12, 0(r31)
	fmr      f31, f1
	mr       r3, r31
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	fmr      f2, f1
	fmr      f1, f31
	bl       angDist__Fff
	fmr      f31, f1
	lfs      f0, lbl_8051C288@sda21(r2)
	lfs      f1, lbl_8051C284@sda21(r2)
	fmuls    f0, f0, f29
	fmuls    f29, f31, f30
	fmuls    f1, f1, f0
	fabs     f0, f29
	frsp     f0, f0
	fcmpo    cr0, f0, f1
	ble      lbl_802B501C
	lfs      f0, lbl_8051C278@sda21(r2)
	fcmpo    cr0, f29, f0
	ble      lbl_802B5018
	fmr      f29, f1
	b        lbl_802B501C

lbl_802B5018:
	fneg     f29, f1

lbl_802B501C:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	fadds    f1, f29, f1
	bl       roundAng__Ff
	fabs     f3, f31
	stfs     f1, 0x1fc(r31)
	lfs      f0, lbl_8051C280@sda21(r2)
	lfs      f2, 0x1fc(r31)
	frsp     f1, f3
	stfs     f2, 0x1a8(r31)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_802B5080
	li       r0, 7
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv
	b        lbl_802B5080

lbl_802B5070:
	li       r0, 6
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv

lbl_802B5080:
	mr       r3, r31
	li       r4, 0
	bl       isStartFlick__Q24Game9EnemyFuncFPQ24Game9EnemyBaseb
	clrlwi.  r0, r3, 0x18
	beq      lbl_802B50A4
	li       r0, 9
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv

lbl_802B50A4:
	mr       r3, r31
	bl       isDropTreasure__Q34Game11OtakaraBase3ObjFv
	clrlwi.  r0, r3, 0x18
	beq      lbl_802B50C8
	li       r0, 0xa
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv
	b        lbl_802B5104

lbl_802B50C8:
	lwz      r3, gameSystem__4Game@sda21(r13)
	cmplwi   r3, 0
	beq      lbl_802B5104
	lwz      r0, 0x44(r3)
	cmpwi    r0, 1
	bne      lbl_802B5104
	lfs      f1, 0x200(r31)
	lfs      f0, lbl_8051C278@sda21(r2)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_802B5104
	li       r0, 0xa
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv

lbl_802B5104:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x31c(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0x188(r31)
	lbz      r0, 0x24(r3)
	cmplwi   r0, 0
	beq      lbl_802B5154
	lwz      r0, 0x1c(r3)
	cmplwi   r0, 0x3e8
	bne      lbl_802B5154
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r6, 0
	lwz      r5, 0x2c0(r31)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_802B5154:
	psq_l    f31, 88(r1), 0, qr0
	lfd      f31, 0x50(r1)
	psq_l    f30, 72(r1), 0, qr0
	lfd      f30, 0x40(r1)
	psq_l    f29, 56(r1), 0, qr0
	lfd      f29, 0x30(r1)
	psq_l    f28, 40(r1), 0, qr0
	lfd      f28, 0x20(r1)
	lwz      r31, 0x1c(r1)
	lwz      r0, 0x64(r1)
	lwz      r30, 0x18(r1)
	mtlr     r0
	addi     r1, r1, 0x60
	blr
	*/
}

/*
 * --INFO--
 * Address:	802B518C
 * Size:	000024
 */
void StateItemTurn::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802B51B0
 * Size:	00007C
 */
void StateItemFlick::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->_2C4 = 0.0f;
	ota->m_escapeSfxTimer = 0.0f;
	ota->m_velocity2 = Vector3f(0.0f);
	ota->setEmotionExcitement();
	ota->startMotion(8, nullptr);
	ota->_2D0 = 1;
	ota->startChargeEffect();
}

/*
 * --INFO--
 * Address:	802B522C
 * Size:	000254
 */
void StateItemFlick::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);
	if (ota->_2C4 > static_cast<Parms*>(ota->m_parms)->m_properParms.m_fp11.m_value) {
		ota->finishMotion();
	}
	ota->_2C4 += sys->m_secondsPerFrame;

	EnemyAnimKeyEvent* event = ota->m_animKeyEvent;
	if (event->m_running) {
		if ((u32) event->m_type == 2) {
			Parms* parms = static_cast<Parms*>(ota->m_parms);
			EnemyFunc::flickStickPikmin(ota, parms->m_general.m_shakeRateMaybe.m_value,
											parms->m_general.m_shakeKnockback.m_value,
											parms->m_general.m_shakeDamage.m_value, -1000.0f, nullptr);
			ota->m_toFlick = 0.0f;

		} else if ((u32) event->m_type == 3) {
			ota->_2C8 = 0.0f;
			ota->_2D0 = 0;
			ota->finishChargeEffect();
			ota->createDisChargeEffect();

		} else if ((u32) event->m_type == 1000) {
			if (ota->isDropTreasure()) {
				transit(ota, OTA_ItemDrop, nullptr);
				return;
			}

			if (ota->isMovePositionSet(true)) {
				Vector3f movePos = ota->m_movePosition;
				Vector3f pos = ota->getPosition();
				f32 angle = angXZ(movePos.x, movePos.z, pos);
				if (FABS(angDist(angle, ota->getFaceDir())) <= THIRD_PI) {
					transit(ota, OTA_ItemMove, nullptr);
					return;
				}
				transit(ota, OTA_ItemTurn, nullptr);
				return;
			}

			transit(ota, OTA_ItemWait, nullptr);
		}
	}
}

/*
 * --INFO--
 * Address:	802B5480
 * Size:	000024
 */
void StateItemFlick::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802B54A4
 * Size:	00005C
 */
void StateItemDrop::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->m_escapeSfxTimer = 0.0f;
	ota->m_velocity2 = Vector3f(0.0f);
	ota->setEmotionExcitement();
	ota->startMotion(9, nullptr);
}

/*
 * --INFO--
 * Address:	802B5500
 * Size:	0001F8
 */
void StateItemDrop::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);

	EnemyAnimKeyEvent* event = ota->m_animKeyEvent;
	if (event->m_running) {
		if ((u32) event->m_type == 2) {
			ota->fallTreasure(true);

		} else if ((u32) event->m_type == 1000) {
			if (ota->m_health <= 0.0f) {
				transit(ota, OTA_Dead, nullptr);
				return;
			} else if (EnemyFunc::isStartFlick(ota, false)) {
				transit(ota, OTA_Flick, nullptr);
				return;
			}

			if (ota->isMovePositionSet(false)) {
				Vector3f movePos = ota->m_movePosition;
				Vector3f pos = ota->getPosition();
				f32 angle = angXZ(movePos.x, movePos.z, pos);
				if (FABS(angDist(angle, ota->getFaceDir())) <= THIRD_PI) {
					transit(ota, OTA_Move, nullptr);
					return;
				}
				transit(ota, OTA_Turn, nullptr);
				return;
			}

			transit(ota, OTA_Wait, nullptr);
		}
	}
}

/*
 * --INFO--
 * Address:	802B56F8
 * Size:	00002C
 */
void StateItemDrop::cleanup(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->_2E8 = 0.0f;
	ota->setEmotionCaution();
}

/*
 * --INFO--
 * Address:	802B5724
 * Size:	000048
 */
void StateBombWait::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->_2E8 = 0.0f;
	ota->m_velocity2 = Vector3f(0.0f);
	ota->startMotion(5, nullptr);
}

/*
 * --INFO--
 * Address:	802B576C
 * Size:	0001C0
 */
void StateBombWait::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);

	if (ota->m_targetCreature == nullptr) {
		ota->kill(nullptr);
		return;
	}

	if (ota->isTransitChaseState()) {
		ota->finishMotion();
	}

	EnemyAnimKeyEvent* event = ota->m_animKeyEvent;
	if (event->m_running && ((u32) event->m_type == 1000)) {
		Creature* creature = ota->getChaseTargetCreature();
		if (creature != nullptr) {
			Vector3f creaturePos = creature->getPosition();
			Vector3f pos = ota->getPosition();
			f32 angle = angXZ(creaturePos.x, creaturePos.z, pos);
			if (FABS(angDist(angle, ota->getFaceDir())) <= THIRD_PI) {
				transit(ota, OTA_BombMove, nullptr);
				return;
			}
			transit(ota, OTA_BombTurn, nullptr);
			return;
		}
		transit(ota, OTA_BombWait, nullptr);
	}
}

/*
 * --INFO--
 * Address:	802B592C
 * Size:	000004
 */
void StateBombWait::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	802B5930
 * Size:	000048
 */
void StateBombMove::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->setEmotionExcitement();
	ota->startMotion(6, nullptr);
}

/*
 * --INFO--
 * Address:	802B5978
 * Size:	0001E8
 */
void StateBombMove::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);

	if (ota->m_targetCreature == nullptr) {
		ota->kill(nullptr);
		return;
	}

	ota->stimulateBomb();

	Creature* creature = ota->getChaseTargetCreature();
	if (creature != nullptr) {
		Vector3f creaturePos = creature->getPosition();
		Vector3f pos = ota->getPosition();
		f32 angle = angXZ(creaturePos.x, creaturePos.z, pos);
		if (FABS(angDist(angle, ota->getFaceDir())) <= THIRD_PI) {
			Parms* parms = static_cast<Parms*>(ota->m_parms);
			EnemyFunc::walkToTarget(ota, creaturePos, parms->m_general.m_moveSpeed.m_value, parms->m_general.m_rotationalAccel.m_value,
										parms->m_general.m_rotationalSpeed.m_value);
		} else {
			ota->m_nextState = OTA_BombTurn;
			ota->m_velocity2 = Vector3f(0.0f);
			ota->finishMotion();
		}
	} else {
		ota->m_nextState = OTA_BombWait;
		ota->m_velocity2 = Vector3f(0.0f);
		ota->finishMotion();		
	}

	ota->startEscapeSE();

	if (ota->m_animKeyEvent->m_running && ((u32) ota->m_animKeyEvent->m_type == 1000)) {
		transit(ota, ota->m_nextState, nullptr);
	}
}

/*
 * --INFO--
 * Address:	802B5B60
 * Size:	000024
 */
void StateBombMove::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802B5B84
 * Size:	000058
 */
void StateBombTurn::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* ota = static_cast<Obj*>(enemy);
	ota->m_nextState = OTA_Null;
	ota->m_velocity2 = Vector3f(0.0f);
	ota->setEmotionExcitement();
	ota->startMotion(7, nullptr);
}

/*
 * --INFO--
 * Address:	802B5BDC
 * Size:	000224
 */
// same regswaps as StateTurn::exec above
void StateBombTurn::exec(EnemyBase* enemy)
{
	Obj* ota = static_cast<Obj*>(enemy);

	if (ota->m_targetCreature == nullptr) {
		ota->kill(nullptr);
		return;
	}

	ota->stimulateBomb();

	Creature* creature = ota->getChaseTargetCreature();
	if (creature != nullptr) {

		Vector3f creaturePos = creature->getPosition();
		Parms* parms = static_cast<Parms*>(ota->m_parms);
		f32 rotSpeed = parms->m_general.m_rotationalSpeed.m_value;
		f32 rotAccel = parms->m_general.m_rotationalAccel.m_value;

		Vector3f pos = ota->getPosition();
		f32 angleDist = angDist(_angXZ(creaturePos.x, creaturePos.z, pos.x, pos.z), ota->getFaceDir());

		f32 approxSpeed = angleDist * rotAccel;
		f32 limit = (DEG2RAD * rotSpeed) * PI;
		if (FABS(approxSpeed) > limit) {
			approxSpeed = (approxSpeed > 0.0f) ? limit : -limit;
		}

		ota->m_faceDir = roundAng(approxSpeed + ota->getFaceDir());
		ota->_1A4.m_matrix[0][1] = ota->m_faceDir;
		
		if (FABS(angleDist) <= THIRD_PI) {
			ota->m_nextState = OTA_BombMove;
			ota->finishMotion();
		}
	} else {
		ota->m_nextState = OTA_BombWait;
		ota->finishMotion();		
	}

	ota->startEscapeSE();

	if (ota->m_animKeyEvent->m_running && ((u32) ota->m_animKeyEvent->m_type == 1000)) {
		transit(ota, ota->m_nextState, nullptr);
	}
	/*
	stwu     r1, -0x70(r1)
	mflr     r0
	stw      r0, 0x74(r1)
	stfd     f31, 0x60(r1)
	psq_st   f31, 104(r1), 0, qr0
	stfd     f30, 0x50(r1)
	psq_st   f30, 88(r1), 0, qr0
	stfd     f29, 0x40(r1)
	psq_st   f29, 72(r1), 0, qr0
	stfd     f28, 0x30(r1)
	psq_st   f28, 56(r1), 0, qr0
	stw      r31, 0x2c(r1)
	stw      r30, 0x28(r1)
	lwz      r0, 0x230(r4)
	mr       r30, r3
	mr       r31, r4
	cmplwi   r0, 0
	bne      lbl_802B5C34
	mr       r3, r31
	li       r4, 0
	bl       kill__Q24Game8CreatureFPQ24Game15CreatureKillArg
	b        lbl_802B5DC8

lbl_802B5C34:
	mr       r3, r31
	bl       stimulateBomb__Q34Game11OtakaraBase3ObjFv
	mr       r3, r31
	bl       getChaseTargetCreature__Q34Game11OtakaraBase3ObjFv
	cmplwi   r3, 0
	beq      lbl_802B5D68
	mr       r4, r3
	addi     r3, r1, 0x14
	lwz      r12, 0(r4)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	mr       r4, r31
	lwz      r5, 0xc0(r31)
	lwz      r12, 0(r31)
	addi     r3, r1, 8
	lfs      f31, 0x14(r1)
	lwz      r12, 8(r12)
	lfs      f28, 0x1c(r1)
	lfs      f29, 0x334(r5)
	lfs      f30, 0x30c(r5)
	mtctr    r12
	bctrl
	lfs      f1, 8(r1)
	lis      r3, atanTable___5JMath@ha
	lfs      f0, 0x10(r1)
	addi     r3, r3, atanTable___5JMath@l
	fsubs    f1, f31, f1
	fsubs    f2, f28, f0
	bl       "atan2___Q25JMath18TAtanTable<1024,f>CFff"
	bl       roundAng__Ff
	lwz      r12, 0(r31)
	fmr      f31, f1
	mr       r3, r31
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	fmr      f2, f1
	fmr      f1, f31
	bl       angDist__Fff
	fmr      f31, f1
	lfs      f0, lbl_8051C288@sda21(r2)
	lfs      f1, lbl_8051C284@sda21(r2)
	fmuls    f0, f0, f29
	fmuls    f29, f31, f30
	fmuls    f1, f1, f0
	fabs     f0, f29
	frsp     f0, f0
	fcmpo    cr0, f0, f1
	ble      lbl_802B5D14
	lfs      f0, lbl_8051C278@sda21(r2)
	fcmpo    cr0, f29, f0
	ble      lbl_802B5D10
	fmr      f29, f1
	b        lbl_802B5D14

lbl_802B5D10:
	fneg     f29, f1

lbl_802B5D14:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	fadds    f1, f29, f1
	bl       roundAng__Ff
	fabs     f3, f31
	stfs     f1, 0x1fc(r31)
	lfs      f0, lbl_8051C280@sda21(r2)
	lfs      f2, 0x1fc(r31)
	frsp     f1, f3
	stfs     f2, 0x1a8(r31)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_802B5D78
	li       r0, 0xc
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv
	b        lbl_802B5D78

lbl_802B5D68:
	li       r0, 0xb
	mr       r3, r31
	stw      r0, 0x2c0(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv

lbl_802B5D78:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x31c(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0x188(r31)
	lbz      r0, 0x24(r3)
	cmplwi   r0, 0
	beq      lbl_802B5DC8
	lwz      r0, 0x1c(r3)
	cmplwi   r0, 0x3e8
	bne      lbl_802B5DC8
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r6, 0
	lwz      r5, 0x2c0(r31)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_802B5DC8:
	psq_l    f31, 104(r1), 0, qr0
	lfd      f31, 0x60(r1)
	psq_l    f30, 88(r1), 0, qr0
	lfd      f30, 0x50(r1)
	psq_l    f29, 72(r1), 0, qr0
	lfd      f29, 0x40(r1)
	psq_l    f28, 56(r1), 0, qr0
	lfd      f28, 0x30(r1)
	lwz      r31, 0x2c(r1)
	lwz      r0, 0x74(r1)
	lwz      r30, 0x28(r1)
	mtlr     r0
	addi     r1, r1, 0x70
	blr
	*/
}

/*
 * --INFO--
 * Address:	802B5E00
 * Size:	000024
 */
void StateBombTurn::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }
} // namespace OtakaraBase
} // namespace Game
