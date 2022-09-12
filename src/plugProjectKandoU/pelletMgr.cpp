#include "Dolphin/rand.h"
#include "Game/GameSystem.h"
#include "Game/pelletMgr.h"
#include "Game/PelletView.h"
#include "Game/shadowMgr.h"
#include "Game/EnemyBase.h"
#include "Game/Stickers.h"
#include "Game/GameMessage.h"
#include "Game/GameStats.h"
#include "efx/TFruitsDown.h"
#include "PSM/Otakara.h"
#include "Iterator.h"
#include "System.h"
#include "ObjectTypes.h"
#include "CollInfo.h"
#include "Radar.h"

namespace Game {

/*
 * --INFO--
 * Address:	801658EC
 * Size:	000020
 */
char* Pellet::getCreatureName()
{
	if (m_config != nullptr) {
		return m_config->m_params.m_name.m_data;
	}
	return "no config pellet";
}

/*
 * --INFO--
 * Address:	8016590C
 * Size:	000034
 */
s32 Pellet::getCreatureID()
{
	if (m_config != nullptr) {
		return getConfigIndex();
	}
	return -1;
}

/*
 * --INFO--
 * Address:	80165940
 * Size:	000190
 */
void Pellet::getShadowParam(ShadowParam& shadow)
{
	Vector3f col;
	m_mainMatrix.getBasis(1, col);

	if (-(SQUARE(FABS(col.y)) - 1.0f) > 0.0f) {
		col.y = col.y;
	}

	float pickRadius  = getPickRadius();
	Vector3f position = getPosition();
	Vector3f shadowPos;
	if (col.y > 0.0f) {
		float midHeight    = 0.5f * getCylinderHeight();
		Vector3f scaledCol = col * midHeight;
		shadowPos          = position - scaledCol;
	} else {
		float midHeight    = 0.5f * getCylinderHeight();
		Vector3f scaledCol = col * midHeight;
		shadowPos          = position + scaledCol;
	}

	float absY = FABS(col.y);
	shadowPos.y += 0.2f;
	shadow.m_position                  = shadowPos;
	shadow.m_boundingSphere.m_position = col;
	shadow.m_boundingSphere.m_radius   = 90.0f;
	shadow._1C                         = pickRadius * FABS(col.y);
}

/*
 * --INFO--
 * Address:	80165AD0
 * Size:	000074
 */
bool Pellet::needShadow()
{
	return ((pelletMgr->_3C == 0) || ((pelletMgr->_3C != 0) && isMovieActor() && (m_lod.m_flags & AILOD::FLAG_NEED_SHADOW)));
}

/*
 * --INFO--
 * Address:	80165B44
 * Size:	000008
 */
u8 Pellet::getWallTimer() { return m_wallTimer; }

/*
 * --INFO--
 * Address:	80165B4C
 * Size:	000034
 */
PelletViewArg::PelletViewArg()
{
	_18         = Vector3f(1.0f);
	m_enemy     = nullptr;
	m_matrix    = nullptr;
	m_position  = Vector3f(0.0f);
	m_enemyName = 0;
}

/*
 * --INFO--
 * Address:	80165B80
 * Size:	000220
 */
// WIP: https://decomp.me/scratch/a4K8T
// regswaps
Pellet* PelletView::becomePellet(PelletViewArg* viewArg)
{
	PelletInitArg initArg;
	initArg.m_textIdentifier = viewArg->m_enemyName;
	initArg._0C              = 0;
	initArg._10              = -1;
	initArg.m_pelletType     = PELTYPE_CARCASS;
	initArg._18              = this;

	Pellet* newPellet = pelletMgr->birth(&initArg);
	if (newPellet != nullptr) {
		Vector3f position = viewArg->m_position;
		position.y += 0.5f * newPellet->getCylinderHeight();

		PelletConfig* config = newPellet->m_config;
		Vector3f offset      = config->m_params.m_offset.m_data;

		Vector3f resultVec;
		Vector3f* vecPtr = &resultVec;
		*vecPtr          = offset;

		Vector3f row1;
		viewArg->m_matrix->getRow(0, row1);
		vecPtr->x = dot(offset, row1);
		Vector3f row2;
		viewArg->m_matrix->getRow(1, row2);
		vecPtr->y = dot(offset, row2);
		Vector3f row3;
		viewArg->m_matrix->getRow(2, row3);
		vecPtr->z = dot(offset, row3);
		position  = position + resultVec;

		newPellet->setPosition(position, false);
		m_pellet = newPellet;

		newPellet->_324 = 1;
		newPellet->setOrientation(*viewArg->m_matrix);
		newPellet->m_scale = viewArg->_18;
		newPellet->m_lod.m_flags |= (AILOD::VisibleOnViewport0 + AILOD::VisibleOnViewport1 + AILOD::FLAG_NEED_SHADOW);

		viewStartPreCarryMotion();

		m_creature = static_cast<Creature*>(viewArg->m_enemy);
		P2ASSERTLINE(895, m_creature != nullptr);
	} else {
		m_pellet   = nullptr;
		m_creature = nullptr;
	}

	return m_pellet;
	/*
	stwu     r1, -0x60(r1)
	mflr     r0
	lis      r6, __vt__Q24Game13PelletInitArg@ha
	lis      r5, __vt__Q24Game15CreatureInitArg@ha
	stw      r0, 0x64(r1)
	addi     r0, r5, __vt__Q24Game15CreatureInitArg@l
	addi     r8, r6, __vt__Q24Game13PelletInitArg@l
	li       r7, 0
	stw      r31, 0x5c(r1)
	li       r5, -1
	li       r6, 1
	mr       r31, r3
	stw      r30, 0x58(r1)
	stw      r29, 0x54(r1)
	mr       r29, r4
	addi     r4, r1, 0x20
	stw      r0, 0x20(r1)
	li       r0, 0xff
	lwz      r3, pelletMgr__4Game@sda21(r13)
	stw      r8, 0x20(r1)
	stb      r7, 0x3c(r1)
	sth      r7, 0x34(r1)
	stb      r0, 0x36(r1)
	stw      r7, 0x38(r1)
	stb      r7, 0x37(r1)
	stb      r6, 0x24(r1)
	stb      r7, 0x3d(r1)
	stw      r5, 0x44(r1)
	stw      r5, 0x40(r1)
	stb      r7, 0x3e(r1)
	stb      r7, 0x3f(r1)
	lwz      r0, 0(r29)
	stw      r0, 0x28(r1)
	stw      r7, 0x2c(r1)
	stw      r5, 0x30(r1)
	stb      r6, 0x36(r1)
	stw      r31, 0x38(r1)
	bl       birth__Q24Game9PelletMgrFPQ24Game13PelletInitArg
	or.      r30, r3, r3
	beq      lbl_80165D74
	lfs      f0, 4(r29)
	stfs     f0, 0x14(r1)
	lfs      f0, 8(r29)
	stfs     f0, 0x18(r1)
	lfs      f0, 0xc(r29)
	stfs     f0, 0x1c(r1)
	bl       getCylinderHeight__Q24Game6PelletFv
	lfs      f3, lbl_80518918@sda21(r2)
	mr       r3, r30
	lfs      f0, 0x18(r1)
	addi     r4, r1, 0x14
	lfs      f2, 0x1c(r1)
	li       r5, 0
	fmadds   f9, f3, f1, f0
	lfs      f0, 0x14(r1)
	stfs     f9, 0x18(r1)
	lwz      r7, 0x10(r29)
	lwz      r6, 0x35c(r30)
	lfs      f4, 4(r7)
	lfs      f10, 0x214(r6)
	lfs      f3, 0x14(r7)
	lfs      f1, 0x24(r7)
	fmuls    f6, f10, f4
	lfs      f8, 0x210(r6)
	fmuls    f4, f10, f3
	lfs      f7, 0(r7)
	fmuls    f1, f10, f1
	lfs      f5, 0x10(r7)
	lfs      f3, 0x20(r7)
	fmadds   f6, f8, f7, f6
	lfs      f11, 0x218(r6)
	fmadds   f4, f8, f5, f4
	lfs      f7, 8(r7)
	fmadds   f1, f8, f3, f1
	lfs      f5, 0x18(r7)
	lfs      f3, 0x28(r7)
	fmadds   f6, f11, f7, f6
	fmadds   f4, f11, f5, f4
	stfs     f8, 8(r1)
	fmadds   f1, f11, f3, f1
	fadds    f0, f0, f6
	stfs     f10, 0xc(r1)
	fadds    f3, f9, f4
	fadds    f2, f2, f1
	stfs     f11, 0x10(r1)
	stfs     f6, 8(r1)
	stfs     f4, 0xc(r1)
	stfs     f1, 0x10(r1)
	stfs     f0, 0x14(r1)
	stfs     f3, 0x18(r1)
	stfs     f2, 0x1c(r1)
	bl       "setPosition__Q24Game8CreatureFR10Vector3<f>b"
	stw      r30, 4(r31)
	li       r0, 1
	mr       r3, r30
	stb      r0, 0x324(r30)
	lwz      r4, 0x10(r29)
	bl       setOrientation__Q24Game6PelletFR7Matrixf
	lfs      f0, 0x18(r29)
	mr       r3, r31
	stfs     f0, 0x168(r30)
	lfs      f0, 0x1c(r29)
	stfs     f0, 0x16c(r30)
	lfs      f0, 0x20(r29)
	stfs     f0, 0x170(r30)
	lbz      r0, 0xd8(r30)
	ori      r0, r0, 0x34
	stb      r0, 0xd8(r30)
	lwz      r12, 0(r31)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r29)
	stw      r0, 8(r31)
	lwz      r0, 8(r31)
	cmplwi   r0, 0
	bne      lbl_80165D80
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x37f
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce
	b        lbl_80165D80

lbl_80165D74:
	li       r0, 0
	stw      r0, 4(r31)
	stw      r0, 8(r31)

lbl_80165D80:
	lwz      r0, 0x64(r1)
	lwz      r3, 4(r31)
	lwz      r31, 0x5c(r1)
	lwz      r30, 0x58(r1)
	lwz      r29, 0x54(r1)
	mtlr     r0
	addi     r1, r1, 0x60
	blr
	*/
}

/*
 * --INFO--
 * Address:	80165DA0
 * Size:	000084
 */
void PelletView::viewMakeMatrix(Matrixf& outMat)
{
	Vector3f translation(0.0f, -0.5f * m_pellet->getCylinderHeight(), 0.0f);
	Matrixf srtMatrix;
	srtMatrix.makeSRT(m_pellet->m_scale, Vector3f::zero, translation);
	PSMTXConcat(m_pellet->m_mainMatrix.m_matrix.mtxView, srtMatrix.m_matrix.mtxView, outMat.m_matrix.mtxView);
}

/*
 * --INFO--
 * Address:	80165E24
 * Size:	00000C
 */
void Pellet::clearClaim() { _3C0 = 0; }

/*
 * --INFO--
 * Address:	80165E30
 * Size:	000018
 */
void Pellet::sendClaim()
{
	if (_3C0 < 10) {
		_3C0++;
	}
}

/*
 * --INFO--
 * Address:	80165E48
 * Size:	0003F4
 */
// should match when Vector3f::length() matches: https://decomp.me/scratch/lHISE
void Pellet::updateClaim()
{
	if (_3C0 >= 10) {
		int count = 0;
		Vector3f meanPosition(0.0f);
		Stickers sticker(this);
		Iterator<Creature> iterator(&sticker);

		iterator.first();
		while (iterator.m_index != iterator.m_container->getEnd()) {
			meanPosition += iterator.m_container->get(iterator.m_index)->getPosition();
			count++;
			iterator.next();
		}

		if (count > 0) {
			float norm = 1.0f / count;
			meanPosition *= norm;
			Vector3f diff;
			Vector3f* diffPtr = &diff;
			*diffPtr          = meanPosition - m_pelletPosition;
			float len         = diff.length(); // should match when this inline matches

			if (len > 0.0f) {
				float vecNorm = 1.0f / len;
				diff.x *= vecNorm;
				diff.y *= vecNorm;
				diff.z *= vecNorm;
			} else {
				len = 0.0f;
			}

			diff.x *= 30.0f;
			diff.y *= 30.0f;
			diff.z *= 30.0f;

			Vector3f velocity    = getVelocity();
			Vector3f newVelocity = velocity;
			newVelocity += diff;
			setVelocity(newVelocity);
			_3C0 = 0;
		}
	}
	/*
	stwu     r1, -0xb0(r1)
	mflr     r0
	stw      r0, 0xb4(r1)
	stfd     f31, 0xa0(r1)
	psq_st   f31, 168(r1), 0, qr0
	stfd     f30, 0x90(r1)
	psq_st   f30, 152(r1), 0, qr0
	stfd     f29, 0x80(r1)
	psq_st   f29, 136(r1), 0, qr0
	stw      r31, 0x7c(r1)
	stw      r30, 0x78(r1)
	mr       r31, r3
	lwz      r0, 0x3c0(r3)
	cmpwi    r0, 0xa
	blt      lbl_8016620C
	lfs      f31, lbl_80518914@sda21(r2)
	mr       r4, r31
	addi     r3, r1, 0x48
	li       r30, 0
	fmr      f30, f31
	fmr      f29, f31
	bl       __ct__Q24Game8StickersFPQ24Game8Creature
	li       r0, 0
	lis      r3, "__vt__26Iterator<Q24Game8Creature>"@ha
	addi     r4, r3, "__vt__26Iterator<Q24Game8Creature>"@l
	addi     r3, r1, 0x48
	cmplwi   r0, 0
	stw      r4, 0x38(r1)
	stw      r0, 0x44(r1)
	stw      r0, 0x3c(r1)
	stw      r3, 0x40(r1)
	bne      lbl_80165EE0
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x3c(r1)
	b        lbl_80166070

lbl_80165EE0:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x3c(r1)
	b        lbl_80165F4C

lbl_80165EF8:
	lwz      r3, 0x40(r1)
	lwz      r4, 0x3c(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x44(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80166070
	lwz      r3, 0x40(r1)
	lwz      r4, 0x3c(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x3c(r1)

lbl_80165F4C:
	lwz      r12, 0x38(r1)
	addi     r3, r1, 0x38
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80165EF8
	b        lbl_80166070

lbl_80165F6C:
	lwz      r3, 0x40(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	addi     r3, r1, 0x14
	lwz      r12, 0(r4)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f2, 0x14(r1)
	addi     r30, r30, 1
	lfs      f1, 0x18(r1)
	lfs      f0, 0x1c(r1)
	fadds    f31, f31, f2
	lwz      r0, 0x44(r1)
	fadds    f30, f30, f1
	fadds    f29, f29, f0
	cmplwi   r0, 0
	bne      lbl_80165FE0
	lwz      r3, 0x40(r1)
	lwz      r4, 0x3c(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x3c(r1)
	b        lbl_80166070

lbl_80165FE0:
	lwz      r3, 0x40(r1)
	lwz      r4, 0x3c(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x3c(r1)
	b        lbl_80166054

lbl_80166000:
	lwz      r3, 0x40(r1)
	lwz      r4, 0x3c(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x44(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80166070
	lwz      r3, 0x40(r1)
	lwz      r4, 0x3c(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x3c(r1)

lbl_80166054:
	lwz      r12, 0x38(r1)
	addi     r3, r1, 0x38
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80166000

lbl_80166070:
	lwz      r3, 0x40(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0x3c(r1)
	cmplw    r4, r3
	bne      lbl_80165F6C
	cmpwi    r30, 0
	ble      lbl_80166200
	xoris    r3, r30, 0x8000
	lis      r0, 0x4330
	stw      r3, 0x6c(r1)
	lfd      f1, lbl_80518930@sda21(r2)
	stw      r0, 0x68(r1)
	lfs      f5, lbl_80518910@sda21(r2)
	lfd      f0, 0x68(r1)
	lfs      f3, 0x3b0(r31)
	fsubs    f2, f0, f1
	lfs      f0, 0x3ac(r31)
	lfs      f4, 0x3b4(r31)
	lfs      f1, lbl_80518914@sda21(r2)
	fdivs    f2, f5, f2
	fmuls    f31, f31, f2
	fmuls    f30, f30, f2
	fmuls    f29, f29, f2
	fsubs    f2, f31, f0
	fsubs    f3, f30, f3
	fsubs    f4, f29, f4
	fmuls    f0, f2, f2
	stfs     f2, 0x2c(r1)
	fmuls    f5, f3, f3
	fmuls    f6, f4, f4
	stfs     f3, 0x30(r1)
	fadds    f0, f0, f5
	stfs     f4, 0x34(r1)
	fadds    f0, f6, f0
	fcmpo    cr0, f0, f1
	ble      lbl_80166128
	fmadds   f0, f2, f2, f5
	fadds    f3, f6, f0
	fcmpo    cr0, f3, f1
	ble      lbl_8016612C
	frsqrte  f0, f3
	fmuls    f3, f0, f3
	b        lbl_8016612C

lbl_80166128:
	fmr      f3, f1

lbl_8016612C:
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f3, f0
	ble      lbl_80166164
	lfs      f0, lbl_80518910@sda21(r2)
	lfs      f2, 0x2c(r1)
	fdivs    f3, f0, f3
	lfs      f1, 0x30(r1)
	lfs      f0, 0x34(r1)
	fmuls    f2, f2, f3
	fmuls    f1, f1, f3
	fmuls    f0, f0, f3
	stfs     f2, 0x2c(r1)
	stfs     f1, 0x30(r1)
	stfs     f0, 0x34(r1)

lbl_80166164:
	mr       r4, r31
	lfs      f2, 0x2c(r1)
	lfs      f3, lbl_80518928@sda21(r2)
	addi     r3, r1, 8
	lfs      f1, 0x30(r1)
	lfs      f0, 0x34(r1)
	fmuls    f2, f2, f3
	lwz      r12, 0(r31)
	fmuls    f1, f1, f3
	fmuls    f0, f0, f3
	lwz      r12, 0x6c(r12)
	stfs     f2, 0x2c(r1)
	stfs     f1, 0x30(r1)
	stfs     f0, 0x34(r1)
	mtctr    r12
	bctrl
	lfs      f5, 8(r1)
	mr       r3, r31
	lfs      f4, 0xc(r1)
	addi     r4, r1, 0x20
	lfs      f3, 0x10(r1)
	lfs      f2, 0x2c(r1)
	lfs      f1, 0x30(r1)
	lfs      f0, 0x34(r1)
	fadds    f2, f5, f2
	stfs     f5, 0x20(r1)
	fadds    f1, f4, f1
	fadds    f0, f3, f0
	stfs     f4, 0x24(r1)
	stfs     f3, 0x28(r1)
	stfs     f2, 0x20(r1)
	stfs     f1, 0x24(r1)
	stfs     f0, 0x28(r1)
	lwz      r12, 0(r31)
	lwz      r12, 0x68(r12)
	mtctr    r12
	bctrl
	li       r0, 0
	stw      r0, 0x3c0(r31)

lbl_80166200:
	addi     r3, r1, 0x48
	li       r4, -1
	bl       __dt__Q24Game8StickersFv

lbl_8016620C:
	psq_l    f31, 168(r1), 0, qr0
	lfd      f31, 0xa0(r1)
	psq_l    f30, 152(r1), 0, qr0
	lfd      f30, 0x90(r1)
	psq_l    f29, 136(r1), 0, qr0
	lfd      f29, 0x80(r1)
	lwz      r31, 0x7c(r1)
	lwz      r0, 0xb4(r1)
	lwz      r30, 0x78(r1)
	mtlr     r0
	addi     r1, r1, 0xb0
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016623C
 * Size:	00000C
 */
float Pellet::getBuryDepthMax() { return m_config->m_params.m_depthMax.m_data; }

/*
 * --INFO--
 * Address:	80166248
 * Size:	00000C
 */
float Pellet::getBuryDepth() { return m_config->m_params.m_depth.m_data; }

/*
 * --INFO--
 * Address:	80166254
 * Size:	000124
 */
// WIP: https://decomp.me/scratch/HVCzF
void Pellet::getBuryRadius(float)
{
	/*
	stwu     r1, -0x50(r1)
	mflr     r0
	stw      r0, 0x54(r1)
	stfd     f31, 0x40(r1)
	psq_st   f31, 72(r1), 0, qr0
	stw      r31, 0x3c(r1)
	lfs      f4, lbl_80518938@sda21(r2)
	lis      r4, 0x4330
	lwz      r5, 0x35c(r3)
	lis      r3, lbl_8047E318@ha
	fmuls    f0, f4, f1
	addi     r11, r3, lbl_8047E318@l
	lwz      r10, 0x48(r11)
	li       r0, 0
	lwz      r9, 0x4c(r11)
	fctiwz   f0, f0
	lwz      r8, 0x50(r11)
	lwz      r7, 0x54(r11)
	stfd     f0, 0x20(r1)
	lwz      r6, 0x58(r11)
	lwz      r31, 0x24(r1)
	stw      r4, 0x28(r1)
	xoris    r3, r31, 0x8000
	lfd      f2, lbl_80518930@sda21(r2)
	stw      r3, 0x2c(r1)
	cmpwi    r31, 0
	lfs      f3, lbl_8051893C@sda21(r2)
	lfd      f0, 0x28(r1)
	stw      r10, 8(r1)
	fsubs    f0, f0, f2
	lfs      f6, 0x1d0(r5)
	stw      r9, 0xc(r1)
	lfs      f5, 0x1e0(r5)
	fmuls    f0, f3, f0
	stw      r8, 0x10(r1)
	lfs      f2, 0x1f0(r5)
	stw      r7, 0x14(r1)
	fsubs    f0, f1, f0
	lfs      f1, 0x200(r5)
	stw      r6, 0x18(r1)
	fmuls    f31, f4, f0
	stfs     f6, 8(r1)
	stfs     f5, 0xc(r1)
	stfs     f2, 0x10(r1)
	stfs     f1, 0x14(r1)
	stfs     f1, 0x18(r1)
	blt      lbl_8016631C
	cmpwi    r31, 4
	bgt      lbl_8016631C
	li       r0, 1

lbl_8016631C:
	clrlwi.  r0, r0, 0x18
	bne      lbl_80166338
	addi     r3, r11, 0x2c
	addi     r5, r11, 0x3c
	li       r4, 0x3ee
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80166338:
	slwi     r0, r31, 2
	addi     r3, r1, 0xc
	lfs      f1, lbl_80518910@sda21(r2)
	addi     r4, r1, 8
	lfsx     f0, r3, r0
	fsubs    f2, f1, f31
	lfsx     f1, r4, r0
	fmuls    f0, f31, f0
	fmadds   f1, f2, f1, f0
	psq_l    f31, 72(r1), 0, qr0
	lwz      r0, 0x54(r1)
	lfd      f31, 0x40(r1)
	lwz      r31, 0x3c(r1)
	mtlr     r0
	addi     r1, r1, 0x50
	blr
	*/
}

/*
 * --INFO--
 * Address:	80166378
 * Size:	000074
 */
bool Pellet::stimulate(Game::Interaction& interaction)
{
	if (interaction.actCommon(this)) {
		return interaction.actPellet(this);
	}
	return false;
}

/*
 * --INFO--
 * Address:	801663EC
 * Size:	000088
 */
bool InteractMattuan::actPellet(Pellet* pellet)
{
	if (pellet->getKind() == PELTYPE_UPGRADE) {
		pellet->startDiscoverDisable(_08 / sys->m_secondsPerFrame);
	} else {
		pellet->clearDiscoverDisable();
	}
	return true;
}

/*
 * --INFO--
 * Address:	80166474
 * Size:	000188
 */
bool InteractEat::actPellet(Pellet* pellet)
{
	if ((pellet->getKind() == PELTYPE_BERRY) && pellet->isAlive()) {
		// this is very dumb but also necessary to get a second vector on the stack??????
		Vector3f position = pellet->getPosition();
		Vector3f position2;
		Vector3f* posPtr = &position2;
		*posPtr          = position;

		efx::Arg arg(position2);

		// m_pelletColor apparently isn't just for onyon destination? maybe mislabeled.
		if (pellet->m_pelletColor == 0) {
			efx::TFruitsDownR spicy(0x65, 0x66);
			spicy.create(&arg);
		} else {
			efx::TFruitsDownP bitter(0x63, 0x64);
			bitter.create(&arg);
		}

		pellet->m_soundMgr->startSound(0x3842, 0);
		pellet->kill(nullptr);
		return true;
	}
	return false;
}

/*
 * --INFO--
 * Address:	801665FC
 * Size:	000080
 */
bool InteractSuck::actPellet(Game::Pellet* pellet)
{
	PelletGoalStateArg pelletGoalArg(m_creature);
	if (m_creature != nullptr) {
		m_creature->getTypeName();
	}
	pellet->m_pelletSM->transit(pellet, 7, &pelletGoalArg);
	pellet->finishDisplayCarryInfo();
	return true;
}

/*
 * --INFO--
 * Address:	8016667C
 * Size:	000004
 */
void Pellet::doDirectDraw(Graphics&) { }

/*
 * --INFO--
 * Address:	80166680
 * Size:	0001B0
 */
Pellet::Pellet()
    : _3D0(0)
    , _3E4(0)
    , _3E5(0)
    , _3E6(0)
    , _3E7(0)
    , _3E8(0)
    , _3E9(0)
    , _3EA(0)
    , _3EB(0)
    , _3EC(0)
    , _3ED(0)
    , _3EE(0)
    , _3EF(0)
    , _3F0(0)
    , _3F1(0)
    , _3F2(0)
    , _3F3(0)
{
	m_caster       = nullptr;
	m_model        = nullptr;
	m_objectTypeID = OBJTYPE_Pellet;
	m_collTree     = new CollTree;
	m_pelletSM     = new PelletFSM;
	m_pelletSM->init(this);
	m_collisionBuffer.alloc(this, 8);
	m_pelletColor = 4;
	m_pelletView  = nullptr;
	clearCarryColor();
	m_pelletCarry = new PelletCarry;
}

/*
 * --INFO--
 * Address:	80166830
 * Size:	00006C
 */
void Pellet::constructor() { m_soundMgr = new PSM::EventBase(this, 2); }

// namespace PSM {

// /*
//  * --INFO--
//  * Address:	8016689C
//  * Size:	00009C
//  */
// // WEAK - in header
// CreatureObj::~CreatureObj() { }

// } // namespace PSM

/*
 * --INFO--
 * Address:	80166938
 * Size:	000034
 */
void Pellet::shadowOn()
{
	if (shadowMgr != nullptr) {
		shadowMgr->addShadow(this);
	}
}

/*
 * --INFO--
 * Address:	8016696C
 * Size:	000034
 */
void Pellet::shadowOff()
{
	if (shadowMgr != nullptr) {
		shadowMgr->delShadow(this);
	}
}

/*
 * --INFO--
 * Address:	801669A0
 * Size:	000014
 */
JAInter::Object* Pellet::getJAIObject() { return m_soundMgr; }

/*
 * --INFO--
 * Address:	801669B4
 * Size:	000008
 */
PSM::Creature* Pellet::getPSCreature() { return m_soundMgr; }

/*
 * --INFO--
 * Address:	801669BC
 * Size:	00000C
 */
float Pellet::getBottomRadius() { return m_config->m_params.m_radius.m_data; }

/*
 * --INFO--
 * Address:	801669C8
 * Size:	00000C
 */
float Pellet::getPickRadius() { return m_config->m_params.m_pRadius.m_data; }

/*
 * --INFO--
 * Address:	801669D4
 * Size:	00000C
 */
float Pellet::getCylinderHeight() { return m_config->m_params.m_height.m_data; }

/*
 * --INFO--
 * Address:	801669E0
 * Size:	000058
 */
s16 Pellet::getConfigIndex()
{
	P2ASSERTLINE(1433, m_config != nullptr);
	return m_config->m_params.m_index;
}

/*
 * --INFO--
 * Address:	80166A38
 * Size:	00000C
 */
char* Pellet::getConfigName() { return m_config->m_params.m_name.m_data; }

/*
 * --INFO--
 * Address:	80166A44
 * Size:	000130
 */
PelletIndexInitArg::PelletIndexInitArg(int idx)
{
	int code;
	pelletMgr->decode(idx, m_pelletType, code);

	BasePelletMgr* newPelletMgr = pelletMgr->getMgrByID(m_pelletType);
	P2ASSERTLINE(1465, newPelletMgr != nullptr);
	PelletConfig* config = newPelletMgr->getPelletConfig(code);

	m_textIdentifier = config->m_params.m_name.m_data;
	_10              = code;
	_0C              = (int)(3.0f * randFloat());
}

/*
 * --INFO--
 * Address:	80166B74
 * Size:	0000F0
 */
PelletNumberInitArg::PelletNumberInitArg(int p1, int p2)
{
	switch (p1) {
	case 1:
		m_textIdentifier = "number1";
		_10              = 0;
		break;
	case 5:
		m_textIdentifier = "number5";
		_10              = 1;
		break;
	case 10:
		m_textIdentifier = "number10";
		_10              = 2;
		break;
	case 20:
		m_textIdentifier = "number20";
		_10              = 3;
		break;
	default:
		m_textIdentifier = "number1";
		_10              = 0;
		break;
	}

	_0C          = p2;
	m_pelletType = 0;
}

/*
 * --INFO--
 * Address:	80166C64
 * Size:	000040
 */
bool Pellet::isPickable()
{
	if (m_pelletState != nullptr) {
		return m_pelletState->isPickable();
	}
	return false;
}

// /*
//  * --INFO--
//  * Address:	80166CA4
//  * Size:	000008
//  */
// // WEAK - in header
// bool PelletState::isPickable() { return false; }

/*
 * --INFO--
 * Address:	80166CAC
 * Size:	000288
 */
void Pellet::onKill(CreatureKillArg* killArg)
{
	if (gameSystem->m_mode == GSM_VERSUS_MODE) {
		m_pelletSM->start(this, 0, nullptr);
	}

	setAlive(false);

	if (shadowMgr != nullptr) {
		shadowMgr->delShadow(this);
	}

	if (gameSystem->m_mode == GSM_VERSUS_MODE) {
		GameMessagePelletDead msg(this);
		gameSystem->m_section->sendMessage(msg);
	}

	Vector3f scale(1.0f);
	Vector3f rotation(0.0f);
	Vector3f translation(0.0f);
	m_mainMatrix.makeSRT(scale, rotation, translation);

	if (m_model != nullptr) {
		m_lodSphere.m_position = Vector3f(0.0f);
		m_lodSphere.m_radius   = 128000.0f;
		m_scale                = Vector3f(1.0f);
		PSMTXCopy(m_mainMatrix.m_matrix.mtxView, m_model->m_j3dModel->_24);
		m_scale.setTVec(m_model->m_j3dModel->m_modelScale);
		m_model->clearAnimatorAll();
		m_model->m_j3dModel->calc();
	}

	releaseParticles();
	m_collTree->release();
	m_mgr->kill(this);

	if (((killArg != nullptr) && (static_cast<PelletKillArg*>(killArg)->_08 != 0))
	    || ((gameSystem->m_mode == GSM_VERSUS_MODE) && (_32C == 3))) {
		m_mgr->setRevival(this);
	}

	finishDisplayCarryInfo();

	if (m_pelletView != nullptr) {
		m_pelletView->viewOnPelletKilled();
		m_pelletView->m_pellet = nullptr;
		m_pelletView           = nullptr;
	}

	if (getKind() == PELTYPE_TREASURE || getKind() == PELTYPE_UPGRADE) {
		Radar::Mgr::exit(this);
	}
}

/*
 * --INFO--
 * Address:	80166F34
 * Size:	000034
 */
void start__Q24Game28StateMachine<Game::Pellet> FPQ24Game6PelletiPQ24Game8StateArg(void)
{
	/*
	.loc_0x0:
	  stwu      r1, -0x10(r1)
	  mflr      r0
	  stw       r0, 0x14(r1)
	  li        r0, 0
	  stw       r0, 0x3CC(r4)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x14(r12)
	  mtctr     r12
	  bctrl
	  lwz       r0, 0x14(r1)
	  mtlr      r0
	  addi      r1, r1, 0x10
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80166F68
 * Size:	000620
 */
void Pellet::onInit(Game::CreatureInitArg* initArg) 
{
    _3DC = -1;
    _3D8 = -1;
    m_wallTimer = 0;
    _324 = 0;
    m_isInWater = false;

    clearDiscoverDisable();

    _3C0 = 0;
    _3E0 = 0.0f;
    _0C8 = nullptr;
    _311 = 0;
    m_faceDir = 0.0f;
    _438 = 0.0f;
    _3C4 = 0;
    _3D0 = 0;
    m_carryInfoMgr = nullptr;

    clearCapture();

    _418 = 0.0f;

    P2ASSERTLINE(1632, initArg != nullptr);

    u16 stateType = static_cast<PelletInitArg*>(initArg)->_14;
    if (stateType == 0) {
        m_pelletSM->start(this, 0, nullptr);
        m_scale = Vector3f(1.0f);        
    } else if (stateType == 3) {
        m_pelletSM->start(this, 6, nullptr);        
    } else if (stateType == 1) {
        m_pelletSM->start(this, 4, nullptr);
        m_scale = Vector3f(0.01f);        
    } else {
        m_pelletSM->start(this, 5, nullptr);
        m_scale = Vector3f(0.01f);       
    }

    _3F8 = 0;
    _3FC = 0;
    _400 = 0;
    _404 = 0;
    _408 = 0;
    _40C = 0;
    _410 = 0;
    _414 = 0;
    _43C = (u16) static_cast<PelletInitArg*>(initArg)->_10;

    m_config = m_mgr->m_configList->getPelletConfig(static_cast<PelletInitArg*>(initArg)->m_textIdentifier);
    
    if (!(m_config->m_params.m_code.m_data & 1)) {
        shadowOn();
    }
    
    if (static_cast<PelletInitArg*>(initArg)->_1D != 0) {
        _3D8 = GameStat::getMapPikmins(-1);
        int minPikis = m_config->m_params.m_min.m_data;
        if (_3D8 > minPikis) {
            _3D8 = minPikis;
        }
    } else {
        _3D8 = -1;
    }

    
    // temp_r3_6 = arg0->unk20;
    if ((static_cast<PelletInitArg*>(initArg)->m_minCarriers != -1) && (static_cast<PelletInitArg*>(initArg)->m_maxCarriers != -1)) {
        _3D8 = static_cast<PelletInitArg*>(initArg)->m_minCarriers;
        _3DC = static_cast<PelletInitArg*>(initArg)->m_maxCarriers;
    }

    
    m_rigid._175 &= ~0x01;
    m_rigid._175 &= ~0x80;
    m_pelletColor = static_cast<PelletInitArg*>(initArg)->_0C;
    
    if (strcmp(m_config->m_params.m_name.m_data, "loozy") == 0) {
        _32C = 0;
    } else if (strcmp(m_config->m_params.m_name.m_data, "orima") == 0) {
        _32C = 1;
    } else {
        _32C = 2;
    }
    
    if (strcmp(m_config->m_params.m_name.m_data, VsOtakaraName::cBedamaYellow) == 0) {
        _32C = 6;
    } else if (strcmp(m_config->m_params.m_name.m_data, VsOtakaraName::cBedamaRed) == 0) {
        _32C = 4;
    } else if (strcmp(m_config->m_params.m_name.m_data, VsOtakaraName::cBedamaBlue) == 0) {
        _32C = 5;
    } else if (strcmp(m_config->m_params.m_name.m_data, VsOtakaraName::cCoin) == 0) {
        _32C = 3;
    }
    
    if (static_cast<PelletInitArg*>(initArg)->_1C == 0) {
        m_model = m_mgr->createShape(_43C, m_slotIndex);
        onCreateShape();
    }
    
    if (m_model != nullptr) {
        _41C.m_animMgr = m_mgr->m_animMgr[_43C];
        m_radius = 2.0f * m_model->getRoughBoundingRadius();
    } else {
        m_radius = m_config->m_params.m_radius.m_data;
    }
    
    if (_41C.m_animMgr != nullptr) {
        SysShape::MotionListener* listener = this;
        _41C.startAnim(0, listener);
        stop_carrymotion();
        init_pmotions();
        start_pmotions();
        if ((gameSystem->m_mode == GSM_PIKLOPEDIA) && (_32C == 0)) {
            _438 = 30.0f;
        }
    }

    m_mgr->setCollTree(this, _43C);

    if (strcmp(m_config->m_params.m_dynamics.m_data, "never") == 0) {
        _364 = 2;
        _39C = 0;
        m_config->m_params.m_numParticles.m_data = 0;
    } else if (strcmp(m_config->m_params.m_dynamics.m_data, "lod") == 0) {
        _364 = 1;
        _39C = 1;
    } else {
        _364 = 0;
        _39C = 1;
    }
    
    _3E4 = 0;
    _3E5 = 0;
    _3E6 = 0;
    _3E7 = 0;
    _3E8 = 0;
    _3E9 = 0;
    _3EA = 0;
    _3EB = 0;
    _3EC = 0;
    _3ED = 0;
    _3EE = 0;
    _3EF = 0;
    _3F0 = 0;
    _3F1 = 0;
    _3F2 = 0;
    _3F3 = 0;
    _3F6 = 0;
    
    _3F4 = getPelletConfigMax();
    
    if (_3F4 > 128) {
        _3F4 = 128;
    }
    
    if (m_config->m_params.m_min.m_data == 128) {
        _3D8 = 1000;
        _3DC = 1000;
    }
    
    m_dynParticle = nullptr;
    setupParticles();
    do_onInit(initArg);

    if (getKind() == PELTYPE_TREASURE) {
        Radar::Mgr::entry(this, Radar::MAP_TREASURE, 0);
    } else if (getKind() == PELTYPE_UPGRADE) {
        Radar::Mgr::entry(this, Radar::MAP_UPGRADE, 0);
    }
    
    setAlive(true);

    if (gameSystem->m_mode == GSM_VERSUS_MODE) {
        GameMessagePelletBorn msg (this);
        gameSystem->m_section->sendMessage(msg);
    }
}

/*
 * --INFO--
 * Address:	80167588
 * Size:	000004
 */
// WEAK - in header
// void Pellet::do_onInit(CreatureInitArg*) { }

/*
 * --INFO--
 * Address:	8016758C
 * Size:	000004
 */
// WEAK - in header
// void Pellet::onCreateShape() { }

/*
 * --INFO--
 * Address:	80167590
 * Size:	000020
 */
void Pellet::getPelletConfigMin(void)
{
	/*
	lwz      r0, 0x3d8(r3)
	cmpwi    r0, 0
	ble      lbl_801675A4
	mr       r3, r0
	blr

lbl_801675A4:
	lwz      r3, 0x35c(r3)
	lwz      r3, 0x120(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801675B0
 * Size:	000020
 */
void Pellet::getPelletConfigMax(void)
{
	/*
	lwz      r0, 0x3dc(r3)
	cmpwi    r0, 0
	ble      lbl_801675C4
	mr       r3, r0
	blr

lbl_801675C4:
	lwz      r3, 0x35c(r3)
	lwz      r3, 0x130(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801675D0
 * Size:	000354
 */
void Pellet::setupParticles(void)
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
	stfd     f23, 0x50(r1)
	psq_st   f23, 88(r1), 0, qr0
	stmw     r26, 0x38(r1)
	mr       r27, r3
	lfs      f0, lbl_80518914@sda21(r2)
	lwz      r3, 0x35c(r3)
	lfs      f25, 0xa0(r3)
	stfs     f0, 0x2f4(r27)
	stfs     f0, 0x2f8(r27)
	stfs     f0, 0x2fc(r27)
	lwz      r3, 0x35c(r27)
	lwz      r0, 0xf0(r3)
	stw      r0, 0x360(r27)
	lwz      r0, 0x360(r27)
	cmpwi    r0, 0
	beq      lbl_801678C8
	lwz      r4, 0x35c(r27)
	addi     r3, r2, lbl_80518980@sda21
	lwz      r4, 0xe0(r4)
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_801676AC
	lwz      r3, 0x35c(r27)
	lfs      f1, lbl_80518918@sda21(r2)
	lfs      f0, 0xc0(r3)
	lfs      f2, lbl_80518970@sda21(r2)
	fmuls    f0, f1, f0
	fmuls    f0, f2, f0
	fcmpo    cr0, f0, f25
	ble      lbl_801676A0
	mr       r3, r27
	bl       setupParticles_tall__Q24Game6PelletFv
	b        lbl_8016787C

lbl_801676A0:
	mr       r3, r27
	bl       setupParticles_simple__Q24Game6PelletFv
	b        lbl_8016787C

lbl_801676AC:
	li       r3, 0
	li       r0, 1
	stb      r3, 0x364(r27)
	mr       r3, r27
	stb      r0, 0x39c(r27)
	lwz      r29, 0x360(r27)
	addi     r0, r29, 1
	stw      r0, 0x360(r27)
	lwz      r4, 0x360(r27)
	bl       createParticles__Q24Game11DynCreatureFi
	lis      r3, sincosTable___5JMath@ha
	lfs      f27, lbl_80518988@sda21(r2)
	lfd      f28, lbl_80518930@sda21(r2)
	xoris    r30, r29, 0x8000
	lfs      f29, lbl_80518918@sda21(r2)
	addi     r26, r3, sincosTable___5JMath@l
	lfs      f30, lbl_80518914@sda21(r2)
	li       r28, 0
	lfs      f31, lbl_8051898C@sda21(r2)
	lis      r31, 0x4330
	b        lbl_80167814

lbl_80167700:
	stw      r30, 0xc(r1)
	xoris    r0, r28, 0x8000
	lwz      r3, 0x35c(r27)
	stw      r31, 8(r1)
	lfs      f0, 0xc0(r3)
	lfd      f1, 8(r1)
	fmuls    f24, f29, f0
	stw      r0, 0x14(r1)
	fsubs    f0, f1, f28
	stw      r31, 0x10(r1)
	fsubs    f2, f25, f24
	fdivs    f1, f27, f0
	lfd      f0, 0x10(r1)
	fsubs    f0, f0, f28
	fmuls    f1, f1, f0
	fmr      f0, f1
	fcmpo    cr0, f1, f30
	bge      lbl_8016774C
	fneg     f0, f1

lbl_8016774C:
	fmuls    f0, f0, f31
	fcmpo    cr0, f1, f30
	fctiwz   f0, f0
	stfd     f0, 0x18(r1)
	lwz      r0, 0x1c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r26, r0
	lfs      f0, 4(r3)
	fmuls    f26, f2, f0
	bge      lbl_801677A0
	lfs      f0, lbl_80518990@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f1, f0
	fctiwz   f0, f0
	stfd     f0, 0x20(r1)
	lwz      r0, 0x24(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0
	fneg     f0, f0
	b        lbl_801677C0

lbl_801677A0:
	fmuls    f0, f1, f31
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fctiwz   f0, f0
	stfd     f0, 0x28(r1)
	lwz      r0, 0x2c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0

lbl_801677C0:
	fmuls    f23, f2, f0
	lfs      f0, 0x2f4(r27)
	lfs      f1, 0x2f8(r27)
	mr       r4, r28
	lfs      f2, 0x2fc(r27)
	fadds    f0, f0, f23
	fadds    f1, f1, f30
	fadds    f2, f2, f26
	stfs     f0, 0x2f4(r27)
	stfs     f1, 0x2f8(r27)
	stfs     f2, 0x2fc(r27)
	lwz      r3, 0x178(r27)
	bl       getAt__Q24Game11DynParticleFi
	stfs     f23, 0(r3)
	mr       r4, r28
	stfs     f30, 4(r3)
	stfs     f26, 8(r3)
	lwz      r3, 0x178(r27)
	bl       getAt__Q24Game11DynParticleFi
	stfs     f24, 0x18(r3)
	addi     r28, r28, 1

lbl_80167814:
	cmpw     r28, r29
	blt      lbl_80167700
	lfs      f25, lbl_80518914@sda21(r2)
	mr       r4, r29
	lfs      f0, 0x2f4(r27)
	lwz      r3, 0x35c(r27)
	lfs      f1, 0x2f8(r27)
	fadds    f0, f0, f25
	lfs      f2, 0x2fc(r27)
	lfs      f23, 0xc0(r3)
	fadds    f1, f1, f25
	fadds    f2, f2, f25
	lfs      f24, lbl_80518918@sda21(r2)
	stfs     f0, 0x2f4(r27)
	stfs     f1, 0x2f8(r27)
	stfs     f2, 0x2fc(r27)
	lwz      r3, 0x178(r27)
	bl       getAt__Q24Game11DynParticleFi
	stfs     f25, 0(r3)
	fmuls    f24, f24, f23
	mr       r4, r29
	stfs     f25, 4(r3)
	stfs     f25, 8(r3)
	lwz      r3, 0x178(r27)
	bl       getAt__Q24Game11DynParticleFi
	stfs     f24, 0x18(r3)

lbl_8016787C:
	lwz      r3, 0x360(r27)
	lis      r0, 0x4330
	stw      r0, 0x28(r1)
	xoris    r0, r3, 0x8000
	lfd      f2, lbl_80518930@sda21(r2)
	stw      r0, 0x2c(r1)
	lfs      f4, lbl_80518910@sda21(r2)
	lfd      f1, 0x28(r1)
	lfs      f0, 0x2f4(r27)
	fsubs    f3, f1, f2
	lfs      f1, 0x2f8(r27)
	lfs      f2, 0x2fc(r27)
	fdivs    f3, f4, f3
	fmuls    f0, f0, f3
	fmuls    f1, f1, f3
	fmuls    f2, f2, f3
	stfs     f0, 0x2f4(r27)
	stfs     f1, 0x2f8(r27)
	stfs     f2, 0x2fc(r27)

lbl_801678C8:
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
	psq_l    f23, 88(r1), 0, qr0
	lfd      f23, 0x50(r1)
	lmw      r26, 0x38(r1)
	lwz      r0, 0xe4(r1)
	mtlr     r0
	addi     r1, r1, 0xe0
	blr
	*/
}

/*
 * --INFO--
 * Address:	80167924
 * Size:	000220
 */
void Pellet::setupParticles_simple(void)
{
	/*
	stwu     r1, -0xc0(r1)
	mflr     r0
	stw      r0, 0xc4(r1)
	stfd     f31, 0xb0(r1)
	psq_st   f31, 184(r1), 0, qr0
	stfd     f30, 0xa0(r1)
	psq_st   f30, 168(r1), 0, qr0
	stfd     f29, 0x90(r1)
	psq_st   f29, 152(r1), 0, qr0
	stfd     f28, 0x80(r1)
	psq_st   f28, 136(r1), 0, qr0
	stfd     f27, 0x70(r1)
	psq_st   f27, 120(r1), 0, qr0
	stfd     f26, 0x60(r1)
	psq_st   f26, 104(r1), 0, qr0
	stfd     f25, 0x50(r1)
	psq_st   f25, 88(r1), 0, qr0
	stfd     f24, 0x40(r1)
	psq_st   f24, 72(r1), 0, qr0
	stw      r31, 0x3c(r1)
	stw      r30, 0x38(r1)
	stw      r29, 0x34(r1)
	stw      r28, 0x30(r1)
	mr       r29, r3
	lwz      r5, 0x35c(r3)
	lwz      r4, 0x360(r3)
	lfs      f24, 0xa0(r5)
	bl       createParticles__Q24Game11DynCreatureFi
	lwz      r0, 0x360(r29)
	lis      r31, 0x4330
	lwz      r4, 0x35c(r29)
	lis      r3, sincosTable___5JMath@ha
	xoris    r0, r0, 0x8000
	stw      r31, 8(r1)
	lfd      f29, lbl_80518930@sda21(r2)
	addi     r28, r3, sincosTable___5JMath@l
	stw      r0, 0xc(r1)
	li       r30, 0
	lfs      f3, lbl_80518988@sda21(r2)
	lfd      f0, 8(r1)
	lfs      f1, lbl_80518918@sda21(r2)
	fsubs    f2, f0, f29
	lfs      f0, 0xc0(r4)
	lfs      f30, lbl_80518914@sda21(r2)
	fmuls    f25, f1, f0
	lfs      f31, lbl_8051898C@sda21(r2)
	fdivs    f26, f3, f2
	fsubs    f27, f24, f25
	b        lbl_80167AD8

lbl_801679E8:
	xoris    r0, r30, 0x8000
	stw      r31, 8(r1)
	stw      r0, 0xc(r1)
	lfd      f0, 8(r1)
	fsubs    f0, f0, f29
	fmuls    f1, f26, f0
	fmr      f0, f1
	fcmpo    cr0, f1, f30
	bge      lbl_80167A10
	fneg     f0, f1

lbl_80167A10:
	fmuls    f0, f0, f31
	fcmpo    cr0, f1, f30
	fctiwz   f0, f0
	stfd     f0, 0x10(r1)
	lwz      r0, 0x14(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r28, r0
	lfs      f0, 4(r3)
	fmuls    f28, f27, f0
	bge      lbl_80167A64
	lfs      f0, lbl_80518990@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f1, f0
	fctiwz   f0, f0
	stfd     f0, 0x18(r1)
	lwz      r0, 0x1c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0
	fneg     f0, f0
	b        lbl_80167A84

lbl_80167A64:
	fmuls    f0, f1, f31
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fctiwz   f0, f0
	stfd     f0, 0x20(r1)
	lwz      r0, 0x24(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0

lbl_80167A84:
	fmuls    f24, f27, f0
	lfs      f0, 0x2f4(r29)
	lfs      f1, 0x2f8(r29)
	mr       r4, r30
	lfs      f2, 0x2fc(r29)
	fadds    f0, f0, f24
	fadds    f1, f1, f30
	fadds    f2, f2, f28
	stfs     f0, 0x2f4(r29)
	stfs     f1, 0x2f8(r29)
	stfs     f2, 0x2fc(r29)
	lwz      r3, 0x178(r29)
	bl       getAt__Q24Game11DynParticleFi
	stfs     f24, 0(r3)
	mr       r4, r30
	stfs     f30, 4(r3)
	stfs     f28, 8(r3)
	lwz      r3, 0x178(r29)
	bl       getAt__Q24Game11DynParticleFi
	stfs     f25, 0x18(r3)
	addi     r30, r30, 1

lbl_80167AD8:
	lwz      r0, 0x360(r29)
	cmpw     r30, r0
	blt      lbl_801679E8
	psq_l    f31, 184(r1), 0, qr0
	lfd      f31, 0xb0(r1)
	psq_l    f30, 168(r1), 0, qr0
	lfd      f30, 0xa0(r1)
	psq_l    f29, 152(r1), 0, qr0
	lfd      f29, 0x90(r1)
	psq_l    f28, 136(r1), 0, qr0
	lfd      f28, 0x80(r1)
	psq_l    f27, 120(r1), 0, qr0
	lfd      f27, 0x70(r1)
	psq_l    f26, 104(r1), 0, qr0
	lfd      f26, 0x60(r1)
	psq_l    f25, 88(r1), 0, qr0
	lfd      f25, 0x50(r1)
	psq_l    f24, 72(r1), 0, qr0
	lfd      f24, 0x40(r1)
	lwz      r31, 0x3c(r1)
	lwz      r30, 0x38(r1)
	lwz      r29, 0x34(r1)
	lwz      r0, 0xc4(r1)
	lwz      r28, 0x30(r1)
	mtlr     r0
	addi     r1, r1, 0xc0
	blr
	*/
}

/*
 * --INFO--
 * Address:	80167B44
 * Size:	000230
 */
void Pellet::setupParticles_tall(void)
{
	/*
	stwu     r1, -0xd0(r1)
	mflr     r0
	stw      r0, 0xd4(r1)
	stfd     f31, 0xc0(r1)
	psq_st   f31, 200(r1), 0, qr0
	stfd     f30, 0xb0(r1)
	psq_st   f30, 184(r1), 0, qr0
	stfd     f29, 0xa0(r1)
	psq_st   f29, 168(r1), 0, qr0
	stfd     f28, 0x90(r1)
	psq_st   f28, 152(r1), 0, qr0
	stfd     f27, 0x80(r1)
	psq_st   f27, 136(r1), 0, qr0
	stfd     f26, 0x70(r1)
	psq_st   f26, 120(r1), 0, qr0
	stfd     f25, 0x60(r1)
	psq_st   f25, 104(r1), 0, qr0
	stfd     f24, 0x50(r1)
	psq_st   f24, 88(r1), 0, qr0
	stfd     f23, 0x40(r1)
	psq_st   f23, 72(r1), 0, qr0
	stmw     r27, 0x2c(r1)
	mr       r30, r3
	lfs      f1, lbl_80518918@sda21(r2)
	lwz      r3, 0x35c(r3)
	lfs      f0, lbl_80518994@sda21(r2)
	lfs      f2, 0xc0(r3)
	lfs      f23, 0xa0(r3)
	fmuls    f24, f1, f2
	fmr      f25, f24
	fcmpo    cr0, f24, f0
	ble      lbl_80167BC8
	fmr      f25, f0

lbl_80167BC8:
	lwz      r31, 0x360(r30)
	mr       r3, r30
	mr       r4, r31
	bl       createParticles__Q24Game11DynCreatureFi
	xoris    r0, r31, 0x8000
	lis      r28, 0x4330
	stw      r0, 0xc(r1)
	fsubs    f0, f24, f25
	lis      r3, sincosTable___5JMath@ha
	lfd      f29, lbl_80518930@sda21(r2)
	stw      r28, 8(r1)
	fsubs    f27, f23, f25
	lfs      f2, lbl_80518988@sda21(r2)
	lfd      f1, 8(r1)
	fneg     f26, f0
	lfs      f30, lbl_80518914@sda21(r2)
	addi     r29, r3, sincosTable___5JMath@l
	fsubs    f0, f1, f29
	lfs      f31, lbl_8051898C@sda21(r2)
	li       r27, 0
	fdivs    f24, f2, f0
	b        lbl_80167D10

lbl_80167C20:
	xoris    r0, r27, 0x8000
	stw      r28, 8(r1)
	stw      r0, 0xc(r1)
	lfd      f0, 8(r1)
	fsubs    f0, f0, f29
	fmuls    f1, f24, f0
	fmr      f0, f1
	fcmpo    cr0, f1, f30
	bge      lbl_80167C48
	fneg     f0, f1

lbl_80167C48:
	fmuls    f0, f0, f31
	fcmpo    cr0, f1, f30
	fctiwz   f0, f0
	stfd     f0, 0x10(r1)
	lwz      r0, 0x14(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r29, r0
	lfs      f0, 4(r3)
	fmuls    f28, f27, f0
	bge      lbl_80167C9C
	lfs      f0, lbl_80518990@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f1, f0
	fctiwz   f0, f0
	stfd     f0, 0x18(r1)
	lwz      r0, 0x1c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0
	fneg     f0, f0
	b        lbl_80167CBC

lbl_80167C9C:
	fmuls    f0, f1, f31
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fctiwz   f0, f0
	stfd     f0, 0x20(r1)
	lwz      r0, 0x24(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0

lbl_80167CBC:
	fmuls    f23, f27, f0
	lfs      f0, 0x2f4(r30)
	lfs      f1, 0x2f8(r30)
	mr       r4, r27
	lfs      f2, 0x2fc(r30)
	fadds    f0, f0, f23
	fadds    f1, f1, f26
	fadds    f2, f2, f28
	stfs     f0, 0x2f4(r30)
	stfs     f1, 0x2f8(r30)
	stfs     f2, 0x2fc(r30)
	lwz      r3, 0x178(r30)
	bl       getAt__Q24Game11DynParticleFi
	stfs     f23, 0(r3)
	mr       r4, r27
	stfs     f26, 4(r3)
	stfs     f28, 8(r3)
	lwz      r3, 0x178(r30)
	bl       getAt__Q24Game11DynParticleFi
	stfs     f25, 0x18(r3)
	addi     r27, r27, 1

lbl_80167D10:
	cmpw     r27, r31
	blt      lbl_80167C20
	psq_l    f31, 200(r1), 0, qr0
	lfd      f31, 0xc0(r1)
	psq_l    f30, 184(r1), 0, qr0
	lfd      f30, 0xb0(r1)
	psq_l    f29, 168(r1), 0, qr0
	lfd      f29, 0xa0(r1)
	psq_l    f28, 152(r1), 0, qr0
	lfd      f28, 0x90(r1)
	psq_l    f27, 136(r1), 0, qr0
	lfd      f27, 0x80(r1)
	psq_l    f26, 120(r1), 0, qr0
	lfd      f26, 0x70(r1)
	psq_l    f25, 104(r1), 0, qr0
	lfd      f25, 0x60(r1)
	psq_l    f24, 88(r1), 0, qr0
	lfd      f24, 0x50(r1)
	psq_l    f23, 72(r1), 0, qr0
	lfd      f23, 0x40(r1)
	lmw      r27, 0x2c(r1)
	lwz      r0, 0xd4(r1)
	mtlr     r0
	addi     r1, r1, 0xd0
	blr
	*/
}

/*
 * --INFO--
 * Address:	80167D74
 * Size:	000018
 */
bool Pellet::panmodokiCarryable() { return !(m_config->m_params.m_code.m_data & 1); }

/*
 * --INFO--
 * Address:	80167D8C
 * Size:	00004C
 */
bool Pellet::isCarried()
{
	if (_3F6 || isPicked()) {
		return true;
	}
	return false;
}

/*
 * --INFO--
 * Address:	80167DD8
 * Size:	00000C
 */
void Pellet::isPicked(void)
{
	/*
	lbz      r0, 0x3d0(r3)
	clrlwi   r3, r0, 0x1f
	blr
	*/
}

/*
 * --INFO--
 * Address:	80167DE4
 * Size:	000044
 */
void Pellet::finishDisplayCarryInfo()
{
	if (m_carryInfoMgr != nullptr) {
		m_carryInfoMgr->m_activeList.m_param.m_carryInfo.disappear();
		m_carryInfoMgr = nullptr;
	}
}

/*
 * --INFO--
 * Address:	80167E28
 * Size:	0000A0
 */
void Pellet::getCarryInfoParam(CarryInfoParam&)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	lfs      f1, lbl_80518928@sda21(r2)
	stw      r0, 0x14(r1)
	li       r0, 0
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	mr       r30, r3
	stw      r0, 0(r4)
	li       r0, 1
	lfs      f0, 0x1b0(r3)
	stfs     f0, 4(r4)
	lfs      f0, 0x1b4(r3)
	stfs     f0, 8(r4)
	lfs      f0, 0x1b8(r3)
	stfs     f0, 0xc(r4)
	lwz      r4, 0x35c(r3)
	lfs      f0, 0xc0(r4)
	fadds    f0, f1, f0
	stfs     f0, 0x10(r31)
	stb      r0, 0x14(r31)
	stw      r0, 0x1c(r31)
	bl       getTotalCarryPikmins__Q24Game6PelletFv
	sth      r3, 0x18(r31)
	lwz      r0, 0x3d8(r30)
	cmpwi    r0, 0
	ble      lbl_80167E9C
	b        lbl_80167EA4

lbl_80167E9C:
	lwz      r3, 0x35c(r30)
	lwz      r0, 0x120(r3)

lbl_80167EA4:
	sth      r0, 0x16(r31)
	lwz      r0, 0x3d4(r30)
	stb      r0, 0x15(r31)
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
 * Address:	80167EC8
 * Size:	000068
 */
void Pellet::setCarryColor(int color)
{
	if ((gameSystem->m_mode == GSM_VERSUS_MODE) && (color != m_carryColor)) {
		m_carryColor = color;
		sound_otakaraEventStart();
	}
	m_carryColor = color;
}

/*
 * --INFO--
 * Address:	80167F30
 * Size:	000004
 */
// WEAK - in header
// void Pellet::sound_otakaraEventStart() { }

/*
 * --INFO--
 * Address:	80167F34
 * Size:	00000C
 */
void Pellet::clearCarryColor() { m_carryColor = 5; }

/*
 * --INFO--
 * Address:	80167F40
 * Size:	00001C
 */
void Pellet::getVelocity(void)
{
	/*
	lfs      f0, 0x1bc(r4)
	stfs     f0, 0(r3)
	lfs      f0, 0x1c0(r4)
	stfs     f0, 4(r3)
	lfs      f0, 0x1c4(r4)
	stfs     f0, 8(r3)
	blr
	*/
}

} // namespace Game

/*
 * --INFO--
 * Address:	80167F5C
 * Size:	00001C
 */
void setVelocity__Q24Game6PelletFR10Vector3f(void)
{
	/*
	lfs      f0, 0(r4)
	stfs     f0, 0x1bc(r3)
	lfs      f0, 4(r4)
	stfs     f0, 0x1c0(r3)
	lfs      f0, 8(r4)
	stfs     f0, 0x1c4(r3)
	blr
	*/
}

namespace Game {

/*
 * --INFO--
 * Address:	80167F78
 * Size:	000104
 */
void Pellet::allocateTexCaster()
{
	if ((getKind() == PELTYPE_TREASURE || getKind() == PELTYPE_UPGRADE) && m_caster == nullptr) {
		float radius = m_config->m_params.m_pRadius.m_data;
		Sys::Sphere sphere(m_pelletPosition, 2.0f * radius);
		m_caster = TexCaster::Mgr::sInstance->create(sphere, TAU * randFloat());

		if (m_caster != nullptr) {
			if (m_captureMatrix != nullptr) {
				m_caster->hide();
			} else {
				m_caster->fadein(0.5f);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	8016807C
 * Size:	0002F0
 */
void Pellet::onSetPosition(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	stw      r30, 8(r1)
	lwz      r4, gameSystem__4Game@sda21(r13)
	lwz      r4, 0x44(r4)
	cmpwi    r4, 4
	beq      lbl_801681C8
	lwz      r5, 0xb8(r31)
	li       r30, 0
	cmplwi   r5, 0
	bne      lbl_801680E4
	lbz      r0, mDebug__Q24Game9PelletMgr@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_801680E4
	lwz      r3, 0x35c(r31)
	lfs      f0, lbl_80518914@sda21(r2)
	lfs      f1, 0x1b0(r3)
	fcmpo    cr0, f1, f0
	ble      lbl_801680E4
	lbz      r0, 0x3c4(r31)
	cmplwi   r0, 0
	bne      lbl_801680E4
	li       r30, 1

lbl_801680E4:
	cmpwi    r4, 1
	bne      lbl_80168140
	cmplwi   r5, 0
	bne      lbl_80168140
	lbz      r0, 0x3c4(r31)
	cmplwi   r0, 0
	bne      lbl_80168140
	lbz      r0, 0x32c(r31)
	cmplwi   r0, 4
	bne      lbl_80168114
	li       r30, 0
	b        lbl_80168140

lbl_80168114:
	cmplwi   r0, 5
	bne      lbl_80168124
	li       r30, 0
	b        lbl_80168140

lbl_80168124:
	cmplwi   r0, 6
	bne      lbl_80168140
	mr       r3, r31
	bl       getStateID__Q24Game6PelletFv
	cmpwi    r3, 5
	beq      lbl_80168140
	li       r30, 1

lbl_80168140:
	clrlwi.  r0, r30, 0x18
	beq      lbl_801681C8
	lwz      r3, mgr__Q24Game12ItemTreasure@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0xbc(r12)
	mtctr    r12
	bctrl
	or.      r30, r3, r3
	beq      lbl_801681AC
	lwz      r3, mapMgr__4Game@sda21(r13)
	addi     r4, r31, 0x3ac
	lwz      r12, 4(r3)
	lwz      r12, 0x28(r12)
	mtctr    r12
	bctrl
	stfs     f1, 0x3b0(r31)
	mr       r3, r30
	li       r4, 0
	bl       init__Q24Game8CreatureFPQ24Game15CreatureInitArg
	mr       r3, r30
	addi     r4, r31, 0x3ac
	li       r5, 0
	bl       "setPosition__Q24Game8CreatureFR10Vector3<f>b"
	mr       r3, r30
	mr       r4, r31
	bl       setTreasure__Q34Game12ItemTreasure4ItemFPQ24Game6Pellet
	b        lbl_801681C8

lbl_801681AC:
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E38C@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x916
	addi     r5, r5, lbl_8047E38C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_801681C8:
	lis      r4, "zero__10Vector3<f>"@ha
	addi     r3, r31, 0x17c
	addi     r5, r4, "zero__10Vector3<f>"@l
	addi     r4, r31, 0x3ac
	bl       "initPosition__Q24Game5RigidFR10Vector3<f>R10Vector3<f>"
	lwz      r4, 0x180(r31)
	mr       r3, r31
	lwz      r0, 0x184(r31)
	stw      r4, 0x138(r31)
	stw      r0, 0x13c(r31)
	lwz      r4, 0x188(r31)
	lwz      r0, 0x18c(r31)
	stw      r4, 0x140(r31)
	stw      r0, 0x144(r31)
	lwz      r4, 0x190(r31)
	lwz      r0, 0x194(r31)
	stw      r4, 0x148(r31)
	stw      r0, 0x14c(r31)
	lwz      r4, 0x198(r31)
	lwz      r0, 0x19c(r31)
	stw      r4, 0x150(r31)
	stw      r0, 0x154(r31)
	lwz      r4, 0x1a0(r31)
	lwz      r0, 0x1a4(r31)
	stw      r4, 0x158(r31)
	stw      r0, 0x15c(r31)
	lwz      r4, 0x1a8(r31)
	lwz      r0, 0x1ac(r31)
	stw      r4, 0x160(r31)
	stw      r0, 0x164(r31)
	lfs      f0, 0x3ac(r31)
	stfs     f0, 0x444(r31)
	lfs      f0, 0x3b0(r31)
	stfs     f0, 0x448(r31)
	lfs      f0, 0x3b4(r31)
	stfs     f0, 0x44c(r31)
	bl       updateParticlePositions__Q24Game11DynCreatureFv
	lfs      f1, lbl_80518910@sda21(r2)
	lfs      f0, lbl_80518914@sda21(r2)
	stfs     f1, 0x17c(r31)
	stfs     f0, 0x118(r31)
	lbz      r0, 0x32c(r31)
	cmplwi   r0, 1
	bne      lbl_80168280
	lfs      f0, lbl_80518998@sda21(r2)
	stfs     f0, 0x118(r31)

lbl_80168280:
	lwz      r3, 0x35c(r31)
	lfs      f2, lbl_8051899C@sda21(r2)
	lfs      f6, 0xd0(r3)
	lfs      f0, 0xc0(r3)
	lfs      f3, 0xa0(r3)
	fdivs    f7, f0, f6
	lfs      f4, lbl_8051893C@sda21(r2)
	lfs      f5, lbl_80518910@sda21(r2)
	lfs      f0, 0x2c0(r31)
	lfs      f1, lbl_80518918@sda21(r2)
	fdivs    f6, f3, f6
	fmuls    f3, f7, f7
	fmuls    f6, f6, f6
	fdivs    f2, f3, f2
	fmadds   f2, f6, f4, f2
	fmuls    f1, f6, f1
	fmuls    f2, f5, f2
	fmuls    f1, f5, f1
	fmuls    f0, f0, f2
	stfs     f0, 0x2c0(r31)
	lfs      f0, 0x2c4(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0x2c4(r31)
	lfs      f0, 0x2c8(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0x2c8(r31)
	lfs      f0, 0x2d0(r31)
	fmuls    f0, f0, f1
	stfs     f0, 0x2d0(r31)
	lfs      f0, 0x2d4(r31)
	fmuls    f0, f0, f1
	stfs     f0, 0x2d4(r31)
	lfs      f0, 0x2d8(r31)
	fmuls    f0, f0, f1
	stfs     f0, 0x2d8(r31)
	lfs      f0, 0x2e0(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0x2e0(r31)
	lfs      f0, 0x2e4(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0x2e4(r31)
	lfs      f0, 0x2e8(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0x2e8(r31)
	lfs      f0, 0x3ac(r31)
	stfs     f0, 0x444(r31)
	lfs      f0, 0x3b0(r31)
	stfs     f0, 0x448(r31)
	lfs      f0, 0x3b4(r31)
	stfs     f0, 0x44c(r31)
	lbz      r0, 0x2f1(r31)
	ori      r0, r0, 1
	stb      r0, 0x2f1(r31)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016836C
 * Size:	000160
 */
void Pellet::setPanModokiRotation(float)
{
	/*
	stwu     r1, -0x50(r1)
	mflr     r0
	lfs      f2, lbl_80518914@sda21(r2)
	stw      r0, 0x54(r1)
	stw      r31, 0x4c(r1)
	mr       r31, r3
	stfs     f1, 0x3b8(r3)
	lfs      f4, 0x13c(r3)
	stfs     f4, 8(r1)
	fmuls    f0, f4, f4
	lfs      f3, 0x14c(r3)
	stfs     f3, 0xc(r1)
	fmuls    f5, f3, f3
	lfs      f3, 0x15c(r3)
	fadds    f0, f0, f5
	fmuls    f6, f3, f3
	stfs     f3, 0x10(r1)
	fadds    f0, f6, f0
	fcmpo    cr0, f0, f2
	ble      lbl_801683D8
	fmadds   f0, f4, f4, f5
	fadds    f4, f6, f0
	fcmpo    cr0, f4, f2
	ble      lbl_801683DC
	frsqrte  f0, f4
	fmuls    f4, f0, f4
	b        lbl_801683DC

lbl_801683D8:
	fmr      f4, f2

lbl_801683DC:
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f4, f0
	ble      lbl_80168414
	lfs      f0, lbl_80518910@sda21(r2)
	lfs      f3, 8(r1)
	fdivs    f4, f0, f4
	lfs      f2, 0xc(r1)
	lfs      f0, 0x10(r1)
	fmuls    f3, f3, f4
	fmuls    f2, f2, f4
	fmuls    f0, f0, f4
	stfs     f3, 8(r1)
	stfs     f2, 0xc(r1)
	stfs     f0, 0x10(r1)

lbl_80168414:
	addi     r3, r1, 0x14
	addi     r4, r1, 8
	bl       "makeNaturalPosture__7MatrixfFR10Vector3<f>"
	lwz      r5, 0x14(r1)
	addi     r3, r31, 0x1f8
	lwz      r0, 0x18(r1)
	addi     r4, r31, 0x138
	stw      r5, 0x138(r31)
	stw      r0, 0x13c(r31)
	lwz      r5, 0x1c(r1)
	lwz      r0, 0x20(r1)
	stw      r5, 0x140(r31)
	stw      r0, 0x144(r31)
	lwz      r5, 0x24(r1)
	lwz      r0, 0x28(r1)
	stw      r5, 0x148(r31)
	stw      r0, 0x14c(r31)
	lwz      r5, 0x2c(r1)
	lwz      r0, 0x30(r1)
	stw      r5, 0x150(r31)
	stw      r0, 0x154(r31)
	lwz      r5, 0x34(r1)
	lwz      r0, 0x38(r1)
	stw      r5, 0x158(r31)
	stw      r0, 0x15c(r31)
	lwz      r5, 0x3c(r1)
	lwz      r0, 0x40(r1)
	stw      r5, 0x160(r31)
	stw      r0, 0x164(r31)
	bl       fromMatrixf__4QuatFR7Matrixf
	addi     r3, r31, 0x1f8
	bl       normalise__4QuatFv
	lfs      f0, 0x3ac(r31)
	addi     r3, r31, 0x138
	addi     r4, r31, 0x180
	stfs     f0, 0x144(r31)
	lfs      f0, 0x3b0(r31)
	stfs     f0, 0x154(r31)
	lfs      f0, 0x3b4(r31)
	stfs     f0, 0x164(r31)
	bl       PSMTXCopy
	lwz      r0, 0x54(r1)
	lwz      r31, 0x4c(r1)
	mtlr     r0
	addi     r1, r1, 0x50
	blr
	*/
}

/*
 * --INFO--
 * Address:	801684CC
 * Size:	0002D0
 */
void Pellet::setOrientation(Matrixf&)
{
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stfd     f31, 0x20(r1)
	psq_st   f31, 40(r1), 0, qr0
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r31, r3
	mr       r30, r4
	addi     r3, r1, 8
	bl       __ct__4QuatFv
	mr       r4, r30
	addi     r3, r1, 8
	bl       fromMatrixf__4QuatFR7Matrixf
	addi     r3, r1, 8
	bl       normalise__4QuatFv
	lfs      f0, 8(r1)
	addi     r3, r31, 0x138
	addi     r4, r1, 8
	stfs     f0, 0x1f8(r31)
	lfs      f0, 0xc(r1)
	stfs     f0, 0x1fc(r31)
	lfs      f0, 0x10(r1)
	stfs     f0, 0x200(r31)
	lfs      f0, 0x14(r1)
	stfs     f0, 0x204(r31)
	bl       makeQ__7MatrixfFR4Quat
	lfs      f0, 0x3ac(r31)
	addi     r3, r31, 0x138
	addi     r4, r31, 0x180
	stfs     f0, 0x144(r31)
	lfs      f0, 0x3b0(r31)
	stfs     f0, 0x154(r31)
	lfs      f0, 0x3b4(r31)
	stfs     f0, 0x164(r31)
	bl       PSMTXCopy
	lfs      f1, 0x14c(r31)
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f1, f0
	ble      lbl_80168578
	lfs      f1, 0x140(r31)
	lfs      f31, 0x160(r31)
	b        lbl_80168580

lbl_80168578:
	lfs      f1, 0x138(r31)
	lfs      f31, 0x158(r31)

lbl_80168580:
	lfs      f0, lbl_805189A0@sda21(r2)
	fcmpo    cr0, f31, f0
	bge      lbl_80168594
	fmr      f31, f0
	b        lbl_801685A4

lbl_80168594:
	lfs      f0, lbl_80518910@sda21(r2)
	fcmpo    cr0, f31, f0
	ble      lbl_801685A4
	fmr      f31, f0

lbl_801685A4:
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f1, f0
	ble      lbl_80168690
	lfs      f0, lbl_805189A0@sda21(r2)
	li       r0, 0
	fcmpo    cr0, f31, f0
	cror     2, 1, 2
	bne      lbl_801685D8
	lfs      f0, lbl_80518910@sda21(r2)
	fcmpo    cr0, f31, f0
	cror     2, 0, 2
	bne      lbl_801685D8
	li       r0, 1

lbl_801685D8:
	clrlwi.  r0, r0, 0x18
	bne      lbl_801685FC
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x9c8
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_801685FC:
	lfs      f0, lbl_80518910@sda21(r2)
	fcmpo    cr0, f31, f0
	cror     2, 1, 2
	bne      lbl_80168614
	lfs      f0, lbl_80518914@sda21(r2)
	b        lbl_80168688

lbl_80168614:
	lfs      f0, lbl_805189A0@sda21(r2)
	fcmpo    cr0, f31, f0
	cror     2, 0, 2
	bne      lbl_8016862C
	lfs      f0, lbl_805189A4@sda21(r2)
	b        lbl_80168688

lbl_8016862C:
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f31, f0
	bge      lbl_80168664
	fneg     f0, f31
	lfs      f1, lbl_805189A8@sda21(r2)
	fmuls    f1, f1, f0
	bl       __cvt_fp2unsigned
	lis      r4, asinAcosTable___5JMath@ha
	slwi     r0, r3, 2
	addi     r3, r4, asinAcosTable___5JMath@l
	lfs      f0, lbl_805189AC@sda21(r2)
	lfsx     f1, r3, r0
	fadds    f0, f1, f0
	b        lbl_80168688

lbl_80168664:
	lfs      f0, lbl_805189A8@sda21(r2)
	fmuls    f1, f0, f31
	bl       __cvt_fp2unsigned
	lis      r4, asinAcosTable___5JMath@ha
	slwi     r0, r3, 2
	addi     r3, r4, asinAcosTable___5JMath@l
	lfs      f0, lbl_805189AC@sda21(r2)
	lfsx     f1, r3, r0
	fsubs    f0, f0, f1

lbl_80168688:
	stfs     f0, 0x3b8(r31)
	b        lbl_80168770

lbl_80168690:
	lfs      f0, lbl_805189A0@sda21(r2)
	li       r0, 0
	fcmpo    cr0, f31, f0
	cror     2, 1, 2
	bne      lbl_801686B8
	lfs      f0, lbl_80518910@sda21(r2)
	fcmpo    cr0, f31, f0
	cror     2, 0, 2
	bne      lbl_801686B8
	li       r0, 1

lbl_801686B8:
	clrlwi.  r0, r0, 0x18
	bne      lbl_801686DC
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x9cb
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_801686DC:
	lfs      f0, lbl_80518910@sda21(r2)
	fcmpo    cr0, f31, f0
	cror     2, 1, 2
	bne      lbl_801686F4
	lfs      f0, lbl_80518914@sda21(r2)
	b        lbl_80168768

lbl_801686F4:
	lfs      f0, lbl_805189A0@sda21(r2)
	fcmpo    cr0, f31, f0
	cror     2, 0, 2
	bne      lbl_8016870C
	lfs      f0, lbl_805189A4@sda21(r2)
	b        lbl_80168768

lbl_8016870C:
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f31, f0
	bge      lbl_80168744
	fneg     f0, f31
	lfs      f1, lbl_805189A8@sda21(r2)
	fmuls    f1, f1, f0
	bl       __cvt_fp2unsigned
	lis      r4, asinAcosTable___5JMath@ha
	slwi     r0, r3, 2
	addi     r3, r4, asinAcosTable___5JMath@l
	lfs      f0, lbl_805189AC@sda21(r2)
	lfsx     f1, r3, r0
	fadds    f0, f1, f0
	b        lbl_80168768

lbl_80168744:
	lfs      f0, lbl_805189A8@sda21(r2)
	fmuls    f1, f0, f31
	bl       __cvt_fp2unsigned
	lis      r4, asinAcosTable___5JMath@ha
	slwi     r0, r3, 2
	addi     r3, r4, asinAcosTable___5JMath@l
	lfs      f0, lbl_805189AC@sda21(r2)
	lfsx     f1, r3, r0
	fsubs    f0, f0, f1

lbl_80168768:
	fneg     f0, f0
	stfs     f0, 0x3b8(r31)

lbl_80168770:
	lfs      f1, 0x3b8(r31)
	bl       roundAng__Ff
	stfs     f1, 0x3b8(r31)
	psq_l    f31, 40(r1), 0, qr0
	lwz      r0, 0x34(r1)
	lfd      f31, 0x20(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016879C
 * Size:	000028
 */
void Pellet::getStateID(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	mr       r4, r3
	stw      r0, 0x14(r1)
	lwz      r3, 0x3c8(r3)
	bl       "getCurrID__Q24Game28StateMachine<Q24Game6Pellet>FPQ24Game6Pellet"
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	801687C4
 * Size:	000260
 */
void Pellet::bounceCallback(Sys::Triangle*)
{
	/*
	stwu     r1, -0x80(r1)
	mflr     r0
	stw      r0, 0x84(r1)
	stfd     f31, 0x70(r1)
	psq_st   f31, 120(r1), 0, qr0
	stw      r31, 0x6c(r1)
	stw      r30, 0x68(r1)
	stw      r29, 0x64(r1)
	mr       r30, r3
	addi     r3, r1, 0x14
	mr       r4, r30
	lwz      r5, 0x35c(r30)
	lwz      r12, 0(r30)
	lfs      f31, 0xb0(r5)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f0, 0x14(r1)
	li       r31, 0
	lfs      f2, 0x18(r1)
	lfs      f1, 0x1c(r1)
	stfs     f0, 0x20(r1)
	lfs      f0, lbl_80518928@sda21(r2)
	stfs     f2, 0x24(r1)
	fcmpo    cr0, f31, f0
	stfs     f1, 0x28(r1)
	lwz      r3, 0x35c(r30)
	lfs      f1, 0xc0(r3)
	fsubs    f0, f2, f1
	stfs     f1, 0x2c(r1)
	stfs     f0, 0x24(r1)
	ble      lbl_8016884C
	li       r31, 2
	b        lbl_8016885C

lbl_8016884C:
	lfs      f0, lbl_80518994@sda21(r2)
	fcmpo    cr0, f31, f0
	ble      lbl_8016885C
	li       r31, 1

lbl_8016885C:
	mr       r3, r30
	addi     r5, r1, 0x20
	li       r4, 0
	bl       checkWater__Q24Game8CreatureFPQ24Game8WaterBoxRQ23Sys6Sphere
	mr       r0, r3
	mr       r3, r30
	mr       r29, r0
	addi     r5, r1, 0x20
	li       r4, 0
	bl       checkWater__Q24Game8CreatureFPQ24Game8WaterBoxRQ23Sys6Sphere
	cmplwi   r3, 0
	beq      lbl_8016899C
	lbz      r0, 0x324(r30)
	cmplwi   r0, 0
	bne      lbl_80168990
	lis      r3, __vt__Q23efx5TBase@ha
	li       r4, 0
	addi     r0, r3, __vt__Q23efx5TBase@l
	lis      r3, __vt__Q23efx8TSimple3@ha
	stw      r0, 0x44(r1)
	addi     r0, r3, __vt__Q23efx8TSimple3@l
	lis      r3, __vt__Q23efx12TOtakaraDive@ha
	li       r7, 0x279
	stw      r0, 0x44(r1)
	addi     r0, r3, __vt__Q23efx12TOtakaraDive@l
	li       r6, 0x27a
	li       r5, 0x27b
	sth      r7, 0x48(r1)
	mr       r3, r29
	sth      r6, 0x4a(r1)
	sth      r5, 0x4c(r1)
	stw      r4, 0x50(r1)
	stw      r4, 0x54(r1)
	stw      r4, 0x58(r1)
	stw      r0, 0x44(r1)
	lwz      r12, 0(r29)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	lfs      f0, 0(r3)
	lis      r4, __vt__Q23efx3Arg@ha
	lwz      r8, 0x20(r1)
	lis      r3, __vt__Q23efx8ArgScale@ha
	stfs     f0, 0x24(r1)
	addi     r5, r4, __vt__Q23efx3Arg@l
	lwz      r6, 0x28(r1)
	addi     r0, r3, __vt__Q23efx8ArgScale@l
	lwz      r9, 0x35c(r30)
	addi     r3, r1, 0x44
	lwz      r7, 0x24(r1)
	addi     r4, r1, 0x30
	lfs      f3, 0xb0(r9)
	stw      r8, 8(r1)
	stw      r7, 0xc(r1)
	lfs      f2, 8(r1)
	stw      r6, 0x10(r1)
	lfs      f1, 0xc(r1)
	stw      r5, 0x30(r1)
	lfs      f0, 0x10(r1)
	stfs     f2, 0x34(r1)
	stfs     f1, 0x38(r1)
	stfs     f0, 0x3c(r1)
	stw      r0, 0x30(r1)
	stfs     f3, 0x40(r1)
	bl       create__Q23efx12TOtakaraDiveFPQ23efx3Arg
	lwz      r3, 0x330(r30)
	addi     r4, r31, 0x380b
	li       r5, 0
	lwz      r12, 0x28(r3)
	lwz      r12, 0x7c(r12)
	mtctr    r12
	bctrl
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x1d8(r12)
	mtctr    r12
	bctrl

lbl_80168990:
	li       r0, 1
	stb      r0, 0x324(r30)
	b        lbl_80168A00

lbl_8016899C:
	lbz      r0, 0x324(r30)
	cmplwi   r0, 0
	bne      lbl_80168A00
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x1f4(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	cmplwi   r0, 1
	beq      lbl_80168A00
	lwz      r3, 0x330(r30)
	addi     r4, r31, 0x3808
	li       r5, 0
	lwz      r12, 0x28(r3)
	lwz      r12, 0x7c(r12)
	mtctr    r12
	bctrl
	li       r0, 1
	mr       r3, r30
	stb      r0, 0x324(r30)
	lwz      r12, 0(r30)
	lwz      r12, 0x1d8(r12)
	mtctr    r12
	bctrl

lbl_80168A00:
	psq_l    f31, 120(r1), 0, qr0
	lwz      r0, 0x84(r1)
	lfd      f31, 0x70(r1)
	lwz      r31, 0x6c(r1)
	lwz      r30, 0x68(r1)
	lwz      r29, 0x64(r1)
	mtlr     r0
	addi     r1, r1, 0x80
	blr
	*/
}

/*
 * --INFO--
 * Address:	80168A24
 * Size:	000004
 */
// WEAK - in header
// void Pellet::onBounce() { }

/*
 * --INFO--
 * Address:	80168A28
 * Size:	000F84
 */
void Pellet::update(void)
{
	/*
	stwu     r1, -0x2f0(r1)
	mflr     r0
	stw      r0, 0x2f4(r1)
	stfd     f31, 0x2e0(r1)
	psq_st   f31, 744(r1), 0, qr0
	stfd     f30, 0x2d0(r1)
	psq_st   f30, 728(r1), 0, qr0
	stfd     f29, 0x2c0(r1)
	psq_st   f29, 712(r1), 0, qr0
	stfd     f28, 0x2b0(r1)
	psq_st   f28, 696(r1), 0, qr0
	stw      r31, 0x2ac(r1)
	stw      r30, 0x2a8(r1)
	stw      r29, 0x2a4(r1)
	mr       r30, r3
	lis      r5, lbl_8047E318@ha
	mr       r4, r30
	addi     r3, r1, 0x14
	lwz      r12, 0(r30)
	addi     r31, r5, lbl_8047E318@l
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f1, 0x14(r1)
	mr       r3, r30
	lfs      f2, 0x18(r1)
	addi     r5, r1, 0xb0
	lfs      f0, 0x1c(r1)
	li       r4, 0
	stfs     f1, 0xb0(r1)
	stfs     f2, 0xb4(r1)
	stfs     f0, 0xb8(r1)
	lwz      r6, 0x35c(r30)
	lfs      f1, 0xc0(r6)
	fsubs    f0, f2, f1
	stfs     f1, 0xbc(r1)
	stfs     f0, 0xb4(r1)
	bl       checkWater__Q24Game8CreatureFPQ24Game8WaterBoxRQ23Sys6Sphere
	cmplwi   r3, 0
	beq      lbl_80168AD4
	li       r0, 1
	stb      r0, 0x325(r30)
	b        lbl_80168ADC

lbl_80168AD4:
	li       r0, 0
	stb      r0, 0x325(r30)

lbl_80168ADC:
	mr       r3, r30
	bl       updateDiscoverDisable__Q24Game6PelletFv
	lwz      r3, 0x330(r30)
	cmplwi   r3, 0
	beq      lbl_80168C68
	lwz      r12, 0x28(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r3, gameSystem__4Game@sda21(r13)
	lwz      r0, 0x44(r3)
	cmpwi    r0, 0
	bne      lbl_80168C68
	lwz      r3, moviePlayer__4Game@sda21(r13)
	lwz      r0, 0x1f0(r3)
	clrlwi.  r0, r0, 0x1f
	bne      lbl_80168C68
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x208(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80168C68
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x1f4(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	cmplwi   r0, 3
	beq      lbl_80168B7C
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x1f4(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	cmplwi   r0, 4
	bne      lbl_80168C68

lbl_80168B7C:
	lwz      r0, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_80168B9C
	addi     r3, r31, 0x80
	addi     r5, r31, 0x3c
	li       r4, 0x1d3
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80168B9C:
	lwz      r29, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r29, 0
	bne      lbl_80168BBC
	addi     r3, r31, 0x80
	addi     r5, r31, 0x3c
	li       r4, 0x1dc
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80168BBC:
	lwz      r0, 4(r29)
	cmplwi   r0, 0
	bne      lbl_80168BDC
	addi     r3, r31, 0x8c
	addi     r5, r31, 0x3c
	li       r4, 0xcf
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80168BDC:
	lwz      r3, 4(r29)
	lwz      r29, 4(r3)
	cmplwi   r29, 0
	bne      lbl_80168C00
	addi     r3, r31, 0x8c
	addi     r5, r31, 0x98
	li       r4, 0xd1
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80168C00:
	lwz      r12, 0(r29)
	mr       r3, r29
	lwz      r12, 0x40(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80168C30
	addi     r3, r31, 0xbc
	addi     r5, r31, 0x3c
	li       r4, 0x177
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80168C30:
	mr       r3, r29
	lwz      r12, 0(r29)
	lwz      r12, 0x58(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80168C68
	lwz      r3, 0x330(r30)
	li       r4, 0x4002
	li       r5, 0
	lwz      r12, 0x28(r3)
	lwz      r12, 0x7c(r12)
	mtctr    r12
	bctrl

lbl_80168C68:
	lwz      r3, 0x334(r30)
	addi     r4, r1, 0xa4
	bl       "frameWork__Q24Game11PelletCarryFR10Vector3<f>"
	clrlwi.  r0, r3, 0x18
	beq      lbl_80168CCC
	lwz      r0, 0xf0(r30)
	cmplwi   r0, 0
	bne      lbl_80168C94
	lwz      r3, 0x334(r30)
	bl       reset__Q24Game11PelletCarryFv
	b        lbl_80168CCC

lbl_80168C94:
	mr       r4, r30
	addi     r3, r1, 8
	lwz      r12, 0(r30)
	lwz      r12, 0x6c(r12)
	mtctr    r12
	bctrl
	lfs      f0, 0xc(r1)
	mr       r3, r30
	addi     r4, r1, 0xa4
	stfs     f0, 0xa8(r1)
	lwz      r12, 0(r30)
	lwz      r12, 0x68(r12)
	mtctr    r12
	bctrl

lbl_80168CCC:
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	bne      lbl_80168CE0
	mr       r3, r30
	bl       updateClaim__Q24Game6PelletFv

lbl_80168CE0:
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_80168D5C
	lwz      r29, 0x3d8(r30)
	cmpwi    r29, 0
	ble      lbl_80168CFC
	b        lbl_80168D04

lbl_80168CFC:
	lwz      r3, 0x35c(r30)
	lwz      r29, 0x120(r3)

lbl_80168D04:
	mr       r3, r30
	bl       getTotalCarryPikmins__Q24Game6PelletFv
	cmpw     r3, r29
	bge      lbl_80168D5C
	mr       r3, r30
	li       r4, 0
	lwz      r12, 0(r30)
	lwz      r12, 0x14c(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0x334(r30)
	bl       reset__Q24Game11PelletCarryFv
	lbz      r0, 0x3f6(r30)
	cmplwi   r0, 0
	bne      lbl_80168D5C
	lwz      r12, 0(r30)
	lis      r4, "zero__10Vector3<f>"@ha
	mr       r3, r30
	lwz      r12, 0x68(r12)
	addi     r4, r4, "zero__10Vector3<f>"@l
	mtctr    r12
	bctrl

lbl_80168D5C:
	lwz      r3, 0x114(r30)
	addi     r4, r30, 0x444
	bl       getBoundingSphere__8CollTreeFRQ23Sys6Sphere
	mr       r3, r30
	bl       updateCell__Q24Game8CreatureFv
	lwz      r0, 0x358(r30)
	cmplwi   r0, 0
	beq      lbl_80168DB0
	lwz      r3, 0x114(r30)
	bl       update__8CollTreeFv
	lwz      r3, 0x114(r30)
	addi     r4, r30, 0x444
	bl       getBoundingSphere__8CollTreeFRQ23Sys6Sphere
	lwz      r3, 0x114(r30)
	li       r4, 0
	lwz      r3, 0(r3)
	lwz      r3, 0x5c(r3)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl

lbl_80168DB0:
	lwz      r3, 0x3c8(r30)
	mr       r4, r30
	lwz      r12, 0(r3)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0x3c8(r30)
	mr       r4, r30
	bl       "getCurrID__Q24Game28StateMachine<Q24Game6Pellet>FPQ24Game6Pellet"
	cmpwi    r3, 6
	bne      lbl_80168DF4
	addi     r3, r1, 0x98
	bl       __ct__Q24Game9AILODParmFv
	mr       r3, r30
	addi     r4, r1, 0x98
	bl       updateLOD__Q24Game8CreatureFRQ24Game9AILODParm
	b        lbl_80169970

lbl_80168DF4:
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0xa8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80168E50
	addi     r3, r1, 0x8c
	bl       __ct__Q24Game9AILODParmFv
	mr       r3, r30
	addi     r4, r1, 0x8c
	bl       updateLOD__Q24Game8CreatureFRQ24Game9AILODParm
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0xb8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80169970
	lbz      r0, 0xd8(r30)
	ori      r0, r0, 0x34
	stb      r0, 0xd8(r30)
	b        lbl_80169970

lbl_80168E50:
	lwz      r0, 0xb8(r30)
	cmplwi   r0, 0
	beq      lbl_80168E74
	addi     r3, r1, 0x80
	bl       __ct__Q24Game9AILODParmFv
	mr       r3, r30
	addi     r4, r1, 0x80
	bl       updateLOD__Q24Game8CreatureFRQ24Game9AILODParm
	b        lbl_80169970

lbl_80168E74:
	addi     r3, r1, 0x74
	bl       __ct__Q24Game9AILODParmFv
	mr       r3, r30
	addi     r4, r1, 0x74
	bl       updateLOD__Q24Game8CreatureFRQ24Game9AILODParm
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0xb8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80168EB0
	lbz      r0, 0xd8(r30)
	ori      r0, r0, 0x34
	stb      r0, 0xd8(r30)

lbl_80168EB0:
	lbz      r0, 0x364(r30)
	li       r5, 2
	cmplwi   r0, 0
	bne      lbl_80168EC8
	li       r4, 1
	b        lbl_80168EF4

lbl_80168EC8:
	cmplwi   r0, 2
	bne      lbl_80168ED8
	li       r4, 0
	b        lbl_80168EF4

lbl_80168ED8:
	lbz      r0, 0xd8(r30)
	clrlwi   r0, r0, 0x1e
	cmpwi    r0, 2
	blt      lbl_80168EF0
	li       r4, 0
	b        lbl_80168EF4

lbl_80168EF0:
	li       r4, 1

lbl_80168EF4:
	lbz      r3, 0xd8(r30)
	rlwinm.  r0, r3, 0, 0x1d, 0x1d
	beq      lbl_80168F0C
	clrlwi   r0, r3, 0x1e
	cmpwi    r0, 1
	blt      lbl_80168F10

lbl_80168F0C:
	li       r5, 1

lbl_80168F10:
	stb      r4, 0x39c(r30)
	lbz      r0, disableDynamics__Q24Game9PelletMgr@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_80168F2C
	lbz      r0, 0x39c(r30)
	cmplwi   r0, 0
	bne      lbl_80169364

lbl_80168F2C:
	lwz      r3, sys@sda21(r13)
	lfs      f0, 0x3ac(r30)
	lfs      f31, 0x54(r3)
	stfs     f0, 0x64(r1)
	lfs      f1, 0x3b0(r30)
	stfs     f1, 0x68(r1)
	lfs      f0, 0x3b4(r30)
	stfs     f0, 0x6c(r1)
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_80168F64
	lfs      f0, lbl_80518938@sda21(r2)
	fsubs    f0, f1, f0
	stfs     f0, 0x68(r1)

lbl_80168F64:
	lwz      r3, 0x35c(r30)
	addi     r31, r30, 0x1bc
	lfs      f2, lbl_80518918@sda21(r2)
	lfs      f1, 0xc0(r3)
	lfs      f0, lbl_80518914@sda21(r2)
	fmuls    f1, f2, f1
	stfs     f1, 0x70(r1)
	stfs     f0, 0x1e0(r30)
	stfs     f0, 0x1e4(r30)
	stfs     f0, 0x1e8(r30)
	stfs     f0, 0x1d4(r30)
	stfs     f0, 0x1d8(r30)
	stfs     f0, 0x1dc(r30)
	lbz      r0, 0x3f6(r30)
	cmplwi   r0, 0
	bne      lbl_80168FB0
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_80168FBC

lbl_80168FB0:
	lwz      r0, 0xc8(r30)
	cmplwi   r0, 0
	bne      lbl_80168FD0

lbl_80168FBC:
	lwz      r3, _aiConstants__4Game@sda21(r13)
	lfs      f0, 4(r31)
	lfs      f1, 0x28(r3)
	fnmsubs  f0, f31, f1, f0
	stfs     f0, 4(r31)

lbl_80168FD0:
	lfs      f0, lbl_80518914@sda21(r2)
	mr       r3, r30
	stfs     f0, 0x120(r30)
	lfs      f0, 0(r31)
	stfs     f0, 0x58(r1)
	lfs      f0, 4(r31)
	stfs     f0, 0x5c(r1)
	lfs      f0, 8(r31)
	stfs     f0, 0x60(r1)
	lwz      r12, 0(r30)
	lwz      r12, 0xb0(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80169060
	lbz      r0, 0x32c(r30)
	cmplwi   r0, 1
	beq      lbl_80169060
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	bne      lbl_80169060
	lbz      r0, 0x3f6(r30)
	cmplwi   r0, 0
	bne      lbl_80169060
	lfs      f1, 0x58(r1)
	lfs      f0, 0x11c(r30)
	lfs      f2, 0x5c(r1)
	fadds    f0, f1, f0
	lfs      f1, 0x60(r1)
	stfs     f0, 0x58(r1)
	lfs      f0, 0x120(r30)
	fadds    f0, f2, f0
	stfs     f0, 0x5c(r1)
	lfs      f0, 0x124(r30)
	fadds    f0, f1, f0
	stfs     f0, 0x60(r1)

lbl_80169060:
	lfs      f4, lbl_80518914@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	li       r5, 0
	stfs     f4, 0x11c(r30)
	addi     r7, r1, 0x64
	lfs      f3, lbl_80518918@sda21(r2)
	addi     r6, r1, 0x58
	stfs     f4, 0x120(r30)
	li       r0, -1
	lfs      f0, lbl_805189B0@sda21(r2)
	fmr      f1, f31
	stfs     f4, 0x124(r30)
	addi     r4, r1, 0x1f8
	stw      r5, 0x20c(r1)
	lfs      f2, 0x800(r3)
	stw      r7, 0x1f8(r1)
	lwz      r3, mapMgr__4Game@sda21(r13)
	stw      r6, 0x1fc(r1)
	stfs     f3, 0x200(r1)
	stfs     f4, 0x204(r1)
	stw      r5, 0x208(r1)
	stw      r5, 0x23c(r1)
	stb      r5, 0x26c(r1)
	stb      r5, 0x211(r1)
	stb      r5, 0x210(r1)
	stw      r5, 0x240(r1)
	stb      r5, 0x288(r1)
	stw      r5, 0x28c(r1)
	stfs     f2, 0x224(r1)
	stfs     f0, 0x228(r1)
	stw      r0, 0x290(r1)
	stw      r5, 0x244(r1)
	stb      r5, 0x212(r1)
	stw      r30, 0x20c(r1)
	lwz      r12, 4(r3)
	lwz      r12, 0x24(r12)
	mtctr    r12
	bctrl
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_80169188
	lwz      r3, 0x240(r1)
	neg      r0, r3
	or       r0, r0, r3
	rlwinm.  r0, r0, 1, 0x1f, 0x1f
	beq      lbl_80169150
	lfs      f1, 0x5c(r1)
	lfs      f0, 0x258(r1)
	lfs      f2, 0x58(r1)
	fmuls    f0, f1, f0
	lfs      f1, 0x254(r1)
	lfs      f4, 0x60(r1)
	lfs      f3, 0x25c(r1)
	fmadds   f1, f2, f1, f0
	lfs      f0, lbl_80518918@sda21(r2)
	fmadds   f1, f4, f3, f1
	fcmpo    cr0, f1, f0
	ble      lbl_80169150
	li       r0, 0

lbl_80169150:
	clrlwi.  r0, r0, 0x18
	beq      lbl_80169170
	lbz      r3, 0x3bc(r30)
	cmplwi   r3, 0x64
	bge      lbl_80169190
	addi     r0, r3, 2
	stb      r0, 0x3bc(r30)
	b        lbl_80169190

lbl_80169170:
	lbz      r3, 0x3bc(r30)
	cmplwi   r3, 0
	beq      lbl_80169190
	addi     r0, r3, -1
	stb      r0, 0x3bc(r30)
	b        lbl_80169190

lbl_80169188:
	li       r0, 0
	stb      r0, 0x3bc(r30)

lbl_80169190:
	lfs      f0, 0x58(r1)
	li       r0, 0
	stfs     f0, 0(r31)
	lfs      f0, 0x5c(r1)
	stfs     f0, 4(r31)
	lfs      f0, 0x60(r1)
	stfs     f0, 8(r31)
	lwz      r3, platMgr__4Game@sda21(r13)
	stw      r31, 0x1fc(r1)
	cmplwi   r3, 0
	stb      r0, 0x211(r1)
	beq      lbl_801691CC
	fmr      f1, f31
	addi     r4, r1, 0x1f8
	bl       traceMove__Q24Game7PlatMgrFRQ24Game8MoveInfof

lbl_801691CC:
	lwz      r4, 0x23c(r1)
	cmplwi   r4, 0
	beq      lbl_8016930C
	lwz      r0, 0xc8(r30)
	cmplwi   r0, 0
	bne      lbl_801691F8
	lwz      r12, 0(r30)
	mr       r3, r30
	lwz      r12, 0xe8(r12)
	mtctr    r12
	bctrl

lbl_801691F8:
	lwz      r0, 0x23c(r1)
	stw      r0, 0xc8(r30)
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	bne      lbl_80169314
	lbz      r0, 0x3f6(r30)
	cmplwi   r0, 0
	bne      lbl_80169314
	lfs      f1, 0x24c(r1)
	lfs      f4, 4(r31)
	lwz      r4, _aiConstants__4Game@sda21(r13)
	lwz      r3, sys@sda21(r13)
	fmuls    f0, f4, f1
	lfs      f13, 0x248(r1)
	lfs      f28, 0(r31)
	lfs      f7, 0x28(r4)
	lfs      f6, 0x54(r3)
	fmadds   f5, f28, f13, f0
	lfs      f2, 0x250(r1)
	lfs      f3, 8(r31)
	fmuls    f6, f7, f6
	lfs      f0, lbl_80518914@sda21(r2)
	fmadds   f11, f3, f2, f5
	lfs      f10, lbl_80518994@sda21(r2)
	fneg     f12, f6
	lfs      f5, lbl_80518910@sda21(r2)
	fmuls    f6, f13, f11
	fmuls    f9, f12, f1
	fmuls    f7, f1, f11
	fsubs    f8, f28, f6
	fmuls    f6, f2, f11
	fmadds   f11, f0, f13, f9
	fsubs    f7, f4, f7
	fmuls    f9, f8, f31
	fmadds   f11, f0, f2, f11
	fsubs    f6, f3, f6
	fmuls    f8, f7, f31
	fmuls    f9, f9, f10
	fmuls    f7, f6, f31
	fmuls    f8, f8, f10
	fmuls    f6, f13, f11
	fsubs    f9, f28, f9
	fmuls    f7, f7, f10
	fsubs    f6, f0, f6
	fmuls    f1, f1, f11
	stfs     f9, 0(r31)
	fsubs    f8, f4, f8
	fneg     f6, f6
	fsubs    f4, f12, f1
	fmuls    f1, f2, f11
	stfs     f8, 4(r31)
	fsubs    f3, f3, f7
	fneg     f2, f4
	fsubs    f0, f0, f1
	stfs     f3, 8(r31)
	fmuls    f3, f6, f5
	fmuls    f1, f2, f5
	lfs      f2, 0(r31)
	fneg     f0, f0
	fadds    f2, f2, f3
	fmuls    f0, f0, f5
	stfs     f2, 0(r31)
	lfs      f2, 4(r31)
	fadds    f1, f2, f1
	stfs     f1, 4(r31)
	lfs      f1, 8(r31)
	fadds    f0, f1, f0
	stfs     f0, 8(r31)
	b        lbl_80169314

lbl_8016930C:
	li       r0, 0
	stw      r0, 0xc8(r30)

lbl_80169314:
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_80169330
	lfs      f1, 0x68(r1)
	lfs      f0, lbl_80518938@sda21(r2)
	fadds    f0, f1, f0
	stfs     f0, 0x68(r1)

lbl_80169330:
	lfs      f0, 0x64(r1)
	stfs     f0, 0x3ac(r30)
	lfs      f0, 0x68(r1)
	stfs     f0, 0x3b0(r30)
	lfs      f0, 0x6c(r1)
	stfs     f0, 0x3b4(r30)
	lfs      f0, 0x3ac(r30)
	stfs     f0, 0x1b0(r30)
	lfs      f0, 0x3b0(r30)
	stfs     f0, 0x1b4(r30)
	lfs      f0, 0x3b4(r30)
	stfs     f0, 0x1b8(r30)
	b        lbl_8016995C

lbl_80169364:
	cmpwi    r5, 0
	ble      lbl_8016995C
	addi     r3, r30, 0x17c
	li       r4, 0
	bl       computeForces__Q24Game5RigidFi
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	bne      lbl_801693A0
	lbz      r0, 0x3f6(r30)
	cmplwi   r0, 0
	bne      lbl_801693A0
	lwz      r4, 0x35c(r30)
	mr       r3, r30
	lfs      f1, 0x110(r4)
	bl       computeForces__Q24Game11DynCreatureFf

lbl_801693A0:
	lwz      r3, _aiConstants__4Game@sda21(r13)
	mr       r4, r30
	li       r31, 1
	lfs      f0, 0x28(r3)
	fneg     f0, f0
	stfs     f0, 0x1cc(r30)
	lwz      r3, 0x3c8(r30)
	bl       "getCurrID__Q24Game28StateMachine<Q24Game6Pellet>FPQ24Game6Pellet"
	cmpwi    r3, 0
	bne      lbl_801695BC
	lbz      r0, 0x311(r30)
	cmplwi   r0, 0
	beq      lbl_801695BC
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x208(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_801695BC
	lfs      f2, 0x1bc(r30)
	lfs      f1, 0x1c0(r30)
	fmuls    f0, f2, f2
	lfs      f3, 0x1c4(r30)
	fmuls    f4, f1, f1
	lfs      f1, lbl_80518914@sda21(r2)
	fmuls    f3, f3, f3
	fadds    f0, f0, f4
	fadds    f0, f3, f0
	fcmpo    cr0, f0, f1
	ble      lbl_80169438
	fmadds   f0, f2, f2, f4
	fadds    f2, f3, f0
	fcmpo    cr0, f2, f1
	ble      lbl_8016943C
	frsqrte  f0, f2
	fmuls    f2, f0, f2
	b        lbl_8016943C

lbl_80169438:
	fmr      f2, f1

lbl_8016943C:
	lfs      f0, lbl_80518994@sda21(r2)
	fcmpo    cr0, f2, f0
	bge      lbl_801695BC
	lfs      f2, 0x1e0(r30)
	lfs      f1, 0x1e4(r30)
	fmuls    f0, f2, f2
	lfs      f3, 0x1e8(r30)
	fmuls    f4, f1, f1
	lfs      f1, lbl_80518914@sda21(r2)
	fmuls    f3, f3, f3
	fadds    f0, f0, f4
	fadds    f0, f3, f0
	fcmpo    cr0, f0, f1
	ble      lbl_80169490
	fmadds   f0, f2, f2, f4
	fadds    f2, f3, f0
	fcmpo    cr0, f2, f1
	ble      lbl_80169494
	frsqrte  f0, f2
	fmuls    f2, f0, f2
	b        lbl_80169494

lbl_80169490:
	fmr      f2, f1

lbl_80169494:
	lfs      f0, lbl_805189B4@sda21(r2)
	fcmpo    cr0, f2, f0
	bge      lbl_801695BC
	lbz      r0, 0x3f6(r30)
	cmplwi   r0, 0
	bne      lbl_801695BC
	lwz      r4, sys@sda21(r13)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	lfs      f0, 0x1b0(r30)
	lfs      f28, 0x54(r4)
	addi     r7, r1, 0x48
	lfs      f5, lbl_80518918@sda21(r2)
	addi     r6, r1, 0x3c
	stfs     f0, 0x48(r1)
	li       r5, 0
	lwz      r8, _aiConstants__4Game@sda21(r13)
	li       r0, -1
	lfs      f6, 0x1b4(r30)
	fmr      f1, f28
	lfs      f4, lbl_80518914@sda21(r2)
	addi     r4, r1, 0x15c
	stfs     f6, 0x4c(r1)
	lfs      f2, 0x800(r3)
	lfs      f3, 0x1b8(r30)
	lfs      f0, lbl_805189B0@sda21(r2)
	stfs     f3, 0x50(r1)
	lwz      r3, mapMgr__4Game@sda21(r13)
	lwz      r9, 0x35c(r30)
	lfs      f3, 0xc0(r9)
	fmuls    f5, f5, f3
	fsubs    f3, f6, f5
	stfs     f5, 0x54(r1)
	stfs     f3, 0x4c(r1)
	lfs      f3, 0x28(r8)
	fneg     f3, f3
	stfs     f4, 0x3c(r1)
	stfs     f4, 0x44(r1)
	stfs     f3, 0x40(r1)
	stw      r7, 0x15c(r1)
	stw      r6, 0x160(r1)
	stfs     f4, 0x164(r1)
	stfs     f4, 0x168(r1)
	stw      r5, 0x16c(r1)
	stw      r5, 0x1a0(r1)
	stb      r5, 0x1d0(r1)
	stb      r5, 0x175(r1)
	stb      r5, 0x174(r1)
	stw      r5, 0x1a4(r1)
	stw      r5, 0x170(r1)
	stb      r5, 0x1ec(r1)
	stw      r5, 0x1f0(r1)
	stfs     f2, 0x188(r1)
	stfs     f0, 0x18c(r1)
	stw      r0, 0x1f4(r1)
	stw      r5, 0x1a8(r1)
	stb      r5, 0x176(r1)
	lwz      r12, 4(r3)
	lwz      r12, 0x24(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x1a0(r1)
	cmplwi   r0, 0
	bne      lbl_801695AC
	lwz      r3, platMgr__4Game@sda21(r13)
	cmplwi   r3, 0
	beq      lbl_801695AC
	fmr      f1, f28
	addi     r4, r1, 0x15c
	bl       traceMove__Q24Game7PlatMgrFRQ24Game8MoveInfof

lbl_801695AC:
	lwz      r0, 0x1a0(r1)
	cmplwi   r0, 0
	beq      lbl_801695BC
	li       r31, 0

lbl_801695BC:
	lwz      r3, sys@sda21(r13)
	clrlwi.  r0, r31, 0x18
	lfs      f0, lbl_80518918@sda21(r2)
	lfs      f1, 0x54(r3)
	lfs      f30, 0x1b0(r30)
	fmuls    f31, f1, f0
	lfs      f29, 0x1b4(r30)
	lfs      f28, 0x1b8(r30)
	beq      lbl_80169668
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0xb0(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016964C
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	bne      lbl_8016964C
	lbz      r0, 0x3f6(r30)
	cmplwi   r0, 0
	bne      lbl_8016964C
	lfs      f0, lbl_80518914@sda21(r2)
	stfs     f0, 0x120(r30)
	lfs      f1, 0x1bc(r30)
	lfs      f0, 0x11c(r30)
	fadds    f0, f1, f0
	stfs     f0, 0x1bc(r30)
	lfs      f1, 0x1c0(r30)
	lfs      f0, 0x120(r30)
	fadds    f0, f1, f0
	stfs     f0, 0x1c0(r30)
	lfs      f1, 0x1c4(r30)
	lfs      f0, 0x124(r30)
	fadds    f0, f1, f0
	stfs     f0, 0x1c4(r30)

lbl_8016964C:
	li       r29, 0

lbl_80169650:
	fmr      f1, f31
	mr       r3, r30
	bl       simulate__Q24Game11DynCreatureFf
	addi     r29, r29, 1
	cmpwi    r29, 2
	blt      lbl_80169650

lbl_80169668:
	lwz      r4, sys@sda21(r13)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	lfs      f6, lbl_80518918@sda21(r2)
	lfs      f31, 0x54(r4)
	addi     r7, r1, 0x2c
	lfs      f0, lbl_80518910@sda21(r2)
	addi     r6, r1, 0x20
	stfs     f30, 0x2c(r1)
	li       r5, 0
	fdivs    f9, f0, f31
	lfs      f3, lbl_80518914@sda21(r2)
	stfs     f29, 0x30(r1)
	li       r0, -1
	lfs      f2, 0x800(r3)
	addi     r4, r1, 0xc0
	stfs     f28, 0x34(r1)
	fmr      f1, f31
	lfs      f0, lbl_805189B0@sda21(r2)
	lwz      r8, 0x35c(r30)
	lwz      r3, mapMgr__4Game@sda21(r13)
	lfs      f4, 0xc0(r8)
	fmuls    f4, f6, f4
	stfs     f4, 0x38(r1)
	lfs      f4, 0x1b0(r30)
	stfs     f4, 0x20(r1)
	fsubs    f4, f4, f30
	lfs      f5, 0x1b4(r30)
	fmuls    f30, f4, f9
	stfs     f5, 0x24(r1)
	fsubs    f7, f5, f29
	lfs      f5, 0x1b8(r30)
	fmuls    f29, f7, f9
	fsubs    f8, f5, f28
	stfs     f5, 0x28(r1)
	stfs     f4, 0x20(r1)
	fmuls    f28, f8, f9
	stfs     f7, 0x24(r1)
	stfs     f8, 0x28(r1)
	stfs     f30, 0x20(r1)
	stfs     f29, 0x24(r1)
	stfs     f28, 0x28(r1)
	stw      r7, 0xc0(r1)
	stw      r6, 0xc4(r1)
	stfs     f6, 0xc8(r1)
	stfs     f3, 0xcc(r1)
	stw      r5, 0xd0(r1)
	stw      r5, 0x104(r1)
	stb      r5, 0x134(r1)
	stb      r5, 0xd9(r1)
	stb      r5, 0xd8(r1)
	stw      r5, 0x108(r1)
	stw      r5, 0xd4(r1)
	stb      r5, 0x150(r1)
	stw      r5, 0x154(r1)
	stfs     f2, 0xec(r1)
	stfs     f0, 0xf0(r1)
	stw      r0, 0x158(r1)
	stw      r5, 0x10c(r1)
	stb      r5, 0xda(r1)
	lwz      r12, 4(r3)
	lwz      r12, 0x24(r12)
	mtctr    r12
	bctrl
	lwz      r3, platMgr__4Game@sda21(r13)
	cmplwi   r3, 0
	beq      lbl_80169780
	fmr      f1, f31
	addi     r4, r1, 0xc0
	bl       traceMove__Q24Game7PlatMgrFRQ24Game8MoveInfof

lbl_80169780:
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_80169800
	lwz      r3, 0x108(r1)
	neg      r0, r3
	or       r0, r0, r3
	rlwinm.  r0, r0, 1, 0x1f, 0x1f
	beq      lbl_801697C8
	lfs      f0, 0x120(r1)
	lfs      f2, 0x11c(r1)
	fmuls    f1, f29, f0
	lfs      f3, 0x124(r1)
	lfs      f0, lbl_80518918@sda21(r2)
	fmadds   f1, f30, f2, f1
	fmadds   f1, f28, f3, f1
	fcmpo    cr0, f1, f0
	ble      lbl_801697C8
	li       r0, 0

lbl_801697C8:
	clrlwi.  r0, r0, 0x18
	beq      lbl_801697E8
	lbz      r3, 0x3bc(r30)
	cmplwi   r3, 0x64
	bge      lbl_80169808
	addi     r0, r3, 2
	stb      r0, 0x3bc(r30)
	b        lbl_80169808

lbl_801697E8:
	lbz      r3, 0x3bc(r30)
	cmplwi   r3, 0
	beq      lbl_80169808
	addi     r0, r3, -1
	stb      r0, 0x3bc(r30)
	b        lbl_80169808

lbl_80169800:
	li       r0, 0
	stb      r0, 0x3bc(r30)

lbl_80169808:
	lwz      r3, 0xc0(r1)
	lfs      f1, lbl_80518914@sda21(r2)
	lfs      f3, 8(r3)
	lfs      f0, 0(r3)
	stfs     f0, 0x1b0(r30)
	stfs     f3, 0x1b8(r30)
	lfs      f3, 0x1bc(r30)
	lfs      f2, 0x1c0(r30)
	lfs      f4, 0x1c4(r30)
	fmuls    f0, f3, f3
	fmuls    f2, f2, f2
	fmuls    f4, f4, f4
	fadds    f0, f0, f2
	fadds    f0, f4, f0
	fcmpo    cr0, f0, f1
	ble      lbl_80169864
	fmadds   f0, f3, f3, f2
	fadds    f2, f4, f0
	fcmpo    cr0, f2, f1
	ble      lbl_80169868
	frsqrte  f0, f2
	fmuls    f2, f0, f2
	b        lbl_80169868

lbl_80169864:
	fmr      f2, f1

lbl_80169868:
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f2, f0
	ble      lbl_801698A4
	lfs      f1, lbl_80518910@sda21(r2)
	lfs      f0, 0x1bc(r30)
	fdivs    f1, f1, f2
	fmuls    f0, f0, f1
	stfs     f0, 0x1bc(r30)
	lfs      f0, 0x1c0(r30)
	fmuls    f0, f0, f1
	stfs     f0, 0x1c0(r30)
	lfs      f0, 0x1c4(r30)
	fmuls    f0, f0, f1
	stfs     f0, 0x1c4(r30)
	b        lbl_801698A8

lbl_801698A4:
	fmr      f2, f0

lbl_801698A8:
	lfs      f3, 0x11c(r30)
	lfs      f1, 0x120(r30)
	fmuls    f0, f3, f3
	lfs      f4, 0x124(r30)
	fmuls    f5, f1, f1
	lfs      f1, lbl_80518914@sda21(r2)
	fmuls    f4, f4, f4
	fadds    f0, f0, f5
	fadds    f0, f4, f0
	fcmpo    cr0, f0, f1
	ble      lbl_801698F0
	fmadds   f0, f3, f3, f5
	fadds    f0, f4, f0
	fcmpo    cr0, f0, f1
	ble      lbl_801698F4
	frsqrte  f1, f0
	fmuls    f0, f1, f0
	b        lbl_801698F4

lbl_801698F0:
	fmr      f0, f1

lbl_801698F4:
	fcmpo    cr0, f2, f0
	ble      lbl_80169928
	fsubs    f1, f2, f0
	lfs      f0, 0x1bc(r30)
	fmuls    f0, f0, f1
	stfs     f0, 0x1bc(r30)
	lfs      f0, 0x1c0(r30)
	fmuls    f0, f0, f1
	stfs     f0, 0x1c0(r30)
	lfs      f0, 0x1c4(r30)
	fmuls    f0, f0, f1
	stfs     f0, 0x1c4(r30)
	b        lbl_8016994C

lbl_80169928:
	lfs      f0, 0x1bc(r30)
	fmuls    f0, f0, f2
	stfs     f0, 0x1bc(r30)
	lfs      f0, 0x1c0(r30)
	fmuls    f0, f0, f2
	stfs     f0, 0x1c0(r30)
	lfs      f0, 0x1c4(r30)
	fmuls    f0, f0, f2
	stfs     f0, 0x1c4(r30)

lbl_8016994C:
	lfs      f0, lbl_80518914@sda21(r2)
	stfs     f0, 0x11c(r30)
	stfs     f0, 0x120(r30)
	stfs     f0, 0x124(r30)

lbl_8016995C:
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x1ec(r12)
	mtctr    r12
	bctrl

lbl_80169970:
	psq_l    f31, 744(r1), 0, qr0
	lfd      f31, 0x2e0(r1)
	psq_l    f30, 728(r1), 0, qr0
	lfd      f30, 0x2d0(r1)
	psq_l    f29, 712(r1), 0, qr0
	lfd      f29, 0x2c0(r1)
	psq_l    f28, 696(r1), 0, qr0
	lfd      f28, 0x2b0(r1)
	lwz      r31, 0x2ac(r1)
	lwz      r30, 0x2a8(r1)
	lwz      r0, 0x2f4(r1)
	lwz      r29, 0x2a4(r1)
	mtlr     r0
	addi     r1, r1, 0x2f0
	blr
	*/
}

/*
 * --INFO--
 * Address:	801699AC
 * Size:	000004
 */
// WEAK - in header
// void Pellet::do_update() { }

} // namespace Game

namespace PSM {

/*
 * --INFO--
 * Address:	801699B0
 * Size:	000008
 */
u32 Scene_Game::isCave(void) { return 0x0; }

namespace Game {

} // namespace Game

/*
 * --INFO--
 * Address:	........
 * Size:	000004
 */
void Pellet::move_noDynamics(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	801699B8
 * Size:	00001C
 */
void Pellet::getPikiBirthCount(int&, int&)
{
	/*
	lwz      r6, 0x35c(r3)
	lwz      r0, 0x150(r6)
	stw      r0, 0(r4)
	lwz      r3, 0x35c(r3)
	lwz      r0, 0x140(r3)
	stw      r0, 0(r5)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801699D4
 * Size:	000014
 */
void PelletMgr::setMovieDraw(bool)
{
	/*
	clrlwi   r0, r4, 0x18
	cntlzw   r0, r0
	srwi     r0, r0, 5
	stb      r0, 0x3c(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801699E8
 * Size:	00012C
 */
void Pellet::doSimulation(float)
{
	/*
	stwu     r1, -0x50(r1)
	mflr     r0
	li       r4, 1
	stw      r0, 0x54(r1)
	li       r0, 0
	stw      r31, 0x4c(r1)
	mr       r31, r3
	stb      r4, 8(r1)
	addi     r4, r1, 8
	stb      r0, 8(r1)
	bl       checkHell__Q24Game8CreatureFRQ34Game8Creature12CheckHellArg
	cmpwi    r3, 2
	bne      lbl_80169B00
	mr       r4, r31
	addi     r3, r1, 0x10
	lwz      r12, 0(r31)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lis      r3, "__vt__27Condition<Q24Game8WayPoint>"@ha
	lfs      f3, 0x10(r1)
	addi     r0, r3, "__vt__27Condition<Q24Game8WayPoint>"@l
	lfs      f2, 0x18(r1)
	lfs      f0, 0x14(r1)
	lis      r3, __vt__Q24Game11WPCondition@ha
	stw      r0, 0xc(r1)
	addi     r4, r3, __vt__Q24Game11WPCondition@l
	lfs      f1, lbl_80518914@sda21(r2)
	lis      r3, lbl_804B1F4C@ha
	stfs     f0, 0x20(r1)
	addi     r5, r1, 0xc
	lfs      f0, lbl_80518994@sda21(r2)
	li       r0, 0
	stw      r4, 0xc(r1)
	addi     r6, r3, lbl_804B1F4C@l
	lwz      r3, mapMgr__4Game@sda21(r13)
	addi     r4, r1, 0x28
	stfs     f3, 0x1c(r1)
	stfs     f2, 0x24(r1)
	stfs     f1, 0x20(r1)
	stw      r6, 0xc(r1)
	stfs     f3, 0x28(r1)
	stfs     f1, 0x2c(r1)
	stfs     f2, 0x30(r1)
	stw      r5, 0x34(r1)
	stb      r0, 0x38(r1)
	stfs     f0, 0x3c(r1)
	lwz      r3, 8(r3)
	bl       getNearestWayPoint__Q24Game8RouteMgrFRQ24Game11WPSearchArg
	cmplwi   r3, 0
	beq      lbl_80169B00
	lfs      f1, 0x50(r3)
	addi     r4, r1, 0x1c
	lfs      f2, 0x54(r3)
	lfs      f0, 0x4c(r3)
	lwz      r3, mapMgr__4Game@sda21(r13)
	stfs     f0, 0x1c(r1)
	stfs     f1, 0x20(r1)
	stfs     f2, 0x24(r1)
	lwz      r12, 4(r3)
	lwz      r12, 0x28(r12)
	mtctr    r12
	bctrl
	lfs      f0, lbl_805189B4@sda21(r2)
	mr       r3, r31
	addi     r4, r1, 0x1c
	li       r5, 0
	fadds    f0, f0, f1
	stfs     f0, 0x20(r1)
	bl       "setPosition__Q24Game8CreatureFR10Vector3<f>b"

lbl_80169B00:
	lwz      r0, 0x54(r1)
	lwz      r31, 0x4c(r1)
	mtlr     r0
	addi     r1, r1, 0x50
	blr
	*/
}

/*
 * --INFO--
 * Address:	80169B14
 * Size:	000114
 */
void Pellet::updateTrMatrix(void)
{
	/*
	stwu     r1, -0xb0(r1)
	mflr     r0
	stw      r0, 0xb4(r1)
	stw      r31, 0xac(r1)
	mr       r31, r3
	lwz      r0, 0xb8(r3)
	cmplwi   r0, 0
	bne      lbl_80169C14
	lfs      f0, 0x1b0(r31)
	addi     r3, r1, 0x74
	lfs      f2, lbl_805189A0@sda21(r2)
	addi     r4, r1, 8
	stfs     f0, 0x3ac(r31)
	lfs      f0, 0x1b4(r31)
	stfs     f0, 0x3b0(r31)
	lfs      f0, 0x1b8(r31)
	stfs     f0, 0x3b4(r31)
	lfs      f3, 0x2fc(r31)
	lfs      f1, 0x2f8(r31)
	lfs      f0, 0x2f4(r31)
	fmuls    f3, f3, f2
	fmuls    f1, f1, f2
	fmuls    f0, f0, f2
	stfs     f3, 0x10(r1)
	stfs     f0, 8(r1)
	stfs     f1, 0xc(r1)
	bl       "makeT__7MatrixfFR10Vector3<f>"
	addi     r3, r1, 0x44
	addi     r4, r31, 0x1f8
	bl       makeQ__7MatrixfFR4Quat
	addi     r3, r1, 0x44
	addi     r4, r1, 0x74
	addi     r5, r1, 0x14
	bl       PSMTXConcat
	lfs      f0, 0x3ac(r31)
	lwz      r3, 0x14(r1)
	stfs     f0, 0x20(r1)
	lwz      r0, 0x18(r1)
	lfs      f0, 0x3b0(r31)
	stfs     f0, 0x30(r1)
	lfs      f0, 0x3b4(r31)
	stfs     f0, 0x40(r1)
	stw      r3, 0x138(r31)
	stw      r0, 0x13c(r31)
	lwz      r3, 0x1c(r1)
	lwz      r0, 0x20(r1)
	stw      r3, 0x140(r31)
	stw      r0, 0x144(r31)
	lwz      r3, 0x24(r1)
	lwz      r0, 0x28(r1)
	stw      r3, 0x148(r31)
	stw      r0, 0x14c(r31)
	lwz      r3, 0x2c(r1)
	lwz      r0, 0x30(r1)
	stw      r3, 0x150(r31)
	stw      r0, 0x154(r31)
	lwz      r3, 0x34(r1)
	lwz      r0, 0x38(r1)
	stw      r3, 0x158(r31)
	stw      r0, 0x15c(r31)
	lwz      r3, 0x3c(r1)
	lwz      r0, 0x40(r1)
	stw      r3, 0x160(r31)
	stw      r0, 0x164(r31)

lbl_80169C14:
	lwz      r0, 0xb4(r1)
	lwz      r31, 0xac(r1)
	mtlr     r0
	addi     r1, r1, 0xb0
	blr
	*/
}

/*
 * --INFO--
 * Address:	80169C28
 * Size:	00027C
 */
void Pellet::doAnimation()
{
	if (!pelletMgr->_3C || isMovieActor()) {
		if (gameSystem != nullptr && gameSystem->_3C & 0x20) {
			update();
		} else {
			if (m_collTree != nullptr) {
				m_collTree->getBoundingSphere(m_lodSphere);
			}
			AILODParm parm;
			updateLOD(parm);
		}

		if (m_pelletSM->getCurrID(this) == 6) {
			_41C.animate(_438);

			SysShape::Model* model  = m_model;
			J3DMtxCalcAnmBase* calc = static_cast<J3DMtxCalcAnmBase*>(_41C.getCalc());

			J3DJoint* joint  = model->m_j3dModel->m_modelData->m_jointTree.m_joints[0];
			joint->m_mtxCalc = calc;
			update_pmotions();
		} else if (m_captureMatrix == nullptr) {
			if (m_pelletView == nullptr && m_model != nullptr && _41C.m_animMgr != nullptr) {
				_41C.animate(_438);

				SysShape::Model* model  = m_model;
				J3DMtxCalcAnmBase* calc = static_cast<J3DMtxCalcAnmBase*>(_41C.getCalc());

				J3DJoint* joint  = model->m_j3dModel->m_modelData->m_jointTree.m_joints[0];
				joint->m_mtxCalc = calc;
				update_pmotions();
			}

			m_pelletPosition  = m_rigid.m_configs[0]._00;
			Vector3f opposite = _2F4 * -1.0f;

			Matrixf matT;
			matT.makeT(opposite);

			Matrixf matQ;
			matQ.makeQ(m_rigid.m_configs[0]._48);

			Matrixf outMat;
			PSMTXConcat(matQ.m_matrix.mtxView, matT.m_matrix.mtxView, outMat.m_matrix.mtxView);
			outMat.setTranslation(m_pelletPosition);

			m_mainMatrix = outMat;

			updateParticlePositions();
		} else {
			return;
		}

		entryShape();
	}
}

/*
 * --INFO--
 * Address:	80169EA4
 * Size:	0000F0
 */
void Pellet::doEntry(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r4, pelletMgr__4Game@sda21(r13)
	lbz      r0, 0x3c(r4)
	cmplwi   r0, 0
	beq      lbl_80169EE0
	lwz      r12, 0(r3)
	lwz      r12, 0xb8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80169F80

lbl_80169EE0:
	lwz      r0, 0x358(r31)
	cmplwi   r0, 0
	bne      lbl_80169F6C
	lbz      r0, 0xd8(r31)
	rlwinm.  r0, r0, 0, 0x1d, 0x1d
	beq      lbl_80169F24
	lwz      r3, 0x174(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x1f8(r12)
	mtctr    r12
	bctrl
	b        lbl_80169F6C

lbl_80169F24:
	lbz      r0, sEntryOpt__Q24Game12BaseHIOParms@sda21(r13)
	cmplwi   r0, 0
	beq      lbl_80169F58
	lwz      r4, gameSystem__4Game@sda21(r13)
	li       r3, 0
	lwz      r0, 0x44(r4)
	cmpwi    r0, 1
	beq      lbl_80169F4C
	cmpwi    r0, 3
	bne      lbl_80169F50

lbl_80169F4C:
	li       r3, 1

lbl_80169F50:
	clrlwi.  r0, r3, 0x18
	beq      lbl_80169F80

lbl_80169F58:
	lwz      r3, 0x174(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl

lbl_80169F6C:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x1d4(r12)
	mtctr    r12
	bctrl

lbl_80169F80:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80169F94
 * Size:	000004
 */
// WEAK - in header
// void Pellet::changeMaterial() { }

/*
 * --INFO--
 * Address:	80169F98
 * Size:	000020
 */
void Pellet::doSetView(int view) { Creature::doSetView(view); }

/*
 * --INFO--
 * Address:	80169FB8
 * Size:	000020
 */
void Pellet::doViewCalc() { Creature::doViewCalc(); }

/*
 * --INFO--
 * Address:	80169FD8
 * Size:	0000DC
 */
void Pellet::theEntry()
{
	SysShape::Model* model = m_model;
	if (model != nullptr) {
		if (m_lod.m_flags & AILOD::FLAG_NEED_SHADOW) {
			model->show();
		} else {
			if (BaseHIOParms::sEntryOpt && !gameSystem->isMultiplayerMode()) {
				return;
			}
			model->hide();
		}
		changeMaterial();
		m_model->m_j3dModel->entry();
		m_model->m_j3dModel->calcDiffTexMtx();
	}
}

/*
 * --INFO--
 * Address:	8016A0B4
 * Size:	00009C
 */
void Pellet::entryShape()
{
	if (m_pelletView == nullptr) {
		if (m_model != nullptr) {
			PSMTXCopy(m_mainMatrix.m_matrix.mtxView, m_model->m_j3dModel->_24);
			m_scale.setTVec(m_model->m_j3dModel->m_modelScale);
			m_model->m_j3dModel->calc();
			m_collTree->update();
		}
	} else {
		m_collTree->update();
	}
}

/*
 * --INFO--
 * Address:	8016A150
 * Size:	000024
 */
void Pellet::getBoundingSphere(Sys::Sphere& sphere) { sphere = m_lodSphere; }

/*
 * --INFO--
 * Address:	8016A174
 * Size:	00003C
 */
void Pellet::getLODSphere(Sys::Sphere& sphere)
{
	sphere.m_position = m_lodSphere.m_position;
	if (m_pelletView == nullptr) {
		sphere.m_radius = m_radius;
	} else {
		sphere.m_radius = m_lodSphere.m_radius;
	}
}

/*
 * --INFO--
 * Address:	8016A1B0
 * Size:	000058
 */
void Pellet::init_pmotions()
{
	int numPMotions = m_config->m_params.m_numPMotions.m_data;
	if (numPMotions > 0) {
		_338[0]        = numPMotions;
		_33C.m_animMgr = _41C.m_animMgr;
		_33C.startAnim(0, nullptr);
	} else {
		_338[0] = 0;
	}
}

/*
 * --INFO--
 * Address:	8016A208
 * Size:	0000B4
 */
void Pellet::update_pmotions(void)
{
	/*
	stwu     r1, -0xa0(r1)
	mflr     r0
	stw      r0, 0xa4(r1)
	stmw     r27, 0x8c(r1)
	mr       r27, r3
	li       r29, 0
	addi     r28, r27, 0x33c
	b        lbl_8016A29C

lbl_8016A228:
	mr       r3, r28
	lfs      f1, lbl_80518910@sda21(r2)
	lwz      r12, 0(r28)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189B8@sda21
	crclr    6
	bl       sprintf
	lwz      r3, 0x174(r27)
	addi     r4, r1, 8
	bl       getJoint__Q28SysShape5ModelFPc
	cmplwi   r3, 0
	beq      lbl_8016A298
	lhz      r30, 0x38(r3)
	mr       r3, r28
	lwz      r12, 0(r28)
	lwz      r31, 0x174(r27)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lwz      r4, 8(r31)
	rlwinm   r0, r30, 2, 0xe, 0x1d
	lwz      r4, 4(r4)
	lwz      r4, 0x28(r4)
	lwzx     r4, r4, r0
	stw      r3, 0x54(r4)

lbl_8016A298:
	addi     r29, r29, 1

lbl_8016A29C:
	lbz      r0, 0x338(r27)
	cmpw     r29, r0
	blt      lbl_8016A228
	lmw      r27, 0x8c(r1)
	lwz      r0, 0xa4(r1)
	mtlr     r0
	addi     r1, r1, 0xa0
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016A2BC
 * Size:	000044
 */
void Pellet::start_pmotions(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lbz      r0, 0x338(r3)
	cmplwi   r0, 0
	beq      lbl_8016A2F0
	cmplwi   r3, 0
	mr       r5, r3
	addi     r3, r3, 0x33c
	beq      lbl_8016A2E8
	addi     r5, r5, 0x314

lbl_8016A2E8:
	li       r4, 1
	bl       startAnim__Q28SysShape8AnimatorFiPQ28SysShape14MotionListener

lbl_8016A2F0:
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	000004
 */
void Pellet::stop_pmotions(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000090
 */
void Pellet::start_carrymotion(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8016A300
 * Size:	00000C
 */
void Pellet::stop_carrymotion(void)
{
	/*
	lfs      f0, lbl_80518914@sda21(r2)
	stfs     f0, 0x438(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016A30C
 * Size:	000054
 */
void Pellet::finish_carrymotion(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lwz      r0, 0x42c(r3)
	cmplwi   r0, 0
	beq      lbl_8016A334
	lbz      r0, 0x434(r3)
	ori      r0, r0, 2
	stb      r0, 0x434(r3)
	b        lbl_8016A350

lbl_8016A334:
	lwz      r3, 0x358(r3)
	cmplwi   r3, 0
	beq      lbl_8016A350
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_8016A350:
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016A360
 * Size:	000088
 */
void Pellet::onKeyEvent(SysShape::KeyEvent const&)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lwz      r0, 0x1c(r4)
	stw      r31, 0xc(r1)
	mr       r31, r3
	cmplwi   r0, 0x3e8
	bne      lbl_8016A3D4
	lbz      r0, 0x434(r31)
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016A3D4
	cmplwi   r31, 0
	mr       r5, r31
	beq      lbl_8016A39C
	addi     r5, r5, 0x314

lbl_8016A39C:
	addi     r3, r31, 0x41c
	li       r4, 0
	bl       startAnim__Q28SysShape8AnimatorFiPQ28SysShape14MotionListener
	lbz      r0, 0x3d0(r31)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_8016A3CC
	lwz      r3, sys@sda21(r13)
	lfs      f1, lbl_80518928@sda21(r2)
	lfs      f0, 0x54(r3)
	fmuls    f0, f1, f0
	stfs     f0, 0x438(r31)
	b        lbl_8016A3D4

lbl_8016A3CC:
	lfs      f0, lbl_80518914@sda21(r2)
	stfs     f0, 0x438(r31)

lbl_8016A3D4:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016A3E8
 * Size:	0000C0
 */
void Pellet::isSlotFree(short)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	extsh    r4, r31
	cmpwi    r4, 0x270f
	stw      r30, 8(r1)
	mr       r30, r3
	bne      lbl_8016A420
	lbz      r0, 0x3f6(r30)
	cntlzw   r0, r0
	srwi     r3, r0, 5
	b        lbl_8016A490

lbl_8016A420:
	extsh.   r0, r31
	li       r3, 0
	blt      lbl_8016A43C
	lha      r0, 0x3f4(r30)
	cmpw     r4, r0
	bge      lbl_8016A43C
	li       r3, 1

lbl_8016A43C:
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016A460
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0xe66
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016A460:
	extsh    r6, r31
	li       r5, 1
	srawi    r3, r6, 3
	subfic   r0, r3, 0xf
	slwi     r4, r3, 3
	add      r3, r30, r0
	subf     r4, r4, r6
	lbz      r0, 0x3e4(r3)
	slw      r3, r5, r4
	and      r0, r3, r0
	cntlzw   r0, r0
	srwi     r3, r0, 5

lbl_8016A490:
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
 * Address:	8016A4A8
 * Size:	00001C
 */
void Pellet::getSpeicalSlot(void)
{
	/*
	lbz      r0, 0x3f6(r3)
	li       r3, 0x270f
	cmplwi   r0, 0
	beq      lbl_8016A4BC
	li       r3, -1

lbl_8016A4BC:
	extsh    r3, r3
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016A4C4
 * Size:	000054
 */
void Pellet::getFreeStickSlot(void)
{
	/*
	lha      r0, 0x3f4(r3)
	li       r7, 0
	li       r6, 1
	mtctr    r0
	cmpwi    r0, 0
	ble      lbl_8016A510

lbl_8016A4DC:
	srawi    r4, r7, 3
	subfic   r0, r4, 0xf
	slwi     r5, r4, 3
	add      r4, r3, r0
	subf     r5, r5, r7
	lbz      r0, 0x3e4(r4)
	slw      r4, r6, r5
	and.     r0, r4, r0
	bne      lbl_8016A508
	extsh    r3, r7
	blr

lbl_8016A508:
	addi     r7, r7, 1
	bdnz     lbl_8016A4DC

lbl_8016A510:
	li       r3, -1
	blr
	*/
}

} // namespace PSM

/*
 * --INFO--
 * Address:	8016A518
 * Size:	000128
 */
void getNearFreeStickSlot__Q24Game6PelletFR10Vector3f(void)
{
	/*
	stwu     r1, -0x40(r1)
	mflr     r0
	stw      r0, 0x44(r1)
	stfd     f31, 0x30(r1)
	psq_st   f31, 56(r1), 0, qr0
	stw      r31, 0x2c(r1)
	stw      r30, 0x28(r1)
	stw      r29, 0x24(r1)
	stw      r28, 0x20(r1)
	lfs      f31, lbl_805189C0@sda21(r2)
	mr       r28, r3
	mr       r29, r4
	li       r31, -1
	li       r30, 0
	b        lbl_8016A604

lbl_8016A554:
	extsh    r6, r30
	li       r5, 1
	srawi    r3, r6, 3
	subfic   r0, r3, 0xf
	slwi     r4, r3, 3
	add      r3, r28, r0
	subf     r4, r4, r6
	lbz      r0, 0x3e4(r3)
	slw      r3, r5, r4
	and.     r0, r3, r0
	bne      lbl_8016A600
	mr       r3, r28
	mr       r4, r30
	lwz      r12, 0(r28)
	addi     r5, r1, 8
	lwz      r12, 0x180(r12)
	mtctr    r12
	bctrl
	lfs      f1, 0xc(r1)
	lfs      f0, 4(r29)
	lfs      f3, 8(r1)
	fsubs    f4, f1, f0
	lfs      f2, 0(r29)
	lfs      f1, 0x10(r1)
	lfs      f0, 8(r29)
	fsubs    f3, f3, f2
	fmuls    f4, f4, f4
	fsubs    f2, f1, f0
	lfs      f0, lbl_80518914@sda21(r2)
	fmadds   f1, f3, f3, f4
	fmuls    f2, f2, f2
	fadds    f1, f2, f1
	fcmpo    cr0, f1, f0
	ble      lbl_8016A5EC
	ble      lbl_8016A5F0
	frsqrte  f0, f1
	fmuls    f1, f0, f1
	b        lbl_8016A5F0

lbl_8016A5EC:
	fmr      f1, f0

lbl_8016A5F0:
	fcmpo    cr0, f1, f31
	bge      lbl_8016A600
	fmr      f31, f1
	mr       r31, r30

lbl_8016A600:
	addi     r30, r30, 1

lbl_8016A604:
	lha      r0, 0x3f4(r28)
	extsh    r3, r30
	cmpw     r3, r0
	blt      lbl_8016A554
	mr       r3, r31
	psq_l    f31, 56(r1), 0, qr0
	lwz      r0, 0x44(r1)
	lfd      f31, 0x30(r1)
	lwz      r31, 0x2c(r1)
	lwz      r30, 0x28(r1)
	lwz      r29, 0x24(r1)
	lwz      r28, 0x20(r1)
	mtlr     r0
	addi     r1, r1, 0x40
	blr
	*/
}

namespace Game {

/*
 * --INFO--
 * Address:	8016A640
 * Size:	0000E8
 */
void Pellet::getRandomFreeStickSlot(void)
{
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stw      r31, 0x2c(r1)
	stw      r30, 0x28(r1)
	mr       r30, r3
	lha      r31, 0x3f4(r3)
	bl       rand
	lis      r4, 0x4330
	xoris    r0, r3, 0x8000
	stw      r0, 0xc(r1)
	xoris    r0, r31, 0x8000
	lfd      f2, lbl_80518930@sda21(r2)
	li       r9, 0x80
	stw      r4, 8(r1)
	li       r3, -1
	lfs      f0, lbl_80518940@sda21(r2)
	li       r10, 0
	lfd      f1, 8(r1)
	li       r6, 1
	stw      r0, 0x14(r1)
	fsubs    f1, f1, f2
	stw      r4, 0x10(r1)
	fdivs    f1, f1, f0
	lfd      f0, 0x10(r1)
	fsubs    f0, f0, f2
	fmuls    f0, f0, f1
	fctiwz   f0, f0
	stfd     f0, 0x18(r1)
	lwz      r8, 0x1c(r1)
	b        lbl_8016A704

lbl_8016A6BC:
	srawi    r4, r7, 3
	subfic   r0, r4, 0xf
	slwi     r5, r4, 3
	add      r4, r30, r0
	subf     r5, r5, r7
	lbz      r0, 0x3e4(r4)
	slw      r4, r6, r5
	and.     r0, r4, r0
	bne      lbl_8016A700
	subf     r0, r8, r7
	srawi    r4, r0, 0x1f
	xor      r0, r4, r0
	subf     r0, r4, r0
	cmpw     r0, r9
	bge      lbl_8016A700
	mr       r9, r0
	mr       r3, r10

lbl_8016A700:
	addi     r10, r10, 1

lbl_8016A704:
	extsh    r7, r10
	cmpw     r7, r31
	blt      lbl_8016A6BC
	lwz      r0, 0x34(r1)
	lwz      r31, 0x2c(r1)
	lwz      r30, 0x28(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016A728
 * Size:	00020C
 */
void Pellet::getPelletGoal(void)
{
	/*
	stwu     r1, -0x40(r1)
	mflr     r0
	stw      r0, 0x44(r1)
	stw      r31, 0x3c(r1)
	stw      r30, 0x38(r1)
	mr       r30, r3
	lwz      r4, gameSystem__4Game@sda21(r13)
	lwz      r0, 0x44(r4)
	cmpwi    r0, 1
	beq      lbl_8016A7AC
	lwz      r12, 0(r3)
	lwz      r12, 0x1f4(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	cmplwi   r0, 3
	beq      lbl_8016A900
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x1f4(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	cmplwi   r0, 2
	beq      lbl_8016A900
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x1f4(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	cmplwi   r0, 4
	beq      lbl_8016A900

lbl_8016A7AC:
	lwz      r0, 0x3f8(r30)
	li       r5, -1
	li       r31, 0
	li       r3, 0
	cmpw     r5, r0
	bge      lbl_8016A7C8
	mr       r5, r0

lbl_8016A7C8:
	lwz      r0, 0x3fc(r30)
	cmpw     r5, r0
	bge      lbl_8016A7D8
	mr       r5, r0

lbl_8016A7D8:
	lwz      r0, 0x400(r30)
	cmpw     r5, r0
	bge      lbl_8016A7E8
	mr       r5, r0

lbl_8016A7E8:
	lwz      r0, 0x3f8(r30)
	addi     r4, r1, 8
	li       r6, 0
	cmpw     r5, r0
	bne      lbl_8016A808
	stw      r6, 8(r1)
	li       r31, 1
	li       r3, 4

lbl_8016A808:
	lwz      r0, 0x3fc(r30)
	li       r6, 1
	cmpw     r5, r0
	bne      lbl_8016A824
	stwx     r6, r4, r3
	addi     r31, r31, 1
	addi     r3, r3, 4

lbl_8016A824:
	lwz      r0, 0x400(r30)
	li       r6, 2
	cmpw     r5, r0
	bne      lbl_8016A83C
	stwx     r6, r4, r3
	addi     r31, r31, 1

lbl_8016A83C:
	bl       rand
	lis      r4, 0x4330
	xoris    r0, r3, 0x8000
	stw      r0, 0x1c(r1)
	xoris    r0, r31, 0x8000
	lfd      f2, lbl_80518930@sda21(r2)
	stw      r4, 0x18(r1)
	lfs      f0, lbl_80518940@sda21(r2)
	lfd      f1, 0x18(r1)
	stw      r0, 0x24(r1)
	fsubs    f1, f1, f2
	stw      r4, 0x20(r1)
	fdivs    f1, f1, f0
	lfd      f0, 0x20(r1)
	fsubs    f0, f0, f2
	fmuls    f0, f0, f1
	fctiwz   f0, f0
	stfd     f0, 0x28(r1)
	lwz      r0, 0x2c(r1)
	cmpw     r0, r31
	blt      lbl_8016A894
	li       r0, 0

lbl_8016A894:
	slwi     r0, r0, 2
	addi     r3, r1, 8
	lwzx     r30, r3, r0
	lwz      r3, mgr__Q24Game9ItemOnyon@sda21(r13)
	mr       r4, r30
	bl       getOnyon__Q34Game9ItemOnyon3MgrFi
	lwz      r4, gameSystem__4Game@sda21(r13)
	mr       r31, r3
	lwz      r0, 0x44(r4)
	cmpwi    r0, 0
	bne      lbl_8016A8D8
	lwz      r3, playData__4Game@sda21(r13)
	mr       r4, r30
	bl       hasBootContainer__Q24Game8PlayDataFi
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016A8D8
	li       r31, 0

lbl_8016A8D8:
	cmplwi   r31, 0
	bne      lbl_8016A918
	lwz      r3, mgr__Q24Game9ItemOnyon@sda21(r13)
	li       r4, 1
	bl       getOnyon__Q34Game9ItemOnyon3MgrFi
	or.      r31, r3, r3
	bne      lbl_8016A918
	lwz      r3, mgr__Q24Game9ItemOnyon@sda21(r13)
	lwz      r31, 0xac(r3)
	b        lbl_8016A918

lbl_8016A900:
	lwz      r3, mgr__Q24Game9ItemOnyon@sda21(r13)
	lwz      r0, 0xb0(r3)
	cmplwi   r0, 0
	mr       r31, r0
	bne      lbl_8016A918
	lwz      r31, 0xac(r3)

lbl_8016A918:
	lwz      r0, 0x44(r1)
	mr       r3, r31
	lwz      r31, 0x3c(r1)
	lwz      r30, 0x38(r1)
	mtlr     r0
	addi     r1, r1, 0x40
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016A934
 * Size:	00003C
 */
void Pellet::getTotalPikmins(void)
{
	/*
	lwz      r5, 0x3f8(r3)
	lwz      r4, 0x3fc(r3)
	lwz      r0, 0x400(r3)
	add      r5, r5, r4
	lwz      r4, 0x404(r3)
	add      r5, r5, r0
	lwz      r0, 0x408(r3)
	add      r5, r5, r4
	lwz      r4, 0x40c(r3)
	add      r5, r5, r0
	lwz      r0, 0x410(r3)
	add      r5, r5, r4
	add      r5, r5, r0
	mr       r3, r5
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016A970
 * Size:	00006C
 */
void Pellet::getTotalCarryPikmins(void)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	mr       r31, r3
	stw      r30, 0x18(r1)
	li       r30, 0
	stw      r29, 0x14(r1)
	li       r29, 0

lbl_8016A994:
	lwz      r3, pikiMgr__4Game@sda21(r13)
	mr       r4, r29
	bl       getColorTransportScale__Q24Game7PikiMgrFi
	lwz      r0, 0x3f8(r31)
	addi     r29, r29, 1
	cmpwi    r29, 7
	addi     r31, r31, 4
	mullw    r0, r0, r3
	add      r30, r30, r0
	blt      lbl_8016A994
	lwz      r0, 0x24(r1)
	mr       r3, r30
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
 * Address:	8016A9DC
 * Size:	000078
 */
void Pellet::getPikmins(int)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	li       r0, 0
	stw      r31, 0xc(r1)
	or.      r31, r4, r4
	stw      r30, 8(r1)
	mr       r30, r3
	blt      lbl_8016AA0C
	cmpwi    r31, 7
	bge      lbl_8016AA0C
	li       r0, 1

lbl_8016AA0C:
	clrlwi.  r0, r0, 0x18
	bne      lbl_8016AA30
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0xf3e
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016AA30:
	slwi     r0, r31, 2
	add      r3, r30, r0
	lwz      r3, 0x3f8(r3)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016AA54
 * Size:	0001D4
 */
void Pellet::onSlotStickStart(Game::Creature*, short)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	mr       r31, r4
	stw      r30, 0x18(r1)
	mr       r30, r3
	stw      r29, 0x14(r1)
	mr       r29, r5
	extsh    r5, r29
	cmpwi    r5, 0x270f
	beq      lbl_8016AB34
	extsh.   r0, r29
	li       r3, 0
	blt      lbl_8016AAA0
	lha      r0, 0x3f4(r30)
	cmpw     r5, r0
	bge      lbl_8016AAA0
	li       r3, 1

lbl_8016AAA0:
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016AAC4
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0xf4d
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016AAC4:
	mr       r3, r30
	mr       r4, r29
	lwz      r12, 0(r30)
	lwz      r12, 0x168(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016AB00
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0xf4e
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016AB00:
	extsh    r6, r29
	cmpwi    r6, 0x80
	bge      lbl_8016AB34
	srawi    r4, r6, 3
	li       r3, 1
	subfic   r0, r4, 0xf
	add      r5, r30, r0
	slwi     r0, r4, 3
	lbz      r4, 0x3e4(r5)
	subf     r0, r0, r6
	slw      r0, r3, r0
	or       r0, r4, r0
	stb      r0, 0x3e4(r5)

lbl_8016AB34:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016ABBC
	lbz      r29, 0x2b8(r31)
	li       r0, 0
	cmpwi    r29, 0
	blt      lbl_8016AB6C
	cmpwi    r29, 7
	bge      lbl_8016AB6C
	li       r0, 1

lbl_8016AB6C:
	clrlwi.  r0, r0, 0x18
	bne      lbl_8016AB90
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0xf55
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016AB90:
	slwi     r0, r29, 2
	mr       r3, r31
	add      r5, r30, r0
	lwz      r4, 0x3f8(r5)
	addi     r0, r4, 1
	stw      r0, 0x3f8(r5)
	bl       getPelletCarryPower__Q24Game4PikiFv
	lfs      f0, 0x418(r30)
	fadds    f0, f0, f1
	stfs     f0, 0x418(r30)
	b        lbl_8016ABC8

lbl_8016ABBC:
	lwz      r3, 0x414(r30)
	addi     r0, r3, 1
	stw      r0, 0x414(r30)

lbl_8016ABC8:
	lwz      r0, 0x3dc(r30)
	cmpwi    r0, 0
	ble      lbl_8016ABD8
	b        lbl_8016ABE0

lbl_8016ABD8:
	lwz      r3, 0x35c(r30)
	lwz      r0, 0x130(r3)

lbl_8016ABE0:
	cmpwi    r0, 1
	beq      lbl_8016AC0C
	li       r0, 5
	cmplwi   r30, 0
	stw      r0, 0x3d4(r30)
	mr       r4, r30
	beq      lbl_8016AC00
	addi     r4, r30, 0x318

lbl_8016AC00:
	lwz      r3, carryInfoMgr@sda21(r13)
	bl       appear__12CarryInfoMgrFP14CarryInfoOwner
	stw      r3, 0x398(r30)

lbl_8016AC0C:
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
 * Address:	8016AC28
 * Size:	0001E8
 */
void Pellet::onSlotStickEnd(Game::Creature*, short)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r6, lbl_8047E318@ha
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	addi     r31, r6, lbl_8047E318@l
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r29, 0x14(r1)
	mr       r29, r3
	stw      r28, 0x10(r1)
	mr       r28, r5
	extsh    r5, r28
	cmpwi    r5, 0x270f
	beq      lbl_8016AD04
	extsh.   r0, r28
	li       r3, 0
	blt      lbl_8016AC80
	lha      r0, 0x3f4(r29)
	cmpw     r5, r0
	bge      lbl_8016AC80
	li       r3, 1

lbl_8016AC80:
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016AC9C
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x3c
	li       r4, 0xf70
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016AC9C:
	mr       r3, r29
	mr       r4, r28
	lwz      r12, 0(r29)
	lwz      r12, 0x168(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016ACD0
	addi     r3, r31, 0x2c
	addi     r5, r31, 0xd0
	li       r4, 0xf74
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016ACD0:
	extsh    r6, r28
	cmpwi    r6, 0x80
	bge      lbl_8016AD04
	srawi    r4, r6, 3
	li       r3, 1
	subfic   r0, r4, 0xf
	add      r5, r29, r0
	slwi     r0, r4, 3
	lbz      r4, 0x3e4(r5)
	subf     r0, r0, r6
	slw      r0, r3, r0
	andc     r0, r4, r0
	stb      r0, 0x3e4(r5)

lbl_8016AD04:
	mr       r3, r30
	lwz      r12, 0(r30)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016AD84
	lbz      r28, 0x2b8(r30)
	li       r0, 0
	cmpwi    r28, 0
	blt      lbl_8016AD3C
	cmpwi    r28, 7
	bge      lbl_8016AD3C
	li       r0, 1

lbl_8016AD3C:
	clrlwi.  r0, r0, 0x18
	bne      lbl_8016AD58
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x3c
	li       r4, 0xf7c
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016AD58:
	slwi     r0, r28, 2
	mr       r3, r30
	add      r5, r29, r0
	lwz      r4, 0x3f8(r5)
	addi     r0, r4, -1
	stw      r0, 0x3f8(r5)
	bl       getPelletCarryPower__Q24Game4PikiFv
	lfs      f0, 0x418(r29)
	fsubs    f0, f0, f1
	stfs     f0, 0x418(r29)
	b        lbl_8016AD90

lbl_8016AD84:
	lwz      r3, 0x414(r29)
	addi     r0, r3, -1
	stw      r0, 0x414(r29)

lbl_8016AD90:
	lwz      r4, 0x3f8(r29)
	lwz      r3, 0x3fc(r29)
	lwz      r0, 0x400(r29)
	add      r4, r4, r3
	lwz      r3, 0x404(r29)
	add      r4, r4, r0
	lwz      r0, 0x408(r29)
	add      r4, r4, r3
	lwz      r3, 0x40c(r29)
	add      r4, r4, r0
	lwz      r0, 0x410(r29)
	add      r4, r4, r3
	add.     r4, r4, r0
	bne      lbl_8016ADF0
	lwz      r3, 0x398(r29)
	cmplwi   r3, 0
	beq      lbl_8016ADE4
	addi     r3, r3, 0x48
	bl       disappear__9CarryInfoFv
	li       r0, 0
	stw      r0, 0x398(r29)

lbl_8016ADE4:
	lwz      r3, 0x334(r29)
	li       r4, 0
	bl       giveup__Q24Game11PelletCarryFUs

lbl_8016ADF0:
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

} // namespace Game

/*
 * --INFO--
 * Address:	........
 * Size:	00018C
 */
void calcStickSlotLocal__Q24Game6PelletFsR10Vector3f(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8016AE10
 * Size:	00021C
 */
void calcStickSlotGlobal__Q24Game6PelletFsR10Vector3f(void)
{
	/*
	stwu     r1, -0x60(r1)
	mflr     r0
	stw      r0, 0x64(r1)
	stw      r31, 0x5c(r1)
	mr       r31, r5
	stw      r30, 0x58(r1)
	mr       r30, r3
	stw      r29, 0x54(r1)
	mr       r29, r4
	extsh    r4, r29
	cmpwi    r4, 0x270f
	bne      lbl_8016AE54
	lfs      f0, lbl_80518914@sda21(r2)
	stfs     f0, 0x14(r1)
	stfs     f0, 0x18(r1)
	stfs     f0, 0x1c(r1)
	b        lbl_8016AFE8

lbl_8016AE54:
	extsh.   r0, r29
	li       r3, 0
	blt      lbl_8016AE70
	lha      r0, 0x3f4(r30)
	cmpw     r4, r0
	bge      lbl_8016AE70
	li       r3, 1

lbl_8016AE70:
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016AE94
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0xfb0
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016AE94:
	lha      r5, 0x3f4(r30)
	lis      r4, 0x4330
	extsh    r0, r29
	lwz      r3, 0x35c(r30)
	xoris    r5, r5, 0x8000
	stw      r4, 0x20(r1)
	xoris    r0, r0, 0x8000
	lfd      f3, lbl_80518930@sda21(r2)
	stw      r5, 0x24(r1)
	lfs      f4, lbl_80518988@sda21(r2)
	lfd      f0, 0x20(r1)
	stw      r0, 0x2c(r1)
	fsubs    f2, f0, f3
	lfs      f1, 0x3e0(r30)
	stw      r4, 0x28(r1)
	lfs      f0, lbl_80518914@sda21(r2)
	fdivs    f4, f4, f2
	lfd      f2, 0x28(r1)
	lfs      f5, 0xb0(r3)
	fsubs    f2, f2, f3
	fmadds   f4, f4, f2, f1
	fmr      f1, f4
	fcmpo    cr0, f4, f0
	bge      lbl_8016AEF8
	fneg     f1, f4

lbl_8016AEF8:
	lfs      f2, lbl_8051898C@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	lfs      f0, lbl_80518914@sda21(r2)
	addi     r4, r3, sincosTable___5JMath@l
	fmuls    f1, f1, f2
	fcmpo    cr0, f4, f0
	fctiwz   f0, f1
	stfd     f0, 0x30(r1)
	lwz      r0, 0x34(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r4, r0
	lfs      f0, 4(r3)
	fmuls    f3, f5, f0
	bge      lbl_8016AF54
	lfs      f0, lbl_80518990@sda21(r2)
	fmuls    f0, f4, f0
	fctiwz   f0, f0
	stfd     f0, 0x38(r1)
	lwz      r0, 0x3c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r4, r0
	fneg     f0, f0
	b        lbl_8016AF6C

lbl_8016AF54:
	fmuls    f0, f4, f2
	fctiwz   f0, f0
	stfd     f0, 0x40(r1)
	lwz      r0, 0x44(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r4, r0

lbl_8016AF6C:
	fmuls    f1, f5, f0
	lfs      f0, lbl_80518914@sda21(r2)
	stfs     f3, 0x1c(r1)
	mr       r3, r30
	stfs     f1, 0x14(r1)
	stfs     f0, 0x18(r1)
	bl       getFace__Q24Game6PelletFv
	lwz      r4, 0x35c(r30)
	cmpwi    r3, 0
	lfs      f2, lbl_80518918@sda21(r2)
	lfs      f1, 0xc0(r4)
	lfs      f0, lbl_80518910@sda21(r2)
	fmadds   f1, f2, f1, f0
	bne      lbl_8016AFCC
	fneg     f0, f1
	stfs     f0, 0x18(r1)
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_8016AFE8
	frsp     f1, f0
	lfs      f0, lbl_80518938@sda21(r2)
	fsubs    f0, f1, f0
	stfs     f0, 0x18(r1)
	b        lbl_8016AFE8

lbl_8016AFCC:
	stfs     f1, 0x18(r1)
	lbz      r0, 0x3d0(r30)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_8016AFE8
	lfs      f0, lbl_80518938@sda21(r2)
	fadds    f0, f1, f0
	stfs     f0, 0x18(r1)

lbl_8016AFE8:
	addi     r3, r30, 0x138
	addi     r4, r1, 0x14
	addi     r5, r1, 8
	bl       PSMTXMultVec
	lfs      f1, 0xc(r1)
	lfs      f2, 0x10(r1)
	lfs      f0, 8(r1)
	stfs     f0, 0(r31)
	stfs     f1, 4(r31)
	stfs     f2, 8(r31)
	lwz      r31, 0x5c(r1)
	lwz      r30, 0x58(r1)
	lwz      r29, 0x54(r1)
	lwz      r0, 0x64(r1)
	mtlr     r0
	addi     r1, r1, 0x60
	blr
	*/
}

namespace Game {

/*
 * --INFO--
 * Address:	8016B02C
 * Size:	000068
 */
void Pellet::getFace(void)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	lbz      r0, 0x364(r3)
	cmplwi   r0, 2
	bne      lbl_8016B04C
	li       r3, 0
	b        lbl_8016B084

lbl_8016B04C:
	addi     r4, r1, 8
	bl       "getYVector__Q24Game8CreatureFR10Vector3<f>"
	lfs      f1, 0xc(r1)
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f1, f0
	ble      lbl_8016B06C
	li       r3, 0
	b        lbl_8016B084

lbl_8016B06C:
	lfs      f0, lbl_805189C4@sda21(r2)
	fcmpo    cr0, f1, f0
	bge      lbl_8016B080
	li       r3, 1
	b        lbl_8016B084

lbl_8016B080:
	li       r3, 2

lbl_8016B084:
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016B094
 * Size:	0002AC
 */
void Pellet::startPick(void)
{
	/*
	stwu     r1, -0x40(r1)
	mflr     r0
	stw      r0, 0x44(r1)
	stw      r31, 0x3c(r1)
	mr       r31, r3
	stw      r30, 0x38(r1)
	lbz      r0, 0x3d0(r3)
	clrlwi.  r0, r0, 0x1f
	bne      lbl_8016B328
	lwz      r4, 0x35c(r31)
	lhz      r0, 0x244(r4)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_8016B0D8
	lwz      r12, 0(r3)
	lwz      r12, 0x1dc(r12)
	mtctr    r12
	bctrl

lbl_8016B0D8:
	lwz      r0, 0x42c(r31)
	cmplwi   r0, 0
	beq      lbl_8016B124
	lbz      r0, 0x434(r31)
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	bne      lbl_8016B140
	cmplwi   r31, 0
	mr       r5, r31
	beq      lbl_8016B100
	addi     r5, r31, 0x314

lbl_8016B100:
	addi     r3, r31, 0x41c
	li       r4, 0
	bl       startAnim__Q28SysShape8AnimatorFiPQ28SysShape14MotionListener
	lwz      r3, sys@sda21(r13)
	lfs      f1, lbl_80518928@sda21(r2)
	lfs      f0, 0x54(r3)
	fmuls    f0, f1, f0
	stfs     f0, 0x438(r31)
	b        lbl_8016B140

lbl_8016B124:
	lwz      r3, 0x358(r31)
	cmplwi   r3, 0
	beq      lbl_8016B140
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl

lbl_8016B140:
	lbz      r0, 0x364(r31)
	cmplwi   r0, 2
	beq      lbl_8016B158
	mr       r3, r31
	addi     r4, r1, 0x20
	bl       "getYVector__Q24Game8CreatureFR10Vector3<f>"

lbl_8016B158:
	mr       r3, r31
	addi     r4, r1, 0x2c
	bl       "getYVector__Q24Game8CreatureFR10Vector3<f>"
	lfs      f3, 0x34(r1)
	lfs      f2, lbl_80518938@sda21(r2)
	lfs      f1, 0x30(r1)
	lfs      f0, 0x2c(r1)
	fmuls    f3, f3, f2
	fmuls    f1, f1, f2
	fmuls    f0, f0, f2
	stfs     f3, 0x34(r1)
	stfs     f0, 0x2c(r1)
	stfs     f1, 0x30(r1)
	lbz      r0, 0x364(r31)
	cmplwi   r0, 2
	bne      lbl_8016B1A0
	li       r0, 0
	b        lbl_8016B1DC

lbl_8016B1A0:
	mr       r3, r31
	addi     r4, r1, 0x14
	bl       "getYVector__Q24Game8CreatureFR10Vector3<f>"
	lfs      f1, 0x18(r1)
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f1, f0
	ble      lbl_8016B1C4
	li       r0, 0
	b        lbl_8016B1DC

lbl_8016B1C4:
	lfs      f0, lbl_805189C4@sda21(r2)
	fcmpo    cr0, f1, f0
	bge      lbl_8016B1D8
	li       r0, 1
	b        lbl_8016B1DC

lbl_8016B1D8:
	li       r0, 2

lbl_8016B1DC:
	cmpwi    r0, 0
	bne      lbl_8016B218
	lfs      f1, 0x1b0(r31)
	lfs      f0, 0x2c(r1)
	fadds    f0, f1, f0
	stfs     f0, 0x1b0(r31)
	lfs      f1, 0x1b4(r31)
	lfs      f0, 0x30(r1)
	fadds    f0, f1, f0
	stfs     f0, 0x1b4(r31)
	lfs      f1, 0x1b8(r31)
	lfs      f0, 0x34(r1)
	fadds    f0, f1, f0
	stfs     f0, 0x1b8(r31)
	b        lbl_8016B248

lbl_8016B218:
	lfs      f1, 0x1b0(r31)
	lfs      f0, 0x2c(r1)
	fsubs    f0, f1, f0
	stfs     f0, 0x1b0(r31)
	lfs      f1, 0x1b4(r31)
	lfs      f0, 0x30(r1)
	fsubs    f0, f1, f0
	stfs     f0, 0x1b4(r31)
	lfs      f1, 0x1b8(r31)
	lfs      f0, 0x34(r1)
	fsubs    f0, f1, f0
	stfs     f0, 0x1b8(r31)

lbl_8016B248:
	lwz      r30, 0x178(r31)
	b        lbl_8016B2D0

lbl_8016B250:
	lbz      r0, 0x364(r31)
	cmplwi   r0, 2
	bne      lbl_8016B264
	li       r0, 0
	b        lbl_8016B2A0

lbl_8016B264:
	mr       r3, r31
	addi     r4, r1, 8
	bl       "getYVector__Q24Game8CreatureFR10Vector3<f>"
	lfs      f1, 0xc(r1)
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f1, f0
	ble      lbl_8016B288
	li       r0, 0
	b        lbl_8016B2A0

lbl_8016B288:
	lfs      f0, lbl_805189C4@sda21(r2)
	fcmpo    cr0, f1, f0
	bge      lbl_8016B29C
	li       r0, 1
	b        lbl_8016B2A0

lbl_8016B29C:
	li       r0, 2

lbl_8016B2A0:
	cmpwi    r0, 0
	bne      lbl_8016B2BC
	lfs      f1, 4(r30)
	lfs      f0, lbl_80518938@sda21(r2)
	fsubs    f0, f1, f0
	stfs     f0, 4(r30)
	b        lbl_8016B2CC

lbl_8016B2BC:
	lfs      f1, 4(r30)
	lfs      f0, lbl_80518938@sda21(r2)
	fadds    f0, f1, f0
	stfs     f0, 4(r30)

lbl_8016B2CC:
	lwz      r30, 0x1c(r30)

lbl_8016B2D0:
	cmplwi   r30, 0
	bne      lbl_8016B250
	lbz      r0, 0x3d0(r31)
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016B2FC
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x210(r12)
	mtctr    r12
	bctrl
	b        lbl_8016B31C

lbl_8016B2FC:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x20c(r12)
	mtctr    r12
	bctrl
	lbz      r0, 0x3d0(r31)
	ori      r0, r0, 2
	stb      r0, 0x3d0(r31)

lbl_8016B31C:
	lbz      r0, 0x3d0(r31)
	ori      r0, r0, 1
	stb      r0, 0x3d0(r31)

lbl_8016B328:
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
 * Address:	8016B340
 * Size:	000004
 */
// WEAK - in header
// void Pellet::sound_otakaraEventRestart() { }

/*
 * --INFO--
 * Address:	8016B344
 * Size:	00017C
 */
void Pellet::endPick(bool)
{
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stw      r31, 0x2c(r1)
	mr       r31, r3
	stw      r30, 0x28(r1)
	mr       r30, r4
	lbz      r0, 0x3d0(r3)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_8016B4A8
	lwz      r3, 0x334(r31)
	bl       reset__Q24Game11PelletCarryFv
	li       r0, 5
	mr       r3, r31
	stw      r0, 0x3d4(r31)
	lwz      r12, 0(r31)
	lwz      r12, 0x214(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r30, 0x18
	bne      lbl_8016B3F4
	lwz      r0, 0x42c(r31)
	cmplwi   r0, 0
	beq      lbl_8016B3B4
	lbz      r0, 0x434(r31)
	ori      r0, r0, 2
	stb      r0, 0x434(r31)
	b        lbl_8016B3D0

lbl_8016B3B4:
	lwz      r3, 0x358(r31)
	cmplwi   r3, 0
	beq      lbl_8016B3D0
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_8016B3D0:
	lwz      r3, 0x35c(r31)
	lhz      r0, 0x244(r3)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_8016B3F4
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x1e0(r12)
	mtctr    r12
	bctrl

lbl_8016B3F4:
	lbz      r0, 0x3d0(r31)
	rlwinm   r0, r0, 0, 0x18, 0x1e
	stb      r0, 0x3d0(r31)
	lbz      r0, 0x364(r31)
	cmplwi   r0, 2
	beq      lbl_8016B418
	mr       r3, r31
	addi     r4, r1, 0x14
	bl       "getYVector__Q24Game8CreatureFR10Vector3<f>"

lbl_8016B418:
	lwz      r30, 0x178(r31)
	b        lbl_8016B4A0

lbl_8016B420:
	lbz      r0, 0x364(r31)
	cmplwi   r0, 2
	bne      lbl_8016B434
	li       r0, 0
	b        lbl_8016B470

lbl_8016B434:
	mr       r3, r31
	addi     r4, r1, 8
	bl       "getYVector__Q24Game8CreatureFR10Vector3<f>"
	lfs      f1, 0xc(r1)
	lfs      f0, lbl_80518914@sda21(r2)
	fcmpo    cr0, f1, f0
	ble      lbl_8016B458
	li       r0, 0
	b        lbl_8016B470

lbl_8016B458:
	lfs      f0, lbl_805189C4@sda21(r2)
	fcmpo    cr0, f1, f0
	bge      lbl_8016B46C
	li       r0, 1
	b        lbl_8016B470

lbl_8016B46C:
	li       r0, 2

lbl_8016B470:
	cmpwi    r0, 0
	bne      lbl_8016B48C
	lfs      f1, 4(r30)
	lfs      f0, lbl_80518938@sda21(r2)
	fadds    f0, f1, f0
	stfs     f0, 4(r30)
	b        lbl_8016B49C

lbl_8016B48C:
	lfs      f1, 4(r30)
	lfs      f0, lbl_80518938@sda21(r2)
	fsubs    f0, f1, f0
	stfs     f0, 4(r30)

lbl_8016B49C:
	lwz      r30, 0x1c(r30)

lbl_8016B4A0:
	cmplwi   r30, 0
	bne      lbl_8016B420

lbl_8016B4A8:
	lwz      r0, 0x34(r1)
	lwz      r31, 0x2c(r1)
	lwz      r30, 0x28(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016B4C0
 * Size:	000004
 */
// WEAK - in header
// void Pellet::sound_otakaraEventStop() { }

/*
 * --INFO--
 * Address:	8016B4C4
 * Size:	00000C
 */
void Pellet::clearDiscoverDisable(void)
{
	// Generated from stb r0, 0x32D(r3)
	_32D = 0;
}

/*
 * --INFO--
 * Address:	8016B4D0
 * Size:	000008
 */
void Pellet::startDiscoverDisable(unsigned char a1)
{
	// Generated from stb r4, 0x32D(r3)
	_32D = a1;
}

/*
 * --INFO--
 * Address:	8016B4D8
 * Size:	000018
 */
void Pellet::updateDiscoverDisable(void)
{
	/*
	lbz      r4, 0x32d(r3)
	cmplwi   r4, 0
	beqlr
	addi     r0, r4, -1
	stb      r0, 0x32d(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016B4F0
 * Size:	00002C
 */
void Pellet::discoverDisabled(void)
{
	/*
	lwz      r4, gameSystem__4Game@sda21(r13)
	lwz      r0, 0x44(r4)
	cmpwi    r0, 0
	bne      lbl_8016B514
	lbz      r3, 0x32d(r3)
	neg      r0, r3
	or       r0, r0, r3
	srwi     r3, r0, 0x1f
	blr

lbl_8016B514:
	li       r3, 0
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016B51C
 * Size:	00002C
 */
void Pellet::doSave(Stream&)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lbz      r0, 0x3c4(r3)
	mr       r3, r4
	mr       r4, r0
	bl       writeByte__6StreamFUc
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016B548
 * Size:	0001DC
 */
void Pellet::doLoad(Stream&)
{
	/*
	stwu     r1, -0xa0(r1)
	mflr     r0
	stw      r0, 0xa4(r1)
	stfd     f31, 0x90(r1)
	psq_st   f31, 152(r1), 0, qr0
	stfd     f30, 0x80(r1)
	psq_st   f30, 136(r1), 0, qr0
	stfd     f29, 0x70(r1)
	psq_st   f29, 120(r1), 0, qr0
	stw      r31, 0x6c(r1)
	stw      r30, 0x68(r1)
	stw      r29, 0x64(r1)
	stw      r28, 0x60(r1)
	mr       r31, r3
	mr       r3, r4
	bl       readByte__6StreamFv
	clrlwi   r5, r3, 0x18
	mr       r4, r31
	neg      r0, r5
	addi     r3, r1, 0xc
	or       r0, r0, r5
	srwi     r0, r0, 0x1f
	stb      r0, 0x3c4(r31)
	lwz      r12, 0(r31)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f29, 0xc(r1)
	li       r0, 0
	lfs      f31, 0x10(r1)
	addi     r4, r1, 0x3c
	lfs      f30, 0x14(r1)
	lfs      f0, lbl_80518994@sda21(r2)
	stfs     f29, 0x3c(r1)
	lwz      r3, mapMgr__4Game@sda21(r13)
	stfs     f31, 0x40(r1)
	stfs     f30, 0x44(r1)
	stw      r0, 0x48(r1)
	stb      r0, 0x4c(r1)
	stfs     f0, 0x50(r1)
	lwz      r3, 8(r3)
	bl       getNearestWayPoint__Q24Game8RouteMgrFRQ24Game11WPSearchArg
	mr       r30, r3
	li       r29, 0
	li       r28, 0

lbl_8016B5FC:
	lwz      r3, mgr__Q24Game9ItemOnyon@sda21(r13)
	mr       r4, r28
	bl       getOnyon__Q34Game9ItemOnyon3MgrFi
	cmplwi   r3, 0
	beq      lbl_8016B620
	lwz      r0, 0x23c(r3)
	cmplw    r30, r0
	bne      lbl_8016B620
	li       r29, 1

lbl_8016B620:
	addi     r28, r28, 1
	cmpwi    r28, 3
	blt      lbl_8016B5FC
	lwz      r3, mgr__Q24Game9ItemOnyon@sda21(r13)
	lwz      r3, 0xb0(r3)
	lwz      r0, 0x23c(r3)
	cmplw    r0, r30
	bne      lbl_8016B644
	li       r29, 1

lbl_8016B644:
	clrlwi.  r0, r29, 0x18
	beq      lbl_8016B6EC
	lis      r4, "__vt__27Condition<Q24Game8WayPoint>"@ha
	lis      r3, __vt__Q24Game11WPCondition@ha
	addi     r0, r4, "__vt__27Condition<Q24Game8WayPoint>"@l
	lfs      f0, lbl_80518994@sda21(r2)
	stw      r0, 8(r1)
	addi     r0, r3, __vt__Q24Game11WPCondition@l
	lis      r3, __vt__13WPExcludeSpot@ha
	addi     r5, r1, 8
	stw      r0, 8(r1)
	addi     r4, r3, __vt__13WPExcludeSpot@l
	li       r0, 0
	lwz      r3, mapMgr__4Game@sda21(r13)
	stw      r4, 8(r1)
	addi     r4, r1, 0x24
	stfs     f29, 0x24(r1)
	stfs     f31, 0x28(r1)
	stfs     f30, 0x2c(r1)
	stw      r5, 0x30(r1)
	stb      r0, 0x34(r1)
	stfs     f0, 0x38(r1)
	lwz      r3, 8(r3)
	bl       getNearestWayPoint__Q24Game8RouteMgrFRQ24Game11WPSearchArg
	cmplwi   r3, 0
	beq      lbl_8016B6EC
	lfs      f2, 0x50(r3)
	addi     r4, r1, 0x18
	lfs      f3, 0x54(r3)
	li       r5, 0
	lfs      f0, 0x4c(r3)
	mr       r3, r31
	lfs      f1, lbl_80518918@sda21(r2)
	stfs     f0, 0x18(r1)
	stfs     f2, 0x1c(r1)
	stfs     f3, 0x20(r1)
	lwz      r6, 0x35c(r31)
	lfs      f0, 0xc0(r6)
	fmuls    f0, f1, f0
	fadds    f0, f2, f0
	stfs     f0, 0x1c(r1)
	bl       "setPosition__Q24Game8CreatureFR10Vector3<f>b"

lbl_8016B6EC:
	psq_l    f31, 152(r1), 0, qr0
	lfd      f31, 0x90(r1)
	psq_l    f30, 136(r1), 0, qr0
	lfd      f30, 0x80(r1)
	psq_l    f29, 120(r1), 0, qr0
	lfd      f29, 0x70(r1)
	lwz      r31, 0x6c(r1)
	lwz      r30, 0x68(r1)
	lwz      r29, 0x64(r1)
	lwz      r0, 0xa4(r1)
	lwz      r28, 0x60(r1)
	mtlr     r0
	addi     r1, r1, 0xa0
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016B724
 * Size:	0000F4
 */
void Pellet::onStartCapture(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	lfs      f0, lbl_80518914@sda21(r2)
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r3, 0xb8(r3)
	lfs      f1, 0xc(r3)
	lfs      f2, 0x1c(r3)
	lfs      f3, 0x2c(r3)
	stfs     f0, 0x1bc(r31)
	stfs     f0, 0x1c0(r31)
	stfs     f0, 0x1c4(r31)
	stfs     f1, 0x1b0(r31)
	stfs     f2, 0x1b4(r31)
	stfs     f3, 0x1b8(r31)
	stfs     f1, 0x444(r31)
	stfs     f2, 0x448(r31)
	stfs     f3, 0x44c(r31)
	stfs     f1, 0x3ac(r31)
	stfs     f2, 0x3b0(r31)
	stfs     f3, 0x3b4(r31)
	lwz      r0, 0x174(r31)
	cmplwi   r0, 0
	beq      lbl_8016B7F0
	addi     r3, r31, 0x138
	addi     r4, r31, 0x3ac
	bl       "makeT__7MatrixfFR10Vector3<f>"
	lwz      r4, 0x174(r31)
	addi     r3, r31, 0x138
	lwz      r4, 8(r4)
	addi     r4, r4, 0x24
	bl       PSMTXCopy
	lwz      r3, 0x174(r31)
	lfs      f0, 0x168(r31)
	lwz      r3, 8(r3)
	stfs     f0, 0x18(r3)
	lfs      f0, 0x16c(r31)
	stfs     f0, 0x1c(r3)
	lfs      f0, 0x170(r31)
	stfs     f0, 0x20(r3)
	lwz      r3, 0x174(r31)
	lwz      r3, 8(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0x114(r31)
	cmplwi   r3, 0
	beq      lbl_8016B7F0
	bl       update__8CollTreeFv

lbl_8016B7F0:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x1e0(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	00001C
 */
void Pellet::getCurrentBuryDepth(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8016B818
 * Size:	000110
 */
void Pellet::onUpdateCapture(Matrixf&)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	mr       r30, r3
	lwz      r0, 0x42c(r3)
	cmplwi   r0, 0
	beq      lbl_8016B854
	addi     r3, r30, 0x41c
	lfs      f1, lbl_80518914@sda21(r2)
	lwz      r12, 0x41c(r30)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl

lbl_8016B854:
	lwz      r31, 0x174(r30)
	cmplwi   r31, 0
	beq      lbl_8016B888
	addi     r3, r30, 0x41c
	lwz      r12, 0x41c(r30)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lwz      r4, 8(r31)
	lwz      r4, 4(r4)
	lwz      r4, 0x28(r4)
	lwz      r4, 0(r4)
	stw      r3, 0x54(r4)

lbl_8016B888:
	lwz      r0, 0x358(r30)
	cmplwi   r0, 0
	bne      lbl_8016B8F4
	lwz      r3, 0x174(r30)
	cmplwi   r3, 0
	beq      lbl_8016B8FC
	lwz      r4, 8(r3)
	addi     r3, r30, 0x138
	addi     r4, r4, 0x24
	bl       PSMTXCopy
	lwz      r3, 0x174(r30)
	lfs      f0, 0x168(r30)
	lwz      r3, 8(r3)
	stfs     f0, 0x18(r3)
	lfs      f0, 0x16c(r30)
	stfs     f0, 0x1c(r3)
	lfs      f0, 0x170(r30)
	stfs     f0, 0x20(r3)
	lwz      r3, 0x174(r30)
	lwz      r3, 8(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0x114(r30)
	bl       update__8CollTreeFv
	b        lbl_8016B8FC

lbl_8016B8F4:
	lwz      r3, 0x114(r30)
	bl       update__8CollTreeFv

lbl_8016B8FC:
	lbz      r0, 0x32c(r30)
	cmplwi   r0, 0
	bne      lbl_8016B910
	li       r0, 0x5a
	stb      r0, 0x32d(r30)

lbl_8016B910:
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
 * Address:	8016B928
 * Size:	000098
 */
void Pellet::onEndCapture(void)
{
	/*
	stwu     r1, -0x40(r1)
	mflr     r0
	stw      r0, 0x44(r1)
	addi     r4, r1, 8
	stw      r31, 0x3c(r1)
	mr       r31, r3
	addi     r3, r31, 0x138
	bl       PSMTXCopy
	li       r0, 1
	mr       r3, r31
	stb      r0, 0x3c4(r31)
	lwz      r12, 0(r31)
	lwz      r12, 0x1dc(r12)
	mtctr    r12
	bctrl
	mr       r3, r31
	addi     r4, r31, 0x1b0
	li       r5, 0
	bl       "setPosition__Q24Game8CreatureFR10Vector3<f>b"
	mr       r3, r31
	addi     r4, r31, 0x3ac
	lwz      r12, 0(r31)
	lwz      r12, 0x1fc(r12)
	mtctr    r12
	bctrl
	lbz      r0, 0x364(r31)
	cmplwi   r0, 2
	bne      lbl_8016B9A0
	addi     r3, r1, 8
	bl       PSMTXIdentity

lbl_8016B9A0:
	mr       r3, r31
	addi     r4, r1, 8
	bl       setOrientation__Q24Game6PelletFR7Matrixf
	lwz      r0, 0x44(r1)
	lwz      r31, 0x3c(r1)
	mtlr     r0
	addi     r1, r1, 0x40
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016B9C0
 * Size:	000270
 */
BasePelletMgr::BasePelletMgr(Game::PelletList::cKind)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	extsh.   r0, r4
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r30, r3
	stw      r29, 0x14(r1)
	mr       r29, r5
	beq      lbl_8016B9F0
	addi     r0, r30, 0x54
	stw      r0, 4(r30)

lbl_8016B9F0:
	lis      r4, __vt__16GenericObjectMgr@ha
	lis      r3, __vt__Q24Game13BasePelletMgr@ha
	addi     r0, r4, __vt__16GenericObjectMgr@l
	addi     r31, r30, 0x18
	stw      r0, 0(r30)
	addi     r0, r3, __vt__Q24Game13BasePelletMgr@l
	mr       r3, r31
	stw      r0, 0(r30)
	bl       "__ct__24MonoObjectMgr<8CollPart>Fv"
	lis      r4, __vt__11CollPartMgr@ha
	mr       r3, r29
	addi     r4, r4, __vt__11CollPartMgr@l
	stw      r4, 0(r31)
	addi     r0, r4, 0x2c
	stw      r0, 0x1c(r31)
	bl       getConfigList__Q34Game10PelletList3MgrFQ34Game10PelletList5cKind
	stw      r3, 8(r30)
	lwz      r3, 8(r30)
	lwz      r31, 0x18(r3)
	slwi     r29, r31, 2
	stw      r31, 0x50(r30)
	mr       r3, r29
	bl       __nwa__FUl
	stw      r3, 0xc(r30)
	mr       r3, r29
	bl       __nwa__FUl
	stw      r3, 0x10(r30)
	mr       r3, r29
	bl       __nwa__FUl
	stw      r3, 0x14(r30)
	mr       r3, r31
	bl       __nwa__FUl
	stw      r3, 0x4c(r30)
	li       r5, 0
	li       r4, 1
	li       r0, 0
	mtctr    r31
	cmpwi    r31, 0
	ble      lbl_8016BAB4

lbl_8016BA8C:
	lbz      r3, mDebug__Q24Game9PelletMgr@sda21(r13)
	cmplwi   r3, 0
	beq      lbl_8016BAA4
	lwz      r3, 0x4c(r30)
	stbx     r4, r3, r5
	b        lbl_8016BAAC

lbl_8016BAA4:
	lwz      r3, 0x4c(r30)
	stbx     r0, r3, r5

lbl_8016BAAC:
	addi     r5, r5, 1
	bdnz     lbl_8016BA8C

lbl_8016BAB4:
	cmpwi    r31, 0
	li       r4, 0
	ble      lbl_8016BC08
	cmpwi    r31, 8
	addi     r5, r31, -8
	ble      lbl_8016BBD0
	addi     r0, r5, 7
	li       r3, 0
	srwi     r0, r0, 3
	mtctr    r0
	cmpwi    r5, 0
	ble      lbl_8016BBD0

lbl_8016BAE4:
	lwz      r5, 0xc(r30)
	li       r0, 0
	addi     r12, r3, 4
	addi     r11, r3, 8
	stwx     r0, r5, r3
	addi     r10, r3, 0xc
	addi     r9, r3, 0x10
	addi     r8, r3, 0x14
	lwz      r5, 0x10(r30)
	addi     r7, r3, 0x18
	addi     r6, r3, 0x1c
	addi     r4, r4, 8
	stwx     r0, r5, r3
	lwz      r5, 0x14(r30)
	stwx     r0, r5, r3
	addi     r3, r3, 0x20
	lwz      r5, 0xc(r30)
	stwx     r0, r5, r12
	lwz      r5, 0x10(r30)
	stwx     r0, r5, r12
	lwz      r5, 0x14(r30)
	stwx     r0, r5, r12
	lwz      r5, 0xc(r30)
	stwx     r0, r5, r11
	lwz      r5, 0x10(r30)
	stwx     r0, r5, r11
	lwz      r5, 0x14(r30)
	stwx     r0, r5, r11
	lwz      r5, 0xc(r30)
	stwx     r0, r5, r10
	lwz      r5, 0x10(r30)
	stwx     r0, r5, r10
	lwz      r5, 0x14(r30)
	stwx     r0, r5, r10
	lwz      r5, 0xc(r30)
	stwx     r0, r5, r9
	lwz      r5, 0x10(r30)
	stwx     r0, r5, r9
	lwz      r5, 0x14(r30)
	stwx     r0, r5, r9
	lwz      r5, 0xc(r30)
	stwx     r0, r5, r8
	lwz      r5, 0x10(r30)
	stwx     r0, r5, r8
	lwz      r5, 0x14(r30)
	stwx     r0, r5, r8
	lwz      r5, 0xc(r30)
	stwx     r0, r5, r7
	lwz      r5, 0x10(r30)
	stwx     r0, r5, r7
	lwz      r5, 0x14(r30)
	stwx     r0, r5, r7
	lwz      r5, 0xc(r30)
	stwx     r0, r5, r6
	lwz      r5, 0x10(r30)
	stwx     r0, r5, r6
	lwz      r5, 0x14(r30)
	stwx     r0, r5, r6
	bdnz     lbl_8016BAE4

lbl_8016BBD0:
	subf     r0, r4, r31
	slwi     r6, r4, 2
	li       r5, 0
	mtctr    r0
	cmpw     r4, r31
	bge      lbl_8016BC08

lbl_8016BBE8:
	lwz      r3, 0xc(r30)
	stwx     r5, r3, r6
	lwz      r3, 0x10(r30)
	stwx     r5, r3, r6
	lwz      r3, 0x14(r30)
	stwx     r5, r3, r6
	addi     r6, r6, 4
	bdnz     lbl_8016BBE8

lbl_8016BC08:
	li       r0, 0
	mr       r3, r30
	stw      r0, 0x48(r30)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

} // namespace Game

/*
 * --INFO--
 * Address:	8016BC30
 * Size:	0000B8
 */
CollPartMgr::~CollPartMgr()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8016BCCC
	lis      r4, __vt__11CollPartMgr@ha
	addi     r4, r4, __vt__11CollPartMgr@l
	stw      r4, 0(r30)
	addi     r0, r4, 0x2c
	stw      r0, 0x1c(r30)
	beq      lbl_8016BCBC
	lis      r4, "__vt__24MonoObjectMgr<8CollPart>"@ha
	addi     r4, r4, "__vt__24MonoObjectMgr<8CollPart>"@l
	stw      r4, 0(r30)
	addi     r0, r4, 0x2c
	stw      r0, 0x1c(r30)
	beq      lbl_8016BCBC
	lis      r4, "__vt__20ObjectMgr<8CollPart>"@ha
	addi     r4, r4, "__vt__20ObjectMgr<8CollPart>"@l
	stw      r4, 0(r30)
	addi     r0, r4, 0x2c
	stw      r0, 0x1c(r30)
	beq      lbl_8016BCBC
	lis      r4, "__vt__20Container<8CollPart>"@ha
	addi     r0, r4, "__vt__20Container<8CollPart>"@l
	stw      r0, 0(r30)
	beq      lbl_8016BCBC
	lis      r5, __vt__16GenericContainer@ha
	li       r4, 0
	addi     r0, r5, __vt__16GenericContainer@l
	stw      r0, 0(r30)
	bl       __dt__5CNodeFv

lbl_8016BCBC:
	extsh.   r0, r31
	ble      lbl_8016BCCC
	mr       r3, r30
	bl       __dl__FPv

lbl_8016BCCC:
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
 * Address:	8016BCE8
 * Size:	0000A0
 */
void MonoObjectMgr<CollPart>::~MonoObjectMgr()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8016BD6C
	lis      r4, "__vt__24MonoObjectMgr<8CollPart>"@ha
	addi     r4, r4, "__vt__24MonoObjectMgr<8CollPart>"@l
	stw      r4, 0(r30)
	addi     r0, r4, 0x2c
	stw      r0, 0x1c(r30)
	beq      lbl_8016BD5C
	lis      r4, "__vt__20ObjectMgr<8CollPart>"@ha
	addi     r4, r4, "__vt__20ObjectMgr<8CollPart>"@l
	stw      r4, 0(r30)
	addi     r0, r4, 0x2c
	stw      r0, 0x1c(r30)
	beq      lbl_8016BD5C
	lis      r4, "__vt__20Container<8CollPart>"@ha
	addi     r0, r4, "__vt__20Container<8CollPart>"@l
	stw      r0, 0(r30)
	beq      lbl_8016BD5C
	lis      r5, __vt__16GenericContainer@ha
	li       r4, 0
	addi     r0, r5, __vt__16GenericContainer@l
	stw      r0, 0(r30)
	bl       __dt__5CNodeFv

lbl_8016BD5C:
	extsh.   r0, r31
	ble      lbl_8016BD6C
	mr       r3, r30
	bl       __dl__FPv

lbl_8016BD6C:
	lwz      r0, 0x14(r1)
	mr       r3, r30
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

namespace Game {

/*
 * --INFO--
 * Address:	8016BD88
 * Size:	000030
 */
void BasePelletMgr::getPelletConfig(int)
{
	/*
	cmpwi    r4, 0
	blt      lbl_8016BDA0
	lwz      r3, 8(r3)
	lwz      r0, 0x18(r3)
	cmpw     r4, r0
	blt      lbl_8016BDA8

lbl_8016BDA0:
	li       r3, 0
	blr

lbl_8016BDA8:
	mulli    r0, r4, 0x260
	lwz      r3, 0x1c(r3)
	add      r3, r3, r0
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016BDB8
 * Size:	00007C
 */
void BasePelletMgr::setUse(int)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	or.      r31, r4, r4
	stw      r30, 8(r1)
	mr       r30, r3
	li       r3, 0
	blt      lbl_8016BDEC
	lwz      r0, 0x50(r30)
	cmpw     r31, r0
	bge      lbl_8016BDEC
	li       r3, 1

lbl_8016BDEC:
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016BE10
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x1143
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016BE10:
	lwz      r3, 0x4c(r30)
	li       r0, 1
	stbx     r0, r3, r31
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	000078
 */
void BasePelletMgr::used(int)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000024
 */
void BasePelletMgr::setUseFlagAll(bool)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8016BE34
 * Size:	000298
 */
void BasePelletMgr::load(void)
{
	/*
	stwu     r1, -0x430(r1)
	mflr     r0
	lis      r4, gGameConfig__4Game@ha
	lis      r5, lbl_8047E318@ha
	stw      r0, 0x434(r1)
	addi     r4, r4, gGameConfig__4Game@l
	stmw     r23, 0x40c(r1)
	mr       r23, r3
	addi     r31, r5, lbl_8047E318@l
	li       r28, 0
	lwz      r0, 0x158(r4)
	cmpwi    r0, 0
	beq      lbl_8016BEF4
	lwz      r3, sys@sda21(r13)
	lwz      r0, 0xd4(r3)
	cmpwi    r0, 4
	beq      lbl_8016BED8
	bge      lbl_8016BE94
	cmpwi    r0, 0
	beq      lbl_8016BEBC
	blt      lbl_8016BEF8
	cmpwi    r0, 3
	bge      lbl_8016BEF8
	b        lbl_8016BED8

lbl_8016BE94:
	cmpwi    r0, 6
	beq      lbl_8016BED8
	bge      lbl_8016BEF8
	addi     r3, r1, 0x208
	addi     r4, r31, 0xe0
	addi     r5, r2, lbl_805189C8@sda21
	crclr    6
	bl       sprintf
	addi     r28, r1, 0x208
	b        lbl_8016BEF8

lbl_8016BEBC:
	addi     r3, r1, 0x208
	addi     r4, r31, 0xe0
	addi     r5, r2, lbl_805189CC@sda21
	crclr    6
	bl       sprintf
	addi     r28, r1, 0x208
	b        lbl_8016BEF8

lbl_8016BED8:
	addi     r3, r1, 0x208
	addi     r4, r31, 0xe0
	addi     r5, r2, lbl_805189D0@sda21
	crclr    6
	bl       sprintf
	addi     r28, r1, 0x208
	b        lbl_8016BEF8

lbl_8016BEF4:
	addi     r28, r31, 0xf8

lbl_8016BEF8:
	li       r30, 0
	li       r27, 0
	mr       r29, r30
	b        lbl_8016C0A8

lbl_8016BF08:
	lwz      r0, 0x1c(r3)
	li       r25, 0
	addi     r3, r2, lbl_805189D4@sda21
	add      r26, r0, r30
	sth      r27, 0x258(r26)
	lwz      r4, 0x50(r26)
	bl       strcmp
	cmpwi    r3, 0
	beq      lbl_8016BF5C
	lwz      r6, 0x50(r26)
	mr       r5, r28
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189DC@sda21
	crclr    6
	bl       sprintf
	addi     r3, r1, 8
	li       r4, 1
	li       r5, 0
	li       r6, 1
	bl
mount__10JKRArchiveFPCcQ210JKRArchive10EMountModeP7JKRHeapQ210JKRArchive15EMountDirection
	mr       r25, r3

lbl_8016BF5C:
	lwz      r4, 0x70(r26)
	li       r24, 0
	addi     r3, r2, lbl_805189D4@sda21
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_8016BF84
	lwz      r3, 0xc(r23)
	li       r0, 0
	stwx     r0, r3, r29
	b        lbl_8016C034

lbl_8016BF84:
	lwz      r5, 0x70(r26)
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189E4@sda21
	crclr    6
	bl       sprintf
	addi     r3, r1, 8
	li       r4, 0
	bl       getGlbResource__13JKRFileLoaderFPCcP13JKRFileLoader
	or.      r24, r3, r3
	bne      lbl_8016BFC4
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x10c
	addi     r6, r1, 8
	li       r4, 0x11d0
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016BFC4:
	lhz      r0, 0x244(r26)
	lis      r3, 0x21020010@ha
	addi     r4, r3, 0x21020010@l
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016BFDC
	ori      r4, r4, 0x20

lbl_8016BFDC:
	mr       r3, r24
	bl       load__22J3DModelLoaderDataBaseFPCvUl
	lhz      r0, 0x244(r26)
	mr       r24, r3
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016C02C
	li       r4, 0
	b        lbl_8016C01C

lbl_8016BFFC:
	lwz      r3, 0x80(r24)
	rlwinm   r0, r4, 2, 0xe, 0x1d
	addi     r4, r4, 1
	lwzx     r3, r3, r0
	lwz      r0, 0xc(r3)
	rlwinm   r0, r0, 0, 0x14, 0xf
	ori      r0, r0, 0x2000
	stw      r0, 0xc(r3)

lbl_8016C01C:
	lhz      r0, 0x7c(r24)
	clrlwi   r3, r4, 0x10
	cmplw    r3, r0
	blt      lbl_8016BFFC

lbl_8016C02C:
	lwz      r3, 0xc(r23)
	stwx     r24, r3, r29

lbl_8016C034:
	lwz      r6, 0x80(r26)
	cmplwi   r6, 0
	beq      lbl_8016C06C
	mr       r5, r28
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189DC@sda21
	crclr    6
	bl       sprintf
	mr       r4, r24
	mr       r5, r25
	addi     r3, r1, 8
	bl       load__Q28SysShape7AnimMgrFPcP12J3DModelDataP13JKRFileLoader
	lwz      r4, 0x10(r23)
	stwx     r3, r4, r29

lbl_8016C06C:
	lwz      r6, 0x90(r26)
	cmplwi   r6, 0
	beq      lbl_8016C09C
	mr       r5, r28
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189DC@sda21
	crclr    6
	bl       sprintf
	addi     r3, r1, 8
	bl       load__15CollPartFactoryFPc
	lwz      r4, 0x14(r23)
	stwx     r3, r4, r29

lbl_8016C09C:
	addi     r30, r30, 0x260
	addi     r29, r29, 4
	addi     r27, r27, 1

lbl_8016C0A8:
	lwz      r3, 8(r23)
	lwz      r0, 0x18(r3)
	cmpw     r27, r0
	blt      lbl_8016BF08
	lmw      r23, 0x40c(r1)
	lwz      r0, 0x434(r1)
	mtlr     r0
	addi     r1, r1, 0x430
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016C0CC
 * Size:	0003E4
 */
void BasePelletMgr::load_texArc(char*)
{
	/*
	stwu     r1, -0x430(r1)
	mflr     r0
	lis      r5, gGameConfig__4Game@ha
	lis      r6, lbl_8047E318@ha
	stw      r0, 0x434(r1)
	addi     r5, r5, gGameConfig__4Game@l
	stmw     r22, 0x408(r1)
	mr       r31, r3
	mr       r22, r4
	addi     r30, r6, lbl_8047E318@l
	li       r24, 0
	lwz      r0, 0x158(r5)
	cmpwi    r0, 0
	beq      lbl_8016C190
	lwz      r3, sys@sda21(r13)
	lwz      r0, 0xd4(r3)
	cmpwi    r0, 4
	beq      lbl_8016C174
	bge      lbl_8016C130
	cmpwi    r0, 0
	beq      lbl_8016C158
	blt      lbl_8016C194
	cmpwi    r0, 3
	bge      lbl_8016C194
	b        lbl_8016C174

lbl_8016C130:
	cmpwi    r0, 6
	beq      lbl_8016C174
	bge      lbl_8016C194
	addi     r3, r1, 0x208
	addi     r4, r30, 0xe0
	addi     r5, r2, lbl_805189C8@sda21
	crclr    6
	bl       sprintf
	addi     r24, r1, 0x208
	b        lbl_8016C194

lbl_8016C158:
	addi     r3, r1, 0x208
	addi     r4, r30, 0xe0
	addi     r5, r2, lbl_805189CC@sda21
	crclr    6
	bl       sprintf
	addi     r24, r1, 0x208
	b        lbl_8016C194

lbl_8016C174:
	addi     r3, r1, 0x208
	addi     r4, r30, 0xe0
	addi     r5, r2, lbl_805189D0@sda21
	crclr    6
	bl       sprintf
	addi     r24, r1, 0x208
	b        lbl_8016C194

lbl_8016C190:
	addi     r24, r30, 0xf8

lbl_8016C194:
	mr       r5, r24
	mr       r6, r22
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189DC@sda21
	crclr    6
	bl       sprintf
	mr       r3, r31
	addi     r4, r1, 8
	bl       openTextArc__Q24Game13BasePelletMgrFPc
	or.      r27, r3, r3
	bne      lbl_8016C1D8
	addi     r3, r30, 0x2c
	addi     r5, r30, 0x128
	addi     r6, r1, 8
	li       r4, 0x1278
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016C1D8:
	li       r29, 0
	li       r26, 0
	mr       r28, r29
	b        lbl_8016C480

lbl_8016C1E8:
	lwz      r0, 0x1c(r3)
	cmpwi    r26, 0
	li       r3, 0
	add      r25, r0, r29
	blt      lbl_8016C20C
	lwz      r0, 0x50(r31)
	cmpw     r26, r0
	bge      lbl_8016C20C
	li       r3, 1

lbl_8016C20C:
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016C228
	addi     r3, r30, 0x2c
	addi     r5, r30, 0x3c
	li       r4, 0x1149
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016C228:
	lwz      r3, 0x4c(r31)
	lbzx     r0, r3, r26
	cmplwi   r0, 0
	beq      lbl_8016C474
	sth      r26, 0x258(r25)
	li       r23, 0
	addi     r3, r2, lbl_805189D4@sda21
	lwz      r4, 0x50(r25)
	bl       strcmp
	cmpwi    r3, 0
	beq      lbl_8016C284
	lwz      r6, 0x50(r25)
	mr       r5, r24
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189DC@sda21
	crclr    6
	bl       sprintf
	addi     r3, r1, 8
	li       r4, 1
	li       r5, 0
	li       r6, 1
	bl
mount__10JKRArchiveFPCcQ210JKRArchive10EMountModeP7JKRHeapQ210JKRArchive15EMountDirection
	mr       r23, r3

lbl_8016C284:
	lwz      r4, 0x70(r25)
	li       r22, 0
	addi     r3, r2, lbl_805189D4@sda21
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_8016C2AC
	lwz      r3, 0xc(r31)
	li       r0, 0
	stwx     r0, r3, r28
	b        lbl_8016C3D0

lbl_8016C2AC:
	cmplwi   r23, 0
	bne      lbl_8016C2C8
	addi     r3, r30, 0x2c
	addi     r5, r30, 0x13c
	li       r4, 0x12a8
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016C2C8:
	lwz      r5, 0x70(r25)
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189E4@sda21
	crclr    6
	bl       sprintf
	addi     r3, r1, 8
	li       r4, 0
	bl       getGlbResource__13JKRFileLoaderFPCcP13JKRFileLoader
	cmplwi   r3, 0
	mr       r22, r3
	bne      lbl_8016C32C
	mr       r3, r23
	addi     r4, r1, 8
	lwz      r12, 0(r23)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	mr       r0, r3
	addi     r3, r30, 0x2c
	mr       r22, r0
	addi     r5, r30, 0x150
	addi     r6, r1, 8
	li       r4, 0x12b2
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016C32C:
	lbz      r0, 0x25a(r25)
	cmplwi   r0, 0
	beq      lbl_8016C360
	lhz      r0, 0x244(r25)
	lis      r3, 0x21020010@ha
	addi     r4, r3, 0x21020010@l
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016C350
	ori      r4, r4, 0x20

lbl_8016C350:
	mr       r3, r22
	bl       load__22J3DModelLoaderDataBaseFPCvUl
	mr       r22, r3
	b        lbl_8016C384

lbl_8016C360:
	lhz      r0, 0x244(r25)
	lis      r3, 0x20020010@ha
	addi     r4, r3, 0x20020010@l
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016C378
	ori      r4, r4, 0x20

lbl_8016C378:
	mr       r3, r22
	bl       load__22J3DModelLoaderDataBaseFPCvUl
	mr       r22, r3

lbl_8016C384:
	lwz      r3, 0xc(r31)
	stwx     r22, r3, r28
	lhz      r0, 0x244(r25)
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016C3D0
	li       r4, 0
	b        lbl_8016C3C0

lbl_8016C3A0:
	lwz      r3, 0x80(r22)
	rlwinm   r0, r4, 2, 0xe, 0x1d
	addi     r4, r4, 1
	lwzx     r3, r3, r0
	lwz      r0, 0xc(r3)
	rlwinm   r0, r0, 0, 0x14, 0xf
	ori      r0, r0, 0x2000
	stw      r0, 0xc(r3)

lbl_8016C3C0:
	lhz      r0, 0x7c(r22)
	clrlwi   r3, r4, 0x10
	cmplw    r3, r0
	blt      lbl_8016C3A0

lbl_8016C3D0:
	lwz      r6, 0x80(r25)
	cmplwi   r6, 0
	beq      lbl_8016C440
	lwz      r5, 0x40(r25)
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189E8@sda21
	crclr    6
	bl       sprintf
	mr       r3, r27
	mr       r5, r22
	mr       r6, r23
	addi     r4, r1, 8
	li       r7, 0
	bl
load__Q28SysShape7AnimMgrFP13JKRFileLoaderPcP12J3DModelDataP13JKRFileLoaderPc
	lwz      r4, 0x10(r31)
	stwx     r3, r4, r28
	lwz      r3, 0x10(r31)
	lwzx     r0, r3, r28
	cmplwi   r0, 0
	bne      lbl_8016C440
	mr       r3, r27
	mr       r5, r22
	mr       r6, r23
	addi     r4, r1, 8
	li       r7, 0
	bl
load__Q28SysShape7AnimMgrFP13JKRFileLoaderPcP12J3DModelDataP13JKRFileLoaderPc
	lwz      r4, 0x10(r31)
	stwx     r3, r4, r28

lbl_8016C440:
	lwz      r6, 0x90(r25)
	cmplwi   r6, 0
	beq      lbl_8016C474
	lwz      r5, 0x40(r25)
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189E8@sda21
	crclr    6
	bl       sprintf
	mr       r3, r27
	addi     r4, r1, 8
	bl       load__15CollPartFactoryFP13JKRFileLoaderPc
	lwz      r4, 0x14(r31)
	stwx     r3, r4, r28

lbl_8016C474:
	addi     r29, r29, 0x260
	addi     r28, r28, 4
	addi     r26, r26, 1

lbl_8016C480:
	lwz      r3, 8(r31)
	lwz      r0, 0x18(r3)
	cmpw     r26, r0
	blt      lbl_8016C1E8
	mr       r3, r31
	mr       r4, r27
	bl       closeTextArc__Q24Game13BasePelletMgrFP10JKRArchive
	lmw      r22, 0x408(r1)
	lwz      r0, 0x434(r1)
	mtlr     r0
	addi     r1, r1, 0x430
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016C4B0
 * Size:	00010C
 */
void BasePelletMgr::openTextArc(char*)
{
	/*
	stwu     r1, -0x410(r1)
	mflr     r0
	lis      r3, gGameConfig__4Game@ha
	li       r5, 0
	stw      r0, 0x414(r1)
	addi     r3, r3, gGameConfig__4Game@l
	stw      r31, 0x40c(r1)
	mr       r31, r4
	lwz      r0, 0x158(r3)
	cmpwi    r0, 0
	beq      lbl_8016C574
	lwz      r3, sys@sda21(r13)
	lwz      r0, 0xd4(r3)
	cmpwi    r0, 4
	beq      lbl_8016C554
	bge      lbl_8016C508
	cmpwi    r0, 0
	beq      lbl_8016C534
	blt      lbl_8016C580
	cmpwi    r0, 3
	bge      lbl_8016C580
	b        lbl_8016C554

lbl_8016C508:
	cmpwi    r0, 6
	beq      lbl_8016C554
	bge      lbl_8016C580
	lis      r4, lbl_8047E3F8@ha
	addi     r3, r1, 0x208
	addi     r4, r4, lbl_8047E3F8@l
	addi     r5, r2, lbl_805189C8@sda21
	crclr    6
	bl       sprintf
	addi     r5, r1, 0x208
	b        lbl_8016C580

lbl_8016C534:
	lis      r4, lbl_8047E3F8@ha
	addi     r3, r1, 0x208
	addi     r4, r4, lbl_8047E3F8@l
	addi     r5, r2, lbl_805189CC@sda21
	crclr    6
	bl       sprintf
	addi     r5, r1, 0x208
	b        lbl_8016C580

lbl_8016C554:
	lis      r4, lbl_8047E3F8@ha
	addi     r3, r1, 0x208
	addi     r4, r4, lbl_8047E3F8@l
	addi     r5, r2, lbl_805189D0@sda21
	crclr    6
	bl       sprintf
	addi     r5, r1, 0x208
	b        lbl_8016C580

lbl_8016C574:
	lis      r3, lbl_8047E410@ha
	addi     r0, r3, lbl_8047E410@l
	mr       r5, r0

lbl_8016C580:
	mr       r6, r31
	addi     r3, r1, 8
	addi     r4, r2, lbl_805189E8@sda21
	crclr    6
	bl       sprintf
	lwz      r5, sCurrentHeap__7JKRHeap@sda21(r13)
	addi     r3, r1, 8
	li       r4, 1
	li       r6, 2
	bl
mount__10JKRArchiveFPCcQ210JKRArchive10EMountModeP7JKRHeapQ210JKRArchive15EMountDirection
	lwz      r0, 0x414(r1)
	lwz      r31, 0x40c(r1)
	mtlr     r0
	addi     r1, r1, 0x410
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016C5BC
 * Size:	000030
 */
void BasePelletMgr::closeTextArc(JKRArchive*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	mr       r3, r4
	stw      r0, 0x14(r1)
	lwz      r12, 0(r4)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016C5EC
 * Size:	0000E4
 */
void BasePelletMgr::useModelMgr(int, unsigned long)
{
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stmw     r27, 0x1c(r1)
	mr       r28, r3
	mr       r29, r4
	mr       r30, r5
	li       r31, 2
	lwz      r6, gameSystem__4Game@sda21(r13)
	cmplwi   r6, 0
	beq      lbl_8016C62C
	lwz      r3, 0x58(r6)
	lwz      r0, 0x114(r3)
	cmpwi    r0, 1
	bne      lbl_8016C62C
	li       r31, 1

lbl_8016C62C:
	li       r3, 0x1c
	bl       __nw__FUl
	or.      r27, r3, r3
	beq      lbl_8016C6B8
	li       r3, 0x14
	bl       __nw__FUl
	or.      r9, r3, r3
	beq      lbl_8016C694
	lis      r3, lbl_804B1AC0@ha
	lis      r4, "__vt__30IDelegate1<PQ28SysShape5Model>"@ha
	addi     r7, r3, lbl_804B1AC0@l
	lis      r3,
"__vt__52Delegate1<Q24Game13BasePelletMgr,PQ28SysShape5Model>"@ha lwz      r6,
0(r7) addi     r4, r4, "__vt__30IDelegate1<PQ28SysShape5Model>"@l lwz      r5,
4(r7) addi     r0, r3,
"__vt__52Delegate1<Q24Game13BasePelletMgr,PQ28SysShape5Model>"@l lwz      r3,
8(r7) stw      r6, 8(r1) stw      r4, 0(r9) stw      r0, 0(r9) stw      r28,
4(r9) stw      r6, 8(r9) stw      r5, 0xc(r9) stw      r5, 0xc(r1) stw      r3,
0x10(r1) stw      r3, 0x10(r9)

lbl_8016C694:
	lwz      r4, 8(r28)
	mr       r3, r27
	lwz      r5, 0xc(r28)
	mr       r6, r29
	lwz      r4, 0x18(r4)
	mr       r7, r30
	mr       r8, r31
	bl
"__ct__Q28SysShape8ModelMgrFiPP12J3DModelDataiUlUlP30IDelegate1<PQ28SysShape5Model>"
	mr       r27, r3

lbl_8016C6B8:
	stw      r27, 0x48(r28)
	lmw      r27, 0x1c(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016C6D0
 * Size:	00002C
 */
void BasePelletMgr::createModelCallback(SysShape::Model*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x54(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016C6FC
 * Size:	000004
 */
void BasePelletMgr::onCreateModel(SysShape::Model*) { }

/*
 * --INFO--
 * Address:	8016C700
 * Size:	0000E4
 */
void BasePelletMgr::createShape(int, int)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	li       r30, 2
	stw      r29, 0x14(r1)
	mr       r29, r3
	lwz      r6, gameSystem__4Game@sda21(r13)
	cmplwi   r6, 0
	beq      lbl_8016C740
	lwz      r3, 0x58(r6)
	lwz      r0, 0x114(r3)
	cmpwi    r0, 1
	bne      lbl_8016C740
	li       r30, 1

lbl_8016C740:
	lwz      r3, 0x48(r29)
	cmplwi   r3, 0
	beq      lbl_8016C758
	bl       createModel__Q28SysShape8ModelMgrFii
	mr       r30, r3
	b        lbl_8016C7C4

lbl_8016C758:
	lwz      r3, 0xc(r29)
	slwi     r31, r4, 2
	lwzx     r0, r3, r31
	cmplwi   r0, 0
	bne      lbl_8016C78C
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E47C@ha
	mr       r6, r4
	li       r4, 0x13c5
	addi     r3, r3, lbl_8047E344@l
	addi     r5, r5, lbl_8047E47C@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016C78C:
	li       r3, 0x14
	bl       __nw__FUl
	or.      r4, r3, r3
	beq      lbl_8016C7B4
	lwz      r4, 0xc(r29)
	mr       r6, r30
	li       r5, 0
	lwzx     r4, r4, r31
	bl       __ct__Q28SysShape5ModelFP12J3DModelDataUlUl
	mr       r4, r3

lbl_8016C7B4:
	lwz      r3, 8(r4)
	mr       r30, r4
	li       r4, 0
	bl       newDifferedTexMtx__8J3DModelF14J3DTexDiffFlag

lbl_8016C7C4:
	lwz      r0, 0x24(r1)
	mr       r3, r30
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
 * Address:	8016C7E4
 * Size:	000158
 */
void BasePelletMgr::setCollTree(Game::Pellet*, int)
{
	/*
	stwu     r1, -0x50(r1)
	mflr     r0
	stw      r0, 0x54(r1)
	stw      r31, 0x4c(r1)
	stw      r30, 0x48(r1)
	mr       r30, r4
	stw      r29, 0x44(r1)
	mr       r29, r3
	lwz      r4, 0x174(r4)
	cmplwi   r4, 0
	bne      lbl_8016C8C0
	lwz      r3, 0x358(r30)
	lwz      r12, 0(r3)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	lwz      r5, 0x35c(r30)
	lis      r4, "zero__10Vector3<f>"@ha
	lfsu     f2, "zero__10Vector3<f>"@l(r4)
	mr       r31, r3
	lfs      f3, 0xb0(r5)
	lfs      f1, 4(r4)
	lfs      f0, 8(r4)
	stfs     f2, 0x24(r1)
	stfs     f1, 0x28(r1)
	stfs     f0, 0x2c(r1)
	stfs     f3, 0x30(r1)
	lwz      r3, 0x358(r30)
	lwz      r12, 0(r3)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	mr       r5, r3
	lwz      r3, 0x114(r30)
	mr       r4, r31
	addi     r6, r1, 0x24
	addi     r7, r29, 0x18
	bl
createSingleSphere__8CollTreeFPQ28SysShape9MtxObjectiRQ23Sys6SphereP11CollPartMgr
	lwz      r3, 0x114(r30)
	lwz      r31, 0(r3)
	cmplwi   r31, 0
	beq      lbl_8016C920
	lwz      r4, 0x358(r30)
	addi     r3, r1, 8
	lwz      r12, 0(r4)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	lfs      f0, 8(r1)
	stfs     f0, 0x20(r31)
	lfs      f0, 0xc(r1)
	stfs     f0, 0x24(r31)
	lfs      f0, 0x10(r1)
	stfs     f0, 0x28(r31)
	b        lbl_8016C920

lbl_8016C8C0:
	lwz      r3, 0x14(r29)
	slwi     r0, r5, 2
	lwzx     r5, r3, r0
	cmplwi   r5, 0
	beq      lbl_8016C8E4
	lwz      r3, 0x114(r30)
	addi     r6, r29, 0x18
	bl
createFromFactory__8CollTreeFPQ28SysShape9MtxObjectP15CollPartFactoryP11CollPartMgr
	b        lbl_8016C920

lbl_8016C8E4:
	lwz      r5, 0x35c(r30)
	lis      r3, "zero__10Vector3<f>"@ha
	lfsu     f2, "zero__10Vector3<f>"@l(r3)
	addi     r6, r1, 0x14
	lfs      f3, 0xa0(r5)
	addi     r7, r29, 0x18
	lfs      f1, 4(r3)
	li       r5, 0
	lfs      f0, 8(r3)
	stfs     f2, 0x14(r1)
	stfs     f1, 0x18(r1)
	stfs     f0, 0x1c(r1)
	stfs     f3, 0x20(r1)
	lwz      r3, 0x114(r30)
	bl
createSingleSphere__8CollTreeFPQ28SysShape9MtxObjectiRQ23Sys6SphereP11CollPartMgr

lbl_8016C920:
	lwz      r0, 0x54(r1)
	lwz      r31, 0x4c(r1)
	lwz      r30, 0x48(r1)
	lwz      r29, 0x44(r1)
	mtlr     r0
	addi     r1, r1, 0x50
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016C93C
 * Size:	000024
 */
void BasePelletMgr::generatorNewPelletParm(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	li       r3, 4
	stw      r0, 0x14(r1)
	bl       __nw__FUl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016C960
 * Size:	000008
 */
u32 BasePelletMgr::generatorGetShape(Game::GenPelletParm*) { return 0x0; }

/*
 * --INFO--
 * Address:	........
 * Size:	000004
 */
void BasePelletMgr::setupSoundViewerAndBas(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8016C968
 * Size:	000018
 */
PelletIterator::PelletIterator(void)
{
	/*
	li       r0, 0
	stw      r0, 0(r3)
	stw      r0, 8(r3)
	stw      r0, 0xc(r3)
	stw      r0, 4(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016C980
 * Size:	00004C
 */
void PelletIterator::first(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lwz      r4, pelletMgr__4Game@sda21(r13)
	lwz      r0, 0x30(r4)
	stw      r0, 8(r3)
	lwz      r4, 8(r3)
	cmplwi   r4, 0
	beq      lbl_8016C9B0
	lwz      r0, 0x18(r4)
	stw      r0, 4(r3)
	b        lbl_8016C9B8

lbl_8016C9B0:
	li       r0, 0
	stw      r0, 4(r3)

lbl_8016C9B8:
	bl       setFirst__Q24Game14PelletIteratorFv
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016C9CC
 * Size:	000068
 */
void PelletIterator::operator*(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 4(r3)
	cmplwi   r0, 0
	bne      lbl_8016CA08
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x144d
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016CA08:
	lwz      r3, 4(r31)
	lwz      r4, 0xc(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x88(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016CA34
 * Size:	0000C0
 */
void PelletIterator::next(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 0(r3)
	cmplwi   r0, 0
	bne      lbl_8016CA74
	lwz      r3, 4(r31)
	lwz      r4, 0xc(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x8c(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r31)
	b        lbl_8016CA8C

lbl_8016CA74:
	lis      r3, lbl_8047E344@ha
	li       r4, 0x1456
	addi     r3, r3, lbl_8047E344@l
	addi     r5, r2, lbl_805189F0@sda21
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016CA8C:
	lwz      r3, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x94(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0xc(r31)
	cmplw    r0, r3
	bne      lbl_8016CAE0
	lwz      r3, 8(r31)
	lwz      r0, 4(r3)
	stw      r0, 8(r31)
	lwz      r3, 8(r31)
	cmplwi   r3, 0
	beq      lbl_8016CAD8
	lwz      r0, 0x18(r3)
	mr       r3, r31
	stw      r0, 4(r31)
	bl       setFirst__Q24Game14PelletIteratorFv
	b        lbl_8016CAE0

lbl_8016CAD8:
	li       r0, 0
	stw      r0, 4(r31)

lbl_8016CAE0:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016CAF4
 * Size:	000010
 */
void PelletIterator::isDone(void)
{
	/*
	lwz      r0, 4(r3)
	cntlzw   r0, r0
	srwi     r3, r0, 5
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016CB04
 * Size:	000350
 */
void PelletIterator::setFirst(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r3, 4(r3)
	cmplwi   r3, 0
	beq      lbl_8016CE38
	lwz      r0, 0(r31)
	cmplwi   r0, 0
	bne      lbl_8016CB48
	lwz      r12, 0(r3)
	lwz      r12, 0x90(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r31)
	b        lbl_8016CB60

lbl_8016CB48:
	lis      r3, lbl_8047E344@ha
	li       r4, 0x1471
	addi     r3, r3, lbl_8047E344@l
	addi     r5, r2, lbl_805189F0@sda21
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016CB60:
	lwz      r3, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x94(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0xc(r31)
	cmplw    r0, r3
	bne      lbl_8016CE40
	lwz      r3, 8(r31)
	lwz      r0, 4(r3)
	stw      r0, 8(r31)
	lwz      r3, 8(r31)
	cmplwi   r3, 0
	beq      lbl_8016CE2C
	lwz      r0, 0x18(r3)
	stw      r0, 4(r31)
	lwz      r3, 4(r31)
	cmplwi   r3, 0
	beq      lbl_8016CE20
	lwz      r0, 0(r31)
	cmplwi   r0, 0
	bne      lbl_8016CBD0
	lwz      r12, 0(r3)
	lwz      r12, 0x90(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r31)
	b        lbl_8016CBE8

lbl_8016CBD0:
	lis      r3, lbl_8047E344@ha
	li       r4, 0x1471
	addi     r3, r3, lbl_8047E344@l
	addi     r5, r2, lbl_805189F0@sda21
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016CBE8:
	lwz      r3, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x94(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0xc(r31)
	cmplw    r0, r3
	bne      lbl_8016CE40
	lwz      r3, 8(r31)
	lwz      r0, 4(r3)
	stw      r0, 8(r31)
	lwz      r3, 8(r31)
	cmplwi   r3, 0
	beq      lbl_8016CE14
	lwz      r0, 0x18(r3)
	stw      r0, 4(r31)
	lwz      r3, 4(r31)
	cmplwi   r3, 0
	beq      lbl_8016CE08
	lwz      r0, 0(r31)
	cmplwi   r0, 0
	bne      lbl_8016CC58
	lwz      r12, 0(r3)
	lwz      r12, 0x90(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r31)
	b        lbl_8016CC70

lbl_8016CC58:
	lis      r3, lbl_8047E344@ha
	li       r4, 0x1471
	addi     r3, r3, lbl_8047E344@l
	addi     r5, r2, lbl_805189F0@sda21
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016CC70:
	lwz      r3, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x94(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0xc(r31)
	cmplw    r0, r3
	bne      lbl_8016CE40
	lwz      r3, 8(r31)
	lwz      r0, 4(r3)
	stw      r0, 8(r31)
	lwz      r3, 8(r31)
	cmplwi   r3, 0
	beq      lbl_8016CDFC
	lwz      r0, 0x18(r3)
	stw      r0, 4(r31)
	lwz      r3, 4(r31)
	cmplwi   r3, 0
	beq      lbl_8016CDF0
	lwz      r0, 0(r31)
	cmplwi   r0, 0
	bne      lbl_8016CCE0
	lwz      r12, 0(r3)
	lwz      r12, 0x90(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r31)
	b        lbl_8016CCF8

lbl_8016CCE0:
	lis      r3, lbl_8047E344@ha
	li       r4, 0x1471
	addi     r3, r3, lbl_8047E344@l
	addi     r5, r2, lbl_805189F0@sda21
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016CCF8:
	lwz      r3, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x94(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0xc(r31)
	cmplw    r0, r3
	bne      lbl_8016CE40
	lwz      r3, 8(r31)
	lwz      r0, 4(r3)
	stw      r0, 8(r31)
	lwz      r3, 8(r31)
	cmplwi   r3, 0
	beq      lbl_8016CDE4
	lwz      r0, 0x18(r3)
	stw      r0, 4(r31)
	lwz      r3, 4(r31)
	cmplwi   r3, 0
	beq      lbl_8016CDD8
	lwz      r0, 0(r31)
	cmplwi   r0, 0
	bne      lbl_8016CD68
	lwz      r12, 0(r3)
	lwz      r12, 0x90(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r31)
	b        lbl_8016CD80

lbl_8016CD68:
	lis      r3, lbl_8047E344@ha
	li       r4, 0x1471
	addi     r3, r3, lbl_8047E344@l
	addi     r5, r2, lbl_805189F0@sda21
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016CD80:
	lwz      r3, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x94(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0xc(r31)
	cmplw    r0, r3
	bne      lbl_8016CE40
	lwz      r3, 8(r31)
	bl       "getNext__31TObjectNode<16GenericObjectMgr>Fv"
	stw      r3, 8(r31)
	lwz      r3, 8(r31)
	cmplwi   r3, 0
	beq      lbl_8016CDCC
	lwz      r0, 0x18(r3)
	mr       r3, r31
	stw      r0, 4(r31)
	bl       setFirst__Q24Game14PelletIteratorFv
	b        lbl_8016CE40

lbl_8016CDCC:
	li       r0, 0
	stw      r0, 4(r31)
	b        lbl_8016CE40

lbl_8016CDD8:
	li       r0, 0
	stw      r0, 0xc(r31)
	b        lbl_8016CE40

lbl_8016CDE4:
	li       r0, 0
	stw      r0, 4(r31)
	b        lbl_8016CE40

lbl_8016CDF0:
	li       r0, 0
	stw      r0, 0xc(r31)
	b        lbl_8016CE40

lbl_8016CDFC:
	li       r0, 0
	stw      r0, 4(r31)
	b        lbl_8016CE40

lbl_8016CE08:
	li       r0, 0
	stw      r0, 0xc(r31)
	b        lbl_8016CE40

lbl_8016CE14:
	li       r0, 0
	stw      r0, 4(r31)
	b        lbl_8016CE40

lbl_8016CE20:
	li       r0, 0
	stw      r0, 0xc(r31)
	b        lbl_8016CE40

lbl_8016CE2C:
	li       r0, 0
	stw      r0, 4(r31)
	b        lbl_8016CE40

lbl_8016CE38:
	li       r0, 0
	stw      r0, 0xc(r31)

lbl_8016CE40:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

} // namespace Game

/*
 * --INFO--
 * Address:	8016CE54
 * Size:	000008
 */
void TObjectNode<GenericObjectMgr>::getNext()
{
	/*
	lwz      r3, 4(r3)
	blr
	*/
}

namespace Game {

/*
 * --INFO--
 * Address:	8016CE5C
 * Size:	0000CC
 */
PelletMgr::PelletMgr(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	stw      r30, 8(r1)
	bl       __ct__5CNodeFv
	lis      r4, __vt__16GenericContainer@ha
	lis      r3, "__vt__29Container<16GenericObjectMgr>"@ha
	addi     r0, r4, __vt__16GenericContainer@l
	lis      r5, __vt__16GenericObjectMgr@ha
	stw      r0, 0(r31)
	addi     r0, r3, "__vt__29Container<16GenericObjectMgr>"@l
	lis      r4, "__vt__29ObjectMgr<16GenericObjectMgr>"@ha
	lis      r3, "__vt__33NodeObjectMgr<16GenericObjectMgr>"@ha
	stw      r0, 0(r31)
	li       r0, 0
	addi     r6, r4, "__vt__29ObjectMgr<16GenericObjectMgr>"@l
	addi     r4, r3, "__vt__33NodeObjectMgr<16GenericObjectMgr>"@l
	stb      r0, 0x18(r31)
	addi     r0, r5, __vt__16GenericObjectMgr@l
	addi     r30, r31, 0x20
	addi     r5, r6, 0x2c
	stw      r0, 0x1c(r31)
	addi     r0, r4, 0x2c
	mr       r3, r30
	stw      r6, 0(r31)
	stw      r5, 0x1c(r31)
	stw      r4, 0(r31)
	stw      r0, 0x1c(r31)
	bl       __ct__5CNodeFv
	lis      r3, "__vt__31TObjectNode<16GenericObjectMgr>"@ha
	lis      r4, __vt__Q24Game9PelletMgr@ha
	addi     r0, r3, "__vt__31TObjectNode<16GenericObjectMgr>"@l
	lis      r3, lbl_8047E494@ha
	stw      r0, 0(r30)
	addi     r6, r4, __vt__Q24Game9PelletMgr@l
	addi     r5, r6, 0x2c
	addi     r4, r3, lbl_8047E494@l
	stw      r6, 0(r31)
	li       r0, 0
	mr       r3, r31
	stw      r5, 0x1c(r31)
	stw      r4, 0x14(r31)
	stb      r0, 0x3c(r31)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

} // namespace Game

/*
 * --INFO--
 * Address:	8016CF28
 * Size:	0000C8
 */
void NodeObjectMgr<GenericObjectMgr>::~NodeObjectMgr()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8016CFD4
	lis      r3, "__vt__33NodeObjectMgr<16GenericObjectMgr>"@ha
	addic.   r0, r30, 0x20
	addi     r3, r3, "__vt__33NodeObjectMgr<16GenericObjectMgr>"@l
	stw      r3, 0(r30)
	addi     r0, r3, 0x2c
	stw      r0, 0x1c(r30)
	beq      lbl_8016CF7C
	lis      r4, "__vt__31TObjectNode<16GenericObjectMgr>"@ha
	addi     r3, r30, 0x20
	addi     r0, r4, "__vt__31TObjectNode<16GenericObjectMgr>"@l
	li       r4, 0
	stw      r0, 0x20(r30)
	bl       __dt__5CNodeFv

lbl_8016CF7C:
	cmplwi   r30, 0
	beq      lbl_8016CFC4
	lis      r3, "__vt__29ObjectMgr<16GenericObjectMgr>"@ha
	addi     r3, r3, "__vt__29ObjectMgr<16GenericObjectMgr>"@l
	stw      r3, 0(r30)
	addi     r0, r3, 0x2c
	stw      r0, 0x1c(r30)
	beq      lbl_8016CFC4
	lis      r3, "__vt__29Container<16GenericObjectMgr>"@ha
	addi     r0, r3, "__vt__29Container<16GenericObjectMgr>"@l
	stw      r0, 0(r30)
	beq      lbl_8016CFC4
	lis      r4, __vt__16GenericContainer@ha
	mr       r3, r30
	addi     r0, r4, __vt__16GenericContainer@l
	li       r4, 0
	stw      r0, 0(r30)
	bl       __dt__5CNodeFv

lbl_8016CFC4:
	extsh.   r0, r31
	ble      lbl_8016CFD4
	mr       r3, r30
	bl       __dl__FPv

lbl_8016CFD4:
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
 * Address:	8016CFF0
 * Size:	000060
 */
void TObjectNode<GenericObjectMgr>::~TObjectNode()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8016D034
	lis      r5, "__vt__31TObjectNode<16GenericObjectMgr>"@ha
	li       r4, 0
	addi     r0, r5, "__vt__31TObjectNode<16GenericObjectMgr>"@l
	stw      r0, 0(r30)
	bl       __dt__5CNodeFv
	extsh.   r0, r31
	ble      lbl_8016D034
	mr       r3, r30
	bl       __dl__FPv

lbl_8016D034:
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
 * Address:	8016D050
 * Size:	000088
 */
void ObjectMgr<GenericObjectMgr>::~ObjectMgr()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8016D0BC
	lis      r4, "__vt__29ObjectMgr<16GenericObjectMgr>"@ha
	addi     r4, r4, "__vt__29ObjectMgr<16GenericObjectMgr>"@l
	stw      r4, 0(r30)
	addi     r0, r4, 0x2c
	stw      r0, 0x1c(r30)
	beq      lbl_8016D0AC
	lis      r4, "__vt__29Container<16GenericObjectMgr>"@ha
	addi     r0, r4, "__vt__29Container<16GenericObjectMgr>"@l
	stw      r0, 0(r30)
	beq      lbl_8016D0AC
	lis      r5, __vt__16GenericContainer@ha
	li       r4, 0
	addi     r0, r5, __vt__16GenericContainer@l
	stw      r0, 0(r30)
	bl       __dt__5CNodeFv

lbl_8016D0AC:
	extsh.   r0, r31
	ble      lbl_8016D0BC
	mr       r3, r30
	bl       __dl__FPv

lbl_8016D0BC:
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
 * Address:	8016D0D8
 * Size:	000070
 */
void Container<GenericObjectMgr>::~Container()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8016D12C
	lis      r4, "__vt__29Container<16GenericObjectMgr>"@ha
	addi     r0, r4, "__vt__29Container<16GenericObjectMgr>"@l
	stw      r0, 0(r30)
	beq      lbl_8016D11C
	lis      r5, __vt__16GenericContainer@ha
	li       r4, 0
	addi     r0, r5, __vt__16GenericContainer@l
	stw      r0, 0(r30)
	bl       __dt__5CNodeFv

lbl_8016D11C:
	extsh.   r0, r31
	ble      lbl_8016D12C
	mr       r3, r30
	bl       __dl__FPv

lbl_8016D12C:
	lwz      r0, 0x14(r1)
	mr       r3, r30
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

namespace Game {

/*
 * --INFO--
 * Address:	........
 * Size:	0000B8
 */
void PelletMgr::setUseFlagAll(bool)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8016D148
 * Size:	0000F0
 */
void PelletMgr::createManagers(unsigned long)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	li       r3, 0xa4
	bl       __nw__FUl
	or.      r4, r3, r3
	beq      lbl_8016D178
	li       r4, 1
	bl       __ct__Q34Game12PelletNumber3MgrFv
	mr       r4, r3

lbl_8016D178:
	stw      r4, mgr__Q24Game12PelletNumber@sda21(r13)
	mr       r3, r31
	bl       addMgr__Q24Game9PelletMgrFPQ24Game13BasePelletMgr
	li       r3, 0xa4
	bl       __nw__FUl
	or.      r4, r3, r3
	beq      lbl_8016D1A0
	li       r4, 1
	bl       __ct__Q34Game13PelletCarcass3MgrFv
	mr       r4, r3

lbl_8016D1A0:
	stw      r4, mgr__Q24Game13PelletCarcass@sda21(r13)
	mr       r3, r31
	bl       addMgr__Q24Game9PelletMgrFPQ24Game13BasePelletMgr
	li       r3, 0xa4
	bl       __nw__FUl
	or.      r4, r3, r3
	beq      lbl_8016D1C8
	li       r4, 1
	bl       __ct__Q34Game11PelletFruit3MgrFv
	mr       r4, r3

lbl_8016D1C8:
	stw      r4, mgr__Q24Game11PelletFruit@sda21(r13)
	mr       r3, r31
	bl       addMgr__Q24Game9PelletMgrFPQ24Game13BasePelletMgr
	li       r3, 0xa4
	bl       __nw__FUl
	or.      r4, r3, r3
	beq      lbl_8016D1F0
	li       r4, 1
	bl       __ct__Q34Game13PelletOtakara3MgrFv
	mr       r4, r3

lbl_8016D1F0:
	stw      r4, mgr__Q24Game13PelletOtakara@sda21(r13)
	mr       r3, r31
	bl       addMgr__Q24Game9PelletMgrFPQ24Game13BasePelletMgr
	li       r3, 0xa4
	bl       __nw__FUl
	or.      r4, r3, r3
	beq      lbl_8016D218
	li       r4, 1
	bl       __ct__Q34Game10PelletItem3MgrFv
	mr       r4, r3

lbl_8016D218:
	stw      r4, mgr__Q24Game10PelletItem@sda21(r13)
	mr       r3, r31
	bl       addMgr__Q24Game9PelletMgrFPQ24Game13BasePelletMgr
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016D238
 * Size:	000080
 */
void PelletMgr::resetMgrs(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lwz      r3, mgr__Q24Game12PelletNumber@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x28(r12)
	mtctr    r12
	bctrl
	lwz      r3, mgr__Q24Game13PelletCarcass@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x28(r12)
	mtctr    r12
	bctrl
	lwz      r3, mgr__Q24Game11PelletFruit@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x28(r12)
	mtctr    r12
	bctrl
	lwz      r3, mgr__Q24Game10PelletItem@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x38(r12)
	mtctr    r12
	bctrl
	lwz      r3, mgr__Q24Game13PelletOtakara@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x38(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

} // namespace Game

/*
 * --INFO--
 * Address:	8016D2B8
 * Size:	000050
 */
void resetMgr__Q24Game47FixedSizePelletMgr<Game::PelletFruit::Object> Fv(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	addi     r3, r31, 0x70
	lwz      r12, 0x70(r31)
	lwz      r12, 0x80(r12)
	mtctr    r12
	bctrl
	addi     r3, r31, 0x18
	lwz      r12, 0x18(r31)
	lwz      r12, 0x80(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016D308
 * Size:	000050
 */
void resetMgr__Q24Game49FixedSizePelletMgr<Game::PelletCarcass::Object> Fv(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	addi     r3, r31, 0x70
	lwz      r12, 0x70(r31)
	lwz      r12, 0x80(r12)
	mtctr    r12
	bctrl
	addi     r3, r31, 0x18
	lwz      r12, 0x18(r31)
	lwz      r12, 0x80(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016D358
 * Size:	000050
 */
void resetMgr__Q24Game48FixedSizePelletMgr<Game::PelletNumber::Object> Fv(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	addi     r3, r31, 0x70
	lwz      r12, 0x70(r31)
	lwz      r12, 0x80(r12)
	mtctr    r12
	bctrl
	addi     r3, r31, 0x18
	lwz      r12, 0x18(r31)
	lwz      r12, 0x80(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

namespace Game {

/*
 * --INFO--
 * Address:	8016D3A8
 * Size:	000080
 */
void PelletMgr::setupResources(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lwz      r3, mgr__Q24Game12PelletNumber@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x44(r12)
	mtctr    r12
	bctrl
	lwz      r3, mgr__Q24Game13PelletCarcass@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x44(r12)
	mtctr    r12
	bctrl
	lwz      r3, mgr__Q24Game11PelletFruit@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x44(r12)
	mtctr    r12
	bctrl
	lwz      r3, mgr__Q24Game13PelletOtakara@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x44(r12)
	mtctr    r12
	bctrl
	lwz      r3, mgr__Q24Game10PelletItem@sda21(r13)
	lwz      r12, 0(r3)
	lwz      r12, 0x44(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

} // namespace Game

/*
 * --INFO--
 * Address:	........
 * Size:	00050C
 */
void calcNearestTreasure__Q24Game9PelletMgrFR10Vector3f f(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8016D428
 * Size:	00004C
 */
void Iterator<Game::PelletItem::Object>::isDone()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r3, 8(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r0, 4(r31)
	subf     r0, r0, r3
	cntlzw   r0, r0
	srwi     r3, r0, 5
	lwz      r31, 0xc(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016D474
 * Size:	00004C
 */
void Iterator<Game::PelletOtakara::Object>::isDone()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r3, 8(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r0, 4(r31)
	subf     r0, r0, r3
	cntlzw   r0, r0
	srwi     r3, r0, 5
	lwz      r31, 0xc(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

namespace Game {

/*
 * --INFO--
 * Address:	8016D4C0
 * Size:	00021C
 */
void PelletMgr::birth(Game::PelletInitArg*)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	or.      r30, r4, r4
	stw      r29, 0x14(r1)
	mr       r29, r3
	li       r3, 0
	beq      lbl_8016D4F8
	lbz      r0, 0x16(r30)
	cmplwi   r0, 0xff
	beq      lbl_8016D4F8
	li       r3, 1

lbl_8016D4F8:
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016D51C
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x1512
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016D51C:
	lbz      r4, 0x16(r30)
	mr       r3, r29
	bl       getMgrByID__Q24Game9PelletMgrFUc
	or.      r31, r3, r3
	bne      lbl_8016D54C
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x1514
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016D54C:
	lwz      r3, gameSystem__4Game@sda21(r13)
	lwz      r0, 0x44(r3)
	cmpwi    r0, 4
	beq      lbl_8016D618
	cmpwi    r0, 1
	beq      lbl_8016D618
	lbz      r0, mDebug__Q24Game9PelletMgr@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_8016D618
	lbz      r0, 0x17(r30)
	cmplwi   r0, 0
	bne      lbl_8016D618
	lwz      r3, 8(r31)
	lwz      r4, 8(r30)
	bl       getPelletConfig__Q24Game16PelletConfigListFPc
	mr       r4, r3
	addi     r3, r2, lbl_805189F8@sda21
	lwz      r4, 0x180(r4)
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_8016D618
	lbz      r0, 0x16(r30)
	lwz      r4, 0x10(r30)
	cmplwi   r0, 3
	bne      lbl_8016D5E0
	lwz      r3, playData__4Game@sda21(r13)
	lwz      r3, 0xb0(r3)
	addi     r3, r3, 4
	bl       __cl__Q24Game11KindCounterFi
	lbz      r0, 0(r3)
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016D618
	lwz      r3, 8(r31)
	lwz      r4, 8(r30)
	bl       getPelletConfig__Q24Game16PelletConfigListFPc
	li       r3, 0
	b        lbl_8016D6C0

lbl_8016D5E0:
	cmplwi   r0, 4
	bne      lbl_8016D618
	lwz      r3, playData__4Game@sda21(r13)
	lwz      r3, 0xb0(r3)
	addi     r3, r3, 0xc
	bl       __cl__Q24Game11KindCounterFi
	lbz      r0, 0(r3)
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016D618
	lwz      r3, 8(r31)
	lwz      r4, 8(r30)
	bl       getPelletConfig__Q24Game16PelletConfigListFPc
	li       r3, 0
	b        lbl_8016D6C0

lbl_8016D618:
	lbz      r0, 0x1f(r30)
	cmplwi   r0, 0
	beq      lbl_8016D68C
	lwz      r3, 8(r31)
	lwz      r4, 8(r30)
	bl       getPelletConfig__Q24Game16PelletConfigListFPc
	lwz      r12, 0(r31)
	mr       r4, r3
	mr       r3, r31
	lwz      r12, 0x48(r12)
	mtctr    r12
	bctrl
	or.      r29, r3, r3
	beq      lbl_8016D684
	mr       r3, r31
	lwz      r4, 0x440(r29)
	lwz      r12, 0(r31)
	lwz      r12, 0x4c(r12)
	mtctr    r12
	bctrl
	li       r0, 1
	mr       r3, r29
	stb      r0, 0x1c(r30)
	mr       r4, r30
	bl       init__Q24Game8CreatureFPQ24Game15CreatureInitArg
	mr       r3, r29
	b        lbl_8016D6C0

lbl_8016D684:
	li       r3, 0
	b        lbl_8016D6C0

lbl_8016D68C:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x3c(r12)
	mtctr    r12
	bctrl
	or.      r29, r3, r3
	beq      lbl_8016D6BC
	lwz      r0, 0x18(r30)
	mr       r4, r30
	stw      r0, 0x358(r29)
	stw      r31, 0x454(r29)
	bl       init__Q24Game8CreatureFPQ24Game15CreatureInitArg

lbl_8016D6BC:
	mr       r3, r29

lbl_8016D6C0:
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
 * Address:	8016D6DC
 * Size:	0001AC
 */
void PelletMgr::setUse(Game::PelletInitArg*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	li       r3, 0
	stw      r30, 8(r1)
	or.      r30, r4, r4
	beq      lbl_8016D710
	lbz      r0, 0x16(r30)
	cmplwi   r0, 0xff
	beq      lbl_8016D710
	li       r3, 1

lbl_8016D710:
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016D734
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x159b
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016D734:
	lbz      r4, 0x16(r30)
	mr       r3, r31
	bl       getMgrByID__Q24Game9PelletMgrFUc
	or.      r31, r3, r3
	bne      lbl_8016D764
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x159d
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016D764:
	lwz      r3, gameSystem__4Game@sda21(r13)
	lwz      r0, 0x44(r3)
	cmpwi    r0, 4
	beq      lbl_8016D81C
	lbz      r0, 0x17(r30)
	cmplwi   r0, 0
	bne      lbl_8016D81C
	lwz      r3, 8(r31)
	lwz      r4, 8(r30)
	bl       getPelletConfig__Q24Game16PelletConfigListFPc
	mr       r4, r3
	addi     r3, r2, lbl_805189F8@sda21
	lwz      r4, 0x180(r4)
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_8016D81C
	lbz      r0, 0x16(r30)
	lwz      r4, 0x10(r30)
	cmplwi   r0, 3
	bne      lbl_8016D7E4
	lwz      r3, playData__4Game@sda21(r13)
	lwz      r3, 0xb0(r3)
	addi     r3, r3, 4
	bl       __cl__Q24Game11KindCounterFi
	lbz      r0, 0(r3)
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016D81C
	lwz      r3, 8(r31)
	lwz      r4, 8(r30)
	bl       getPelletConfig__Q24Game16PelletConfigListFPc
	li       r3, 0
	b        lbl_8016D870

lbl_8016D7E4:
	cmplwi   r0, 4
	bne      lbl_8016D81C
	lwz      r3, playData__4Game@sda21(r13)
	lwz      r3, 0xb0(r3)
	addi     r3, r3, 0xc
	bl       __cl__Q24Game11KindCounterFi
	lbz      r0, 0(r3)
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016D81C
	lwz      r3, 8(r31)
	lwz      r4, 8(r30)
	bl       getPelletConfig__Q24Game16PelletConfigListFPc
	li       r3, 0
	b        lbl_8016D870

lbl_8016D81C:
	lwz      r30, 0x10(r30)
	li       r3, 0
	cmpwi    r30, 0
	blt      lbl_8016D83C
	lwz      r0, 0x50(r31)
	cmpw     r30, r0
	bge      lbl_8016D83C
	li       r3, 1

lbl_8016D83C:
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016D860
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x1143
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016D860:
	lwz      r4, 0x4c(r31)
	li       r0, 1
	li       r3, 1
	stbx     r0, r4, r30

lbl_8016D870:
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
 * Address:	8016D888
 * Size:	00015C
 */
void PelletMgr::OtakaraItemCode::isNull(void)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	mr       r29, r3
	lis      r3, lbl_8047E318@ha
	lha      r6, 0(r29)
	addi     r31, r3, lbl_8047E318@l
	extsh.   r0, r6
	bne      lbl_8016D8C0
	li       r3, 1
	b        lbl_8016D9C8

lbl_8016D8C0:
	srawi    r0, r6, 8
	li       r30, 0
	clrlwi   r0, r0, 0x18
	cmplwi   r0, 3
	bne      lbl_8016D8DC
	lwz      r30, mgr__Q24Game13PelletOtakara@sda21(r13)
	b        lbl_8016D8E8

lbl_8016D8DC:
	cmplwi   r0, 4
	bne      lbl_8016D8E8
	lwz      r30, mgr__Q24Game10PelletItem@sda21(r13)

lbl_8016D8E8:
	cmplwi   r30, 0
	bne      lbl_8016D904
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x190
	li       r4, 0x15c6
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016D904:
	lha      r6, 0(r29)
	clrlwi.  r7, r6, 0x18
	blt      lbl_8016D920
	lwz      r3, 8(r30)
	lwz      r0, 0x18(r3)
	cmpw     r7, r0
	blt      lbl_8016D928

lbl_8016D920:
	li       r30, 0
	b        lbl_8016D934

lbl_8016D928:
	mulli    r0, r7, 0x260
	lwz      r3, 0x1c(r3)
	add      r30, r3, r0

lbl_8016D934:
	cmplwi   r30, 0
	bne      lbl_8016D950
	addi     r3, r31, 0x2c
	addi     r5, r31, 0x1a4
	li       r4, 0x15ca
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016D950:
	lwz      r4, 0x180(r30)
	addi     r3, r2, lbl_805189F8@sda21
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_8016D9C4
	lha      r3, 0(r29)
	srawi    r0, r3, 8
	clrlwi   r4, r3, 0x18
	clrlwi   r0, r0, 0x18
	cmplwi   r0, 3
	bne      lbl_8016D9A0
	lwz      r3, playData__4Game@sda21(r13)
	lwz      r3, 0xb0(r3)
	addi     r3, r3, 4
	bl       __cl__Q24Game11KindCounterFi
	lbz      r0, 0(r3)
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016D9C4
	li       r3, 1
	b        lbl_8016D9C8

lbl_8016D9A0:
	lwz      r3, playData__4Game@sda21(r13)
	lwz      r3, 0xb0(r3)
	addi     r3, r3, 0xc
	bl       __cl__Q24Game11KindCounterFi
	lbz      r0, 0(r3)
	rlwinm.  r0, r0, 0, 0x1e, 0x1e
	beq      lbl_8016D9C4
	li       r3, 1
	b        lbl_8016D9C8

lbl_8016D9C4:
	li       r3, 0

lbl_8016D9C8:
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
 * Address:	8016D9E4
 * Size:	0000C8
 */
void PelletMgr::makePelletInitArg(Game::PelletInitArg&, char*)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stmw     r27, 0xc(r1)
	mr       r27, r3
	mr       r29, r5
	mr       r28, r4
	mr       r4, r29
	lwz      r31, mgr__Q24Game13PelletOtakara@sda21(r13)
	lwz      r3, 8(r31)
	bl       getPelletConfig__Q24Game16PelletConfigListFPc
	cmplwi   r3, 0
	mr       r30, r3
	bne      lbl_8016DA30
	lwz      r31, mgr__Q24Game10PelletItem@sda21(r13)
	mr       r4, r29
	lwz      r3, 8(r31)
	bl       getPelletConfig__Q24Game16PelletConfigListFPc
	mr       r30, r3

lbl_8016DA30:
	cmplwi   r30, 0
	bne      lbl_8016DA58
	lis      r3, lbl_8047E344@ha
	lis      r4, lbl_8047E4E8@ha
	addi     r5, r4, lbl_8047E4E8@l
	mr       r6, r29
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x15ee
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016DA58:
	stw      r29, 8(r28)
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x5c(r12)
	mtctr    r12
	bctrl
	stb      r3, 0x16(r28)
	li       r0, 0
	mr       r3, r27
	mr       r4, r28
	lha      r6, 0x258(r30)
	mr       r5, r29
	stw      r6, 0x10(r28)
	stw      r0, 0x18(r28)
	bl       makeVsCarryMinMax__Q24Game9PelletMgrFRQ24Game13PelletInitArgPc
	lmw      r27, 0xc(r1)
	li       r3, 1
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016DAAC
 * Size:	0000E4
 */
void PelletMgr::makeVsCarryMinMax(Game::PelletInitArg&, char*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r5
	stw      r30, 8(r1)
	mr       r30, r4
	lwz      r3, gameSystem__4Game@sda21(r13)
	cmplwi   r3, 0
	beq      lbl_8016DB78
	lwz      r0, 0x44(r3)
	cmpwi    r0, 1
	bne      lbl_8016DB78
	lwz      r3, cBedamaYellow__13VsOtakaraName@sda21(r13)
	mr       r4, r31
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_8016DB08
	li       r3, 1
	li       r0, 8
	stw      r3, 0x20(r30)
	stw      r0, 0x24(r30)
	b        lbl_8016DB78

lbl_8016DB08:
	lwz      r3, cBedamaRed__13VsOtakaraName@sda21(r13)
	mr       r4, r31
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_8016DB30
	li       r3, 1
	li       r0, 8
	stw      r3, 0x20(r30)
	stw      r0, 0x24(r30)
	b        lbl_8016DB78

lbl_8016DB30:
	lwz      r3, cBedamaBlue__13VsOtakaraName@sda21(r13)
	mr       r4, r31
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_8016DB58
	li       r3, 1
	li       r0, 8
	stw      r3, 0x20(r30)
	stw      r0, 0x24(r30)
	b        lbl_8016DB78

lbl_8016DB58:
	lwz      r3, cCoin__13VsOtakaraName@sda21(r13)
	mr       r4, r31
	bl       strcmp
	cmpwi    r3, 0
	bne      lbl_8016DB78
	li       r0, 1
	stw      r0, 0x20(r30)
	stw      r0, 0x24(r30)

lbl_8016DB78:
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
 * Address:	8016DB90
 * Size:	0002EC
 */
void PelletMgr::makePelletInitArg(Game::PelletInitArg&, Game::PelletMgr::OtakaraItemCode&)
{
	/*
	.loc_0x0:
	  stwu      r1, -0x20(r1)
	  mflr      r0
	  lis       r3, 0x8048
	  stw       r0, 0x24(r1)
	  stw       r31, 0x1C(r1)
	  subi      r31, r3, 0x1CE8
	  stw       r30, 0x18(r1)
	  mr        r30, r5
	  stw       r29, 0x14(r1)
	  mr        r29, r4
	  stw       r28, 0x10(r1)
	  lha       r6, 0x0(r5)
	  extsh.    r0, r6
	  bne-      .loc_0x40
	  li        r0, 0x1
	  b         .loc_0x148

	.loc_0x40:
	  srawi     r0, r6, 0x8
	  li        r28, 0
	  rlwinm    r0,r0,0,24,31
	  cmplwi    r0, 0x3
	  bne-      .loc_0x5C
	  lwz       r28, -0x6AE0(r13)
	  b         .loc_0x68

	.loc_0x5C:
	  cmplwi    r0, 0x4
	  bne-      .loc_0x68
	  lwz       r28, -0x6AD8(r13)

	.loc_0x68:
	  cmplwi    r28, 0
	  bne-      .loc_0x84
	  addi      r3, r31, 0x2C
	  addi      r5, r31, 0x190
	  li        r4, 0x15C6
	  crclr     6, 0x6
	  bl        -0x1435D0

	.loc_0x84:
	  lha       r6, 0x0(r30)
	  rlwinm.   r7,r6,0,24,31
	  blt-      .loc_0xA0
	  lwz       r3, 0x8(r28)
	  lwz       r0, 0x18(r3)
	  cmpw      r7, r0
	  blt-      .loc_0xA8

	.loc_0xA0:
	  li        r28, 0
	  b         .loc_0xB4

	.loc_0xA8:
	  mulli     r0, r7, 0x260
	  lwz       r3, 0x1C(r3)
	  add       r28, r3, r0

	.loc_0xB4:
	  cmplwi    r28, 0
	  bne-      .loc_0xD0
	  addi      r3, r31, 0x2C
	  addi      r5, r31, 0x1A4
	  li        r4, 0x15CA
	  crclr     6, 0x6
	  bl        -0x14361C

	.loc_0xD0:
	  lwz       r4, 0x180(r28)
	  subi      r3, r2, 0x5968
	  bl        -0xA35A8
	  cmpwi     r3, 0
	  bne-      .loc_0x144
	  lha       r3, 0x0(r30)
	  srawi     r0, r3, 0x8
	  rlwinm    r4,r3,0,24,31
	  rlwinm    r0,r0,0,24,31
	  cmplwi    r0, 0x3
	  bne-      .loc_0x120
	  lwz       r3, -0x6B70(r13)
	  lwz       r3, 0xB0(r3)
	  addi      r3, r3, 0x4
	  bl        0x77768
	  lbz       r0, 0x0(r3)
	  rlwinm.   r0,r0,0,30,30
	  beq-      .loc_0x144
	  li        r0, 0x1
	  b         .loc_0x148

	.loc_0x120:
	  lwz       r3, -0x6B70(r13)
	  lwz       r3, 0xB0(r3)
	  addi      r3, r3, 0xC
	  bl        0x77744
	  lbz       r0, 0x0(r3)
	  rlwinm.   r0,r0,0,30,30
	  beq-      .loc_0x144
	  li        r0, 0x1
	  b         .loc_0x148

	.loc_0x144:
	  li        r0, 0

	.loc_0x148:
	  rlwinm.   r0,r0,0,24,31
	  beq-      .loc_0x158
	  li        r3, 0
	  b         .loc_0x2CC

	.loc_0x158:
	  lha       r6, 0x0(r30)
	  li        r28, 0
	  srawi     r0, r6, 0x8
	  rlwinm    r0,r0,0,24,31
	  cmplwi    r0, 0x3
	  bne-      .loc_0x178
	  lwz       r28, -0x6AE0(r13)
	  b         .loc_0x184

	.loc_0x178:
	  cmplwi    r0, 0x4
	  bne-      .loc_0x184
	  lwz       r28, -0x6AD8(r13)

	.loc_0x184:
	  cmplwi    r28, 0
	  bne-      .loc_0x1A0
	  addi      r3, r31, 0x2C
	  addi      r5, r31, 0x190
	  li        r4, 0x1628
	  crclr     6, 0x6
	  bl        -0x1436EC

	.loc_0x1A0:
	  lha       r6, 0x0(r30)
	  rlwinm.   r7,r6,0,24,31
	  blt-      .loc_0x1BC
	  lwz       r3, 0x8(r28)
	  lwz       r0, 0x18(r3)
	  cmpw      r7, r0
	  blt-      .loc_0x1C4

	.loc_0x1BC:
	  li        r28, 0
	  b         .loc_0x1D0

	.loc_0x1C4:
	  mulli     r0, r7, 0x260
	  lwz       r3, 0x1C(r3)
	  add       r28, r3, r0

	.loc_0x1D0:
	  cmplwi    r28, 0
	  bne-      .loc_0x1EC
	  addi      r3, r31, 0x2C
	  addi      r5, r31, 0x1A4
	  li        r4, 0x162C
	  crclr     6, 0x6
	  bl        -0x143738

	.loc_0x1EC:
	  lwz       r3, 0x40(r28)
	  li        r0, 0
	  stw       r3, 0x8(r29)
	  lha       r3, 0x0(r30)
	  srawi     r3, r3, 0x8
	  stb       r3, 0x16(r29)
	  lha       r3, 0x0(r30)
	  rlwinm    r3,r3,0,24,31
	  stw       r3, 0x10(r29)
	  stw       r0, 0x18(r29)
	  lwz       r3, -0x6C18(r13)
	  lwz       r28, 0x8(r29)
	  cmplwi    r3, 0
	  beq-      .loc_0x2C8
	  lwz       r0, 0x44(r3)
	  cmpwi     r0, 0x1
	  bne-      .loc_0x2C8
	  lwz       r3, -0x7B7C(r13)
	  mr        r4, r28
	  bl        -0xA3708
	  cmpwi     r3, 0
	  bne-      .loc_0x258
	  li        r3, 0x1
	  li        r0, 0x8
	  stw       r3, 0x20(r29)
	  stw       r0, 0x24(r29)
	  b         .loc_0x2C8

	.loc_0x258:
	  lwz       r3, -0x7B80(r13)
	  mr        r4, r28
	  bl        -0xA3730
	  cmpwi     r3, 0
	  bne-      .loc_0x280
	  li        r3, 0x1
	  li        r0, 0x8
	  stw       r3, 0x20(r29)
	  stw       r0, 0x24(r29)
	  b         .loc_0x2C8

	.loc_0x280:
	  lwz       r3, -0x7B84(r13)
	  mr        r4, r28
	  bl        -0xA3758
	  cmpwi     r3, 0
	  bne-      .loc_0x2A8
	  li        r3, 0x1
	  li        r0, 0x8
	  stw       r3, 0x20(r29)
	  stw       r0, 0x24(r29)
	  b         .loc_0x2C8

	.loc_0x2A8:
	  lwz       r3, -0x7B88(r13)
	  mr        r4, r28
	  bl        -0xA3780
	  cmpwi     r3, 0
	  bne-      .loc_0x2C8
	  li        r0, 0x1
	  stw       r0, 0x20(r29)
	  stw       r0, 0x24(r29)

	.loc_0x2C8:
	  li        r3, 0x1

	.loc_0x2CC:
	  lwz       r0, 0x24(r1)
	  lwz       r31, 0x1C(r1)
	  lwz       r30, 0x18(r1)
	  lwz       r29, 0x14(r1)
	  lwz       r28, 0x10(r1)
	  mtlr      r0
	  addi      r1, r1, 0x20
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8016DE7C
 * Size:	000060
 */
void PelletMgr::makeOtakaraItemCode(char*, Game::PelletMgr::OtakaraItemCode&)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	mr       r3, r4
	stw      r0, 0x24(r1)
	addi     r4, r1, 8
	stw      r31, 0x1c(r1)
	mr       r31, r5
	bl getConfigAndKind__Q34Game10PelletList3MgrFPcRQ34Game10PelletList5cKind
	cmplwi   r3, 0
	beq      lbl_8016DEC0
	lha      r0, 0x258(r3)
	lwz      r4, 8(r1)
	clrlwi   r0, r0, 0x18
	rlwinm   r3, r4, 8, 0x10, 0x17
	add      r0, r3, r0
	sth      r0, 0(r31)
	b        lbl_8016DEC8

lbl_8016DEC0:
	li       r0, 0
	sth      r0, 0(r31)

lbl_8016DEC8:
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016DEDC
 * Size:	000034
 */
void PelletMgr::OtakaraItemCode::read(Stream&)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	mr       r3, r4
	bl       readShort__6StreamFv
	sth      r3, 0(r31)
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016DF10
 * Size:	000060
 */
void PelletMgr::OtakaraItemCode::write(Stream&)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	mr       r30, r3
	mr       r3, r31
	lwz      r4, 0x414(r4)
	bl       textWriteTab__6StreamFi
	lha      r4, 0(r30)
	mr       r3, r31
	bl       writeShort__6StreamFs
	lis      r4, lbl_8047E500@ha
	mr       r3, r31
	addi     r4, r4, lbl_8047E500@l
	crclr    6
	bl       textWriteText__6StreamFPce
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
 * Address:	8016DF70
 * Size:	00006C
 */
void PelletMgr::addMgr(Game::BasePelletMgr*)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r29, 0x14(r1)
	mr       r29, r3
	li       r3, 0x1c
	bl       __nw__FUl
	or.      r31, r3, r3
	beq      lbl_8016DFB0
	bl       __ct__5CNodeFv
	lis      r3, "__vt__31TObjectNode<16GenericObjectMgr>"@ha
	addi     r0, r3, "__vt__31TObjectNode<16GenericObjectMgr>"@l
	stw      r0, 0(r31)

lbl_8016DFB0:
	stw      r30, 0x18(r31)
	mr       r4, r31
	addi     r3, r29, 0x20
	bl       add__5CNodeFP5CNode
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
 * Address:	8016DFDC
 * Size:	0001E4
 */
void PelletMgr::doAnimation(void)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__28Iterator<16GenericObjectMgr>"@l
	cmplwi   r0, 0
	stw      r0, 0x14(r1)
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8016E024
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E190

lbl_8016E024:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E090

lbl_8016E03C:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016E190
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016E090:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016E03C
	b        lbl_8016E190

lbl_8016E0B0:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_8016E100
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E190

lbl_8016E100:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E174

lbl_8016E120:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016E190
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016E174:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016E120

lbl_8016E190:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_8016E0B0
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

} // namespace Game

/*
 * --INFO--
 * Address:	8016E1C0
 * Size:	00004C
 */
void Iterator<GenericObjectMgr>::isDone()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r3, 8(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r0, 4(r31)
	subf     r0, r0, r3
	cntlzw   r0, r0
	srwi     r3, r0, 5
	lwz      r31, 0xc(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

namespace Game {

/*
 * --INFO--
 * Address:	8016E20C
 * Size:	0001E4
 */
void PelletMgr::doEntry(void)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__28Iterator<16GenericObjectMgr>"@l
	cmplwi   r0, 0
	stw      r0, 0x14(r1)
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8016E254
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E3C0

lbl_8016E254:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E2C0

lbl_8016E26C:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016E3C0
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016E2C0:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016E26C
	b        lbl_8016E3C0

lbl_8016E2E0:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_8016E330
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E3C0

lbl_8016E330:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E3A4

lbl_8016E350:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016E3C0
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016E3A4:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016E350

lbl_8016E3C0:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_8016E2E0
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016E3F0
 * Size:	0001F4
 */
void PelletMgr::doSetView(int)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r5, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r5, r5, "__vt__28Iterator<16GenericObjectMgr>"@l
	stw      r31, 0x1c(r1)
	cmplwi   r0, 0
	mr       r31, r4
	stw      r0, 0x14(r1)
	stw      r5, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8016E440
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E5B0

lbl_8016E440:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E4AC

lbl_8016E458:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016E5B0
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016E4AC:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016E458
	b        lbl_8016E5B0

lbl_8016E4CC:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	mr       r4, r31
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_8016E520
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E5B0

lbl_8016E520:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E594

lbl_8016E540:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016E5B0
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016E594:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016E540

lbl_8016E5B0:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_8016E4CC
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016E5E4
 * Size:	0001E4
 */
void PelletMgr::doViewCalc(void)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__28Iterator<16GenericObjectMgr>"@l
	cmplwi   r0, 0
	stw      r0, 0x14(r1)
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8016E62C
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E798

lbl_8016E62C:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E698

lbl_8016E644:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016E798
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016E698:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016E644
	b        lbl_8016E798

lbl_8016E6B8:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_8016E708
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E798

lbl_8016E708:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E77C

lbl_8016E728:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016E798
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016E77C:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016E728

lbl_8016E798:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_8016E6B8
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016E7C8
 * Size:	0001F4
 */
void PelletMgr::doSimulation(float)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__28Iterator<16GenericObjectMgr>"@l
	stfd     f31, 0x18(r1)
	fmr      f31, f1
	cmplwi   r0, 0
	stw      r4, 8(r1)
	stw      r0, 0x14(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8016E818
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E988

lbl_8016E818:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E884

lbl_8016E830:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016E988
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016E884:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016E830
	b        lbl_8016E988

lbl_8016E8A4:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	fmr      f1, f31
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_8016E8F8
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E988

lbl_8016E8F8:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016E96C

lbl_8016E918:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016E988
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016E96C:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016E918

lbl_8016E988:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_8016E8A4
	lwz      r0, 0x24(r1)
	lfd      f31, 0x18(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016E9BC
 * Size:	000004
 */
void PelletMgr::doDirectDraw(Graphics&) { }

/*
 * --INFO--
 * Address:	8016E9C0
 * Size:	0001F4
 */
void PelletMgr::doSimpleDraw(Viewport*)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r5, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r5, r5, "__vt__28Iterator<16GenericObjectMgr>"@l
	stw      r31, 0x1c(r1)
	cmplwi   r0, 0
	mr       r31, r4
	stw      r0, 0x14(r1)
	stw      r5, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8016EA10
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016EB80

lbl_8016EA10:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016EA7C

lbl_8016EA28:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016EB80
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016EA7C:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016EA28
	b        lbl_8016EB80

lbl_8016EA9C:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	mr       r4, r31
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_8016EAF0
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016EB80

lbl_8016EAF0:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016EB64

lbl_8016EB10:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016EB80
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016EB64:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016EB10

lbl_8016EB80:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_8016EA9C
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016EBB4
 * Size:	0001D4
 */
void PelletMgr::setupSoundViewerAndBas(void)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__28Iterator<16GenericObjectMgr>"@l
	cmplwi   r0, 0
	stw      r0, 0x14(r1)
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8016EBFC
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016ED58

lbl_8016EBFC:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016EC68

lbl_8016EC14:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016ED58
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016EC68:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016EC14
	b        lbl_8016ED58

lbl_8016EC88:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_8016ECC8
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016ED58

lbl_8016ECC8:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016ED3C

lbl_8016ECE8:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016ED58
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016ED3C:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016ECE8

lbl_8016ED58:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_8016EC88
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016ED88
 * Size:	000014
 */
void PelletMgr::decode(long, unsigned char&, int&)
{
	/*
	srwi     r3, r4, 0x18
	clrlwi   r0, r4, 8
	stb      r3, 0(r5)
	stw      r0, 0(r6)
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016ED9C
 * Size:	00000C
 */
void PelletMgr::encode(unsigned char, int)
{
	/*
	slwi     r0, r4, 0x18
	or       r3, r0, r5
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016EDA8
 * Size:	0000B4
 */
char* PelletMgr::getCaveName(int)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	srwi     r0, r4, 0x18
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	clrlwi   r30, r4, 8
	mr       r4, r0
	bl       getMgrByID__Q24Game9PelletMgrFUc
	or.      r31, r3, r3
	bne      lbl_8016EDF0
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x16f9
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016EDF0:
	cmpwi    r30, 0
	blt      lbl_8016EE08
	lwz      r3, 8(r31)
	lwz      r0, 0x18(r3)
	cmpw     r30, r0
	blt      lbl_8016EE10

lbl_8016EE08:
	li       r31, 0
	b        lbl_8016EE1C

lbl_8016EE10:
	mulli    r0, r30, 0x260
	lwz      r3, 0x1c(r3)
	add      r31, r3, r0

lbl_8016EE1C:
	cmplwi   r31, 0
	bne      lbl_8016EE40
	lis      r3, lbl_8047E344@ha
	lis      r5, lbl_8047E354@ha
	addi     r3, r3, lbl_8047E344@l
	li       r4, 0x16fb
	addi     r5, r5, lbl_8047E354@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8016EE40:
	lwz      r0, 0x14(r1)
	lwz      r3, 0x40(r31)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016EE5C
 * Size:	000270
 */
void PelletMgr::getCaveID(char*)
{
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	lis      r5, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x34(r1)
	li       r0, 0
	addi     r5, r5, "__vt__28Iterator<16GenericObjectMgr>"@l
	stmw     r27, 0x1c(r1)
	cmplwi   r0, 0
	mr       r31, r4
	stw      r0, 0x14(r1)
	stw      r5, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8016EEAC
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016F094

lbl_8016EEAC:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016EF18

lbl_8016EEC4:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016F094
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016EF18:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016EEC4
	b        lbl_8016F094

lbl_8016EF38:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	li       r27, 0
	li       r29, 0
	mr       r28, r3
	b        lbl_8016EFC8

lbl_8016EF5C:
	cmpwi    r27, 0
	blt      lbl_8016EF6C
	cmpw     r27, r0
	blt      lbl_8016EF74

lbl_8016EF6C:
	li       r3, 0
	b        lbl_8016EF7C

lbl_8016EF74:
	lwz      r0, 0x1c(r3)
	add      r3, r0, r29

lbl_8016EF7C:
	lwz      r30, 0x40(r3)
	mr       r3, r31
	bl       strlen
	mr       r5, r3
	mr       r3, r30
	mr       r4, r31
	bl       strncmp
	cmpwi    r3, 0
	bne      lbl_8016EFC0
	mr       r3, r28
	lwz      r12, 0(r28)
	lwz      r12, 0x5c(r12)
	mtctr    r12
	bctrl
	slwi     r0, r3, 0x18
	or       r3, r0, r27
	b        lbl_8016F0B8

lbl_8016EFC0:
	addi     r29, r29, 0x260
	addi     r27, r27, 1

lbl_8016EFC8:
	lwz      r3, 8(r28)
	lwz      r0, 0x18(r3)
	cmpw     r27, r0
	blt      lbl_8016EF5C
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_8016F004
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016F094

lbl_8016F004:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016F078

lbl_8016F024:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016F094
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016F078:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016F024

lbl_8016F094:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_8016EF38
	li       r3, -1

lbl_8016F0B8:
	lmw      r27, 0x1c(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	000200
 */
void PelletMgr::getMgrByIndex(int)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8016F0CC
 * Size:	00021C
 */
void PelletMgr::getMgrByID(unsigned char)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r5, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r5, r5, "__vt__28Iterator<16GenericObjectMgr>"@l
	stw      r31, 0x1c(r1)
	cmplwi   r0, 0
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r0, 0x14(r1)
	stw      r5, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8016F120
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016F1A8

lbl_8016F120:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016F18C

lbl_8016F138:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016F1A8
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016F18C:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016F138

lbl_8016F1A8:
	clrlwi   r31, r30, 0x18
	b        lbl_8016F2AC

lbl_8016F1B0:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	mr       r0, r3
	mr       r30, r0
	lwz      r12, 0x5c(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	cmplw    r31, r0
	bne      lbl_8016F1F0
	mr       r3, r30
	b        lbl_8016F2D0

lbl_8016F1F0:
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_8016F21C
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016F2AC

lbl_8016F21C:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8016F290

lbl_8016F23C:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016F2AC
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8016F290:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016F23C

lbl_8016F2AC:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_8016F1B0
	li       r3, 0

lbl_8016F2D0:
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000BC
 */
void PelletMgr::dumpAllPellets(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8016F2E8
 * Size:	0000E0
 */
PelletMgr::~PelletMgr(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	or.      r31, r3, r3
	stw      r30, 8(r1)
	mr       r30, r4
	beq      lbl_8016F3AC
	lis      r3, __vt__Q24Game9PelletMgr@ha
	addi     r3, r3, __vt__Q24Game9PelletMgr@l
	stw      r3, 0(r31)
	addi     r0, r3, 0x2c
	stw      r0, 0x1c(r31)
	beq      lbl_8016F39C
	lis      r3, "__vt__33NodeObjectMgr<16GenericObjectMgr>"@ha
	addic.   r0, r31, 0x20
	addi     r3, r3, "__vt__33NodeObjectMgr<16GenericObjectMgr>"@l
	stw      r3, 0(r31)
	addi     r0, r3, 0x2c
	stw      r0, 0x1c(r31)
	beq      lbl_8016F354
	lis      r4, "__vt__31TObjectNode<16GenericObjectMgr>"@ha
	addi     r3, r31, 0x20
	addi     r0, r4, "__vt__31TObjectNode<16GenericObjectMgr>"@l
	li       r4, 0
	stw      r0, 0x20(r31)
	bl       __dt__5CNodeFv

lbl_8016F354:
	cmplwi   r31, 0
	beq      lbl_8016F39C
	lis      r3, "__vt__29ObjectMgr<16GenericObjectMgr>"@ha
	addi     r3, r3, "__vt__29ObjectMgr<16GenericObjectMgr>"@l
	stw      r3, 0(r31)
	addi     r0, r3, 0x2c
	stw      r0, 0x1c(r31)
	beq      lbl_8016F39C
	lis      r3, "__vt__29Container<16GenericObjectMgr>"@ha
	addi     r0, r3, "__vt__29Container<16GenericObjectMgr>"@l
	stw      r0, 0(r31)
	beq      lbl_8016F39C
	lis      r4, __vt__16GenericContainer@ha
	mr       r3, r31
	addi     r0, r4, __vt__16GenericContainer@l
	li       r4, 0
	stw      r0, 0(r31)
	bl       __dt__5CNodeFv

lbl_8016F39C:
	extsh.   r0, r30
	ble      lbl_8016F3AC
	mr       r3, r31
	bl       __dl__FPv

lbl_8016F3AC:
	lwz      r0, 0x14(r1)
	mr       r3, r31
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F3C8
 * Size:	00000C
 */
char* PelletMgr::getMgrName(void)
{
	/*
	lis      r3, lbl_8047E494@ha
	addi     r3, r3, lbl_8047E494@l
	blr
	*/
}

} // namespace Game

/*
 * --INFO--
 * Address:	8016F3D4
 * Size:	000038
 */
void Iterator<GenericObjectMgr>::operator*()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	mr       r4, r3
	stw      r0, 0x14(r1)
	lwz      r3, 8(r3)
	lwz      r4, 4(r4)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F40C
 * Size:	0000E4
 */
void Iterator<GenericObjectMgr>::next()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 0xc(r3)
	cmplwi   r0, 0
	bne      lbl_8016F44C
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F4DC

lbl_8016F44C:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F4C0

lbl_8016F46C:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0xc(r31)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016F4DC
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)

lbl_8016F4C0:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016F46C

lbl_8016F4DC:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F4F0
 * Size:	0000DC
 */
void Iterator<GenericObjectMgr>::first()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 0xc(r3)
	cmplwi   r0, 0
	bne      lbl_8016F52C
	lwz      r3, 8(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F5B8

lbl_8016F52C:
	lwz      r3, 8(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F59C

lbl_8016F548:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0xc(r31)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016F5B8
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)

lbl_8016F59C:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016F548

lbl_8016F5B8:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F5CC
 * Size:	000038
 */
void Iterator<Game::PelletItem::Object>::operator*()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	mr       r4, r3
	stw      r0, 0x14(r1)
	lwz      r3, 8(r3)
	lwz      r4, 4(r4)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F604
 * Size:	0000E4
 */
void Iterator<Game::PelletItem::Object>::next()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 0xc(r3)
	cmplwi   r0, 0
	bne      lbl_8016F644
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F6D4

lbl_8016F644:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F6B8

lbl_8016F664:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0xc(r31)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016F6D4
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)

lbl_8016F6B8:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016F664

lbl_8016F6D4:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F6E8
 * Size:	0000DC
 */
void Iterator<Game::PelletItem::Object>::first()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 0xc(r3)
	cmplwi   r0, 0
	bne      lbl_8016F724
	lwz      r3, 8(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F7B0

lbl_8016F724:
	lwz      r3, 8(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F794

lbl_8016F740:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0xc(r31)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016F7B0
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)

lbl_8016F794:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016F740

lbl_8016F7B0:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F7C4
 * Size:	000038
 */
void Iterator<Game::PelletOtakara::Object>::operator*()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	mr       r4, r3
	stw      r0, 0x14(r1)
	lwz      r3, 8(r3)
	lwz      r4, 4(r4)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F7FC
 * Size:	0000E4
 */
void Iterator<Game::PelletOtakara::Object>::next()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 0xc(r3)
	cmplwi   r0, 0
	bne      lbl_8016F83C
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F8CC

lbl_8016F83C:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F8B0

lbl_8016F85C:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0xc(r31)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016F8CC
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)

lbl_8016F8B0:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016F85C

lbl_8016F8CC:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F8E0
 * Size:	0000DC
 */
void Iterator<Game::PelletOtakara::Object>::first()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 0xc(r3)
	cmplwi   r0, 0
	bne      lbl_8016F91C
	lwz      r3, 8(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F9A8

lbl_8016F91C:
	lwz      r3, 8(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_8016F98C

lbl_8016F938:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0xc(r31)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016F9A8
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)

lbl_8016F98C:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016F938

lbl_8016F9A8:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F9BC
 * Size:	000008
 */
void generatorBirth__Q24Game13BasePelletMgrFR10Vector3f R10Vector3f PQ24Game13GenPelletParm(void) { return 0x0; }

namespace Game {

/*
 * --INFO--
 * Address:	8016F9C4
 * Size:	000004
 */
void BasePelletMgr::generatorWrite(Stream&, Game::GenPelletParm*) { }

/*
 * --INFO--
 * Address:	8016F9C8
 * Size:	000004
 */
void BasePelletMgr::generatorRead(Stream&, Game::GenPelletParm*, unsigned long) { }

/*
 * --INFO--
 * Address:	8016F9CC
 * Size:	00000C
 */
void BasePelletMgr::generatorLocalVersion(void)
{
	/*
	lis      r3, 0x30303030@ha
	addi     r3, r3, 0x30303030@l
	blr
	*/
}

/*
 * --INFO--
 * Address:	8016F9D8
 * Size:	000004
 */
void BasePelletMgr::doAnimation(void) { }

/*
 * --INFO--
 * Address:	8016F9DC
 * Size:	000004
 */
void BasePelletMgr::doEntry(void) { }

/*
 * --INFO--
 * Address:	8016F9E0
 * Size:	000004
 */
void BasePelletMgr::doSetView(int) { }

/*
 * --INFO--
 * Address:	8016F9E4
 * Size:	000004
 */
void BasePelletMgr::doViewCalc(void) { }

/*
 * --INFO--
 * Address:	8016F9E8
 * Size:	000004
 */
void BasePelletMgr::doSimulation(float) { }

/*
 * --INFO--
 * Address:	8016F9EC
 * Size:	000004
 */
void BasePelletMgr::doDirectDraw(Graphics&) { }

} // namespace Game

/*
 * --INFO--
 * Address:	8016F9F0
 * Size:	000070
 */
void Container<CollPart>::~Container()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8016FA44
	lis      r4, "__vt__20Container<8CollPart>"@ha
	addi     r0, r4, "__vt__20Container<8CollPart>"@l
	stw      r0, 0(r30)
	beq      lbl_8016FA34
	lis      r5, __vt__16GenericContainer@ha
	li       r4, 0
	addi     r0, r5, __vt__16GenericContainer@l
	stw      r0, 0(r30)
	bl       __dt__5CNodeFv

lbl_8016FA34:
	extsh.   r0, r31
	ble      lbl_8016FA44
	mr       r3, r30
	bl       __dl__FPv

lbl_8016FA44:
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
 * Address:	8016FA60
 * Size:	000088
 */
void ObjectMgr<CollPart>::~ObjectMgr()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_8016FACC
	lis      r4, "__vt__20ObjectMgr<8CollPart>"@ha
	addi     r4, r4, "__vt__20ObjectMgr<8CollPart>"@l
	stw      r4, 0(r30)
	addi     r0, r4, 0x2c
	stw      r0, 0x1c(r30)
	beq      lbl_8016FABC
	lis      r4, "__vt__20Container<8CollPart>"@ha
	addi     r0, r4, "__vt__20Container<8CollPart>"@l
	stw      r0, 0(r30)
	beq      lbl_8016FABC
	lis      r5, __vt__16GenericContainer@ha
	li       r4, 0
	addi     r0, r5, __vt__16GenericContainer@l
	stw      r0, 0(r30)
	bl       __dt__5CNodeFv

lbl_8016FABC:
	extsh.   r0, r31
	ble      lbl_8016FACC
	mr       r3, r30
	bl       __dl__FPv

lbl_8016FACC:
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
 * Address:	8016FAE8
 * Size:	000084
 */
void WPExcludeSpot::satisfy(Game::WayPoint*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	li       r31, 0
	stw      r30, 8(r1)
	mr       r30, r4

lbl_8016FB04:
	lwz      r3, mgr__Q24Game9ItemOnyon@sda21(r13)
	mr       r4, r31
	bl       getOnyon__Q34Game9ItemOnyon3MgrFi
	cmplwi   r3, 0
	beq      lbl_8016FB2C
	lwz      r0, 0x23c(r3)
	cmplw    r30, r0
	bne      lbl_8016FB2C
	li       r3, 0
	b        lbl_8016FB54

lbl_8016FB2C:
	addi     r31, r31, 1
	cmpwi    r31, 3
	blt      lbl_8016FB04
	lwz      r3, mgr__Q24Game9ItemOnyon@sda21(r13)
	lwz      r3, 0xb0(r3)
	lwz      r0, 0x23c(r3)
	subf     r3, r0, r30
	subf     r0, r30, r0
	or       r0, r3, r0
	srwi     r3, r0, 0x1f

lbl_8016FB54:
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
 * Address:	8016FB6C
 * Size:	0004DC
 */
void satisfy__Q223 @unnamed @pelletMgr_cpp @6NotOffFPQ24Game8WayPoint(void)
{
	/*
	stwu     r1, -0x80(r1)
	mflr     r0
	stw      r0, 0x84(r1)
	stfd     f31, 0x70(r1)
	psq_st   f31, 120(r1), 0, qr0
	stfd     f30, 0x60(r1)
	psq_st   f30, 104(r1), 0, qr0
	stfd     f29, 0x50(r1)
	psq_st   f29, 88(r1), 0, qr0
	stfd     f28, 0x40(r1)
	psq_st   f28, 72(r1), 0, qr0
	lbz      r0, 0x34(r4)
	clrlwi.  r0, r0, 0x1f
	beq      lbl_8016FBAC
	li       r3, 0
	b        lbl_80170018

lbl_8016FBAC:
	lwz      r3, mgr__Q24Game8ItemHole@sda21(r13)
	lfs      f29, 0x4c(r4)
	cmplwi   r3, 0
	lfs      f28, 0x54(r4)
	beq      lbl_8016FDE4
	beq      lbl_8016FBC8
	addi     r3, r3, 0x30

lbl_8016FBC8:
	li       r0, 0
	lis      r4, "__vt__26Iterator<Q24Game8BaseItem>"@ha
	addi     r4, r4, "__vt__26Iterator<Q24Game8BaseItem>"@l
	stw      r0, 0x3c(r1)
	cmplwi   r0, 0
	stw      r4, 0x30(r1)
	stw      r0, 0x34(r1)
	stw      r3, 0x38(r1)
	bne      lbl_8016FC04
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x34(r1)
	b        lbl_8016FC8C

lbl_8016FC04:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x34(r1)
	b        lbl_8016FC70

lbl_8016FC1C:
	lwz      r3, 0x38(r1)
	lwz      r4, 0x34(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x3c(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016FC8C
	lwz      r3, 0x38(r1)
	lwz      r4, 0x34(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x34(r1)

lbl_8016FC70:
	lwz      r12, 0x30(r1)
	addi     r3, r1, 0x30
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016FC1C

lbl_8016FC8C:
	lfs      f31, lbl_80518914@sda21(r2)
	lfs      f30, lbl_805189FC@sda21(r2)
	b        lbl_8016FDC4

lbl_8016FC98:
	lwz      r3, 0x38(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	addi     r3, r1, 0x14
	lwz      r12, 0(r4)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f0, 0x1c(r1)
	lfs      f1, 0x14(r1)
	fsubs    f0, f0, f28
	fsubs    f1, f1, f29
	fmuls    f0, f0, f0
	fmadds   f0, f1, f1, f0
	fcmpo    cr0, f0, f31
	ble      lbl_8016FCF4
	ble      lbl_8016FCF8
	frsqrte  f1, f0
	fmuls    f0, f1, f0
	b        lbl_8016FCF8

lbl_8016FCF4:
	fmr      f0, f31

lbl_8016FCF8:
	fcmpo    cr0, f0, f30
	bge      lbl_8016FD08
	li       r3, 0
	b        lbl_80170018

lbl_8016FD08:
	lwz      r0, 0x3c(r1)
	cmplwi   r0, 0
	bne      lbl_8016FD34
	lwz      r3, 0x38(r1)
	lwz      r4, 0x34(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x34(r1)
	b        lbl_8016FDC4

lbl_8016FD34:
	lwz      r3, 0x38(r1)
	lwz      r4, 0x34(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x34(r1)
	b        lbl_8016FDA8

lbl_8016FD54:
	lwz      r3, 0x38(r1)
	lwz      r4, 0x34(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x3c(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016FDC4
	lwz      r3, 0x38(r1)
	lwz      r4, 0x34(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x34(r1)

lbl_8016FDA8:
	lwz      r12, 0x30(r1)
	addi     r3, r1, 0x30
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016FD54

lbl_8016FDC4:
	lwz      r3, 0x38(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0x34(r1)
	cmplw    r4, r3
	bne      lbl_8016FC98

lbl_8016FDE4:
	lwz      r3, mgr__Q24Game15ItemBigFountain@sda21(r13)
	cmplwi   r3, 0
	beq      lbl_80170014
	beq      lbl_8016FDF8
	addi     r3, r3, 0x30

lbl_8016FDF8:
	li       r0, 0
	lis      r4, "__vt__26Iterator<Q24Game8BaseItem>"@ha
	addi     r4, r4, "__vt__26Iterator<Q24Game8BaseItem>"@l
	stw      r0, 0x2c(r1)
	cmplwi   r0, 0
	stw      r4, 0x20(r1)
	stw      r0, 0x24(r1)
	stw      r3, 0x28(r1)
	bne      lbl_8016FE34
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x24(r1)
	b        lbl_8016FEBC

lbl_8016FE34:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x24(r1)
	b        lbl_8016FEA0

lbl_8016FE4C:
	lwz      r3, 0x28(r1)
	lwz      r4, 0x24(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x2c(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016FEBC
	lwz      r3, 0x28(r1)
	lwz      r4, 0x24(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x24(r1)

lbl_8016FEA0:
	lwz      r12, 0x20(r1)
	addi     r3, r1, 0x20
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016FE4C

lbl_8016FEBC:
	lfs      f30, lbl_80518914@sda21(r2)
	lfs      f31, lbl_805189FC@sda21(r2)
	b        lbl_8016FFF4

lbl_8016FEC8:
	lwz      r3, 0x28(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	addi     r3, r1, 8
	lwz      r12, 0(r4)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f0, 0x10(r1)
	lfs      f1, 8(r1)
	fsubs    f0, f0, f28
	fsubs    f1, f1, f29
	fmuls    f0, f0, f0
	fmadds   f0, f1, f1, f0
	fcmpo    cr0, f0, f30
	ble      lbl_8016FF24
	ble      lbl_8016FF28
	frsqrte  f1, f0
	fmuls    f0, f1, f0
	b        lbl_8016FF28

lbl_8016FF24:
	fmr      f0, f30

lbl_8016FF28:
	fcmpo    cr0, f0, f31
	bge      lbl_8016FF38
	li       r3, 0
	b        lbl_80170018

lbl_8016FF38:
	lwz      r0, 0x2c(r1)
	cmplwi   r0, 0
	bne      lbl_8016FF64
	lwz      r3, 0x28(r1)
	lwz      r4, 0x24(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x24(r1)
	b        lbl_8016FFF4

lbl_8016FF64:
	lwz      r3, 0x28(r1)
	lwz      r4, 0x24(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x24(r1)
	b        lbl_8016FFD8

lbl_8016FF84:
	lwz      r3, 0x28(r1)
	lwz      r4, 0x24(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x2c(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8016FFF4
	lwz      r3, 0x28(r1)
	lwz      r4, 0x24(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0x24(r1)

lbl_8016FFD8:
	lwz      r12, 0x20(r1)
	addi     r3, r1, 0x20
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8016FF84

lbl_8016FFF4:
	lwz      r3, 0x28(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0x24(r1)
	cmplw    r4, r3
	bne      lbl_8016FEC8

lbl_80170014:
	li       r3, 1

lbl_80170018:
	psq_l    f31, 120(r1), 0, qr0
	lfd      f31, 0x70(r1)
	psq_l    f30, 104(r1), 0, qr0
	lfd      f30, 0x60(r1)
	psq_l    f29, 88(r1), 0, qr0
	lfd      f29, 0x50(r1)
	psq_l    f28, 72(r1), 0, qr0
	lwz      r0, 0x84(r1)
	lfd      f28, 0x40(r1)
	mtlr     r0
	addi     r1, r1, 0x80
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170048
 * Size:	000044
 */
void onSetPosition__Q24Game6PelletFR10Vector3f(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lfs      f0, 0(r4)
	stfs     f0, 0x3ac(r3)
	lfs      f0, 4(r4)
	stfs     f0, 0x3b0(r3)
	lfs      f0, 8(r4)
	stfs     f0, 0x3b4(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x1b0(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

namespace Game {

/*
 * --INFO--
 * Address:	8017008C
 * Size:	000008
 */
void Pellet::inWater(void)
{
	/*
	lbz      r3, 0x325(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170094
 * Size:	000008
 */
s32 Pellet::getBedamaColor(void) { return -0x1; }

/*
 * --INFO--
 * Address:	8017009C
 * Size:	000008
 */
void Pellet::getSound_PosPtr(void)
{
	/*
	addi     r3, r3, 0x3ac
	blr
	*/
}

/*
 * --INFO--
 * Address:	801700A4
 * Size:	000008
 */
void Pellet::getFaceDir(void)
{
	/*
	lfs      f1, 0x3b8(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801700AC
 * Size:	000008
 */
u32 Pellet::deferPikiCollision(void) { return 0x1; }

/*
 * --INFO--
 * Address:	801700B4
 * Size:	000004
 */
void Pellet::sound_otakaraEventFinish(void) { }

namespace PSM {

/*
 * --INFO--
 * Address:	801700B8
 * Size:	0000BC
 */
EventBase::~EventBase(void)
{
	/*
stwu     r1, -0x10(r1)
mflr     r0
stw      r0, 0x14(r1)
stw      r31, 0xc(r1)
mr       r31, r4
stw      r30, 8(r1)
or.      r30, r3, r3
beq      lbl_80170158
lis      r3, __vt__Q23PSM9EventBase@ha
addi     r4, r3, __vt__Q23PSM9EventBase@l
stw      r4, 0x28(r30)
addi     r3, r4, 8
addi     r0, r4, 0x40
stw      r3, 0x10(r30)
stw      r0, 0x30(r30)
beq      lbl_80170148
lis      r4, __vt__Q23PSM11CreatureObj@ha
addi     r3, r30, 0x30
addi     r6, r4, __vt__Q23PSM11CreatureObj@l
li       r4, 0
stw      r6, 0x28(r30)
addi     r5, r6, 8
addi     r0, r6, 0x40
stw      r5, 0x10(r30)
stw      r0, 0x30(r30)
bl       __dt__Q27JAInter6ObjectFv
cmplwi   r30, 0
beq      lbl_80170148
lis      r4, __vt__Q23PSM8Creature@ha
mr       r3, r30
addi     r5, r4, __vt__Q23PSM8Creature@l
li       r4, 0
stw      r5, 0x28(r30)
addi     r0, r5, 8
stw      r0, 0x10(r30)
bl       __dt__Q23PSM7ObjBaseFv

lbl_80170148:
extsh.   r0, r31
ble      lbl_80170158
mr       r3, r30
bl       __dl__FPv

lbl_80170158:
lwz      r0, 0x14(r1)
mr       r3, r30
lwz      r31, 0xc(r1)
lwz      r30, 8(r1)
mtlr     r0
addi     r1, r1, 0x10
blr
	*/
}

} // namespace PSM

/*
 * --INFO--
 * Address:	80170174
 * Size:	000008
 */
u32 CreatureObj::getCastType(void) { return 0x0; }

/*
 * --INFO--
 * Address:	8017017C
 * Size:	000010
 */
void CreatureObj::getJAIObject(void)
{
	/*
	cmplwi   r3, 0
	beqlr
	addi     r3, r3, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	8017018C
 * Size:	000010
 */
void CreatureObj::getHandleArea(unsigned char)
{
	/*
	lwz      r3, 0x4c(r3)
	rlwinm   r0, r4, 2, 0x16, 0x1d
	add      r3, r3, r0
	blr
	*/
}

/*
 * --INFO--
 * Address:	8017019C
 * Size:	000004
 */
void CreatureObj::onCalcOn(void) { }

namespace Game {

} // namespace Game

/*
 * --INFO--
 * Address:	801701A0
 * Size:	00000C
 */
void PelletGoalStateArg::getName(void)
{
	/*
	lis      r3, lbl_8047E534@ha
	addi     r3, r3, lbl_8047E534@l
	blr
	*/
}

} // namespace Game

/*
 * --INFO--
 * Address:	801701AC
 * Size:	000004
 */
void init__Q24Game28StateMachine<Game::Pellet> FPQ24Game6Pellet(void) { }

/*
 * --INFO--
 * Address:	801701B0
 * Size:	000008
 */
void NodeObjectMgr<GenericObjectMgr>::get(void*)
{
	/*
	lwz      r3, 0x18(r4)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801701B8
 * Size:	000008
 */
void NodeObjectMgr<GenericObjectMgr>::getNext(void*)
{
	/*
	lwz      r3, 4(r4)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801701C0
 * Size:	000008
 */
void NodeObjectMgr<GenericObjectMgr>::getStart()
{
	/*
	lwz      r3, 0x30(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801701C8
 * Size:	000008
 */
u32 NodeObjectMgr<GenericObjectMgr>::getEnd() { return 0x0; }

/*
 * --INFO--
 * Address:	801701D0
 * Size:	000018
 */
void NodeObjectMgr<GenericObjectMgr>::resetMgr()
{
	/*
	li       r0, 0
	stw      r0, 0x30(r3)
	stw      r0, 0x2c(r3)
	stw      r0, 0x28(r3)
	stw      r0, 0x24(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801701E8
 * Size:	000018
 */
void MonoObjectMgr<Game::PelletFruit::Object>::resetMgr()
{
	/*
	li       r0, 0
	stw      r0, 0x28(r3)
	stw      r0, 0x24(r3)
	stw      r0, 0x20(r3)
	stw      r0, 0x2c(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170200
 * Size:	000018
 */
void MonoObjectMgr<Game::PelletCarcass::Object>::resetMgr()
{
	/*
	li       r0, 0
	stw      r0, 0x28(r3)
	stw      r0, 0x24(r3)
	stw      r0, 0x20(r3)
	stw      r0, 0x2c(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170218
 * Size:	000018
 */
void MonoObjectMgr<Game::PelletNumber::Object>::resetMgr()
{
	/*
	li       r0, 0
	stw      r0, 0x28(r3)
	stw      r0, 0x24(r3)
	stw      r0, 0x20(r3)
	stw      r0, 0x2c(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170230
 * Size:	000040
 */
void MonoObjectMgr<CollPart>::getNext(void*)
{
	/*
	lwz      r5, 0x24(r3)
	addi     r6, r4, 1
	subf     r0, r6, r5
	mtctr    r0
	cmpw     r6, r5
	bge      lbl_80170268

lbl_80170248:
	lwz      r4, 0x2c(r3)
	lbzx     r0, r4, r6
	cmplwi   r0, 0
	bne      lbl_80170260
	mr       r3, r6
	blr

lbl_80170260:
	addi     r6, r6, 1
	bdnz     lbl_80170248

lbl_80170268:
	mr       r3, r5
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170270
 * Size:	000030
 */
void MonoObjectMgr<CollPart>::getStart()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	li       r4, -1
	stw      r0, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	801702A0
 * Size:	000008
 */
void MonoObjectMgr<CollPart>::getEnd()
{
	/*
	lwz      r3, 0x24(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801702A8
 * Size:	000010
 */
void MonoObjectMgr<CollPart>::getAt(int)
{
	/*
	mulli    r0, r4, 0x64
	lwz      r3, 0x28(r3)
	add      r3, r3, r0
	blr
	*/
}

/*
 * --INFO--
 * Address:	801702B8
 * Size:	000008
 */
void MonoObjectMgr<CollPart>::getTo()
{
	/*
	lwz      r3, 0x24(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801702C0
 * Size:	000080
 */
void MonoObjectMgr<CollPart>::doAnimation()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	li       r31, 0
	stw      r30, 0x18(r1)
	li       r30, 0
	stw      r29, 0x14(r1)
	mr       r29, r3
	b        lbl_80170318

lbl_801702E8:
	lwz      r3, 0x2c(r29)
	lbzx     r0, r3, r30
	cmplwi   r0, 0
	bne      lbl_80170310
	lwz      r0, 0x28(r29)
	add      r3, r0, r31
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_80170310:
	addi     r31, r31, 0x64
	addi     r30, r30, 1

lbl_80170318:
	lwz      r0, 0x24(r29)
	cmpw     r30, r0
	blt      lbl_801702E8
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
 * Address:	80170340
 * Size:	000080
 */
void MonoObjectMgr<CollPart>::doEntry()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	li       r31, 0
	stw      r30, 0x18(r1)
	li       r30, 0
	stw      r29, 0x14(r1)
	mr       r29, r3
	b        lbl_80170398

lbl_80170368:
	lwz      r3, 0x2c(r29)
	lbzx     r0, r3, r30
	cmplwi   r0, 0
	bne      lbl_80170390
	lwz      r0, 0x28(r29)
	add      r3, r0, r31
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl

lbl_80170390:
	addi     r31, r31, 0x64
	addi     r30, r30, 1

lbl_80170398:
	lwz      r0, 0x24(r29)
	cmpw     r30, r0
	blt      lbl_80170368
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
 * Address:	801703C0
 * Size:	000090
 */
void MonoObjectMgr<CollPart>::doSetView(int)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	li       r31, 0
	stw      r30, 0x18(r1)
	mr       r30, r4
	stw      r29, 0x14(r1)
	li       r29, 0
	stw      r28, 0x10(r1)
	mr       r28, r3
	b        lbl_80170424

lbl_801703F0:
	lwz      r3, 0x2c(r28)
	lbzx     r0, r3, r29
	cmplwi   r0, 0
	bne      lbl_8017041C
	lwz      r0, 0x28(r28)
	mr       r4, r30
	add      r3, r0, r31
	lwz      r12, 0(r3)
	lwz      r12, 0x24(r12)
	mtctr    r12
	bctrl

lbl_8017041C:
	addi     r31, r31, 0x64
	addi     r29, r29, 1

lbl_80170424:
	lwz      r0, 0x24(r28)
	cmpw     r29, r0
	blt      lbl_801703F0
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
 * Address:	80170450
 * Size:	000080
 */
void MonoObjectMgr<CollPart>::doViewCalc()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	li       r31, 0
	stw      r30, 0x18(r1)
	li       r30, 0
	stw      r29, 0x14(r1)
	mr       r29, r3
	b        lbl_801704A8

lbl_80170478:
	lwz      r3, 0x2c(r29)
	lbzx     r0, r3, r30
	cmplwi   r0, 0
	bne      lbl_801704A0
	lwz      r0, 0x28(r29)
	add      r3, r0, r31
	lwz      r12, 0(r3)
	lwz      r12, 0x28(r12)
	mtctr    r12
	bctrl

lbl_801704A0:
	addi     r31, r31, 0x64
	addi     r30, r30, 1

lbl_801704A8:
	lwz      r0, 0x24(r29)
	cmpw     r30, r0
	blt      lbl_80170478
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
 * Address:	801704D0
 * Size:	000090
 */
void MonoObjectMgr<CollPart>::doSimulation(float)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stfd     f31, 0x18(r1)
	fmr      f31, f1
	stw      r31, 0x14(r1)
	li       r31, 0
	stw      r30, 0x10(r1)
	li       r30, 0
	stw      r29, 0xc(r1)
	mr       r29, r3
	b        lbl_80170534

lbl_80170500:
	lwz      r3, 0x2c(r29)
	lbzx     r0, r3, r30
	cmplwi   r0, 0
	bne      lbl_8017052C
	lwz      r0, 0x28(r29)
	fmr      f1, f31
	add      r3, r0, r31
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl

lbl_8017052C:
	addi     r31, r31, 0x64
	addi     r30, r30, 1

lbl_80170534:
	lwz      r0, 0x24(r29)
	cmpw     r30, r0
	blt      lbl_80170500
	lwz      r0, 0x24(r1)
	lfd      f31, 0x18(r1)
	lwz      r31, 0x14(r1)
	lwz      r30, 0x10(r1)
	lwz      r29, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170560
 * Size:	000090
 */
void MonoObjectMgr<CollPart>::doDirectDraw(Graphics&)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	li       r31, 0
	stw      r30, 0x18(r1)
	li       r30, 0
	stw      r29, 0x14(r1)
	mr       r29, r4
	stw      r28, 0x10(r1)
	mr       r28, r3
	b        lbl_801705C4

lbl_80170590:
	lwz      r3, 0x2c(r28)
	lbzx     r0, r3, r30
	cmplwi   r0, 0
	bne      lbl_801705BC
	lwz      r0, 0x28(r28)
	mr       r4, r29
	add      r3, r0, r31
	lwz      r12, 0(r3)
	lwz      r12, 0x30(r12)
	mtctr    r12
	bctrl

lbl_801705BC:
	addi     r31, r31, 0x64
	addi     r30, r30, 1

lbl_801705C4:
	lwz      r0, 0x24(r28)
	cmpw     r30, r0
	blt      lbl_80170590
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
 * Address:	801705F0
 * Size:	000018
 */
void MonoObjectMgr<CollPart>::resetMgr()
{
	/*
	li       r0, 0
	stw      r0, 0x28(r3)
	stw      r0, 0x24(r3)
	stw      r0, 0x20(r3)
	stw      r0, 0x2c(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170608
 * Size:	000030
 */
void MonoObjectMgr<CollPart>::clearMgr()
{
	/*
	li       r0, 0
	li       r6, 0
	stw      r0, 0x20(r3)
	li       r5, 1
	b        lbl_80170628

lbl_8017061C:
	lwz      r4, 0x2c(r3)
	stbx     r5, r4, r6
	addi     r6, r6, 1

lbl_80170628:
	lwz      r0, 0x24(r3)
	cmpw     r6, r0
	blt      lbl_8017061C
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170638
 * Size:	000004
 */
void MonoObjectMgr<CollPart>::onAlloc() { }

/*
 * --INFO--
 * Address:	8017063C
 * Size:	000010
 */
void MonoObjectMgr<CollPart>::get(void*)
{
	/*
	mulli    r0, r4, 0x64
	lwz      r3, 0x28(r3)
	add      r3, r3, r0
	blr
	*/
}

/*
 * --INFO--
 * Address:	8017064C
 * Size:	0001E4
 */
void ObjectMgr<GenericObjectMgr>::doAnimation()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__28Iterator<16GenericObjectMgr>"@l
	cmplwi   r0, 0
	stw      r0, 0x14(r1)
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_80170694
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170800

lbl_80170694:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170700

lbl_801706AC:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80170800
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80170700:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_801706AC
	b        lbl_80170800

lbl_80170720:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_80170770
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170800

lbl_80170770:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_801707E4

lbl_80170790:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80170800
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_801707E4:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80170790

lbl_80170800:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80170720
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170830
 * Size:	0001E4
 */
void ObjectMgr<GenericObjectMgr>::doEntry()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__28Iterator<16GenericObjectMgr>"@l
	cmplwi   r0, 0
	stw      r0, 0x14(r1)
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_80170878
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_801709E4

lbl_80170878:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_801708E4

lbl_80170890:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_801709E4
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_801708E4:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80170890
	b        lbl_801709E4

lbl_80170904:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_80170954
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_801709E4

lbl_80170954:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_801709C8

lbl_80170974:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_801709E4
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_801709C8:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80170974

lbl_801709E4:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80170904
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170A14
 * Size:	0001F4
 */
void ObjectMgr<GenericObjectMgr>::doSetView(int)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r5, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r5, r5, "__vt__28Iterator<16GenericObjectMgr>"@l
	stw      r31, 0x1c(r1)
	cmplwi   r0, 0
	mr       r31, r4
	stw      r0, 0x14(r1)
	stw      r5, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_80170A64
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170BD4

lbl_80170A64:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170AD0

lbl_80170A7C:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80170BD4
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80170AD0:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80170A7C
	b        lbl_80170BD4

lbl_80170AF0:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	mr       r4, r31
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_80170B44
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170BD4

lbl_80170B44:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170BB8

lbl_80170B64:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80170BD4
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80170BB8:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80170B64

lbl_80170BD4:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80170AF0
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170C08
 * Size:	0001E4
 */
void ObjectMgr<GenericObjectMgr>::doViewCalc()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__28Iterator<16GenericObjectMgr>"@l
	cmplwi   r0, 0
	stw      r0, 0x14(r1)
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_80170C50
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170DBC

lbl_80170C50:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170CBC

lbl_80170C68:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80170DBC
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80170CBC:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80170C68
	b        lbl_80170DBC

lbl_80170CDC:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_80170D2C
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170DBC

lbl_80170D2C:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170DA0

lbl_80170D4C:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80170DBC
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80170DA0:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80170D4C

lbl_80170DBC:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80170CDC
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170DEC
 * Size:	0001F4
 */
void ObjectMgr<GenericObjectMgr>::doSimulation(float)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__28Iterator<16GenericObjectMgr>"@l
	stfd     f31, 0x18(r1)
	fmr      f31, f1
	cmplwi   r0, 0
	stw      r4, 8(r1)
	stw      r0, 0x14(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_80170E3C
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170FAC

lbl_80170E3C:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170EA8

lbl_80170E54:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80170FAC
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80170EA8:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80170E54
	b        lbl_80170FAC

lbl_80170EC8:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	fmr      f1, f31
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_80170F1C
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170FAC

lbl_80170F1C:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80170F90

lbl_80170F3C:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80170FAC
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80170F90:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80170F3C

lbl_80170FAC:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80170EC8
	lwz      r0, 0x24(r1)
	lfd      f31, 0x18(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80170FE0
 * Size:	0001F4
 */
void ObjectMgr<GenericObjectMgr>::doDirectDraw(Graphics&)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r5, "__vt__28Iterator<16GenericObjectMgr>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r5, r5, "__vt__28Iterator<16GenericObjectMgr>"@l
	stw      r31, 0x1c(r1)
	cmplwi   r0, 0
	mr       r31, r4
	stw      r0, 0x14(r1)
	stw      r5, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_80171030
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_801711A0

lbl_80171030:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8017109C

lbl_80171048:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_801711A0
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_8017109C:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80171048
	b        lbl_801711A0

lbl_801710BC:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	mr       r4, r31
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_80171110
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_801711A0

lbl_80171110:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171184

lbl_80171130:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_801711A0
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171184:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80171130

lbl_801711A0:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_801710BC
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	801711D4
 * Size:	00002C
 */
void Container<GenericObjectMgr>::getObject(void*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80171200
 * Size:	000008
 */
u32 Container<GenericObjectMgr>::getAt(int) { return 0x0; }

/*
 * --INFO--
 * Address:	80171208
 * Size:	000008
 */
u32 Container<GenericObjectMgr>::getTo() { return 0x0; }

/*
 * --INFO--
 * Address:	80171210
 * Size:	00002C
 */
void Container<CollPart>::getObject(void*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8017123C
 * Size:	000008
 */
u32 Container<CollPart>::getAt(int) { return 0x0; }

/*
 * --INFO--
 * Address:	80171244
 * Size:	000008
 */
u32 Container<CollPart>::getTo() { return 0x0; }

/*
 * --INFO--
 * Address:	8017124C
 * Size:	000030
 */
void Delegate1<Game::BasePelletMgr, SysShape::Model*>::invoke(SysShape::Model*)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	mr       r5, r3
	stw      r0, 0x14(r1)
	addi     r12, r5, 8
	lwz      r3, 4(r3)
	bl       __ptmf_scall
	nop
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	8017127C
 * Size:	0001F4
 */
void ObjectMgr<CollPart>::doDirectDraw(Graphics&)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r5, "__vt__19Iterator<8CollPart>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r5, r5, "__vt__19Iterator<8CollPart>"@l
	stw      r31, 0x1c(r1)
	cmplwi   r0, 0
	mr       r31, r4
	stw      r0, 0x14(r1)
	stw      r5, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_801712CC
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8017143C

lbl_801712CC:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171338

lbl_801712E4:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8017143C
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171338:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_801712E4
	b        lbl_8017143C

lbl_80171358:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	mr       r4, r31
	lwz      r12, 0x30(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_801713AC
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8017143C

lbl_801713AC:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171420

lbl_801713CC:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8017143C
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171420:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_801713CC

lbl_8017143C:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80171358
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80171470
 * Size:	00004C
 */
void Iterator<CollPart>::isDone()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r3, 8(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r0, 4(r31)
	subf     r0, r0, r3
	cntlzw   r0, r0
	srwi     r3, r0, 5
	lwz      r31, 0xc(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	801714BC
 * Size:	0001F4
 */
void ObjectMgr<CollPart>::doSimulation(float)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__19Iterator<8CollPart>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__19Iterator<8CollPart>"@l
	stfd     f31, 0x18(r1)
	fmr      f31, f1
	cmplwi   r0, 0
	stw      r4, 8(r1)
	stw      r0, 0x14(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_8017150C
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8017167C

lbl_8017150C:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171578

lbl_80171524:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8017167C
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171578:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80171524
	b        lbl_8017167C

lbl_80171598:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	fmr      f1, f31
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_801715EC
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_8017167C

lbl_801715EC:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171660

lbl_8017160C:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_8017167C
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171660:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_8017160C

lbl_8017167C:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80171598
	lwz      r0, 0x24(r1)
	lfd      f31, 0x18(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	801716B0
 * Size:	0001E4
 */
void ObjectMgr<CollPart>::doViewCalc()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__19Iterator<8CollPart>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__19Iterator<8CollPart>"@l
	cmplwi   r0, 0
	stw      r0, 0x14(r1)
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_801716F8
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171864

lbl_801716F8:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171764

lbl_80171710:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80171864
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171764:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80171710
	b        lbl_80171864

lbl_80171784:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	lwz      r12, 0x28(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_801717D4
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171864

lbl_801717D4:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171848

lbl_801717F4:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80171864
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171848:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_801717F4

lbl_80171864:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80171784
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80171894
 * Size:	0001F4
 */
void ObjectMgr<CollPart>::doSetView(int)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r5, "__vt__19Iterator<8CollPart>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r5, r5, "__vt__19Iterator<8CollPart>"@l
	stw      r31, 0x1c(r1)
	cmplwi   r0, 0
	mr       r31, r4
	stw      r0, 0x14(r1)
	stw      r5, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_801718E4
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171A54

lbl_801718E4:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171950

lbl_801718FC:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80171A54
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171950:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_801718FC
	b        lbl_80171A54

lbl_80171970:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	mr       r4, r31
	lwz      r12, 0x24(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_801719C4
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171A54

lbl_801719C4:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171A38

lbl_801719E4:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80171A54
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171A38:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_801719E4

lbl_80171A54:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80171970
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80171A88
 * Size:	0001E4
 */
void ObjectMgr<CollPart>::doEntry()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__19Iterator<8CollPart>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__19Iterator<8CollPart>"@l
	cmplwi   r0, 0
	stw      r0, 0x14(r1)
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_80171AD0
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171C3C

lbl_80171AD0:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171B3C

lbl_80171AE8:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80171C3C
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171B3C:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80171AE8
	b        lbl_80171C3C

lbl_80171B5C:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_80171BAC
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171C3C

lbl_80171BAC:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171C20

lbl_80171BCC:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80171C3C
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171C20:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80171BCC

lbl_80171C3C:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80171B5C
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80171C6C
 * Size:	0001E4
 */
void ObjectMgr<CollPart>::doAnimation()
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, "__vt__19Iterator<8CollPart>"@ha
	stw      r0, 0x24(r1)
	li       r0, 0
	addi     r4, r4, "__vt__19Iterator<8CollPart>"@l
	cmplwi   r0, 0
	stw      r0, 0x14(r1)
	stw      r4, 8(r1)
	stw      r0, 0xc(r1)
	stw      r3, 0x10(r1)
	bne      lbl_80171CB4
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171E20

lbl_80171CB4:
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171D20

lbl_80171CCC:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80171E20
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171D20:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80171CCC
	b        lbl_80171E20

lbl_80171D40:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	cmplwi   r0, 0
	bne      lbl_80171D90
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171E20

lbl_80171D90:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)
	b        lbl_80171E04

lbl_80171DB0:
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_80171E20
	lwz      r3, 0x10(r1)
	lwz      r4, 0xc(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 0xc(r1)

lbl_80171E04:
	lwz      r12, 8(r1)
	addi     r3, r1, 8
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80171DB0

lbl_80171E20:
	lwz      r3, 0x10(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lwz      r4, 0xc(r1)
	cmplw    r4, r3
	bne      lbl_80171D40
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80171E50
 * Size:	00009C
 */
void MonoObjectMgr<CollPart>::MonoObjectMgr()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	bl       __ct__5CNodeFv
	lis      r4, __vt__16GenericContainer@ha
	lis      r3, "__vt__20Container<8CollPart>"@ha
	addi     r0, r4, __vt__16GenericContainer@l
	lis      r6, __vt__16GenericObjectMgr@ha
	stw      r0, 0(r31)
	addi     r0, r3, "__vt__20Container<8CollPart>"@l
	lis      r4, "__vt__20ObjectMgr<8CollPart>"@ha
	lis      r3, "__vt__24MonoObjectMgr<8CollPart>"@ha
	stw      r0, 0(r31)
	li       r8, 0
	addi     r7, r4, "__vt__20ObjectMgr<8CollPart>"@l
	addi     r5, r3, "__vt__24MonoObjectMgr<8CollPart>"@l
	stb      r8, 0x18(r31)
	addi     r0, r6, __vt__16GenericObjectMgr@l
	addi     r6, r7, 0x2c
	addi     r4, r5, 0x2c
	stw      r0, 0x1c(r31)
	li       r0, 1
	mr       r3, r31
	stw      r7, 0(r31)
	stw      r6, 0x1c(r31)
	stw      r5, 0(r31)
	stw      r4, 0x1c(r31)
	stb      r0, 0x18(r31)
	stw      r8, 0x24(r31)
	stw      r8, 0x20(r31)
	stw      r8, 0x28(r31)
	stw      r8, 0x2c(r31)
	lwz      r31, 0xc(r1)
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80171EEC
 * Size:	00009C
 */
void transit__Q24Game28StateMachine<Game::Pellet> FPQ24Game6PelletiPQ24Game8StateArg(void)
{
	/*
	.loc_0x0:
	  stwu      r1, -0x20(r1)
	  mflr      r0
	  stw       r0, 0x24(r1)
	  rlwinm    r0,r5,2,0,29
	  stmw      r27, 0xC(r1)
	  mr        r27, r3
	  mr        r28, r4
	  mr        r29, r6
	  lwz       r30, 0x3CC(r4)
	  lwz       r3, 0x14(r3)
	  cmplwi    r30, 0
	  lwzx      r31, r3, r0
	  beq-      .loc_0x50
	  mr        r3, r30
	  lwz       r12, 0x0(r30)
	  lwz       r12, 0x10(r12)
	  mtctr     r12
	  bctrl
	  lwz       r0, 0x4(r30)
	  stw       r0, 0x18(r27)

	.loc_0x50:
	  lwz       r0, 0xC(r27)
	  cmpw      r31, r0
	  blt-      .loc_0x60

	.loc_0x5C:
	  b         .loc_0x5C

	.loc_0x60:
	  lwz       r3, 0x4(r27)
	  rlwinm    r0,r31,2,0,29
	  mr        r4, r28
	  mr        r5, r29
	  lwzx      r3, r3, r0
	  stw       r3, 0x3CC(r28)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x8(r12)
	  mtctr     r12
	  bctrl
	  lmw       r27, 0xC(r1)
	  lwz       r0, 0x24(r1)
	  mtlr      r0
	  addi      r1, r1, 0x20
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80171F88
 * Size:	000004
 */
void init__Q24Game24FSMState<Game::Pellet> FPQ24Game6PelletPQ24Game8StateArg(void) { }

/*
 * --INFO--
 * Address:	80171F8C
 * Size:	000004
 */
void cleanup__Q24Game24FSMState<Game::Pellet> FPQ24Game6Pellet(void) { }

/*
 * --INFO--
 * Address:	80171F90
 * Size:	00001C
 */
void getCurrID__Q24Game28StateMachine<Game::Pellet> FPQ24Game6Pellet(void)
{
	/*
	lwz      r3, 0x3cc(r4)
	cmplwi   r3, 0
	beq      lbl_80171FA4
	lwz      r3, 4(r3)
	blr

lbl_80171FA4:
	li       r3, -1
	blr
	*/
}

/*
 * --INFO--
 * Address:	80171FAC
 * Size:	000038
 */
void exec__Q24Game28StateMachine<Game::Pellet> FPQ24Game6Pellet(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	lwz      r3, 0x3cc(r4)
	cmplwi   r3, 0
	beq      lbl_80171FD4
	lwz      r12, 0(r3)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl

lbl_80171FD4:
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80171FE4
 * Size:	000004
 */
void exec__Q24Game24FSMState<Game::Pellet> FPQ24Game6Pellet(void) { }

/*
 * --INFO--
 * Address:	80171FE8
 * Size:	00009C
 */
void resetMgrAndResources__Q24Game49FixedSizePelletMgr<Game::PelletOtakara::Object> Fv(void)
{
	/*
	.loc_0x0:
	  stwu      r1, -0x10(r1)
	  mflr      r0
	  stw       r0, 0x14(r1)
	  stw       r31, 0xC(r1)
	  mr        r31, r3
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x28(r12)
	  mtctr     r12
	  bctrl
	  li        r8, 0
	  li        r9, 0
	  mr        r7, r8
	  mr        r6, r8
	  mr        r5, r8
	  mr        r4, r8
	  b         .loc_0x68

	.loc_0x40:
	  lwz       r3, 0xC(r31)
	  stwx      r7, r3, r8
	  lwz       r3, 0x10(r31)
	  stwx      r6, r3, r8
	  lwz       r3, 0x14(r31)
	  stwx      r5, r3, r8
	  addi      r8, r8, 0x4
	  lwz       r3, 0x4C(r31)
	  stbx      r4, r3, r9
	  addi      r9, r9, 0x1

	.loc_0x68:
	  lwz       r0, 0x50(r31)
	  cmpw      r9, r0
	  blt+      .loc_0x40
	  lwz       r0, 0x48(r31)
	  cmplwi    r0, 0
	  beq-      .loc_0x88
	  li        r0, 0
	  stw       r0, 0x48(r31)

	.loc_0x88:
	  lwz       r0, 0x14(r1)
	  lwz       r31, 0xC(r1)
	  mtlr      r0
	  addi      r1, r1, 0x10
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80172084
 * Size:	000050
 */
void resetMgr__Q24Game49FixedSizePelletMgr<Game::PelletOtakara::Object> Fv(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	addi     r3, r31, 0x70
	lwz      r12, 0x70(r31)
	lwz      r12, 0x80(r12)
	mtctr    r12
	bctrl
	addi     r3, r31, 0x18
	lwz      r12, 0x18(r31)
	lwz      r12, 0x80(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	801720D4
 * Size:	00009C
 */
void resetMgrAndResources__Q24Game46FixedSizePelletMgr<Game::PelletItem::Object> Fv(void)
{
	/*
	.loc_0x0:
	  stwu      r1, -0x10(r1)
	  mflr      r0
	  stw       r0, 0x14(r1)
	  stw       r31, 0xC(r1)
	  mr        r31, r3
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x28(r12)
	  mtctr     r12
	  bctrl
	  li        r8, 0
	  li        r9, 0
	  mr        r7, r8
	  mr        r6, r8
	  mr        r5, r8
	  mr        r4, r8
	  b         .loc_0x68

	.loc_0x40:
	  lwz       r3, 0xC(r31)
	  stwx      r7, r3, r8
	  lwz       r3, 0x10(r31)
	  stwx      r6, r3, r8
	  lwz       r3, 0x14(r31)
	  stwx      r5, r3, r8
	  addi      r8, r8, 0x4
	  lwz       r3, 0x4C(r31)
	  stbx      r4, r3, r9
	  addi      r9, r9, 0x1

	.loc_0x68:
	  lwz       r0, 0x50(r31)
	  cmpw      r9, r0
	  blt+      .loc_0x40
	  lwz       r0, 0x48(r31)
	  cmplwi    r0, 0
	  beq-      .loc_0x88
	  li        r0, 0
	  stw       r0, 0x48(r31)

	.loc_0x88:
	  lwz       r0, 0x14(r1)
	  lwz       r31, 0xC(r1)
	  mtlr      r0
	  addi      r1, r1, 0x10
	  blr
	*/
}

/*
 * --INFO--
 * Address:	80172170
 * Size:	000050
 */
void resetMgr__Q24Game46FixedSizePelletMgr<Game::PelletItem::Object> Fv(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	addi     r3, r31, 0x70
	lwz      r12, 0x70(r31)
	lwz      r12, 0x80(r12)
	mtctr    r12
	bctrl
	addi     r3, r31, 0x18
	lwz      r12, 0x18(r31)
	lwz      r12, 0x80(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	801721C0
 * Size:	000038
 */
void Iterator<CollPart>::operator*()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	mr       r4, r3
	stw      r0, 0x14(r1)
	lwz      r3, 8(r3)
	lwz      r4, 4(r4)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	801721F8
 * Size:	0000E4
 */
void Iterator<CollPart>::next()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 0xc(r3)
	cmplwi   r0, 0
	bne      lbl_80172238
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_801722C8

lbl_80172238:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_801722AC

lbl_80172258:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0xc(r31)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_801722C8
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)

lbl_801722AC:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80172258

lbl_801722C8:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	801722DC
 * Size:	0000DC
 */
void Iterator<CollPart>::first()
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 0xc(r3)
	cmplwi   r0, 0
	bne      lbl_80172318
	lwz      r3, 8(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_801723A4

lbl_80172318:
	lwz      r3, 8(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)
	b        lbl_80172388

lbl_80172334:
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x20(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 0xc(r31)
	lwz      r12, 0(r3)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	bne      lbl_801723A4
	lwz      r3, 8(r31)
	lwz      r4, 4(r31)
	lwz      r12, 0(r3)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	stw      r3, 4(r31)

lbl_80172388:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	beq      lbl_80172334

lbl_801723A4:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	801723B8
 * Size:	000018
 */
void MonoObjectMgr<Game::PelletItem::Object>::resetMgr()
{
	/*
	li       r0, 0
	stw      r0, 0x28(r3)
	stw      r0, 0x24(r3)
	stw      r0, 0x20(r3)
	stw      r0, 0x2c(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801723D0
 * Size:	000018
 */
void MonoObjectMgr<Game::PelletOtakara::Object>::resetMgr()
{
	/*
	li       r0, 0
	stw      r0, 0x28(r3)
	stw      r0, 0x24(r3)
	stw      r0, 0x20(r3)
	stw      r0, 0x2c(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801723E8
 * Size:	000028
 */
void __sinit_pelletMgr_cpp(void)
{
	/*
	lis      r4, __float_nan@ha
	li       r0, -1
	lfs      f0, __float_nan@l(r4)
	lis      r3, lbl_804B1A60@ha
	stw      r0, lbl_80515998@sda21(r13)
	stfsu    f0, lbl_804B1A60@l(r3)
	stfs     f0, lbl_8051599C@sda21(r13)
	stfs     f0, 4(r3)
	stfs     f0, 8(r3)
	blr
	*/
}
