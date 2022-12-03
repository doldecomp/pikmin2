#include "og/Screen/DispMember.h"
#include "og/Screen/ScaleMgr.h"
#include "og/Screen/anime.h"
#include "og/Screen/callbackNodes.h"
#include "og/newScreen/WorldMapInfoWindow.h"
#include "types.h"
#include "Morimura/Bases.h"
#include "Morimura/Window.h"

/*
    Generated from dpostproc

    .section .data, "wa"  # 0x8049E220 - 0x804EFC20
    .global __vt__Q28Morimura24TSelectExplanationWindow
    __vt__Q28Morimura24TSelectExplanationWindow:
        .4byte 0
        .4byte 0
        .4byte create__Q28Morimura11TScreenBaseFPCcUl
        .4byte update__Q28Morimura24TSelectExplanationWindowFv
        .4byte
   draw__Q28Morimura24TSelectExplanationWindowFR8GraphicsP13J2DPerspGraph .4byte
   0 .global __vt__Q28Morimura17TConfirmEndWindow
    __vt__Q28Morimura17TConfirmEndWindow:
        .4byte 0
        .4byte 0
        .4byte __dt__Q28Morimura17TConfirmEndWindowFv
        .4byte getChildCount__5CNodeFv
        .4byte 0
        .4byte 0
        .4byte "@24@__dt__Q28Morimura17TConfirmEndWindowFv"
        .4byte update__Q26Screen7ObjBaseFv
        .4byte draw__Q26Screen7ObjBaseFR8Graphics
        .4byte start__Q26Screen7ObjBaseFPCQ26Screen13StartSceneArg
        .4byte end__Q26Screen7ObjBaseFPCQ26Screen11EndSceneArg
        .4byte setOwner__Q26Screen7ObjBaseFPQ26Screen9SceneBase
        .4byte getOwner__Q26Screen7ObjBaseCFv
        .4byte create__Q26Screen7ObjBaseFP10JKRArchive
        .4byte confirmSetScene__Q26Screen7ObjBaseFRQ26Screen11SetSceneArg
        .4byte confirmStartScene__Q26Screen7ObjBaseFPQ26Screen13StartSceneArg
        .4byte confirmEndScene__Q26Screen7ObjBaseFPQ26Screen11EndSceneArg
        .4byte
   doStart__Q28Morimura17TConfirmEndWindowFPCQ26Screen13StartSceneArg .4byte
   doEnd__Q32og9newScreen15ObjSMenuPauseVSFPCQ26Screen11EndSceneArg .4byte
   doCreate__Q32og9newScreen22ObjWorldMapInfoWindow0FP10JKRArchive .4byte
   doUpdateFadein__Q28Morimura17TConfirmEndWindowFv .4byte
   doUpdateFadeinFinish__Q28Morimura17TConfirmEndWindowFv .4byte
   doUpdate__Q32og9newScreen15ObjSMenuPauseVSFv .4byte
   doUpdateFinish__Q32og9newScreen15ObjSMenuPauseVSFv .4byte
   doUpdateFadeout__Q28Morimura17TConfirmEndWindowFv .4byte
   doUpdateFadeoutFinish__Q28Morimura17TConfirmEndWindowFv .4byte
   doDraw__Q28Morimura17TConfirmEndWindowFR8Graphics .4byte
   doConfirmSetScene__Q26Screen7ObjBaseFRQ26Screen11SetSceneArg .4byte
   doConfirmStartScene__Q26Screen7ObjBaseFPQ26Screen13StartSceneArg .4byte
   doConfirmEndScene__Q26Screen7ObjBaseFRPQ26Screen11EndSceneArg .4byte
   in_L__Q32og9newScreen15ObjSMenuPauseVSFv .4byte
   in_R__Q32og9newScreen15ObjSMenuPauseVSFv .4byte
   wait__Q32og9newScreen15ObjSMenuPauseVSFv .4byte
   out_L__Q32og9newScreen22ObjWorldMapInfoWindow0Fv .4byte
   out_R__Q32og9newScreen15ObjSMenuPauseVSFv .4byte
   loop__Q32og9newScreen12ObjSMenuBaseFv .4byte
   doUpdateCancelAction__Q32og9newScreen15ObjSMenuPauseVSFv .4byte
   doUpdateRAction__Q32og9newScreen15ObjSMenuPauseVSFv .4byte
   doUpdateLAction__Q32og9newScreen15ObjSMenuPauseVSFv .4byte
   updateFadeIn__Q32og9newScreen12ObjSMenuBaseFv .4byte
   updateFadeOut__Q32og9newScreen12ObjSMenuBaseFv .4byte
   commonUpdate__Q32og9newScreen22ObjWorldMapInfoWindow0Fv .4byte
   out_cancel__Q32og9newScreen22ObjWorldMapInfoWindow0Fv .4byte
   out_menu_0__Q32og9newScreen22ObjWorldMapInfoWindow0Fv .4byte
   out_menu_1__Q32og9newScreen22ObjWorldMapInfoWindow0Fv .4byte
   getResult__Q32og9newScreen22ObjWorldMapInfoWindow0Fv

    .section .sdata2, "a"     # 0x80516360 - 0x80520E40
    .global lbl_8051F358
    lbl_8051F358:
        .4byte 0x00000000
    .global lbl_8051F35C
    lbl_8051F35C:
        .float 0.05
    .global lbl_8051F360
    lbl_8051F360:
        .float 0.1
    .global lbl_8051F364
    lbl_8051F364:
        .float 1.0
    .global lbl_8051F368
    lbl_8051F368:
        .4byte 0x3DF5C28F
    .global lbl_8051F36C
    lbl_8051F36C:
        .4byte 0xBDF5C28F
*/

