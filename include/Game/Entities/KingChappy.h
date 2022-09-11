#ifndef _GAME_ENTITIES_KINGCHAPPY_H
#define _GAME_ENTITIES_KINGCHAPPY_H

#include "Game/EnemyStateMachine.h"
#include "Game/EnemyAnimatorBase.h"
#include "Game/EnemyParmsBase.h"
#include "Game/EnemyMgrBase.h"
#include "Game/JointFuncs.h"
#include "Game/EnemyBase.h"
#include "Game/WalkSmokeEffect.h"
#include "SysShape/Joint.h"
#include "Collinfo.h"

/**
 * --Header for Emperor Bulblax (KingChappy)--
 */

namespace efx {
struct TKchYodare;
struct TKchDiveSand;
struct TKchDiveWat;
struct TKchCryAB;
struct TKchCryInd;
struct TKchSmokeHana;
struct TKchAttackYodare;
struct TKchDeadYodare;
struct TKchDeadHana;
struct TEnemyHamonChasePos;
} // namespace efx

namespace Game {
namespace KingChappy {
struct FSM;

struct Obj : public EnemyBase {
	Obj();

	//////////////// VTABLE
	virtual void onInit(CreatureInitArg*);                  // _30
	virtual void onKill(CreatureKillArg*);                  // _34
	virtual void doSimulation(f32);                         // _4C
	virtual void doDirectDraw(Graphics&);                   // _50
	virtual f32 getBodyRadius();                            // _54 (weak)
	virtual f32 getCellRadius();                            // _58 (weak)
	virtual void inWaterCallback(WaterBox*);                // _84
	virtual bool isUnderground();                           // _D0 (weak)
	virtual void collisionCallback(CollEvent&);             // _EC
	virtual void getShadowParam(ShadowParam&);              // _134
	virtual void applyImpulse(Vector3f&, Vector3f&);        // _18C (weak)
	virtual ~Obj();                                         // _1BC (weak)
	virtual void birth(Vector3f&, f32);                     // _1C0
	virtual void setInitialSetting(EnemyInitialParamBase*); // _1C4 (weak)
	virtual void doUpdate();                                // _1CC
	virtual void doAnimationUpdateAnimator();               // _1D8
	virtual void doAnimationCullingOff();                   // _1DC
	virtual void doDebugDraw(Graphics&);                    // _1EC
	virtual void setParameters();                           // _228
	virtual void initMouthSlots();                          // _22C
	virtual void initWalkSmokeEffect();                     // _230
	virtual WalkSmokeEffect::Mgr* getWalkSmokeEffectMgr();  // _234
	virtual void updateEfxHamon();                          // _24C (weak)
	virtual void createEfxHamon();                          // _250 (weak)
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID();     // _258 (weak)
	virtual MouthSlots* getMouthSlots();                    // _25C (weak)
	virtual bool damageCallBack(Creature*, f32, CollPart*); // _278
	virtual bool pressCallBack(Creature*, f32, CollPart*);  // _27C (weak)
	virtual bool bombCallBack(Creature*, Vector3f&, f32);   // _294
	virtual bool eatWhitePikminCallBack(Creature*, f32);    // _298 (weak)
	virtual void doStartStoneState();                       // _2A4
	virtual void doFinishStoneState();                      // _2A8
	virtual void startCarcassMotion();                      // _2C4
	virtual void wallCallback(const MoveInfo&);             // _2E8
	virtual f32 getDownSmokeScale();                        // _2EC (weak)
	virtual void doStartMovie();                            // _2F0
	virtual void doEndMovie();                              // _2F4
	virtual void setFSM(FSM*);                              // _2F8 (weak)
	//////////////// VTABLE END

	void eatBomb();
	void getPikminInMouth(bool);
	void getTonguePosVel(Vector3f&, Vector3f&);
	void setNextGoal();
	void searchTarget();
	void isOutOfTerritory(f32);
	void forceTransit(int);
	void requestTransit(int);
	void walkFunc();
	void turnFunc(f32);
	void isReachToGoal(f32);
	void checkAttack(bool);
	void checkFlick(bool);
	void checkDead(bool);
	void checkTurn(bool);
	void startMotionSelf(int, SysShape::MotionListener*);
	void endBlendAnimation();
	void leftFootMtxCalc();
	void rightFootMtxCalc();
	void footMtxCalc(f32 (*)[4], Vector3f*, f32*);
	void resetFootPos();
	void fadeAllEffect();
	void createEffect(int);
	void fadeEffect(int);
	void createBounceEffect();

