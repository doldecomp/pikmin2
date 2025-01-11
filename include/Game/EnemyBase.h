#ifndef _GAME_ENEMYBASE_H
#define _GAME_ENEMYBASE_H

#include "Game/Creature.h"
#include "Game/CollEvent.h"
#include "Game/EnemyStateMachine.h"
#include "Game/MoveInfo.h"
#include "Game/EnemyEffectNode.h"
#include "Game/PelletView.h"
#include "Game/EnemyPelletInfo.h"
#include "Game/pelletMgr.h"

#include "SysShape/MotionListener.h"

#include "PSM/EnemyBase.h"
#include "efx/TEnemyPiyo.h"

#include "trig.h"

#define EMOTE_None       (0)
#define EMOTE_Caution    (1)
#define EMOTE_Excitement (2)

#define OBJ(enemy) (static_cast<Obj*>(enemy))

struct MouthSlots;

namespace PSM {
struct EnemyBase;
} // namespace PSM

namespace Game {
struct EnemyBase;

namespace EnemyBaseFSM {
struct StateMachine;
} // namespace EnemyBaseFSM

namespace EnemyStone {
struct Obj;
} // namespace EnemyStone

namespace WalkSmokeEffect {
struct Mgr;
} // namespace WalkSmokeEffect

struct EnemyAnimatorBase;
struct EnemyAnimKeyEvent;
struct EnemyMgrBase;
struct WaterBox;
struct LifeGaugeParam;
struct Interaction;

enum EnemyEvent {
	EB_Invulnerable        = 0x1,        // cannot be damaged
	EB_TakingDamage        = 0x2,        // currently taking damage
	EB_Untargetable        = 0x4,        // untargetable by pikmin (e.g. flying, dead)
	EB_DamageAnimEnabled   = 0x8,        // can perform damage animation
	EB_Colliding           = 0x10,       // currently doing a collision event
	EB_FlickEnabled        = 0x20,       // can flick/throw off pikmin
	EB_Cullable            = 0x40,       // can be culled/deloaded
	EB_LeaveCarcass        = 0x80,       // leave carcass upon death
	EB_DeathEffectEnabled  = 0x100,      // can perform death EFX on death
	EB_Bittered            = 0x200,      // currently bittered
	EB_Constrained         = 0x400,      // position is fixed, but can rotate or be moved externally
	EB_LifegaugeVisible    = 0x800,      // has visible lifegauge
	EB_PlatformCollEnabled = 0x1000,     // can interact with platform collision
	EB_CullSound           = 0x2000,     // unknown (only set by an imomushi state, reset by imomushi and rock states?)
	EB_EatingWhitePikmin   = 0x4000,     // has eaten white pikmin (trigger poison effect, damage)
	EB_Animating           = 0x8000,     // currently animating
	EB_AttackingNavi0      = 0x10000,    // is attacking the player's main character?
	EB_AttackingNavi1      = 0x20000,    // is attacking an ai player?
	EB_HardConstrained     = 0x40000,    // kinematic, i.e. disables physics completely/locks position
	EB_SquashOnDamageAnim  = 0x80000,    // set on at finishDropping, and HipDropCallback
	EB_BitterQueued        = 0x100000,   // has been hit by bitter spray, is not bittered yet
	EB_NoInterrupt         = 0x200000,   // cannot currently interrupt anim/action - cannot be stunned, bitters will be queued
	EB_BitterImmune        = 0x400000,   // cannot be bittered
	EB_24                  = 0x800000,   // unknown
	EB_IsAnimated          = 0x1000000,  // set when an enemy (non-blended) animation is playing, needed for .bas based sounds to work
	EB_PS2                 = 0x2000000,  // disabled on animation start, never enabled, has similar purpose to EB_IsBlendAnimated
	EB_IsBlendAnimated     = 0x4000000,  // set when an enemy blended animation is playing
	EB_PS4                 = 0x8000000,  // disabled on animation start, never enabled
	EB_Alive               = 0x10000000, //
	EB_CollisionActive     = 0x20000000, //
	EB_ModelHidden         = 0x40000000, //
};

enum EnemyEvent2 {
	EB2_Earthquake       = 0x1,  // currently hit by purple earthquake/ground pound
	EB2_Stunned          = 0x2,  // currently stunned/'fit' by purple
	EB2_3                = 0x4,  // unknown
	EB2_4                = 0x8,  // unknown
	EB2_Dropping         = 0x10, // currently falling/dropping
	EB2_DroppingMassZero = 0x20  // currently falling/dropping with 0 mass
};

enum DropGroup {
	EDG_None       = 0, // not dropping
	EDG_Normal     = 1, // drop on pikmin or navi approach
	EDG_Pikmin     = 2, // drop on pikmin approach only
	EDG_Navi       = 3, // drop on navi approach only
	EDG_Carry      = 4, // drop on pikmin carrying an object only
	EDG_Earthquake = 5, // drop on purple earthquake/ground pound only
};

// Interface for specific overrides (e.g. PelplantInitialParams)
struct EnemyInitialParamBase {
};

struct EnemyKillArg : public CreatureKillArg {
	inline EnemyKillArg(int flag)
	    : CreatureKillArg(flag)
	{
	}

	virtual const char* getName() // _08 (weak)
	{
		return "EnemyKillArg";
	}

	// _00 = VTBL
	// _04 = CreatureKillArg
};

/// @brief Base class for enemy objects
struct EnemyBase : public Creature, public SysShape::MotionListener, virtual public Game::PelletView {
	EnemyBase();

