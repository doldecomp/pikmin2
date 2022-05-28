#ifndef _GAME_ENEMYBASE_H
#define _GAME_ENEMYBASE_H

#include "BitFlag.h"
#include "Game/AILODParm.h"
#include "Game/CollEvent.h"
#include "Game/Creature.h"
#include "Game/CurrTriInfo.h"
#include "Game/EnemyPelletInfo.h"
#include "Game/EnemyStateMachine.h"
#include "Game/PelletView.h"
#include "Game/PelletMgr.h"
#include "Dolphin/rand.h"
#include "Game/enemyInfo.h"
#include "JAInter/Object.h"
#include "Matrix3f.h"
#include "Sys/Sphere.h"
#include "SysShape/MotionListener.h"
#include "Vector3.h"
#include "efx/TEnemyPiyo.h"
#include "types.h"

struct MouthSlots;

namespace PSM {
struct EnemyBase;
} // namespace PSM

namespace WalkSmokeEffect {
struct Mgr;
} // namespace WalkSmokeEffect

namespace Game {
struct EnemyAnimatorBase;
struct EnemyAnimKeyEvent;
struct EnemyEffectNodeHamon;
struct EnemyInitialParamBase;
struct EnemyMgrBase;

namespace EnemyStone {
struct Obj;
} // namespace EnemyStone

struct EnemyKillArg : public CreatureKillArg {
	/**
	 * @reifiedAddress{80107C38}
	 * @reifiedFile{plugProjectYamashitaU/enemyBase.cpp}
	 */
	virtual const char* getName() // _00
	{
		return "EnemyKillArg";
	}
};

struct EnemyBase : public Creature, public SysShape::MotionListener, virtual public Game::PelletView {
	EnemyBase();

