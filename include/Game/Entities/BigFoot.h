#ifndef _GAME_ENTITIES_BIGFOOT_H
#define _GAME_ENTITIES_BIGFOOT_H

#include "Game/EnemyStateMachine.h"
#include "Game/EnemyAnimatorBase.h"
#include "Game/EnemyParmsBase.h"
#include "Game/EnemyMgrBase.h"
#include "Game/JointFuncs.h"
#include "Game/EnemyBase.h"
#include "Sys/MatBaseAnimation.h"
#include "Sys/MatBaseAnimator.h"
#include "efx/TOdama.h"
#include "efx/TDama.h"
#include "Collinfo.h"

/**
 * --Header for Raging Long Legs (BigFoot)--
 */

namespace Game {
struct IKSystemMgr;
struct IKSystemParms;

namespace BigFoot {
struct BigFootGroundCallBack;
struct BigFootShadowMgr;
struct FSM;

enum StateID {
	BIGFOOT_NULL  = -1,
	BIGFOOT_Dead  = 0,
	BIGFOOT_Stay  = 1,
	BIGFOOT_Land  = 2,
	BIGFOOT_Wait  = 3,
	BIGFOOT_Flick = 4,
	BIGFOOT_Walk  = 5,
	BIGFOOT_Count,
};

struct Obj : public EnemyBase {
	Obj();

	//////////////// VTABLE
	virtual void onInit(CreatureInitArg* settings);         // _30
	virtual void onKill(CreatureKillArg* settings);         // _34
	virtual void doDirectDraw(Graphics& gfx);               // _50
	virtual void collisionCallback(CollEvent& event);       // _EC
	virtual void getShadowParam(ShadowParam& settings);     // _134
	virtual bool needShadow();                              // _138
	virtual ~Obj() {};                                      // _1BC (weak)
	virtual void setInitialSetting(EnemyInitialParamBase*); // _1C4
	virtual void doUpdate();                                // _1CC
	virtual void doUpdateCommon();                          // _1D0
	virtual void doAnimationCullingOff();                   // _1DC
	virtual void doDebugDraw(Graphics&);                    // _1EC
	virtual void getThrowupItemPosition(Vector3f*);         // _268
	virtual void getThrowupItemVelocity(Vector3f*);         // _26C
	virtual bool damageCallBack(Creature*, f32, CollPart*); // _278
	virtual void doStartStoneState();                       // _2A4
	virtual void doFinishStoneState();                      // _2A8
	virtual void doStartMovie();                            // _2F0
	virtual void doEndMovie();                              // _2F4
	virtual void setFSM(FSM*);                              // _2F8
	virtual void inWaterCallback(WaterBox* wb) { }          // _84 (weak)
	virtual void outWaterCallback() { }                     // _88 (weak)
	virtual f32 getDamageCoeStoneState() { return 0.25f; }  // _2AC (weak)
	virtual void throwupItemInDeathProcedure() { }          // _270 (weak)
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID()      // _258 (weak)
	{
		return EnemyTypeID::EnemyID_BigFoot;
	}
	//////////////// VTABLE END

	void resetFlickWalkTimeMax();
	void setFlickWalkTimeMax();
	void getTargetPosition();
	void createIKSystem();
	void setupIKSystem();
	void setIKParameter();
	void setIKSystemTargetPosition(Vector3f&);
	void updateIKSystem();
	void doAnimationIKSystem();
	void finishAnimationIKSystem();
	void startProgramedIK();
	void startIKMotion();
	void finishIKMotion();
	void forceFinishIKMotion();
	bool isFinishIKMotion();
	void startBlendMotion();
	void finishBlendMotion();
	Vector3f getTraceCentrePosition();
	bool isCollisionCheck(CollPart*);
	void createShadowSystem();
	void setupShadowSystem();
	void doAnimationShadowSystem();
	void createMaterialAnimation();
	void startMaterialAnimation();
	void updateMaterialAnimation();
	void setupCollision();
	void createItemAndEnemy();
	void startBossChargeBGM();
	void startBossAttackLoopBGM();
	void finishBossAttackLoopBGM();
	void startStoneStateBossAttackLoopBGM();
	void finishStoneStateBossAttackLoopBGM();
	void updateBossBGM();
	void resetBossAppearBGM();
	void setBossAppearBGM();
	void createEffect();
	void setupEffect();
	void createOnGroundEffect(int, WaterBox*);
	void createOffGroundEffect(int, WaterBox*);
	void startPinchJointEffect();
	void finishPinchJointEffect();
	void startDeadEffect();
	void updatePinchLife();
	void startFurEffect();
	void finishFurEffect();
	void updateDeadFurEffect();
	void effectDrawOn();
	void effectDrawOff();
	void addShadowScale();

