#include "types.h"
#include "CarryInfo.h"
#include "Graphics.h"
#include "Viewport.h"
#include "JSystem/JKR/JKRArchive.h"
#include "Game/MoviePlayer.h"
#include "Dolphin/gx.h"
#include "nans.h"

namespace {
const Color4 sColorTableNumerator[7] = {
	Color4(30, 30, 255, 255),   // blue
	Color4(255, 0, 0, 255),     // red
	Color4(234, 234, 0, 255),   // yellow
	Color4(255, 255, 255, 255), // white (used for treasures to pod)
	Color4(255, 255, 255, 255), // white (used for treasures to ship)
	Color4(102, 153, 153, 255), // gray  (used when not enough to lift?)
	Color4(102, 211, 211, 255), // gray  (used in scale blocks?)
};

const Color4 sColorTableDenominator[7] = {
	Color4(30, 30, 255, 255),   Color4(255, 0, 0, 255),     Color4(234, 234, 0, 255),   Color4(255, 255, 255, 255),
	Color4(255, 255, 255, 255), Color4(102, 153, 153, 255), Color4(112, 216, 216, 255), // this is the only one where
	                                                                                    // the denominator is different
};
} // namespace

CarryInfoMgr* carryInfoMgr;

/*
 * --INFO--
 * Address:	8011AFD0
 * Size:	00000C
 */
void CarryInfo::disappear() { mHidden = true; }

/*
 * --INFO--
 * Address:	8011AFDC
 * Size:	000264
 */
void CarryInfo::update(const CarryInfoParam& param)
{
	if (mHidden != CINFO_Hidden) {
		switch (param.mUseType) {
		case 0: {
			switch (mHidden) {
			case CINFO_Appear: {
				f32 temp = 0.04f * (param.mYOffsetMax - mYOffset);
				mGrowRate += temp;
				mYOffset += mGrowRate;
				mScale = mYOffset / param.mYOffsetMax;
				break;
			}

			case CINFO_1: {
				f32 temp = 0.04f * -mYOffset;
				mGrowRate += temp;
				mYOffset += mGrowRate;

				if (mYOffset < 0.0f) {
					mGrowRate = 0.0f;
					mYOffset  = 0.0f;
					mScale    = 0.0f;
					mHidden   = CINFO_Hidden;

				} else {
					mScale = mYOffset / param.mYOffsetMax;
				}
				break;
			}
			}
			f32 modifier = 1.0f;
			mGrowRate *= 0.88f;

			modifier        = (mScale > modifier) ? modifier : mScale;
			f32 scaledAlpha = 255.0f * modifier;
			f32 alpha;
			if (scaledAlpha >= 0.0f) {
				alpha = 0.5f + scaledAlpha;
			} else {
				alpha = scaledAlpha - 0.5f;
			}
			mAlpha = (u8)alpha;
			break;
		}

		case 1: {
			mCounter++;
			if (mYOffset < param.mYOffsetMax) {
				f32 temp = (param.mYOffsetMax - mYOffset) * 0.04f;
				mGrowRate += temp;
			}
			mYOffset += mGrowRate;
			mGrowRate *= 0.9f;
			mScale = mYOffset / param.mYOffsetMax;
			if (mScale > 1.0f) {
				mScale = 1.0f;
			}

			switch (mHidden) {
			case CINFO_Appear: {
				f32 scaledAlpha = mScale * 255.0f;
				f32 alpha;
				if (scaledAlpha >= 0.0f) {
					alpha = 0.5f + scaledAlpha;
				} else {
					alpha = scaledAlpha - 0.5f;
				}
				mAlpha = (u8)alpha;
				break;
			}

			case CINFO_1: {
				if (mAlpha > 8) {
					mAlpha -= 8;
				} else {
					mAlpha    = 0;
					mGrowRate = 0.0f;
					mYOffset  = 0.0f;
					mScale    = 0.0f;
					mHidden   = CINFO_Hidden;
				}
				break;
			}
			}

			break;
		}
		}
	}
}

/*
 * --INFO--
 * Address:	8011B240
 * Size:	0004AC
 */