	// vtable 1 (Creature)
	virtual Vector3f getPosition();           // _00
	virtual void checkCollision(CellObject*); // _04
	/**
	 * @reifiedAddress{801028F0}
	 * @reifiedFile{plugProjectYamashitaU/enemyBase.cpp}
	 */
	virtual void getBoundingSphere(Sys::Sphere& sphere) // _08
	{
		sphere = m_boundingSphere;
	}
	virtual bool collisionUpdatable();                          // _0C
	virtual bool isPiki();                                      // _10
	virtual bool isNavi();                                      // _14
	virtual bool deferPikiCollision();                          // _18
	virtual char* getTypeName();                                // _1C
	virtual u16 getObjType();                                   // _20
	virtual void constructor();                                 // _24
	virtual void onInit(CreatureInitArg*);                      // _28
	virtual void onKill(CreatureKillArg*);                      // _2C
	virtual void onInitPost(CreatureInitArg*);                  // _30
	virtual void doAnimation();                                 // _34
	virtual void doEntry();                                     // _38
	virtual void doSetView(int);                                // _3C
	virtual void doViewCalc();                                  // _40
	virtual void doSimulation(float);                           // _44
	virtual void doDirectDraw(Graphics&);                       // _48
	virtual float getBodyRadius();                              // _4C
	virtual float getCellRadius();                              // _50
	virtual void initPosition(Vector3f&);                       // _54
	virtual void onInitPosition(Vector3f&);                     // _58
	virtual float getFaceDir();                                 // _5C
	virtual void setVelocity(Vector3f&);                        // _60
	virtual Vector3f getVelocity();                             // _64
	virtual void onSetPosition(Vector3f&);                      // _68
	virtual void onSetPositionPost(Vector3f&);                  // _6C
	virtual void updateTrMatrix();                              // _70
	virtual bool isTeki();                                      // _74
	virtual bool isPellet();                                    // _78
	virtual void inWaterCallback(WaterBox*);                    // _7C
	virtual void outWaterCallback();                            // _80
	virtual bool inWater();                                     // _84
	virtual u32 getFlockMgr();                                  // _88
	virtual void onStartCapture();                              // _8C
	virtual void onUpdateCapture(Matrixf&);                     // _90
	virtual void onEndCapture();                                // _94
	virtual bool isAtari();                                     // _98
	virtual void setAtari(bool);                                // _9C
	virtual bool isAlive();                                     // _A0
	virtual void setAlive(bool);                                // _A4
	virtual bool isCollisionFlick();                            // _A8
	virtual void setCollisionFlick(bool);                       // _AC
	virtual bool isMovieActor();                                // _B0
	virtual bool isMovieExtra();                                // _B4
	virtual bool isMovieMotion();                               // _B8
	virtual void setMovieMotion(bool);                          // _BC
	virtual bool isBuried();                                    // _C0
	virtual bool isFlying();                                    // _C4
	virtual bool isUnderground();                               // _C8
	virtual bool isLivingThing();                               // _CC
	virtual bool isDebugCollision();                            // _D0
	virtual void setDebugCollision(bool);                       // _D4
	virtual void doSave(Stream&);                               // _D8
	virtual void doLoad(Stream&);                               // _DC
	virtual void bounceCallback(Sys::Triangle*);                // _E0
	virtual void collisionCallback(CollEvent&);                 // _E4
	virtual void platCallback(PlatEvent&);                      // _E8
	virtual JAInter::Object* getJAIObject();                    // _EC
	virtual PSM::Creature* getPSCreature();                     // _F0
	virtual AILOD* getSound_AILOD();                            // _F4
	virtual Vector3f* getSound_PosPtr();                        // _F8
	virtual bool sound_culling();                               // _FC
	virtual float getSound_CurrAnimFrame();                     // _100
	virtual float getSound_CurrAnimSpeed();                     // _104
	virtual void on_movie_begin(bool);                          // _108
	virtual void on_movie_end(bool);                            // _10C
	virtual void movieStartAnimation(unsigned long);            // _110
	virtual void movieStartDemoAnimation(SysShape::AnimInfo*);  // _114
	virtual void movieSetAnimationLastFrame();                  // _118
	virtual void movieSetTranslation(Vector3f&, float);         // _11C
	virtual void movieSetFaceDir(float);                        // _120
	virtual bool movieGotoPosition(Vector3f&);                  // _124
	virtual void movieUserCommand(unsigned long, MoviePlayer*); // _128
	virtual void getShadowParam(ShadowParam&);                  // _12C
	virtual bool needShadow();                                  // _130
	virtual void getLifeGaugeParam(LifeGaugeParam&);            // _134
	virtual void getLODSphere(Sys::Sphere&);                    // _138
	virtual void getLODCylinder(Sys::Cylinder&);                // _13C
	virtual void startPick();                                   // _140
	virtual void endPick(bool);                                 // _144
	virtual u32* getMabiki();                                   // _148
	virtual Footmarks* getFootmarks();                          // _14C
	virtual void onStickStart(Creature*);                       // _150
	virtual void onStickEnd(Creature*);                         // _154
	virtual void onStickStartSelf(Creature*);                   // _158
	virtual void onStickEndSelf(Creature*);                     // _15C
	virtual bool isSlotFree(short);                             // _160
	virtual int getFreeStickSlot();                             // _164
	virtual int getNearFreeStickSlot(Vector3f&);                // _168
	virtual int getRandomFreeStickSlot();                       // _16C
	virtual void onSlotStickStart(Creature*, short);            // _170
	virtual void onSlotStickEnd(Creature*, short);              // _174
	virtual void calcStickSlotGlobal(short, Vector3f&);         // _178
	virtual void getVelocityAt(Vector3f&, Vector3f&);           // _17C
	virtual float getAngularEffect(Vector3f&, Vector3f&);       // _180
	virtual void applyImpulse(Vector3f&, Vector3f&);            // _184
	virtual bool ignoreAtari(Creature*);                        // _188
	virtual Vector3f getSuckPos();                              // _18C
	virtual Vector3f getGoalPos();                              // _190
	virtual bool isSuckReady();                                 // _194
	virtual bool isSuckArriveWait();                            // _198
	virtual bool stimulate(Interaction&);                       // _19C
	virtual char* getCreatureName();                            // _1A0
	virtual s32 getCreatureID();                                // _1A4
	// vtable 2 (MotionListener+self)
	virtual ~EnemyBase();                                           // _004
	virtual void birth(Vector3f&, float);                           // _008
	virtual void SetInitialSetting(EnemyInitialParamBase*) = 0;     // _00C
	virtual void update();                                          // _010
	virtual void doUpdate() = 0;                                    // _014
	virtual void doUpdateCommon();                                  // _018
	virtual void doUpdateCarcass();                                 // _01C
	virtual void doAnimationUpdateAnimator();                       // _020
	virtual void doAnimationCullingOff();                           // _024
	virtual void doAnimationCullingOn();                            // _028
	virtual void doAnimationStick();                                // _02C
	virtual void doSimulationCarcass(float);                        // _030
	virtual void doDebugDraw(Graphics&);                            // _034
	virtual void doSimpleDraw(struct Viewport*);                    // _038
	virtual void doSimulationGround(float);                         // _03C
	virtual void doSimulationFlying(float);                         // _040
	virtual void doSimulationStick(float);                          // _044
	virtual void changeMaterial();                                  // _048
	virtual void getCommonEffectPos(Vector3f&);                     // _04C
	virtual Vector3f* getFitEffectPos();                            // _050
	virtual SysShape::Model* viewGetShape();                        // _054
	virtual void view_start_carrymotion();                          // _058
	virtual void view_finish_carrymotion();                         // _05C
	virtual void viewStartPreCarryMotion();                         // _060
	virtual void viewStartCarryMotion();                            // _064
	virtual void viewOnPelletKilled();                              // _068
	virtual void getOffsetForMapCollision();                        // _06C
	virtual void setParameters();                                   // _070
	virtual void initMouthSlots();                                  // _074
	virtual void initWalkSmokeEffect();                             // _078
	virtual WalkSmokeEffect::Mgr* getWalkSmokeEffectMgr();          // _07C
	virtual void onKeyEvent(const SysShape::KeyEvent&);             // _080
	virtual bool injure();                                          // _084
	virtual void setCollEvent(CollEvent&);                          // _088
	virtual void getEfxHamonPos(Vector3f*);                         // _08C
	virtual void createInstanceEfxHamon();                          // _090
	virtual void updateEfxHamon();                                  // _094
	virtual void createEfxHamon();                                  // _098
	virtual void fadeEfxHamon();                                    // _09C
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID() = 0;         // _0A0
	virtual MouthSlots* getMouthSlots();                            // _0A4
	virtual void doGetLifeGaugeParam(LifeGaugeParam&);              // _0A8
	virtual void throwupItem();                                     // _0AC
	virtual void getThrowupItemPosition(Vector3f*);                 // _0B0
	virtual void getThrowupItemVelocity(Vector3f*);                 // _0B4
	virtual void throwupItemInDeathProcedure();                     // _0B8
	virtual void setLODSphere(Sys::Sphere&);                        // _0BC
	virtual bool damageCallBack(Creature*, float, CollPart*);       // _0C0
	virtual bool pressCallBack(Creature*, float, CollPart*);        // _0C4
	virtual bool flyCollisionCallBack(Creature*, float, CollPart*); // _0C8
	virtual bool hipdropCallBack(Creature*, float, CollPart*);      // _0CC
	virtual bool dropCallBack(Creature*);                           // _0D0
	virtual bool earthquakeCallBack(Creature*, float);              // _0D4
	virtual bool farmCallBack(Creature*, float);                    // _0D8
	virtual bool bombCallBack(Creature*, Vector3f&, float);         // _0DC
	virtual bool eatWhitePikminCallBack(Creature*, float);          // _0E0
	virtual bool dopeCallBack(Creature*, int);                      // _0E4
	virtual bool doDopeCallBack(Creature*, int);                    // _0E8
	virtual void doStartStoneState();                               // _0EC
	virtual void doFinishStoneState();                              // _0F0
	virtual float getDamageCoeStoneState();                         // _0F4
	virtual void doStartEarthquakeState(float);                     // _0F8
	virtual void doFinishEarthquakeState();                         // _0FC
	virtual void doStartEarthquakeFitState();                       // _100
	virtual void doFinishEarthquakeFitState();                      // _104
	virtual void lifeRecover();                                     // _108
	virtual void startCarcassMotion();                              // _10C
	virtual void setCarcassArg(struct PelletViewArg&);              // _110
	virtual float getCarcassArgHeight();                            // _114
	virtual bool doBecomeCarcass();                                 // _118
	virtual void startWaitingBirthTypeDrop();                       // _11C
	virtual void finishWaitingBirthTypeDrop();                      // _120
	virtual bool isFinishableWaitingBirthTypeDrop();                // _124
	virtual void doStartWaitingBirthTypeDrop();                     // _128
	virtual void doFinishWaitingBirthTypeDrop();                    // _12C
	virtual void wallCallback(const struct MoveInfo&);              // _130
	virtual float getDownSmokeScale();                              // _134
	virtual void doStartMovie();                                    // _138
	virtual void doEndMovie();                                      // _13C
	// virtual void _2F0() = 0;                                        // _2F0
	// virtual void _2F4() = 0;                                        // _2F4
	// vtable 3 (PelletView)
	virtual float viewGetBaseScale();                 // _2F8
	virtual int viewGetCollTreeJointIndex();          // _300
	virtual Vector3f viewGetCollTreeOffset();         // _304
	virtual void viewEntryShape(Matrixf&, Vector3f&); // _31C

