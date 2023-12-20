#include "Game/shadowMgr.h"
#include "nans.h"

namespace Game {

static const int unusedArray[] = { 0, 0, 0 };
static const char unusedName[] = "246-ShadowCylinder";

/**
 * @note Address: N/A
 * @note Size: 0x108
 */
CylinderList::CylinderList(int)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0x210
 */
void CylinderList::createCylinder(int, float)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0x2C
 */
void CylinderList::draw()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: 0x8023DA30
 * @note Size: 0x4DC
 */
CylinderBase::CylinderBase()
{
	/*
	stwu     r1, -0xe0(r1)
	mflr     r0
	stw      r0, 0xe4(r1)
	stfd     f31, 0xd0(r1)
	psq_st   f31, 216(r1), 0, qr0
	stfd     f30, 0xc0(r1)
	psq_st   f30, 200(r1), 0, qr0
	stfd     f29, 0xb0(r1)
	psq_st   f29, 184(r1), 0, qr0
	stfd     f28, 0xa0(r1)
	psq_st   f28, 168(r1), 0, qr0
	stfd     f27, 0x90(r1)
	psq_st   f27, 152(r1), 0, qr0
	stfd     f26, 0x80(r1)
	psq_st   f26, 136(r1), 0, qr0
	stfd     f25, 0x70(r1)
	psq_st   f25, 120(r1), 0, qr0
	stfd     f24, 0x60(r1)
	psq_st   f24, 104(r1), 0, qr0
	stmw     r24, 0x40(r1)
	lis      r4, __vt__Q24Game12CylinderBase@ha
	mr       r24, r3
	addi     r0, r4, __vt__Q24Game12CylinderBase@l
	lis      r3, "__ct__10Vector3<f>Fv"@ha
	addi     r4, r3, "__ct__10Vector3<f>Fv"@l
	stw      r0, 0(r24)
	lis      r3, lbl_804C1780@ha
	li       r5, 0
	addi     r27, r3, lbl_804C1780@l
	li       r6, 0xc
	addi     r3, r24, 0x20
	li       r7, 2
	bl       __construct_array
	lis      r4, "__ct__10Vector3<f>Fv"@ha
	addi     r3, r24, 0x38
	addi     r4, r4, "__ct__10Vector3<f>Fv"@l
	li       r5, 0
	li       r6, 0xc
	li       r7, 2
	bl       __construct_array
	li       r3, 0xc
	bl       __nwa__FUl
	lis      r5, sincosTable___5JMath@ha
	lis      r4, sCylinderVertPos__4Game@ha
	stw      r3, 4(r24)
	addi     r30, r5, sincosTable___5JMath@l
	lfd      f29, lbl_8051A638@sda21(r2)
	addi     r31, r4, sCylinderVertPos__4Game@l
	lfs      f30, lbl_8051A620@sda21(r2)
	li       r25, 0
	lfs      f31, lbl_8051A624@sda21(r2)
	li       r26, 0
	lfs      f24, lbl_8051A62C@sda21(r2)
	lis      r29, 0x4330
	lfs      f26, lbl_8051A618@sda21(r2)
	lfd      f27, lbl_8051A630@sda21(r2)
	lfs      f28, lbl_8051A61C@sda21(r2)

lbl_8023DB14:
	cmpwi    r25, 1
	lfs      f25, lbl_8051A640@sda21(r2)
	beq      lbl_8023DB40
	bge      lbl_8023DB30
	cmpwi    r25, 0
	bge      lbl_8023DB4C
	b        lbl_8023DB4C

lbl_8023DB30:
	cmpwi    r25, 3
	bge      lbl_8023DB4C
	b        lbl_8023DB48
	b        lbl_8023DB4C

lbl_8023DB40:
	lfs      f25, lbl_8051A644@sda21(r2)
	b        lbl_8023DB4C

lbl_8023DB48:
	lfs      f25, lbl_8051A648@sda21(r2)

lbl_8023DB4C:
	li       r3, 0xc
	bl       __nw__FUl
	or.      r28, r3, r3
	beq      lbl_8023DC30
	li       r0, 0
	cmpwi    r25, 1
	stb      r0, 0(r28)
	stw      r0, 4(r28)
	stw      r0, 8(r28)
	beq      lbl_8023DBAC
	bge      lbl_8023DB84
	cmpwi    r25, 0
	bge      lbl_8023DB90
	b        lbl_8023DBE0

lbl_8023DB84:
	cmpwi    r25, 3
	bge      lbl_8023DBE0
	b        lbl_8023DBC8

lbl_8023DB90:
	li       r0, 0xc
	addi     r3, r27, 0x20
	stb      r0, 0(r28)
	li       r0, 0x8d
	stw      r3, 4(r28)
	stw      r0, 8(r28)
	b        lbl_8023DBE0

lbl_8023DBAC:
	li       r0, 8
	addi     r3, r27, 0xc0
	stb      r0, 0(r28)
	li       r0, 0x6d
	stw      r3, 4(r28)
	stw      r0, 8(r28)
	b        lbl_8023DBE0

lbl_8023DBC8:
	li       r0, 4
	addi     r3, r27, 0x140
	stb      r0, 0(r28)
	li       r0, 0x4d
	stw      r3, 4(r28)
	stw      r0, 8(r28)

lbl_8023DBE0:
	lbz      r0, 0(r28)
	li       r3, 0
	cmplwi   r0, 0
	beq      lbl_8023DC0C
	lwz      r0, 4(r28)
	cmplwi   r0, 0
	beq      lbl_8023DC0C
	lwz      r0, 8(r28)
	cmpwi    r0, 0
	beq      lbl_8023DC0C
	li       r3, 1

lbl_8023DC0C:
	clrlwi.  r0, r3, 0x18
	bne      lbl_8023DC30
	lis      r3, lbl_80483F78@ha
	lis      r5, lbl_80483F8C@ha
	addi     r3, r3, lbl_80483F78@l
	li       r4, 0xbc
	addi     r5, r5, lbl_80483F8C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8023DC30:
	lwz      r3, 4(r24)
	cmpwi    r25, 1
	li       r0, 0
	stwx     r28, r3, r26
	lwz      r3, 4(r24)
	lwzx     r4, r3, r26
	beq      lbl_8023DC6C
	bge      lbl_8023DC5C
	cmpwi    r25, 0
	bge      lbl_8023DC78
	b        lbl_8023DC78

lbl_8023DC5C:
	cmpwi    r25, 3
	bge      lbl_8023DC78
	b        lbl_8023DC74
	b        lbl_8023DC78

lbl_8023DC6C:
	li       r0, 0x48
	b        lbl_8023DC78

lbl_8023DC74:
	li       r0, 0x78

lbl_8023DC78:
	lbz      r7, 0(r4)
	mr       r5, r0
	stw      r29, 8(r1)
	slwi     r6, r0, 2
	li       r3, 0
	stw      r7, 0xc(r1)
	lfd      f0, 8(r1)
	fsubs    f0, f0, f27
	fdivs    f1, f26, f0
	fmuls    f0, f1, f28
	b        lbl_8023DE0C

lbl_8023DCA4:
	xoris    r7, r3, 0x8000
	stw      r29, 8(r1)
	add      r9, r3, r8
	stw      r7, 0xc(r1)
	lfd      f2, 8(r1)
	fsubs    f2, f2, f29
	fmuls    f4, f2, f1
	fsubs    f3, f4, f0
	fmr      f2, f3
	fcmpo    cr0, f3, f30
	bge      lbl_8023DCD4
	fneg     f2, f3

lbl_8023DCD4:
	fmuls    f2, f2, f31
	add      r10, r31, r6
	fcmpo    cr0, f3, f30
	fctiwz   f2, f2
	stfd     f2, 0x10(r1)
	lwz      r7, 0x14(r1)
	rlwinm   r7, r7, 3, 0x12, 0x1c
	add      r7, r30, r7
	lfs      f2, 4(r7)
	fmuls    f2, f25, f2
	stfs     f2, 0(r10)
	stfs     f30, 4(r10)
	bge      lbl_8023DD34
	lfs      f2, lbl_8051A628@sda21(r2)
	lis      r7, sincosTable___5JMath@ha
	addi     r7, r7, sincosTable___5JMath@l
	fmuls    f2, f3, f2
	fctiwz   f2, f2
	stfd     f2, 0x18(r1)
	lwz      r8, 0x1c(r1)
	rlwinm   r8, r8, 3, 0x12, 0x1c
	lfsx     f2, r7, r8
	fneg     f2, f2
	b        lbl_8023DD54

lbl_8023DD34:
	fmuls    f2, f3, f31
	lis      r7, sincosTable___5JMath@ha
	addi     r7, r7, sincosTable___5JMath@l
	fctiwz   f2, f2
	stfd     f2, 0x20(r1)
	lwz      r8, 0x24(r1)
	rlwinm   r8, r8, 3, 0x12, 0x1c
	lfsx     f2, r7, r8

lbl_8023DD54:
	fmuls    f2, f25, f2
	fmr      f3, f4
	fcmpo    cr0, f4, f30
	stfs     f2, 8(r10)
	bge      lbl_8023DD6C
	fneg     f3, f4

lbl_8023DD6C:
	fmuls    f2, f3, f31
	mulli    r7, r9, 3
	fcmpo    cr0, f4, f30
	fctiwz   f2, f2
	add      r7, r0, r7
	slwi     r7, r7, 2
	add      r9, r31, r7
	stfd     f2, 0x28(r1)
	lwz      r7, 0x2c(r1)
	rlwinm   r7, r7, 3, 0x12, 0x1c
	add      r7, r30, r7
	lfs      f2, 4(r7)
	fmuls    f2, f25, f2
	stfs     f2, 0(r9)
	stfs     f24, 4(r9)
	bge      lbl_8023DDD8
	lfs      f2, lbl_8051A628@sda21(r2)
	lis      r7, sincosTable___5JMath@ha
	addi     r7, r7, sincosTable___5JMath@l
	fmuls    f2, f4, f2
	fctiwz   f2, f2
	stfd     f2, 0x30(r1)
	lwz      r8, 0x34(r1)
	rlwinm   r8, r8, 3, 0x12, 0x1c
	lfsx     f2, r7, r8
	fneg     f2, f2
	b        lbl_8023DDF8

lbl_8023DDD8:
	fmuls    f2, f4, f31
	lis      r7, sincosTable___5JMath@ha
	addi     r7, r7, sincosTable___5JMath@l
	fctiwz   f2, f2
	stfd     f2, 0x38(r1)
	lwz      r8, 0x3c(r1)
	rlwinm   r8, r8, 3, 0x12, 0x1c
	lfsx     f2, r7, r8

lbl_8023DDF8:
	fmuls    f2, f25, f2
	addi     r5, r5, 3
	addi     r6, r6, 0xc
	addi     r3, r3, 1
	stfs     f2, 8(r9)

lbl_8023DE0C:
	lbz      r8, 0(r4)
	cmpw     r3, r8
	blt      lbl_8023DCA4
	addi     r25, r25, 1
	addi     r26, r26, 4
	cmpwi    r25, 3
	blt      lbl_8023DB14
	bl       getRenderModeObj__6SystemFv
	lhz      r25, 6(r3)
	bl       getRenderModeObj__6SystemFv
	lhz      r4, 4(r3)
	lis      r0, 0x4330
	lfs      f5, lbl_8051A620@sda21(r2)
	mr       r3, r24
	stw      r4, 0x3c(r1)
	lfd      f4, lbl_8051A630@sda21(r2)
	stw      r0, 0x38(r1)
	lfs      f1, lbl_8051A640@sda21(r2)
	lfd      f0, 0x38(r1)
	stfs     f5, 0x10(r24)
	fsubs    f3, f0, f4
	lfs      f0, lbl_8051A64C@sda21(r2)
	stfs     f5, 0x14(r24)
	stw      r25, 0x34(r1)
	stw      r0, 0x30(r1)
	lfd      f2, 0x30(r1)
	stfs     f3, 0x18(r24)
	fsubs    f2, f2, f4
	stfs     f2, 0x1c(r24)
	stfs     f5, 0x20(r24)
	stfs     f5, 0x24(r24)
	stfs     f1, 0x28(r24)
	stfs     f5, 0x38(r24)
	stfs     f5, 0x3c(r24)
	stfs     f1, 0x40(r24)
	stfs     f0, 0x50(r24)
	stfs     f5, 0x2c(r24)
	stfs     f5, 0x30(r24)
	stfs     f1, 0x34(r24)
	stfs     f5, 0x44(r24)
	stfs     f5, 0x48(r24)
	stfs     f1, 0x4c(r24)
	stfs     f0, 0x54(r24)
	psq_l    f31, 216(r1), 0, qr0
	lfd      f31, 0xd0(r1)
	psq_l    f30, 200(r1), 0, qr0
	lfd      f30, 0xc0(r1)
	psq_l    f29, 184(r1), 0, qr0
	lfd      f29, 0xb0(r1)
	psq_l    f28, 168(r1), 0, qr0
	lfd      f28, 0xa0(r1)
	psq_l    f27, 152(r1), 0, qr0
	lfd      f27, 0x90(r1)
	psq_l    f26, 136(r1), 0, qr0
	lfd      f26, 0x80(r1)
	psq_l    f25, 120(r1), 0, qr0
	lfd      f25, 0x70(r1)
	psq_l    f24, 104(r1), 0, qr0
	lfd      f24, 0x60(r1)
	lmw      r24, 0x40(r1)
	lwz      r0, 0xe4(r1)
	mtlr     r0
	addi     r1, r1, 0xe0
	blr
	*/
}

/**
 * @note Address: 0x8023DF0C
 * @note Size: 0x8
 */
void CylinderBase::setColor(Color4* color) { mColor = color; }

/**
 * @note Address: 0x8023DF14
 * @note Size: 0x24
 */
void CylinderBase::setShadowRect(Rectf&)
{
	/*
	lfs      f0, 0(r4)
	stfs     f0, 0x10(r3)
	lfs      f0, 4(r4)
	stfs     f0, 0x14(r3)
	lfs      f0, 8(r4)
	stfs     f0, 0x18(r3)
	lfs      f0, 0xc(r4)
	stfs     f0, 0x1c(r3)
	blr
	*/
}

/**
 * @note Address: 0x8023DF38
 * @note Size: 0xB4
 */
void CylinderBase::setCameraParms(Camera*, int)
{
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stw      r31, 0x2c(r1)
	stw      r30, 0x28(r1)
	mr       r30, r5
	stw      r29, 0x24(r1)
	mr       r29, r4
	stw      r28, 0x20(r1)
	mr       r28, r3
	addi     r3, r1, 0x14
	lwz      r12, 0(r4)
	lwz      r12, 0x4c(r12)
	mtctr    r12
	bctrl
	mulli    r31, r30, 0xc
	lfs      f0, 0x14(r1)
	mr       r4, r29
	addi     r3, r1, 8
	add      r5, r28, r31
	stfs     f0, 0x20(r5)
	lfs      f0, 0x18(r1)
	stfs     f0, 0x24(r5)
	lfs      f0, 0x1c(r1)
	stfs     f0, 0x28(r5)
	bl       getViewVector__11CullFrustumFv
	lfs      f0, 8(r1)
	add      r4, r28, r31
	slwi     r0, r30, 2
	stfs     f0, 0x38(r4)
	add      r3, r28, r0
	lfs      f0, 0xc(r1)
	stfs     f0, 0x3c(r4)
	lfs      f0, 0x10(r1)
	stfs     f0, 0x40(r4)
	lfs      f0, 0x138(r29)
	stfs     f0, 0x50(r3)
	lwz      r31, 0x2c(r1)
	lwz      r30, 0x28(r1)
	lwz      r29, 0x24(r1)
	lwz      r28, 0x20(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/**
 * @note Address: 0x8023DFEC
 * @note Size: 0xCC
 */
void CylinderBase::makeSRT(Matrixf&, Game::ShadowParam&)
{
	/*
	lfs      f1, 0x10(r5)
	lfs      f0, lbl_8051A640@sda21(r2)
	lfs      f3, 0(r5)
	fcmpo    cr0, f1, f0
	lfs      f4, 4(r5)
	lfs      f5, 8(r5)
	lfs      f6, 0x1c(r5)
	lfs      f7, 0x18(r5)
	cror     2, 1, 2
	beq      lbl_8023E024
	lfs      f2, lbl_8051A620@sda21(r2)
	fcmpo    cr0, f1, f2
	cror     2, 0, 2
	bne      lbl_8023E05C

lbl_8023E024:
	stfs     f6, 0(r4)
	lfs      f0, lbl_8051A620@sda21(r2)
	stfs     f0, 0x10(r4)
	stfs     f0, 0x20(r4)
	stfs     f0, 4(r4)
	stfs     f7, 0x14(r4)
	stfs     f0, 0x24(r4)
	stfs     f0, 8(r4)
	stfs     f0, 0x18(r4)
	stfs     f6, 0x28(r4)
	stfs     f3, 0xc(r4)
	stfs     f4, 0x1c(r4)
	stfs     f5, 0x2c(r4)
	blr

lbl_8023E05C:
	stfs     f6, 0(r4)
	lfs      f1, 0xc(r5)
	lfs      f0, 0x10(r5)
	fneg     f1, f1
	fdivs    f0, f1, f0
	fmuls    f0, f6, f0
	stfs     f0, 0x10(r4)
	stfs     f2, 0x20(r4)
	stfs     f2, 4(r4)
	stfs     f7, 0x14(r4)
	stfs     f2, 0x24(r4)
	stfs     f2, 8(r4)
	lfs      f1, 0x14(r5)
	lfs      f0, 0x10(r5)
	fneg     f1, f1
	fdivs    f0, f1, f0
	fmuls    f0, f6, f0
	stfs     f0, 0x18(r4)
	stfs     f6, 0x28(r4)
	stfs     f3, 0xc(r4)
	stfs     f4, 0x1c(r4)
	stfs     f5, 0x2c(r4)
	blr
	*/
}

/**
 * @note Address: 0x8023E0B8
 * @note Size: 0xA4
 */
int CylinderBase::getCylinderType(Game::ShadowParam&, int)
{
	/*
	mulli    r6, r5, 0xc
	slwi     r0, r5, 2
	lwz      r7, 0xc(r3)
	add      r5, r3, r0
	lfs      f1, 4(r4)
	add      r3, r3, r6
	lfs      f0, 0x24(r3)
	lfs      f3, 0(r4)
	fsubs    f0, f1, f0
	lfs      f2, 0x20(r3)
	lfs      f1, 0x3c(r3)
	fsubs    f2, f3, f2
	lfs      f4, 8(r4)
	fmuls    f0, f1, f0
	lfs      f3, 0x28(r3)
	lfs      f1, 0x38(r3)
	fsubs    f5, f4, f3
	lfs      f4, 0x50(r5)
	lfs      f3, 0x1c(r4)
	fmadds   f0, f1, f2, f0
	lfs      f1, 0x40(r3)
	fmuls    f2, f4, f3
	fmadds   f1, f1, f5, f0
	lfs      f0, 0x24(r7)
	fdivs    f1, f2, f1
	fcmpo    cr0, f1, f0
	ble      lbl_8023E12C
	li       r3, 0
	blr

lbl_8023E12C:
	lfs      f0, 0x4c(r7)
	fcmpo    cr0, f1, f0
	ble      lbl_8023E140
	li       r3, 1
	blr

lbl_8023E140:
	lfs      f0, lbl_8051A620@sda21(r2)
	fcmpo    cr0, f1, f0
	ble      lbl_8023E154
	li       r3, 2
	blr

lbl_8023E154:
	li       r3, 0
	blr
	*/
}

/**
 * @note Address: 0x8023E15C
 * @note Size: 0x4
 */
void CylinderBase::setFilterTextureID(int) { }

/**
 * @note Address: 0x8023E160
 * @note Size: 0x4
 */
void CylinderBase::drawInit() { }

/**
 * @note Address: 0x8023E164
 * @note Size: 0x4
 */
void CylinderBase::drawCylinder(Matrixf&, int) { }

/**
 * @note Address: 0x8023E168
 * @note Size: 0x4
 */
void CylinderBase::drawFinish() { }

/**
 * @note Address: N/A
 * @note Size: 0x10C
 */
void CylinderBase::setupFillGX()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0x5C
 */
void CylinderBase::setupDrawCylinderGX()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0x88
 */
void CylinderBase::setupFilterGX()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0x4C
 */
void CylinderBase::setOrthoProjection()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0xA4
 */
void CylinderBase::setOrthoCamera()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0xD0
 */
void CylinderBase::setScissorViewport()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0x90
 */
void CylinderBase::fillShadowRect()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0xD4
 */
void CylinderBase::fillRectAlphaZero()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0x38
 */
void CylinderBase::drawCylinderList(int)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: 0x8023E16C
 * @note Size: 0x164
 */
ShadowCylinder2::ShadowCylinder2(Game::ShadowParms*, Color4*)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	mr       r31, r5
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r29, 0x14(r1)
	mr       r29, r3
	stw      r28, 0x10(r1)
	bl       __ct__Q24Game12CylinderBaseFv
	lis      r4, __vt__Q24Game15ShadowCylinder2@ha
	lis      r3, lbl_80483FBC@ha
	addi     r0, r4, __vt__Q24Game15ShadowCylinder2@l
	li       r5, 0
	stw      r0, 0(r29)
	addi     r4, r3, lbl_80483FBC@l
	lwz      r3, sys@sda21(r13)
	bl       heapStatusStart__6SystemFPcP7JKRHeap
	bl       getRenderModeObj__6SystemFv
	lhz      r28, 6(r3)
	bl       getRenderModeObj__6SystemFv
	lhz      r0, 4(r3)
	rlwinm   r4, r28, 0x1f, 0x11, 0x1f
	li       r5, 0x27
	li       r6, 0
	rlwinm   r3, r0, 0x1f, 0x11, 0x1f
	li       r7, 0
	bl       GXGetTexBufferSize
	lwz      r4, gameSystem__4Game@sda21(r13)
	mr       r28, r3
	cmplwi   r4, 0
	beq      lbl_8023E248
	lwz      r3, 0x44(r4)
	li       r0, 0
	cmpwi    r3, 1
	beq      lbl_8023E208
	cmpwi    r3, 3
	bne      lbl_8023E20C

lbl_8023E208:
	li       r0, 1

lbl_8023E20C:
	clrlwi.  r0, r0, 0x18
	bne      lbl_8023E248
	li       r3, 4
	li       r4, 0x20
	bl       __nwa__FUli
	stw      r3, 0x58(r29)
	mr       r3, r28
	li       r4, 0x20
	bl       __nwa__FUli
	lwz      r4, 0x58(r29)
	stw      r3, 0(r4)
	li       r3, 0x20
	bl       __nwa__FUl
	stw      r3, 0x5c(r29)
	b        lbl_8023E28C

lbl_8023E248:
	li       r3, 8
	li       r4, 0x20
	bl       __nwa__FUli
	stw      r3, 0x58(r29)
	mr       r3, r28
	li       r4, 0x20
	bl       __nwa__FUli
	lwz      r5, 0x58(r29)
	li       r4, 0x20
	stw      r3, 0(r5)
	mr       r3, r28
	bl       __nwa__FUli
	lwz      r4, 0x58(r29)
	stw      r3, 4(r4)
	li       r3, 0x40
	bl       __nwa__FUl
	stw      r3, 0x5c(r29)

lbl_8023E28C:
	stw      r30, 0xc(r29)
	lis      r3, lbl_80483FBC@ha
	li       r0, 0
	stw      r31, 8(r29)
	addi     r4, r3, lbl_80483FBC@l
	stw      r0, 0x60(r29)
	lwz      r3, sys@sda21(r13)
	bl       heapStatusEnd__6SystemFPc
	lwz      r0, 0x24(r1)
	mr       r3, r29
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r28, 0x10(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/**
 * @note Address: 0x8023E2D0
 * @note Size: 0x44
 */
void ShadowCylinder2::setFilterTextureID(int)
{
	/*
	lwz      r5, gameSystem__4Game@sda21(r13)
	cmplwi   r5, 0
	beq      lbl_8023E30C
	lwz      r5, 0x44(r5)
	li       r0, 0
	cmpwi    r5, 1
	beq      lbl_8023E2F4
	cmpwi    r5, 3
	bne      lbl_8023E2F8

lbl_8023E2F4:
	li       r0, 1

lbl_8023E2F8:
	clrlwi.  r0, r0, 0x18
	bne      lbl_8023E30C
	li       r0, 0
	stw      r0, 0x60(r3)
	blr

lbl_8023E30C:
	stw      r4, 0x60(r3)
	blr
	*/
}

/**
 * @note Address: 0x8023E314
 * @note Size: 0x350
 */
void ShadowCylinder2::drawInit()
{
	/*
	stwu     r1, -0xe0(r1)
	mflr     r0
	stw      r0, 0xe4(r1)
	stfd     f31, 0xd0(r1)
	psq_st   f31, 216(r1), 0, qr0
	stfd     f30, 0xc0(r1)
	psq_st   f30, 200(r1), 0, qr0
	stw      r31, 0xbc(r1)
	stw      r30, 0xb8(r1)
	stw      r29, 0xb4(r1)
	stw      r28, 0xb0(r1)
	mr       r31, r3
	lis      r3, lbl_80483F58@ha
	lfs      f1, 0x14(r31)
	addi     r30, r3, lbl_80483F58@l
	lfs      f2, 0x1c(r31)
	addi     r3, r1, 0x68
	lfs      f3, 0x10(r31)
	lfs      f4, 0x18(r31)
	lfs      f5, lbl_8051A620@sda21(r2)
	lfs      f6, lbl_8051A650@sda21(r2)
	bl       C_MTXOrtho
	addi     r3, r1, 0x68
	li       r4, 1
	bl       GXSetProjection
	lwz      r29, 0x40(r30)
	addi     r3, r1, 0x38
	lwz      r28, 0x44(r30)
	addi     r4, r1, 0x2c
	lwz      r12, 0x48(r30)
	addi     r5, r1, 0x14
	lwz      r11, 0x4c(r30)
	addi     r6, r1, 0x20
	lwz      r10, 0x50(r30)
	lwz      r9, 0x54(r30)
	lwz      r8, 0x58(r30)
	lwz      r7, 0x5c(r30)
	lwz      r0, 0x60(r30)
	stw      r29, 0x14(r1)
	stw      r28, 0x18(r1)
	stw      r12, 0x1c(r1)
	stw      r11, 0x20(r1)
	stw      r10, 0x24(r1)
	stw      r9, 0x28(r1)
	stw      r8, 0x2c(r1)
	stw      r7, 0x30(r1)
	stw      r0, 0x34(r1)
	bl       C_MTXLookAt
	addi     r3, r1, 0x38
	li       r4, 0
	bl       GXLoadPosMtxImm
	lfs      f31, 0x14(r31)
	lfs      f0, 0x1c(r31)
	lfs      f30, 0x10(r31)
	fsubs    f1, f0, f31
	bl       __cvt_fp2unsigned
	lfs      f0, 0x18(r31)
	mr       r28, r3
	fsubs    f1, f0, f30
	bl       __cvt_fp2unsigned
	fmr      f1, f31
	mr       r29, r3
	bl       __cvt_fp2unsigned
	fmr      f1, f30
	mr       r30, r3
	bl       __cvt_fp2unsigned
	mr       r4, r30
	mr       r5, r29
	mr       r6, r28
	bl       GXSetScissor
	lfs      f2, 0x14(r31)
	lfs      f0, 0x1c(r31)
	lfs      f1, 0x10(r31)
	lfs      f3, 0x18(r31)
	fsubs    f4, f0, f2
	lfs      f5, lbl_8051A620@sda21(r2)
	fsubs    f3, f3, f1
	lfs      f6, lbl_8051A640@sda21(r2)
	bl       GXSetViewport
	li       r3, 0
	bl       GXSetNumTexGens
	li       r3, 0
	bl       GXSetNumIndStages
	li       r3, 0
	bl       __GXSetIndirectMask
	li       r3, 0
	bl       GXSetCurrentMtx
	li       r3, 1
	bl       GXSetNumTevStages
	li       r3, 0
	li       r4, 4
	bl       GXSetTevOp
	li       r3, 0
	li       r4, 0xff
	li       r5, 0xff
	li       r6, 4
	bl       GXSetTevOrder
	li       r3, 1
	bl       GXSetNumChans
	lwz      r8, 8(r31)
	addi     r4, r1, 0xc
	li       r3, 4
	lbz      r7, 0(r8)
	lbz      r6, 1(r8)
	lbz      r5, 2(r8)
	lbz      r0, 3(r8)
	stb      r7, 8(r1)
	stb      r6, 9(r1)
	stb      r5, 0xa(r1)
	stb      r0, 0xb(r1)
	lwz      r0, 8(r1)
	stw      r0, 0xc(r1)
	bl       GXSetChanMatColor
	li       r3, 4
	li       r4, 0
	li       r5, 0
	li       r6, 0
	li       r7, 0
	li       r8, 0
	li       r9, 2
	bl       GXSetChanCtrl
	li       r3, 2
	bl       GXSetCullMode
	li       r3, 0
	li       r4, 0
	li       r5, 0
	bl       GXSetZMode
	li       r3, 0
	li       r4, 1
	li       r5, 1
	li       r6, 0
	bl       GXSetBlendMode
	li       r3, 0
	bl       GXSetColorUpdate
	li       r3, 1
	bl       GXSetAlphaUpdate
	li       r3, 1
	li       r4, 0
	bl       GXSetDstAlpha
	bl       GXClearVtxDesc
	bl       GXInvalidateVtxCache
	li       r3, 9
	li       r4, 1
	bl       GXSetVtxDesc
	li       r3, 0
	li       r4, 9
	li       r5, 1
	li       r6, 4
	li       r7, 0
	bl       GXSetVtxAttrFmt
	li       r3, 0x80
	li       r4, 0
	li       r5, 4
	bl       GXBegin
	lfs      f2, 0x14(r31)
	lis      r5, 0xCC008000@ha
	lfs      f0, 0x10(r31)
	li       r3, 0
	lfs      f1, lbl_8051A620@sda21(r2)
	li       r4, 0
	stfs     f0, 0xCC008000@l(r5)
	stfs     f2, -0x8000(r5)
	stfs     f1, -0x8000(r5)
	lfs      f2, 0x14(r31)
	lfs      f0, 0x18(r31)
	stfs     f0, -0x8000(r5)
	stfs     f2, -0x8000(r5)
	stfs     f1, -0x8000(r5)
	lfs      f2, 0x1c(r31)
	lfs      f0, 0x18(r31)
	stfs     f0, -0x8000(r5)
	stfs     f2, -0x8000(r5)
	stfs     f1, -0x8000(r5)
	lfs      f2, 0x1c(r31)
	lfs      f0, 0x10(r31)
	stfs     f0, -0x8000(r5)
	stfs     f2, -0x8000(r5)
	stfs     f1, -0x8000(r5)
	bl       GXSetDstAlpha
	lwz      r0, lbl_8051A654@sda21(r2)
	addi     r4, r1, 0x10
	li       r3, 4
	stw      r0, 0x10(r1)
	bl       GXSetChanMatColor
	bl       GXClearVtxDesc
	bl       GXInvalidateVtxCache
	li       r3, 9
	li       r4, 3
	bl       GXSetVtxDesc
	li       r3, 0
	li       r4, 9
	li       r5, 1
	li       r6, 4
	li       r7, 0
	bl       GXSetVtxAttrFmt
	lis      r4, sCylinderVertPos__4Game@ha
	li       r3, 9
	addi     r4, r4, sCylinderVertPos__4Game@l
	li       r5, 0xc
	bl       GXSetArray
	psq_l    f31, 216(r1), 0, qr0
	lfd      f31, 0xd0(r1)
	psq_l    f30, 200(r1), 0, qr0
	lfd      f30, 0xc0(r1)
	lwz      r31, 0xbc(r1)
	lwz      r30, 0xb8(r1)
	lwz      r29, 0xb4(r1)
	lwz      r0, 0xe4(r1)
	lwz      r28, 0xb0(r1)
	mtlr     r0
	addi     r1, r1, 0xe0
	blr
	*/
}

/**
 * @note Address: 0x8023E664
 * @note Size: 0xC0
 */
void ShadowCylinder2::drawCylinder(Matrixf&, int)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	mr       r0, r4
	li       r4, 0
	stw      r31, 0xc(r1)
	mr       r31, r5
	stw      r30, 8(r1)
	mr       r30, r3
	mr       r3, r0
	bl       GXLoadPosMtxImm
	li       r3, 1
	li       r4, 3
	li       r5, 0
	bl       GXSetZMode
	li       r3, 2
	bl       GXSetCullMode
	li       r3, 1
	li       r4, 1
	li       r5, 1
	li       r6, 5
	bl       GXSetBlendMode
	lwz      r3, 4(r30)
	slwi     r31, r31, 2
	lwzx     r3, r3, r31
	lwz      r0, 8(r3)
	lwz      r3, 4(r3)
	rlwinm   r4, r0, 0, 0, 0x1a
	bl       GXCallDisplayList
	li       r3, 1
	bl       GXSetCullMode
	li       r3, 3
	li       r4, 1
	li       r5, 1
	li       r6, 5
	bl       GXSetBlendMode
	lwz      r3, 4(r30)
	lwzx     r3, r3, r31
	lwz      r0, 8(r3)
	lwz      r3, 4(r3)
	rlwinm   r4, r0, 0, 0, 0x1a
	bl       GXCallDisplayList
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8023E724
 * @note Size: 0x1E4
 */
void ShadowCylinder2::drawFinish()
{
	/*
	stwu     r1, -0xe0(r1)
	mflr     r0
	stw      r0, 0xe4(r1)
	stfd     f31, 0xd0(r1)
	psq_st   f31, 216(r1), 0, qr0
	stfd     f30, 0xc0(r1)
	psq_st   f30, 200(r1), 0, qr0
	stw      r31, 0xbc(r1)
	stw      r30, 0xb8(r1)
	stw      r29, 0xb4(r1)
	stw      r28, 0xb0(r1)
	mr       r31, r3
	lis      r3, lbl_80483F58@ha
	lfs      f1, 0x14(r31)
	addi     r30, r3, lbl_80483F58@l
	lfs      f2, 0x1c(r31)
	addi     r3, r1, 0x64
	lfs      f3, 0x10(r31)
	lfs      f4, 0x18(r31)
	lfs      f5, lbl_8051A620@sda21(r2)
	lfs      f6, lbl_8051A650@sda21(r2)
	bl       C_MTXOrtho
	addi     r3, r1, 0x64
	li       r4, 1
	bl       GXSetProjection
	lwz      r29, 0x40(r30)
	addi     r3, r1, 0x34
	lwz      r28, 0x44(r30)
	addi     r4, r1, 0x28
	lwz      r12, 0x48(r30)
	addi     r5, r1, 0x10
	lwz      r11, 0x4c(r30)
	addi     r6, r1, 0x1c
	lwz      r10, 0x50(r30)
	lwz      r9, 0x54(r30)
	lwz      r8, 0x58(r30)
	lwz      r7, 0x5c(r30)
	lwz      r0, 0x60(r30)
	stw      r29, 0x10(r1)
	stw      r28, 0x14(r1)
	stw      r12, 0x18(r1)
	stw      r11, 0x1c(r1)
	stw      r10, 0x20(r1)
	stw      r9, 0x24(r1)
	stw      r8, 0x28(r1)
	stw      r7, 0x2c(r1)
	stw      r0, 0x30(r1)
	bl       C_MTXLookAt
	addi     r3, r1, 0x34
	li       r4, 0
	bl       GXLoadPosMtxImm
	lfs      f31, 0x14(r31)
	lfs      f0, 0x1c(r31)
	lfs      f30, 0x10(r31)
	fsubs    f1, f0, f31
	bl       __cvt_fp2unsigned
	lfs      f0, 0x18(r31)
	mr       r28, r3
	fsubs    f1, f0, f30
	bl       __cvt_fp2unsigned
	fmr      f1, f31
	mr       r29, r3
	bl       __cvt_fp2unsigned
	fmr      f1, f30
	mr       r30, r3
	bl       __cvt_fp2unsigned
	mr       r4, r30
	mr       r5, r29
	mr       r6, r28
	bl       GXSetScissor
	lfs      f2, 0x14(r31)
	lfs      f0, 0x1c(r31)
	lfs      f1, 0x10(r31)
	lfs      f3, 0x18(r31)
	fsubs    f4, f0, f2
	lfs      f5, lbl_8051A620@sda21(r2)
	fsubs    f3, f3, f1
	lfs      f6, lbl_8051A640@sda21(r2)
	bl       GXSetViewport
	li       r3, 1
	bl       GXSetColorUpdate
	li       r3, 1
	bl       GXSetAlphaUpdate
	lwz      r8, 8(r31)
	addi     r4, r1, 0xc
	li       r3, 4
	lbz      r7, 0(r8)
	lbz      r6, 1(r8)
	lbz      r5, 2(r8)
	lbz      r0, 3(r8)
	stb      r7, 8(r1)
	stb      r6, 9(r1)
	stb      r5, 0xa(r1)
	stb      r0, 0xb(r1)
	lwz      r0, 8(r1)
	stw      r0, 0xc(r1)
	bl       GXSetChanMatColor
	li       r3, 2
	bl       GXSetCullMode
	li       r3, 0
	li       r4, 0
	li       r5, 0
	bl       GXSetZMode
	mr       r3, r31
	bl       copyShadowTexture__Q24Game15ShadowCylinder2Fv
	mr       r3, r31
	bl       setupTextureFilterGX__Q24Game15ShadowCylinder2Fv
	mr       r3, r31
	bl       drawTextureFilter__Q24Game15ShadowCylinder2Fv
	psq_l    f31, 216(r1), 0, qr0
	lfd      f31, 0xd0(r1)
	psq_l    f30, 200(r1), 0, qr0
	lfd      f30, 0xc0(r1)
	lwz      r31, 0xbc(r1)
	lwz      r30, 0xb8(r1)
	lwz      r29, 0xb4(r1)
	lwz      r0, 0xe4(r1)
	lwz      r28, 0xb0(r1)
	mtlr     r0
	addi     r1, r1, 0xe0
	blr
	*/
}

/**
 * @note Address: 0x8023E908
 * @note Size: 0x170
 */
void ShadowCylinder2::copyShadowTexture()
{
	/*
	stwu     r1, -0x50(r1)
	mflr     r0
	stw      r0, 0x54(r1)
	stw      r31, 0x4c(r1)
	mr       r31, r3
	lfs      f0, 0x10(r3)
	lfs      f2, 0x14(r3)
	fctiwz   f3, f0
	lfs      f1, 0x18(r3)
	lfs      f0, 0x1c(r3)
	fctiwz   f2, f2
	fctiwz   f1, f1
	fctiwz   f0, f0
	stfd     f3, 8(r1)
	stfd     f2, 0x10(r1)
	lwz      r3, 0xc(r1)
	stfd     f1, 0x18(r1)
	lwz      r4, 0x14(r1)
	stfd     f0, 0x20(r1)
	lwz      r5, 0x1c(r1)
	lwz      r6, 0x24(r1)
	bl       GXSetTexCopySrc
	lfs      f3, 0x18(r31)
	li       r5, 0x27
	lfs      f2, 0x10(r31)
	li       r6, 1
	lfs      f1, 0x1c(r31)
	lfs      f0, 0x14(r31)
	fsubs    f3, f3, f2
	lfs      f2, lbl_8051A61C@sda21(r2)
	fsubs    f0, f1, f0
	fmuls    f1, f3, f2
	fmuls    f0, f0, f2
	fctiwz   f1, f1
	fctiwz   f0, f0
	stfd     f1, 0x28(r1)
	stfd     f0, 0x30(r1)
	lwz      r3, 0x2c(r1)
	lwz      r4, 0x34(r1)
	bl       GXSetTexCopyDst
	lwz      r0, 0x60(r31)
	li       r4, 0
	lwz      r3, 0x58(r31)
	slwi     r0, r0, 2
	lwzx     r3, r3, r0
	bl       GXCopyTex
	bl       GXPixModeSync
	lfs      f3, 0x18(r31)
	li       r7, 1
	lfs      f2, 0x10(r31)
	li       r8, 0
	lfs      f1, 0x1c(r31)
	li       r9, 0
	lfs      f0, 0x14(r31)
	fsubs    f3, f3, f2
	lfs      f2, lbl_8051A61C@sda21(r2)
	li       r10, 0
	fsubs    f0, f1, f0
	lwz      r4, 0x60(r31)
	fmuls    f1, f3, f2
	lwz      r3, 0x58(r31)
	slwi     r0, r4, 2
	fmuls    f0, f0, f2
	fctiwz   f1, f1
	lwz      r6, 0x5c(r31)
	slwi     r5, r4, 5
	lwzx     r4, r3, r0
	fctiwz   f0, f0
	stfd     f1, 0x38(r1)
	add      r3, r6, r5
	stfd     f0, 0x40(r1)
	lwz      r5, 0x3c(r1)
	lwz      r6, 0x44(r1)
	bl       GXInitTexObj
	lfs      f1, lbl_8051A620@sda21(r2)
	li       r4, 1
	lwz      r0, 0x60(r31)
	li       r5, 1
	fmr      f2, f1
	lwz      r3, 0x5c(r31)
	slwi     r0, r0, 5
	fmr      f3, f1
	add      r3, r3, r0
	li       r6, 0
	li       r7, 0
	li       r8, 0
	bl       GXInitTexObjLOD
	lwz      r0, 0x54(r1)
	lwz      r31, 0x4c(r1)
	mtlr     r0
	addi     r1, r1, 0x50
	blr
	*/
}

/**
 * @note Address: 0x8023EA78
 * @note Size: 0xFC
 */
void ShadowCylinder2::setupTextureFilterGX()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	li       r4, 0
	stw      r0, 0x14(r1)
	lwz      r0, 0x60(r3)
	lwz      r3, 0x5c(r3)
	slwi     r0, r0, 5
	add      r3, r3, r0
	bl       GXLoadTexObj
	li       r3, 1
	bl       GXSetNumTexGens
	li       r3, 0
	li       r4, 1
	li       r5, 4
	li       r6, 0x3c
	li       r7, 0
	li       r8, 0x7d
	bl       GXSetTexCoordGen2
	li       r3, 0
	li       r4, 0
	li       r5, 0
	li       r6, 4
	bl       GXSetTevOrder
	lwz      r0, lbl_80520E88@sda21(r2)
	addi     r4, r1, 8
	li       r3, 1
	stw      r0, 8(r1)
	bl       GXSetTevColor
	li       r3, 0
	li       r4, 9
	li       r5, 3
	li       r6, 0xa
	li       r7, 0xf
	bl       GXSetTevColorIn
	li       r3, 0
	li       r4, 8
	li       r5, 0
	li       r6, 0
	li       r7, 0
	li       r8, 0
	bl       GXSetTevColorOp
	li       r3, 0
	li       r4, 4
	li       r5, 1
	li       r6, 5
	li       r7, 7
	bl       GXSetTevAlphaIn
	li       r3, 0
	li       r4, 8
	li       r5, 0
	li       r6, 0
	li       r7, 0
	li       r8, 0
	bl       GXSetTevAlphaOp
	li       r3, 1
	li       r4, 4
	li       r5, 5
	li       r6, 5
	bl       GXSetBlendMode
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8023EB74
 * @note Size: 0x108
 */
void ShadowCylinder2::drawTextureFilter()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	bl       GXClearVtxDesc
	bl       GXInvalidateVtxCache
	li       r3, 9
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
	li       r4, 0xd
	li       r5, 1
	li       r6, 1
	li       r7, 4
	bl       GXSetVtxAttrFmt
	li       r3, 0x80
	li       r4, 0
	li       r5, 4
	bl       GXBegin
	lfs      f2, 0x14(r31)
	lis      r4, 0xCC008000@ha
	lfs      f0, 0x10(r31)
	li       r3, 0
	lfs      f1, lbl_8051A620@sda21(r2)
	li       r0, 0x10
	stfs     f0, 0xCC008000@l(r4)
	stfs     f2, -0x8000(r4)
	stfs     f1, -0x8000(r4)
	stb      r3, -0x8000(r4)
	stb      r3, -0x8000(r4)
	lfs      f2, 0x14(r31)
	lfs      f0, 0x18(r31)
	stfs     f0, -0x8000(r4)
	stfs     f2, -0x8000(r4)
	stfs     f1, -0x8000(r4)
	stb      r0, -0x8000(r4)
	stb      r3, -0x8000(r4)
	lfs      f2, 0x1c(r31)
	lfs      f0, 0x18(r31)
	stfs     f0, -0x8000(r4)
	stfs     f2, -0x8000(r4)
	stfs     f1, -0x8000(r4)
	stb      r0, -0x8000(r4)
	stb      r0, -0x8000(r4)
	lfs      f2, 0x1c(r31)
	lfs      f0, 0x10(r31)
	stfs     f0, -0x8000(r4)
	stfs     f2, -0x8000(r4)
	stfs     f1, -0x8000(r4)
	stb      r3, -0x8000(r4)
	stb      r0, -0x8000(r4)
	lwz      r31, 0xc(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8023EC7C
 * @note Size: 0x5C
 */
ShadowCylinder3::ShadowCylinder3(Game::ShadowParms*, Color4*)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	mr       r31, r5
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r29, 0x14(r1)
	mr       r29, r3
	bl       __ct__Q24Game12CylinderBaseFv
	lis      r4, __vt__Q24Game15ShadowCylinder3@ha
	mr       r3, r29
	addi     r0, r4, __vt__Q24Game15ShadowCylinder3@l
	stw      r0, 0(r29)
	stw      r30, 0xc(r29)
	stw      r31, 8(r29)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/**
 * @note Address: 0x8023ECD8
 * @note Size: 0x350
 */
void ShadowCylinder3::drawInit()
{
	/*
	stwu     r1, -0xe0(r1)
	mflr     r0
	stw      r0, 0xe4(r1)
	stfd     f31, 0xd0(r1)
	psq_st   f31, 216(r1), 0, qr0
	stfd     f30, 0xc0(r1)
	psq_st   f30, 200(r1), 0, qr0
	stw      r31, 0xbc(r1)
	stw      r30, 0xb8(r1)
	stw      r29, 0xb4(r1)
	stw      r28, 0xb0(r1)
	mr       r31, r3
	lis      r3, lbl_80483F58@ha
	lfs      f1, 0x14(r31)
	addi     r30, r3, lbl_80483F58@l
	lfs      f2, 0x1c(r31)
	addi     r3, r1, 0x68
	lfs      f3, 0x10(r31)
	lfs      f4, 0x18(r31)
	lfs      f5, lbl_8051A620@sda21(r2)
	lfs      f6, lbl_8051A650@sda21(r2)
	bl       C_MTXOrtho
	addi     r3, r1, 0x68
	li       r4, 1
	bl       GXSetProjection
	lwz      r29, 0x40(r30)
	addi     r3, r1, 0x38
	lwz      r28, 0x44(r30)
	addi     r4, r1, 0x2c
	lwz      r12, 0x48(r30)
	addi     r5, r1, 0x14
	lwz      r11, 0x4c(r30)
	addi     r6, r1, 0x20
	lwz      r10, 0x50(r30)
	lwz      r9, 0x54(r30)
	lwz      r8, 0x58(r30)
	lwz      r7, 0x5c(r30)
	lwz      r0, 0x60(r30)
	stw      r29, 0x14(r1)
	stw      r28, 0x18(r1)
	stw      r12, 0x1c(r1)
	stw      r11, 0x20(r1)
	stw      r10, 0x24(r1)
	stw      r9, 0x28(r1)
	stw      r8, 0x2c(r1)
	stw      r7, 0x30(r1)
	stw      r0, 0x34(r1)
	bl       C_MTXLookAt
	addi     r3, r1, 0x38
	li       r4, 0
	bl       GXLoadPosMtxImm
	lfs      f31, 0x14(r31)
	lfs      f0, 0x1c(r31)
	lfs      f30, 0x10(r31)
	fsubs    f1, f0, f31
	bl       __cvt_fp2unsigned
	lfs      f0, 0x18(r31)
	mr       r28, r3
	fsubs    f1, f0, f30
	bl       __cvt_fp2unsigned
	fmr      f1, f31
	mr       r29, r3
	bl       __cvt_fp2unsigned
	fmr      f1, f30
	mr       r30, r3
	bl       __cvt_fp2unsigned
	mr       r4, r30
	mr       r5, r29
	mr       r6, r28
	bl       GXSetScissor
	lfs      f2, 0x14(r31)
	lfs      f0, 0x1c(r31)
	lfs      f1, 0x10(r31)
	lfs      f3, 0x18(r31)
	fsubs    f4, f0, f2
	lfs      f5, lbl_8051A620@sda21(r2)
	fsubs    f3, f3, f1
	lfs      f6, lbl_8051A640@sda21(r2)
	bl       GXSetViewport
	li       r3, 0
	bl       GXSetNumTexGens
	li       r3, 0
	bl       GXSetNumIndStages
	li       r3, 0
	bl       __GXSetIndirectMask
	li       r3, 0
	bl       GXSetCurrentMtx
	li       r3, 1
	bl       GXSetNumTevStages
	li       r3, 0
	li       r4, 4
	bl       GXSetTevOp
	li       r3, 0
	li       r4, 0xff
	li       r5, 0xff
	li       r6, 4
	bl       GXSetTevOrder
	li       r3, 1
	bl       GXSetNumChans
	lwz      r8, 8(r31)
	addi     r4, r1, 0xc
	li       r3, 4
	lbz      r7, 0(r8)
	lbz      r6, 1(r8)
	lbz      r5, 2(r8)
	lbz      r0, 3(r8)
	stb      r7, 8(r1)
	stb      r6, 9(r1)
	stb      r5, 0xa(r1)
	stb      r0, 0xb(r1)
	lwz      r0, 8(r1)
	stw      r0, 0xc(r1)
	bl       GXSetChanMatColor
	li       r3, 4
	li       r4, 0
	li       r5, 0
	li       r6, 0
	li       r7, 0
	li       r8, 0
	li       r9, 2
	bl       GXSetChanCtrl
	li       r3, 2
	bl       GXSetCullMode
	li       r3, 0
	li       r4, 0
	li       r5, 0
	bl       GXSetZMode
	li       r3, 0
	li       r4, 1
	li       r5, 1
	li       r6, 0
	bl       GXSetBlendMode
	li       r3, 0
	bl       GXSetColorUpdate
	li       r3, 1
	bl       GXSetAlphaUpdate
	li       r3, 1
	li       r4, 0
	bl       GXSetDstAlpha
	bl       GXClearVtxDesc
	bl       GXInvalidateVtxCache
	li       r3, 9
	li       r4, 1
	bl       GXSetVtxDesc
	li       r3, 0
	li       r4, 9
	li       r5, 1
	li       r6, 4
	li       r7, 0
	bl       GXSetVtxAttrFmt
	li       r3, 0x80
	li       r4, 0
	li       r5, 4
	bl       GXBegin
	lfs      f2, 0x14(r31)
	lis      r5, 0xCC008000@ha
	lfs      f0, 0x10(r31)
	li       r3, 0
	lfs      f1, lbl_8051A620@sda21(r2)
	li       r4, 0
	stfs     f0, 0xCC008000@l(r5)
	stfs     f2, -0x8000(r5)
	stfs     f1, -0x8000(r5)
	lfs      f2, 0x14(r31)
	lfs      f0, 0x18(r31)
	stfs     f0, -0x8000(r5)
	stfs     f2, -0x8000(r5)
	stfs     f1, -0x8000(r5)
	lfs      f2, 0x1c(r31)
	lfs      f0, 0x18(r31)
	stfs     f0, -0x8000(r5)
	stfs     f2, -0x8000(r5)
	stfs     f1, -0x8000(r5)
	lfs      f2, 0x1c(r31)
	lfs      f0, 0x10(r31)
	stfs     f0, -0x8000(r5)
	stfs     f2, -0x8000(r5)
	stfs     f1, -0x8000(r5)
	bl       GXSetDstAlpha
	lwz      r0, lbl_8051A658@sda21(r2)
	addi     r4, r1, 0x10
	li       r3, 4
	stw      r0, 0x10(r1)
	bl       GXSetChanMatColor
	bl       GXClearVtxDesc
	bl       GXInvalidateVtxCache
	li       r3, 9
	li       r4, 3
	bl       GXSetVtxDesc
	li       r3, 0
	li       r4, 9
	li       r5, 1
	li       r6, 4
	li       r7, 0
	bl       GXSetVtxAttrFmt
	lis      r4, sCylinderVertPos__4Game@ha
	li       r3, 9
	addi     r4, r4, sCylinderVertPos__4Game@l
	li       r5, 0xc
	bl       GXSetArray
	psq_l    f31, 216(r1), 0, qr0
	lfd      f31, 0xd0(r1)
	psq_l    f30, 200(r1), 0, qr0
	lfd      f30, 0xc0(r1)
	lwz      r31, 0xbc(r1)
	lwz      r30, 0xb8(r1)
	lwz      r29, 0xb4(r1)
	lwz      r0, 0xe4(r1)
	lwz      r28, 0xb0(r1)
	mtlr     r0
	addi     r1, r1, 0xe0
	blr
	*/
}

/**
 * @note Address: 0x8023F028
 * @note Size: 0xF8
 */
void ShadowCylinder3::drawCylinder(Matrixf&, int)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	mr       r0, r4
	li       r4, 0
	stw      r31, 0xc(r1)
	mr       r31, r5
	stw      r30, 8(r1)
	mr       r30, r3
	mr       r3, r0
	bl       GXLoadPosMtxImm
	li       r3, 1
	bl       GXSetCullMode
	li       r3, 1
	li       r4, 6
	li       r5, 0
	bl       GXSetZMode
	li       r3, 1
	li       r4, 1
	li       r5, 1
	li       r6, 5
	bl       GXSetBlendMode
	lwz      r3, 4(r30)
	slwi     r31, r31, 2
	lwzx     r3, r3, r31
	lwz      r0, 8(r3)
	lwz      r3, 4(r3)
	rlwinm   r4, r0, 0, 0, 0x1a
	bl       GXCallDisplayList
	li       r3, 2
	bl       GXSetCullMode
	li       r3, 1
	li       r4, 3
	li       r5, 0
	bl       GXSetZMode
	lwz      r3, 4(r30)
	lwzx     r3, r3, r31
	lwz      r0, 8(r3)
	lwz      r3, 4(r3)
	rlwinm   r4, r0, 0, 0, 0x1a
	bl       GXCallDisplayList
	li       r3, 0
	li       r4, 7
	li       r5, 0
	bl       GXSetZMode
	li       r3, 3
	li       r4, 1
	li       r5, 1
	li       r6, 5
	bl       GXSetBlendMode
	lwz      r3, 4(r30)
	lwzx     r3, r3, r31
	lwz      r0, 8(r3)
	lwz      r3, 4(r3)
	rlwinm   r4, r0, 0, 0, 0x1a
	bl       GXCallDisplayList
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8023F120
 * @note Size: 0x1D4
 */
void ShadowCylinder3::drawFinish()
{
	/*
	stwu     r1, -0xe0(r1)
	mflr     r0
	stw      r0, 0xe4(r1)
	stfd     f31, 0xd0(r1)
	psq_st   f31, 216(r1), 0, qr0
	stfd     f30, 0xc0(r1)
	psq_st   f30, 200(r1), 0, qr0
	stw      r31, 0xbc(r1)
	stw      r30, 0xb8(r1)
	stw      r29, 0xb4(r1)
	stw      r28, 0xb0(r1)
	mr       r31, r3
	lis      r3, lbl_80483F58@ha
	lfs      f1, 0x14(r31)
	addi     r30, r3, lbl_80483F58@l
	lfs      f2, 0x1c(r31)
	addi     r3, r1, 0x64
	lfs      f3, 0x10(r31)
	lfs      f4, 0x18(r31)
	lfs      f5, lbl_8051A620@sda21(r2)
	lfs      f6, lbl_8051A650@sda21(r2)
	bl       C_MTXOrtho
	addi     r3, r1, 0x64
	li       r4, 1
	bl       GXSetProjection
	lwz      r29, 0x40(r30)
	addi     r3, r1, 0x34
	lwz      r28, 0x44(r30)
	addi     r4, r1, 0x28
	lwz      r12, 0x48(r30)
	addi     r5, r1, 0x10
	lwz      r11, 0x4c(r30)
	addi     r6, r1, 0x1c
	lwz      r10, 0x50(r30)
	lwz      r9, 0x54(r30)
	lwz      r8, 0x58(r30)
	lwz      r7, 0x5c(r30)
	lwz      r0, 0x60(r30)
	stw      r29, 0x10(r1)
	stw      r28, 0x14(r1)
	stw      r12, 0x18(r1)
	stw      r11, 0x1c(r1)
	stw      r10, 0x20(r1)
	stw      r9, 0x24(r1)
	stw      r8, 0x28(r1)
	stw      r7, 0x2c(r1)
	stw      r0, 0x30(r1)
	bl       C_MTXLookAt
	addi     r3, r1, 0x34
	li       r4, 0
	bl       GXLoadPosMtxImm
	lfs      f31, 0x14(r31)
	lfs      f0, 0x1c(r31)
	lfs      f30, 0x10(r31)
	fsubs    f1, f0, f31
	bl       __cvt_fp2unsigned
	lfs      f0, 0x18(r31)
	mr       r28, r3
	fsubs    f1, f0, f30
	bl       __cvt_fp2unsigned
	fmr      f1, f31
	mr       r29, r3
	bl       __cvt_fp2unsigned
	fmr      f1, f30
	mr       r30, r3
	bl       __cvt_fp2unsigned
	mr       r4, r30
	mr       r5, r29
	mr       r6, r28
	bl       GXSetScissor
	lfs      f2, 0x14(r31)
	lfs      f0, 0x1c(r31)
	lfs      f1, 0x10(r31)
	lfs      f3, 0x18(r31)
	fsubs    f4, f0, f2
	lfs      f5, lbl_8051A620@sda21(r2)
	fsubs    f3, f3, f1
	lfs      f6, lbl_8051A640@sda21(r2)
	bl       GXSetViewport
	li       r3, 1
	bl       GXSetColorUpdate
	li       r3, 1
	bl       GXSetAlphaUpdate
	lwz      r8, 8(r31)
	addi     r4, r1, 0xc
	li       r3, 4
	lbz      r7, 0(r8)
	lbz      r6, 1(r8)
	lbz      r5, 2(r8)
	lbz      r0, 3(r8)
	stb      r7, 8(r1)
	stb      r6, 9(r1)
	stb      r5, 0xa(r1)
	stb      r0, 0xb(r1)
	lwz      r0, 8(r1)
	stw      r0, 0xc(r1)
	bl       GXSetChanMatColor
	li       r3, 2
	bl       GXSetCullMode
	li       r3, 0
	li       r4, 0
	li       r5, 0
	bl       GXSetZMode
	mr       r3, r31
	bl       drawScreenFilter__Q24Game15ShadowCylinder3Fv
	psq_l    f31, 216(r1), 0, qr0
	lfd      f31, 0xd0(r1)
	psq_l    f30, 200(r1), 0, qr0
	lfd      f30, 0xc0(r1)
	lwz      r31, 0xbc(r1)
	lwz      r30, 0xb8(r1)
	lwz      r29, 0xb4(r1)
	lwz      r0, 0xe4(r1)
	lwz      r28, 0xb0(r1)
	mtlr     r0
	addi     r1, r1, 0xe0
	blr
	*/
}

/**
 * @note Address: 0x8023F2F4
 * @note Size: 0xD0
 */
void ShadowCylinder3::drawScreenFilter()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	li       r4, 6
	li       r5, 7
	stw      r0, 0x14(r1)
	li       r6, 5
	stw      r31, 0xc(r1)
	mr       r31, r3
	li       r3, 1
	bl       GXSetBlendMode
	bl       GXClearVtxDesc
	bl       GXInvalidateVtxCache
	li       r3, 9
	li       r4, 1
	bl       GXSetVtxDesc
	li       r3, 0
	li       r4, 9
	li       r5, 1
	li       r6, 4
	li       r7, 0
	bl       GXSetVtxAttrFmt
	li       r3, 0x80
	li       r4, 0
	li       r5, 4
	bl       GXBegin
	lfs      f2, 0x14(r31)
	lis      r3, 0xCC008000@ha
	lfs      f0, 0x10(r31)
	lfs      f1, lbl_8051A620@sda21(r2)
	stfs     f0, 0xCC008000@l(r3)
	stfs     f2, -0x8000(r3)
	stfs     f1, -0x8000(r3)
	lfs      f2, 0x14(r31)
	lfs      f0, 0x18(r31)
	stfs     f0, -0x8000(r3)
	stfs     f2, -0x8000(r3)
	stfs     f1, -0x8000(r3)
	lfs      f2, 0x1c(r31)
	lfs      f0, 0x18(r31)
	stfs     f0, -0x8000(r3)
	stfs     f2, -0x8000(r3)
	stfs     f1, -0x8000(r3)
	lfs      f2, 0x1c(r31)
	lfs      f0, 0x10(r31)
	stfs     f0, -0x8000(r3)
	stfs     f2, -0x8000(r3)
	stfs     f1, -0x8000(r3)
	lwz      r31, 0xc(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x8023F3C4
 * @note Size: 0x4
 */
void ShadowCylinder3::setFilterTextureID(int) { }

} // namespace Game

/**
 * @note Address: 0x8023F3C8
 * @note Size: 0x28
 */
void __sinit_ShadowCylinder_cpp()
{
	/*
	lis      r4, __float_nan@ha
	li       r0, -1
	lfs      f0, __float_nan@l(r4)
	lis      r3, lbl_804C1780@ha
	stw      r0, lbl_80515CE8@sda21(r13)
	stfsu    f0, lbl_804C1780@l(r3)
	stfs     f0, lbl_80515CEC@sda21(r13)
	stfs     f0, 4(r3)
	stfs     f0, 8(r3)
	blr
	*/
}
