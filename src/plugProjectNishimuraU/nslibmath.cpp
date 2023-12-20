#include "types.h"
#include "Vector3.h"

namespace Game {
namespace NsMathExp {
/**
 * @note Address: 0x8023D7B0
 * @note Size: 0xA8
 * Aside from arg order and defines, identical to Pikmin 1's NsCalculation::calcLagrange
 * Matches!
 */
void calcLagrange(const Vector3f* p_vec, float p2, Vector3f& new_vec)
// calculates Lagrange, stores in new_vec
{
	float p2_sub1 = p2 - 1.0f;
	float p2_sub2 = p2 - 2.0f;
	new_vec.x     = p2_sub1 * (p_vec[2].x * 0.5f * p2) + (p2_sub2 * (p_vec[0].x * 0.5f * p2_sub1) - (p2_sub2 * (p_vec[1].x * p2)));
	new_vec.y     = p2_sub1 * (p_vec[2].y * 0.5f * p2) + (p2_sub2 * (p_vec[0].y * 0.5f * p2_sub1) - (p2_sub2 * (p_vec[1].y * p2)));
	new_vec.z     = p2_sub1 * (p_vec[2].z * 0.5f * p2) + (p2_sub2 * (p_vec[0].z * 0.5f * p2_sub1) - (p2_sub2 * (p_vec[1].z * p2)));
}

/**
 * @note Address: 0x8023D858
 * @note Size: 0x1D8
 */
void calcJointPos(const Vector3f& inPos1, const Vector3f& inPos2, f32 p1, f32 p2, Vector3f& outPos1, Vector3f& outPos2)
{
	f32 p1Sqr    = p1 * p1;
	f32 p2Sqr    = p2 * p2;
	Vector3f vec = inPos2;

	Vector3f sep = inPos2 - inPos1;
	f32 sqrDist  = sep.sqrMagnitude(); // f11
	if (!(sqrDist < 1.0E-6f)) {
		f32 factor = (0.5f / sqrDist) * (sqrDist + (p1Sqr - p2Sqr)); // f3
		Vector3f vec1(factor * sep.x + inPos1.x, factor * sep.y + inPos1.y, factor * sep.z + inPos1.z);
		Vector3f vec2 = vec1 - inPos1;
		f32 val1      = p1Sqr - SQUARE(vec2.x) - SQUARE(vec2.y) - SQUARE(vec2.z); // f30
		if (!(val1 <= 0.0f)) {
			Vector3f cross1 = cross(outPos1, sep);
			outPos1         = cross(cross1, sep);
			f32 outSqr      = outPos1.sqrMagnitude();
			if (outSqr != 0.0f) {
				f32 len   = _sqrtf2(val1 / outSqr);
				outPos2.x = len * outPos1.x + cross1.x;
				outPos2.y = len * outPos1.y + cross1.y;
				outPos2.z = len * outPos1.z + cross1.z;
				return;
			}
		}
	}

	f32 p1new = _sqrtf2(p1Sqr); // f7
	f32 p2new = _sqrtf2(p2Sqr); // f3

	f32 radSum = p1new / (p1new + p2new); // f6

	outPos2 = Vector3f(radSum * vec.x + inPos1.x, radSum * vec.y + inPos1.y, radSum * vec.z + inPos1.z);

	/*
	.loc_0x0:
	  stwu      r1, -0x30(r1)
	  stfd      f31, 0x20(r1)
	  psq_st    f31,0x28(r1),0,0
	  stfd      f30, 0x10(r1)
	  psq_st    f30,0x18(r1),0,0
	  lfs       f0, 0x4(r4)
	  fmuls     f5, f1, f1
	  lfs       f8, 0x4(r3)
	  fmuls     f4, f2, f2
	  lfs       f3, 0x0(r4)
	  fsubs     f1, f0, f8
	  lfs       f7, 0x0(r3)
	  lfs       f2, 0x8(r4)
	  fsubs     f0, f3, f7
	  lfs       f10, 0x8(r3)
	  fmuls     f6, f1, f1
	  fsubs     f2, f2, f10
	  lfs       f3, -0x3D54(r2)
	  fmadds    f6, f0, f0, f6
	  fmadds    f11, f2, f2, f6
	  fcmpo     cr0, f11, f3
	  blt-      .loc_0x154
	  lfs       f6, -0x3D58(r2)
	  fsubs     f3, f5, f4
	  lfs       f9, -0x3D50(r2)
	  fdivs     f6, f6, f11
	  fadds     f3, f11, f3
	  fmuls     f3, f6, f3
	  fmadds    f12, f3, f0, f7
	  fmadds    f13, f3, f1, f8
	  fmadds    f3, f3, f2, f10
	  fsubs     f6, f12, f7
	  fsubs     f7, f13, f8
	  fsubs     f8, f3, f10
	  fnmsubs   f6, f6, f6, f5
	  fnmsubs   f6, f7, f7, f6
	  fnmsubs   f30, f8, f8, f6
	  fcmpo     cr0, f30, f9
	  cror      2, 0, 0x2
	  beq-      .loc_0x154
	  lfs       f31, 0x0(r5)
	  lfs       f11, 0x4(r5)
	  fmuls     f7, f31, f2
	  lfs       f10, 0x8(r5)
	  fmuls     f6, f11, f0
	  fmuls     f8, f10, f1
	  fmsubs    f10, f10, f0, f7
	  fmsubs    f31, f31, f1, f6
	  fmsubs    f11, f11, f2, f8
	  fmuls     f8, f2, f10
	  fmuls     f7, f0, f31
	  fmuls     f6, f1, f11
	  fmsubs    f8, f1, f31, f8
	  fmsubs    f7, f2, f11, f7
	  fmsubs    f6, f0, f10, f6
	  stfs      f8, 0x0(r5)
	  stfs      f7, 0x4(r5)
	  stfs      f6, 0x8(r5)
	  lfs       f10, 0x0(r5)
	  lfs       f6, 0x4(r5)
	  fmuls     f7, f10, f10
	  lfs       f8, 0x8(r5)
	  fmuls     f6, f6, f6
	  fmuls     f8, f8, f8
	  fadds     f6, f7, f6
	  fadds     f6, f8, f6
	  fcmpu     cr0, f9, f6
	  beq-      .loc_0x154
	  fdivs     f1, f30, f6
	  fcmpo     cr0, f1, f9
	  ble-      .loc_0x12C
	  ble-      .loc_0x130
	  fsqrte    f0, f1
	  fmuls     f1, f0, f1
	  b         .loc_0x130

	.loc_0x12C:
	  fmr       f1, f9

	.loc_0x130:
	  fmadds    f0, f1, f10, f12
	  stfs      f0, 0x0(r6)
	  lfs       f0, 0x4(r5)
	  fmadds    f0, f1, f0, f13
	  stfs      f0, 0x4(r6)
	  lfs       f0, 0x8(r5)
	  fmadds    f0, f1, f0, f3
	  stfs      f0, 0x8(r6)
	  b         .loc_0x1C0

	.loc_0x154:
	  lfs       f7, -0x3D50(r2)
	  fcmpo     cr0, f5, f7
	  ble-      .loc_0x174
	  ble-      .loc_0x170
	  fsqrte    f3, f5
	  fmuls     f7, f3, f5
	  b         .loc_0x174

	.loc_0x170:
	  fmr       f7, f5

	.loc_0x174:
	  lfs       f3, -0x3D50(r2)
	  fcmpo     cr0, f4, f3
	  ble-      .loc_0x194
	  ble-      .loc_0x190
	  fsqrte    f3, f4
	  fmuls     f3, f3, f4
	  b         .loc_0x194

	.loc_0x190:
	  fmr       f3, f4

	.loc_0x194:
	  fadds     f6, f7, f3
	  lfs       f5, 0x0(r3)
	  lfs       f4, 0x4(r3)
	  lfs       f3, 0x8(r3)
	  fdivs     f6, f7, f6
	  fmadds    f5, f6, f0, f5
	  fmadds    f1, f6, f1, f4
	  fmadds    f0, f6, f2, f3
	  stfs      f5, 0x0(r6)
	  stfs      f1, 0x4(r6)
	  stfs      f0, 0x8(r6)

	.loc_0x1C0:
	  psq_l     f31,0x28(r1),0,0
	  lfd       f31, 0x20(r1)
	  psq_l     f30,0x18(r1),0,0
	  lfd       f30, 0x10(r1)
	  addi      r1, r1, 0x30
	  blr
	*/
}
} // namespace NsMathExp
} // namespace Game