	// _00 		= VTBL
	// _00-_2BC	= EnemyBase
	FSM* mFsm;                                  // _2BC
	f32 mStateTimer;                            // _2C0
	StateID mNextState;                         // _2C4
	Vector3f mTargetPosition;                   // _2C8
	f32 mShadowScale;                           // _2D4
	f32 mFlickWalkTimeMax;                      // _2D8
	bool _2DC;                                  // _2DC
	bool mIsSmoking;                            // _2DD
	bool mIsEnraged;                            // _2DE, next walk cycle will be fast
	IKSystemMgr* mIkSystemMgr;                  // _2E0
	IKSystemParms* mIkSystemParms;              // _2E4
	BigFootGroundCallBack* mGroundCallBack;     // _2E8
	BigFootShadowMgr* mShadowMgr;               // _2EC
	Vector3f mJointPositions[4][4];             // _2F0
	efx::TOdamaFoot* mFootFX[4];                // _3B0, stepping on ground
	efx::TDamaFootw* mFootWFX[4];               // _3C0, stepping in water
	efx::TDamaSmoke* mSmokeFX[3];               // _3D0, smoke
	efx::TOdamaHahen* mHahenFX[4][3];           // _3DC, shards
	efx::TDamaDeadElecA* mDeadElecAFX[4][3];    // _40C, death electricity A
	efx::TDamaDeadElecB* mDeadElecBFX[4][2];    // _43C, death electricity B
	efx::TOdamaDeadHahenA* mDeadHahenAFX[4][2]; // _45C, death shards A
	efx::TOdamaDeadHahenB* mDeadHahenBFX[4];    // _47C, death shards B
	efx::TOdamaDeadHahenC1* mDeadHahenC1FX;     // _48C, death shards C1
	efx::TOdamaDeadHahenC2* mDeadHahenC2FX;     // _490, death shards C2
	efx::TOdamaFur1* mBodyHairFX;               // _494
	efx::TOdamaFur2* mLegHairFX[4];             // _498
	Sys::MatLoopAnimator* mMatLoopAnimator;     // _4A8
	                                            // _4AC = PelletView
};

struct Mgr : public EnemyMgrBase {
	Mgr(int objLimit, u8 modelType);

	//////////////// VTABLE
	// virtual ~Mgr() {};                              // _58 (weak)
	virtual void createObj(int);                       // _A0
	virtual EnemyBase* getEnemy(int idx);              // _A4
	virtual void doAlloc();                            // _A8
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID() // _AC (weak)
	{
		return EnemyTypeID::EnemyID_BigFoot;
	}
	virtual SysShape::Model* createModel();         // _B0
	virtual void loadModelData();                   // _C8
	virtual void loadTexData();                     // _D0
	virtual J3DModelData* doLoadBmd(void* filename) // _D4 (weak)
	{
		return J3DModelLoaderDataBase::load(filename, 0x21240030);
	}
	//////////////// VTABLE END

	// _00 		= VTBL
	// _00-_44	= EnemyMgrBase
	Sys::MatTevRegAnimation* mTevRegAnimation; // _44
	Obj* mObj;                                 // _48
};

struct Parms : public EnemyParmsBase {
	struct ProperParms : public Parameters {
		inline ProperParms()
		    : Parameters(nullptr, "EnemyParmsBase")
		    , mBaseCoefficient(this, 'fp01', "�x�[�X�W��", 3.0f, 0.0f, 10.0f)        // 'base factor'
		    , mRaiseSlowdownFactor(this, 'fp02', "�グ�����W��", -0.2f, -5.0f, 5.0f) // 'raising deceleration factor'
		    , mDownwardAccelFactor(this, 'fp03', "���������W��", 0.5f, -5.0f, 5.0f)  // 'downward acceleration factor'
		    , mMinDecelFactor(this, 'fp04', "�Œጸ�����W��", -2.5f, -10.0f,
		                      10.0f) // 'minimum deceleration acceleration factor'
		    , mMaxDecelFactor(this, 'fp05', "�ō��������W��", 10.0f, -10.0f,
		                      10.0f)                                              // 'maximum deceleration acceleration factor'
		    , mLegSwing(this, 'fp06', "���̐U��グ", 120.0f, 0.0f, 200.0f)       // 'leg swing'
		    , mBaseCoefficients(this, 'fp11', "�x�[�X�W��(s)", 3.0f, 0.0f, 10.0f) // 'base factor(s)'
		    , mFp12(this, 'fp12', "�グ�����W��(s)", -0.2f, -5.0f, 5.0f)          // 'raising deceleration factor(s)'
		    , mFp13(this, 'fp13', "���������W��(s)", 0.5f, -5.0f, 5.0f)           // 'downward acceleration factor(s)'
		    , mFp14(this, 'fp14', "�Œጸ�����W��(s)", -2.0f, -10.0f,
		            10.0f) // 'minimum deceleration acceleration factor(s)'
		    , mFp15(this, 'fp15', "�ō��������W��(s)", 10.0f, -10.0f,
		            10.0f)                                                             // 'maximum deceleration acceleration factor(s)'
		    , mFp16(this, 'fp16', "���̐U��グ(s)", 120.0f, 0.0f, 200.0f)             // 'leg swing(s)'
		    , mMovementOffset(this, 'fp17', "�ړ��I�t�Z�b�g(s)", 50.0f, 0.0f, 200.0f)  // 'movement offset(s)'
		    , mNormalTravelTime(this, 'fp20', "�ʏ�ړ�����", 10.0f, 0.0f, 100.0f)     // 'normal travel time'
		    , mPostShakeTravelTime(this, 'fp21', "�U����ړ�����", 3.0f, 0.0f, 100.0f) // 'post-shakeoff travel time'
		{
		}

