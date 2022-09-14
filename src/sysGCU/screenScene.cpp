#include "Dolphin/stl.h"
#include "IDelegate.h"
#include "JSystem/JKR/JKRArchive.h"
#include "JSystem/JUT/JUTException.h"
#include "JSystem/JUT/TColor.h"
#include "Screen/Enums.h"
#include "Screen/SceneInfoList.h"
#include "og/Screen/DispMemberDummy.h"
#include "og/Screen/ogScreen.h"
#include "og/newScreen/ogUtil.h"
#include "Screen/Bases.h"
#include "System.h"
#include "types.h"

/*
    Generated from dpostproc

    .section .rodata  # 0x804732E0 - 0x8049E220
    .global lbl_8049B8A0
    lbl_8049B8A0:
        .4byte 0x73637265
        .4byte 0x656E5363
        .4byte 0x656E652E
        .4byte 0x63707000
    .global lbl_8049B8B0
    lbl_8049B8B0:
        .asciz "P2Assert"
        .skip 3
    .global lbl_8049B8BC
    lbl_8049B8BC:
        .4byte 0x73637265
        .4byte 0x656E4D67
        .4byte 0x722E6800

    .section .data, "wa"	# 0x8049E220 - 0x804EFC20
    .global lbl_804ED680
    lbl_804ED680:
        .4byte 0x00000000
        .4byte 0xFFFFFFFF
        .4byte userCallBackFunc__Q26Screen9SceneBaseFPQ28Resource10MgrCommand
    .global __vt__Q26Screen9SceneBase
    __vt__Q26Screen9SceneBase:
        .4byte 0
        .4byte 0
        .4byte 0
        .4byte 0
        .4byte 0
        .4byte isUseBackupSceneInfo__Q26Screen9SceneBaseFv
        .4byte isDrawInDemo__Q26Screen9SceneBaseCFv
        .4byte 0
        .4byte 0
        .4byte doUserCallBackFunc__Q26Screen9SceneBaseFPQ28Resource10MgrCommand
        .4byte setPort__Q26Screen9SceneBaseFR8Graphics
        .4byte doUpdateActive__Q26Screen9SceneBaseFv
        .4byte doConfirmSetScene__Q26Screen9SceneBaseFRQ26Screen11SetSceneArg
        .4byte
   doConfirmStartScene__Q26Screen9SceneBaseFPQ26Screen13StartSceneArg .4byte
   doConfirmEndScene__Q26Screen9SceneBaseFRPQ26Screen11EndSceneArg .4byte
   doStart__Q26Screen9SceneBaseFPQ26Screen13StartSceneArg .4byte
   doEnd__Q26Screen9SceneBaseFPQ26Screen11EndSceneArg .4byte
   setDefaultDispMember__Q26Screen9SceneBaseFv .4byte
   doSetBackupScene__Q26Screen9SceneBaseFRQ26Screen11SetSceneArg .4byte
   doGetFinishState__Q26Screen9SceneBaseFv .global
   "__vt__55Delegate1<Q26Screen9SceneBase,PQ28Resource10MgrCommand>"
    "__vt__55Delegate1<Q26Screen9SceneBase,PQ28Resource10MgrCommand>":
        .4byte 0
        .4byte 0
        .4byte
   "invoke__55Delegate1<Q26Screen9SceneBase,PQ28Resource10MgrCommand>FPQ28Resource10MgrCommand"
    .global "__vt__36IDelegate1<PQ28Resource10MgrCommand>"
    "__vt__36IDelegate1<PQ28Resource10MgrCommand>":
        .4byte 0
        .4byte 0
        .4byte 0
        .4byte 0

    .section .sdata2, "a"     # 0x80516360 - 0x80520E40
    .global lbl_80520B70
    lbl_80520B70:
        .4byte 0x6E6F206E
        .4byte 0x616D6500
    .global lbl_80520B78
    lbl_80520B78:
        .4byte 0x3F3F3F00
    .global lbl_80520B7C
    lbl_80520B7C:
        .4byte 0x00000000
*/

