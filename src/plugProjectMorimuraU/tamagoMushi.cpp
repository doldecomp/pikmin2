#include "Game/Entities/TamagoMushi.h"
#include "Game/EnemyAnimKeyEvent.h"
#include "Game/EnemyFunc.h"
#include "Game/PikiMgr.h"
#include "Game/PikiState.h"
#include "Game/Entities/ItemHoney.h"
#include "efx/TUjinko.h"
#include "efx/TTamagoAp.h"
#include "Dolphin/rand.h"

namespace Game {
namespace TamagoMushi {
static const char unusedName[] = "tamagoMushi";

/**
 * @note Address: 0x8036EBA8
 * @note Size: 0x20
 */
void Obj::setParameters() { EnemyBase::setParameters(); }

/**
 * @note Address: 0x8036EBC8
 * @note Size: 0x20
 */
void Obj::birth(Vector3f& pos, f32 faceDir) { EnemyBase::birth(pos, faceDir); }

/**
 * @note Address: 0x8036EBE8
 * @note Size: 0x2D0
 */
void Obj::onInit(CreatureInitArg* initArg)
{
	EnemyBase::onInit(initArg);
	disableEvent(0, EB_LeaveCarcass);
	disableEvent(0, EB_DamageAnimEnabled);
	disableEvent(0, EB_DeathEffectEnabled);
	_2BC          = 0;
	_2F0          = false;
	mLeader       = nullptr;
	_304          = 0;
	mGoalPosition = mPosition;
	_2C0          = (0.8f + 0.2f * randFloat()) * C_PROPERPARMS.mSurvivalTime.mValue;
	if (gameSystem && gameSystem->isZukanMode()) {
		_2C0 *= 5;
	}

	_2C4 = 0.7f + 0.3f * randFloat();
	_2C8 = 0.7f + 0.3f * randFloat();
	_2CC = 0.3f + 0.7f * randFloat();
	_2FC = 0.0f;
	_300 = false;

	Vector3f dir = Vector3f(sinf(mFaceDir), 0.0f, cosf(mFaceDir));
	setGoalDirect(dir);
	mInPiklopedia = 0;

	P2ASSERTLINE(81, mModel);
	mKoshiJoint = mModel->getJoint("koshijnt");
	P2ASSERTLINE(84, mKoshiJoint);

	mFsm->start(this, TAMAGOMUSHI_Appear, nullptr);
}

/**
 * @note Address: 0x8036EEB8
 * @note Size: 0x13C
 */
Obj::Obj()
{
	mKoshiJoint = nullptr;
	mFsm        = nullptr;
	mAnimator   = new ProperAnimator;
	setFSM(new FSM);
}

/**
 * @note Address: 0x8036F040
 * @note Size: 0xA0
 */
void Obj::doUpdate()
{
	if (!isEvent(0, EB_Bittered)) {
		mFsm->exec(this);
		int stateID = getStateID();
		if (stateID == TAMAGOMUSHI_Walk || stateID == TAMAGOMUSHI_Turn) {
			_2BC++;
			if (_2BC > _2C0) {
				mFsm->transit(this, TAMAGOMUSHI_Hide, nullptr);
			}
		}
	}
}

/**
 * @note Address: 0x8036F0E0
 * @note Size: 0x158
 */
void Obj::doAnimationCullingOff()
{
	mCurAnim->mIsPlaying = false;
	doAnimationUpdateAnimator();

	if (mPellet) {
		viewMakeMatrix(mBaseTrMatrix);
		Matrixf mtx;
		PSMTXScale(mtx.mMatrix.mtxView, mScale.x, mScale.y, mScale.z);
		PSMTXConcat(mBaseTrMatrix.mMatrix.mtxView, mtx.mMatrix.mtxView, mBaseTrMatrix.mMatrix.mtxView);

		Vector3f pos;
		mBaseTrMatrix.getTranslation(pos);
		onSetPosition(pos);
		onSetPositionPost(pos);
	} else {
		mBaseTrMatrix.makeTR(mPosition, mRotation);
	}

	PSMTXCopy(mBaseTrMatrix.mMatrix.mtxView, mModel->mJ3dModel->mPosMtx);

	if (C_PARMS->_923 && getCurrAnimIndex() == 2) {
		J3DModel* model = mModel->getJ3DModel();
		C_MGR->fetch(model, getMotionFrame());

	} else {
		mModel->mJ3dModel->calc();
	}

	mCollTree->update();
}

/**
 * @note Address: 0x8036F238
 * @note Size: 0x4
 */
void Obj::doDirectDraw(Graphics&) { }

/**
 * @note Address: 0x8036F23C
 * @note Size: 0x20
 */
void Obj::doDebugDraw(Graphics& gfx) { EnemyBase::doDebugDraw(gfx); }

/**
 * @note Address: 0x8036F25C
 * @note Size: 0xDC
 */
bool Obj::pressCallBack(Creature* creature, f32 damage, CollPart* part)
{
	if (creature && creature->isPiki()) {
		if (isEvent(0, EB_Bittered)) {
			if (mEnemyStoneObj->isFlag(EnemyStone::STONE_HasViewedDemo)) {
				genItem();
				kill(nullptr);
				return true;
			} else {
				return false;
			}
		}

		if (getStateID() != TAMAGOMUSHI_Dead) {
			mFsm->transit(this, TAMAGOMUSHI_Dead, nullptr);
			enableEvent(0, EB_LifegaugeVisible);
			mHealth = 0.0f;
			return true;
		}
	}

	return false;
}

/**
 * @note Address: 0x8036F338
 * @note Size: 0xBC
 */
bool Obj::bombCallBack(Creature* creature, Vector3f& direction, f32 damage)
{
	if (getStateID() != TAMAGOMUSHI_Dead) {
		if (EnemyBase::bombCallBack(creature, direction, damage)) {
			mFsm->transit(this, TAMAGOMUSHI_Dead, nullptr);
			enableEvent(0, EB_LifegaugeVisible);
			mHealth = 0.0f;
			return true;
		}
	}

	return false;
}

/**
 * @note Address: 0x8036F3F4
 * @note Size: 0x134
 */
bool Obj::damageCallBack(Creature* creature, f32 damage, CollPart* part)
{
	int stateID = getStateID();
	if (isEvent(0, EB_Bittered)) {
		_304++;
		if (_304 > 4) {
			genItem();
			kill(nullptr);
		}

		return true;
	}

	EnemyBase::damageCallBack(creature, 0.0f, part);

	if (stateID != TAMAGOMUSHI_Appear && stateID != TAMAGOMUSHI_Dead) {
		if (creature && creature->isPiki()) {
			int pikiStateID = static_cast<Piki*>(creature)->getStateID();
			if (pikiStateID != PIKISTATE_Panic && pikiStateID != PIKISTATE_Flying) {
				InteractAstonish astonish(this, C_PARMS->_944);
				creature->stimulate(astonish);
			}
		}
	}

	return false;
}

/**
 * @note Address: 0x8036F528
 * @note Size: 0xF8
 */
void Obj::collisionCallback(CollEvent& event)
{
	if (!isEvent(0, EB_Bittered)) {
		int id = getStateID();
		setCollEvent(event);
		Creature* hitobj = event.mCollidingCreature;

		// astonish pikmin with the horrible mitite smell
		if (hitobj && (hitobj->isPiki()) && (id != TAMAGOMUSHI_Appear)) {
			Piki* piki = static_cast<Piki*>(hitobj);
			if ((piki->getStateID() != PIKISTATE_Panic) && (piki->getStateID() != PIKISTATE_Flying)) {
				InteractAstonish act(this, C_PARMS->_944);
				hitobj->stimulate(act);
			}
		}
	}
}

/**
 * @note Address: 0x8036F620
 * @note Size: 0x178
 */
void Obj::bounceCallback(Sys::Triangle* tri)
{
	if (_300) {
		f32 velY     = 0.7f + 0.3f * randFloat();
		f32 speed    = C_PARMS->_938;
		Vector3f vel = Vector3f(sinf(mFaceDir) * speed, C_PARMS->_934 * velY, cosf(mFaceDir) * speed);
		setVelocity(vel);
		mTargetVelocity = vel;
		mPosition.y += 10.0f;
		_2F0        = false;
		mRotation.z = 0.0f;
		mRotation.x = 0.0f;
		appearPanic();
	}

	_300 = false;
}

/**
 * @note Address: 0x8036F798
 * @note Size: 0x2C
 */
bool Obj::hipdropCallBack(Creature* creature, f32 damage, CollPart* part) { return pressCallBack(creature, damage, part); }

/**
 * @note Address: 0x8036F7C4
 * @note Size: 0x30
 */
bool Obj::earthquakeCallBack(Creature* creature, f32 damage) { return pressCallBack(creature, damage, nullptr); }

/**
 * @note Address: 0x8036F7F4
 * @note Size: 0xA8
 */
void Obj::getShadowParam(ShadowParam& shadowParam)
{
	shadowParam.mPosition = mKoshiJoint->getWorldMatrix()->getBasis(3);

	if (mPellet || getStateID() == TAMAGOMUSHI_Dead) {
		shadowParam.mPosition.y = mPosition.y + 2.0f;
	}
	shadowParam.mBoundingSphere.mPosition = Vector3f(0.0f, 1.0f, 0.0f);
	shadowParam.mBoundingSphere.mRadius   = 15.0f;
	shadowParam.mSize                     = 12.0f;
}

/**
 * @note Address: 0x8036F89C
 * @note Size: 0x30
 */
bool Obj::needShadow()
{
	return EnemyBase::needShadow() > 0; // WHY MAN.
}

/**
 * @note Address: 0x8036F8CC
 * @note Size: 0x208
 */
void Obj::genItem()
{
	if (!gameSystem || !gameSystem->isZukanMode()) {
		mInPiklopedia = 1;

		if (!(randFloat() > C_PROPERPARMS.mHoneyRate())) {
			Vector3f nectarVel = Vector3f(sinf(mFaceDir) * 50.0f, 200.0f, sinf(mFaceDir) * 50.0f); // why are these both sines smh
			Vector3f nectarPos = mPosition;
			nectarPos.y += 2.0f;

			P2ASSERTLINE(437, ItemHoney::mgr);
			BaseItem* item = ItemHoney::mgr->birth();
			if (item) {
				ItemHoney::Item* nectar = static_cast<ItemHoney::Item*>(item);
				nectar->init(nullptr);
				nectar->mHoneyType = HONEY_Y;
				nectar->setPosition(nectarPos, false);
				nectar->setVelocity(nectarVel);
			}
		}
	}
}

/**
 * @note Address: 0x8036FAD4
 * @note Size: 0x310
 */
void Obj::walkFunc()
{
	mRotation.x *= 0.9f;
	mRotation.z *= 0.9f;

	f32 x, y, z;
	f32 faceDirOffset;
	f32 targetSpeed    = _2C8 * C_PARMS->mGeneral.mMoveSpeed();
	f32 offsetFactor   = C_PARMS->_924 * _2CC;
	f32 dirChangeLimit = _2C4 * C_PARMS->mGeneral.mMaxTurnAngle();

	_2FC += C_PARMS->_928;
	if (_2FC > 360.0f) {
		_2FC -= 360.0f;
	}

	f32 sinVal = offsetFactor * (f32)sin(_2FC);
	if (C_PARMS->_920) {
		sinVal = 0.0f;
	}

	f32 val       = sinVal * _2D0;
	faceDirOffset = TORADIANS(val);

	_2D0 += 0.1f;
	if (_2D0 > 1.0f) {
		_2D0 = 1.0f;
	}

	if (C_PARMS->_921) {
		_2D4 += 1.0f;
		if (_2D4 > _2D8) {
			_2DC = !_2DC;
			_2D8 = C_PARMS->_92C * randFloat();
			_2D4 = 0.0f;
		}

		if (_2DC && _2D4 < _2D8) {
			targetSpeed *= (C_PARMS->_930 * (1.0f - (_2D4 / _2D8)));
		}
	}

	mFaceDir = _2EC;

	f32 angle = mFaceDir + faceDirOffset;
	x         = targetSpeed * sinf(angle);
	y         = getTargetVelocity().y;
	z         = targetSpeed * cosf(angle);
	_2EC      = mFaceDir;
	if (absF(faceDirOffset) > dirChangeLimit) {
		if (faceDirOffset > 0.0f) {
			faceDirOffset = dirChangeLimit;
		} else {
			faceDirOffset = -dirChangeLimit;
		}
	}

	updateFaceDir(mFaceDir + roundAng(faceDirOffset));

	mTargetVelocity = Vector3f(x, y, z);
}

/**
 * @note Address: 0x8036FDE4
 * @note Size: 0x168
 */
void Obj::setGoalRandom()
{
	f32 val     = C_PARMS->mGeneral.mTerritoryRadius();
	f32 randVal = 0.5f * randFloat() + 0.5f;
	val *= randVal;
	mGoalPosition = mHomePosition;

	f32 randAngle = TAU * randFloat();

	mGoalPosition.x += val * sinf(randAngle);
	mGoalPosition.z += val * cosf(randAngle);
}

/**
 * @note Address: 0x8036FF4C
 * @note Size: 0xB8
 */
void Obj::setGoalDirect(Vector3f& pos)
{
	f32 val     = C_PARMS->_93C;
	f32 randVal = 0.5f * randFloat() + 0.5f;
	val *= randVal;
	mGoalPosition = mPosition;

	mGoalPosition.x += val * pos.x;
	mGoalPosition.z += val * pos.z;
}

/**
 * @note Address: 0x80370004
 * @note Size: 0x15C
 */
bool Obj::turnFunc()
{
	f32 angle = turnToTarget2(mGoalPosition, _2C4 * C_PARMS->mGeneral.mTurnSpeed(), _2C4 * C_PARMS->mGeneral.mMaxTurnAngle());
	if (absF(angle) < 0.1f) {
		return true;
	}

	return false;
}

/**
 * @note Address: 0x80370160
 * @note Size: 0x34
 */
bool Obj::isReachToGoal(f32 goalRadius)
{
	return sqrDistanceXZ(mPosition, mGoalPosition) < SQUARE(goalRadius);
	/*
	fmuls    f0, f1, f1
	lfs      f2, 0x194(r3)
	lfs      f1, 0x2e8(r3)
	lfs      f3, 0x18c(r3)
	fsubs    f2, f2, f1
	lfs      f1, 0x2e0(r3)
	fsubs    f3, f3, f1
	fmuls    f1, f2, f2
	fmadds   f1, f3, f3, f1
	fcmpo    cr0, f1, f0
	mfcr     r0
	srwi     r3, r0, 0x1f
	blr
	*/
}

/**
 * @note Address: 0x80370194
 * @note Size: 0x2C
 */
void Obj::resetWalkParm()
{
	_2D0 = 0.0f;
	_2D4 = 0.0f;
	_2D8 = C_PARMS->_92C;
	_2DC = false;
	_2EC = mFaceDir;
}

/**
 * @note Address: 0x803701C0
 * @note Size: 0x28
 */
void Obj::startCarcassMotion() { startMotion(TAMAGOANIM_Carry, nullptr); }

/**
 * @note Address: 0x803701E8
 * @note Size: 0x58
 */
void Obj::setLeader(Obj* leader)
{
	if (mLeader != leader) {
		mLeader = leader;
		if (mLeader->_2F0) {
			setTypeBall();
		}
		disableEvent(0, EB_Cullable);
	}
}

/**
 * @note Address: 0x80370240
 * @note Size: 0x54
 */
void Obj::setTypeBall()
{
	mFsm->start(this, TAMAGOMUSHI_Wait, nullptr);
	_2F0 = true;
	_300 = true;
}

/**
 * @note Address: 0x80370294
 * @note Size: 0x344
 */
void Obj::appearPanic()
{
	if (!mLeader || mLeader == this) {
		f32 rad = SQUARE(C_PARMS->_948);
		Iterator<Piki> iter(pikiMgr);
		CI_LOOP(iter)
		{
			Piki* piki = *iter;
			if (piki->isSearchable()) {
				// probably should be an inline?
				Vector2f sep = Vector2f(piki->getPosition().x, piki->getPosition().z) - Vector2f(mPosition.x, mPosition.z);
				if (sep.sqrMagnitude() < rad) {
					InteractAstonish astonish(this, C_PARMS->_944);
					piki->stimulate(astonish);
				}
			}
		}
	}
}

/**
 * @note Address: 0x803705D8
 * @note Size: 0x3BC
 */
bool Obj::isFound()
{
	if (mLeader && mLeader != this) {
		return mLeader->isFound();
	}

	if (gameSystem && gameSystem->isZukanMode()) {
		return true;
	}

	f32 searchRad = C_PROPERPARMS.mAppearanceRange();
	if (EnemyFunc::getNearestPikmin(this, 180.0f, searchRad, nullptr, nullptr)) {
		return true;
	}

	if (EnemyFunc::getNearestNavi(this, 180.0f, searchRad, nullptr, nullptr)) {
		return true;
	}

	return false;
}

/**
 * @note Address: 0x803709B0
 * @note Size: 0x44
 */
void Obj::createFellow()
{
	if (!mLeader || mLeader == this) {
		C_MGR->createGroup(this, 10, false);
	}
}

/**
 * @note Address: 0x803709F4
 * @note Size: 0x9C
 */
void Obj::ballMove()
{
	f32 vel = JMAAbs((mCurrentVelocity.y * 2.0f) / 50.0f);
	if (vel > 2.0f) {
		vel = 2.0f;
	}
	EnemyFunc::walkToTarget(this, mGoalPosition, C_PARMS->mGeneral.mMoveSpeed.mValue * 0.2f, C_PARMS->mGeneral.mTurnSpeed.mValue * vel,
	                        C_PARMS->mGeneral.mMaxTurnAngle.mValue * vel);
	mRotation.x *= 0.95f;
	mRotation.z *= 0.95f;
}

/**
 * @note Address: 0x80370A90
 * @note Size: 0xA8
 */
void Obj::createHideEffect()
{
	efx::Arg arg(mPosition);
	efx::TUjinkoHd effect(mModel->mJoints->getWorldMatrix());
	effect.create(&arg);
}

/**
 * @note Address: 0x80370B38
 * @note Size: 0xA8
 */
void Obj::createAppearEffect()
{
	efx::Arg arg(mPosition);
	efx::TTamagoAp effect(mModel->mJoints->getWorldMatrix());
	effect.create(&arg);
}

} // namespace TamagoMushi
} // namespace Game