	// these are up here so they can be used in virtuals.
	inline void enableEvent(int i, u32 flag) { mEvents.mFlags[i].typeView |= flag; }
	inline void disableEvent(int i, u32 flag) { mEvents.mFlags[i].typeView &= ~flag; }
	inline bool isEvent(int i, u32 flag) { return mEvents.mFlags[i].typeView & flag; }

	// vtable 1 (Creature)
	virtual Vector3f getPosition() // _08 (weak)
	{
		return mPosition;
	}
	virtual void getBoundingSphere(Sys::Sphere& sphere) // _10 (weak)
	{
		sphere = mBoundingSphere;
	}
	virtual void constructor();                         // _2C
	virtual void onInit(CreatureInitArg* settings);     // _30
	virtual void onKill(CreatureKillArg* settings);     // _34
	virtual void onInitPost(CreatureInitArg* settings); // _38
	virtual void doAnimation();                         // _3C
	virtual void doEntry();                             // _40
	virtual void doSetView(int viewportNumber);         // _44
	virtual void doViewCalc();                          // _48
	virtual void doSimulation(f32 simSpeed);            // _4C
	virtual void onSetPosition(Vector3f& position)      // _70 (weak)
	{
		mPosition = position;
	}
	virtual void onSetPositionPost(Vector3f& position) // _74 (weak)
	{
		updateSpheres();
	}
	virtual void updateTrMatrix();                      // _78
	virtual void inWaterCallback(WaterBox* wbInsideOf); // _84
	virtual void outWaterCallback();                    // _88
	virtual bool isFlying()                             // _CC (weak)
	{
		return isEvent(0, EB_Untargetable);
	}
	virtual void collisionCallback(CollEvent& coll);          // _EC
	virtual JAInter::Object* getJAIObject();                  // _F4
	virtual PSM::Creature* getPSCreature();                   // _F8
	virtual bool needShadow();                                // _138
	virtual void getLifeGaugeParam(LifeGaugeParam& settings); // _13C
	virtual void onStickStart(Creature* sticker);             // _158
	virtual void onStickEnd(Creature* sticker);               // _15C
	virtual bool stimulate(Interaction& interaction);         // _1A4
	virtual char* getCreatureName()                           // _1A8 (weak)
	{
		return EnemyInfoFunc::getEnemyName(getEnemyTypeID(), 0xFFFF);
	}
	virtual s32 getCreatureID() // _1AC (weak)
	{
		return mCreatureID;
	}
	// vtable 2 (MotionListener+self)
	// virtual void onKeyEvent(const SysShape::KeyEvent& event); - thunk _1B8
	virtual ~EnemyBase() { }                                                                                     // _1BC (weak)
	virtual void birth(Vector3f& position, f32 faceDirection);                                                   // _1C0
	virtual void setInitialSetting(EnemyInitialParamBase* settings) = 0;                                         // _1C4
	virtual void update();                                                                                       // _1C8
	virtual void doUpdate() = 0;                                                                                 // _1CC
	virtual void doUpdateCommon();                                                                               // _1D0
	virtual void doUpdateCarcass();                                                                              // _1D4
	virtual void doAnimationUpdateAnimator();                                                                    // _1D8
	virtual void doAnimationCullingOff();                                                                        // _1DC
	virtual void doAnimationCullingOn();                                                                         // _1E0
	virtual void doAnimationStick();                                                                             // _1E4
	virtual void doSimulationCarcass(f32);                                                                       // _1E8
	virtual void doDebugDraw(Graphics& gfx);                                                                     // _1EC
	virtual void doSimpleDraw(Viewport* vp) { }                                                                  // _1F0 (weak)
	virtual void doSimulationGround(f32 simSpeed);                                                               // _1F4
	virtual void doSimulationFlying(f32 simSpeed);                                                               // _1F8
	virtual void doSimulationStick(f32 simSpeed);                                                                // _1FC
	virtual void changeMaterial();                                                                               // _200
	virtual void getCommonEffectPos(Vector3f& effectPos);                                                        // _204
	virtual Vector3f* getFitEffectPos();                                                                         // _208
	virtual SysShape::Model* viewGetShape();                                                                     // _20C
	virtual void view_start_carrymotion();                                                                       // _210
	virtual void view_finish_carrymotion();                                                                      // _214
	virtual void viewStartPreCarryMotion();                                                                      // _218
	virtual void viewStartCarryMotion();                                                                         // _21C
	virtual void viewOnPelletKilled();                                                                           // _220
	virtual f32 getCellRadius() { return static_cast<EnemyParmsBase*>(mParms)->mGeneral.mCellRadius(); }         // _58 (weak)
	virtual f32 getBodyRadius() { return static_cast<EnemyParmsBase*>(mParms)->mGeneral.mPikminDamageRadius(); } // _54 (weak)
	virtual f32 getFaceDir() { return mFaceDir; }                                                                // _64 (weak)
	virtual void setVelocity(Vector3f& velocity) { mCurrentVelocity = velocity; }                                // _68 (weak)
	virtual Vector3f getVelocity() { return mCurrentVelocity; }                                                  // _6C (weak)
	virtual void getVelocityAt(Vector3f& velSrc, Vector3f& velDest)                                              // _184 (weak)
	{
		velSrc  = mCurrentVelocity;
		velDest = mCurrentVelocity;
	}
	virtual bool isTeki() { return true; }                                           // _7C (weak)
	virtual Vector3f* getSound_PosPtr() { return &mPosition; }                       // _100 (weak)
	virtual Vector3f getOffsetForMapCollision() { return Vector3f(0.0f); }           // _224 (weak)
	virtual void setParameters();                                                    // _228
	virtual void initMouthSlots() { }                                                // _22C (weak)
	virtual void initWalkSmokeEffect() { }                                           // _230 (weak)
	virtual bool inWater() { return (mWaterBox != nullptr); }                        // _8C (weak)
	virtual WalkSmokeEffect::Mgr* getWalkSmokeEffectMgr() { return nullptr; }        // _234 (weak)
	virtual void onKeyEvent(const SysShape::KeyEvent& event);                        // _238 (weak)
	virtual bool injure();                                                           // _23C
	virtual void setCollEvent(CollEvent& newEvent);                                  // _240
	virtual void getEfxHamonPos(Vector3f* pos) { *pos = mPosition; }                 // _244 (weak)
	virtual void createInstanceEfxHamon();                                           // _248
	virtual void updateEfxHamon();                                                   // _24C
	virtual void createEfxHamon();                                                   // _250
	virtual void fadeEfxHamon();                                                     // _254
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID() = 0;                          // _258
	virtual MouthSlots* getMouthSlots() { return nullptr; }                          // _25C (weak)
	virtual void doGetLifeGaugeParam(LifeGaugeParam& settings);                      // _260
	virtual void throwupItem();                                                      // _264
	virtual void getThrowupItemPosition(Vector3f* throwupPosition);                  // _268
	virtual void getThrowupItemVelocity(Vector3f* throwupVelocity);                  // _26C
	virtual void throwupItemInDeathProcedure() { throwupItem(); }                    // _270 (weak)
	virtual void setLODSphere(Sys::Sphere& sphere) { mCurLodSphere = sphere; }       // _274 (weak)
	virtual void getLODSphere(Sys::Sphere& lodSphere) { lodSphere = mCurLodSphere; } // _140 (weak)
	virtual bool damageCallBack(Creature* source, f32 damage, CollPart* part);       // _278
	virtual bool pressCallBack(Creature* source, f32 damage, CollPart* part);        // _27C
	virtual bool flyCollisionCallBack(Creature* source, f32 damage, CollPart* part); // _280
	virtual bool hipdropCallBack(Creature* source, f32 damage, CollPart* part);      // _284
	virtual bool dropCallBack(Creature* source);                                     // _288
	virtual bool earthquakeCallBack(Creature* source, f32 bounceFactor);             // _28C
	virtual bool farmCallBack(Creature* source, f32 power);                          // _290
	virtual bool bombCallBack(Creature* source, Vector3f& direction, f32 damage);    // _294
	virtual bool eatWhitePikminCallBack(Creature* source, f32 damage);               // _298
	virtual bool dopeCallBack(Creature* source, int sprayType);                      // _29C
	virtual bool doDopeCallBack(Creature* source, int sprayType) { return true; }    // _2A0 (weak)
	virtual void doStartStoneState();                                                // _2A4
	virtual void doFinishStoneState();                                               // _2A8
	virtual f32 getDamageCoeStoneState() { return 1.5f; }                            // _2AC (weak)
	virtual f32 getSound_CurrAnimFrame() { return mAnimator->getAnimator().mTimer; } // _108 (weak)
	virtual f32 getSound_CurrAnimSpeed() { return mAnimator->mSpeed; }               // _10C (weak)
	virtual bool sound_culling()                                                     // _104 (weak)
	{
		bool culling = false;
		if (isEvent(0, EB_CullSound)) {
			if (!mLod.isFlag(AILOD_IsVisible) && !mLod.isFlag(AILOD_PikiInCell)) {
				culling = true;
			}
		}
		return culling;
	}
	virtual void doStartEarthquakeState(f32 yVelocityScale); // _2B0
	virtual void doFinishEarthquakeState();                  // _2B4
	virtual void doStartEarthquakeFitState();                // _2B8
	virtual void doFinishEarthquakeFitState();               // _2BC
	virtual void lifeRecover();                              // _2C0
	virtual void startCarcassMotion()                        // _2C4 (weak)
	{
		SysShape::MotionListener* listener = this;

		EnemyAnimatorBase* animator = mAnimator;
		animator->mFlags.unset(SysShape::Animator::AnimCompleted | SysShape::Animator::AnimFinishMotion);
		animator->mNormalizedTime = 1.0f;
		animator->getAnimator(0).startAnim(0, listener);

		disableEvent(0, EB_IsAnimated + EB_PS2 + EB_IsBlendAnimated + EB_PS4);
		enableEvent(0, EB_IsAnimated);

		setPSEnemyBaseAnime();
	}
	virtual void setCarcassArg(PelletViewArg& settings);                  // _2C8
	virtual f32 getCarcassArgHeight() { return mBoundingSphere.mRadius; } // _2CC (weak)
	virtual bool doBecomeCarcass();                                       // _2D0
	virtual void startWaitingBirthTypeDrop();                             // _2D4
	virtual void finishWaitingBirthTypeDrop();                            // _2D8
	virtual bool isFinishableWaitingBirthTypeDrop();                      // _2DC
	virtual void doStartWaitingBirthTypeDrop();                           // _2E0
	virtual void doFinishWaitingBirthTypeDrop();                          // _2E4
	virtual void wallCallback(const MoveInfo& info) { }                   // _2E8 (weak)
	virtual f32 getDownSmokeScale();                                      // _2EC
	virtual void doStartMovie() { }                                       // _2F0 (weak)
	virtual void doEndMovie() { }                                         // _2F4 (weak)

