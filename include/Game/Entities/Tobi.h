#ifndef _GAME_ENTITIES_TOBI_H
#define _GAME_ENTITIES_TOBI_H

#include "Game/EnemyStateMachine.h"
#include "Game/EnemyAnimatorBase.h"
#include "Game/EnemyParmsBase.h"
#include "Game/EnemyMgrBase.h"
#include "Game/EnemyBase.h"
#include "Collinfo.h"

#define GET_APPCHECK_VAL(check)      ((u8)check)
#define GET_APPCHECK_MAX(check)      (check >> 8)
#define SET_APPCHECK_MAX(check, val) (check = (val) << 8)

/**
 * --Header for Shearwigs (Tobi)--
 */

namespace Game {
namespace ItemBridge {
struct Item;
} // namespace ItemBridge

namespace Tobi {
struct FSM;

enum StateID {
	TOBI_NULL       = -1,
	TOBI_Dead       = 0,
	TOBI_Press      = 1,
	TOBI_Stay       = 2,
	TOBI_Appear     = 3,
	TOBI_Dive       = 4,
	TOBI_Move       = 5,
	TOBI_MoveSide   = 6,
	TOBI_MoveCentre = 7,
	TOBI_MoveTop    = 8,
	TOBI_GoHome     = 9,
	TOBI_Fly        = 10,
	TOBI_Attack1    = 11,
	TOBI_Attack2    = 12,
	TOBI_Eat        = 13,
	TOBI_StateCount,
};

struct Obj : public EnemyBase {
	Obj();

	//////////////// VTABLE
	virtual void onInit(CreatureInitArg* settings);                             // _30
	virtual void doDirectDraw(Graphics& gfx);                                   // _50
	virtual bool isUnderground();                                               // _D0 (weak)
	virtual void getShadowParam(ShadowParam& settings);                         // _134
	virtual ~Obj() { }                                                          // _1BC (weak)
	virtual void setInitialSetting(EnemyInitialParamBase* params);              // _1C4
	virtual void doUpdate();                                                    // _1CC
	virtual void doDebugDraw(Graphics& gfx);                                    // _1EC
	virtual void initMouthSlots();                                              // _22C
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID();                         // _258 (weak)
	virtual MouthSlots* getMouthSlots();                                        // _25C (weak)
	virtual bool pressCallBack(Creature*, f32, CollPart*);                      // _27C
	bool flyCollisionCallBack(Creature* source, f32 damage, CollPart* part);    // _280
	virtual bool hipdropCallBack(Creature* source, f32 damage, CollPart* part); // _284
	virtual void doStartStoneState();                                           // _2A4
	virtual void doFinishStoneState();                                          // _2A8
	virtual void doStartEarthquakeFitState();                                   // _2B8
	virtual void doFinishEarthquakeFitState();                                  // _2BC
	virtual void lifeRecover();                                                 // _2C0
	virtual void startCarcassMotion();                                          // _2C4
	virtual f32 getDownSmokeScale();                                            // _2EC (weak)
	virtual void setFSM(FSM* fsm);                                              // _2F8
	//////////////// VTABLE END

	void lifeIncrement();
	void randomFlyingTarget();
	bool isFlyingLife();
	void setInWaterDamage();
	void resetAppearCheck();
	bool isAppearCheck();
	void resetBridgeSearch();
	void setBridgeSearch();
	void setNearestBridge();
	void setCullingCheck();
	int checkBreakOrMove();
	bool isBreakBridge();
	bool moveBridgeSide();
	bool moveBridgeCentre();
	bool moveBridgeTop();
	void breakTargetBridge();
	void createAppearEffect();
	void createDisAppearEffect();
	void createBridgeEffect();
	void createEatEffect();

	// _00 		= VTBL
	// _00-_2BC	= EnemyBase
	FSM* mFsm;                 // _2BC
	u8 _2C0;                   // _2C0
	bool mIsUnderground;       // _2C1
	u16 mAppearCheck;          // _2C2
	StateID mNextState;        // _2C4
	MouthSlots mMouthSlots;    // _2C8
	Vector3f mTargetPosition;  // _2D0
	ItemBridge::Item* mBridge; // _2DC
	f32 _2E0;                  // _2E0
	f32 _2E4;                  // _2E4
	                           // _2E8 = PelletView
};

struct Mgr : public EnemyMgrBase {
	Mgr(int objLimit, u8 modelType);

