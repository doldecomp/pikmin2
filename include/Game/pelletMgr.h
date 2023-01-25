#ifndef _GAME_PELLETMGR_H
#define _GAME_PELLETMGR_H

#include "CarryInfo.h"
#include "Game/DynCreature.h"
#include "ObjectMgr.h"
#include "GenericObjectMgr.h"
#include "Game/Interaction.h"
#include "Game/PelletCarry.h"
#include "Game/pelletConfig.h"
#include "Game/StateMachine.h"
#include "Game/BasePelletMgr.h"
#include "Game/GameSystem.h"
#include "efx/TOrima.h"
#include "SysShape/MotionListener.h"
#include "SysShape/KeyEvent.h"
#include "SysShape/Animator.h"
#include "SysShape/Joint.h"
#include "Sys/Sphere.h"
#include "Sys/Triangle.h"
#include "CarryInfo.h"
#include "TexCaster.h"
#include "Vector3.h"
#include "Matrixf.h"
#include "types.h"
#include "JSystem/JUT/JUTException.h"
#include "JSystem/J3D/J3DMtxCalc.h"
#include "System.h"
#include "Iterator.h"

// pellet carry colors/onion destinations
// for use with Pellet::mPelletColor
#define PELCOLOR_BLUE   (0)
#define PELCOLOR_RED    (1)
#define PELCOLOR_YELLOW (2)
#define PELCOLOR_RANDOM (3)

// pellet types
// for use with Pellet:mPelletType and getKind()
#define PELTYPE_NUMBER   (0)
#define PELTYPE_CARCASS  (1)
#define PELTYPE_BERRY    (2)
#define PELTYPE_TREASURE (3)
#define PELTYPE_UPGRADE  (4)

namespace PSM {
struct EventBase;
} // namespace PSM

namespace Game {
struct BasePelletMgr;
struct Pellet;
struct PelletInitArg;
struct PelletView;
struct PelletFSM;
struct PathNode;
struct PelletState;
struct Onyon;

struct PelletMgr : public NodeObjectMgr<GenericObjectMgr> {
	struct OtakaraItemCode {
		OtakaraItemCode(s16 v = 0)
		    : mValue(v)
		{
		}

		operator s16() { return mValue; }

		bool isNull();
		void read(Stream&);
		void write(Stream&);

		s16 mValue; // _00
	};

	PelletMgr();

	// vtable 1
	virtual ~PelletMgr() { }                    // _08 (weak)
	virtual void doAnimation();                 // _64 (weak)
	virtual void doEntry();                     // _68 (weak)
	virtual void doSetView(int viewportNumber); // _6C (weak)
	virtual void doViewCalc();                  // _70 (weak)
	virtual void doSimulation(f32 rate);        // _74 (weak)
	virtual void doDirectDraw(Graphics& gfx);   // _78 (weak)
	virtual char* getMgrName()                  // _80 (weak)
	{
		return "�y���b�g�}�l�[�W��"; // pellet manager
	}
	virtual char* getCaveName(int);       // _84
	virtual int getCaveID(char*);         // _88
	virtual void doSimpleDraw(Viewport*); // _8C (weak)

	void setMovieDraw(bool);

	void createManagers(u32);
	void resetMgrs();
	void setupResources();
	Pellet* birth(PelletInitArg*);
	bool setUse(PelletInitArg*);
	bool makePelletInitArg(PelletInitArg&, char*);
	void makeVsCarryMinMax(PelletInitArg&, char*);
	bool makePelletInitArg(PelletInitArg&, PelletMgr::OtakaraItemCode&);
	void makeOtakaraItemCode(char*, PelletMgr::OtakaraItemCode&);
	void addMgr(BasePelletMgr*);
	void setupSoundViewerAndBas();
	void decode(long, u8&, int&);
	int encode(u8, int);
	BasePelletMgr* getMgrByID(u8);