/*
 * __ct
 * --INFO--
 * Address:	803A3644
 * Size:	000050
 */
Morimura::TConfirmEndWindow::TConfirmEndWindow(char const* p1)
    : og::newScreen::ObjWorldMapInfoWindow0(p1)
    , m_isOpenMaybe(false)
    , _D5(0)
{
}

/*
 * --INFO--
 * Address:	803A3694
 * Size:	000040
 */
bool Morimura::TConfirmEndWindow::doStart(Screen::StartSceneArg const* arg)
{
	_44           = 0.0f;
	m_isOpenMaybe = false;
	_D5           = 1;
	_CC->_21      = 1;
	return og::newScreen::ObjWorldMapInfoWindow0::doStart(arg);
}

/*
 * --INFO--
 * Address:	803A36D4
 * Size:	000054
 */
void Morimura::TConfirmEndWindow::doUpdateFadeinFinish(void)
{
	_B8->open(0.05f);
	_BC->open(0.1f);
	blink_Menu(_AC);
	og::newScreen::ObjSMenuPauseVS::doUpdateFadeinFinish();
}

/*
 * --INFO--
 * Address:	803A3728
 * Size:	000020
 */
bool Morimura::TConfirmEndWindow::doUpdateFadein(void)
{
	og::newScreen::ObjWorldMapInfoWindow0::doUpdateFadein();
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	bl       doUpdateFadein__Q32og9newScreen22ObjWorldMapInfoWindow0Fv
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	803A3748
 * Size:	000040
 */
void Morimura::TConfirmEndWindow::doUpdateFadeoutFinish(void)
{
	m_isOpenMaybe = false;
	_B8->stop();
	_BC->stop();
}

/*
 * --INFO--
 * Address:	803A3788
 * Size:	000028
 */
bool Morimura::TConfirmEndWindow::doUpdateFadeout()
{
	_D5 = 0;
	return og::newScreen::ObjSMenuPauseVS::doUpdateFadeout();
}

/*
 * --INFO--
 * Address:	803A37B0
 * Size:	000038
 */
void Morimura::TConfirmEndWindow::doDraw(Graphics& gfx)
{
	if (m_isOpenMaybe) {
		ObjSMenuPauseVS::doDraw(gfx);
	} else {
		m_isOpenMaybe = true;
	}
}

/*
 * --INFO--
 * Address:	803A37E8
 * Size:	000024
 */
void Morimura::TConfirmEndWindow::setRetireMsg(u64 msgID) { _BC->setText(msgID); }

/*
 * --INFO--
 * Address:	803A380C
 * Size:	000074
 */
Morimura::TSelectExplanationWindow::TSelectExplanationWindow(JKRArchive* archive, int p2)
    : TScreenBase(archive, p2)
{
	_18        = 0;
	_24        = 0.0f;
	_28        = 0.0f;
	_1C        = 0.0f;
	_20        = 0.0f;
	m_scaleMgr = new og::Screen::ScaleMgr();
}

/*
 * --INFO--
 * Address:	803A3880
 * Size:	000194
 */
void Morimura::TSelectExplanationWindow::update(void)
{
	if (_18 == 0) {
		_24 = 0.0f;
	} else {
		_08->update();
		for (int i = 0; i < _10; i++) {
			m_animScreens[i]->update();
		}
		switch (_18) {
		case 1:
			_28 += _24;
			if (1.0f <= _28) {
				_28 = 1.0f;
				_0C = nullptr;
				_18 = 2;
			}
			break;
		case 2:
			break;
		case 3:
			_28 += _24;
			if (_28 < 0.0f) {
				_28 = 0.0f;
				_24 = 0.0f;
				_18 = 0;
			}
			break;
		}
		_08->animation();
	}
	_08->m_screenScaleX = (1.0f - _28) * _1C - P2DScreen::Mgr_tuning::mstTuningTransX;
	_08->m_screenScaleY = (1.0f - _28) * _20 - P2DScreen::Mgr_tuning::mstTuningTransY;
	float calcResult    = m_scaleMgr->calc();
	_08->m_someX        = calcResult * P2DScreen::Mgr_tuning::mstTuningScaleX;
	_08->m_someY        = calcResult * P2DScreen::Mgr_tuning::mstTuningScaleY;
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	mr       r29, r3
	lwz      r0, 0x18(r3)
	cmpwi    r0, 0
	bne      lbl_803A38B4
	lfs      f0, lbl_8051F358@sda21(r2)
	stfs     f0, 0x24(r29)
	b        lbl_803A399C

lbl_803A38B4:
	lwz      r3, 8(r29)
	lwz      r12, 0(r3)
	lwz      r12, 0x30(r12)
	mtctr    r12
	bctrl
	li       r30, 0
	li       r31, 0
	b        lbl_803A38E8

lbl_803A38D4:
	lwz      r3, 4(r29)
	lwzx     r3, r3, r31
	bl       update__Q32og6Screen12AnimBaseBaseFv
	addi     r31, r31, 4
	addi     r30, r30, 1

lbl_803A38E8:
	lwz      r0, 0x10(r29)
	cmpw     r30, r0
	blt      lbl_803A38D4
	lwz      r0, 0x18(r29)
	cmpwi    r0, 2
	beq      lbl_803A3994
	bge      lbl_803A3910
	cmpwi    r0, 1
	bge      lbl_803A391C
	b        lbl_803A3994

lbl_803A3910:
	cmpwi    r0, 4
	bge      lbl_803A3994
	b        lbl_803A3964

lbl_803A391C:
	lfs      f2, 0x28(r29)
	lfs      f1, 0x24(r29)
	lfs      f0, lbl_8051F364@sda21(r2)
	fadds    f1, f2, f1
	stfs     f1, 0x28(r29)
	lfs      f1, 0x28(r29)
	fcmpo    cr0, f1, f0
	cror     2, 1, 2
	bne      lbl_803A3994
	stfs     f0, 0x28(r29)
	mr       r3, r29
	lwz      r12, 0(r29)
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl
	li       r0, 2
	stw      r0, 0x18(r29)
	b        lbl_803A3994

lbl_803A3964:
	lfs      f2, 0x28(r29)
	lfs      f1, 0x24(r29)
	lfs      f0, lbl_8051F358@sda21(r2)
	fadds    f1, f2, f1
	stfs     f1, 0x28(r29)
	lfs      f1, 0x28(r29)
	fcmpo    cr0, f1, f0
	bge      lbl_803A3994
	stfs     f0, 0x28(r29)
	li       r0, 0
	stfs     f0, 0x24(r29)
	stw      r0, 0x18(r29)

lbl_803A3994:
	lwz      r3, 8(r29)
	bl       animation__9J2DScreenFv

lbl_803A399C:
	lfs      f1, lbl_8051F364@sda21(r2)
	lfs      f0, 0x28(r29)
	lfs      f2, 0x1c(r29)
	fsubs    f4, f1, f0
	lfs      f3, 0x20(r29)
	lfs      f1, mstTuningTransX__Q29P2DScreen10Mgr_tuning@sda21(r2)
	lfs      f0, mstTuningTransY__Q29P2DScreen10Mgr_tuning@sda21(r2)
	fmuls    f2, f4, f2
	lwz      r3, 8(r29)
	fmuls    f3, f4, f3
	fadds    f1, f2, f1
	fadds    f0, f3, f0
	stfs     f1, 0x140(r3)
	stfs     f0, 0x144(r3)
	lwz      r3, 0x2c(r29)
	bl       calc__Q32og6Screen8ScaleMgrFv
	lfs      f2, mstTuningScaleX__Q29P2DScreen10Mgr_tuning@sda21(r2)
	lfs      f0, mstTuningScaleY__Q29P2DScreen10Mgr_tuning@sda21(r2)
	fmuls    f2, f1, f2
	lwz      r3, 8(r29)
	fmuls    f0, f1, f0
	stfs     f2, 0x138(r3)
	stfs     f0, 0x13c(r3)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	803A3A14
 * Size:	00002C
 */
void Morimura::TSelectExplanationWindow::draw(Graphics& gfx, J2DPerspGraph* perspGraph)
{
	if (_18 != 0) {
		TScreenBase::draw(gfx, perspGraph);
	}
}

/*
 * --INFO--
 * Address:	803A3A40
 * Size:	000014
 */
void Morimura::TSelectExplanationWindow::openWindow(void)
{
	_24 = 0.12f;
	_18 = 1;
}

/*
 * --INFO--
 * Address:	803A3A54
 * Size:	000014
 */
void Morimura::TSelectExplanationWindow::closeWindow(void)
{
	_24 = -0.12f;
	_18 = 3;
}