void CarryInfo::draw(Graphics& gfx, CarryInfoParam& param)
{
	if (mHidden != CINFO_Hidden) {
		Viewport* vp = gfx.mCurrentViewport;
		Matrixf* mtx = vp->getMatrix(1);
		Matrixf newmtx;

		Vector3f temp = mtx->getBasis(0);
		temp *= mScale;
		newmtx.setBasis(0, temp);
		temp = mtx->getBasis(1);
		temp *= mScale;
		newmtx.setBasis(1, temp);
		temp = mtx->getBasis(2);
		temp *= mScale;
		newmtx.setBasis(2, temp);
		temp = mtx->getBasis(3);
		temp *= mScale;
		newmtx.setBasis(3, temp);

		Matrixf storemtx;
		PSMTXConcat(vp->getMatrix(1)->mMatrix.mtxView, newmtx.mMatrix.mtxView, storemtx.mMatrix.mtxView);
		GXLoadPosMtxImm(storemtx.mMatrix.mtxView, 0);

		if (param.mUseType == 1) {
			f32 temp = (f32)mCounter * TAU * 0.03125;
			temp     = pikmin2_sinf(temp);
			temp     = (temp + 1.0f) * 0.5f;
			Color4 color2, color;
			color2.a = mAlpha;

			color.r = temp * (255.0f);
			color.g = temp * (155.0f);
			color.b = temp * (59.0f);
			color.a = temp * (color2.a);

			color2.r = 0xff;
			color2.g = 0x8a;
			color2.b = 0x15;

			drawNumber(gfx, 7.0f, 0.0f, param.mCarryInfo.mGrowRate, color2, 1.0f);
			drawNumberPrim(gfx, (-7.0f * 0.5f - 3.0f), 0.0f, 11, color, 1.0f);
		} else if (param.mUseType == 0) {
			f32 scale1, scale2, offs1, offs2;
			if (param.mIsTopFirst) {
				scale1 = 1.1f;
				scale2 = 0.75f;
				offs1  = 10.15f;
				offs2  = -7.7f;
			} else {
				scale1 = 0.75f;
				scale2 = 1.1;
				offs1  = 7.7f;
				offs2  = -10.15f;
			}
			Color4 colortop, colorbottom;
			colortop.r = sColorTableNumerator[param.mColor].r;
			colortop.g = sColorTableNumerator[param.mColor].g;
			colortop.b = sColorTableNumerator[param.mColor].b;
			colortop.a = mAlpha;

			colorbottom.r = sColorTableDenominator[param.mColor].r;
			colorbottom.g = sColorTableDenominator[param.mColor].g;
			colorbottom.b = sColorTableDenominator[param.mColor].b;
			colorbottom.a = colortop.a;

			drawNumberPrim(gfx, 0.0f, 0.0f, 10, colortop, 1.0f);
			drawNumber(gfx, 0.0f, offs1, param.mValue1, colortop, scale1);
			drawNumber(gfx, 0.0f, offs2, param.mValue2, colorbottom, scale2);
		}
	}
	/*
	stwu     r1, -0x150(r1)
	mflr     r0
	stw      r0, 0x154(r1)
	stfd     f31, 0x140(r1)
	psq_st   f31, 328(r1), 0, qr0
	stfd     f30, 0x130(r1)
	psq_st   f30, 312(r1), 0, qr0
	stfd     f29, 0x120(r1)
	psq_st   f29, 296(r1), 0, qr0
	stfd     f28, 0x110(r1)
	psq_st   f28, 280(r1), 0, qr0
	stmw     r27, 0xfc(r1)
	mr       r29, r3
	mr       r30, r4
	lbz      r0, 0xc(r3)
	mr       r31, r5
	cmplwi   r0, 2
	beq      lbl_8011B6B8
	lwz      r27, 0x25c(r30)
	li       r4, 1
	mr       r3, r27
	bl       getMatrix__8ViewportFb
	lfs      f0, 0(r3)
	li       r4, 1
	lfs      f1, 8(r29)
	fmuls    f0, f0, f1
	stfs     f0, 0x18(r1)
	lfs      f0, 4(r3)
	fmuls    f0, f0, f1
	stfs     f0, 0x28(r1)
	lfs      f0, 8(r3)
	fmuls    f0, f0, f1
	stfs     f0, 0x38(r1)
	lfs      f0, 0x10(r3)
	fmuls    f0, f0, f1
	stfs     f0, 0x1c(r1)
	lfs      f0, 0x14(r3)
	fmuls    f0, f0, f1
	stfs     f0, 0x2c(r1)
	lfs      f0, 0x18(r3)
	fmuls    f0, f0, f1
	stfs     f0, 0x3c(r1)
	lfs      f0, 0x20(r3)
	fmuls    f0, f0, f1
	stfs     f0, 0x20(r1)
	lfs      f0, 0x24(r3)
	fmuls    f0, f0, f1
	stfs     f0, 0x30(r1)
	lfs      f0, 0x28(r3)
	mr       r3, r27
	fmuls    f0, f0, f1
	stfs     f0, 0x40(r1)
	lfs      f0, 4(r31)
	stfs     f0, 0x24(r1)
	lfs      f1, 8(r31)
	lfs      f0, 4(r29)
	fadds    f0, f1, f0
	stfs     f0, 0x34(r1)
	lfs      f0, 0xc(r31)
	stfs     f0, 0x44(r1)
	bl       getMatrix__8ViewportFb
	addi     r4, r1, 0x18
	addi     r5, r1, 0x48
	bl       PSMTXConcat
	addi     r3, r1, 0x48
	li       r4, 0
	bl       GXLoadPosMtxImm
	lwz      r6, 0(r31)
	cmpwi    r6, 1
	beq      lbl_8011B458
	bge      lbl_8011B69C
	cmpwi    r6, 0
	bge      lbl_8011B368
	b        lbl_8011B69C

lbl_8011B368:
	lwz      r0, 0x1c(r31)
	cmpwi    r0, 0
	bne      lbl_8011B388
	lfs      f29, lbl_80517B7C@sda21(r2)
	lfs      f28, lbl_80517B80@sda21(r2)
	lfs      f31, lbl_80517B84@sda21(r2)
	lfs      f30, lbl_80517B88@sda21(r2)
	b        lbl_8011B398

lbl_8011B388:
	lfs      f29, lbl_80517B80@sda21(r2)
	lfs      f28, lbl_80517B7C@sda21(r2)
	lfs      f31, lbl_80517B8C@sda21(r2)
	lfs      f30, lbl_80517B90@sda21(r2)

lbl_8011B398:
	lbz      r0, 0x15(r31)
	lis      r4, "sColorTableNumerator__26@unnamed@carryInfoMgr_cpp@"@ha
	lis      r3, "sColorTableDenominator__26@unnamed@carryInfoMgr_cpp@"@ha
	lbz      r10, 0xd(r29)
	slwi     r5, r0, 2
	addi     r0, r4, "sColorTableNumerator__26@unnamed@carryInfoMgr_cpp@"@l
	add      r4, r0, r5
	addi     r0, r3, "sColorTableDenominator__26@unnamed@carryInfoMgr_cpp@"@l
	add      r5, r0, r5
	lfs      f1, lbl_80517B60@sda21(r2)
	lbz      r9, 2(r4)
	mr       r3, r29
	lbz      r8, 1(r4)
	fmr      f2, f1
	lbz      r7, 0(r4)
	mr       r4, r30
	lbz      r12, 2(r5)
	addi     r6, r1, 0x14
	lbz      r11, 1(r5)
	lbz      r0, 0(r5)
	li       r5, 0xa
	stb      r7, 0x14(r1)
	lfs      f3, lbl_80517B6C@sda21(r2)
	stb      r8, 0x15(r1)
	stb      r9, 0x16(r1)
	stb      r10, 0x17(r1)
	stb      r0, 0x10(r1)
	stb      r11, 0x11(r1)
	stb      r12, 0x12(r1)
	stb      r10, 0x13(r1)
	bl       drawNumberPrim__9CarryInfoFR8GraphicsffiR6Color4f
	fmr      f2, f31
	lfs      f1, lbl_80517B60@sda21(r2)
	fmr      f3, f29
	lhz      r5, 0x16(r31)
	mr       r3, r29
	mr       r4, r30
	addi     r6, r1, 0x14
	bl       drawNumber__9CarryInfoFR8GraphicsffiR6Color4f
	fmr      f2, f30
	lfs      f1, lbl_80517B60@sda21(r2)
	fmr      f3, f28
	lhz      r5, 0x18(r31)
	mr       r3, r29
	mr       r4, r30
	addi     r6, r1, 0x10
	bl       drawNumber__9CarryInfoFR8GraphicsffiR6Color4f
	b        lbl_8011B6B8

lbl_8011B458:
	lbz      r3, 0xe(r29)
	lis      r0, 0x4330
	stw      r0, 0x78(r1)
	slwi     r0, r3, 0x1b
	srwi     r3, r3, 0x1f
	subf     r0, r3, r0
	lfd      f5, lbl_80517BB8@sda21(r2)
	rotlwi   r0, r0, 5
	lfs      f6, lbl_80517B94@sda21(r2)
	add      r0, r0, r3
	lfs      f2, lbl_80517B98@sda21(r2)
	xoris    r0, r0, 0x8000
	lfs      f0, lbl_80517B60@sda21(r2)
	stw      r0, 0x7c(r1)
	lfs      f3, lbl_80517B74@sda21(r2)
	lfd      f4, 0x78(r1)
	lfs      f1, lbl_80517B6C@sda21(r2)
	fsubs    f4, f4, f5
	fmuls    f4, f6, f4
	fmuls    f2, f4, f2
	fcmpo    cr0, f2, f0
	bge      lbl_8011B4DC
	lfs      f0, lbl_80517B9C@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f2, f0
	fctiwz   f0, f0
	stfd     f0, 0x80(r1)
	lwz      r0, 0x84(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0
	fneg     f0, f0
	b        lbl_8011B500

lbl_8011B4DC:
	lfs      f0, lbl_80517BA0@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f2, f0
	fctiwz   f0, f0
	stfd     f0, 0x88(r1)
	lwz      r0, 0x8c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0

lbl_8011B500:
	lbz      r27, 0xd(r29)
	lis      r5, 0x4330
	li       r7, 0x7f
	li       r10, 0xb
	li       r9, 0
	clrlwi   r0, r27, 0x18
	stw      r7, 0x94(r1)
	fadds    f2, f1, f0
	li       r28, 0xff
	li       r12, 0x8a
	stw      r5, 0x90(r1)
	li       r11, 0x15
	lfd      f0, lbl_80517BC0@sda21(r2)
	lfd      f1, 0x90(r1)
	fmuls    f4, f3, f2
	stw      r10, 0xac(r1)
	mr       r3, r29
	fsubs    f2, f1, f0
	lfs      f3, lbl_80517B70@sda21(r2)
	stw      r5, 0xa8(r1)
	lfs      f5, lbl_80517BA4@sda21(r2)
	mr       r4, r30
	lfd      f1, 0xa8(r1)
	stw      r9, 0xc4(r1)
	fsubs    f10, f3, f2
	fsubs    f3, f1, f0
	lfs      f7, lbl_80517BA8@sda21(r2)
	stw      r5, 0xc0(r1)
	addi     r6, r1, 0xc
	lfs      f1, lbl_80517BAC@sda21(r2)
	lfd      f2, 0xc0(r1)
	stw      r27, 0xdc(r1)
	fsubs    f9, f5, f3
	fsubs    f6, f2, f0
	lfs      f2, lbl_80517B60@sda21(r2)
	stw      r5, 0xd8(r1)
	lfs      f3, lbl_80517B6C@sda21(r2)
	lfd      f5, 0xd8(r1)
	fsubs    f7, f7, f6
	stw      r0, 0xe4(r1)
	fsubs    f6, f5, f0
	stw      r5, 0xe0(r1)
	lfd      f5, 0xe0(r1)
	stw      r7, 0x9c(r1)
	fsubs    f5, f5, f0
	stw      r5, 0x98(r1)
	lfd      f8, 0x98(r1)
	fsubs    f6, f6, f5
	stw      r10, 0xb4(r1)
	fsubs    f8, f8, f0
	stw      r5, 0xb0(r1)
	lfd      f5, 0xb0(r1)
	fmadds   f10, f4, f10, f8
	stw      r9, 0xcc(r1)
	fsubs    f8, f5, f0
	stw      r5, 0xc8(r1)
	fctiwz   f10, f10
	lfd      f5, 0xc8(r1)
	fmadds   f8, f4, f9, f8
	stfd     f10, 0xa0(r1)
	fsubs    f5, f5, f0
	fctiwz   f8, f8
	stw      r0, 0xec(r1)
	lwz      r8, 0xa4(r1)
	stw      r5, 0xe8(r1)
	fmadds   f7, f4, f7, f5
	lfd      f5, 0xe8(r1)
	fctiwz   f7, f7
	stfd     f8, 0xb8(r1)
	fsubs    f0, f5, f0
	stb      r7, 8(r1)
	lwz      r7, 0xbc(r1)
	fmadds   f0, f4, f6, f0
	stfd     f7, 0xd0(r1)
	stb      r10, 9(r1)
	fctiwz   f0, f0
	lwz      r5, 0xd4(r1)
	stb      r9, 0xa(r1)
	stfd     f0, 0xf0(r1)
	stb      r27, 0xb(r1)
	lwz      r0, 0xf4(r1)
	stb      r28, 0xc(r1)
	stb      r12, 0xd(r1)
	stb      r11, 0xe(r1)
	stb      r27, 0xf(r1)
	stb      r8, 8(r1)
	stb      r7, 9(r1)
	stb      r5, 0xa(r1)
	stb      r0, 0xb(r1)
	lwz      r5, 0x20(r31)
	bl       drawNumber__9CarryInfoFR8GraphicsffiR6Color4f
	fneg     f1, f1
	lfs      f3, lbl_80517B74@sda21(r2)
	lfs      f0, lbl_80517BB0@sda21(r2)
	mr       r3, r29
	lfs      f2, lbl_80517B60@sda21(r2)
	mr       r4, r30
	fmsubs   f1, f3, f1, f0
	lfs      f3, lbl_80517B6C@sda21(r2)
	addi     r6, r1, 8
	li       r5, 0xb
	bl       drawNumberPrim__9CarryInfoFR8GraphicsffiR6Color4f
	b        lbl_8011B6B8

lbl_8011B69C:
	lis      r3, lbl_8047B268@ha
	lis      r4, lbl_8047B27C@ha
	addi     r5, r4, lbl_8047B27C@l
	addi     r3, r3, lbl_8047B268@l
	li       r4, 0x193
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8011B6B8:
	psq_l    f31, 328(r1), 0, qr0
	lfd      f31, 0x140(r1)
	psq_l    f30, 312(r1), 0, qr0
	lfd      f30, 0x130(r1)
	psq_l    f29, 296(r1), 0, qr0
	lfd      f29, 0x120(r1)
	psq_l    f28, 280(r1), 0, qr0
	lfd      f28, 0x110(r1)
	lmw      r27, 0xfc(r1)
	lwz      r0, 0x154(r1)
	mtlr     r0
	addi     r1, r1, 0x150
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011B6EC
 * Size:	000328
 */
f32 CarryInfo::drawNumber(Graphics& gfx, float xpos, float ypos, int dispNum, Color4& color, float scale)
{
	if (dispNum < 10) {
		drawNumberPrim(gfx, xpos, ypos, dispNum, color, scale);

		return 7.0f * scale;

	} else if (dispNum < 100) {
		f32 temp = 5.6f * scale;

		drawNumberPrim(gfx, xpos - temp, ypos, dispNum / 10, color, scale);
		drawNumberPrim(gfx, xpos + temp, ypos, dispNum % 10, color, scale);

		return 2.0f * temp + 7.0f * scale;

	} else if (dispNum < 1000) {
		f32 temp = 12.599999f * scale;

		drawNumberPrim(gfx, xpos - temp, ypos, dispNum / 100, color, scale);
		drawNumberPrim(gfx, xpos, ypos, (dispNum / 10) % 10, color, scale);
		drawNumberPrim(gfx, xpos + temp, ypos, dispNum % 10, color, scale);

		return 2.0f * temp + 7.0f * scale;

	} else {
		f32 temp_2;
		f32 temp_1 = 5.6f * scale;
		temp_2     = 3.0f * temp_1;

		drawNumberPrim(gfx, xpos - temp_2, ypos, dispNum / 1000, color, scale);
		drawNumberPrim(gfx, xpos - temp_1, ypos, (dispNum / 100) % 10, color, scale);
		drawNumberPrim(gfx, xpos + temp_1, ypos, (dispNum / 10) % 10, color, scale);
		drawNumberPrim(gfx, xpos + temp_2, ypos, dispNum % 10, color, scale);

		return 6.0f * temp_1 + 7.0f * scale;
	}
}

/*
 * --INFO--
 * Address:	8011BA14
 * Size:	0001B4
 */
void CarryInfo::drawNumberPrim(Graphics& gfx, f32 arg1, f32 arg2, int arg3, Color4& color, f32 arg5)
{
	f32 temp_f5  = 7.0f * arg5;
	f32 temp_f3  = 0.083333336f;
	f32 temp_f31 = arg1 - temp_f5;
	f32 temp_f30 = arg1 + temp_f5;
	f32 temp_f29 = arg2 - temp_f5;
	f32 temp_f28 = arg2 + temp_f5;
	f32 temp_f27 = temp_f3 * arg3;
	f32 temp_f26 = temp_f27 + temp_f3;
	f32 temp_f1  = 0.0f;
	f32 temp_f0  = 1.0f;

	GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);

	GXPosition3f32(temp_f31, temp_f29, temp_f1);
	GXColor4u8(color.r, color.g, color.b, color.a);
	GXPosition2f32(temp_f27, temp_f0);

	GXPosition3f32(temp_f30, temp_f29, temp_f1);
	GXColor4u8(color.r, color.g, color.b, color.a);
	GXPosition2f32(temp_f26, temp_f0);

	GXPosition3f32(temp_f31, temp_f28, temp_f1);
	GXColor4u8(color.r, color.g, color.b, color.a);
	GXPosition2f32(temp_f27, temp_f1);

	GXPosition3f32(temp_f30, temp_f28, temp_f1);
	GXColor4u8(color.r, color.g, color.b, color.a);
	GXPosition2f32(temp_f26, temp_f1);
}