	// _00 		= VTBL
	// _00-_2BC	= EnemyBase
	Vector3f _2BC;                       // _2BC
	MouthSlots m_mouthSlots;             // _2C8
	SysShape::Joint* _2D0;               // _2D0
	SysShape::Joint* _2D4;               // _2D4
	SysShape::Joint* _2D8;               // _2D8
	SysShape::Joint* _2DC;               // _2DC
	SysShape::Joint* _2E0;               // _2E0
	u8 _2E4[0x8];                        // _2E4, unknown
	u8 _2EC;                             // _2EC, unknown
	int _2F0;                            // _2F0
	Vector3f _2F4;                       // _2F4
	u8 _300[0xC];                        // _300, unknown
	int _30C;                            // _30C
	s16 _310;                            // _310, specific joint index?
	u8 _312[0x2];                        // _312, padding probably
	u8 _314[0x10];                       // _314, unknown
	s16 _324;                            // _324, right foot joint index?
	Vector3f _328;                       // _328
	u8 _334[0x4];                        // _334, unknown
	u8 _338;                             // _338
	u8 _339[0x3];                        // _339, padding probably
	u8 _33C[0x4];                        // _33C, unknown
	void* _340;                          // _340, code? unknown
	WalkSmokeEffect::Mgr m_walkSmokeMgr; // _344
	FSM* m_FSM;                          // _34C
	efx::TKchYodare* m_efxYodare;        // _350
	efx::TKchDiveSand* m_efxDiveSand;    // _354
	efx::TKchDiveWat* m_efxDiveWater;    // _358
	efx::TKchCryAB* m_efxCryAB;          // _35C
	efx::TKchCryInd* m_efxCryInd;        // _360
	efx::TKchSmokeHana* m_efxSmoke;      // _364
	efx::TKchAttackYodare* m_efxAttack;  // _368
	efx::TKchDeadYodare* _36C;           // _36C
	efx::TKchDeadHana* _370;             // _370
	efx::TEnemyHamonChasePos* _374;      // _374
	efx::TEnemyHamonChasePos* _378;      // _378
	Vector3f _37C;                       // _37C
	Vector3f _388;                       // _388
	u8 _394;                             // _394
	                                     // _398 = PelletView
};

struct Mgr : public EnemyMgrBase {
	Mgr(int, u8);

	//////////////// VTABLE
	virtual ~Mgr();                                     // _58 (weak)
	virtual EnemyBase* birth(EnemyBirthArg&);           // _70
	virtual void createObj(int);                        // _A0 (weak)
	virtual EnemyBase* getEnemy(int);                   // _A4 (weak)
	virtual void doAlloc();                             // _A8
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID(); // _AC (weak)
	virtual SysShape::Model* createModel();             // _B0
	//////////////// VTABLE END

	// _00 		= VTBL
	// _00-_44	= EnemyMgrBase
	Obj* m_obj; // _44
};

struct Parms : public EnemyParmsBase {
	struct ProperParms : public Parameters {
		ProperParms(); // (weak)

		Parm<f32> m_fp01; // _804
		Parm<f32> m_fp02; // _82C
		Parm<f32> m_fp03; // _854
		Parm<f32> m_fp04; // _87C
		Parm<f32> m_fp05; // _8A4
		Parm<f32> m_fp06; // _8CC
		Parm<f32> m_fp07; // _8F4
		Parm<f32> m_fp08; // _91C
		Parm<f32> m_fp09; // _944
		Parm<f32> m_fp10; // _96C
		Parm<f32> m_fp11; // _994
		Parm<f32> m_fp12; // _9BC
		Parm<f32> m_fp13; // _9E4
		Parm<f32> m_fp14; // _A0C
		Parm<f32> m_fp15; // _A34
		Parm<f32> m_fp16; // _A5C
		Parm<f32> m_fp17; // _A84
		Parm<f32> m_fp18; // _AAC
		Parm<f32> m_fp19; // _AD4
		Parm<f32> m_fp20; // _AFC
		Parm<f32> m_fp21; // _B24
		Parm<int> m_ip01; // _B4C
		Parm<int> m_ip02; // _B74
		Parm<int> m_ip03; // _B9C
	};

	Parms();

	virtual void read(Stream&); // _08 (weak)

	// _00-_7F8	= EnemyParmsBase
	ProperParms m_properParms; // _7F8
	u8 _BC8;                   // _BC8
	u8 _BC9;                   // _BC9
	u8 _BCA;                   // _BCA
	u8 _BCB;                   // _BCB
	u8 _BCC;                   // _BCC
	f32 _BD0;                  // _BD0
};

struct ProperAnimator : public EnemyBlendAnimatorBase {
	virtual ~ProperAnimator(); // _08 (weak)

	// _00      = VTBL
	// _00-_60  = EnemyBlendAnimatorBase
	SysShape::Animator m_specificAnimator;
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

struct StateAppear : public State {
	StateAppear(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

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

struct StateCaution : public State {
	StateCaution(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDamage : public State {
	StateDamage(int);

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

struct StateEat : public State {
	StateEat(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateFlick : public State {
	StateFlick(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateHide : public State {
	StateHide(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateHideWait : public State {
	StateHideWait(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateSwallow : public State {
	StateSwallow(int);

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

struct StateWalk : public State {
	StateWalk(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateWarCry : public State {
	StateWarCry(int);

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};
/////////////////////////////////////////////////////////////////
} // namespace KingChappy
} // namespace Game

#endif