	void addDamage(float, float);

	void bounceProcedure(Sys::Triangle*);

	void collisionMapAndPlat(float);

	PSM::EnemyBase* createPSEnemyBase();
	void createEffects();
	void createBounceEffect(const Vector3f&, float);
	void createDeadBombEffect();
	void createDropEffect(const Vector3f&, float);
	void createSplashDownEffect(const Vector3f&, float);
	void fadeEffects();

	void doEntryCarcass();
	void doEntryLiving();
	void doSimulationConstraint(float);
	void hardConstraintOn();
	void hardConstraintOff();
	void constraintOff();

	void finishDropping(bool);

	void deathProcedure();
	void gotoHell();

	bool isCullingOff();

	void startMotion();
	void startMotion(int, SysShape::MotionListener*);
	void finishMotion();
	void stopMotion();
	bool isFinishMotion();
	bool isStopMotion();
	float getFirstKeyFrame();
	float getMotionFrame();
	float getMotionFrameMax();
	void setMotionFrame(float);

	int getCurrAnimIndex();
	void setAnimSpeed(float);
	void resetAnimSpeed();

	void setEmotionCaution();
	void setEmotionExcitement();
	void setEmotionNone();

	void setAnimMgr(SysShape::AnimMgr*);
	void setOtakaraCode(PelletMgr::OtakaraItemCode&);
	void setPSEnemyBaseAnime();
	void setZukanVisible(bool);

