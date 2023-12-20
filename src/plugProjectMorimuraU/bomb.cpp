#include "Game/enemyInfo.h"
#include "Game/MapMgr.h"
#include "Game/EnemyAnimKeyEvent.h"
#include "types.h"
#include "Game/Entities/Bomb.h"
#include "Game/Entities/BombOtakara.h"

namespace Game {
namespace Bomb {
/**
 * @note Address: 0x8034A21C
 * @note Size: 0x20
 */
void Obj::setParameters() { EnemyBase::setParameters(); }

/**
 * @note Address: 0x8034A23C
 * @note Size: 0xEC
 */
void Obj::onStartCapture()
{
	mFsm->start(this, BOMB_Wait, nullptr);
	if (mCaptureMatrix) {
		Vector3f position = mCaptureMatrix->getBasis(3);
		onSetPosition(position);
		mCurrentVelocity = Vector3f(0.0f);
		mTargetVelocity  = Vector3f(0.0f);
		enableEvent(0, EB_Constrained);
		if (gameSystem && gameSystem->isVersusMode()) {
			disableEvent(0, EB_Invulnerable);
		} else {
			enableEvent(0, EB_Invulnerable);
		}

		disableEvent(0, EB_Cullable);
	}
}

/**
 * @note Address: 0x8034A328
 * @note Size: 0x48
 */
void Obj::onEndCapture()
{
	constraintOff();
	disableEvent(0, EB_Invulnerable);
	_2BC           = 1;
	mCaptureMatrix = nullptr;
}

/**
 * @note Address: 0x8034A370
 * @note Size: 0x20
 */
void Obj::birth(Vector3f& position, f32 p1) { EnemyBase::birth(position, p1); }

/**
 * @note Address: 0x8034A390
 * @note Size: 0x168
 */
void Obj::onInit(CreatureInitArg* initArg)
{
	EnemyBase::onInit(initArg);
	disableEvent(0, EB_LeaveCarcass);
	disableEvent(0, EB_DamageAnimEnabled);
	disableEvent(0, EB_DeathEffectEnabled);

	_2BC     = 0;
	_2BD     = 0;
	_2C8     = 0;
	_2C0     = 0;
	_2C4     = 0;
	mCarrier = nullptr;

	mFsm->start(this, BOMB_Wait, nullptr);

	if (!isBirthTypeDropGroup()) {
		enableEvent(0, EB_Constrained);
		if (mapMgr) {
			Vector3f position = mPosition;
			position.y += 20.0f;
			mPosition.y = mapMgr->getMinY(position);
		}
	}

	mCurAnim->mIsPlaying = false;
	doAnimationUpdateAnimator();

	mBaseTrMatrix.makeSRT(mScale, mRotation, mPosition);

	PSMTXCopy(mBaseTrMatrix.mMatrix.mtxView, mModel->mJ3dModel->mPosMtx);
	mModel->mJ3dModel->calc();

	mEfxLight->mMtx = mModel->getJoint("core1")->getWorldMatrix();
}

/**
 * @note Address: 0x8034A4F8
 * @note Size: 0x1DC
 */
Obj::Obj()
{
	_2BC      = 0;
	_2BD      = 0;
	_2C0      = 0;
	_2C4      = 0;
	_2C8      = 0;
	_2C9      = 0;
	mFsm      = nullptr;
	mEfxLight = nullptr;
	mAnimator = new ProperAnimator;
	setFSM(new FSM);
	mEfxLight = new efx::TBombrockLight;
}

/**
 * @note Address: 0x8034A720
 * @note Size: 0xD4
 */
void Obj::doUpdate()
{
	if (_2C9) {
		mAcceleration *= 0.9f;
		mCurrentVelocity.x *= 0.9f;
		if (mCurrentVelocity.y > 0.0f) {
			mCurrentVelocity.y *= 0.9f;
		}
		mCurrentVelocity.z *= 0.9f;
	}

	if (mBounceTriangle) {
		mTargetVelocity = Vector3f(0.0f);
	} else {
		mTargetVelocity = mCurrentVelocity;
	}

	mFsm->exec(this);
}

/**
 * @note Address: 0x8034A7F4
 * @note Size: 0x4
 */
void Obj::doDirectDraw(Graphics&) { }

/**
 * @note Address: 0x8034A7F8
 * @note Size: 0x4
 */
void Obj::doDebugDraw(Graphics&) { }

/**
 * @note Address: 0x8034A7FC
 * @note Size: 0x2C
 */
void Obj::doEntry()
{
	if (!_2BD) {
		EnemyBase::doEntry();
	}
}

/**
 * @note Address: 0x8034A828
 * @note Size: 0x1F4
 */
void Obj::doAnimationCullingOff()
{
	mCurAnim->mIsPlaying = false;
	doAnimationUpdateAnimator();
	bool check   = true;
	Vector3f vec = mBaseTrMatrix.getBasis(3);
	if (mCaptureMatrix) {
		Vector3f checkVec = mCaptureMatrix->getBasis(3);
		if (vec.x != checkVec.x || vec.y != checkVec.y || vec.z != checkVec.z) {
			check = true;
			PSMTXCopy(mCaptureMatrix->mMatrix.mtxView, mBaseTrMatrix.mMatrix.mtxView);
		}
	} else {
		check = false;
		if (isStickToMouth() || isEvent(0, EB_Bittered) || mPosition.x != vec.x || mPosition.y != vec.y || mPosition.z != vec.z) {
			check = true;
			mBaseTrMatrix.makeSRT(mScale, mRotation, mPosition);
		}
	}

	if (check || !isStopMotion()) {
		PSMTXCopy(mBaseTrMatrix.mMatrix.mtxView, mModel->mJ3dModel->mPosMtx);
		mModel->mJ3dModel->calc();
		mCollTree->update();
	}

	if (!isStickTo() && !isStopMotion() && !_2C8 && mHealth < 4.0f) { // why 4
		_2C8 = 1;
		efx::Arg fxArg(mPosition);
		mEfxLight->create(&fxArg);
	}
}

/**
 * @note Address: 0x8034AA1C
 * @note Size: 0x4C
 */
void Obj::doAnimationCullingOn()
{
	if (isAnimStart()) {
		disableEvent(0, EB_Cullable);
	} else {
		EnemyBase::doAnimationCullingOn();
	}
}

/**
 * @note Address: 0x8034AA68
 * @note Size: 0x134
 */
void Obj::doSimulation(f32 simSpeed)
{
	if (isStickTo()) {
		Vector3f dir = Vector3f(sinf(mFaceDir), 0.0f, cosf(mFaceDir));
		updateStick(dir);
		updateCell();
	} else if (mCaptureMatrix) {
		mPosition = mCaptureMatrix->getBasis(3);
		updateSpheres();
	} else {
		EnemyBase::doSimulation(simSpeed);
	}
}

/**
 * @note Address: 0x8034AB9C
 * @note Size: 0x50
 */
void Obj::getShadowParam(ShadowParam& param)
{
	param.mPosition   = mPosition;
	param.mPosition.y = mPosition.y + 2.0f;

	param.mBoundingSphere.mPosition = Vector3f(0.0f, 1.0f, 0.0f);
	param.mBoundingSphere.mRadius   = 30.0f;
	param.mSize                     = 10.0f;
}

/**
 * @note Address: 0x8034ABEC
 * @note Size: 0x48
 */
bool Obj::needShadow() { return (!EnemyBase::needShadow()) ? false : mCaptureMatrix == nullptr; }

/**
 * @note Address: 0x8034AC34
 * @note Size: 0x80
 */
void Obj::doFinishStoneState()
{
	EnemyBase::doFinishStoneState();
	if (getStateID() == BOMB_Wait && getMotionFrame() == 0.0f && !_2BC) {
		stopMotion();
	}

	disableEvent(0, EB_Invulnerable);
	mTargetVelocity = Vector3f(0.0f);
}

/**
 * @note Address: 0x8034ACB4
 * @note Size: 0x48
 */
void Obj::doStartStoneState()
{
	EnemyBase::doStartStoneState();
	mEfxLight->fade();
	_2C8 = 0;
}

/**
 * @note Address: 0x8034ACFC
 * @note Size: 0x84
 */
void Obj::onKill(CreatureKillArg* killArg)
{
	if (mCarrier && mCarrier->getEnemyTypeID() == EnemyTypeID::EnemyID_BombOtakara) {
		mCarrier->mTargetCreature = nullptr;
	}

	mEfxLight->fade();
	EnemyBase::onKill(killArg);
}

/**
 * @note Address: 0x8034AD80
 * @note Size: 0x30
 */
void Obj::doStartMovie() { mEfxLight->startDemoDrawOff(); }

/**
 * @note Address: 0x8034ADB0
 * @note Size: 0x30
 */
void Obj::doEndMovie() { mEfxLight->endDemoDrawOn(); }

/**
 * @note Address: 0x8034ADE0
 * @note Size: 0x74
 */
bool Obj::damageCallBack(Creature* creature, f32 damage, CollPart* collpart)
{
	if (!_2BC || mBounceTriangle) {
		if (isEvent(0, EB_Bittered)) {
			_2C4++;
			if (_2C4 > 4) {
				kill(nullptr);
			}
			return true;
		} else {
			EnemyBase::damageCallBack(creature, 0.0f, collpart);
		}
	}

	return false;
}

/**
 * @note Address: 0x8034AE54
 * @note Size: 0x160
 */
bool Obj::bombCallBack(Creature* creature, Vector3f& direction, f32 damage)
{
	if (!mCaptureMatrix && !isEvent(0, EB_Bittered) && creature->isTeki()) {
		if (static_cast<EnemyBase*>(creature)->getEnemyTypeID() == EnemyTypeID::EnemyID_Bomb) {
			if (getStateID() == BOMB_Wait && _2C0 == 0) {
				Vector3f creaturePos = creature->getPosition();
				f32 rad              = C_PARMS->mGeneral.mAttackRadius.mValue;
				rad *= rad;
				f32 factor = (1.0f - (sqrDistanceXZ(creaturePos, mPosition) / rad)) * (f32)C_PROPERPARMS.mTriggerLimit();
				_2C0       = (int)factor + 1;
			}
		} else {
			damageCallBack(creature, 0.0f, nullptr);
		}

		mFlickTimer = 0.0f;
		return true;
	}

	return false;
}

/**
 * @note Address: 0x8034AFB4
 * @note Size: 0x8
 */
bool Obj::pressCallBack(Creature*, f32, CollPart*) { return false; }

/**
 * @note Address: 0x8034AFBC
 * @note Size: 0x78
 */
void Obj::bounceCallback(Sys::Triangle* triangle)
{
	if (_2BC) {
		createBounceEffect(mPosition, 0.5f);
		return;
	}

	if (isBirthTypeDropGroup() && getStateID() == BOMB_Wait) {
		createBounceEffect(mPosition, 0.5f);
		forceBomb();
	}
}

/**
 * @note Address: 0x8034B034
 * @note Size: 0x9C
 */
void Obj::collisionCallback(CollEvent& collEvent)
{
	EnemyBase::collisionCallback(collEvent);
	if (isBirthTypeDropGroup() && collEvent.mCollidingCreature && !collEvent.mCollidingCreature->isTeki() && getStateID() == BOMB_Wait) {
		createBounceEffect(mPosition, 0.5f);
		forceBomb();
		_2C9 = 1;
	}
}

/**
 * @note Address: 0x8034B0D0
 * @note Size: 0x60
 */
void Obj::forceBomb()
{
	if (getStateID() == BOMB_Wait) {
		disableEvent(0, EB_Invulnerable);
		mFsm->transit(this, BOMB_Bomb, nullptr);
	}
}

/**
 * @note Address: N/A
 * @note Size: 0x48
 */
bool Obj::isBombStart()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: 0x8034B130
 * @note Size: 0x28
 */
void Obj::bombEffInWater() { EnemyBase::createSplashDownEffect(mPosition, 1.3f); }

/**
 * @note Address: 0x8034B158
 * @note Size: 0x5C
 */
bool Obj::canEat()
{
	if (isAlive() && getStateID() == BOMB_Wait) {
		return true;
	}

	return false;
}

/**
 * @note Address: 0x8034B1B4
 * @note Size: 0xD8
 */
bool Obj::isAnimStart()
{
	bool check;
	if (isBirthTypeDropGroup() || !(mFlickTimer >= C_PROPERPARMS.mDamageLimit.mValue)) {
		if (!_2BC || !mBounceTriangle) {
			if (!_2C0) {
				check = false;
			} else {

				_2C0++;

				if (_2C0 > C_PROPERPARMS.mTriggerLimit.mValue) {
					_2C0  = 0;
					check = true;
				} else {
					check = false;
				}
			}

			if (check) {
			yes:
				return true;
			}
		} else {
			goto yes;
		}
	} else {
		goto yes;
	}
	return false;
}

} // namespace Bomb
} // namespace Game
