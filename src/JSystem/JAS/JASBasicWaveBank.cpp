#include "Dolphin/os.h"
#include "JSystem/JAS/JASCalc.h"
#include "JSystem/JAS/JASMutexLock.h"
#include "JSystem/JAS/JASWave.h"
#include "JSystem/JKR/JKRHeap.h"
#include "types.h"

/*
    Generated from dpostproc

    .section .data, "wa"  # 0x8049E220 - 0x804EFC20
    .global __vt__Q216JASBasicWaveBank10TWaveGroup
    __vt__Q216JASBasicWaveBank10TWaveGroup:
        .4byte 0
        .4byte 0
        .4byte onDispose__10JASWaveArcFv
        .4byte onLoadDone__Q216JASBasicWaveBank10TWaveGroupFv
        .4byte onEraseDone__Q216JASBasicWaveBank10TWaveGroupFv
    .global __vt__13JASWaveHandle
    __vt__13JASWaveHandle:
        .4byte 0
        .4byte 0
        .4byte __dt__13JASWaveHandleFv
        .4byte 0
        .4byte 0
    .global __vt__Q216JASBasicWaveBank11TWaveHandle
    __vt__Q216JASBasicWaveBank11TWaveHandle:
        .4byte 0
        .4byte 0
        .4byte __dt__Q216JASBasicWaveBank11TWaveHandleFv
        .4byte getWaveInfo__Q216JASBasicWaveBank11TWaveHandleCFv
        .4byte getWavePtr__Q216JASBasicWaveBank11TWaveHandleCFv
    .global __vt__16JASBasicWaveBank
    __vt__16JASBasicWaveBank:
        .4byte 0
        .4byte 0
        .4byte __dt__16JASBasicWaveBankFv
        .4byte getWaveHandle__16JASBasicWaveBankCFUl
        .4byte getWaveArc__16JASBasicWaveBankFi
    .global __vt__11JASWaveBank
    __vt__11JASWaveBank:
        .4byte 0
        .4byte 0
        .4byte __dt__11JASWaveBankFv
        .4byte 0
        .4byte 0
        .4byte 0
*/

/*
 * --INFO--
 * Address:	80099E60
 * Size:	000060
 */
JASBasicWaveBank::JASBasicWaveBank()
    : JASWaveBank()
    , m_handles(nullptr)
    , m_tableSize(0)
    , m_groups(nullptr)
    , m_groupCount(0)
{
	OSInitMutex(&m_mutex);
}

/*
 * --INFO--
 * Address:	80099EC0
 * Size:	000048
 * __dt__11JASWaveBankFv
 */
// JASWaveBank::~JASWaveBank() { }

/*
 * --INFO--
 * Address:	80099F08
 * Size:	0000BC
 * __dt__16JASBasicWaveBankFv
 */
JASBasicWaveBank::~JASBasicWaveBank()
{
	delete[] m_handles;
	for (u32 i = 0; i < m_groupCount; i++) {
		delete m_groups[i];
	}
	delete[] m_groups;
}

/*
 * --INFO--
 * Address:	80099FC4
 * Size:	000024
 */
JASBasicWaveBank::TWaveGroup* JASBasicWaveBank::getWaveGroup(int groupIndex)
{
	if (groupIndex >= m_groupCount) {
		return nullptr;
	}
	return m_groups[groupIndex];
}

/*
 * --INFO--
 * Address:	80099FE8
 * Size:	0000E8
 */
void JASBasicWaveBank::setGroupCount(unsigned long count)
{
	for (int i = 0; i < m_groupCount; i++) {
		delete m_groups[i];
	}
	delete[] m_groups;
	m_groupCount = count;
	m_groups     = new (getCurrentHeap(), 0) TWaveGroup*[count];
	for (int i = 0; i < m_groupCount; i++) {
		m_groups[i] = new (getCurrentHeap(), 0) TWaveGroup(this);
	}
}

/*
 * --INFO--
 * Address:	8009A0D0
 * Size:	000064
 */
