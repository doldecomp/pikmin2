#include "Game/Entities/Pom.h"
#include "Game/EnemyAnimKeyEvent.h"

namespace Game {
namespace Pom {

/*
 * --INFO--
 * Address:	80255CA4
 * Size:	000224
 */
void FSM::init(EnemyBase* enemy)
{
	create(POM_Count);
	registerState(new StateWait);
	registerState(new StateDead);
	registerState(new StateOpen);
	registerState(new StateClose);
	registerState(new StateShot);
	registerState(new StateSwing);
}

/*
 * --INFO--
 * Address:	80255EC8
 * Size:	00002C
 */
void StateWait::init(EnemyBase* enemy, StateArg* stateArg) { enemy->startMotion(0, nullptr); }

/*
 * --INFO--
 * Address:	80255EF4
 * Size:	00005C
 */
void StateWait::exec(EnemyBase* enemy)
{
	Obj* pom = static_cast<Obj*>(enemy);
	pom->changePomColor();
	transit(pom, POM_Open, nullptr);
}

/*
 * --INFO--
 * Address:	80255F50
 * Size:	000004
 */
void StateWait::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	80255F54
 * Size:	000060
 */
void StateDead::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* pom  = static_cast<Obj*>(enemy);
	pom->_2C0 = false;
	pom->_2C1 = 0;
	pom->_2E4 = 0.0f;
	pom->resetEvent(0, EB_Cullable);
	pom->startMotion(1, nullptr);
	pom->createPomDeadEffect();
}

/*
 * --INFO--
 * Address:	80255FB4
 * Size:	000044
 */
void StateDead::exec(EnemyBase* enemy)
{
	if (enemy->m_animKeyEvent->m_running && (u32)enemy->m_animKeyEvent->m_type == 1000) {
		enemy->kill(nullptr);
	}
}

/*
 * --INFO--
 * Address:	80255FF8
 * Size:	000004
 */
void StateDead::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	80255FFC
 * Size:	000040
 */
void StateOpen::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* pom  = static_cast<Obj*>(enemy);
	pom->_2C0 = false;
	pom->_2C1 = 0;
	pom->_2E4 = 0.0f;
	pom->startMotion(2, nullptr);
}

/*
 * --INFO--
 * Address:	8025603C
 * Size:	0000A0
 */
void StateOpen::exec(EnemyBase* enemy)
{
	Obj* pom = static_cast<Obj*>(enemy);
	pom->changePomColor();
	if (pom->_2C0) {
		if (pom->isEvent(0, EB_Collision)) {
			transit(pom, POM_Swing, nullptr);
		}
	} else if (pom->m_animKeyEvent->m_running && (u32)pom->m_animKeyEvent->m_type == 2) {
		pom->_2C0 = true;
		pom->_2C1 = 1;
	}
}

/*
 * --INFO--
 * Address:	802560DC
 * Size:	000004
 */
void StateOpen::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	802560E0
 * Size:	000040
 */
void StateClose::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* pom  = static_cast<Obj*>(enemy);
	pom->_2C0 = false;
	pom->_2C1 = 0;
	pom->_2E4 = 0.0f;
	pom->startMotion(3, nullptr);
}

/*
 * --INFO--
 * Address:	80256120
 * Size:	000078
 */
void StateClose::exec(EnemyBase* enemy)
{
	if (enemy->m_animKeyEvent->m_running && (u32)enemy->m_animKeyEvent->m_type == 1000) {
		if (enemy->m_stickPikminCount != 0) {
			transit(enemy, POM_Shot, nullptr);
		} else {
			transit(enemy, POM_Wait, nullptr);
		}
	}
}

/*
 * --INFO--
 * Address:	80256198
 * Size:	000004
 */
void StateClose::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	8025619C
 * Size:	00004C
 */
void StateShot::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* pom  = static_cast<Obj*>(enemy);
	pom->_2C0 = false;
	pom->_2C1 = 0;
	pom->_2E4 = 0.0f;
	pom->resetEvent(0, EB_Cullable);
	pom->startMotion(4, nullptr);
}

/*
 * --INFO--
 * Address:	802561E8
 * Size:	000094
 */
void StateShot::exec(EnemyBase* enemy)
{
	Obj* pom = static_cast<Obj*>(enemy);
	if (enemy->m_animKeyEvent->m_running) {
		if ((u32)enemy->m_animKeyEvent->m_type == 2) {
			pom->shotPikmin();
		} else if ((u32)enemy->m_animKeyEvent->m_type == 1000) {
			if (pom->_2C4 < pom->_2C8) {
				transit(pom, POM_Wait, nullptr);
			} else {
				transit(pom, POM_Dead, nullptr);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	8025627C
 * Size:	000010
 */
void StateShot::cleanup(EnemyBase* enemy) { enemy->setEvent(0, EB_Cullable); }

/*
 * --INFO--
 * Address:	8025628C
 * Size:	00003C
 */
void StateSwing::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* pom  = static_cast<Obj*>(enemy);
	pom->_2C0 = false;
	pom->_2E4 = 0.0f;
	pom->startMotion(5, nullptr);
}

/*
 * --INFO--
 * Address:	802562C8
 * Size:	0000F8
 */
void StateSwing::exec(EnemyBase* enemy)
{
	Obj* pom = static_cast<Obj*>(enemy);
	pom->changePomColor();
	pom->_2E4 += sys->m_secondsPerFrame;

	if (pom->_2E4 > static_cast<Parms*>(pom->m_parms)->m_properParms.m_fp01.m_value || !(pom->_2C4 < pom->_2C8)) {
		transit(pom, POM_Close, nullptr);

	} else if (pom->_2C0) {
		if (pom->isEvent(0, EB_Collision)) {
			transit(pom, POM_Swing, nullptr);
		}

	} else if (pom->m_animKeyEvent->m_running && (u32)pom->m_animKeyEvent->m_type == 1000) {
		pom->_2C0 = true;
	}
}

/*
 * --INFO--
 * Address:	802563C0
 * Size:	000004
 */
void StateSwing::cleanup(EnemyBase* enemy) { }
} // namespace Pom
} // namespace Game
