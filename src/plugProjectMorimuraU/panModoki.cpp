#include "Game/Entities/PanModoki.h"
#include "Game/Entities/OoPanModoki.h"
#include "Game/Entities/Nest.h"
#include "Game/EnemyFunc.h"
#include "Game/generalEnemyMgr.h"
#include "Game/CameraMgr.h"
#include "Game/rumble.h"
#include "Game/MapMgr.h"
#include "Game/routeMgr.h"
#include "Game/Stickers.h"
#include "Game/pathfinder.h"
#include "Dolphin/rand.h"
#include "efx/TPan.h"
#include "nans.h"

namespace Game {

/**
 * @note Address: 0x8034F5E0
 * @note Size: 0x70
 */
bool InteractSuckFinish::actEnemy(EnemyBase* enemy)
{
	switch (enemy->getEnemyTypeID()) {
	case EnemyTypeID::EnemyID_PanModoki:
	case EnemyTypeID::EnemyID_OoPanModoki:
		static_cast<PanModokiBase::Obj*>(enemy)->suckFinish();
		return true;
	default:
		return false;
	}
}

namespace PanModokiBase {

/**
 * @note Address: 0x8034F650
 * @note Size: 0x68
 */
void Obj::setParameters()
{
	EnemyBase::setParameters();
	Nest::Obj* nest = mNest;
	if (mNest) {
		nest->setScale(C_PROPERPARMS.mNestScale());
		mNest->mCollTree->mPart->setScale(C_PROPERPARMS.mNestScale());
	}
}

/**
 * @note Address: 0x8034F6B8
 * @note Size: 0x120
 */
void Obj::birth(Vector3f& position, f32 faceDirection)
{
	EnemyMgrBase* mgr;
	EnemyBase::birth(position, faceDirection);
	mgr = generalEnemyMgr->getEnemyMgr(EnemyTypeID::EnemyID_PanHouse);
	if (mgr) {
		EnemyBirthArg args;
		args.mPosition  = mPosition;
		args.mFaceDir   = getFaceDir();
		Nest::Obj* nest = static_cast<Nest::Obj*>(mgr->birth(args));
		P2ASSERTLINE(89, nest);
		if (nest) {
			nest->init(nullptr);
			mNest = nest;
			mNest->setHouseType(getEnemyTypeID());
			nest      = mNest;
			f32 scale = C_PROPERPARMS.mNestScale();
			nest->setScale(scale);
			mNest->mCollTree->mPart->setScale(scale);
		}
	}
}

/**
 * @note Address: 0x8034F7D8
 * @note Size: 0x1DC
 */
void Obj::onInit(CreatureInitArg* args)
{
	EnemyBase::onInit(args);
	disableEvent(0, EB_Cullable);
	disableEvent(0, EB_DamageAnimEnabled);
	mNextWayPointPosition = mHomePosition;
	mCarryDir             = mFaceDir;
	setEmotionNone();
	mFindNextRouteCounter = 0;
	mPrevCheckPosition    = mHomePosition;
	mCarryingYPosition    = mPosition.y;
	mMoveToWpTimer        = 0;
	_2E4                  = 1;
	mIsPathfinding        = false;
	mCanReactToPress      = 0;
	mMoveSpeedTimer       = 0;
	mWpIndex1             = 0;
	mWpIndex3             = 0;
	mWpIndex2             = 0;
	mPelletCarryVelocity  = 0.0f;
	mIsCarryStuck         = 0;

	mBodyJoint = mModel->getJoint("body");
	P2ASSERTLINE(137, mBodyJoint);

	mKamuJoint = mModel->getJoint("kamu");
	P2ASSERTLINE(140, mKamuJoint);

	mCarryingYPosition = mPosition.y;
	mFsm->start(this, PANMODOKI_Appear, nullptr);
	P2ASSERTLINE(145, mEfxSmoke);
	mEfxSmoke->mPosition = &mPosition;
	mHeldTreasureNum     = 0;
	for (int i = 0; i < PANMODOKI_MaxHeldTreasures; i++) {
		mHeldTreasures[i] = nullptr;
	}
}

/**
 * @note Address: 0x8034F9B4
 * @note Size: 0x2A0
 */
Obj::Obj()
    : mCarryDir(0.0f)
    , mBodyJoint(nullptr)
    , mKamuJoint(nullptr)
    , mEfxHide(nullptr)
    , mEfxSmoke(nullptr)
    , mCarrySizeDiff(20.0f)
    , mShadowSize(15.0f)
    , mUnusedVal(5.0f)
    , mBounceEffectSize(0.6f)
    , mAppearEffectSize(1.0f)
    , mNest(nullptr)
    , mFsm(nullptr)
    , mPathNode(nullptr)
    , mHeldTreasureNum(0)
{
	mAnimator = new ProperAnimator;
	setFSM(new FSM);
	mEfxHide  = new efx::TPanHide;
	mEfxSmoke = new efx::TPanSmoke(&mPosition);
}

/**
 * @note Address: 0x8034FC54
 * @note Size: 0x34
 */
void Obj::doUpdate() { mFsm->exec(this); }

/**
 * @note Address: 0x8034FC88
 * @note Size: 0xB4
 */
void Obj::doAnimation()
{
	Matrixf matrix;
	EnemyBase::doAnimation();
	if (!isEvent(0, EB_Bittered)) {
		int stateID = getStateID();
		if ((stateID == PANMODOKI_Hide || stateID == PANMODOKI_CarryEnd) && mTargetCreature) {
			updateCaptureMatrix();
		}
		if (mHeldTreasures[0] && mNest) {
			mHeldTreasures[0]->startCapture(&mNest->mHouseTrMatrix);
			Vector3f scale = Vector3f(0.1f);
			matrix.makeST(scale, Vector3f::zero);
			mHeldTreasures[0]->updateCapture(matrix);
		}
	}
}

/**
 * @note Address: 0x8034FD3C
 * @note Size: 0x318
 */
void Obj::doAnimationStick()
{
	Pellet* carryTarget = getCarryTarget();
	if (carryTarget && !carryTarget->mCaptureMatrix) {
		Vector3f yVec;
		carryTarget->getYVector(yVec);
		yVec.normalise();
		Vector3f faceVec = Vector3f(sin(mFaceDir), 0.0f, cos(mFaceDir));
		faceVec.normalise();
		Vector3f resVec;
		PSVECCrossProduct((Vec*)&yVec, (Vec*)&faceVec, (Vec*)&resVec);
		resVec.normalise();
		PSVECCrossProduct((Vec*)&resVec, (Vec*)&yVec, (Vec*)&faceVec);
		faceVec.normalise();

		mBaseTrMatrix.mMatrix.mtxView[0][0] = resVec.x;
		mBaseTrMatrix.mMatrix.mtxView[1][0] = resVec.y;
		mBaseTrMatrix.mMatrix.mtxView[2][0] = resVec.z;

		mBaseTrMatrix.mMatrix.mtxView[0][1] = yVec.x;
		mBaseTrMatrix.mMatrix.mtxView[1][1] = yVec.y;
		mBaseTrMatrix.mMatrix.mtxView[2][1] = yVec.z;

		mBaseTrMatrix.mMatrix.mtxView[0][2] = faceVec.x;
		mBaseTrMatrix.mMatrix.mtxView[1][2] = faceVec.y;
		mBaseTrMatrix.mMatrix.mtxView[2][2] = faceVec.z;

		mBaseTrMatrix.mMatrix.mtxView[0][3] = mPosition.x;
		mBaseTrMatrix.mMatrix.mtxView[1][3] = mPosition.y;
		mBaseTrMatrix.mMatrix.mtxView[2][3] = mPosition.z;
		return;
	}

	mBaseTrMatrix.makeSRT(mScale, mRotation, mPosition);
}

/**
 * @note Address: 0x80350054
 * @note Size: 0x27C
 */
void Obj::updateCaptureMatrix()
{
	Pellet* pellet = getCarryTarget();
	f32 result     = 0.0f;

	if (gameSystem && gameSystem->isVersusMode() && pellet && !isStickTo()) {
		releaseCarryTarget();
	}

	if (pellet->getKind() == PelletType::Carcass && !pellet->isAlive()) {
		releaseCarryTarget();
	}

	if (getCarryTarget()) {
		Matrixf* matrix = mKamuJoint->getWorldMatrix();

		Vector3f xVec;
		matrix->getColumn(0, xVec);
		Vector3f slotPos;
		calcSlotGlobalPos(slotPos);

		f32 dist = pellet->getSquarePositionTo(slotPos);
		// Vector3f pelletPos1(pellet->getPosition().x, 0.0f, pellet->getPosition().z);
		// Vector3f diff = slotPos - pelletPos1;
		// diff.y        = 0.0f;
		f32 dist2D = 0.0f;
		if (dist > dist2D) {
			dist2D = pellet->getPositionTo(slotPos);
			// f32 z = pellet->getPosition().z;
			// f32 x = pellet->getPosition().x;
			// f32 slotX = slotPos.x;
			// f32 slotZ = slotPos.z;
			// f32 diffX = slotX - x;
			// f32 diffZ = slotZ - z;
			// dist2D = diffX * diffX + diffZ * diffZ;
			// sqrtf(dist2D);
			// dist2D =
			// THIS has to be an inline
			// diff2D.y        = 0.0f;
			// dist2D          = diff2D.length2D();
		}

		f32 pelletZ = mCarrySizeDiff * 0.2f + dist2D;
		matrix      = mKamuJoint->getWorldMatrix();
		PSMTXCopy(matrix->mMatrix.mtxView, mCarryMatrix.mMatrix.mtxView);
		mCarryMatrix.mMatrix.structView.tx += (f32)(xVec.x * pelletZ);
		mCarryMatrix.mMatrix.structView.ty += (f32)(xVec.y * pelletZ);
		mCarryMatrix.mMatrix.structView.tz += (f32)(xVec.z * pelletZ);
		pellet->startCapture(&mCarryMatrix);
		Vector3f rot(0.0f, HALF_PI - mAlsoRotationOffset, PI);

		Matrixf matTr;
		matTr.makeTR(Vector3f::zero, rot);
		pellet->updateCapture(matTr);
	}
	/*
	stwu     r1, -0xd0(r1)
	mflr     r0
	stw      r0, 0xd4(r1)
	stfd     f31, 0xc0(r1)
	psq_st   f31, 200(r1), 0, qr0
	stfd     f30, 0xb0(r1)
	psq_st   f30, 184(r1), 0, qr0
	stfd     f29, 0xa0(r1)
	psq_st   f29, 168(r1), 0, qr0
	stfd     f28, 0x90(r1)
	psq_st   f28, 152(r1), 0, qr0
	stw      r31, 0x8c(r1)
	stw      r30, 0x88(r1)
	mr       r30, r3
	bl       getCarryTarget__Q34Game13PanModokiBase3ObjFv
	lwz      r4, gameSystem__4Game@sda21(r13)
	mr       r31, r3
	cmplwi   r4, 0
	beq      lbl_803500CC
	lwz      r0, 0x44(r4)
	cmpwi    r0, 1
	bne      lbl_803500CC
	cmplwi   r31, 0
	beq      lbl_803500CC
	mr       r3, r30
	bl       isStickTo__Q24Game8CreatureFv
	clrlwi.  r0, r3, 0x18
	bne      lbl_803500CC
	mr       r3, r30
	bl       releaseCarryTarget__Q34Game13PanModokiBase3ObjFv

lbl_803500CC:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x1f4(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	cmplwi   r0, 1
	bne      lbl_80350110
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0xa8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80350110
	mr       r3, r30
	bl       releaseCarryTarget__Q34Game13PanModokiBase3ObjFv

lbl_80350110:
	mr       r3, r30
	bl       getCarryTarget__Q34Game13PanModokiBase3ObjFv
	cmplwi   r3, 0
	beq      lbl_80350298
	lwz      r3, 0x2d8(r30)
	bl       getWorldMatrix__Q28SysShape5JointFv
	lfs      f31, 0(r3)
	addi     r4, r1, 0x44
	lfs      f30, 0x10(r3)
	lfs      f29, 0x20(r3)
	mr       r3, r30
	bl       "calcSlotGlobalPos__Q34Game13PanModokiBase3ObjFR10Vector3<f>"
	mr       r4, r31
	addi     r3, r1, 0x20
	lwz      r12, 0(r31)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	mr       r4, r31
	addi     r3, r1, 0x2c
	lwz      r12, 0(r31)
	lfs      f28, 0x28(r1)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f0, 0x4c(r1)
	lfs      f2, 0x2c(r1)
	fsubs    f1, f0, f28
	lfs      f0, 0x44(r1)
	lfs      f3, lbl_8051E490@sda21(r2)
	fsubs    f2, f0, f2
	fmuls    f0, f1, f1
	fmadds   f0, f2, f2, f0
	fcmpo    cr0, f0, f3
	ble      lbl_80350200
	mr       r4, r31
	addi     r3, r1, 0x14
	lwz      r12, 0(r31)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	mr       r4, r31
	addi     r3, r1, 8
	lwz      r12, 0(r31)
	lfs      f28, 0x1c(r1)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f0, 0x4c(r1)
	lfs      f3, 8(r1)
	fsubs    f2, f0, f28
	lfs      f1, 0x44(r1)
	lfs      f0, lbl_8051E490@sda21(r2)
	fsubs    f3, f1, f3
	fmuls    f1, f2, f2
	fmadds   f3, f3, f3, f1
	fcmpo    cr0, f3, f0
	ble      lbl_80350200
	frsqrte  f0, f3
	fmuls    f3, f0, f3

lbl_80350200:
	lfs      f1, lbl_8051E4BC@sda21(r2)
	lfs      f0, 0x32c(r30)
	lwz      r3, 0x2d8(r30)
	fmadds   f28, f1, f0, f3
	bl       getWorldMatrix__Q28SysShape5JointFv
	addi     r4, r30, 0x348
	bl       PSMTXCopy
	fmuls    f2, f31, f28
	lfs      f3, 0x354(r30)
	fmuls    f1, f30, f28
	mr       r3, r31
	fmuls    f0, f29, f28
	addi     r4, r30, 0x348
	fadds    f2, f3, f2
	stfs     f2, 0x354(r30)
	lfs      f2, 0x364(r30)
	fadds    f1, f2, f1
	stfs     f1, 0x364(r30)
	lfs      f1, 0x374(r30)
	fadds    f0, f1, f0
	stfs     f0, 0x374(r30)
	bl       startCapture__Q24Game8CreatureFP7Matrixf
	lfs      f2, lbl_8051E4C0@sda21(r2)
	lis      r3, "zero__10Vector3<f>"@ha
	lfs      f0, 0x2e0(r30)
	addi     r4, r3, "zero__10Vector3<f>"@l
	lfs      f1, lbl_8051E490@sda21(r2)
	addi     r3, r1, 0x50
	fsubs    f2, f2, f0
	lfs      f0, lbl_8051E4C4@sda21(r2)
	stfs     f1, 0x38(r1)
	addi     r5, r1, 0x38
	stfs     f2, 0x3c(r1)
	stfs     f0, 0x40(r1)
	bl       "makeTR__7MatrixfFR10Vector3<f>R10Vector3<f>"
	mr       r3, r31
	addi     r4, r1, 0x50
	bl       updateCapture__Q24Game8CreatureFR7Matrixf

lbl_80350298:
	psq_l    f31, 200(r1), 0, qr0
	lfd      f31, 0xc0(r1)
	psq_l    f30, 184(r1), 0, qr0
	lfd      f30, 0xb0(r1)
	psq_l    f29, 168(r1), 0, qr0
	lfd      f29, 0xa0(r1)
	psq_l    f28, 152(r1), 0, qr0
	lfd      f28, 0x90(r1)
	lwz      r31, 0x8c(r1)
	lwz      r0, 0xd4(r1)
	lwz      r30, 0x88(r1)
	mtlr     r0
	addi     r1, r1, 0xd0
	blr
	*/
}

/**
 * @note Address: 0x803502D0
 * @note Size: 0x4
 */
void Obj::doDirectDraw(Graphics&) { }

/**
 * @note Address: 0x803502D4
 * @note Size: 0x20
 */
void Obj::doDebugDraw(Graphics& graphics) { EnemyBase::doDebugDraw(graphics); }

/**
 * @note Address: 0x803502F4
 * @note Size: 0x30
 */
bool Obj::damageCallBack(Creature* source, f32 damage, CollPart* part)
{
	if (isEvent(0, EB_Bittered)) {
		EnemyBase::damageCallBack(source, damage, part);
	}
	return false;
}

/**
 * @note Address: 0x80350324
 * @note Size: 0x1BC
 */
bool Obj::pressCallBack(Creature* creature, f32 damage, CollPart* part)
{
	if (mHealth <= 0.0f) {
		return false;
	}
	if (creature && creature->isPiki()) {
		if (!isEvent(0, EB_Bittered)) {
			if (C_PARMS->mCanPressType && isFinishMotion()) {
				return false;
			}

			switch (getStateID()) {
			case PANMODOKI_Walk:
			case PANMODOKI_Wait:
			case PANMODOKI_Stick:
				// these have to be zero'd by component to stop this inlining in OoPanModoki::Obj::pressCallBack lol.
				mCurrentVelocity.x = 0.0f;
				mCurrentVelocity.y = 0.0f;
				mCurrentVelocity.z = 0.0f;
				mTargetVelocity.x  = 0.0f;
				mTargetVelocity.y  = 0.0f;
				mTargetVelocity.z  = 0.0f;
				mCanReactToPress   = 0;
				if (C_PARMS->mCanPressType) {
					EnemyBase::finishMotion();
					mNextState = PANMODOKI_Damage;
				} else {
					mFsm->transit(this, PANMODOKI_Damage, nullptr);
				}
				return true;

			case PANMODOKI_Back:
			case PANMODOKI_Pulled:
				// these have to be zero'd by component to stop this inlining in OoPanModoki::Obj::pressCallBack lol.
				mCurrentVelocity.x = 0.0f;
				mCurrentVelocity.y = 0.0f;
				mCurrentVelocity.z = 0.0f;
				mTargetVelocity.x  = 0.0f;
				mTargetVelocity.y  = 0.0f;
				mTargetVelocity.z  = 0.0f;
				mCanReactToPress   = 0;
				if (C_PARMS->mCanPressType) {
					EnemyBase::finishMotion();
					mNextState = PANMODOKI_Damage;
				} else {
					mFsm->transit(this, PANMODOKI_Damage, nullptr);
				}
				return true;
			}
		}
		return false;
	}
	return false;
}

/**
 * @note Address: 0x803504E0
 * @note Size: 0x2C
 */
bool Obj::hipdropCallBack(Creature* source, f32 damage, CollPart* part) { pressCallBack(source, damage, part); }

/**
 * @note Address: 0x8035050C
 * @note Size: 0xAC
 */
void Obj::collisionCallback(CollEvent& event)
{
	Creature* source;
	source = event.mCollidingCreature;
	if (source && source->isTeki()
	    && static_cast<EnemyBase*>(event.mCollidingCreature)->getEnemyTypeID() == EnemyTypeID::EnemyID_PanHouse) {
		mAcceleration = Vector3f(0.0f);
	}
	if (isEvent(0, EB_Bittered)) {
		mAcceleration = Vector3f(0.0f);
	}
	EnemyBase::collisionCallback(event);
}

/**
 * @note Address: 0x803505B8
 * @note Size: 0x44
 */
void Obj::outWaterCallback()
{
	EnemyBase::outWaterCallback();
	if (getStateID() == PANMODOKI_Pulled) {
		createPulledSmokeEffect();
	}
}

/**
 * @note Address: 0x803505FC
 * @note Size: 0x34
 */
void Obj::inWaterCallback(WaterBox* waterbox)
{
	EnemyBase::inWaterCallback(waterbox);
	fadePulledSmokeEffect();
}

/**
 * @note Address: 0x80350630
 * @note Size: 0x54
 */
void Obj::bounceCallback(Sys::Triangle* triangle)
{
	if (getStateID() == PANMODOKI_Sucked) {
		mFsm->transit(this, PANMODOKI_Damage, nullptr);
	}
}

/**
 * @note Address: 0x80350684
 * @note Size: 0x50
 */
void Obj::damageRumble()
{
	cameraMgr->startVibration(VIBTYPE_LightMidShort, mPosition, CAMNAVI_Both);
	rumbleMgr->startRumble(RUMBLETYPE_Fixed11, mPosition, RUMBLEID_Both);
}

/**
 * @note Address: 0x803506D4
 * @note Size: 0x21C
 */
void Obj::doSimulation(f32 simspeed)
{
	if (isStickTo()) {
		mAcceleration = Vector3f(0.0f);
	}

	mFindNextRouteCounter -= 1;
	if (mFindNextRouteCounter < 0) {
		mFindNextRouteCounter = 0;
	}
	EnemyBase::doSimulation(simspeed);
	EnemyBase::getStateID();
	if (EnemyBase::isCullingOff() && isStickTo()) {
		if (!isConstrained() && getCarryTarget()) {
			Vector3f slotPos;
			calcSlotGlobalPos(slotPos);
			Vector3f dir = getDirection(mFaceDir);
			slotPos.x -= dir.x * mCarrySizeDiff;
			slotPos.z -= dir.z * mCarrySizeDiff;
			Vector3f pos = slotPos;
			pos.y += 20.0f;
			f32 minY           = mapMgr->getMinY(pos);
			mCarryingYPosition = minY;
			f32 realY          = slotPos.y - C_PARMS->_99C;
			if (minY < realY) {
				minY = realY;
			}
			if (slotPos.y < mCarryingYPosition) {
				minY = (slotPos.y + mCarryingYPosition) * 0.5f;
			}
			slotPos.y          = minY;
			mCarryingYPosition = minY;
			mPosition          = slotPos;
		}
	}
}

/**
 * @note Address: 0x803508F0
 * @note Size: 0x88
 */
void Obj::getShadowParam(ShadowParam& shadowParam)
{
	mBodyJoint->getWorldMatrix()->getTranslation(shadowParam.mPosition);
	shadowParam.mPosition.y               = 2.0f + mPosition.y;
	shadowParam.mBoundingSphere.mPosition = Vector3f(0.0f, 1.0f, 0.0f);
	shadowParam.mBoundingSphere.mRadius   = 50.0f;
	shadowParam.mSize                     = mShadowSize;
}

/**
 * @note Address: 0x80350978
 * @note Size: 0x58
 */
bool Obj::needShadow()
{
	bool result;
	if (!EnemyBase::needShadow()) {
		result = false;
	} else {
		result = false;
		if (!isEvent(0, EB_Constrained) && !isEvent(0, EB_HardConstrained)) {
			result = true;
		}
	}
	return result;
}

/**
 * @note Address: 0x803509D0
 * @note Size: 0x28
 */
void Obj::startCarcassMotion() { EnemyBase::startMotion(PANMODOKIANIM_Carry, nullptr); }

/**
 * @note Address: 0x803509F8
 * @note Size: 0x8C
 */
void Obj::initMouthSlots()
{
	MouthCollPart* mouthCollPart;
	mMouthSlots.alloc(1);
	mMouthSlots.setup(0, mModel, "kamu");
	for (int i = 0; i < mMouthSlots.mMax; i++) {
		mouthCollPart          = mMouthSlots.getSlot(i);
		mouthCollPart->mRadius = 30.0f;
	}
}

/**
 * @note Address: 0x80350A84
 * @note Size: 0x44
 */
void Obj::onKill(CreatureKillArg* settings)
{
	EnemyBase::onKill(settings);
	throwUpEatItem();
	releasePathFinder();
	killNest();
}

/**
 * @note Address: 0x80350AC8
 * @note Size: 0x50
 */
void Obj::doStartMovie()
{
	mEfxHide->startDemoDrawOff();
	mEfxSmoke->startDemoDrawOff();
}

/**
 * @note Address: 0x80350B18
 * @note Size: 0x50
 */
void Obj::doEndMovie()
{
	mEfxHide->endDemoDrawOn();
	mEfxSmoke->endDemoDrawOn();
}

/**
 * @note Address: 0x80350B68
 * @note Size: 0x54
 */
void Obj::doStartStoneState()
{
	EnemyBase::doStartStoneState();
	mCollTree->getCollPart('body')->mSpecialID = 'st__';
	releaseCarryTarget();
}

/**
 * @note Address: 0x80350BBC
 * @note Size: 0xAC
 */
void Obj::doFinishStoneState()
{
	EnemyBase::doFinishStoneState();
	mCollTree->getCollPart('body')->mSpecialID = '____';
	EnemyFunc::flickStickPikmin(this, C_GENERALPARMS.mShakeChance.mValue, C_GENERALPARMS.mShakeKnockback.mValue,
	                            C_GENERALPARMS.mShakeDamage.mValue, -1000.0, nullptr);
	mFlickTimer = 0.0f;
	int stateID = getStateID();
	if (stateID == PANMODOKI_Pulled || stateID == PANMODOKI_Back) {
		mFsm->transit(this, PANMODOKI_Wait, nullptr);
	}
}

/**
 * @note Address: 0x80350C68
 * @note Size: 0x64
 */
void Obj::initWalkSmokeEffect()
{
	mWalkSmokeMgr.alloc(2);
	mWalkSmokeMgr.setup(0, mModel, "asiL", 2.0f);
	mWalkSmokeMgr.setup(1, mModel, "asiR", 2.0f);
}

/**
 * @note Address: 0x80350CCC
 * @note Size: 0x8
 */
WalkSmokeEffect::Mgr* Obj::getWalkSmokeEffectMgr() { return &mWalkSmokeMgr; }

/**
 * @note Address: 0x80350CD4
 * @note Size: 0x4B4
 */
void Obj::findNextRoutePoint(bool cond)
{
	RouteMgr* routeMgr = mapMgr->mRouteMgr;
	mIsCarryStuck      = 0;
	if (mFindNextRouteCounter > 0 && cond) {
		if (mWpIndex3 == mWpIndex2 && mWpIndex2 == mWpIndex1) {
			mNextWayPointPosition = mHomePosition;
			return;
		}
		WPEdgeSearchArg args(mPosition);
		if (routeMgr->getNearestEdge(args)) {
			s16 wpID1 = mWpIndex2;
			s16 wpID2 = mWpIndex3;
			if (!(args.mWp1->isFlag(WPF_Closed))) {
				if (routeMgr->getWayPoint(args.mWp1->mIndex)->mNumFromLinks == 1 && !(args.mWp2->isFlag(WPF_Closed))) {
					mWpIndex3 = mWpIndex2;
					mWpIndex2 = args.mWp2->mIndex;
				} else {
					mWpIndex2 = args.mWp1->mIndex;
					if (routeMgr->getWayPoint(args.mWp2->mIndex)->mNumFromLinks > 1 && !(args.mWp2->mFlags & 1)) {
						mWpIndex3 = args.mWp2->mIndex;
					} else {
						mWpIndex3 = mWpIndex2;
					}
				}
			} else {
				mWpIndex2 = args.mWp2->mIndex;
				if (routeMgr->getWayPoint(args.mWp1->mIndex)->mNumFromLinks > 1 && !(args.mWp1->mFlags & 1)) {
					mWpIndex3 = args.mWp1->mIndex;
				} else {
					mWpIndex3 = mWpIndex2;
				}
			}
			if (mWpIndex2 == wpID1 && mWpIndex3 == wpID2) {
				mNextWayPointPosition   = mPosition;
				mNextWayPointPosition.x = -(sinf(mFaceDir) * 100.0f - mNextWayPointPosition.x);
				mNextWayPointPosition.z = -(cosf(mFaceDir) * 100.0f - mNextWayPointPosition.z);
				return;
			}

			mNextWayPointPosition = Vector3f(routeMgr->getWayPoint(mWpIndex2)->mPosition);
			return;
		}
	}

	WayPoint* wp2 = routeMgr->getWayPoint(mWpIndex2);
	P2ASSERTLINE(993, wp2);
	s16 idxArray[8];
	int counter = 0;

	WayPointIterator iter(wp2, true);
	CI_LOOP(iter)
	{
		s16 currIdx      = *iter;
		WayPoint* currWP = routeMgr->getWayPoint(currIdx);
		if (currWP && !currWP->isFlag(WPF_Closed) && currWP->mNumToLinks + currWP->mNumFromLinks > 1) {
			idxArray[counter] = currIdx;
			counter++;
		}
	}
	if (counter != 0) {
		int randIdx = randInt(counter);
		if (randIdx >= counter) {
			randIdx = counter - 1;
		}
		s16 idx = idxArray[randIdx];
		routeMgr->getWayPoint(idx);
		if (counter == 1 || idx != mWpIndex3) {
			mWpIndex3 = mWpIndex2;
			mWpIndex2 = idx;
		}
	}
	WayPoint* nextWP = routeMgr->getWayPoint(mWpIndex2);
	if (nextWP) {
		mNextWayPointPosition = Vector3f(nextWP->mPosition);
	}
}

/**
 * @note Address: 0x80351188
 * @note Size: 0x274
 */
bool Obj::isCarryToGoal()
{
	if (!mIsPathfinding) {
		return false;
	}

	f32 homeRadius = C_GENERALPARMS.mHomeRadius.mValue;
	if (mMoveSpeedTimer > 100) {
		homeRadius = 60.0f;
	}
	homeRadius *= homeRadius;

	Vector3f pos = mPosition;
	if (sqrDistanceXZ(pos, mHomePosition) < homeRadius) {
		releasePathFinder();
		return true;
	}
	f32 rad2 = 30.0f;
	f32 rad3 = 50.0f;
	if (mMoveSpeedTimer > 100) {
		rad2 = 60.0f;
		rad3 = 75.0f;
	}
	rad2 *= rad2;
	rad3 *= rad3;

	f32 sqrDist      = pos.sqrDistance2D(mNextWayPointPosition);
	Creature* pellet = getCarryTarget();
	f32 something    = -1.0f;

	// this is so a pellet inline.
	if (pellet) {
		something = getSquareDistanceTo2D(pellet, mNextWayPointPosition);
	}
	if ((sqrDist < rad2) || (something > 0.0f && (something < rad3))) {
		mMoveSpeedTimer = 0;
		s16 something2  = mWpIndex2;
		if (something2 == mWpIndex1) {
			mNextWayPointPosition = mHomePosition;
			if (something < rad3) {
				return true;
			}
		} else {
			for (PathNode* path = mPathNode; path; path = path->mNext) {
				if (path->mWpIndex == something2) {
					mWpIndex3 = something2;
					if (path->mNext) {
						mWpIndex2 = path->mNext->mWpIndex;
					} else {
						mWpIndex2 = mWpIndex1;
					}
					WayPoint* currWP      = mapMgr->mRouteMgr->getWayPoint(mWpIndex2);
					mNextWayPointPosition = Vector3f(currWP->mPosition);
					return false;
				}
			}
		}
	}
	return false;
}

/**
 * @note Address: 0x803513FC
 * @note Size: 0x2CC
 */
void Obj::walkFunc()
{
	f32 moveSpeed = C_GENERALPARMS.mMoveSpeed.mValue;
	f32 rotSpeed  = C_GENERALPARMS.mMaxTurnAngle.mValue;
	f32 rotAccel  = C_GENERALPARMS.mTurnSpeed.mValue;
	f32 something = 100.0f;
	if (getEnemyTypeID() == EnemyTypeID::EnemyID_OoPanModoki) {
		something = 150.0f;
	}

	if (absF(mNextWayPointPosition.x - mPosition.x) < something && absF(mNextWayPointPosition.z - mPosition.z) < something) {
		mMoveSpeedTimer += 1;
		if (100 < mMoveSpeedTimer) {
			moveSpeed *= 0.5f;
		}
		if (200 < mMoveSpeedTimer) {
			mMoveSpeedTimer = 0;
		}
	} else {
		mMoveSpeedTimer = 0;
	}

	if (!mFindNextRouteCounter) {
		mTargetCreature = static_cast<Creature*>(findNearestPellet());
		if (mTargetCreature) {
			mNextWayPointPosition = mTargetCreature->getPosition();
		}
	} else {
		rotSpeed = C_PROPERPARMS.mMaxFastTurnAngle.mValue;
		rotAccel = C_PROPERPARMS.mFastTurnSpeed.mValue;
	}
	EnemyFunc::walkToTarget(this, mNextWayPointPosition, moveSpeed, rotAccel, rotSpeed);
	if (mFloorTriangle) {
		f32 collPos = mFloorNormal.x;
		f32 ten     = 10.0f;
		if (collPos > 0.1f) {
			mPelletCarryVelocity.x = -ten;
		} else if (collPos < -0.1f) {
			mPelletCarryVelocity.x = ten;
		} else {
			mPelletCarryVelocity.x *= 0.9f;
		}
		mCurrentVelocity.x += mPelletCarryVelocity.x;
		f32 collPosZ = mFloorNormal.z;
		if (collPosZ > 0.1f) {
			mPelletCarryVelocity.z = -ten;
		} else if (collPosZ < -0.1f) {
			mPelletCarryVelocity.z = ten;
		} else {
			mPelletCarryVelocity.z *= 0.9f;
		}
		mCurrentVelocity.z += mPelletCarryVelocity.z;
	}

	if (!mFindNextRouteCounter) {
		mMoveToWpTimer++;
		if (mMoveToWpTimer > 0x3c) {
			f32 posZCross = mPosition.z - mPrevCheckPosition.z;
			f32 posXCross = mPosition.x - mPrevCheckPosition.x;
			if (((posXCross * posXCross) + (posZCross * posZCross)) < 100.0f) {
				mFindNextRouteCounter = 0x78;
				mTargetCreature       = nullptr;
				findNextRoutePoint(true);
			}
			mPrevCheckPosition = mPosition;
			mMoveToWpTimer     = 0;
		}
	}
}

/**
 * @note Address: 0x803516C8
 * @note Size: 0x184
 */
bool Obj::isReachToGoal(f32 radius)
{
	if (isDead()) {
		return false;
	}

	Creature* creature = mTargetCreature;
	if (creature) {
		P2ASSERTLINE(1200, creature);
		radius += static_cast<Pellet*>(creature)->mConfig->mParams.mRadius.mData;
	} else {
		radius *= 2.0f;
	}

	if (inRadius(radius, mPosition, mNextWayPointPosition)) {
		if (getStateID() == PANMODOKI_Walk && mTargetCreature) {
			if (isCreatureIn2DRadius(radius, mPosition)) {
				mFsm->transit(this, PANMODOKI_Stick, nullptr);
			}
		}
		mMoveSpeedTimer = 0;
		return true;
	}
	return false;
}

/**
 * @note Address: 0x8035184C
 * @note Size: 0x74
 */
bool Obj::canBack()
{
	bool result;
	Pellet* pellet = getCarryTarget();
	if (!pellet) {
		return false;
	}

	result = getCarryTarget()->mPelletCarry->pullable(2, mCarryStrength);
	getEnemyTypeID(); // ???

	return result;
}

/**
 * @note Address: 0x803518C0
 * @note Size: 0x344
 */
Pellet* Obj::findNearestPellet()
{
	Pellet* resPellet = nullptr;
	f32 minDist;
	f32 maxAngle   = TORADIANS(C_GENERALPARMS.mSearchAngle());
	f32 searchDist = C_GENERALPARMS.mSearchDistance();
	if (searchDist < 0.0f) {
		searchDist = FLT_MAX;
	} else {
		searchDist *= searchDist;
	}
	minDist = searchDist;
	PelletIterator iterator;
	CI_LOOP(iterator)
	{
		Pellet* pelt = *iterator;
		if (pelt->isPickable() && pelt->isAlive() && pelt->getKind() != PelletType::Upgrade && pelt->mCaptureMatrix == nullptr
		    && isTargetable(pelt) && canTarget(pelt->mConfig->mParams.mMin.mData, C_PROPERPARMS.mMaxCarryWeight.mValue)) {
			f32 y = pelt->getPosition().y - 0.5f * pelt->getCylinderHeight();
			if (absF(y - mPosition.y) > 10.0f) {
				continue;
			}
			f32 angle = getCreatureViewAngle(pelt);
			if (absF(angle) <= maxAngle) {
				s32 id = pelt->getCreatureID();
				if (pelt->getKind() == PelletType::Carcass && (id == 0 || id == 1)) {
					if (strcmp("orima", pelt->getCreatureName()) == 0) {
						continue;
					}
				}
				Vector3f pelPos2 = pelt->getPosition();
				f32 dist         = sqrDistanceXZ(mPosition, pelPos2);
				if (dist < minDist) {
					resPellet = pelt;
					minDist   = dist;
				}
			}
		}
	}

	return resPellet;
}

/**
 * @note Address: 0x80351C04
 * @note Size: 0x68
 */
Pellet* Obj::getCarryTarget()
{
	Creature* pellet = mTargetCreature;
	if (!mTargetCreature) {
		return nullptr;
	}

	if (pellet->isTeki()) {
		return static_cast<EnemyBase*>(mTargetCreature)->mPellet;
	}

	return static_cast<Pellet*>(mTargetCreature);
}

/**
 * @note Address: 0x80351C6C
 * @note Size: 0x1E4
 */
void Obj::releaseCarryTarget()
{
	Pellet* pellet = getCarryTarget();
	if (pellet) {
		if (getStateID() == PANMODOKI_Back) {
			Vector3f targetVel = pellet->getVelocity();
			targetVel.x        = -targetVel.x;
			targetVel.z        = -targetVel.z;
			pellet->setVelocity(targetVel);
		} else if (pellet->mCaptureMatrix) {
			pellet->endCapture();
			Vector3f targetVel = getDirection(mFaceDir);
			targetVel.x *= 50.0f;
			targetVel.y = 100.0f;
			targetVel.z *= 50.0f;
			pellet->setVelocity(targetVel);
		}
		endStick();
		pellet->mPelletCarry->giveup(2);
	}
	mTargetCreature = nullptr;
}

/**
 * @note Address: 0x80351E50
 * @note Size: 0x284
 */
void Obj::checkNearHomeGraphIndex()
{
	WPSearchArg searchArgs(mPosition, nullptr, 0, 10.0f);
	RouteMgr* route  = mapMgr->mRouteMgr;
	WayPoint* nearWP = route->getNearestWayPoint(searchArgs);
	JUT_ASSERTLINE(1369, nearWP, "P2Assert");
	s16 index = nearWP->mIndex;
	mWpIndex1 = index;
	mWpIndex3 = index;
	mWpIndex2 = index;
	nearWP    = route->getWayPoint(mWpIndex2);
	JUT_ASSERTLINE(1374, nearWP, "P2Assert");
	mNextWayPointPosition = Vector3f(nearWP->mPosition);
	WPEdgeSearchArg edgeSearchArgs(mPosition);
	if (route->getNearestEdge(edgeSearchArgs)) {
		s16 idx = (int)edgeSearchArgs.mWp1->mIndex; // required to match smh
		if (edgeSearchArgs.mWp1->isFlag(WPF_Closed)) {
			idx = edgeSearchArgs.mWp2->mIndex;
		}
		mWpIndex1             = idx;
		mWpIndex3             = idx;
		mWpIndex2             = idx;
		nearWP                = route->getWayPoint(mWpIndex2);
		mNextWayPointPosition = Vector3f(nearWP->mPosition);
	}
	f32 turnSpeed    = 1.0f;
	f32 maxTurnSpeed = 360.0f; // this ends up as tau via the inline lol
	turnToTarget2(mNextWayPointPosition, turnSpeed, maxTurnSpeed);
}

/**
 * @note Address: N/A
 * @note Size: 0xD0
 */
void Obj::clearCarryVelocity()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: 0x803520D4
 * @note Size: 0x518
 */
bool Obj::carryTarget(f32 param)
{
	f32 turnSpeed, maxTurnAngle, speed;
	speed        = param * CG_PROPERPARMS(this).mCarrySpeed();
	turnSpeed    = CG_GENERALPARMS(this).mTurnSpeed();
	maxTurnAngle = CG_GENERALPARMS(this).mMaxTurnAngle();
	Pellet* pelt = getCarryTarget();
	if (getStateID() == PANMODOKI_Pulled) {
		turnSpeed *= 0.5f;
		if (pelt && pelt->getStateID() != 1) {

			mNextWayPointPosition   = pelt->getPosition();
			mNextWayPointPosition.x = -(pelt->getVelocity().x * 10.0f - mNextWayPointPosition.x);
			mNextWayPointPosition.z = -(pelt->getVelocity().z * 10.0f - mNextWayPointPosition.z);
		}
	}
	Vector3f wpPos = mNextWayPointPosition;
	if (sqrDistanceXZ(mPosition, mNextWayPointPosition) < 10000.0f) {
		turnSpeed    = CG_PROPERPARMS(this).mFastTurnSpeed.mValue;
		maxTurnAngle = CG_PROPERPARMS(this).mMaxFastTurnAngle.mValue;
	}
	if (pelt) {
		mFaceDir = mCarryDir;
		EnemyFunc::walkToTarget(this, wpPos, speed, turnSpeed, maxTurnAngle);
		mCarryDir          = mFaceDir;
		Creature* target   = mTargetCreature;
		Vector3f targetVel = mTargetVelocity;
		targetVel.y        = 0.0f;
		// maxTurnAngle         = mTargetVelocity.x;
		// speed             = mTargetVelocity.z;
		// Pellet* newPelt  = getCarryTarget();
		Vector3f peltVel = getCarryTarget()->getVelocity();
		peltVel          = peltVel + (targetVel - peltVel) * (sys->mDeltaTime / 0.15f);
		peltVel.y += targetVel.y;
		peltVel.x = targetVel.x;
		peltVel.z = targetVel.z;
		// Vector3f resultVec(targetVel.x, peltVel.y + (0.0f - peltVel.y) * (sys->mFpsFactor / 0.15f) + 0.0f, targetVel.z);
		if (CG_PARMS(this)->_99A && pelt) {
			if (!mIsCarryStuck) {
				mMoveToWpTimer++;
				if (mMoveToWpTimer > 0x5A) {
					if (sqrDistanceXZ(mPosition, mPrevCheckPosition) < 100.0f) {
						mIsCarryStuck = 1;
					} else {
						mMoveToWpTimer = 0;
					}
					mPrevCheckPosition = mPosition;
				}
			}
			if (!mIsCarryStuck) {
				f32 collPos = mFloorNormal.x;
				f32 ten     = 10.0f;
				if (collPos > 0.1f) {
					mPelletCarryVelocity.x = -ten;
				} else {
					if (collPos < -0.1f) {
						mPelletCarryVelocity.x = ten;
					} else {
						mPelletCarryVelocity.x *= 0.99f;
					}
				}
				f32 collPosZ = mFloorNormal.z;
				if (collPosZ > 0.1f) {
					mPelletCarryVelocity.z = -ten;
				} else {
					if (collPosZ < -0.1f) {
						mPelletCarryVelocity.z = ten;
					} else {
						mPelletCarryVelocity.z *= 0.99f;
					}
				}
			} else {
				mPelletCarryVelocity.x = peltVel.x / 2;
				mPelletCarryVelocity.z = peltVel.z / 2;
			}
			peltVel.x += mPelletCarryVelocity.x;
			peltVel.z += mPelletCarryVelocity.z;
		}
		pelt->mPelletCarry->pull(2, peltVel, mCarryStrength);
		f32 angle   = getCreatureViewAngle(pelt);
		mFaceDir    = roundAng(mFaceDir + angle);
		mRotation.y = mFaceDir;
		pelt->setPanModokiRotation(roundAng((mCarryDir + mCarryRotationOffset) - mAlsoRotationOffset));
	}
	return false;
}

/**
 * @note Address: 0x803525EC
 * @note Size: 0x50
 */
void Obj::changeCarryDir(bool direct)
{
	if (direct) {
		mCarryDir = mFaceDir;
	} else {
		mCarryDir = roundAng(mFaceDir + PI);
	}
}

/**
 * @note Address: 0x8035263C
 * @note Size: 0x1B4
 */
void Obj::setCarryDir(bool direct)
{
	Pellet* creature;
	Matrixf matrix;
	if (direct) {
		mCarryDir = mFaceDir;
	} else {
		mCarryDir = roundAng(mFaceDir + PI);
	}
	creature = getCarryTarget();
	if (creature) {
		Vector3f pos3 = Vector3f(mPosition.x - creature->getPosition().x, 0.0f, mPosition.z - creature->getPosition().z);
		pos3.set(mPosition); // dumb
		PSMTXInverse(creature->mBaseTrMatrix.mMatrix.mtxView, matrix.mMatrix.mtxView);
		Vector3f pos         = matrix.mtxMult(pos3);
		mAlsoRotationOffset  = atan2(pos.x, pos.z);
		mCarryRotationOffset = 0.0f;
		if (direct) {
			mCarryRotationOffset = PI;
		}
		mCarryStrength = (creature->getPelletConfigMin() + creature->getPelletConfigMax()) * 0.5f;
	}
}

/**
 * @note Address: 0x803527F0
 * @note Size: 0x384
 */
void Obj::endCarry()
{
	Pellet* pelt = getCarryTarget();
	hardConstraintOn();
	if (!pelt) {
		return;
	}

	Stickers stick(pelt);
	Iterator<Creature> iter(&stick);
	CI_LOOP(iter)
	{
		Creature* stuck = *iter;
		if (stuck->isPiki()) {
			InteractKill interactKill(this, nullptr);
			stuck->stimulate(interactKill);
		}
	}
	endStick();
	pelt->mPelletCarry->giveup(2);
	bool doKillPellet = true;
	if (pelt->getKind() == PelletType::Treasure) {
		mHeldTreasures[mHeldTreasureNum] = pelt;
		if (mHeldTreasureNum == 0) {
			pelt->setAlive(false);
			pelt->startCapture(&mNest->mHouseTrMatrix);
			doKillPellet = false;
		}
		mHeldTreasureNum++;
	}
	if (doKillPellet) {
		PelletKillArg arg;
		pelt->kill(&arg);
	}
	mTargetCreature = nullptr;
}

/**
 * @note Address: 0x80352B74
 * @note Size: 0xA0
 */
void Obj::checkSucked()
{
	if (!isDead()) {
		Creature* target = mTargetCreature;
		if (target) {
			target = getCarryTarget();
			if (static_cast<Pellet*>(target)->getStateID() == 1) {
				mEvents.mFlags[0].typeView |= EB_NoInterrupt;
				fadePulledSmokeEffect();
			}
		}
	}
}

/**
 * @note Address: 0x80352C14
 * @note Size: 0xBC
 */
void Obj::suckFinish()
{
	Pellet* pellet = static_cast<Pellet*>(mTargetCreature);
	pellet         = getCarryTarget();
	endStick();
	if (pellet) {
		pellet->mPelletCarry->giveup(2);
	}
	mFsm->transit(this, PANMODOKI_Sucked, nullptr);
	mTargetCreature = nullptr;
	fadePulledSmokeEffect();
}

/**
 * @note Address: 0x80352CD0
 * @note Size: 0x118
 */
bool Obj::isEndPathFinder()
{
	bool result;
	if (mIsPathfinding) {
		return true;
	} else {
		P2ASSERTLINE(1708, testPathfinder);
		switch (testPathfinder->check(mPathID)) {
		case 0:
			testPathfinder->makepath(mPathID, &mPathNode);
			mIsPathfinding = true;
			return true;
		case 2:
			result         = false;
			mIsPathfinding = false;
			break;
		case 1:
			if (EnemyBase::getCurrAnimIndex() != 8) {
				EnemyBase::startMotion(8, nullptr);
			}
			setPathFinder(true);
			mIsPathfinding = false;
			return false;
		case 3:
			mIsPathfinding = false;
			return false;
		default:
			result = false;
		}
	}
	return result;
}

/**
 * @note Address: 0x80352DE8
 * @note Size: 0x2BC
 */
bool Obj::setPathFinder(bool cond)
{
	s16 nearIdx;
	s16 farIdx;
	releasePathFinder();
	mPelletCarryVelocity = 0.0f;
	WPEdgeSearchArg args(mPosition);
	RouteMgr* routeMgr = mapMgr->mRouteMgr;
	P2ASSERTLINE(1756, routeMgr);
	if (routeMgr->getNearestEdge(args)) {
		WayPoint* wp1   = args.mWp1;
		WayPoint* wp2   = args.mWp2;
		s16 idx1        = wp1->mIndex;
		s16 idx2        = wp2->mIndex;
		nearIdx         = idx1;
		farIdx          = idx2;
		Vector3f wp1Pos = wp1->mPosition;
		Vector3f wp2Pos = wp2->mPosition;

		if (sqrDistanceXZ(wp1Pos, mHomePosition) > sqrDistanceXZ(wp2Pos, mHomePosition)) {
			farIdx  = idx1;
			nearIdx = idx2;
		}
		if (routeMgr->getWayPoint(nearIdx)->isFlag(WPF_Closed)) {
			nearIdx = farIdx;
		}
		if (!(routeMgr->getWayPoint(args.mWp1->mIndex)->isFlag(WPF_Closed))
		    && !(routeMgr->getWayPoint(args.mWp2->mIndex)->isFlag(WPF_Closed))) {
			if (nearIdx == args.mWp1->mIndex) {
				if (absF(wp1Pos.y - mPosition.y) > 15.0f) {
					nearIdx = args.mWp2->mIndex;
				}
			} else if (absF(wp2Pos.y - mPosition.y) > 15.0f) {
				nearIdx = args.mWp1->mIndex;
			}
		}
		mWpIndex3 = mWpIndex2;
		mWpIndex2 = nearIdx;

		int flag = cond != 0 ? (PATHFLAG_PathThroughWater | PATHFLAG_AllowUnvisited | PATHFLAG_TwoWayPathing)
		                     : (PATHFLAG_RequireOpen | PATHFLAG_PathThroughWater | PATHFLAG_AllowUnvisited | PATHFLAG_TwoWayPathing);

		if (mPathID) {
			testPathfinder->release(mPathID);
		}
		PathfindRequest request(mWpIndex2, mWpIndex1, flag);
		mPathID                 = testPathfinder->start(request);
		Vector3f wpPos          = routeMgr->getWayPoint(mWpIndex2)->mPosition;
		mNextWayPointPosition.x = wpPos.x;
		mNextWayPointPosition.y = wpPos.y;
		mNextWayPointPosition.z = wpPos.z;
		return true;
	}
	JUT_PANICLINE(1810, nullptr);
	return false;
}

/**
 * @note Address: 0x803530A4
 * @note Size: 0x44
 */
void Obj::releasePathFinder()
{
	mIsPathfinding = false;
	if (testPathfinder && mPathID) {
		testPathfinder->release(mPathID);
	}
}

/**
 * @note Address: 0x803530E8
 * @note Size: 0x20
 */
void PanModokiBase::Obj::killNest()
{
	if (mNest) {
		mNest->mDeathTimer = 1;
	}
	mNest = nullptr;
}

/**
 * @note Address: 0x80353108
 * @note Size: 0x324
 */
bool Obj::isTargetable(Pellet* pellet)
{
	if (gameSystem && gameSystem->isVersusMode() && pellet->mPelletFlag == 3) {
		return false;
	}

	if (pellet) {
		if (pellet->getKind() >= PelletType::Treasure && mHeldTreasureNum >= PANMODOKI_MaxHeldTreasures) {
			return false;
		}

		if (!pellet->panmodokiCarryable()) {
			return false;
		}

		Stickers stick(pellet);
		Iterator<Creature> it(&stick);
		CI_LOOP(it)
		{
			Creature* obj = *it;
			if (obj->isTeki()) {
				return false;
			}
		}

		if (!pellet->mPelletCarry->pullable(Game::PCS_Unk2, (pellet->getPelletConfigMin() + pellet->getPelletConfigMax()) * 0.5f)) {
			return false;
		}

		return true;
	}
	return false;
}

/**
 * @note Address: 0x8035342C
 * @note Size: 0x17C
 */
void Obj::calcSlotGlobalPos(Vector3f& pos)
{
	Pellet* pellet = static_cast<Pellet*>(mTargetCreature);
	Matrixf matrix;
	pellet = getCarryTarget();
	P2ASSERTLINE(1903, pellet);
	f32 rad      = pellet->getPickRadius();
	f32 angle    = mAlsoRotationOffset;
	Vector3f dir = Vector3f(rad * sinf(angle), 0.0f, rad * cosf(angle));
	PSMTXCopy(pellet->mBaseTrMatrix.mMatrix.mtxView, matrix.mMatrix.mtxView);
	pos = matrix.mtxMult(dir);
}

/**
 * @note Address: 0x803535A8
 * @note Size: 0x28
 */
void Obj::boundEffect() { createBounceEffect(mPosition, mBounceEffectSize); }

/**
 * @note Address: 0x803535D0
 * @note Size: 0xE8
 */
void Obj::createAppearEffect()
{
	if (mWaterBox == nullptr) {
		efx::TPanApp tpan;
		efx::ArgScale args(mPosition, mAppearEffectSize);
		tpan.create(&args);
	} else {
		createEfxHamon();
		EnemyBase::createSplashDownEffect(mPosition, mBounceEffectSize);
	}
}

/**
 * @note Address: 0x803536B8
 * @note Size: 0xE0
 */
void Obj::createHideEffect()
{
	if (mWaterBox == nullptr) {
		Vector3f nestPos = mNest->getPosition();
		efx::ArgScale args(nestPos, mAppearEffectSize);
		mEfxHide->create(&args);
	} else {
		fadeEfxHamon();
	}
}

/**
 * @note Address: 0x80353798
 * @note Size: 0x30
 */
void Obj::fadeHideEffect() { mEfxHide->fade(); }

/**
 * @note Address: 0x803537C8
 * @note Size: 0x84
 */
void Obj::createPulledSmokeEffect()
{
	efx::ArgScale args(mPosition, mAppearEffectSize);
	mEfxSmoke->create(&args);
}

/**
 * @note Address: 0x8035384C
 * @note Size: 0x30
 */
void Obj::fadePulledSmokeEffect() { mEfxSmoke->fade(); }

/**
 * @note Address: 0x8035387C
 * @note Size: 0x2CC
 */
void Obj::throwUpEatItem()
{
	if (mHeldTreasures[0]) {
		PelletKillArg killArg;
		mHeldTreasures[0]->kill(&killArg);
	}

	for (int i = 0; i < mHeldTreasureNum; i++) {
		PelletInitArg initArg;

		if (pelletMgr->makePelletInitArg(initArg, mHeldTreasures[i]->getConfigName())) {
			Pellet* pellet = mHeldTreasures[i];
			if (pellet) {
				pellet->mMgr->setComeAlive(pellet);
				initArg.mState             = PelBirthType_ScaleAppear;
				initArg.mDoSkipCreateModel = 1; // breadbug drops are already loaded
				pellet->init(&initArg);

				Vector3f pos = mHomePosition;
				pos.y += 10.0f;

				Vector3f vel;
				getThrowupItemVelocity(&vel);

				f32 angle = (TAU * (f32)i) / (f32)mHeldTreasureNum;
				if (mHeldTreasureNum != 1) {
					vel.x += sinf(angle) * 50.0f;
					vel.z += cosf(angle) * 50.0f;
				}

				pellet->setPosition(pos, false);
				pellet->setVelocity(vel);
				pellet->createKiraEffect(pos);

				mSoundObj->startSound(PSSE_EN_ENEMY_LOOSE_ITEM, 0);
			}
		}
	}
}

} // namespace PanModokiBase

namespace OoPanModoki {

/**
 * @note Address: 0x80353B48
 * @note Size: 0xB8
 */
Obj::Obj()
{
	mCarrySizeDiff    = 40.0f;
	mShadowSize       = 30.0f;
	mUnusedVal        = 12.0f;
	mBounceEffectSize = 0.9f;
	mAppearEffectSize = 1.6f;
}

/**
 * @note Address: 0x80353C00
 * @note Size: 0x34
 */
void Obj::appearRumble() { rumbleMgr->startRumble(RUMBLETYPE_Fixed11, mPosition, RUMBLEID_Both); }

/**
 * @note Address: 0x80353C34
 * @note Size: 0x34
 */
void Obj::hideRumble() { rumbleMgr->startRumble(RUMBLETYPE_Fixed10, mPosition, RUMBLEID_Both); }

/**
 * @note Address: 0x80353C68
 * @note Size: 0x94
 */
bool Obj::pressCallBack(Game::Creature* creature, f32 damage, CollPart* collPart)
{
	if (creature && creature->isPiki() && static_cast<Piki*>(creature)->getKind() != Purple) {
		return false;
	}
	return PanModokiBase::Obj::pressCallBack(creature, damage, collPart);
}

} // namespace OoPanModoki
} // namespace Game
