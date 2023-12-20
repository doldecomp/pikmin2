#include "nans.h"
#include "sysMath.h"
#include "Light.h"

// Fix rodata mismatch with null bytes
static const char _RODATA_FIX[0xC] = { '\0' };

namespace TreasureLight {
/**
 * @note Address: 0x8013286C
 * @note Size: 0x150
 */
Mgr::Mgr()
    : LightMgr("���󃉃C�g")
{
	mRotationAngle  = 300.0f;
	mElevationAngle = 330.0f;

	mMainLight             = new LightObj("���C�����C�g", GX_LIGHT0, TYPE_Spot, JUtility::TColor(0xFF, 0xFF, 0xFF, 0xFF));
	mMainLight->mSpotFn    = 3;
	mMainLight->mElevation = Vector3f(0.0f, -1.0f, 0.0f);
	registLightObj(mMainLight);

	mSpecLight          = new LightObj("�X�y�L����-���C�g", GX_LIGHT7, TYPE_Spec, JUtility::TColor(0xFF, 0xFF, 0xFF, 0xFF));
	mSpecLight->mKScale = 40.0f;
	registLightObj(mSpecLight);

	mAmbientLight.mColor = Color4(0x32, 0x32, 0x32, 0xFF);
}

/**
 * @note Address: 0x801329BC
 * @note Size: 0x4
 */
void Mgr::update() { }

/**
 * @note Address: 0x801329C0
 * @note Size: 0x44
 */
void Mgr::set(Graphics& gfx)
{
	setCommonProc();
	LightMgr::set(gfx);
}

/**
 * @note Address: 0x80132A04
 * @note Size: 0x44
 */
void Mgr::set(Matrixf& mtx)
{
	setCommonProc();
	LightMgr::set(mtx);
}

/**
 * @note Address: 0x80132A48
 * @note Size: 0x184
 * Credits: Altafen
 *
 * https://en.wikipedia.org/wiki/Spherical_coordinate_system
 * You can convert an angle �� to its position on a circle of radius r:
 * x = r * cos(��)
 * y = r * sin(��)
 *
 * So now imagine a line going in the direction of the 2D angle
 * where y is now height, x is now how far away it is from the center pole
 *
 * height   = r * sin(��)
 * distance = r * cos(��)
 *
 * Since the 2D x/y have to shrink a bit as the sphere gets smaller the higher you go,
 * use distance as the radius before putting them in the 2D equations, and you get
 *
 * x = (r * cos(��)) * cos(��)
 * y = (r * cos(��)) * sin(��)
 * z = r * sin(��)
 */
void Mgr::setCommonProc()
{
	f32 rotation_angle  = (mRotationAngle * DEG2RAD) * PI;
	f32 elevation_angle = (mElevationAngle * DEG2RAD) * PI;

	f32 radius = 3000.0f;
	Vector3f rotation;
	rotation.x = pikmin2_cosf(elevation_angle) * radius * pikmin2_sinf(rotation_angle);
	rotation.y = pikmin2_sinf(elevation_angle) * -radius;
	rotation.z = pikmin2_cosf(elevation_angle) * radius * pikmin2_cosf(rotation_angle);

	Vector3f elevation(-rotation.x, -rotation.y, -rotation.z);
	elevation.qNormalise();

	mMainLight->mPosition      = rotation;
	mMainLight->mElevation     = elevation;
	mMainLight->mRefBrightness = 0.85f;

	mSpecLight->mPosition  = rotation;
	mSpecLight->mElevation = elevation;
}

/**
 * @note Address: 0x80132BCC
 * @note Size: 0x20
 */
void Mgr::drawDebugInfo(Graphics& gfx) { LightMgr::drawDebugInfo(gfx); }
} // namespace TreasureLight