namespace Screen {

/*
 * --INFO--
 * Address:	80451790
 * Size:	000134
 */
SceneBase::SceneBase(void)
    : m_controller(nullptr)
    , m_screenMgr(nullptr)
    , _10C(this, &SceneBase::userCallBackFunc)
    , m_stateID(Unknown0)
    , m_command("no name")
    , m_objMgr(nullptr)
{
	m_objMgr           = new ObjMgrBase();
	m_dispMemberBuffer = new u8[0x400];
	P2ASSERTLINE(113, m_dispMemberBuffer != nullptr);
	og::Screen::DispMemberDummy dummy;
	memcpy(m_dispMemberBuffer, (void*)&dummy, sizeof(dummy));
	sprintf(m_name, "???");
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	lis      r5, lbl_804ED680@ha
	lis      r4, __vt__Q26Screen9SceneBase@ha
	stw      r0, 0x34(r1)
	addi     r0, r4, __vt__Q26Screen9SceneBase@l
	li       r9, 0
	addi     r6, r5, lbl_804ED680@l
	stw      r31, 0x2c(r1)
	lis      r4, "__vt__36IDelegate1<PQ28Resource10MgrCommand>"@ha
	addi     r5, r4, "__vt__36IDelegate1<PQ28Resource10MgrCommand>"@l
	mr       r31, r3
	stw      r0, 0(r3)
	lis      r3,
"__vt__55Delegate1<Q26Screen9SceneBase,PQ28Resource10MgrCommand>"@ha addi r0,
r3, "__vt__55Delegate1<Q26Screen9SceneBase,PQ28Resource10MgrCommand>"@l addi r4,
r2, lbl_80520B70@sda21 stw      r9, 0x104(r31) addi     r3, r31, 0x128 stw r9,
0x108(r31) lwz      r8, 0(r6) lwz      r7, 4(r6) lwz      r6, 8(r6) stw      r8,
0x10(r1) stw      r5, 0x10c(r31) stw      r0, 0x10c(r31) stw      r31,
0x110(r31) stw      r8, 0x114(r31) stw      r7, 0x118(r31) stw      r6,
0x11c(r31) stw      r7, 0x14(r1) stw      r6, 0x18(r1) stw      r9, 0x120(r31)
	bl       __ct__Q28Resource10MgrCommandFPc
	li       r0, 0
	li       r3, 0x18
	stw      r0, 0x218(r31)
	bl       __nw__FUl
	or.      r0, r3, r3
	beq      lbl_80451834
	bl       __ct__Q26Screen10ObjMgrBaseFv
	mr       r0, r3

lbl_80451834:
	stw      r0, 0x218(r31)
	li       r3, 0x400
	bl       __nwa__FUl
	stw      r3, 0x21c(r31)
	lwz      r0, 0x21c(r31)
	cmplwi   r0, 0
	bne      lbl_8045186C
	lis      r3, lbl_8049B8A0@ha
	lis      r5, lbl_8049B8B0@ha
	addi     r3, r3, lbl_8049B8A0@l
	li       r4, 0x71
	addi     r5, r5, lbl_8049B8B0@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045186C:
	lis      r4, __vt__Q32og6Screen14DispMemberBase@ha
	lis      r3, __vt__Q32og6Screen15DispMemberDummy@ha
	addi     r0, r4, __vt__Q32og6Screen14DispMemberBase@l
	li       r6, 0
	stw      r0, 8(r1)
	addi     r0, r3, __vt__Q32og6Screen15DispMemberDummy@l
	addi     r4, r1, 8
	li       r5, 8
	stw      r6, 0xc(r1)
	stw      r0, 8(r1)
	lwz      r3, 0x21c(r31)
	bl       memcpy
	addi     r3, r31, 4
	addi     r4, r2, lbl_80520B78@sda21
	crclr    6
	bl       sprintf
	lwz      r0, 0x34(r1)
	mr       r3, r31
	lwz      r31, 0x2c(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	804518C4
 * Size:	000030
 */
IObjBase* SceneBase::searchObj(char* name) { return m_objMgr->search(this, name); }

/*
 * --INFO--
 * Address:	804518F4
 * Size:	000038
 */
void SceneBase::destroy(void)
{
	if (m_command._30 != -1) {
		gResMgr2D->destroy(&m_command);
	}
}

/*
 * --INFO--
 * Address:	8045192C
 * Size:	0000BC
 */
void SceneBase::create(void)
{
	if (m_command._30 == -1) {
		m_someTime    = sys->getTime();
		m_command._B0 = &_10C;
		if (getResName()[0] != '\0') {
			og::newScreen::makeLanguageResName(m_name, getResName());
			gResMgr2D->loadResource(&m_command, m_name, true);
		} else {
			gResMgr2D->loadResource(&m_command, "", true);
		}
		m_stateID = Unknown1;
	}
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	lwz      r0, 0x158(r3)
	cmpwi    r0, -1
	bne      lbl_804519D4
	lwz      r3, sys@sda21(r13)
	bl       getTime__6SystemFv
	stfs     f1, 0x124(r31)
	addi     r0, r31, 0x10c
	mr       r3, r31
	stw      r0, 0x1d8(r31)
	lwz      r12, 0(r31)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	lbz      r0, 0(r3)
	extsb.   r0, r0
	beq      lbl_804519B8
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	addi     r3, r31, 4
	bl       makeLanguageResName__Q22og9newScreenFPcPCc
	lwz      r3, gResMgr2D@sda21(r13)
	addi     r4, r31, 0x128
	addi     r5, r31, 4
	li       r6, 1
	bl       loadResource__Q28Resource3MgrFPQ28Resource10MgrCommandPCcb
	b        lbl_804519CC

lbl_804519B8:
	lwz      r3, gResMgr2D@sda21(r13)
	addi     r4, r31, 0x128
	addi     r5, r2, lbl_80520B7C@sda21
	li       r6, 1
	bl       loadResource__Q28Resource3MgrFPQ28Resource10MgrCommandPCcb

lbl_804519CC:
	li       r0, 1
	stw      r0, 0x120(r31)

lbl_804519D4:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	804519E8
 * Size:	00015C
 */
void SceneBase::update()
{
	switch (m_stateID) {
	case Unknown0:
		break;
	case Unknown1:
		if (gResMgr2D->sync(&m_command, false) != false) {
			if (getResName()[0] != '\0') {
				void* res = m_command.getResource();
				P2ASSERTLINE(194, res != nullptr);
				m_command.becomeCurrentHeap();
				JKRArchive* archive = JKRArchive::mount(res, nullptr, JKRArchive::EMD_Unk1);
				P2ASSERTLINE(197, archive != nullptr);
				createObj(archive);
				m_command.releaseCurrentHeap();
			}
			m_stateID = Unknown2;
			sys->getTime();
		}
		break;
	case Unknown2:
		break;
	case Unknown3:
		if (updateActive()) {
			m_stateID = Unknown4;
		}
		break;
	case Unknown4:
		break;
	default:
		JUTException::panic_f(__FILE__, 226, "P2Assert");
		break;
	}
}

/*
 * --INFO--
 * Address:	80451B44
 * Size:	000040
 */
bool SceneBase::updateActive()
{
	doUpdateActive();
	return m_objMgr->update();
}

/*
 * --INFO--
 * Address:	80451B84
 * Size:	000004
 */
void SceneBase::doUpdateActive() { }

/*
 * @note `break;` has a different result from `return;` here.
 * --INFO--
 * Address:	80451B88
 * Size:	000090
 */
void SceneBase::draw(Graphics& gfx)
{
	switch (m_stateID) {
	case Unknown0:
	case Unknown1:
	case Unknown2:
		// return;
		break;
	case Unknown3:
	case Unknown4:
		setPort(gfx);
		m_objMgr->draw(gfx);
		// return;
		break;
	default:
		P2ASSERTLINE(285, false);
	}
}

/*
 * --INFO--
 * Address:	80451C18
 * Size:	000050
 */
bool SceneBase::start(Screen::StartSceneArg* arg)
{
	if (m_stateID != Unknown0 && m_stateID != Unknown1) {
		m_stateID = Unknown3;
		return doStart(arg);
	} else {
		return false;
	}
}

/*
 * --INFO--
 * Address:	80451C68
 * Size:	000028
 */
bool SceneBase::doStart(Screen::StartSceneArg* arg)
{
	m_objMgr->start(arg);
	return true;
}

/*
 * --INFO--
 * Address:	80451C90
 * Size:	000068
 */
bool SceneBase::end(Screen::EndSceneArg* arg)
{
	bool result;
	if (m_stateID == Unknown0 || m_stateID == Unknown2) {
		m_stateID = Unknown4;
		result    = true;
	} else if (m_stateID != Unknown1) {
		result = doEnd(arg);
	} else {
		result = false;
	}
	return result;
}

/*
 * --INFO--
 * Address:	80451CF8
 * Size:	000024
 */
bool SceneBase::doEnd(Screen::EndSceneArg* arg) { return m_objMgr->end(arg); }

/*
 * --INFO--
 * Address:	80451D1C
 * Size:	00002C
 */
void SceneBase::userCallBackFunc(Resource::MgrCommand* command) { doUserCallBackFunc(command); }

/*
 * --INFO--
 * Address:	80451D48
 * Size:	00002C
 */
void SceneBase::createObj(JKRArchive* archive) { doCreateObj(archive); }

/*
 * --INFO--
 * Address:	80451D74
 * Size:	00005C
 */
void SceneBase::registObj(Screen::ObjBase* obj, JKRArchive* archive)
{
	m_objMgr->registObj(obj, this);
	obj->create(archive);
}

/*
 * --INFO--
 * Address:	80451DD0
 * Size:	000078
 */
bool SceneBase::confirmSetScene(Screen::SetSceneArg& arg) { return (m_objMgr->confirmSetScene(arg) && doConfirmSetScene(arg)); }

/*
 * --INFO--
 * Address:	80451E48
 * Size:	000078
 */
bool SceneBase::confirmStartScene(Screen::StartSceneArg* arg) { return (m_objMgr->confirmStartScene(arg) && doConfirmStartScene(arg)); }

/*
 * --INFO--
 * Address:	80451EC0
 * Size:	000070
 */
bool SceneBase::confirmEndScene(Screen::EndSceneArg* arg) { return (m_objMgr->confirmEndScene(arg) && doConfirmEndScene(arg)); }

/*
 * setScene__Q26Screen9SceneBaseFRQ26Screen11SetSceneArg
 * --INFO--
 * Address:	80451F30
 * Size:	000030
 */
void SceneBase::setScene(Screen::SetSceneArg& arg) { m_screenMgr->setScene(arg); }

/*
 * startScene__Q26Screen9SceneBaseFPQ26Screen13StartSceneArg
 * --INFO--
 * Address:	80451F60
 * Size:	000030
 */
void SceneBase::startScene(Screen::StartSceneArg* arg) { m_screenMgr->startScene(arg); }

/*
 * endScene__Q26Screen9SceneBaseFPQ26Screen11EndSceneArg
 * --INFO--
 * Address:	80451F90
 * Size:	000030
 */
void SceneBase::endScene(Screen::EndSceneArg* arg) { m_screenMgr->endScene(arg); }

/*
 * setBackupScene__Q26Screen9SceneBaseFv
 * --INFO--
 * Address:	80451FC0
 * Size:	000100
 */
bool SceneBase::setBackupScene()
{
	bool result         = false;
	SceneInfoList* list = (SceneInfoList*)m_screenMgr->_60.m_child;
	if (list != nullptr) {
		SetSceneArg arg(list->m_sceneType, (og::Screen::DispMemberBase*)list->m_dispMemberBuffer);
		// SetSceneArg arg;
		// arg.m_sceneType = list->m_sceneType;
		// arg.m_dispMember = (og::Screen::DispMemberBase*)list->m_dispMemberBuffer;
		arg._08 = 0;
		arg._09 = true;
		doSetBackupScene(arg);
		result = m_screenMgr->setScene(arg);
		if (result) {
			Mgr* mgr  = m_screenMgr;
			CNode* v1 = mgr->_60.m_child;
			P2ASSERTLINE(329, v1 != nullptr);
			v1->del();
			mgr->m_sceneInfoListNode.add(v1);
		}
	}
	return result;
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stw      r31, 0x2c(r1)
	stw      r30, 0x28(r1)
	mr       r30, r3
	stw      r29, 0x24(r1)
	li       r29, 0
	lwz      r4, 0x108(r3)
	lwz      r5, 0x70(r4)
	cmplwi   r5, 0
	beq      lbl_804520A0
	lwz      r7, 0x18(r5)
	lis      r4, __vt__Q26Screen12SceneArgBase@ha
	addi     r0, r4, __vt__Q26Screen12SceneArgBase@l
	lis      r4, __vt__Q26Screen11SetSceneArg@ha
	stw      r0, 8(r1)
	addi     r4, r4, __vt__Q26Screen11SetSceneArg@l
	addi     r0, r5, 0x1c
	li       r6, 0
	li       r5, 1
	stw      r4, 8(r1)
	addi     r4, r1, 8
	stw      r7, 0xc(r1)
	stb      r6, 0x10(r1)
	stb      r5, 0x11(r1)
	stw      r0, 0x14(r1)
	lwz      r12, 0(r3)
	lwz      r12, 0x48(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0x108(r30)
	addi     r4, r1, 8
	lwz      r12, 0(r3)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	clrlwi.  r0, r3, 0x18
	mr       r29, r3
	beq      lbl_804520A0
	lwz      r31, 0x108(r30)
	lwz      r30, 0x70(r31)
	cmplwi   r30, 0
	bne      lbl_8045208C
	lis      r3, lbl_8049B8BC@ha
	lis      r5, lbl_8049B8B0@ha
	addi     r3, r3, lbl_8049B8BC@l
	li       r4, 0x149
	addi     r5, r5, lbl_8049B8B0@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045208C:
	mr       r3, r30
	bl       del__5CNodeFv
	mr       r4, r30
	addi     r3, r31, 0x78
	bl       add__5CNodeFP5CNode

lbl_804520A0:
	lwz      r0, 0x34(r1)
	mr       r3, r29
	lwz      r31, 0x2c(r1)
	lwz      r30, 0x28(r1)
	lwz      r29, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	000020
 */
u32 SceneBase::getBackupSceneType()
{
	// UNUSED FUNCTION
}

/*
 * setDispMember__Q26Screen9SceneBaseFPQ32og6Screen14DispMemberBase
 * --INFO--
 * Address:	804520C0
 * Size:	000130
 */
bool SceneBase::setDispMember(og::Screen::DispMemberBase* disp)
{
	if (!disp->isID(getOwnerID(), getMemberID())) {
		og::Screen::DispMemberBase* submember = disp->getSubMember(getOwnerID(), getMemberID());
		if (submember == nullptr) {
			if (!disp->isID(OWNER_OGA, MEMBER_DUMMY)) {
				return false;
			}
			return setDefaultDispMember();
		}
	}
	memcpy(m_dispMemberBuffer, (void*)disp, disp->getSize());
	return true;
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stmw     r27, 0xc(r1)
	mr       r27, r3
	mr       r28, r4
	li       r29, 0
	lwz      r12, 0(r3)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	mr       r30, r3
	mr       r3, r27
	lwz      r12, 0(r27)
	mr       r31, r4
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	mr       r3, r28
	mr       r6, r31
	mr       r5, r30
	bl       isID__Q32og6Screen14DispMemberBaseFUlUx
	clrlwi.  r0, r3, 0x18
	bne      lbl_80452170
	mr       r3, r27
	lwz      r12, 0(r27)
	lwz      r12, 0x10(r12)
	mtctr    r12
	bctrl
	mr       r31, r3
	mr       r3, r27
	lwz      r12, 0(r27)
	mr       r30, r4
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	mr       r4, r3
	mr       r3, r28
	mr       r6, r30
	mr       r5, r31
	bl       getSubMember__Q32og6Screen14DispMemberBaseFUlUx
	cmplwi   r3, 0
	beq      lbl_8045219C

lbl_80452170:
	mr       r3, r28
	lwz      r12, 0(r28)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	mr       r5, r3
	lwz      r3, 0x21c(r27)
	mr       r4, r28
	bl       memcpy
	li       r29, 1
	b        lbl_804521D8

lbl_8045219C:
	lis      r4, 0x004F4741@ha
	lis      r6, 0x554D4D59@ha
	mr       r3, r28
	li       r5, 0x44
	addi     r4, r4, 0x004F4741@l
	addi     r6, r6, 0x554D4D59@l
	bl       isID__Q32og6Screen14DispMemberBaseFUlUx
	clrlwi.  r0, r3, 0x18
	beq      lbl_804521D8
	mr       r3, r27
	lwz      r12, 0(r27)
	lwz      r12, 0x44(r12)
	mtctr    r12
	bctrl
	mr       r29, r3

lbl_804521D8:
	mr       r3, r29
	lmw      r27, 0xc(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	804521F0
 * Size:	000040
 */
int SceneBase::getFinishState() { return (m_stateID == 4) ? doGetFinishState() : -2; }

/*
 * --INFO--
 * Address:	80452230
 * Size:	000054
 */
Controller* SceneBase::getGamePad() const
{
	P2ASSERTLINE(280, m_screenMgr->m_controller != nullptr);
	return m_screenMgr->m_controller;
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	lwz      r31, 0x108(r3)
	lwz      r0, 0x20(r31)
	cmplwi   r0, 0
	bne      lbl_8045226C
	lis      r3, lbl_8049B8BC@ha
	lis      r5, lbl_8049B8B0@ha
	addi     r3, r3, lbl_8049B8BC@l
	li       r4, 0x118
	addi     r5, r5, lbl_8049B8B0@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045226C:
	lwz      r0, 0x14(r1)
	lwz      r3, 0x20(r31)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	80452284
 * Size:	000044
 */
void SceneBase::setColorBG(u8 r, u8 g, u8 b, u8 a)
{
	JUtility::TColor color(r, g, b, a);
	m_screenMgr->setColorBG(color);
}

/*
 * --INFO--
 * Address:	804522C8
 * Size:	000004
 */
void Mgr::setColorBG(JUtility::TColor&) { }

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void SceneBase::setBGMode(int)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	804522CC
 * Size:	000004
 */
void Mgr::setBGMode(int) { }

} // namespace Screen

/*
 * @generated{Delegate1<Screen::SceneBase, Resource::MgrCommand*>::invoke(Resource::MgrCommand*)}
 * --INFO--
 * Address:	804522D0
 * Size:	000030
 */
// void Delegate1<Screen::SceneBase, Resource::MgrCommand*>::invoke(Resource::MgrCommand*)
// {
/*
.loc_0x0:
  stwu      r1, -0x10(r1)
  mflr      r0
  mr        r5, r3
  stw       r0, 0x14(r1)
  addi      r12, r5, 0x8
  lwz       r3, 0x4(r3)
  bl        -0x3907C4
  nop
  lwz       r0, 0x14(r1)
  mtlr      r0
  addi      r1, r1, 0x10
  blr
*/
// }