	// virtual ~Mgr();                                     // _58 (weak)
	virtual void doAlloc();                            // _A8
	virtual void createObj(int);                       // _A0
	virtual EnemyBase* getEnemy(int idx);              // _A4
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID() // _AC (weak)
	{
		return EnemyTypeID::EnemyID_Tobi;
	}

	// _00 		= VTBL
	// _00-_44	= EnemyMgrBase
	Obj* mObj; // _44, likely an array of Objs
};

struct Parms : public EnemyParmsBase {
	struct ProperParms : public Parameters {
		inline ProperParms()
		    : Parameters(nullptr, "EnemyParmsBase")
		    , mTakeOffHealthRatio(this, 'fp01', "�������C�t", 0.5f, 0.0f, 1.0f)  // 'takeoff life'
		    , mLandHealthRatio(this, 'fp02', "�������C�t", 0.7f, 0.0f, 1.0f)     // 'landing life'
		    , mFlightHeight(this, 'fp03', "��s�I�t�Z�b�g", 60.0f, 0.0f, 300.0f) // 'flight offset'
		    , mPoisonDamage(this, 'fp11', "���s�N�~��", 300.0f, 0.0f, 10000.0f)  // 'white pikmin'
		    , mBridgeDamage(this, 'fp12', "���H���p���[", 75.0f, 0.0f, 100.0f)   // 'bridge eating power'
		{
		}

		Parm<f32> mTakeOffHealthRatio; // _804
		Parm<f32> mLandHealthRatio;    // _82C
		Parm<f32> mFlightHeight;       // _854
		Parm<f32> mPoisonDamage;       // _87C, fp11
		Parm<f32> mBridgeDamage;       // _8A4, fp12
	};

	Parms() { }

	virtual void read(Stream& stream) // _08 (weak)
	{
		CreatureParms::read(stream);
		mGeneral.read(stream);
		mProperParms.read(stream);
	}

	// _00-_7F8	= EnemyParmsBase
	ProperParms mProperParms; // _7F8
};

struct ProperAnimator : public EnemyAnimatorBase {
	virtual ~ProperAnimator() { }                                    // _08 (weak)
	virtual void setAnimMgr(SysShape::AnimMgr* mgr);                 // _0C
	virtual SysShape::Animator& getAnimator() { return mAnimator; }; // _10 (weak)
	virtual SysShape::Animator& getAnimator(int idx);                // _14

	// _00 		= VTBL
	// _00-_10	= EnemyAnimatorBase
	SysShape::Animator mAnimator; // _10
};

/////////////////////////////////////////////////////////////////
// STATE MACHINE DEFINITIONS
struct FSM : public EnemyStateMachine {
	virtual void init(EnemyBase*); // _08

	// _00		= VTBL
	// _00-_1C	= EnemyStateMachine
};

struct State : public EnemyFSMState {
	inline State(int stateID, char* name)
	    : EnemyFSMState(stateID)
	{
		mName = name;
	}

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateAppear : public State {
	inline StateAppear()
	    : State(TOBI_Appear, "appear")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateAttack1 : public State {
	inline StateAttack1()
	    : State(TOBI_Attack1, "attack1")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateAttack2 : public State {
	inline StateAttack2()
	    : State(TOBI_Attack2, "attack2")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDead : public State {
	inline StateDead()
	    : State(TOBI_Dead, "dead")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDive : public State {
	inline StateDive()
	    : State(TOBI_Dive, "dive")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateEat : public State {
	inline StateEat()
	    : State(TOBI_Eat, "eat")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateFly : public State {
	inline StateFly()
	    : State(TOBI_Fly, "fly")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateGoHome : public State {
	inline StateGoHome()
	    : State(TOBI_GoHome, "gohome")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateMove : public State {
	inline StateMove()
	    : State(TOBI_Move, "move")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateMoveCentre : public State {
	inline StateMoveCentre()
	    : State(TOBI_MoveCentre, "movecentre")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateMoveSide : public State {
	inline StateMoveSide()
	    : State(TOBI_MoveSide, "moveside")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateMoveTop : public State {
	inline StateMoveTop()
	    : State(TOBI_MoveTop, "movetop")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StatePress : public State {
	inline StatePress()
	    : State(TOBI_Press, "press")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateStay : public State {
	inline StateStay()
	    : State(TOBI_Stay, "stay")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};
/////////////////////////////////////////////////////////////////
} // namespace Tobi
} // namespace Game

#endif
