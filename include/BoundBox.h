#ifndef _BOUNDBOX_H
#define _BOUNDBOX_H

#include "Vector3.h"

namespace Sys {
struct Sphere;
} // namespace Sys

struct BoundBox {
	// define min big and max small so that 'include' will always 'snap' to point
	BoundBox()
	    : mMin(32768.0f)
	    , mMax(-32768.0f)
	{
	}

	BoundBox(f32 min, f32 max)
	    : mMin(min)
	    , mMax(max)
	{
	}

	void makeBoundSphere(Sys::Sphere&);
	void read(struct Stream&);
	void transform(struct Matrixf&);

	/**
	 * @fabricated
	 */
	inline void include(Vector3f& point)
	{
		if (point.x < mMin.x) {
			mMin.x = point.x;
		}
		if (point.y < mMin.y) {
			mMin.y = point.y;
		}
		if (point.z < mMin.z) {
			mMin.z = point.z;
		}
		if (point.x > mMax.x) {
			mMax.x = point.x;
		}
		if (point.y > mMax.y) {
			mMax.y = point.y;
		}
		if (point.z > mMax.z) {
			mMax.z = point.z;
		}
	}

	Vector3f mMin; // _00
	Vector3f mMax; // _0C
};

struct BoundBox2d {
	f32 _00;
	f32 _04;
	f32 _08;
	f32 _0C;
};

#endif
