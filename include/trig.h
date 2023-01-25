#ifndef _TRIG_H
#define _TRIG_H

#include "types.h"
#include "Vector3.h"
#include "JSystem/JMath.h"

#define TAU 6.2831855f

inline bool checkASinCosBounds(f32 x) { return (x >= -1.0f) && (x <= 1.0f); }

inline f32 pikmin2_sinf(f32 x)
{
	if (x < 0.0f) {
		return -JMath::sincosTable_.mTable[((int)(x *= -325.9493f) & 0x7ffU)].first;
	}
	return JMath::sincosTable_.mTable[((int)(x *= 325.9493f) & 0x7ffU)].first;
}

inline f32 pikmin2_cosf(f32 x)
{
	if (x < 0.0f) {
		x = -x;
	}
	return JMath::sincosTable_.mTable[((int)(x *= 325.9493f) & 0x7ffU)].second;
}

inline f32 pikmin2_acos(f32 x)
{
	if (x >= 1.0f) {
		return 0.0f;
	} else if (x <= -1.0f) {
		return PI;
	} else if (x < 0.0f) {
		f32 dumb = HALF_PI;
		f32 acos = JMath::asinAcosTable_.mTable[(u32)(-x * 1023.5f)];
		return acos + dumb;
	} else {
		return HALF_PI - JMath::asinAcosTable_.mTable[(u32)(x * 1023.5f)];
	}
}

inline f32 angXZ(Vector3f& vec1, Vector3f& vec2)
{
	Vector3f pos = vec1 - vec2;
	return roundAng(JMath::atanTable_.atan2_(pos.x, pos.z));
}

inline f32 angXZ(f32 x, f32 z, Vector3f& vec)
{
	Vector3f pos = vec;
	return roundAng(JMath::atanTable_.atan2_(x - pos.x, z - pos.z));
}

inline f32 _angXZ(f32 x1, f32 z1, f32 x2, f32 z2) { return roundAng(JMath::atanTable_.atan2_(x1 - x2, z1 - z2)); }

inline int GetTableIdxNeg(f32 x) { return x *= -325.9493f; }

inline int GetTableIdxPos(f32 x) { return x *= 325.9493f; }

inline f32 altSin(f32 x)
{
	if (x < 0.0f) {
		return -JMath::sincosTable_.mTable[GetTableIdxNeg(x) & 0x7ffU].first;
	}
	return JMath::sincosTable_.mTable[GetTableIdxPos(x) & 0x7ffU].first;
}

inline f32 scaledSin(f32 theta) { return altSin(theta * TAU); }

inline f32 absVal(f32 val) { return (val > 0.0f) ? val : -val; }

inline int absVal(int val) { return (val > 0) ? val : -val; }

inline f32 adjustVal(f32 y, f32 x, f32 delta)
{
	f32 diff = absVal(y - x);

	return (diff < delta) ? x : (y < x) ? y + delta : y - delta;
}

inline int adjustValInt(int current, int dest, const int delta)
{
	return (absVal(current - dest) < delta) ? dest : (current < dest ? current += delta : current -= delta);
}

#endif
