#ifndef _GAME_AICONSTANTS_H
#define _GAME_AICONSTANTS_H

#include "TagParm.h"

namespace Game {
struct AIConstants : public TagParameters {
	AIConstants();
	virtual ~AIConstants() {};

	PrimTagParm<f32> mGravity;     // _1C
	PrimTagParm<int> mDopeCount;   // _2C
	PrimTagParm<int> mDebt;        // _3C
	PrimTagParm<f32> mCameraAngle; // _4C
};

extern AIConstants* _aiConstants;
} // namespace Game

#endif