		Parm<f32> mBaseCoefficient;     // _804, fp01
		Parm<f32> mRaiseSlowdownFactor; // _82C, fp02
		Parm<f32> mDownwardAccelFactor; // _854, fp03
		Parm<f32> mMinDecelFactor;      // _87C, fp04
		Parm<f32> mMaxDecelFactor;      // _8A4, fp05
		Parm<f32> mLegSwing;            // _8CC, fp06
		Parm<f32> mBaseCoefficients;    // _8F4, fp11
		Parm<f32> mFp12;                // _91C
		Parm<f32> mFp13;                // _944
		Parm<f32> mFp14;                // _96C
		Parm<f32> mFp15;                // _994
		Parm<f32> mFp16;                // _9BC
		Parm<f32> mMovementOffset;      // _9E4, fp17
		Parm<f32> mNormalTravelTime;    // _A0C, fp20
		Parm<f32> mPostShakeTravelTime; // _A34, fp21
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
	virtual ~ProperAnimator() {};                                    // _08 (weak)
	virtual void setAnimMgr(SysShape::AnimMgr* mgr);                 // _0C
	virtual SysShape::Animator& getAnimator() { return mAnimator; }; // _10 (weak)
	virtual SysShape::Animator& getAnimator(int idx);                // _14

	// _00 		= VTBL
	// _00-_10	= EnemyAnimatorBase
	SysShape::Animator mAnimator; // _10
};

struct BigFootShadowMgr {
	BigFootShadowMgr(Obj*);

	void init();
	void setJointPosPtr(int, int, Vector3f*);
	void update();

	Matrixf* mMatrix;                        // _00
	Obj* mObj;                               // _04
	Vector3f* mJointPosPtrs[4][4];           // _08
	JointShadowRootNode* mRootNode;          // _48
	SphereShadowNode* mBodySphereShadow;     // _4C
	TubeShadowTransNode* mLegTubeShadow1[4]; // _50, rhand=0, lhand=1, rfoot=2, lfoot=3
	TubeShadowSetNode* mLegTubeShadow2[4];   // _60, rhand=0, lhand=1, rfoot=2, lfoot=3
	TubeShadowSetNode* mLegTubeShadow3[4];   // _70, rhand=0, lhand=1, rfoot=2, lfoot=3
	SphereShadowNode* mLegSphereShadow1[4];  // _80, rhand=0, lhand=1, rfoot=2, lfoot=3
	SphereShadowNode* mLegSphereShadow2[4];  // _90, rhand=0, lhand=1, rfoot=2, lfoot=3
	SphereShadowNode* mLegSphereShadow3[4];  // _A0, rhand=0, lhand=1, rfoot=2, lfoot=3
};

struct BigFootGroundCallBack : public JointGroundCallBack {
	inline BigFootGroundCallBack(Obj* obj)
	    : mObj(obj)
	{
	}

	virtual void invokeOnGround(int, WaterBox*);  // _08
	virtual void invokeOffGround(int, WaterBox*); // _0C

	// _00	= VTBL
	Obj* mObj; // _04
};

/////////////////////////////////////////////////////////////////
// STATE MACHINE DEFINITIONS
struct FSM : public EnemyStateMachine {
	virtual void init(EnemyBase*); // _08

	// _00		= VTBL
	// _00-_1C	= EnemyStateMachine
};

struct State : public EnemyFSMState {
	inline State(u16 stateID, const char* name)
	    : EnemyFSMState(stateID)
	{
		mName = name;
	}

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDead : public State {
	inline StateDead()
	    : State(BIGFOOT_Dead, "dead")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateFlick : public State {
	inline StateFlick()
	    : State(BIGFOOT_Flick, "flick")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateLand : public State {
	inline StateLand()
	    : State(BIGFOOT_Land, "land")
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
	    : State(BIGFOOT_Stay, "stay")
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
	    : State(BIGFOOT_Wait, "wait")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateWalk : public State {
	inline StateWalk()
	    : State(BIGFOOT_Walk, "walk")
	{
	}

	virtual void init(EnemyBase*, StateArg*); // _08
	virtual void exec(EnemyBase*);            // _0C
	virtual void cleanup(EnemyBase*);         // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};
/////////////////////////////////////////////////////////////////
} // namespace BigFoot
} // namespace Game

#endif