	static bool mDebug;
	static bool disableDynamics;

	bool mMovieDrawDisabled; // _3C, setMovieDraw sets this to !input
};

struct PelletIterator {
	PelletIterator();

	void first();
	bool isDone();
	void next();
	Pellet* operator*();
	void setFirst();

	u32 _00;                              // _00 - unknown
	FixedSizePelletMgr<Pellet>* mMgr;     // _04
	TObjectNode<GenericObjectMgr>* mNode; // _08
	int mIndex;                           // _0C
};

/**
 * @size{0x28}
 */
struct PelletInitArg : public CreatureInitArg {
	PelletInitArg()
	{
		_1C                   = 0;
		mState                = 0;
		mPelletType           = 0xFF;
		_18                   = nullptr;
		_17                   = 0;
		_04                   = true;
		mAdjustWeightForSquad = 0;
		mMaxCarriers          = -1;
		mMinCarriers          = -1;
		_1E                   = 0;
		mFromEnemy            = 0;
	}

	/**
	 * @reifiedAddress{80107C2C}
	 * @reifiedFile{plugProjectYamashitaU/enemyBase.cpp}
	 */
	virtual const char* getName() // _00
	{
		return "PelletInitArg";
	}

	bool _04;                 // _04
	char* mTextIdentifier;    // _08
	int _0C;                  // _0C
	int _10;                  // _10
	u16 mState;               // _14
	u8 mPelletType;           // _16
	u8 _17;                   // _17
	PelletView* _18;          // _18
	u8 _1C;                   // _1C
	u8 mAdjustWeightForSquad; // _1D, should Item decrease weight for piki squads that are less than minimum carry weight
	u8 _1E;                   // _1E
	u8 mFromEnemy;            // _1F
	int mMinCarriers;         // _20
	int mMaxCarriers;         // _24
};

struct PelletIndexInitArg : public PelletInitArg {
	PelletIndexInitArg(int);

	u8 _28[0x8]; // _28, unknown
};

struct PelletNumberInitArg : public PelletInitArg {
	PelletNumberInitArg(int size, int);
};

struct PelletKillArg : public CreatureKillArg {
	u8 _08; // _08
};

/**
 * @size = 0x458
 */
struct Pellet : public DynCreature, public SysShape::MotionListener, public CarryInfoOwner {
	Pellet();

	enum PelletFlag {
		FLAG_LOOZY            = 0,
		FLAG_NAVI_NAPSACK     = 1,
		FLAG_NONE             = 2,
		FLAG_VS_CHERRY        = 3,
		FLAG_VS_BEDAMA_RED    = 4,
		FLAG_VS_BEDAMA_BLUE   = 5,
		FLAG_VS_BEDAMA_YELLOW = 6
	};