	// vtable 3 (PelletView)

	void addDamage(f32 damageAmt, f32 flickSpeed);

	void bounceProcedure(Sys::Triangle* triangle);

	// Collision with the map and platforms
	void collisionMapAndPlat(f32 timeStep);

	PSM::EnemyBase* createPSEnemyBase();
	void createEffects();
	void createBounceEffect(const Vector3f& position, f32 scale);
	void createDeadBombEffect();
	void createDropEffect(const Vector3f& position, f32 scale);
	void createSplashDownEffect(const Vector3f& position, f32 scale);
	void fadeEffects();

	void doEntryCarcass();
	void doEntryLiving();
	void doSimulationConstraint(f32 timeStep);
	void hardConstraintOn();
	void hardConstraintOff();
	void constraintOff();

	void finishDropping(bool lockToFloor);

	void deathProcedure();
	void gotoHell();

	bool isCullingOff();

	void startMotion();
	void startMotion(int animIdx, SysShape::MotionListener* mListener);
	void finishMotion();
	void stopMotion();
	bool isFinishMotion();
	bool isStopMotion();
	f32 getFirstKeyFrame();
	f32 getMotionFrame();
	f32 getMotionFrameMax();
	void setMotionFrame(f32 frame);

	int getCurrAnimIndex();
	void setAnimSpeed(f32 speed);
	void resetAnimSpeed();