/*
 * --INFO--
 * Address:	8011BBC8
 * Size:	000004
 */
void CarryInfoList::init() { }

/*
 * --INFO--
 * Address:	8011BBCC
 * Size:	00004C
 */
void CarryInfoList::update()
{
	mOwner->getCarryInfoParam(mParam);
	mParam.mCarryInfo.update(mParam);
}

/*
 * --INFO--
 * Address:	8011BC18
 * Size:	00002C
 */
void CarryInfoList::draw(Graphics& gfx) { mParam.mCarryInfo.draw(gfx, mParam); }

/*
 * --INFO--
 * Address:	8011BC44
 * Size:	00003C
 */
void PokoInfoOwner::getCarryInfoParam(CarryInfoParam& param)
{
	param.mUseType    = 1;
	param.mPosition   = mPosition;
	param.mYOffsetMax = 25.0f;
	param.mColor      = 4;
	param.mValue      = mValue;
}

/*
 * --INFO--
 * Address:	8011BC80
 * Size:	000014
 */
bool CarryInfoList::isFinish() { return (mParam.mCarryInfo.mHidden == CINFO_Hidden); }

/*
 * --INFO--
 * Address:	8011BC94
 * Size:	0000D4
 */
CarryInfoMgr::CarryInfoMgr(int a)
    : InfoMgr(a)
{
	mNode1.clearRelations();

	mPoko_node.clearRelations();

	PokoInfoOwner* pokolist = new PokoInfoOwner[MAX_POKOINFO];
	for (u32 i = 0; i < MAX_POKOINFO; i++) {
		mPoko_node.add(&pokolist[i]);
	}
}