	////////////// VTABLE 1 (DYNCREATURE)
	virtual Vector3f getPosition() // _08 (weak)
	{
		return mPelletPosition;
	}
	virtual void getBoundingSphere(Sys::Sphere& boundSphere);        // _10
	virtual bool deferPikiCollision() { return true; }               // _20 (weak)
	virtual void constructor();                                      // _2C
	virtual void onInit(CreatureInitArg* settings);                  // _30 (weak)
	virtual void onKill(CreatureKillArg* settings);                  // _34
	virtual void doAnimation();                                      // _3C
	virtual void doEntry();                                          // _40
	virtual void doSetView(int viewportNumber);                      // _44
	virtual void doViewCalc();                                       // _48
	virtual void doSimulation(f32 rate);                             // _4C
	virtual void doDirectDraw(Graphics& gfx);                        // _50
	virtual f32 getFaceDir() { return mFaceDir; }                    // _64 (weak)
	virtual void setVelocity(Vector3f& vel);                         // _68
	virtual Vector3f getVelocity();                                  // _6C
	virtual void onSetPosition(Vector3f& dest);                      // _70 (weak)
	virtual void updateTrMatrix();                                   // _78
	virtual bool inWater() { return mIsInWater; }                    // _8C (weak)
	virtual void onStartCapture();                                   // _94
	virtual void onUpdateCapture(Matrixf&);                          // _98
	virtual void onEndCapture();                                     // _9C
	virtual void doSave(Stream&);                                    // _E0
	virtual void doLoad(Stream&);                                    // _E4
	virtual void bounceCallback(Sys::Triangle* tri);                 // _E8
	virtual JAInter::Object* getJAIObject();                         // _F4
	virtual PSM::Creature* getPSCreature();                          // _F8
	virtual Vector3f* getSound_PosPtr() { return &mPelletPosition; } // _100 (weak)
	virtual void getShadowParam(ShadowParam& settings);              // _134
	virtual bool needShadow();                                       // _138
	virtual void getLODSphere(Sys::Sphere& lodSphere);               // _140
	virtual void startPick();                                        // _148
	virtual void endPick(bool);                                      // _14C
	virtual bool isSlotFree(short);                                  // _168
	virtual short getFreeStickSlot();                                // _16C
	virtual short getNearFreeStickSlot(Vector3f&);                   // _170
	virtual short getRandomFreeStickSlot();                          // _174
	virtual void onSlotStickStart(Creature*, short);                 // _178
	virtual void onSlotStickEnd(Creature*, short);                   // _17C
	virtual void calcStickSlotGlobal(short, Vector3f&);              // _180
	virtual bool stimulate(Interaction& data);                       // _1A4
	virtual char* getCreatureName();                                 // _1A8
	virtual s32 getCreatureID();                                     // _1AC
	virtual void onSetPosition();                                    // _1B0
	////////////// VTABLE 1 END (DYNCREATURE)

	////////////// VTABLE 2  (MOTIONLISTENER)
	// --- (only thunk)
	////////////// VTABLE 2 END (MOTIONLISTENER)

	////////////// VTABLE 3 (CARRYINFOOWNER + SELF)
	// getCarryInfoParam thunk at _1C8
	virtual void do_onInit(CreatureInitArg*) { }                // _1CC (weak)
	virtual void onCreateShape() { }                            // _1D0 (weak)
	virtual void theEntry();                                    // _1D4
	virtual void onBounce() { }                                 // _1D8 (weak)
	virtual void shadowOn();                                    // _1DC
	virtual void shadowOff();                                   // _1E0
	virtual bool isPickable();                                  // _1E4
	virtual s32 getBedamaColor() { return -1; }                 // _1E8 (weak)
	virtual void do_update() { }                                // _1EC (weak)
	virtual void onKeyEvent(const SysShape::KeyEvent& keyEvent) // _1F0 (weak, thunk at _1BC)
	{
		if ((keyEvent.mType == 1000U) && (mCarryAnim.mFlags & 2)) {
			mCarryAnim.startAnim(0, this);
			if (_3D0 & 1) {
				mAnimSpeed = 30.0f * sys->mDeltaTime;
				return;
			}
			mAnimSpeed = 0.0f;
		}
	}
	virtual u8 getKind() = 0;                                 // _1F4
	virtual void changeMaterial() { }                         // _1F8 (weak)
	virtual void createKiraEffect(Vector3f&) { }              // _1FC (weak)
	virtual void getCarryInfoParam(CarryInfoParam& infoParam) // _200 (weak, thunk at _1C8)
	{
		infoParam.mUseType    = 0;
		infoParam.mPosition   = mRigid.mConfigs[0]._00;
		infoParam.mYOffsetMax = 30.0f + mConfig->mParams.mHeight.mData;
		infoParam._14         = 1;
		infoParam.mIsTopFirst = 1;
		infoParam.mValue2     = getTotalCarryPikmins();

		int minVal;
		if (mMinCarriers > 0) {
			minVal = mMinCarriers;
		} else {
			minVal = mConfig->mParams.mMin.mData;
		}
		infoParam.mValue1 = minVal;

		infoParam.mColor = mCarryColor;
	}
	virtual bool isCarried();                    // _204
	virtual bool isPicked() { return _3D0 & 1; } // _208 (weak)
	virtual void sound_otakaraEventStart() { }   // _20C (weak)
	virtual void sound_otakaraEventRestart() { } // _210 (weak)
	virtual void sound_otakaraEventStop() { }    // _214 (weak)
	virtual void sound_otakaraEventFinish() { }  // _218 (weak)

