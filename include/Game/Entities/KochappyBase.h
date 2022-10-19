#ifndef _GAME_ENTITIES_KOCHAPPYBASE_H
#define _GAME_ENTITIES_KOCHAPPYBASE_H

#include "Game/EnemyAnimatorBase.h"
#include "Game/EnemyParmsBase.h"
#include "Game/EnemyBase.h"
#include "Game/EnemyMgrBase.h"
#include "Game/PelletView.h"
#include "Game/shadowMgr.h"
#include "Game/WalkSmokeEffect.h"
#include "SysShape/Joint.h"
#include "CollInfo.h"

/**
 * --Header for Dwarf Bulborb Base Class--
 * Derived classes:
 * BlueKochappy   = Dwarf Orange Bulborb
 * Catfish        = Water Dumple
 * Kochappy       = Dwarf Red Bulborb
 * YellowKochappy = Dwarf Snowy Bulborb
 */

namespace Game {
namespace KochappyBase {
struct Parms;

struct FSM : public EnemyStateMachine {
	virtual void init(EnemyBase*); // _08

	// _00		= VTBL
	// _00-_1C	= EnemyStateMachine
};

struct Obj : public EnemyBase {
	Obj();

	//////////////// VTABLE - Note: this order is needed for correct weak function ordering
	virtual void onInit(CreatureInitArg*);                  // _30
	virtual void doDirectDraw(Graphics&);                   // _50
	virtual void bounceCallback(Sys::Triangle*);            // _E8
	virtual void getShadowParam(ShadowParam&);              // _134
	virtual ~Obj() { }                                      // _1BC (weak)
	virtual void birth(Vector3f&, f32);                     // _1C0
	virtual void setInitialSetting(EnemyInitialParamBase*); // _1C4
	virtual void doUpdate();                                // _1C8
	virtual void doDebugDraw(Graphics&);                    // _1EC
	virtual void changeMaterial() = 0;                      // _200
	virtual Vector3f getOffsetForMapCollision();            // _224
	virtual void initMouthSlots();                          // _22C
	virtual void initWalkSmokeEffect();                     // _230
	virtual WalkSmokeEffect::Mgr* getWalkSmokeEffectMgr();  // _234
	virtual bool pressCallBack(Creature*, f32, CollPart*);  // _27C
	virtual void doStartStoneState();                       // _2A4
	virtual void doFinishStoneState();                      // _2A8
	virtual void startCarcassMotion();                      // _2C4
	virtual void setFSM(FSM* fsm)                           // _2F8 (weak)
	{
		m_FSM = fsm;
		m_FSM->init(this);
		m_currentLifecycleState = nullptr;
	}
	virtual void setAnimationSpeed(f32 speed) // _2FC (weak)
	{
		EnemyBase::setAnimSpeed(speed);
	}
	virtual MouthSlots* getMouthSlots() // _25C (weak)
	{
		return &m_mouthSlots;
	}
	virtual void resetEnemyNonStone() { }            // _300 (weak)
	virtual void setEnemyNonStone() { }              // _304 (weak)
	virtual f32 getDownSmokeScale() { return 0.4f; } // _2EC (weak)
	//////////////// VTABLE END

	inline Parms* getParms() { return C_PARMS; }

	// _00 		= VTBL
	// _00-_2BC	= EnemyBase
	FSM* m_FSM;                          // _2BC
	MouthSlots m_mouthSlots;             // _2C0
	SysShape::Joint* m_shadowJoint;      // _2C8
	f32 _2CC;                            // _2CC
	WalkSmokeEffect::Mgr m_walkSmokeMgr; // _2D0
	                                     // _2D4 = PelletView
};

struct Mgr : public EnemyMgrBase {
	Mgr(int objLimit, u8 modelType);

	virtual ~Mgr();                                     // _58 (weak)
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID(); // _AC (weak)
	virtual SysShape::Model* createModel();             // _B0
	virtual void loadModelData();                       // _C8
	virtual void loadAnimData();                        // _CC

	// _00 		= VTBL
	// _00-_44	= EnemyMgrBase
};

struct Parms : public EnemyParmsBase {
	Parms();

	virtual void read(Stream& stream); // _08 (weak)

	// _00-_7F8	= EnemyParmsBase
	u8 _7F8[0x88]; // _7F8
};

struct ProperAnimator : public EnemyAnimatorBase {
	virtual ~ProperAnimator() { }                                    // _08 (weak)
	virtual void setAnimMgr(SysShape::AnimMgr*);                     // _0C
	virtual SysShape::Animator& getAnimator() { return m_animator; } // _10 (weak)
	virtual SysShape::Animator& getAnimator(int);                    // _14

	// _00 		= VTBL
	// _00-_10	= EnemyAnimatorBase
	SysShape::Animator m_animator; // _10
};

/////////////////////////////////////////////////////////////////
// STATE MACHINE DEFINITIONS
enum StateID {
	KOCHAPPY_Wait       = 0,
	KOCHAPPY_Dead       = 1,
	KOCHAPPY_Turn       = 2,
	KOCHAPPY_Walk       = 3,
	KOCHAPPY_Attack     = 4,
	KOCHAPPY_Flick      = 5,
	KOCHAPPY_TurnToHome = 6,
	KOCHAPPY_GoHome     = 7,
	KOCHAPPY_Press      = 8,
	KOCHAPPY_Demo       = 9,
	KOCHAPPY_Count,
};

struct State : public EnemyFSMState {
	inline State(int stateID)
	    : EnemyFSMState(stateID)
	{
	}

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateAttack : public State {
	StateAttack(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDead : public State {
	StateDead(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDemo : public State {
	StateDemo(int);

	virtual void init(EnemyBase*, StateArg*); // _08

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct FlickArg : public StateArg {
	int _00; // _00, sets _10 in StateFlick
};

struct StateFlick : public State {
	StateFlick(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
	int _10; // _10
};

struct StateGoHome : public State {
	StateGoHome(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
	int _10; // _10
};

struct StatePress : public State {
	StatePress(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateTurn : public State {
	StateTurn(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
	int _10; // _10
};

struct StateTurnToHome : public State {
	StateTurnToHome(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct WaitArg : public StateArg {
	u32 _00; // _00
};

struct StateWait : public State {
	StateWait(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateWalk : public State {
	StateWalk(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
	int _10; // _10
};
/////////////////////////////////////////////////////////////////

} // namespace KochappyBase

} // namespace Game

#endif
