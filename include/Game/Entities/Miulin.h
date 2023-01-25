#ifndef _GAME_ENTITIES_MIULIN_H
#define _GAME_ENTITIES_MIULIN_H

#include "Game/EnemyStateMachine.h"
#include "Game/EnemyAnimatorBase.h"
#include "Game/EnemyParmsBase.h"
#include "Game/EnemyMgrBase.h"
#include "Game/EnemyBase.h"
#include "Game/WalkSmokeEffect.h"
#include "SysShape/Joint.h"

/**
 * --Header for Mamuta (Miulin)--
 */

namespace Game {
namespace Miulin {
/////////////////////////////////////////////////////////////////
// STATE MACHINE DEFINITIONS
enum StateID {
	MIULIN_Wait        = 0,
	MIULIN_Walk        = 1,
	MIULIN_AttackStart = 2,
	MIULIN_Attacking   = 3,
	MIULIN_AttackEnd   = 4,
	MIULIN_Turn        = 5,
	MIULIN_Flick       = 6,
	MIULIN_Dead        = 7,
	MIULIN_StateCount,
};

struct FSM : public EnemyStateMachine {
	virtual void init(EnemyBase*); // _08

	// _00		= VTBL
	// _00-_1C	= EnemyStateMachine
};

struct State : public EnemyFSMState {
	inline State(int stateID)
	    : EnemyFSMState(stateID)
	{
	}

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateAttackEnd : public State {
	StateAttackEnd(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateAttacking : public State {
	StateAttacking(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
	u8 _10; // _10
};

struct StateAttackStart : public State {
	StateAttackStart(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDead : public State {
	StateDead(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateFlick : public State {
	StateFlick(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateTurn : public State {
	StateTurn(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateWait : public State {
	StateWait(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateWalk : public State {
	StateWalk(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
	u8 _10[0x8]; // _10, unknown
};
/////////////////////////////////////////////////////////////////

struct Obj : public EnemyBase {
	Obj();

	//////////////// VTABLE
	virtual void onInit(CreatureInitArg* settings);         // _30
	virtual void doSimulation(f32);                         // _4C
	virtual void doDirectDraw(Graphics& gfx);               // _50
	virtual void getShadowParam(ShadowParam& settings);     // _134
	virtual void applyImpulse(Vector3f&, Vector3f&);        // _18C (weak)
	virtual Vector3f getGoalPos();                          // _198 (weak)
	virtual ~Obj() { }                                      // _1BC (weak)
	virtual void birth(Vector3f&, f32);                     // _1C0
	virtual void setInitialSetting(EnemyInitialParamBase*); // _1C4 (weak)
	virtual void doUpdate();                                // _1CC
	virtual void doDebugDraw(Graphics&);                    // _1EC
	virtual void setParameters();                           // _228
	virtual void initWalkSmokeEffect();                     // _230
	virtual WalkSmokeEffect::Mgr* getWalkSmokeEffectMgr();  // _234
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID();     // _258 (weak)
	virtual void startCarcassMotion();                      // _2C4
	virtual void wallCallback(const MoveInfo&);             // _2E8
	virtual f32 getDownSmokeScale();                        // _2EC (weak)
	virtual void setFSM(FSM*);                              // _2F8 (weak)
	//////////////// VTABLE END

	bool isAttackStart();
	bool isFindTarget();
	bool isOutOfTerritory();
	bool isProhibitedSearch();
	bool isStartWalk();
	void setReturnState();
	void walkFunc();
	void turnFunc(f32);
	bool isReachToGoal(f32);
	void setNextGoal();
	bool nextTargetTurnCheck();
	bool isNowCaution();
	void landEffect();
	void attackEffect(Vector3f&);

	// _00 		= VTBL
	// _00-_2BC	= EnemyBase
	Vector3f mGoalPosition;             // _2BC
	Miulin::StateID mNextState;         // _2C8
	SysShape::Joint* mKoshiJoint;       // _2CC
	u32 _2D0;                           // _2D0
	Vector3f _2D4;                      // _2D4
	int _2E0;                           // _2E0
	u8 _2E4;                            // _2E4
	f32 _2E8;                           // _2E8, timer?
	WalkSmokeEffect::Mgr mWalkSmokeMgr; // _2EC
	FSM* mFsm;                          // _2F4
	                                    // _2F8 = PelletView
};

struct Mgr : public EnemyMgrBase {
	Mgr(int objLimit, u8 modelType);

	// virtual ~Mgr();                                     // _58 (weak)
	virtual EnemyBase* birth(EnemyBirthArg&);          // _70
	virtual void doAlloc();                            // _A8
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID() // _AC (weak)
	{
		return EnemyTypeID::EnemyID_Miulin;
	}
	virtual void createObj(int count) // _A0 (weak)
	{
		mObj = new Obj[count];
	}
	virtual EnemyBase* getEnemy(int index) // _A4 (weak)
	{
		return &mObj[index];
	}

	// _00 		= VTBL
	// _00-_44	= EnemyMgrBase
	Obj* mObj; // _44, array of Objs
};

struct Parms : public EnemyParmsBase {
	struct ProperParms : public Parameters {
		inline ProperParms()
		    : Parameters(nullptr, "EnemyParmsBase")
		    , mIp01(this, 'ip01', "���^�[���J�E���^", 100, 0, 1000)         // 'return counter'
		    , mFp03(this, 'fp03', "�A���v���X�p�x", 20.0f, 0.0f, 180.0f)    // 'continuous press angle'
		    , mFp04(this, 'fp04', "�_�b�V�����x�{��", 2.0f, 0.0f, 10.0f)    // 'dash speed multiplier'
		    , mFp05(this, 'fp05', "�_�b�V���A�j���{��", 2.0f, 0.0f, 10.0f)  // 'dash animation scale'
		    , mFp06(this, 'fp06', "����I���p�x", 10.0f, 0.0f, 180.0f)      // 'turning end angle'
		    , mFp07(this, 'fp07', "�_�b�V���\\�p�x", 30.0f, 0.0f, 180.0f) // 'possible dash angle'
		    , mFp08(this, 'fp08', "�U���͈͍ŏ�", 25.0f, 0.0f, 100.0f)      // 'minimum attack range'
		{
		}

		Parm<int> mIp01; // _804
		Parm<f32> mFp03; // _82C
		Parm<f32> mFp04; // _854
		Parm<f32> mFp05; // _87C
		Parm<f32> mFp06; // _8A4
		Parm<f32> mFp07; // _8CC
		Parm<f32> mFp08; // _8F4
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

} // namespace Miulin
} // namespace Game

#endif