	u8 getWallTimer();
	void clearClaim();
	void sendClaim();
	void updateClaim();
	f32 getBuryDepthMax();
	f32 getBuryDepth();
	f32 getBuryRadius(f32);

	f32 getBottomRadius();
	f32 getPickRadius();
	f32 getCylinderHeight();
	int getConfigIndex();
	char* getConfigName();
	int getPelletConfigMin();
	int getPelletConfigMax();
	void setupParticles();
	void setupParticles_simple();
	void setupParticles_tall();
	bool panmodokiCarryable();
	void finishDisplayCarryInfo();
	void setCarryColor(int);
	void clearCarryColor();
	void allocateTexCaster();
	void setPanModokiRotation(f32);
	void setOrientation(Matrixf&);
	int getStateID();
	void update();
	void getPikiBirthCount(int&, int&);
	void entryShape();
	void init_pmotions();
	void update_pmotions();
	void start_pmotions();
	void stop_carrymotion();
	void finish_carrymotion();
	int getSpeicalSlot();
	Onyon* getPelletGoal();
	int getTotalPikmins();
	int getTotalCarryPikmins();
	int getPikmins(int);
	int getFace();
	void clearDiscoverDisable();
	void startDiscoverDisable(u8);
	void updateDiscoverDisable();
	bool discoverDisabled();

	inline void setValidColor(u16 color)
	{
		P2ASSERTLINE(909, !(color > 2));
		mPelletColor = color;
	}

	inline void setSlotOccupied(int slot)
	{
		if (slot < 128) {
			u32 index = slot >> 3;
			u32 flag  = 1 << slot - index * 8;
			mSlots[15 - index] |= flag;
		}
	}

	inline void setSlotFree(int slot)
	{
		if (slot < 128) {
			u32 index = slot >> 3;
			u32 flag  = 1 << slot - index * 8;
			mSlots[15 - index] &= ~flag;
		}
	}

	inline void animate_pmotions(SysShape::Animator* animator)
	{
		for (int i = 0; i < mNumPMotions; i++) {
			animator->animate(1.0f);

			char jointName[128];
			sprintf(jointName, "pmotion");

			SysShape::Joint* joint = mModel->getJoint(jointName);

			if (joint) {
				u16 index               = joint->mJointIndex;
				SysShape::Model* model  = mModel;
				J3DMtxCalcAnmBase* calc = static_cast<J3DMtxCalcAnmBase*>(animator->getCalc());

				model->mJ3dModel->mModelData->mJointTree.mJoints[index]->mMtxCalc = calc;
			}
		}
	}

	inline bool isTreasurePosition() // this probably needs a better name; used in Pellet::onSetPosition
	{
		bool check = false;
		if ((mCaptureMatrix == nullptr) && (PelletMgr::mDebug == false) && (mConfig->mParams.mDepth.mData > 0.0f) && (_3C4 == 0)) {
			check = true;
		}
		if ((gameSystem->mMode == GSM_VERSUS_MODE) && (mCaptureMatrix == nullptr) && (_3C4 == 0)) {
			u8 test = mPelletFlag;
			if (test == FLAG_VS_BEDAMA_RED) {
				check = false;
			} else if (test == FLAG_VS_BEDAMA_BLUE) {
				check = false;
			} else if (test == FLAG_VS_BEDAMA_YELLOW && getStateID() != 5) {
				check = true;
			}
		}
		return check;
	}

