#ifndef _GAME_ENTITIES_ROCK_H
#define _GAME_ENTITIES_ROCK_H

#include "Game/EnemyStateMachine.h"
#include "Game/EnemyAnimatorBase.h"
#include "Game/EnemyParmsBase.h"
#include "Game/EnemyMgrBase.h"
#include "Game/EnemyBase.h"
#include "Game/gameGenerator.h"

/**
 * --Header for Boulders (Rock)--
 * For both falling and rolling boulders.
 */

namespace efx {
struct TRockRun;
struct TRockGrRun;
struct TRockWRun;
} // namespace efx

namespace Game {
namespace Rock {
struct FSM;

struct Obj : public EnemyBase {
	Obj();

	//////////////// VTABLE
	virtual void onInit(CreatureInitArg*);                   // _30
	virtual void onKill(CreatureKillArg*);                   // _34
	virtual void doDirectDraw(Graphics&);                    // _50
	virtual void inWaterCallback(WaterBox*);                 // _84
	virtual void outWaterCallback();                         // _88
	virtual bool isLivingThing();                            // _D4 (weak)
	virtual void collisionCallback(CollEvent&);              // _EC
	virtual void getShadowParam(ShadowParam&);               // _134
	virtual bool needShadow();                               // _138
	virtual bool ignoreAtari(Creature*);                     // _190
	virtual ~Obj();                                          // _1BC (weak)
	virtual void birth(Vector3f&, f32);                      // _1C0
	virtual void setInitialSetting(EnemyInitialParamBase*);  // _1C4
	virtual void doUpdate();                                 // _1CC
	virtual void doDebugDraw(Graphics&);                     // _1EC
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID();      // _258 (weak)
	virtual bool hipdropCallBack(Creature*, f32, CollPart*); // _284
	virtual void wallCallback(const MoveInfo&);              // _2E8
	virtual void doStartMovie();                             // _2F0
	virtual void doEndMovie();                               // _2F4
	virtual void setFSM(FSM*);                               // _2F8
	//////////////// VTABLE END

	bool fallRockScaleUp();
	void moveRockScaleUp();
	void initMoveVelocity();
	void updateMoveVelocity();
	void createEffect();
	void setupEffect();
	void startFallEffect();
	void finishFallEffect();
	void startRollingGroundEffect();
	void finishRollingGroundEffect();
	void startRollingWaterEffect();
	void finishRollingWaterEffect();
	void updateWaterEffectPosition();
	void createRockDeadEffect();
	void effectDrawOn();
	void effectDrawOff();

	// _00 		= VTBL
	// _00-_2BC	= EnemyBase
	FSM* m_FSM;                      // _2BC
	EnemyBase* m_sourceEnemy;        // _2C0
	u8 _2C4;                         // _2C4, maybe isHoming?
	f32 _2C8;                        // _2C8
	f32 _2CC;                        // _2CC
	f32 _2D0;                        // _2D0
	f32 _2D4;                        // _2D4
	efx::TRockRun* m_efxRun;         // _2D8
	efx::TRockGrRun* m_efxGroundRun; // _2DC
	efx::TRockWRun* m_efxWaterRun;   // _2E0
	u8 _2E4[0x4];                    // _2E4, unknown
	                                 // _2E8 = PelletView
};

struct Mgr : public EnemyMgrBase {
	Mgr(int, u8);

	virtual ~Mgr();                                     // _58 (weak)
	virtual void createObj(int);                        // _A0
	virtual EnemyBase* getEnemy(int);                   // _A4
	virtual void doAlloc();                             // _A8
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID(); // _AC (weak)

	// _00 		= VTBL
	// _00-_44	= EnemyMgrBase
	Obj* m_obj; // _44, array of Objs
};

struct Parms : public EnemyParmsBase {
	struct ProperParms : public Parameters {
		inline ProperParms(); // likely

		Parm<f32> m_fp01; // _804
	};

	Parms();

	virtual void read(Stream&); // _08 (weak)

	// _00-_7F8	= EnemyParmsBase
	ProperParms m_properParms; // _7F8
};

struct Generator : public EnemyGeneratorBase {
	Generator();

	virtual ~Generator();            // _08 (weak)
	virtual void doWrite(Stream&);   // _10
	virtual void doRead(Stream&);    // _14
	virtual u32 getLatestVersion();  // _18
	virtual void* getInitialParam(); // _20 (weak)

	void doReadLatestVersion(Stream&);
	void doReadOldVersion(Stream&);

	// _00 		= VTBL
	// _00-_1C  = EnemyGeneratorBase
	u8 _20[0x4];  // _20, unknown
	f32 m_speed;  // _24
	f32 m_offset; // _28
	f32 m_scale;  // _2C
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
	ROCK_Wait     = 0,
	ROCK_Appear   = 1,
	ROCK_DropWait = 2,
	ROCK_Fall     = 3,
	ROCK_Move     = 4,
	ROCK_Dead     = 5,
	ROCK_Count    = 6,
};

struct FSM : public EnemyStateMachine {
	virtual void init(EnemyBase*); // _08

	// _00		= VTBL
	// _00-_1C	= EnemyStateMachine
};

struct State : public EnemyFSMState {
	inline State(u16 stateID, const char* name)
	    : EnemyFSMState(stateID)
	{
		m_name = name;
	}

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateAppear : public State {
	inline StateAppear()
	    : State(ROCK_Appear, "appear")
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
	    : State(ROCK_Dead, "dead")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDropWait : public State {
	inline StateDropWait()
	    : State(ROCK_DropWait, "dropwait")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateFall : public State {
	inline StateFall()
	    : State(ROCK_Fall, "fall")
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
	    : State(ROCK_Move, "move")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateWait : public State {
	inline StateWait()
	    : State(ROCK_Wait, "wait")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};
/////////////////////////////////////////////////////////////////
} // namespace Rock
} // namespace Game

#endif