	void startBlend(int, int, SysShape::BlendFunction*, float, SysShape::MotionListener*);
	void endBlend();

	void show();
	void hide();

	int getStateID();
	bool isBeforeAppearState();
	void startStoneState();

	void scaleDamageAnim();
	void finishScaleDamageAnim();

	void updateSpheres();
	void getWaterSphere(Sys::Sphere*);
	void updateWaterBox();

	void startMovie();
	void endMovie();

	bool isBirthTypeDropGroup();
	bool checkBirthTypeDropEarthquake();
	void setDroppingMassZero();
	void resetDroppingMassZero();

	void resetCollEvent();

	// Creature: _000 - _178
	// MotionListener: _178 - _17C
	// ptr to PelletView: _17C
	EnemyMgrBase* m_mgr;               // _180
	EnemyAnimatorBase* m_animator;     // _184
	EnemyAnimKeyEvent* m_animKeyEvent; // _188
	Vector3f m_position;               // _18C
	Vector3f m_homePosition;           // _198
	Matrix3f _1A4;                     // _1A4
	Vector3f m_velocity;               // _1C8
	Vector3f m_velocity2;              // _1D4
	BitFlag<u32> _1E0[2];              // _1E0
	BitFlag<u32> _1E8[2];              // _1E8
	u8 m_emotion;                      // _1F0
	u8 m_enemyIndexForType;            // _1F1
	u8 _1F2;                           // _1F2
	u8 m_inZukan;                      // _1F3
	int m_stickPikminCount;            // _1F4
	float m_scaleModifier;             // _1F8
	float m_faceDir;                   // _1FC
	float m_health;                    // _200
	float m_maxHealth;                 // _204
	float m_instantDamage;             // _208
	float m_toFlick;                   // _20C
	float _210;                        // _210
	// TODO: Name is from PikDecomp. Sodium called this "purpleStunTimer". Which
	// name is more accurate?
	float m_scaleTimer;                          // _214
	float m_friction;                            // _218
	float m_stoneTimer;                          // _21C
	Sys::Sphere m_boundingSphere;                // _220
	Creature* m_targetCreature;                  // _230
	CollEvent m_collEvent;                       // _234
	Vector3f m_commonEffectOffset;               // _240
	EnemyStone::Obj* m_enemyStoneObj;            // _24C
	PelletMgr::OtakaraItemCode m_pelletDropCode; // _250
	Pellet* m_heldPellet;                        // _254
	EnemyPelletInfo m_pelletInfo;                // _258
	AILODParm m_lodParm;                         // _264
	Sys::Sphere m_lodRange;                      // _270
	WaterBox* m_waterBox;                        // _280
	EnemyEffectNodeHamon* m_effectNodeHamon;     // _284
	u32 _288;                                    // _288
	PSM::EnemyBase* m_soundObj;                  // _28C
	CNode m_effectNodeHamonRoot;                 // _290
	float _2A8;                                  // _2A8
	float _2AC;                                  // _2AC
	u8 m_dropGroup;                              // _2B0
	EnemyFSMState* m_currentLifecycleState;      // _2B4
	EnemyStateMachine* m_lifecycleFSM;           // _2B8
	                                             // PelletView: _2BC - _2C8
};
namespace EnemyBaseFSM {
enum StateID {
	EBS_Drop = 0,
	EBS_DropPikmin,
	EBS_DropOlimar,
	EBS_DropTreasure,
	EBS_DropEarthquake,
	EBS_Appear,
	EBS_Living,
	EBS_Stone,
	EBS_Earthquake,
	EBS_Fit
};
/**
 * Generic lifecycle FSM that every teki has, often in addition to a more
 * specific FSM derived from Game::StateMachine.
 */
struct StateMachine : public Game::EnemyStateMachine {
	virtual void init(EnemyBase*);                            // _00
	virtual EnemyFSMState* getCurrState(EnemyBase*);          // _14
	virtual void setCurrState(EnemyBase*, EnemyFSMState*);    // _18
	virtual void update(EnemyBase*);                          // _1C
	virtual void entry(EnemyBase*);                           // _20
	virtual void simulation(EnemyBase*, float);               // _24
	virtual void animation(EnemyBase*);                       // _28
	virtual void bounceProcedure(EnemyBase*, Sys::Triangle*); // _2C
};

/**
 * Generic lifecycle state.
 */
struct State : public Game::EnemyFSMState {
	inline State(int stateID, const char* name)
	    : EnemyFSMState(stateID, name)
	{
	}