	void setEmotionCaution();
	void setEmotionExcitement();
	void setEmotionNone();

	void setAnimMgr(SysShape::AnimMgr* animMgr);
	void setOtakaraCode(PelletMgr::OtakaraItemCode& code);
	void setPSEnemyBaseAnime();
	void setZukanVisible(bool updateTekiDeathInfo);

	void startBlend(int srcAnimIdx, int destAnimIdx, SysShape::BlendFunction* blendFunc, f32 frameRate, SysShape::MotionListener* listener);
	void endBlend();

	void show();
	void hide();

	void forceKillEffects();
	void deathMethod();

	int getStateID();
	bool isBeforeAppearState();
	void startStoneState();

	void scaleDamageAnim();
	void finishScaleDamageAnim();

	void updateSpheres();
	void getWaterSphere(Sys::Sphere* waterSphere);
	void updateWaterBox();

	void startMovie();
	void endMovie();

	bool isBirthTypeDropGroup();
	bool checkBirthTypeDropEarthquake();
	void setDroppingMassZero();
	void resetDroppingMassZero();

	void resetCollEvent();
	void becomeCarcass();
	void updateEffects();

	inline void setCreatureID(u8 idx) { mCreatureID = idx; }

	inline bool isDead() { return mHealth <= 0.0f; }

	inline bool isEarthQuakeOrDropping() { return isEvent(1, EB2_Earthquake) || isEvent(1, EB2_Dropping); }

	inline f32 getAccelerationScale(f32 maxAccel)
	{
		return maxAccel / static_cast<EnemyParmsBase*>(mParms)->mCreatureProps.mProps.mAccel.mValue;
	}

	inline void setScale(f32 scale)
	{
		mScaleModifier = scale;
		mScale         = Vector3f(scale);
	}

	inline void getDistance2D(Vector3f& point, Vector2f& sep)
	{
		sep.x = mPosition.x - point.x;
		sep.y = mPosition.z - point.z;
	}

	inline f32 getCreatureViewAngle(Creature* target)
	{
		Vector3f targetPosition = target->getPosition();
		Vector3f myPosition     = getPosition();

		f32 x = targetPosition.x - myPosition.x;
		f32 z = targetPosition.z - myPosition.z;

		return angDist(angXZ(x, z), getFaceDir());
	}

	inline f32 getCreatureViewAngle(Vector3f& targetPos)
	{
		Vector3f pos = getPosition();

		f32 x = targetPos.x - pos.x;
		f32 z = targetPos.z - pos.z;

		return angDist(angXZ(x, z), getFaceDir());
	}

	// this seems necessary and correct based on BombSarai::Obj::throwBomb
	inline void updateFaceDir(f32 angle)
	{
		mFaceDir    = angle;
		mRotation.y = mFaceDir;
	}

	inline f32 turnToTarget(Vector3f& targetPos, f32 turnSpeed, f32 maxTurnAngle)
	{
		f32 angleDist = getAngDist(targetPos);
		f32 angle     = clamp(angleDist * turnSpeed, PI * (DEG2RAD * maxTurnAngle));
		updateFaceDir(roundAng(angle + getFaceDir()));

		return angleDist;
	}

	inline f32 turnToTarget2(Vector3f& targetPos, f32 turnSpeed, f32 maxTurnAngle)
	{
		f32 angleDist = getAngDist2(targetPos);
		f32 angle     = clamp(angleDist * turnSpeed, PI * (DEG2RAD * maxTurnAngle));
		updateFaceDir(roundAng(angle + getFaceDir()));

		return angleDist;
	}

	inline f32 turnToTarget(Creature* target, f32 turnSpeed, f32 maxTurnAngle)
	{
		f32 angleDist = getAngDist(target);
		f32 angle     = clamp(angleDist * turnSpeed, PI * (DEG2RAD * maxTurnAngle));

		updateFaceDir(roundAng(angle + getFaceDir()));

		return angleDist;
	}

