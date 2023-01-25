#include "kh/khUtil.h"
#include "Vector3.h"

namespace kh {
namespace Screen {

/*
 * --INFO--
 * Address:	8040B3F4
 * Size:	00004C
 */
u64 getSerialTagName(u64 tag, int offs) { return tag + (offs / 10 * 0x100) + offs % 10; }

/*
 * --INFO--
 * Address:	8040B440
 * Size:	000050
 */
void setTex(J2DScreen* screen, u64 tag, const ResTIMG* tex) { static_cast<J2DPicture*>(screen->search(tag))->changeTexture(tex, '\0'); }

/*
 * --INFO--
 * Address:	8040B490
 * Size:	000050
 */
void setTex(J2DScreen* screen, u64 tag, const char* str) { static_cast<J2DPicture*>(screen->search(tag))->changeTexture(str, '\0'); }

/*
 * --INFO--
 * Address:	8040B4E0
 * Size:	000210
 */
void setMatAnm(J2DPane* pane, J2DAnmBase* anm)
{
	pane->setAnimation(anm);
	JSUTree<J2DPane>* tree = pane->getPaneTree();
	JSUTreeIterator<J2DPane> iterator(tree->getFirstChild());
	while (iterator != tree->getEndChild()) {
		setMatAnm(iterator.getObject(), anm);
		++iterator;
	}
}

/*
 * --INFO--
 * Address:	8040B6F0
 * Size:	00021C
 */
void setInfAlpha(J2DPane* pane)
{
	pane->setInfluencedAlpha(true, false);
	JSUTree<J2DPane>* tree = pane->getPaneTree();
	JSUTreeIterator<J2DPane> iterator(tree->getFirstChild());
	while (iterator != tree->getEndChild()) {
		setInfAlpha(iterator.getObject());
		++iterator;
	}
}

/*
 * --INFO--
 * Address:	8040B90C
 * Size:	0000EC
 */
f32 getPaneCenterX(J2DPane* pane)
{
	Vector3f vec1 = pane->getGlbVtx(0);
	Vector3f vec2 = pane->getGlbVtx(1);
	Vector3f vec3 = pane->getGlbVtx(2);
	Vector3f vec4 = pane->getGlbVtx(3);

	return (vec1.x + vec2.x + vec3.x + vec4.x) * 0.25f;
}

/*
 * --INFO--
 * Address:	8040B9F8
 * Size:	0000EC
 */
f32 getPaneCenterY(J2DPane* pane)
{
	Vector3f vec1 = pane->getGlbVtx(0);
	Vector3f vec2 = pane->getGlbVtx(1);
	Vector3f vec3 = pane->getGlbVtx(2);
	Vector3f vec4 = pane->getGlbVtx(3);

	return (vec1.y + vec2.y + vec3.y + vec4.y) * 0.25f;
}

/*
 * --INFO--
 * Address:	8040BAE4
 * Size:	0000A4
 */
khUtilFadePane* khUtilFadePane::create(P2DScreen::Mgr* mgr, u64 tag, u8 c)
{
	if (mgr == nullptr) {
		return nullptr;
	}
	khUtilFadePane* pane = new khUtilFadePane(c);
	P2ASSERTLINE(146, pane != nullptr);
	pane->add(mgr->addCallBack(tag, pane));
	return pane;
}

/*
 * --INFO--
 * Address:	8040BB88
 * Size:	000088
 */
khUtilFadePane::khUtilFadePane(u8 c)
    : CallBackNode()
    , mPaneNode(nullptr)
    , mState(0)
    , mCurrentAlpha('\0')
    , mChangeAlpha(c)
{
}

/*
 * --INFO--
 * Address:	8040BC10
 * Size:	000104
 */
void khUtilFadePane::update()
{
	switch (mState) {
	case 0:
		if (mCurrentAlpha > 255 - mChangeAlpha) {
			mCurrentAlpha = 255;
			mState        = 1;
			fadein_finish();
		} else {
			mCurrentAlpha += mChangeAlpha;
		}
		break;
	case 2:
		if (mCurrentAlpha < mChangeAlpha) {
			mCurrentAlpha = 0;
			mState        = 3;
			fadeout_finish();
		} else {
			mCurrentAlpha -= mChangeAlpha;
		}
		break;
	}

	FOREACH_NODE(khPaneNode, mPaneNode.mNext, node) { node->mPane->setAlpha(mCurrentAlpha); }
}

/*
 * --INFO--
 * Address:	8040BD18
 * Size:	0000B8
 */
bool khUtilFadePane::add(J2DPane* pane)
{
	bool result = false;
	if (pane) {
		khPaneNode* node = &mPaneNode;
		khPaneNode* node2;
		while (node) {
			node2 = node;
			node  = node2->mNext;
		}
		node = new khPaneNode(pane);
		P2ASSERTLINE(64, node);
		node2->mNext = node;
		result       = true;
		setInfAlpha(pane);
	}
	return result;
	/*
stwu     r1, -0x20(r1)
mflr     r0
stw      r0, 0x24(r1)
stw      r31, 0x1c(r1)
stw      r30, 0x18(r1)
li       r30, 0
stw      r29, 0x14(r1)
or.      r29, r4, r4
beq      lbl_8040BDB0
addi     r30, r3, 0x1c
b        lbl_8040BD48

lbl_8040BD44:
mr       r30, r0

lbl_8040BD48:
lwz      r0, 8(r30)
cmplwi   r0, 0
bne      lbl_8040BD44
li       r3, 0xc
bl       __nw__FUl
or.      r31, r3, r3
beq      lbl_8040BD7C
lis      r3, __vt__Q42kh6Screen14khUtilFadePane10khPaneNode@ha
li       r0, 0
addi     r3, r3, __vt__Q42kh6Screen14khUtilFadePane10khPaneNode@l
stw      r3, 0(r31)
stw      r29, 4(r31)
stw      r0, 8(r31)

lbl_8040BD7C:
cmplwi   r31, 0
bne      lbl_8040BDA0
lis      r3, lbl_80498CC8@ha
lis      r5, lbl_80498CBC@ha
addi     r3, r3, lbl_80498CC8@l
li       r4, 0x40
addi     r5, r5, lbl_80498CBC@l
crclr    6
bl       panic_f__12JUTExceptionFPCciPCce

lbl_8040BDA0:
stw      r31, 8(r30)
mr       r3, r29
li       r30, 1
bl       setInfAlpha__Q22kh6ScreenFP7J2DPane

lbl_8040BDB0:
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
 * Address:	8040BDD0
 * Size:	000020
 */
void khUtilFadePane::fadein()
{
	if (mState == 2 || mState == 3)
		mState = 0;
}

/*
 * --INFO--
 * Address:	8040BDF0
 * Size:	000020
 */
void khUtilFadePane::fadeout()
{
	if (mState == 0 || mState == 1)
		mState = 2;
}

/*
 * --INFO--
 * Address:	8040BE10
 * Size:	000060
 */
void khUtilFadePane::set_init_alpha(u8 a)
{
	mCurrentAlpha = a;
	FOREACH_NODE(khPaneNode, mPaneNode.mNext, node) { node->mPane->setAlpha(mCurrentAlpha); }
}

/*
 * --INFO--
 * Address:	8040BE70
 * Size:	000158
 */
khUtilColorAnm::khUtilColorAnm(P2DScreen::Mgr* screen, u64 tag, int panes, int frames)
{
	mPaneNum  = panes;
	mMaxFrame = frames;
	mCounter  = 0;
	mColor1.set(0, 0, 0, 0);
	mColorList = new JUtility::TColor[mPaneNum];
	for (int i = 0; i < mPaneNum; i++) {
		mColorList[i].set(0, 0, 0, 0);
	}
	mColor2.setRGBA(mColor1);
	mUpdateMode = 0;
	if (screen) {
		screen->addCallBack(tag, this);
	}
}

/*
 * --INFO--
 * Address:	8040BFC8
 * Size:	00021C
 */
void khUtilColorAnm::update()
{
	if (mUpdateMode) {
		f32 calc              = (mCounter * (mPaneNum - 1)) / (f32)mMaxFrame;
		int id                = calc;
		JUtility::TColor col1 = mColorList[id + 1];
		JUtility::TColor col2 = mColorList[id];
		calc -= (f32)id;
		f32 calc2 = 1.0f - calc;

		mColor1.r = (f32)col1.r * calc2 + (f32)col2.r * calc;
		mColor1.g = (f32)col1.g * calc2 + (f32)col2.g * calc;
		mColor1.b = (f32)col1.b * calc2 + (f32)col2.b * calc;
		mColor1.a = (f32)col1.a * calc2 + (f32)col2.a * calc;

		if (mCounter++ >= mMaxFrame) {
			mCounter = 0;
		}
	} else {
		mColor1.setRGBA(mColor2);
		mCounter = 0;
	}
	do_update();
	/*
stwu     r1, -0x90(r1)
mflr     r0
stw      r0, 0x94(r1)
lbz      r0, 0x34(r3)
cmplwi   r0, 0
beq      lbl_8040C19C
lwz      r4, 0x28(r3)
lis      r6, 0x4330
lwz      r5, 0x30(r3)
addi     r4, r4, -1
lwz      r0, 0x2c(r3)
mullw    r4, r5, r4
stw      r6, 0x10(r1)
xoris    r0, r0, 0x8000
lfd      f3, lbl_80520188@sda21(r2)
stw      r0, 0x1c(r1)
lwz      r8, 0x1c(r3)
xoris    r0, r4, 0x8000
stw      r6, 0x18(r1)
lfd      f6, lbl_80520190@sda21(r2)
stw      r0, 0x14(r1)
lfd      f0, 0x18(r1)
lfd      f1, 0x10(r1)
fsubs    f0, f0, f3
stw      r6, 0x28(r1)
fsubs    f2, f1, f3
lfs      f1, lbl_80520184@sda21(r2)
stw      r6, 0x38(r1)
fdivs    f8, f2, f0
stw      r6, 0x50(r1)
stw      r6, 0x30(r1)
stw      r6, 0x68(r1)
stw      r6, 0x48(r1)
stw      r6, 0x60(r1)
fctiwz   f0, f8
stfd     f0, 0x20(r1)
lwz      r7, 0x24(r1)
addi     r0, r7, 1
slwi     r5, r7, 2
slwi     r4, r0, 2
xoris    r0, r7, 0x8000
lwzx     r4, r8, r4
stw      r0, 0x2c(r1)
lwzx     r0, r8, r5
stw      r4, 8(r1)
lfd      f0, 0x28(r1)
stw      r0, 0xc(r1)
lbz      r4, 8(r1)
fsubs    f0, f0, f3
lbz      r0, 9(r1)
stw      r4, 0x3c(r1)
lbz      r4, 0xc(r1)
fsubs    f8, f8, f0
stw      r0, 0x54(r1)
lfd      f0, 0x38(r1)
lbz      r0, 0xa(r1)
fsubs    f7, f1, f8
stw      r4, 0x34(r1)
fsubs    f1, f0, f6
lbz      r4, 0xd(r1)
stw      r0, 0x6c(r1)
lfd      f0, 0x50(r1)
fmuls    f4, f1, f8
stw      r4, 0x4c(r1)
lfd      f2, 0x30(r1)
fsubs    f1, f0, f6
lbz      r0, 0xe(r1)
lfd      f0, 0x68(r1)
fsubs    f5, f2, f6
stw      r0, 0x64(r1)
fmuls    f2, f1, f8
lfd      f3, 0x48(r1)
fsubs    f0, f0, f6
lfd      f1, 0x60(r1)
fsubs    f3, f3, f6
fmadds   f4, f5, f7, f4
fsubs    f1, f1, f6
fmuls    f0, f0, f8
fmadds   f2, f3, f7, f2
fctiwz   f3, f4
fmadds   f0, f1, f7, f0
fctiwz   f1, f2
stfd     f3, 0x40(r1)
fctiwz   f0, f0
stfd     f1, 0x58(r1)
lwz      r0, 0x44(r1)
stfd     f0, 0x70(r1)
lwz      r4, 0x5c(r1)
stb      r0, 0x20(r3)
lwz      r0, 0x74(r1)
stb      r4, 0x21(r3)
stb      r0, 0x22(r3)
lbz      r0, 0xb(r1)
lbz      r4, 0xf(r1)
stw      r0, 0x84(r1)
stw      r6, 0x80(r1)
lfd      f0, 0x80(r1)
stw      r4, 0x7c(r1)
fsubs    f0, f0, f6
stw      r6, 0x78(r1)
lfd      f1, 0x78(r1)
fmuls    f0, f0, f8
fsubs    f1, f1, f6
fmadds   f0, f1, f7, f0
fctiwz   f0, f0
stfd     f0, 0x88(r1)
lwz      r0, 0x8c(r1)
stb      r0, 0x23(r3)
lwz      r4, 0x30(r3)
addi     r4, r4, 1
stw      r4, 0x30(r3)
lwz      r0, 0x2c(r3)
cmpw     r4, r0
blt      lbl_8040C1C4
li       r0, 0
stw      r0, 0x30(r3)
b        lbl_8040C1C4

lbl_8040C19C:
lbz      r4, 0x24(r3)
li       r0, 0
stb      r4, 0x20(r3)
lbz      r4, 0x25(r3)
stb      r4, 0x21(r3)
lbz      r4, 0x26(r3)
stb      r4, 0x22(r3)
lbz      r4, 0x27(r3)
stb      r4, 0x23(r3)
stw      r0, 0x30(r3)

lbl_8040C1C4:
lwz      r12, 0(r3)
lwz      r12, 0x1c(r12)
mtctr    r12
bctrl
lwz      r0, 0x94(r1)
mtlr     r0
addi     r1, r1, 0x90
blr
	*/
}

} // namespace Screen
} // namespace kh