	virtual void update(EnemyBase*);                          // _1C
	virtual void entry(EnemyBase*);                           // _20
	virtual void simulation(EnemyBase*, float);               // _24
	virtual void bounceProcedure(EnemyBase*, Sys::Triangle*); // _28
	virtual void animation(EnemyBase*);                       // _2C

	// _00 VTBL
};

/**
 * Generic birth-by-dropping state.
 */
struct BirthTypeDropState : public State {
	inline BirthTypeDropState(int stateID = EBS_Drop)
	    : State(EBS_Drop, "BirthTypeDrop")
	{
	}

	virtual void init(EnemyBase*, StateArg*);   // _00
	virtual void cleanup(EnemyBase*);           // _08
	virtual void update(EnemyBase*);            // _1C
	virtual void entry(EnemyBase*);             // _20
	virtual void simulation(EnemyBase*, float); // _24
	virtual void animation(EnemyBase*);         // _2C

	virtual bool isFinishableWaitingBirthTypeDrop(EnemyBase*); // _30
};

struct BirthTypeDropPikminState : public BirthTypeDropState {
	inline BirthTypeDropPikminState()
	    : BirthTypeDropState(EBS_DropPikmin)
	{
		m_name = "BirthTypeDropPikmin";
	}

	virtual bool isFinishableWaitingBirthTypeDrop(EnemyBase*); // _30
};

struct BirthTypeDropOlimarState : public BirthTypeDropState {
	inline BirthTypeDropOlimarState()
	    : BirthTypeDropState(EBS_DropOlimar)
	{
		m_name = "BirthTypeDropOlimar";
	}