	inline f32 turnToTarget(Vector3f& targetPos)
	{
		EnemyParmsBase* parms = static_cast<EnemyParmsBase*>(mParms);
		f32 maxTurnAngle      = parms->mGeneral.mMaxTurnAngle.mValue;
		f32 turnSpeed         = parms->mGeneral.mTurnSpeed.mValue;

		f32 angleDist = getAngDist(targetPos);
		f32 angle     = clamp(angleDist * turnSpeed, PI * (DEG2RAD * maxTurnAngle));

		updateFaceDir(roundAng(angle + getFaceDir()));

		return angleDist;
	}

	inline f32 turnToTarget(Creature* creature)
	{
		EnemyParmsBase* parms = static_cast<EnemyParmsBase*>(mParms);
		f32 maxTurnAngle      = parms->mGeneral.mMaxTurnAngle.mValue;
		f32 turnSpeed         = parms->mGeneral.mTurnSpeed.mValue;

		f32 angleDist = getAngDist(creature);
		f32 angle     = clamp(angleDist * turnSpeed, PI * (DEG2RAD * maxTurnAngle));

		updateFaceDir(roundAng(angle + getFaceDir()));

		return angleDist;
	}

	inline f32 turnToTarget3(Creature* creature)
	{
		EnemyParmsBase* parms = static_cast<EnemyParmsBase*>(mParms);
		f32 maxTurnAngle      = parms->mGeneral.mMaxTurnAngle.mValue;
		f32 turnSpeed         = parms->mGeneral.mTurnSpeed.mValue;

		f32 angleDist = getCreatureViewAngle(creature);
		f32 angle     = clamp(angleDist * turnSpeed, PI * (DEG2RAD * maxTurnAngle));

		updateFaceDir(roundAng(angle + getFaceDir()));

		return angleDist;
	}

	inline bool isTargetAttackable(Creature* target, f32 angleDiff, f32 attackDist, f32 attackAngle)
	{
		bool result = false;
		Vector3f sep;
		sep.x = target->getPosition().x - getPosition().x;
		sep.y = target->getPosition().y - getPosition().y;
		sep.z = target->getPosition().z - getPosition().z;
		if ((sep.sqrMagnitude() < SQUARE(attackDist)) && (FABS(angleDiff) <= TORADIANS(attackAngle))) {
			result = true;
		}
		return result;
	}

	/**
	 * Checks if a target is within the range of the enemy.
	 *
	 * @param target The target creature to check.
	 * @param pAngle The angle between the enemy and the target.
	 * @param pPrivateRadius The private radius of the enemy.
	 * @param pSightRadius The sight radius of the enemy.
	 * @param pFov The field of view of the enemy.
	 * @param pViewAngle The view angle of the enemy.
	 * @return True if the target is within range, false otherwise.
	 */
	inline bool isTargetWithinRange(Creature* target, f32 pAngle, f32 pPrivateRadius, f32 pSightRadius, f32 pFov, f32 pViewAngle)
	{
		// Calculate the separation between us and target
		Vector3f sep;
		sep.x = target->getPosition().x - getPosition().x;
		sep.y = target->getPosition().y - getPosition().y;
		sep.z = target->getPosition().z - getPosition().z;

		// Calculate the squared distance between us and target
		f32 privateRadius = SQUARE(pPrivateRadius);
		f32 sightRadius   = SQUARE(pSightRadius);
		f32 distance      = sep.sqrMagnitude2D();

		// Check if the target is outside the private and sight radius and within the field of view
		return (distance > privateRadius && (distance > sightRadius && absF(sep.y) < pFov))
		    // Check if the angle to the target is within the field of view
		    || (FABS(pAngle) <= TORADIANS(pViewAngle)) == false;
	}

	inline f32 changeFaceDir2(Creature* target)
	{
		f32 rotSpeed;
		f32 rotAccel;

		EnemyParmsBase* parms = static_cast<EnemyParmsBase*>(mParms);
		rotSpeed              = parms->mGeneral.mMaxTurnAngle();
		rotAccel              = parms->mGeneral.mTurnSpeed();

		Vector3f targetPos = target->getPosition();
		Vector3f pos       = getPosition();

		f32 angleDist   = angDist(_angXZ(targetPos.x, targetPos.z, pos.x, pos.z), getFaceDir());
		f32 approxSpeed = clamp(angleDist * rotAccel, PI * (DEG2RAD * rotSpeed));

		updateFaceDir(roundAng(approxSpeed + getFaceDir()));
		return angleDist;
	}

	inline f32 changeFaceDir(Vector3f& XYZ)
	{
		f32 rotAccel;
		f32 rotSpeed;

		f32 x;
		f32 z;

		EnemyParmsBase* parms = static_cast<EnemyParmsBase*>(mParms);
		rotSpeed              = parms->mGeneral.mMaxTurnAngle();
		rotAccel              = parms->mGeneral.mTurnSpeed();

		Vector3f pos = getPosition();
		x            = XYZ.x;
		z            = XYZ.z;

		f32 angleDist   = angDist(_angXZ(x, z, pos.x, pos.z), getFaceDir());
		f32 approxSpeed = clamp(angleDist * rotAccel, PI * (DEG2RAD * rotSpeed));

		updateFaceDir(roundAng(approxSpeed + getFaceDir()));
		return angleDist;
	}