	inline int getPokoValue() { return mConfig->mParams.mMoney.mData; }

	// _00		= VTABLE 1
	// _04-_314	= DYNCREATURE
	// _318 	= VTABLE 2? 3?
	f32 mRadius;                   // _31C
	f32 mDepth;                    // _320
	u8 _324;                       // _324 - unknown
	bool mIsInWater;               // _325
	u8 _326[0x2];                  // _326 - could be padding
	TexCaster::Caster* mCaster;    // _328
	u8 mPelletFlag;                // _32C
	u8 mDiscoverDisable;           // _32D
	u8 _32E[0x2];                  //  _32E - could be padding
	PSM::EventBase* mSoundMgr;     // _330
	PelletCarry* mPelletCarry;     // _334
	u8 mNumPMotions;               // _338
	u8 _339[0x3];                  // _339, unknown/padding
	SysShape::Animator _33C;       // _33C
	PelletView* mPelletView;       // _358
	PelletConfig* mConfig;         // _35C
	int _360;                      // _360
	u8 _364;                       // _364
	u8 _365[0x33];                 // _365 - unknown
	CarryInfoMgr* mCarryInfoMgr;   // _398
	u8 _39C;                       // _39C - unknown
	u8 _39D[0xF];                  // _39D - unknown
	Vector3f mPelletPosition;      // _3AC
	f32 mFaceDir;                  // _3B8
	u8 mWallTimer;                 // _3BC
	u8 _3BD[0x3];                  // _3BD - possibly padding
	u32 mClaim;                    // _3C0
	bool _3C4;                     // _3C4
	u8 _3C5[0x3];                  // _3C5 - unknown
	PelletFSM* mPelletSM;          // _3C8
	PelletState* mPelletState;     // _3CC
	u8 _3D0;                       // _3D0
	int mCarryColor;               // _3D4
	int mMinCarriers;              // _3D8, to do with pikmin number
	int mMaxCarriers;              // _3DC
	f32 _3E0;                      // _3E0
	u8 mSlots[16];                 // _3E4
	short mSlotCount;              // _3F4
	u8 _3F6;                       // _3F6
	u8 _3F7;                       // _3F7 - unknown, maybe padding
	u32 mPikminCount[7];           // _3F8, TODO: likely [PikiColorCount]
	u32 _414;                      // _414 - unknown
	f32 mCarryPower;               // _418
	SysShape::Animator mCarryAnim; // _41C
	f32 mAnimSpeed;                // _438
	u16 _43C;                      // _43C
	u16 mPelletColor;              // _43E, this reflects pellet color for Number pellets, and the color of berries
	int mSlotIndex;                // _440
	Sys::Sphere mLodSphere;        // _444
	BasePelletMgr* mMgr;           // _454

	static bool sFromTekiEnable;
};

struct PelletFSM : public StateMachine<Pellet> {
	virtual void init(Pellet*); // _08

	// _00 		= VTABLE
	// _04-_1C 	= StateMachine<Pellet>
};

enum StateID {
	PELSTATE_Normal,
	PELSTATE_Goal,
	PELSTATE_Bury,
	PELSTATE_Up,
	PELSTATE_Appear,
	PELSTATE_ScaleAppear,
	PELSTATE_Zukan,
	PELSTATE_GoalWait,
	PELSTATE_Return,
	PELLET_STATE_COUNT
};

struct PelletGoalStateArg : public StateArg {
	inline PelletGoalStateArg(Creature* creature) { mCreature = creature; }

	Creature* mCreature; // _00
	// _04 = VTBL

	virtual char* getName() { return "PelletGoalStateArg"; } // _08 (weak)
};

struct PelletReturnStateArg : public StateArg {
	inline PelletReturnStateArg(Vector3f& pos) { mPosition = pos; }