	virtual bool isFinishableWaitingBirthTypeDrop(EnemyBase*); // _30
};

struct BirthTypeDropTreasureState : public BirthTypeDropState {
	inline BirthTypeDropTreasureState()
	    : BirthTypeDropState(EBS_DropTreasure)
	{
		m_name = "BirthTypeDropTreasure";
	}

	virtual bool isFinishableWaitingBirthTypeDrop(EnemyBase*); // _30
};

struct BirthTypeDropEarthquakeState : public BirthTypeDropState {
	inline BirthTypeDropEarthquakeState()
	    : BirthTypeDropState(EBS_DropEarthquake)
	{
		m_name = "BirthTypeDropEarthquake";
	}

	virtual bool isFinishableWaitingBirthTypeDrop(EnemyBase*); // _30
};

/**
 * Birth-without-dropping state?
 */
struct AppearState : public State {
	inline AppearState()
	    : State(EBS_Appear, "Appear")
	{
	}

	virtual void init(EnemyBase*, StateArg*);   // _00
	virtual void cleanup(EnemyBase*);           // _08
	virtual void update(EnemyBase*);            // _1C
	virtual void entry(EnemyBase*);             // _20
	virtual void simulation(EnemyBase*, float); // _24
};

/**
 * Generic "alive" state.
 */
struct LivingState : public State {
	inline LivingState(int state = EBS_Living)
	    : State(state, "Living")
	{
	}

	virtual void simulation(EnemyBase*, float); // _24
	virtual void update(EnemyBase*);            // _1C
	virtual void entry(EnemyBase*);             // _20
	virtual void updateCullingOff(EnemyBase*);  // _30
	virtual void updateAlways(EnemyBase*);      // _34
};

struct StoneState : public LivingState {
	inline StoneState()
	    : LivingState(EBS_Stone)
	{
		m_name = "Stone";
	}

	virtual void init(EnemyBase*, StateArg*);                 // _00
	virtual void cleanup(EnemyBase*);                         // _08
	virtual void bounceProcedure(EnemyBase*, Sys::Triangle*); // _28
	virtual void updateCullingOff(EnemyBase*);                // _30
	virtual void updateAlways(EnemyBase*);                    // _34
};

struct EarthquakeState : public LivingState {
	inline EarthquakeState()
	    : LivingState(EBS_Earthquake)
	{
		m_name = "Earthquake";
	}

	virtual void init(EnemyBase*, StateArg*);  // _00
	virtual void cleanup(EnemyBase*);          // _08
	virtual void updateCullingOff(EnemyBase*); // _30
};

struct FitState : public LivingState {
	inline FitState()
	    : LivingState(EBS_Fit)
	    , m_enemyPiyo()
	{
		m_name = "Fit";
	}

	virtual void init(EnemyBase*, StateArg*);  // _00
	virtual void cleanup(EnemyBase*);          // _08
	virtual void updateCullingOff(EnemyBase*); // _30
	virtual void updateAlways(EnemyBase*);     // _34

	efx::TEnemyPiyo m_enemyPiyo; // _10
};
} // namespace EnemyBaseFSM
} // namespace Game

#endif