	inline f32 changeFaceDir(Vector2f& XZ)
	{
		f32 approxSpeed;
		f32 rotSpeed;
		f32 rotAccel;
		f32 x;
		f32 z;

		EnemyParmsBase* parms = static_cast<EnemyParmsBase*>(mParms);
		rotSpeed              = parms->mGeneral.mMaxTurnAngle.mValue;
		rotAccel              = parms->mGeneral.mTurnSpeed.mValue;

		Vector3f pos = getPosition();
		x            = XZ.x;
		z            = XZ.y;

		f32 angleDist = angDist(_angXZ(x, z, pos.x, pos.z), getFaceDir());

		approxSpeed = clamp(angleDist * rotAccel, PI * (DEG2RAD * rotSpeed));

		mFaceDir    = roundAng(approxSpeed + getFaceDir());
		mRotation.y = mFaceDir;
		return angleDist;
	}

	inline f32 changeFaceDir(Creature* target)
	{
		f32 approxSpeed;
		f32 rotSpeed;
		f32 rotAccel;

		EnemyParmsBase* parms = static_cast<EnemyParmsBase*>(mParms);
		rotSpeed              = parms->mGeneral.mMaxTurnAngle.mValue;
		rotAccel              = parms->mGeneral.mTurnSpeed.mValue;

		Vector3f targetPos = target->getPosition();
		Vector3f pos       = getPosition();

		f32 angleDist = angDist(angXZ(targetPos, pos), getFaceDir());

		approxSpeed = clamp(angleDist * rotAccel, PI * (DEG2RAD * rotSpeed));

		mFaceDir    = roundAng(approxSpeed + getFaceDir());
		mRotation.y = mFaceDir;
		return angleDist;
	}

	inline void getPosition2D(Vector3f& pos) { pos = Vector3f(mPosition.x, 0.0f, mPosition.z); }

	inline Vector3f getEBPosition2D() { return Vector3f(mPosition.x, 0.0f, mPosition.z); }

	inline void forceMovePosition(Vector3f offset) { mPosition += offset; }

	inline f32 getDamageAnimFrac(f32 scale) { return (mDamageAnimTimer / scale); }

	inline f32 getSqrHomeRadius() const
	{
		f32 homeRad = static_cast<EnemyParmsBase*>(mParms)->mGeneral.mHomeRadius.mValue;
		return homeRad * homeRad;
	}

	inline efx::Arg createFXArg() { return efx::Arg(mPosition); }

	inline EnemyParmsBase::Parms& getParms() { return static_cast<EnemyParmsBase*>(mParms)->mGeneral; }

	inline bool isWithinHomeRadius() { return sqrDistanceXZ(mPosition, mHomePosition) < getSqrHomeRadius(); }

	inline f32 getSubmergedDepth() const { return *mWaterBox->getSeaHeightPtr() - mPosition.y; }

	inline Vector3f getTargetVelocity() { return mTargetVelocity; }
	inline void setTargetVelocity(const Vector3f& ref) { mTargetVelocity = ref; }

	inline f32 getMoveSpeed() { return static_cast<EnemyParmsBase*>(mParms)->mGeneral.mMoveSpeed(); }
	inline f32 getMoveSpeed(f32 speedFactor) { return speedFactor * static_cast<EnemyParmsBase*>(mParms)->mGeneral.mMoveSpeed(); }

	inline f32 getScaleMod() const { return mScaleModifier; }

	inline void setTargetVelocity(f32 speedFactor)
	{
		f32 x, y, z;
		f32 speed = speedFactor * static_cast<EnemyParmsBase*>(mParms)->mGeneral.mMoveSpeed();
		x         = dolsinf(getFaceDir());
		y         = getTargetVelocity().y;
		z         = dolcosf(getFaceDir());

		mTargetVelocity = Vector3f(speed * x, y, speed * z);
	}

	inline void setTargetVelocity()
	{
		f32 x, y, z;
		f32 speed = static_cast<EnemyParmsBase*>(mParms)->mGeneral.mMoveSpeed();
		x         = dolsinf(getFaceDir());
		y         = getTargetVelocity().y;
		z         = dolcosf(getFaceDir());

		mTargetVelocity = Vector3f(speed * x, y, speed * z);
	}

	inline f32 getSquareDistanceTo2D(Creature* target, Vector3f& position)
	{
		f32 z       = position.z;
		f32 x       = position.x;
		f32 targetZ = target->getPosition().z;
		f32 targetX = target->getPosition().x;
		f32 diffZ   = targetZ - z;
		f32 diffX   = targetX - x;
		return SQUARE(diffX) + SQUARE(diffZ);
	}

	inline bool isCreatureIn2DRadius(f32 rad, Vector3f& pos)
	{
		Vector3f targetCreaturePos;
		targetCreaturePos.z = mTargetCreature->getPosition().z;
		targetCreaturePos.x = mTargetCreature->getPosition().x;
		return inRadius(rad, pos, targetCreaturePos);
	}

	inline bool isAlertLife() { return bool(mHealth < static_cast<EnemyParmsBase*>(mParms)->mGeneral.mLifeBeforeAlert); }

	inline bool isLongLegs()
	{
		return getEnemyTypeID() == EnemyTypeID::EnemyID_Damagumo || getEnemyTypeID() == EnemyTypeID::EnemyID_BigFoot
		    || getEnemyTypeID() == EnemyTypeID::EnemyID_Houdai;
	}

#pragma region Events
	inline void resetEvents()
	{
		mEvents.mFlags[0].clear();
		mEvents.mFlags[1].clear();
		mEventBuffer.mFlags[0].clear();
		mEventBuffer.mFlags[1].clear();
	}