void JASBasicWaveBank::setWaveTableSize(unsigned long tableSize)
{
	delete[] m_handles;
	m_handles = new (JASWaveBank::getCurrentHeap(), 0) TWaveHandle*[tableSize];
	JASCalc::bzero(m_handles, tableSize * sizeof(TWaveHandle*));
	m_tableSize = tableSize;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A0
 */
void JASBasicWaveBank::incWaveTable(const JASBasicWaveBank::TWaveGroup*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000054
 */
// JASMutexLock::~JASMutexLock()
// {
// 	// UNUSED FUNCTION
// }

/*
 * --INFO--
 * Address:	........
 * Size:	0000E8
 */
void JASBasicWaveBank::decWaveTable(const JASBasicWaveBank::TWaveGroup*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8009A134
 * Size:	000030
 */
JASWaveHandle* JASBasicWaveBank::getWaveHandle(unsigned long handleIndex) const
{
	if (handleIndex >= m_tableSize) {
		return nullptr;
	}
	if (m_handles[handleIndex] == nullptr) {
		return nullptr;
	}
	return m_handles[handleIndex];
}

/*
 * --INFO--
 * Address:	8009A164
 * Size:	000058
 * __ct__Q216JASBasicWaveBank10TWaveGroupFP16JASBasicWaveBank
 */
JASBasicWaveBank::TWaveGroup::TWaveGroup(JASBasicWaveBank* bank)
    : JASWaveArc()
    , m_bank(bank)
    , m_info(nullptr)
    , m_infoCount(0)
{
}

/*
 * --INFO--
 * Address:	........
 * Size:	000090
 * __dt__10JASWaveArcFv
 */
// JASWaveArc::~JASWaveArc()
// {
// 	// UNUSED FUNCTION
// }

/*
 * --INFO--
 * Address:	8009A1BC
 * Size:	0000B4
 * __dt__Q216JASBasicWaveBank10TWaveGroupFv
 */
JASBasicWaveBank::TWaveGroup::~TWaveGroup(void) { delete[] m_info; }

/*
 * --INFO--
 * Address:	8009A270
 * Size:	000060
 * __dt__Q216JASBasicWaveBank9TWaveInfoFv
 */
// JASBasicWaveBank::TWaveInfo::~TWaveInfo(void) { }

/*
 * --INFO--
 * Address:	8009A2D0
 * Size:	0001BC
 */
void JASBasicWaveBank::TWaveGroup::setWaveCount(unsigned long count)
{
	delete[] m_info;
	m_infoCount = count;
	m_info      = new (getCurrentHeap(), 0) TWaveInfo[count];
	for (int i = 0; i < count; i++) {
		m_info[i].m_handle.m_heap     = &m_heap;
		m_info[i].m_handle.m_info._24 = &_48; // TODO: Should _48 be the start of a struct?
	}
}

/*
 * --INFO--
 * Address:	8009A48C
 * Size:	000030
 * __ct__Q216JASBasicWaveBank9TWaveInfoFv
 */
JASBasicWaveBank::TWaveInfo::TWaveInfo(void)
    : m_handle()
    , _34(nullptr)
    , _38(0)
{
}

/*
 * --INFO--
 * Address:	8009A4BC
 * Size:	00005C
 * __dt__Q216JASBasicWaveBank11TWaveHandleFv
 */
// JASBasicWaveBank::TWaveHandle::~TWaveHandle() { }

/*
 * --INFO--
 * Address:	8009A518
 * Size:	000048
 * __dt__13JASWaveHandleFv
 */
// JASWaveHandle::~JASWaveHandle() { }

/*
 * --INFO--
 * Address:	8009A560
 * Size:	000090
 */
void JASBasicWaveBank::TWaveGroup::setWaveInfo(int infoIndex, unsigned long p2, JASWaveInfo const& info)
{
	m_info[infoIndex].m_handle._30        = p2;
	m_info[infoIndex].m_handle.m_info     = info;
	m_info[infoIndex].m_handle.m_info._24 = &_48; // TODO: Should _48 be the start of a struct?
}

/*
 * --INFO--
 * Address:	8009A5F0
 * Size:	0000A0
 */
void JASBasicWaveBank::TWaveGroup::onLoadDone(void)
{
	JASMutexLock lock(&m_bank->m_mutex);
	for (int i = 0; i < m_infoCount; i++) {
		TWaveHandle* bankHandle = m_bank->m_handles[getWaveID(i)];
		TWaveInfo* infosInfo    = &m_info[i];
		infosInfo->_38          = 0;
		infosInfo->_34          = bankHandle;
		if (bankHandle != nullptr) {
			// TODO: ???
		}
	}
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stmw     r27, 0x1c(r1)
	mr       r27, r3
	lwz      r29, 0x5c(r3)
	addi     r3, r29, 4
	stw      r3, 8(r1)
	bl       OSLockMutex
	li       r30, 0
	mr       r28, r30
	mr       r31, r30
	b        lbl_8009A668

lbl_8009A624:
	mr       r3, r27
	mr       r4, r30
	bl       getWaveID__Q216JASBasicWaveBank10TWaveGroupCFi
	lwz      r0, 0x60(r27)
	slwi     r4, r3, 2
	lwz      r3, 0x1c(r29)
	add      r5, r0, r28
	stw      r31, 0x38(r5)
	lwzx     r0, r3, r4
	stw      r0, 0x34(r5)
	lwzx     r6, r3, r4
	cmplwi   r6, 0
	beq      lbl_8009A65C
	stw      r5, 0x38(r6)

lbl_8009A65C:
	stwx     r5, r3, r4
	addi     r28, r28, 0x3c
	addi     r30, r30, 1

lbl_8009A668:
	lwz      r0, 0x64(r27)
	cmplw    r30, r0
	blt      lbl_8009A624
	lwz      r3, 8(r1)
	bl       OSUnlockMutex
	lmw      r27, 0x1c(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	8009A690
 * Size:	0000E8
 */
void JASBasicWaveBank::TWaveGroup::onEraseDone(void)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	stw      r28, 0x10(r1)
	mr       r28, r3
	lwz      r30, 0x5c(r3)
	addi     r3, r30, 4
	stw      r3, 8(r1)
	bl       OSLockMutex
	li       r31, 0
	mr       r29, r31
	b        lbl_8009A744

lbl_8009A6CC:
	mr       r3, r28
	mr       r4, r31
	bl       getWaveID__Q216JASBasicWaveBank10TWaveGroupCFi
	lwz      r4, 0x1c(r30)
	slwi     r3, r3, 2
	lwz      r0, 0x60(r28)
	lwzx     r5, r4, r3
	add      r0, r0, r29
	b        lbl_8009A734

lbl_8009A6F0:
	cmplw    r5, r0
	bne      lbl_8009A730
	lwz      r6, 0x38(r5)
	cmplwi   r6, 0
	bne      lbl_8009A710
	lwz      r0, 0x34(r5)
	stwx     r0, r4, r3
	b        lbl_8009A718

lbl_8009A710:
	lwz      r0, 0x34(r5)
	stw      r0, 0x34(r6)

lbl_8009A718:
	lwz      r3, 0x34(r5)
	cmplwi   r3, 0
	beq      lbl_8009A73C
	lwz      r0, 0x38(r5)
	stw      r0, 0x38(r3)
	b        lbl_8009A73C

lbl_8009A730:
	lwz      r5, 0x34(r5)

lbl_8009A734:
	cmplwi   r5, 0
	bne      lbl_8009A6F0

lbl_8009A73C:
	addi     r29, r29, 0x3c
	addi     r31, r31, 1

lbl_8009A744:
	lwz      r0, 0x64(r28)
	cmplw    r31, r0
	blt      lbl_8009A6CC
	lwz      r3, 8(r1)
	bl       OSUnlockMutex
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
 * Address:	8009A778
 * Size:	000014
 */
u32 JASBasicWaveBank::TWaveGroup::getWaveID(int infoIndex) const { return m_info[infoIndex].m_handle._30; }

/*
 * --INFO--
 * Address:	8009A78C
 * Size:	000008
 */
// const JASWaveInfo* JASBasicWaveBank::TWaveHandle::getWaveInfo() const { return &m_info; }

/*
 * --INFO--
 * Address:	8009A794
 * Size:	000024
 */
void* JASBasicWaveBank::TWaveHandle::getWavePtr() const
{
	if (m_heap->_38 == nullptr) {
		return nullptr;
	}
	return m_heap->_38 + m_info._08;
}

/*
 * --INFO--
 * Address:	8009A7B8
 * Size:	000024
 */
JASWaveArc* JASBasicWaveBank::getWaveArc(int groupIndex)
{
	if (groupIndex >= m_groupCount) {
		return nullptr;
	}
	return m_groups[groupIndex];
}