	Vector3f mPosition; // _00
};

struct PelletState : public FSMState<Pellet> {
	PelletState(int id)
	    : FSMState<Pellet>(id)
	{
	}

	virtual bool isBuried();                    // _20 (weak)
	virtual bool appeared();                    // _24 (weak)
	virtual bool isPickable() { return false; } // _28 (weak)

	u8 _0C[0x4]; // _0C
};

struct PelletAppearState : public PelletState {
	PelletAppearState()
	    : PelletState(PELSTATE_Appear)
	{
	}

	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10
	virtual bool appeared();               // _24 (weak)

	f32 mTime;      // _10
	f32 mAngle;     // _14
	f32 mGoalScale; // _18
	f32 _1C;        // _1C
	f32 _20;        // _20
	f32 _24;        // _24
	f32 _28;        // _28
	bool mEfxMade;  // _29
};

struct PelletBuryState : public PelletState {
	PelletBuryState()
	    : PelletState(PELSTATE_Bury)
	{
	}

	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10
	virtual bool isBuried();               // _20 (weak)
};

struct PelletGoalState : public PelletState {
	PelletGoalState()
	    : PelletState(PELSTATE_Goal)
	{
	}

	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10

	bool checkMovie(Pellet*);

	Creature* mOnyon; // _10
	f32 _14;          // _14
	f32 mDistance;    // _18
	f32 mSuckDelay;   // _1C
	f32 mScale;       // _20
	f32 mSuckTime;
	Vector3f mCurrPos;
	bool mStartSuck;
	f32 mTimer;
	u8 mInDemo;     // _3C, unknown
	u8 mIsWaiting;  // _3D
	u8 mDidSuikomi; // _3E
};

struct PelletGoalWaitState : public PelletState {
	PelletGoalWaitState()
	    : PelletState(PELSTATE_GoalWait)
	{
	}

	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10

	Creature* mObj; // _10
};

struct PelletNormalState : public PelletState {
	PelletNormalState()
	    : PelletState(PELSTATE_Normal)
	{
	}

	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10
	virtual bool isPickable();             // _28 (weak)
};

struct PelletReturnState : public PelletState {
	PelletReturnState();

	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10

	int initPathfinding(Pellet*);
	u32 execPathfinding(Pellet*);
	u32 execMove(Pellet*);
	u32 execMoveGoal(Pellet*);

	void flick(Pellet*);
	void getWayPont(int);

	f32 mTimer;      // _10
	f32 mPeltYScale; // _14
	u8 mDoEfx;       // _18
	u8 mDoFlick;
	u16 mState;                     // _1A
	u32 mPathCheckID;               // _1C
	Vector3f mGoalPos;              // _20
	PathNode* mPathNode;            // _2C
	PathNode* mPathNodePrev;        // _30
	int mPathNodes;                 // _34
	::efx::TOrimaLight* mEfx;       // _38
	::efx::TOrimaLightAct* mEfxAct; // _3C
};

struct PelletScaleAppearState : public PelletState {
	PelletScaleAppearState()
	    : PelletState(PELSTATE_ScaleAppear)
	{
	}

	// might inherit PelletAppearState or vice versa?
	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10
	virtual bool appeared();               // _24 (weak)

	f32 mTime;      // _10
	f32 mAngle;     // _14
	f32 mGoalScale; // _18
	f32 _1C;        // _1C
	f32 _20;        // _20
	f32 _24;        // _24
	f32 _28;        // _28
	bool mEfxMade;  // _2C
};

struct PelletUpState : public PelletState {
	PelletUpState()
	    : PelletState(PELSTATE_Up)
	{
	}

	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10
	virtual bool isBuried();               // _20 (weak)
};

struct PelletZukanState : public PelletState {
	PelletZukanState()
	    : PelletState(PELSTATE_Zukan)
	{
	}

	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10

	f32 mTimer; // _10
};

extern PelletMgr* pelletMgr;

} // namespace Game

#endif
