#ifndef _GAME_ENTITIES_FROG_H
#define _GAME_ENTITIES_FROG_H

#include "Game/EnemyStateMachine.h"
#include "Game/EnemyAnimatorBase.h"
#include "Game/EnemyParmsBase.h"
#include "Game/EnemyMgrBase.h"
#include "Game/EnemyBase.h"

/**
 * --Header for Yellow Wollywog (Frog)--
 * Derived Classes:
 * MaroFrog	= Wollywog
 */

namespace efx {
struct TFrogPota;
} // namespace efx

namespace Game {
namespace Frog {
struct FSM;

struct Obj : public EnemyBase {
	Obj();

	//////////////// VTABLE
	virtual void onInit(CreatureInitArg* settings);                                          // _30
	virtual void onKill(CreatureKillArg* settings);                                          // _34
	virtual void doDirectDraw(Graphics& gfx);                                                // _50
	virtual void inWaterCallback(WaterBox* wb) { }                                           // _84 (weak)
	virtual void outWaterCallback() { }                                                      // _88 (weak)
	virtual void collisionCallback(CollEvent& event);                                        // _EC
	virtual void getShadowParam(ShadowParam& settings);                                      // _134
	virtual ~Obj() { }                                                                       // _1BC (weak)
	virtual void setInitialSetting(EnemyInitialParamBase*);                                  // _1C4
	virtual void doUpdate();                                                                 // _1CC
	virtual void doDebugDraw(Graphics&);                                                     // _1EC
	virtual void doSimulationFlying(f32);                                                    // _1F8
	virtual void getCommonEffectPos(Vector3f&);                                              // _204
	virtual Vector3f getOffsetForMapCollision();                                             // _224
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID() { return EnemyTypeID::EnemyID_Frog; } // _258 (weak)
	virtual void doStartStoneState();                                                        // _2A4
	virtual void doFinishStoneState();                                                       // _2A8
	virtual void doStartEarthquakeFitState();                                                // _2B8
	virtual void doFinishEarthquakeFitState();                                               // _2BC
	virtual void startCarcassMotion();                                                       // _2C4
	virtual void doStartWaitingBirthTypeDrop();                                              // _2E0
	virtual void doFinishWaitingBirthTypeDrop();                                             // _2E4
	virtual f32 getDownSmokeScale() { return 1.0f; }                                         // _2EC (weak)
	virtual void doStartMovie();                                                             // _2F0
	virtual void doEndMovie();                                                               // _2F4
	virtual void setFSM(FSM*);                                                               // _2F8
	virtual Vector3f viewGetCollTreeOffset() { return Vector3f(20.0f, 15.0f, 0.0f); }        // _2FC (weak)
	virtual void attackNaviPosition() { }                                                    // _300 (weak)
	//////////////// VTABLE END

	void updateCaution();
	void getViewAngle();
	void startJumpAttack();
	void resetHomePosition();
	void pressOnGround();
	void createEffect();
	void setupEffect();
	void startJumpEffect();
	void finishJumpEffect();
	void createDownEffect(f32);
	void effectDrawOn();
	void effectDrawOff();

	// _00 		= VTBL
	// _00-_2BC	= EnemyBase
	FSM* mFsm;                // _2BC
	f32 _2C0;                 // _2C0
	f32 _2C4;                 // _2C4
	Vector3f mTargetPosition; // _2C8
	int _2D4;                 // _2D4
	bool _2D8;                // _2D8, unknown
	bool _2D9;                // _2D9, unknown
	efx::TFrogPota* mEfxPota; // _2DC
	                          // _2E0 = PelletView
};

struct Mgr : public EnemyMgrBase {
	Mgr(int objLimit, u8 modelType);

	// virtual ~Mgr();                                     // _58 (weak)
	virtual void doAlloc();                            // _A8
	virtual void createObj(int);                       // _A0
	virtual EnemyBase* getEnemy(int idx);              // _A4
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID() // _AC (weak)
	{
		return EnemyTypeID::EnemyID_Frog;
	}

	// _00 		= VTBL
	// _00-_44	= EnemyMgrBase
	Obj* mObj; // _48, array of Objs
};

struct Parms : public EnemyParmsBase {
	struct ProperParms : public Parameters {
		inline ProperParms()
		    : Parameters(nullptr, "FrogParms")
		    , mFp01(this, 'fp01', "�󒆎���", 1.5f, 0.0f, 5.0f)          // 'air time'
		    , mFp02(this, 'fp02', "�W�����v���x", 400.0f, 0.0f, 1000.0f) // 'jump speed'
		    , mFp03(this, 'fp03', "���s�m��", 0.2f, 0.0f, 1.0f)          // 'probability of failure'
		    , mFp04(this, 'fp04', "���������x", 300.0f, 0.0f, 500.0f)    // 'initial fall velocity'
		{
		}

		Parm<f32> mFp01; // _804
		Parm<f32> mFp02; // _82C
		Parm<f32> mFp03; // _854
		Parm<f32> mFp04; // _87C
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
	virtual ~ProperAnimator() { }                                   // _08 (weak)
	virtual void setAnimMgr(SysShape::AnimMgr* mgr);                // _0C
	virtual SysShape::Animator& getAnimator() { return mAnimator; } // _10 (weak)
	virtual SysShape::Animator& getAnimator(int idx);               // _14

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
	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateAttack : public State {
	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDead : public State {
	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateFail : public State {
	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateFall : public State {
	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateGoHome : public State {
	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateJump : public State {
	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateJumpWait : public State {
	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateTurn : public State {
	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateTurnToHome : public State {
	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateWait : public State {
	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};
/////////////////////////////////////////////////////////////////
} // namespace Frog
} // namespace Game

#endif
