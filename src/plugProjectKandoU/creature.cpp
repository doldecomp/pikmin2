#include "CollInfo.h"
#include "Dolphin/mtx.h"
#include "Game/cellPyramid.h"
#include "Game/Creature.h"
#include "Game/gameGenerator.h"
#include "Game/GameSystem.h"
#include "Game/shadowMgr.h"
#include "IDelegate.h"
#include "JSystem/J3D/J3DModel.h"
#include "ObjectTypes.h"
#include "SysShape/Model.h"
#include "Sys/Sphere.h"
#include "types.h"
#include "Vector3.h"
#include "Game/MapMgr.h"
#include "Game/DeathMgr.h"
#include "Game/CollEvent.h"
#include "nans.h"

namespace Game {

Creature* Creature::currOp;
bool Creature::usePacketCulling = true;

inline void Creature::killInline(Game::CreatureKillArg* arg)
{
	endStick();
	setAlive(false);
	Cell::sCurrCellMgr = cellMgr;
	exitCell();
	Cell::sCurrCellMgr = nullptr;
	mUpdateContext.exit();
	releaseAllStickers();
	clearCapture();
	onKill(arg);

	if (mGenerator) {
		mGenerator->informDeath(this);
		mGenerator = nullptr;
	}
}

/*
 * --INFO--
 * Address:	8013AE84
 * Size:	00012C
 */
Creature::Creature()
{
	mCollTree  = nullptr;
	mModel     = nullptr;
	mMass      = 100.0f;
	mGenerator = nullptr;

	mScale = Vector3f(1.0f);

	PSMTXIdentity(mObjMatrix.mMatrix.mtxView);

	mObjectTypeID = OBJTYPE_INVALID_START;

	for (int i = 0; i < 4; i++) {
		mFlags.byteView[i] = 0;
	}

	mFlags.typeView |= (CF_IS_ATARI | CF_IS_ALIVE | CF_IS_COLLISION_FLICK);
	clearStick();
}

/*
 * --INFO--
 * Address:	8013AFC8
 * Size:	000120
 */
void Creature::init(CreatureInitArg* arg)
{
	mCellLayerIndex = 0;
	mCellRect.reset();

	mFlags.clear();

	mFlags.typeView |= (CF_IS_ATARI | CF_IS_ALIVE | CF_IS_COLLISION_FLICK);
	clearStick();

	mUpdateContext.init(collisionUpdateMgr);
	mAcceleration = Vector3f(0.0f);
	clearCapture();

	mBounceTriangle    = nullptr;
	mCollisionPosition = Vector3f(0.0f, 1.0f, 0.0f);
	clearCapture();

	if (getMabiki()) {
		u32* mabiki = getMabiki();
		mabiki[1]   = 0;
		mabiki[0]   = 0;
	}
	onInit(arg);
	onInitPost(arg);
}

/*
 * --INFO--
 * Address:	8013B0F0
 * Size:	0000B4
 */
void Creature::kill(CreatureKillArg* arg) { killInline(arg); }

/*
 * --INFO--
 * Address:	8013B1A8
 * Size:	0000C8
 */
void Creature::setPosition(Vector3f& position, bool skipPostProc)
{
	onSetPosition(position);

	if (skipPostProc) {
		return;
	}

	updateTrMatrix();

	if (mModel) {
		PSMTXCopy(mObjMatrix.mMatrix.mtxView, mModel->mJ3dModel->mPosMtx);
		mModel->mJ3dModel->calc();
		if (mCollTree) {
			mCollTree->update();
		}
	}

	onSetPositionPost(position);
}

/*
 * --INFO--
 * Address:	8013B274
 * Size:	0000CC
 */
void Creature::initPosition(Vector3f& position)
{
	onSetPosition(position);
	updateTrMatrix();

	if (mModel) {
		PSMTXCopy(mObjMatrix.mMatrix.mtxView, mModel->mJ3dModel->mPosMtx);
		mModel->mJ3dModel->calc();
		if (mCollTree) {
			mCollTree->update();
		}
	}

	onSetPositionPost(position);
	onInitPosition(position);
}

/*
 * --INFO--
 * Address:	8013B340
 * Size:	0000A0
 */
void Creature::getYVector(Vector3f& outVector)
{
	outVector.x = mObjMatrix.mMatrix.structView.yx;
	outVector.y = mObjMatrix.mMatrix.structView.yy;
	outVector.z = mObjMatrix.mMatrix.structView.yz;
	outVector.normalise();
}

/*
 * --INFO--
 * Address:	8013B3E0
 * Size:	000034
 */
f32 Creature::getBodyRadius()
{
	Sys::Sphere boundingSphere;
	getBoundingSphere(boundingSphere);
	return boundingSphere.mRadius;
}

/*
 * --INFO--
 * Address:	8013B414
 * Size:	000034
 */
f32 Creature::getCellRadius()
{
	Sys::Sphere boundingSphere;
	getBoundingSphere(boundingSphere);
	return boundingSphere.mRadius;
}

/*
 * --INFO--
 * Address:	8013B448
 * Size:	000024
 */
char* Creature::getTypeName() { return ObjType::getName(mObjectTypeID); }

/*
 * --INFO--
 * Address:	8013B46C
 * Size:	00008C
 */
void Creature::getShadowParam(ShadowParam& param)
{
	param.mPosition = getPosition();
	param.mPosition.y += 0.5f;
	param.mBoundingSphere.mRadius   = 10.0f;
	param.mSize                     = 4.0f;
	param.mBoundingSphere.mPosition = Vector3f(0.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * Address:	8013B4F8
 * Size:	00000C
 */
bool Creature::needShadow() { return mLod.mFlags & AILOD_FLAG_NEED_SHADOW; }

/*
 * --INFO--
 * Address:	8013B504
 * Size:	000070
 */
void Creature::getLifeGaugeParam(LifeGaugeParam& param)
{
	param.mPosition            = getPosition();
	param.mCurHealthPercentage = 1.0f;
	param.mRadius              = 10.0f;
	param.mIsGaugeShown        = true;
}

/*
 * --INFO--
 * Address:	8013B574
 * Size:	000090
 */
void Creature::save(Stream& output, u8 flags)
{
	if (flags & CREATURE_SAVE_FLAG_POSITION) {
		Vector3f position = getPosition();
		position.write(output);
	}

	doSave(output);
}

/*
 * --INFO--
 * Address:	8013B604
 * Size:	0000E4
 */
void Creature::load(Stream& input, u8 flags)
{
	if (flags & CREATURE_SAVE_FLAG_POSITION) {
		Vector3f position;
		position.read(input);
		setPosition(position, false);
	}

	doLoad(input);
}

/*
 * --INFO--
 * Address:	8013B6E8
 * Size:	0000BC
 */
f32 Creature::calcSphereDistance(Creature* other)
{
	Sys::Sphere otherBoundSphere;
	other->getBoundingSphere(otherBoundSphere);

	Sys::Sphere srcBoundSphere;
	getBoundingSphere(srcBoundSphere);

	Vector3f dir = srcBoundSphere.mPosition - otherBoundSphere.mPosition;
	return _length(dir) - (srcBoundSphere.mRadius + otherBoundSphere.mRadius);
}

/*
 * --INFO--
 * Address:	8013B7A4
 * Size:	0000CC
 */
void Creature::applyAirDrag(f32 a, f32 b, f32 c)
{
	Vector3f vel = getVelocity();

	vel.y -= c * (a * vel.y);
	vel.x -= (vel.x * (a * b));
	vel.z -= (vel.z * (a * b));

	setVelocity(vel);
}

/*
 * --INFO--
 * Address:	8013B870
 * Size:	00003C
 */
void Creature::doAnimation()
{
	if (mModel) {
		mModel->mJ3dModel->calc();
	}
}

/*
 * --INFO--
 * Address:	8013B8AC
 * Size:	000004
 */
void Creature::doEntry() { }

/*
 * --INFO--
 * Address:	8013B8B0
 * Size:	000108
 */
void Creature::doSetView(int viewportNo)
{
	// 2 viewports maximum (2 player modes)
	P2ASSERTBOUNDSLINE(558, 0, viewportNo, 2);

	if (!mModel) {
		return;
	}

	P2ASSERTLINE(563, mModel);

	mModel->setCurrentViewNo((u16)viewportNo);
	if (Creature::usePacketCulling) {
		if (mLod.mFlags & (16 << viewportNo)) {
			mModel->showPackets();
			return;
		}

		mModel->hidePackets();
		return;
	}

	mModel->showPackets();
}

/*
 * --INFO--
 * Address:	8013B9B8
 * Size:	00002C
 */
void Creature::doViewCalc()
{
	if (mModel) {
		mModel->viewCalc();
	}
}

/*
 * --INFO--
 * Address:	8013B9E4
 * Size:	000010
 */
bool Creature::isPiki() { return mObjectTypeID == OBJTYPE_Piki; }

/*
 * --INFO--
 * Address:	8013B9F4
 * Size:	000014
 */
bool Creature::isNavi() { return mObjectTypeID == OBJTYPE_Navi; }

/*
 * --INFO--
 * Address:	8013BA08
 * Size:	000014
 */
bool Creature::isTeki() { return mObjectTypeID == OBJTYPE_Teki; }

/*
 * --INFO--
 * Address:	8013BA1C
 * Size:	000014
 */
bool Creature::isPellet() { return mObjectTypeID == OBJTYPE_Pellet; }

/*
 * --INFO--
 * Address:	8013BA30
 * Size:	000020
 */
bool Creature::sound_culling() { return !((mLod.mFlags & AILOD_FLAG_UNKNOWN4) || (mLod.mFlags & AILOD_FLAG_NEED_SHADOW)); }

/*
 * --INFO--
 * Address:	8013BA50
 * Size:	00009C
 */
void Creature::movie_begin(bool required)
{
	SET_FLAG(mFlags.typeView, CF_IS_MOVIE_ACTOR);

	if (!required) {
		SET_FLAG(mFlags.typeView, CF_IS_MOVIE_EXTRA);
		isPiki();
	} else {
		RESET_FLAG(mFlags.typeView, CF_IS_MOVIE_EXTRA);
		isPiki();
	}
	on_movie_begin(required);
}

/*
 * TODO: Determine if param really should be named "required".
 * --INFO--
 * Address:	8013BAEC
 * Size:	000050
 */
void Creature::movie_end(bool required)
{
	on_movie_end(required);
	RESET_FLAG(mFlags.typeView, CF_IS_MOVIE_ACTOR);
	RESET_FLAG(mFlags.typeView, CF_IS_MOVIE_EXTRA);
}

/*
 * --INFO--
 * Address:	8013BB3C
 * Size:	0000E0
 */
WaterBox* Creature::checkWater(WaterBox* waterBox, Sys::Sphere& boundSphere)
{
	if (waterBox) {
		if (!waterBox->inWater(boundSphere)) {
			if (mapMgr) {
				waterBox = mapMgr->findWater(boundSphere);
			}

			if (!waterBox) {
				outWaterCallback();
				waterBox = nullptr;
			}
		}
	} else {
		WaterBox* wb = nullptr;
		if (mapMgr) {
			wb = mapMgr->findWater(boundSphere);
		}

		waterBox = wb;
		if (waterBox) {
			inWaterCallback(waterBox);
		}
	}

	return waterBox;
}

/*
 * --INFO--
 * Address:	8013BC24
 * Size:	000144
 */
int Creature::checkHell(Creature::CheckHellArg& hellArg)
{
	Vector3f pos = getPosition();

	if (pos.y < -500.0f) {
		if (isPiki() && static_cast<FakePiki*>(this)->isPikmin()) {
			deathMgr->inc(0);
		}

		if (hellArg.mIsKillPiki) {
			killInline(nullptr);
		}

		return CREATURE_HELL_DEATH;
	}

	return pos.y < -300.0f;
}

/*
 * --INFO--
 * Address:	8013BD68
 * Size:	000178
 */
void Creature::updateCell()
{
	if (gameSystem && gameSystem->mFlags & 4) {
		return;
	}

	mPassID = -1;

	Sys::Sphere ball(getPosition());
	ball.mRadius = getCellRadius();

	SweepPrune::Object::mMinX.mRadius = ball.mPosition.x - ball.mRadius;
	SweepPrune::Object::mMaxX.mRadius = ball.mPosition.x + ball.mRadius;
	SweepPrune::Object::mMinZ.mRadius = ball.mPosition.z - ball.mRadius;
	SweepPrune::Object::mMaxZ.mRadius = ball.mPosition.z + ball.mRadius;

	SweepPrune::Object* sweepObj = this;

	CellPyramid* mgr;
	sweepObj->mMinX.insertSort((mgr = cellMgr)->mXNode);
	sweepObj->mMaxX.insertSort(mgr->mXNode);
	sweepObj->mMinZ.insertSort(mgr->mZNode);
	sweepObj->mMaxZ.insertSort(mgr->mZNode);

	if (cellMgr) {
		CellPyramid::sCellBugName = getCreatureName();
		CellPyramid::sCellBugID   = getCreatureID();
		cellMgr->entry(this, ball, mCellLayerIndex, mCellRect);
	}
}

/*
 * --INFO--
 * Address:	8013BEE8
 * Size:	000044
 */
int Creature::getCellPikiCount()
{
	if (cellMgr) {
		return cellMgr->getPikiCount(mCellLayerIndex, mCellRect);
	}

	return 0;
}

/*
 * --INFO--
 * Address:	8013BF2C
 * Size:	0000B0
 */
void Creature::applyImpulse(Vector3f& unused, Vector3f& impulse)
{
	Vector3f oldVelocity = getVelocity();
	Vector3f newVelocity = oldVelocity;

	newVelocity = newVelocity + (impulse * mMass);
	setVelocity(newVelocity);
}

/*
 * --INFO--
 * Address:	8013BFDC
 * Size:	0002E4
 */
void Creature::checkCollision(CellObject* cellObj)
{
	Creature* cellCreature = static_cast<Creature*>(cellObj);

	if (isDebugCollision()) {
		getCreatureName();
		cellCreature->getCreatureName();
	}

	if (!cellCreature->isAtari() || !isAtari()) {
		return;
	}

	Creature* creatureObj = cellCreature;

	// TODO: This is cancer, fix
	if (!((!isStickTo() || mSticker != cellCreature) && (!creatureObj->isStickTo() || creatureObj->mSticker != this)
	      && !ignoreAtari(creatureObj))
	    || creatureObj->ignoreAtari(this)) {
		return;
	}

	if (!creatureObj->isAlive() || !isAlive()) {
		return;
	}

	isDebugCollision();

	Delegate3<Creature, CollPart*, CollPart*, Vector3f&> delegate
	    = Delegate3<Creature, CollPart*, CollPart*, Vector3f&>(this, &resolveOneColl);
	currOp = creatureObj;

	if (isDebugCollision()) {
		CollTree::mDebug = true;
	}

	bool creatureCheck = true;
	if (!isPiki() && !isNavi()) {
		creatureCheck = false;
	}

	bool objCheck = true;
	if (!cellCreature->isPiki() && !cellCreature->isNavi()) {
		objCheck = false;
	}

	CollPart* collPart1;
	CollPart* collPart2;
	Vector3f vec;

	if ((creatureCheck && objCheck) || (!creatureCheck && !objCheck)) {
		if (mCollTree->checkCollision(creatureObj->mCollTree, &collPart1, &collPart2, vec)) {
			delegate.invoke(collPart1, collPart2, vec);
		}
	} else {
		mCollTree->checkCollisionMulti(creatureObj->mCollTree, (IDelegate3<CollPart*, CollPart*, Vector3<f32>&>*)&delegate);
	}

	CollTree::mDebug = false;
	currOp           = nullptr;
}

/*
 * --INFO--
 * Address:	8013C2C0
 * Size:	0008CC
 */
void Creature::resolveOneColl(CollPart* source, CollPart* dest, Vector3f& direction)
{
	Creature* op = currOp;
	if (!currOp) {
		return;
	}

	if (isDebugCollision()) {
		getCreatureName();
		op->getCreatureName();
	}

	bool flickCheck = false;
	if (!isCollisionFlick() || !op->isCollisionFlick()) {
		flickCheck = true;
	}

	Vector3f vec(-direction.x, -direction.y, -direction.z);
	if (vec.normalise() == 0.0f) {
		vec = Vector3f(0.0f, 0.0f, 1.0f);
	}

	Vector3f vel1;
	Vector3f vel2;
	Vector3f disp1 = source->mPosition + (vec * source->mRadius);
	Vector3f disp2 = dest->mPosition - (vec * dest->mRadius);

	getVelocityAt(disp1, vel1);
	op->getVelocityAt(disp2, vel2);

	f32 massRatio;
	f32 massRatioOp;

	f32 sum = mMass + op->mMass;
	if (sum > 0.0f) {
		massRatio   = mMass / sum;
		massRatioOp = 1.0f - massRatio;
	} else {
		massRatio = massRatioOp = 0.5f;
	}

	f32 fps = 1.0f / sys->mDeltaTime;
	if (isNavi() && !op->isNavi()) {
		if (!op->isPiki()) {
			addAccel(mAcceleration, direction, massRatio, fps, 0.5f, 0.0f);
		}
	} else {
		setAccel(mAcceleration, direction, massRatio, fps, 0.5f, 0.0f);
	}

	if (op->isNavi() && !isNavi()) {
		if (!isPiki()) {
			setOpAccel(op->mAcceleration, direction, massRatioOp, fps, 0.5f, 0.0f);
		}
	} else {
		setOpAccel(op->mAcceleration, direction, massRatioOp, fps, 0.5f, 0.0f);
	}

	f32 accelMag = mAcceleration.length();
	if (accelMag > 200.0f) {
		f32 accelNorm = 200.0f * (1.0f / accelMag);
		mAcceleration.x *= accelNorm;
		mAcceleration.y *= accelNorm;
		mAcceleration.z *= accelNorm;
	}

	f32 opAccelMag = op->mAcceleration.length();
	if (opAccelMag > 200.0f) {
		f32 opAccelNorm = 200.0f * (1.0f / opAccelMag);
		op->mAcceleration.x *= opAccelNorm;
		op->mAcceleration.y *= opAccelNorm;
		op->mAcceleration.z *= opAccelNorm;
	}

	if (flickCheck) {
		mAcceleration     = Vector3f(0.0f);
		op->mAcceleration = Vector3f(0.0f);
	}

	CollEvent collEvent1(op, dest, source);

	Vector3f sep = vel1 - vel2;
	f32 sepDot   = dot(sep, vec);
	collisionCallback(collEvent1);

	CollEvent collEvent2(this, source, dest);
	op->collisionCallback(collEvent2);

	if (sepDot <= 0.0f) {
		if (isDebugCollision()) {
			getCreatureName();
			op->getCreatureName();
		}

		return;
	}

	isDebugCollision();
	if (flickCheck) {
		isDebugCollision();
		return;
	}

	f32 naviFactor = 0.1f;
	if (isNavi() || op->isNavi()) {
		naviFactor = 0.0f;
	}

	bool checkSum2 = false;
	f32 factor5    = -(1.0f + naviFactor) * sepDot;
	f32 sum2       = mMass + op->mMass;
	if (sum2 == 0.0f) {
		sum2      = 2.0f;
		checkSum2 = true;
	}

	sum2 += getAngularEffect(disp1, vec);
	sum2 += op->getAngularEffect(disp2, vec);
	f32 posFac           = factor5 / (sum2);
	Vector3f updatedVec1 = vec * posFac;
	Vector3f updatedVec2 = vec * -posFac;

	if (!checkSum2) {
		applyImpulse(disp1, updatedVec1);
		op->applyImpulse(disp2, updatedVec2);
		return;
	}

	Vector3f updatedVel1 = getVelocity();
	updatedVel1          = Vector3f(updatedVel1.x + updatedVec1.x, updatedVel1.y + updatedVec1.y, updatedVel1.z + updatedVec1.z);
	setVelocity(updatedVel1);

	Vector3f updatedVel2 = op->getVelocity();
	updatedVel2          = Vector3f(updatedVel2.x + updatedVec2.x, updatedVel2.y + updatedVec2.y, updatedVel2.z + updatedVec2.z);
	op->setVelocity(updatedVel2);
}

} // namespace Game
