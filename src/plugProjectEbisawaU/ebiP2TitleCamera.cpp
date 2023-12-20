#include "ebi/title/TTitle.h"
#include "nans.h"

namespace ebi {
namespace title {
/**
 * @note Address: 0x803C1EBC
 * @note Size: 0x74
 */

void TTitleCameraMgr::update()
{
	mPosition.y += mParms.mYOffset.mValue;
	_18C.x          = 0.0f;
	_18C.y          = 0.0f;
	_18C.z          = -1.0f;
	mLookAtPosition = mPosition;
	mLookAtPosition.y -= 1.0f;
	mViewAngle = mParms.mFOVY.mValue;
	Camera::update();
}

} // namespace title
} // namespace ebi