	inline void restoreEvents()
	{
		mEvents.mFlags[0] = mEventBuffer.mFlags[0];
		mEvents.mFlags[1] = mEventBuffer.mFlags[1];
	}

	inline void backupEvents()
	{
		mEventBuffer.mFlags[0].typeView = mEvents.mFlags[0].typeView;
		mEventBuffer.mFlags[1].typeView = mEvents.mFlags[1].typeView;
	}

#pragma endregion

	inline bool isConstrained() { return (isEvent(0, EB_Constrained) || isEvent(0, EB_HardConstrained)); }

	// Creature: _000 - _178
	// MotionListener: _178 - _17C
	// ptr to PelletView: _17C
	EnemyMgrBase* mMgr;                         // _180
	EnemyAnimatorBase* mAnimator;               // _184
	EnemyAnimKeyEvent* mCurAnim;                // _188
	Vector3f mPosition;                         // _18C
	Vector3f mHomePosition;                     // _198
	Vector3f mRotation;                         // _1A4, mainly used for face dir on Y axis
	Vector3f mDamageAnimRotation;               // _1B0
	Vector3f mStunAnimRotation;                 // _1BC
	Vector3f mCurrentVelocity;                  // _1C8, impulse velocity
	Vector3f mTargetVelocity;                   // _1D4, simulation velocity (only used on simulation)
	BitFlagArray<u32, 2> mEvents;               // _1E0
	BitFlagArray<u32, 2> mEventBuffer;          // _1E8
	u8 mSfxEmotion;                             // _1F0, the 'emotion' used for bg music
	u8 mCreatureID;                             // _1F1
	u8 mUnused1F2;                              // _1F2, set to 0xFF by ctor/birth function, never used
	bool mInPiklopedia;                         // _1F3
	int mStuckPikminCount;                      // _1F4
	f32 mScaleModifier;                         // _1F8
	f32 mFaceDir;                               // _1FC
	f32 mHealth;                                // _200
	f32 mMaxHealth;                             // _204
	f32 mInstantDamage;                         // _208
	f32 mFlickTimer;                            // _20C,
	f32 mDamageAnimTimer;                       // _210, timer of the damage animation
	f32 mStunAnimTimer;                         // _214, timer of the stun animation
	f32 mFriction;                              // _218, related to mass
	f32 mBitterTimer;                           // _21C, timer of the bitter spray stone state
	Sys::Sphere mBoundingSphere;                // _220
	Creature* mTargetCreature;                  // _230
	CollEvent mCollEvent;                       // _234
	Vector3f mEffectOffset;                     // _240
	EnemyStone::Obj* mEnemyStoneObj;            // _24C
	PelletMgr::OtakaraItemCode mPelletDropCode; // _250
	Pellet* mHeldPellet;                        // _254
	EnemyPelletInfo mPelletInfo;                // _258
	AILODParm mLodParm;                         // _264
	Sys::Sphere mCurLodSphere;                  // _270
	WaterBox* mWaterBox;                        // _280
	EnemyEffectNodeHamon* mEffectNodeHamon;     // _284
	Sys::Triangle* mWallTriangle;               // _288
	PSM::EnemyBase* mSoundObj;                  // _28C
	CNode mHamonEffectRoot;                     // _290 - treat as EnemyEffectNodeBase with EnemyEffectNodeHamon nodes
	f32 mExistTimer;                            // _2A8, how long cherry-spawned enemy has existed in 2P battle
	f32 mExistDuration;                         // _2AC, how long cherry-spawned enemy should exist in 2P battle
	s8 mDropGroup;                              // _2B0, see DropGroup enum
	EnemyFSMState* mCurrentLifecycleState;      // _2B4
	EnemyBaseFSM::StateMachine* mLifecycleFSM;  // _2B8
	                                            // PelletView: _2BC - _2C8
};

struct EarthquakeStateArg : public StateArg {
	f32 mBounceFactor; // _00, weighting to scale vertical velocity by
};

namespace EnemyBaseFSM {
enum StateID {
	EBS_Drop           = 0,
	EBS_DropPikmin     = 1,
	EBS_DropOlimar     = 2,
	EBS_DropTreasure   = 3,
	EBS_DropEarthquake = 4,
	EBS_Appear         = 5,
	EBS_Living         = 6,
	EBS_Stone          = 7,
	EBS_Earthquake     = 8,
	EBS_Fit            = 9,
	EBS_Count, // 10
};

/**
 * Generic lifecycle state.
 */
struct State : public Game::EnemyFSMState {
	inline State(int stateID)
	    : EnemyFSMState(stateID)
	{
	}

	virtual void update(EnemyBase*) { }                          // _24 (weak)
	virtual void entry(EnemyBase*) { }                           // _28 (weak)
	virtual void simulation(EnemyBase*, f32) { }                 // _2C (weak)
	virtual void bounceProcedure(EnemyBase*, Sys::Triangle*) { } // _30 (weak)
	virtual void animation(EnemyBase*);                          // _34

	// _00 VTBL
	// _04 int stateID
	// _08 EnemyStateMachine* mStateMachine
	// _0C const char* mName
};

/**
 * Generic birth-by-dropping state.
 */
struct BirthTypeDropState : public State {
	inline BirthTypeDropState(int stateID)
	    : State(stateID)
	{
		mName = "BirthTypeDrop";
	}

