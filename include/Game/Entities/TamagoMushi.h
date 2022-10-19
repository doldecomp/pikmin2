#ifndef _GAME_ENTITIES_TAMAGOMUSHI_H
#define _GAME_ENTITIES_TAMAGOMUSHI_H

#include "Game/EnemyStateMachine.h"
#include "Game/EnemyAnimatorBase.h"
#include "Game/EnemyParmsBase.h"
#include "Game/EnemyMgrBase.h"
#include "Game/EnemyBase.h"
#include "Collinfo.h"

/**
 * --Header for Mitites (TamagoMushi)--
 */

namespace Game {
namespace TamagoMushi {
struct FSM;

struct Obj : public EnemyBase {
	Obj();

	//////////////// VTABLE
	virtual void onInit(CreatureInitArg*);                   // _30
	virtual void doDirectDraw(Graphics&);                    // _50
	virtual bool isLivingThing();                            // _D4 (weak)
	virtual void bounceCallback(Sys::Triangle*);             // _E8
	virtual void collisionCallback(CollEvent&);              // _EC
	virtual void getShadowParam(ShadowParam&);               // _134
	virtual bool needShadow();                               // _138
	virtual ~Obj();                                          // _1BC (weak)
	virtual void birth(Vector3f&, f32);                      // _1C0
	virtual void setInitialSetting(EnemyInitialParamBase*);  // _1C4 (weak)
	virtual void doUpdate();                                 // _1CC
	virtual void doAnimationCullingOff();                    // _1DC
	virtual void doDebugDraw(Graphics&);                     // _1EC
	virtual void setParameters();                            // _228
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID();      // _258 (weak)
	virtual bool damageCallBack(Creature*, f32, CollPart*);  // _278
	virtual bool pressCallBack(Creature*, f32, CollPart*);   // _27C
	virtual bool hipdropCallBack(Creature*, f32, CollPart*); // _284
	virtual bool earthquakeCallBack(Creature*, f32);         // _28C
	virtual bool bombCallBack(Creature*, Vector3f&, f32);    // _294
	virtual void startCarcassMotion();                       // _2C4
	virtual f32 getDownSmokeScale();                         // _2EC (weak)
	virtual void setFSM(FSM*);                               // _2F8 (weak)
	//////////////// VTABLE END

	void genItem();
	void walkFunc();
	void setGoalRandom();
	void setGoalDirect(Vector3f&);
	bool turnFunc();
	bool isReachToGoal(f32);
	void resetWalkParm();
	void setLeader(Obj*);
	void setTypeBall();
	void appearPanic();
	bool isFound();
	void createFellow();
	void ballMove();
	void createHideEffect();
	void createAppearEffect();

	// _00 		= VTBL
	// _00-_2BC	= EnemyBase
	u8 _2BC[0x8];            // _2BC, unknown
	f32 _2C4;                // _2C4
	f32 _2C8;                // _2C8
	f32 _2CC;                // _2CC
	u8 _2D0[0x10];           // _2D0, unknown
	Vector3f m_goalPosition; // _2E0
	u8 _2EC[0x4];            // _2EC, unknown
	u8 _2F0;                 // _2F0
	Obj* m_leader;           // _2F4
	SysShape::Joint* _2F8;   // _2F8
	f32 _2FC;                // _2FC
	u8 _300;                 // _300, unknown
	u8 _301[0x3];            // _301, unknown/padding
	u8 _304[0x4];            // _304, unknown
	FSM* m_FSM;              // _308
	                         // _30C = PelletView
};

struct Mgr : public EnemyMgrBase {
	Mgr(int objLimit, u8 modelType);

	//////////////// VTABLE
	virtual ~Mgr();                                     // _58 (weak)
	virtual EnemyBase* birth(EnemyBirthArg&);           // _70
	virtual void createObj(int);                        // _A0 (weak)
	virtual EnemyBase* getEnemy(int);                   // _A4 (weak)
	virtual void doAlloc();                             // _A8
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID(); // _AC (weak)
	//////////////// VTABLE END

	void fetch(J3DModel*, f32);
	Obj* createGroup(EnemyBirthArg&, int, Vector3f&);
	Obj* createGroupByBigFoot(EnemyBirthArg&, int, Vector3f&, f32);
	Obj* createGroup(Obj*, int, bool);
	Obj* createGroupByBigFoot(Obj*, int, bool, f32);

	// _00 		= VTBL
	// _00-_44	= EnemyMgrBase
	u32 _44;    // _44, J3DUMtxCacheRef<J3DUMtxAnmCacheTable>* according to Ghidra
	Obj* m_obj; // _48, likely an array of Objs
};

struct Parms : public EnemyParmsBase {
	struct ProperParms : public Parameters {
		inline ProperParms(); // likely

		Parm<f32> m_fp01; // _804
		Parm<f32> m_fp02; // _82C
		Parm<f32> m_fp03; // _854
		Parm<int> m_ip01; // _87C
		Parm<int> m_ip02; // _8A4
		Parm<int> m_ip03; // _8CC
		Parm<int> m_ip04; // _8F4
	};

	Parms();

	virtual void read(Stream&); // _08 (weak)

	// _00-_7F8	= EnemyParmsBase
	ProperParms m_properParms; // _7F8
	u8 _920[0x2C];             // _920, unknown
};

struct ProperAnimator : public EnemyAnimatorBase {
	virtual ~ProperAnimator() { }                                     // _08 (weak)
	virtual void setAnimMgr(SysShape::AnimMgr*);                      // _0C
	virtual SysShape::Animator& getAnimator() { return m_animator; }; // _10 (weak)
	virtual SysShape::Animator& getAnimator(int);                     // _14

	// _00 		= VTBL
	// _00-_10	= EnemyAnimatorBase
	SysShape::Animator m_animator; // _10
};

/////////////////////////////////////////////////////////////////
// STATE MACHINE DEFINITIONS
enum StateID {
	TAMAGOMUSHI_Walk   = 0,
	TAMAGOMUSHI_Turn   = 1,
	TAMAGOMUSHI_Appear = 2,
	TAMAGOMUSHI_Hide   = 3,
	TAMAGOMUSHI_Dead   = 4,
	TAMAGOMUSHI_Wait   = 5,
	TAMAGOMUSHI_Count,
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

struct StateAppear : public State {
	StateAppear(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
	bool _10;          // _10
	int _14;           // _14
	int _18;           // _18
	f32 m_appearFrame; // _1C
	bool _20;          // _20, unknown
};

struct StateDead : public State {
	StateDead(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateHide : public State {
	StateHide(int);

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
	int _10; // _10, unknown
	int _14; // _14, unknown
};

/////////////////////////////////////////////////////////////////
} // namespace TamagoMushi
} // namespace Game

#endif