/*
 * --INFO--
 * Address:	8011BD68
 * Size:	00006C
 */
PokoInfoOwner::~PokoInfoOwner() { }

/*
 * --INFO--
 * Address:	8011BDD4
 * Size:	000078
 */
PokoInfoOwner::PokoInfoOwner()
    : CNode("")
{
	mTimer    = 0.0f;
	mList     = nullptr;
	mPosition = Vector3f::zero;
	mValue    = 0;
}

/*
 * --INFO--
 * Address:	8011BE4C
 * Size:	00013C
 */
InfoMgr<CarryInfoOwner, CarryInfoList>::~InfoMgr()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8011BF6C
	lis      r3, "__vt__41InfoMgr<14CarryInfoOwner,13CarryInfoList>"@ha
	addic.   r0, r30, 0x5c
	addi     r0, r3, "__vt__41InfoMgr<14CarryInfoOwner,13CarryInfoList>"@l
	stw      r0, 0(r30)
	beq      lbl_8011BEE0
	lis      r3, __vt__13CarryInfoList@ha
	addic.   r0, r30, 0x5c
	addi     r0, r3, __vt__13CarryInfoList@l
	stw      r0, 0x5c(r30)
	beq      lbl_8011BEE0
	lis      r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@ha
	addi     r0, r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@l
	stw      r0, 0x5c(r30)
	lwz      r3, 0x74(r30)
	cmplwi   r3, 0
	beq      lbl_8011BEB4
	lwz      r0, 0x78(r30)
	stw      r0, 0x1c(r3)

lbl_8011BEB4:
	lwz      r3, 0x78(r30)
	cmplwi   r3, 0
	beq      lbl_8011BEC8
	lwz      r0, 0x74(r30)
	stw      r0, 0x18(r3)

lbl_8011BEC8:
	li       r0, 0
	addi     r3, r30, 0x5c
	stw      r0, 0x78(r30)
	li       r4, 0
	stw      r0, 0x74(r30)
	bl       __dt__11JKRDisposerFv

lbl_8011BEE0:
	addic.   r0, r30, 4
	beq      lbl_8011BF48
	lis      r3, __vt__13CarryInfoList@ha
	addic.   r0, r30, 4
	addi     r0, r3, __vt__13CarryInfoList@l
	stw      r0, 4(r30)
	beq      lbl_8011BF48
	lis      r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@ha
	addi     r0, r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@l
	stw      r0, 4(r30)
	lwz      r3, 0x1c(r30)
	cmplwi   r3, 0
	beq      lbl_8011BF1C
	lwz      r0, 0x20(r30)
	stw      r0, 0x1c(r3)

lbl_8011BF1C:
	lwz      r3, 0x20(r30)
	cmplwi   r3, 0
	beq      lbl_8011BF30
	lwz      r0, 0x1c(r30)
	stw      r0, 0x18(r3)

lbl_8011BF30:
	li       r0, 0
	addi     r3, r30, 4
	stw      r0, 0x20(r30)
	li       r4, 0
	stw      r0, 0x1c(r30)
	bl       __dt__11JKRDisposerFv

lbl_8011BF48:
	cmplwi   r30, 0
	beq      lbl_8011BF5C
	lis      r3, __vt__11InfoMgrBase@ha
	addi     r0, r3, __vt__11InfoMgrBase@l
	stw      r0, 0(r30)

lbl_8011BF5C:
	extsh.   r0, r31
	ble      lbl_8011BF6C
	mr       r3, r30
	bl       __dl__FPv

lbl_8011BF6C:
	lwz      r0, 0x14(r1)
	mr       r3, r30
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011BF88
 * Size:	000170
 */
CarryInfoMgr::~CarryInfoMgr()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8011C0DC
	lis      r3, __vt__12CarryInfoMgr@ha
	li       r0, 0
	addi     r4, r3, __vt__12CarryInfoMgr@l
	addi     r3, r30, 0xd4
	stw      r4, 0(r30)
	li       r4, -1
	stw      r0, carryInfoMgr@sda21(r13)
	bl       __dt__5CNodeFv
	addi     r3, r30, 0xbc
	li       r4, -1
	bl       __dt__5CNodeFv
	cmplwi   r30, 0
	beq      lbl_8011C0CC
	lis      r3, "__vt__41InfoMgr<14CarryInfoOwner,13CarryInfoList>"@ha
	addic.   r0, r30, 0x5c
	addi     r0, r3, "__vt__41InfoMgr<14CarryInfoOwner,13CarryInfoList>"@l
	stw      r0, 0(r30)
	beq      lbl_8011C050
	lis      r3, __vt__13CarryInfoList@ha
	addic.   r0, r30, 0x5c
	addi     r0, r3, __vt__13CarryInfoList@l
	stw      r0, 0x5c(r30)
	beq      lbl_8011C050
	lis      r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@ha
	addi     r0, r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@l
	stw      r0, 0x5c(r30)
	lwz      r3, 0x74(r30)
	cmplwi   r3, 0
	beq      lbl_8011C024
	lwz      r0, 0x78(r30)
	stw      r0, 0x1c(r3)

lbl_8011C024:
	lwz      r3, 0x78(r30)
	cmplwi   r3, 0
	beq      lbl_8011C038
	lwz      r0, 0x74(r30)
	stw      r0, 0x18(r3)

lbl_8011C038:
	li       r0, 0
	addi     r3, r30, 0x5c
	stw      r0, 0x78(r30)
	li       r4, 0
	stw      r0, 0x74(r30)
	bl       __dt__11JKRDisposerFv

lbl_8011C050:
	addic.   r0, r30, 4
	beq      lbl_8011C0B8
	lis      r3, __vt__13CarryInfoList@ha
	addic.   r0, r30, 4
	addi     r0, r3, __vt__13CarryInfoList@l
	stw      r0, 4(r30)
	beq      lbl_8011C0B8
	lis      r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@ha
	addi     r0, r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@l
	stw      r0, 4(r30)
	lwz      r3, 0x1c(r30)
	cmplwi   r3, 0
	beq      lbl_8011C08C
	lwz      r0, 0x20(r30)
	stw      r0, 0x1c(r3)

lbl_8011C08C:
	lwz      r3, 0x20(r30)
	cmplwi   r3, 0
	beq      lbl_8011C0A0
	lwz      r0, 0x1c(r30)
	stw      r0, 0x18(r3)