	virtual void init(EnemyBase* enemy, StateArg* settings);   // _08
	virtual void cleanup(EnemyBase* enemy);                    // _10
	virtual void update(EnemyBase*);                           // _24
	virtual void entry(EnemyBase*) { }                         // _28 (weak)
	virtual void simulation(EnemyBase*, f32) { }               // _2C (weak)
	virtual void animation(EnemyBase*) { }                     // _34 (weak)
	virtual bool isFinishableWaitingBirthTypeDrop(EnemyBase*); // _38
};

struct BirthTypeDropPikminState : public BirthTypeDropState {
	inline BirthTypeDropPikminState()
	    : BirthTypeDropState(EBS_DropPikmin)
	{
		mName = "BirthTypeDropPikmin";
	}

	virtual bool isFinishableWaitingBirthTypeDrop(EnemyBase*); // _38
};

struct BirthTypeDropOlimarState : public BirthTypeDropState {
	inline BirthTypeDropOlimarState()
	    : BirthTypeDropState(EBS_DropOlimar)
	{
		mName = "BirthTypeDropOlimar";
	}

	virtual bool isFinishableWaitingBirthTypeDrop(EnemyBase*); // _38
};

struct BirthTypeDropTreasureState : public BirthTypeDropState {
	inline BirthTypeDropTreasureState()
	    : BirthTypeDropState(EBS_DropTreasure)
	{
		mName = "BirthTypeDropTreasure";
	}

	virtual bool isFinishableWaitingBirthTypeDrop(EnemyBase*); // _38
};

struct BirthTypeDropEarthquakeState : public BirthTypeDropState {
	inline BirthTypeDropEarthquakeState()
	    : BirthTypeDropState(EBS_DropEarthquake)
	{
		mName = "BirthTypeDropEarthquake";
	}

	virtual bool isFinishableWaitingBirthTypeDrop(EnemyBase*); // _38
};

/**
 * Birth-without-dropping state?
 */
struct AppearState : public State {
	inline AppearState()
	    : State(EBS_Appear)
	{
		mName = "Appear";
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void cleanup(EnemyBase* enemy);                  // _10
	virtual void update(EnemyBase*);                         // _24
	virtual void entry(EnemyBase*);                          // _28
	virtual void simulation(EnemyBase*, f32) { }             // _2C (weak)
};

/**
 * Generic "alive" state.
 * @size = 0x10
 */

struct LivingState : public State {
	inline LivingState(int state = EBS_Living)
	    : State(state)
	{
		mName = "Living";
	}

	inline bool isConstrained(EnemyBase* enemy) { return (enemy->isEvent(0, EB_Constrained) || enemy->isEvent(0, EB_HardConstrained)); }

	virtual void update(EnemyBase*);           // _24
	virtual void entry(EnemyBase*);            // _28
	virtual void simulation(EnemyBase*, f32);  // _2C
	virtual void updateCullingOff(EnemyBase*); // _38
	virtual void updateAlways(EnemyBase*);     // _3C
};

/**
 * Bittered state.
 * @size = 0x10
 */
struct StoneState : public LivingState {
	inline StoneState()
	    : LivingState(EBS_Stone)
	{
		mName = "Stone";
	}

	virtual void init(EnemyBase* enemy, StateArg* settings);  // _08
	virtual void cleanup(EnemyBase* enemy);                   // _10
	virtual void bounceProcedure(EnemyBase*, Sys::Triangle*); // _30
	virtual void updateCullingOff(EnemyBase*);                // _38
	virtual void updateAlways(EnemyBase*);                    // _3C
};

/**
 * @size = 0x14
 */
struct EarthquakeState : public LivingState {
	inline EarthquakeState()
	    : LivingState(EBS_Earthquake)
	    , mEarthquakeStepTimer(0)
	{
		mName = "Earthquake";
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void cleanup(EnemyBase* enemy);                  // _10
	virtual void updateCullingOff(EnemyBase*);               // _38

	int mEarthquakeStepTimer; // _10
};

/**
 * @size = 0x24
 * FIT = Stunned
 */
struct FitState : public LivingState {
	inline FitState()
	    : LivingState(EBS_Fit)
	    , mEnemyPiyo()
	{
		mName = "Fit";
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void cleanup(EnemyBase* enemy);                  // _10
	virtual void updateCullingOff(EnemyBase*);               // _38
	virtual void updateAlways(EnemyBase*);                   // _3C

	efx::TEnemyPiyo mEnemyPiyo; // _10
};

/**
 * Generic lifecycle FSM that every teki has, often in addition to a more
 * specific FSM derived from Game::StateMachine.
 */
struct StateMachine : public Game::EnemyStateMachine {
	virtual void init(EnemyBase* enemy);            // _08
	virtual EnemyFSMState* getCurrState(EnemyBase*) // _1C (weak)
	{
		return mState;
	}
	virtual void setCurrState(EnemyBase* enemy, EnemyFSMState* state) // _20 (weak)
	{
		mState = static_cast<State*>(state);
	}
	virtual void update(EnemyBase*);          // _24
	virtual void entry(EnemyBase*);           // _28
	virtual void simulation(EnemyBase*, f32); // _2C
	virtual void animation(EnemyBase* enemy)  // _30 (weak)
	{
		mState->animation(enemy);
	}
	virtual void bounceProcedure(EnemyBase* enemy, Sys::Triangle* triangle) // _34 (weak)
	{
		mState->bounceProcedure(enemy, triangle);
	}

	State* mState; // _1C
};
} // namespace EnemyBaseFSM
} // namespace Game

// defined here to avoid include loop
namespace efx {
inline Arg::Arg(Game::EnemyBase* enemy) { mPosition = enemy->mPosition; }
} // namespace efx

#endif