lbl_8011C0A0:
	li       r0, 0
	addi     r3, r30, 4
	stw      r0, 0x20(r30)
	li       r4, 0
	stw      r0, 0x1c(r30)
	bl       __dt__11JKRDisposerFv

lbl_8011C0B8:
	cmplwi   r30, 0
	beq      lbl_8011C0CC
	lis      r3, __vt__11InfoMgrBase@ha
	addi     r0, r3, __vt__11InfoMgrBase@l
	stw      r0, 0(r30)

lbl_8011C0CC:
	extsh.   r0, r31
	ble      lbl_8011C0DC
	mr       r3, r30
	bl       __dl__FPv

lbl_8011C0DC:
	lwz      r0, 0x14(r1)
	mr       r3, r30
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C0F8
 * Size:	0000C0
 */
void CarryInfoMgr::appearPoko(const Vector3f& pos, int value)
{
	PokoInfoOwner* obj = static_cast<PokoInfoOwner*>(mPoko_node.mChild);

	if (obj) {
		CarryInfoList* newlist = regist(obj);
		if (newlist) {
			obj->del();
			mNode1.addHead(obj);
			obj->mList                          = newlist;
			obj->mPosition                      = pos;
			obj->mValue                         = value;
			obj->mTimer                         = 0.0f;
			newlist                             = obj->mList;
			newlist->mParam.mCarryInfo.mHidden  = CINFO_Appear;
			newlist->mParam.mCarryInfo.mCounter = 0;
		}
	}
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stmw     r27, 0xc(r1)
	mr       r27, r3
	mr       r28, r4
	mr       r29, r5
	lwz      r30, 0xe4(r3)
	cmplwi   r30, 0
	beq      lbl_8011C124
	addi     r30, r30, -4

lbl_8011C124:
	cmplwi   r30, 0
	beq      lbl_8011C1A4
	mr       r3, r27
	mr       r4, r30
	lwz      r12, 0(r27)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	or.      r31, r3, r3
	beq      lbl_8011C1A4
	addi     r3, r30, 4
	bl       del__5CNodeFv
	cmplwi   r30, 0
	mr       r4, r30
	beq      lbl_8011C164
	addi     r4, r30, 4

lbl_8011C164:
	addi     r3, r27, 0xbc
	bl       addHead__5CNodeFP5CNode
	stw      r31, 0x20(r30)
	li       r0, 0
	lfs      f1, 0(r28)
	lfs      f0, 4(r28)
	stfs     f1, 0x24(r30)
	lfs      f1, 8(r28)
	stfs     f0, 0x28(r30)
	lfs      f0, lbl_80517B60@sda21(r2)
	stfs     f1, 0x2c(r30)
	stw      r29, 0x30(r30)
	stfs     f0, 0x1c(r30)
	lwz      r3, 0x20(r30)
	stb      r0, 0x54(r3)
	stb      r0, 0x56(r3)

lbl_8011C1A4:
	lmw      r27, 0xc(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C1B8
 * Size:	000020
 */
CarryInfoList* CarryInfoMgr::regist(CarryInfoOwner* owner)
{
	return regist(owner); // this should be the base class
	                      /*
	                      stwu     r1, -0x10(r1)
	                      mflr     r0
	                      stw      r0, 0x14(r1)
	                      bl "regist__41InfoMgr<14CarryInfoOwner,13CarryInfoList>FP14CarryInfoOwner"
	                      lwz      r0, 0x14(r1)
	                      mtlr     r0
	                      addi     r1, r1, 0x10
	                      blr
	                      */
}

/*
 * --INFO--
 * Address:	8011C1D8
 * Size:	000040
 */
CarryInfoList* CarryInfoMgr::appear(CarryInfoOwner* owner)
{
	CarryInfoList* list = regist(owner);
	if (list) {
		list->mParam.mCarryInfo.mHidden  = CINFO_Appear;
		list->mParam.mCarryInfo.mCounter = 0;
	}
	return list;
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	cmplwi   r3, 0
	beq      lbl_8011C208
	li       r0, 0
	stb      r0, 0x54(r3)
	stb      r0, 0x56(r3)

lbl_8011C208:
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C218
 * Size:	000098
 */
void CarryInfoMgr::loadResource()
{
	JKRArchive* arc = JKRArchive::mount("/user/Yamashita/arc/gameTex.szs", JKRArchive::EMM_Mem, nullptr, JKRArchive::EMD_Unk1);
	void* timg      = JKRFileLoader::getGlbResource("item_0_0.bti", arc);
	JUTTexture* tex = new JUTTexture;
	tex->_20        = static_cast<ResTIMG*>(timg);
	mTexture        = tex;
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, lbl_8047B290@ha
	li       r5, 0
	stw      r0, 0x24(r1)
	li       r6, 1
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	mr       r29, r3
	addi     r3, r4, lbl_8047B290@l
	li       r4, 1
	bl
mount__10JKRArchiveFPCcQ210JKRArchive10EMountModeP7JKRHeapQ210JKRArchive15EMountDirection
	lis      r5, lbl_8047B2B0@ha
	mr       r4, r3
	addi     r3, r5, lbl_8047B2B0@l
	bl       getGlbResource__13JKRFileLoaderFPCcP13JKRFileLoader
	mr       r30, r3
	li       r3, 0x40
	bl       __nw__FUl
	or.      r31, r3, r3
	beq      lbl_8011C290
	li       r0, 0
	mr       r4, r30
	stw      r0, 0x28(r31)
	li       r5, 0
	bl       storeTIMG__10JUTTextureFPC7ResTIMGUc
	lbz      r0, 0x3b(r31)
	rlwinm   r0, r0, 0, 0x1e, 0x1e
	stb      r0, 0x3b(r31)

lbl_8011C290:
	stw      r31, 0xb8(r29)
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C2B0
 * Size:	000198
 */
void CarryInfoMgr::draw(Graphics& gfx)
{
	if (!Game::moviePlayer || !(Game::moviePlayer->mFlags & 1)) {
		Graphics::clearInitGX();
		GXSetNumChans(1);
		GXSetTevDirect(GX_TEVSTAGE0);
		GXSetNumTevStages(1);
		GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
		GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
		GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_POS_XYZ, GX_RGBA8, 0);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_F32, 0);
		GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
		GXSetZMode(GX_FALSE, GX_LESS, GX_FALSE);
		GXSetCurrentMtx(0);
		GXSetNumTexGens(1);
		GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_TEXCOORD0, 0x3c, GX_FALSE, 0x7d);
		Matrixf mtx;
		PSMTXIdentity(mtx.mMatrix.mtxView);
		GXLoadTexMtxImm(mtx.mMatrix.mtxView, 0x1e, GX_MTX2x4);
		mTexture->load(GX_TEXMAP0);
		draw(gfx); // should be base class
	}
	/*
	stwu     r1, -0x40(r1)
	mflr     r0
	stw      r0, 0x44(r1)
	stw      r31, 0x3c(r1)
	mr       r31, r4
	stw      r30, 0x38(r1)
	mr       r30, r3
	lwz      r5, moviePlayer__4Game@sda21(r13)
	cmplwi   r5, 0
	beq      lbl_8011C2E4
	lwz      r0, 0x1f0(r5)
	clrlwi.  r0, r0, 0x1f
	bne      lbl_8011C430

lbl_8011C2E4:
	bl       clearInitGX__8GraphicsFv
	li       r3, 1
	bl       GXSetNumChans
	li       r3, 0
	bl       GXSetTevDirect
	li       r3, 1
	bl       GXSetNumTevStages
	li       r3, 0
	li       r4, 0
	bl       GXSetTevOp
	li       r3, 0
	li       r4, 0
	li       r5, 0
	li       r6, 4
	bl       GXSetTevOrder
	li       r3, 4
	li       r4, 0
	li       r5, 0
	li       r6, 1
	li       r7, 0
	li       r8, 0
	li       r9, 2
	bl       GXSetChanCtrl
	bl       GXClearVtxDesc
	li       r3, 9
	li       r4, 1
	bl       GXSetVtxDesc
	li       r3, 0xb
	li       r4, 1
	bl       GXSetVtxDesc
	li       r3, 0xd
	li       r4, 1
	bl       GXSetVtxDesc
	li       r3, 0
	li       r4, 9
	li       r5, 1
	li       r6, 4
	li       r7, 0
	bl       GXSetVtxAttrFmt
	li       r3, 0
	li       r4, 0xb
	li       r5, 1
	li       r6, 5
	li       r7, 0
	bl       GXSetVtxAttrFmt
	li       r3, 0
	li       r4, 0xd
	li       r5, 1
	li       r6, 4
	li       r7, 0
	bl       GXSetVtxAttrFmt
	li       r3, 1
	li       r4, 4
	li       r5, 5
	li       r6, 0xf
	bl       GXSetBlendMode
	li       r3, 0
	li       r4, 1
	li       r5, 0
	bl       GXSetZMode
	li       r3, 0
	bl       GXSetCurrentMtx
	li       r3, 1
	bl       GXSetNumTexGens
	li       r3, 0
	li       r4, 1
	li       r5, 0xc
	li       r6, 0x3c
	li       r7, 0
	li       r8, 0x7d
	bl       GXSetTexCoordGen2
	addi     r3, r1, 8
	bl       PSMTXIdentity
	addi     r3, r1, 8
	li       r4, 0x1e
	li       r5, 1
	bl       GXLoadTexMtxImm
	lwz      r3, 0xb8(r30)
	li       r4, 0
	bl       load__10JUTTextureF11_GXTexMapID
	mr       r3, r30
	mr       r4, r31
	bl       "draw__41InfoMgr<14CarryInfoOwner,13CarryInfoList>FR8Graphics"

lbl_8011C430:
	lwz      r0, 0x44(r1)
	lwz      r31, 0x3c(r1)
	lwz      r30, 0x38(r1)
	mtlr     r0
	addi     r1, r1, 0x40
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C448
 * Size:	000034
 */
void CarryInfoMgr::update()
{
	updatePokoInfoOwners();
	update(); // should be base class
	          /*
	          stwu     r1, -0x10(r1)
	          mflr     r0
	          stw      r0, 0x14(r1)
	          stw      r31, 0xc(r1)
	          mr       r31, r3
	          bl       updatePokoInfoOwners__12CarryInfoMgrFv
	          mr       r3, r31
	          bl       "update__41InfoMgr<14CarryInfoOwner,13CarryInfoList>Fv"
	          lwz      r0, 0x14(r1)
	          lwz      r31, 0xc(r1)
	          mtlr     r0
	          addi     r1, r1, 0x10
	          blr
	          */
}

/*
 * --INFO--
 * Address:	8011C47C
 * Size:	000108
 */
void CarryInfoMgr::updatePokoInfoOwners()
{
	PokoInfoOwner* obj = static_cast<PokoInfoOwner*>(mPoko_node.mChild);

	while (obj) {
		if (!obj->mList->isFinish() && obj->mList->mOwner == obj) {
			obj->mTimer += sys->mDeltaTime;
			if (obj->mTimer > 1.5f) {
				obj->mList->mParam.mCarryInfo.mHidden = CINFO_1;
			}
		} else {
			obj->del();
			mPoko_node.add(obj);
		}
		obj = static_cast<PokoInfoOwner*>(obj->mNext);
	}
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	stw      r28, 0x10(r1)
	mr       r28, r3
	lwz      r3, 0xcc(r3)
	cmplwi   r3, 0
	beq      lbl_8011C4AC
	addi     r3, r3, -4

lbl_8011C4AC:
	mr       r30, r3
	b        lbl_8011C55C

lbl_8011C4B4:
	lwz      r4, 8(r30)
	cmplwi   r4, 0
	beq      lbl_8011C4C4
	addi     r4, r4, -4

lbl_8011C4C4:
	lwz      r3, 0x20(r30)
	mr       r29, r4
	li       r31, 0
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8011C4F8
	lwz      r3, 0x20(r30)
	lwz      r0, 0x20(r3)
	cmplw    r0, r30
	beq      lbl_8011C500

lbl_8011C4F8:
	li       r31, 1
	b        lbl_8011C530

lbl_8011C500:
	lwz      r3, sys@sda21(r13)
	lfs      f2, 0x1c(r30)
	lfs      f1, 0x54(r3)
	lfs      f0, lbl_80517BE0@sda21(r2)
	fadds    f1, f2, f1
	stfs     f1, 0x1c(r30)
	lfs      f1, 0x1c(r30)
	fcmpo    cr0, f1, f0
	ble      lbl_8011C530
	lwz      r3, 0x20(r30)
	li       r0, 1
	stb      r0, 0x54(r3)

lbl_8011C530:
	clrlwi.  r0, r31, 0x18
	beq      lbl_8011C558
	addi     r3, r30, 4
	bl       del__5CNodeFv
	cmplwi   r30, 0
	mr       r4, r30
	beq      lbl_8011C550
	addi     r4, r30, 4

lbl_8011C550:
	addi     r3, r28, 0xd4
	bl       add__5CNodeFP5CNode

lbl_8011C558:
	mr       r30, r29

lbl_8011C55C:
	cmplwi   r30, 0
	bne      lbl_8011C4B4
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r28, 0x10(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C584
 * Size:	000020
 */
CarryInfoList* CarryInfoMgr::scratch(CarryInfoOwner* owner)
{
	return scratch(owner); // should be base class
	                       /*
	                       stwu     r1, -0x10(r1)
	                       mflr     r0
	                       stw      r0, 0x14(r1)
	                       bl "scratch__41InfoMgr<14CarryInfoOwner,13CarryInfoList>FP14CarryInfoOwner"
	                       lwz      r0, 0x14(r1)
	                       mtlr     r0
	                       addi     r1, r1, 0x10
	                       blr
	                       */
}

/*
 * --INFO--
 * Address:	8011C5A4
 * Size:	000048
 */
InfoMgrBase::~InfoMgrBase()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	or.      r31, r3, r3
	beq      lbl_8011C5D4
	lis      r5, __vt__11InfoMgrBase@ha
	extsh.   r0, r4
	addi     r0, r5, __vt__11InfoMgrBase@l
	stw      r0, 0(r31)
	ble      lbl_8011C5D4
	bl       __dl__FPv

lbl_8011C5D4:
	lwz      r0, 0x14(r1)
	mr       r3, r31
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C5EC
 * Size:	000004
 */
void InfoListBase<CarryInfoOwner, CarryInfoList>::init() { }

/*
 * --INFO--
 * Address:	8011C5F0
 * Size:	000098
 */
InfoListBase<CarryInfoOwner, CarryInfoList>::~InfoListBase()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8011C66C
	lis      r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@ha
	addi     r0, r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@l
	stw      r0, 0(r30)
	lwz      r3, 0x18(r30)
	cmplwi   r3, 0
	beq      lbl_8011C630
	lwz      r0, 0x1c(r30)
	stw      r0, 0x1c(r3)

lbl_8011C630:
	lwz      r3, 0x1c(r30)
	cmplwi   r3, 0
	beq      lbl_8011C644
	lwz      r0, 0x18(r30)
	stw      r0, 0x18(r3)

lbl_8011C644:
	li       r0, 0
	mr       r3, r30
	stw      r0, 0x1c(r30)
	li       r4, 0
	stw      r0, 0x18(r30)
	bl       __dt__11JKRDisposerFv
	extsh.   r0, r31
	ble      lbl_8011C66C
	mr       r3, r30
	bl       __dl__FPv

lbl_8011C66C:
	lwz      r0, 0x14(r1)
	mr       r3, r30
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C688
 * Size:	0000A8
 */
CarryInfoList::~CarryInfoList()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8011C714
	lis      r3, __vt__13CarryInfoList@ha
	addi     r0, r3, __vt__13CarryInfoList@l
	stw      r0, 0(r30)
	beq      lbl_8011C704
	lis      r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@ha
	addi     r0, r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@l
	stw      r0, 0(r30)
	lwz      r3, 0x18(r30)
	cmplwi   r3, 0
	beq      lbl_8011C6D8
	lwz      r0, 0x1c(r30)
	stw      r0, 0x1c(r3)

lbl_8011C6D8:
	lwz      r3, 0x1c(r30)
	cmplwi   r3, 0
	beq      lbl_8011C6EC
	lwz      r0, 0x18(r30)
	stw      r0, 0x18(r3)

lbl_8011C6EC:
	li       r0, 0
	mr       r3, r30
	stw      r0, 0x1c(r30)
	li       r4, 0
	stw      r0, 0x18(r30)
	bl       __dt__11JKRDisposerFv

lbl_8011C704:
	extsh.   r0, r31
	ble      lbl_8011C714
	mr       r3, r30
	bl       __dl__FPv

lbl_8011C714:
	lwz      r0, 0x14(r1)
	mr       r3, r30
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C730
 * Size:	000044
 */
CarryInfoList* InfoMgr<CarryInfoOwner, CarryInfoList>::scratch(CarryInfoOwner* owner)
{
	CarryInfoList* list = 0; // search(&mActiveList, owner); // this I cant get to work
	if (list) {
		addInactiveList(list);
	}
	return list;
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	mr       r5, r4
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r4, 0x20(r3)
	bl
"search__41InfoMgr<14CarryInfoOwner,13CarryInfoList>FP13CarryInfoListP14CarryInfoOwner"
	or.      r4, r3, r3
	beq      lbl_8011C760
	mr       r3, r31
	bl
"addInactiveList__41InfoMgr<14CarryInfoOwner,13CarryInfoList>FP13CarryInfoList"

lbl_8011C760:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C774
 * Size:	00008C
 */
void InfoMgr<CarryInfoOwner, CarryInfoList>::update()
{
	// these InfoMgr functions are all in InfoList.h
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	mr       r29, r3
	lwz      r31, 0x20(r3)
	b        lbl_8011C7DC

lbl_8011C798:
	mr       r3, r31
	lwz      r30, 0x1c(r31)
	lwz      r12, 0(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8011C7D8
	mr       r3, r29
	mr       r4, r31
	bl
"addInactiveList__41InfoMgr<14CarryInfoOwner,13CarryInfoList>FP13CarryInfoList"

lbl_8011C7D8:
	mr       r31, r30

lbl_8011C7DC:
	cmplwi   r31, 0
	bne      lbl_8011C798
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C800
 * Size:	000068
 */
void InfoMgr<CarryInfoOwner, CarryInfoList>::draw(Graphics&)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	mr       r30, r4
	lwz      r0, 0x20(r3)
	cmplwi   r0, 0
	beq      lbl_8011C850
	mr       r31, r0
	b        lbl_8011C848

lbl_8011C82C:
	mr       r3, r31
	mr       r4, r30
	lwz      r12, 0(r31)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	lwz      r31, 0x1c(r31)

lbl_8011C848:
	cmplwi   r31, 0
	bne      lbl_8011C82C

lbl_8011C850:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C868
 * Size:	00002C
 */
CarryInfoList* InfoMgr<CarryInfoOwner, CarryInfoList>::search(CarryInfoList*, CarryInfoOwner*)
{
	/*
	.loc_0x0:
	  b         .loc_0x1C

	.loc_0x4:
	  lwz       r0, 0x20(r4)
	  cmplw     r0, r5
	  bne-      .loc_0x18
	  mr        r3, r4
	  blr

	.loc_0x18:
	  lwz       r4, 0x1C(r4)

	.loc_0x1C:
	  cmplwi    r4, 0
	  bne+      .loc_0x4
	  li        r3, 0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8011C894
 * Size:	000004
 */
void InfoListBase<CarryInfoOwner, CarryInfoList>::update() { }

/*
 * --INFO--
 * Address:	8011C898
 * Size:	000004
 */
void InfoListBase<CarryInfoOwner, CarryInfoList>::draw(Graphics&) { }

/*
 * --INFO--
 * Address:	8011C89C
 * Size:	000064
 */
void InfoMgr<CarryInfoOwner, CarryInfoList>::addInactiveList(CarryInfoList*)
{
	/*
	li       r0, 0
	stw      r0, 0x20(r4)
	lwz      r5, 0x18(r4)
	cmplwi   r5, 0
	beq      lbl_8011C8B8
	lwz      r0, 0x1c(r4)
	stw      r0, 0x1c(r5)

lbl_8011C8B8:
	lwz      r5, 0x1c(r4)
	cmplwi   r5, 0
	beq      lbl_8011C8CC
	lwz      r0, 0x18(r4)
	stw      r0, 0x18(r5)

lbl_8011C8CC:
	li       r5, 0
	addi     r0, r3, 0x5c
	stw      r5, 0x1c(r4)
	stw      r5, 0x18(r4)
	stw      r0, 0x18(r4)
	lwz      r0, 0x78(r3)
	stw      r0, 0x1c(r4)
	lwz      r5, 0x78(r3)
	cmplwi   r5, 0
	beq      lbl_8011C8F8
	stw      r4, 0x18(r5)

lbl_8011C8F8:
	stw      r4, 0x78(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C900
 * Size:	000074
 */
CarryInfoList* InfoMgr<CarryInfoOwner, CarryInfoList>::regist(CarryInfoOwner*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	lwz      r5, 0x20(r3)
	b        lbl_8011C92C

lbl_8011C918:
	lwz      r0, 0x20(r5)
	cmplw    r0, r4
	bne      lbl_8011C928
	b        lbl_8011C938

lbl_8011C928:
	lwz      r5, 0x1c(r5)

lbl_8011C92C:
	cmplwi   r5, 0
	bne      lbl_8011C918
	li       r5, 0

lbl_8011C938:
	cmplwi   r5, 0
	mr       r31, r5
	bne      lbl_8011C948
	lwz      r31, 0x78(r3)

lbl_8011C948:
	cmplwi   r31, 0
	beq      lbl_8011C95C
	stw      r4, 0x20(r31)
	mr       r4, r31
	bl
"addActiveList__41InfoMgr<14CarryInfoOwner,13CarryInfoList>FP13CarryInfoList"

lbl_8011C95C:
	lwz      r0, 0x14(r1)
	mr       r3, r31
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011C974
 * Size:	0002E0
 */
InfoMgr<CarryInfoOwner, CarryInfoList>::InfoMgr(int)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r5, __vt__11InfoMgrBase@ha
	stw      r0, 0x24(r1)
	addi     r0, r5, __vt__11InfoMgrBase@l
	stmw     r26, 8(r1)
	mr       r28, r3
	lis      r3, "__vt__41InfoMgr<14CarryInfoOwner,13CarryInfoList>"@ha
	mr       r30, r4
	addi     r26, r28, 4
	stw      r0, 0(r28)
	addi     r0, r3, "__vt__41InfoMgr<14CarryInfoOwner,13CarryInfoList>"@l
	mr       r3, r26
	stw      r0, 0(r28)
	bl       __ct__11JKRDisposerFv
	lis      r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@ha
	li       r0, 0
	addi     r4, r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@l
	mr       r3, r26
	stw      r4, 0(r26)
	stw      r0, 0x20(r26)
	stw      r0, 0x1c(r26)
	stw      r0, 0x18(r26)
	lwz      r12, 0(r26)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	lis      r3, __vt__13CarryInfoList@ha
	li       r5, 0
	addi     r0, r3, __vt__13CarryInfoList@l
	lfs      f1, lbl_80517BE8@sda21(r2)
	stw      r0, 0(r26)
	lis      r3, "zero__10Vector3<f>"@ha
	addi     r31, r3, "zero__10Vector3<f>"@l
	addi     r27, r28, 0x5c
	stw      r5, 0x24(r26)
	li       r4, 6
	lfs      f0, lbl_80517B60@sda21(r2)
	li       r0, 2
	lfs      f2, 0(r31)
	mr       r3, r27
	stfs     f2, 0x28(r26)
	lfs      f2, 4(r31)
	stfs     f2, 0x2c(r26)
	lfs      f2, 8(r31)
	stfs     f2, 0x30(r26)
	stfs     f1, 0x34(r26)
	stb      r5, 0x38(r26)
	stb      r4, 0x39(r26)
	sth      r5, 0x3a(r26)
	sth      r5, 0x3c(r26)
	stw      r5, 0x40(r26)
	stw      r5, 0x44(r26)
	stfs     f0, 0x48(r26)
	stfs     f0, 0x4c(r26)
	stb      r0, 0x54(r26)
	stb      r5, 0x55(r26)
	stb      r5, 0x56(r26)
	bl       __ct__11JKRDisposerFv
	lis      r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@ha
	li       r0, 0
	addi     r4, r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@l
	mr       r3, r27
	stw      r4, 0(r27)
	stw      r0, 0x20(r27)
	stw      r0, 0x1c(r27)
	stw      r0, 0x18(r27)
	lwz      r12, 0(r27)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	lis      r4, __vt__13CarryInfoList@ha
	li       r5, 0
	addi     r0, r4, __vt__13CarryInfoList@l
	lis      r3, "zero__10Vector3<f>"@ha
	stw      r0, 0(r27)
	addi     r4, r3, "zero__10Vector3<f>"@l
	lfs      f1, lbl_80517BE8@sda21(r2)
	li       r3, 6
	stw      r5, 0x24(r27)
	li       r0, 2
	lfs      f0, lbl_80517B60@sda21(r2)
	mr       r26, r27
	lfs      f2, 0(r4)
	li       r29, 0
	stfs     f2, 0x28(r27)
	lfs      f2, 4(r31)
	stfs     f2, 0x2c(r27)
	lfs      f2, 8(r31)
	stfs     f2, 0x30(r27)
	stfs     f1, 0x34(r27)
	stb      r5, 0x38(r27)
	stb      r3, 0x39(r27)
	sth      r5, 0x3a(r27)
	sth      r5, 0x3c(r27)
	stw      r5, 0x40(r27)
	stw      r5, 0x44(r27)
	stfs     f0, 0x48(r27)
	stfs     f0, 0x4c(r27)
	stb      r0, 0x54(r27)
	stb      r5, 0x55(r27)
	stb      r5, 0x56(r27)
	stw      r30, 0xb4(r28)
	b        lbl_8011CC30

lbl_8011CB14:
	li       r3, 0x58
	bl       __nw__FUl
	or.      r30, r3, r3
	beq      lbl_8011CBD0
	mr       r27, r30
	bl       __ct__11JKRDisposerFv
	lis      r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@ha
	li       r0, 0
	addi     r4, r3, "__vt__46InfoListBase<14CarryInfoOwner,13CarryInfoList>"@l
	mr       r3, r27
	stw      r4, 0(r27)
	stw      r0, 0x20(r27)
	stw      r0, 0x1c(r27)
	stw      r0, 0x18(r27)
	lwz      r12, 0(r27)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	lis      r4, __vt__13CarryInfoList@ha
	lis      r3, "zero__10Vector3<f>"@ha
	addi     r0, r4, __vt__13CarryInfoList@l
	li       r5, 0
	stw      r0, 0(r30)
	addi     r4, r3, "zero__10Vector3<f>"@l
	lfs      f1, lbl_80517BE8@sda21(r2)
	li       r3, 6
	stw      r5, 0x24(r30)
	li       r0, 2
	lfs      f0, lbl_80517B60@sda21(r2)
	lfs      f2, 0(r4)
	stfs     f2, 0x28(r30)
	lfs      f2, 4(r31)
	stfs     f2, 0x2c(r30)
	lfs      f2, 8(r31)
	stfs     f2, 0x30(r30)
	stfs     f1, 0x34(r30)
	stb      r5, 0x38(r30)
	stb      r3, 0x39(r30)
	sth      r5, 0x3a(r30)
	sth      r5, 0x3c(r30)
	stw      r5, 0x40(r30)
	stw      r5, 0x44(r30)
	stfs     f0, 0x48(r30)
	stfs     f0, 0x4c(r30)
	stb      r0, 0x54(r30)
	stb      r5, 0x55(r30)
	stb      r5, 0x56(r30)

lbl_8011CBD0:
	li       r0, 0
	stw      r0, 0x20(r30)
	lwz      r3, 0x18(r30)
	cmplwi   r3, 0
	beq      lbl_8011CBEC
	lwz      r0, 0x1c(r30)
	stw      r0, 0x1c(r3)

lbl_8011CBEC:
	lwz      r3, 0x1c(r30)
	cmplwi   r3, 0
	beq      lbl_8011CC00
	lwz      r0, 0x18(r30)
	stw      r0, 0x18(r3)

lbl_8011CC00:
	li       r0, 0
	stw      r0, 0x1c(r30)
	stw      r0, 0x18(r30)
	stw      r26, 0x18(r30)
	lwz      r0, 0x78(r28)
	stw      r0, 0x1c(r30)
	lwz      r3, 0x78(r28)
	cmplwi   r3, 0
	beq      lbl_8011CC28
	stw      r30, 0x18(r3)

lbl_8011CC28:
	stw      r30, 0x78(r28)
	addi     r29, r29, 1

lbl_8011CC30:
	lwz      r0, 0xb4(r28)
	cmpw     r29, r0
	blt      lbl_8011CB14
	mr       r3, r28
	lmw      r26, 8(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8011CC54
 * Size:	00005C
 */
void InfoMgr<CarryInfoOwner, CarryInfoList>::addActiveList(CarryInfoList*)
{
	/*
	lwz      r5, 0x18(r4)
	cmplwi   r5, 0
	beq      lbl_8011CC68
	lwz      r0, 0x1c(r4)
	stw      r0, 0x1c(r5)

lbl_8011CC68:
	lwz      r5, 0x1c(r4)
	cmplwi   r5, 0
	beq      lbl_8011CC7C
	lwz      r0, 0x18(r4)
	stw      r0, 0x18(r5)

lbl_8011CC7C:
	li       r5, 0
	addi     r0, r3, 4
	stw      r5, 0x1c(r4)
	stw      r5, 0x18(r4)
	stw      r0, 0x18(r4)
	lwz      r0, 0x20(r3)
	stw      r0, 0x1c(r4)
	lwz      r5, 0x20(r3)
	cmplwi   r5, 0
	beq      lbl_8011CCA8
	stw      r4, 0x18(r5)

lbl_8011CCA8:
	stw      r4, 0x20(r3)
	blr
	*/
}
