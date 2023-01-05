#include "JSystem/JAS/JASHeap.h"
#include "JSystem/JAS/JASWave.h"
#include "JSystem/JKR/JKRHeap.h"
#include "types.h"

/*
    Generated from dpostproc

    .section .data, "wa"  # 0x8049E220 - 0x804EFC20
    .global __vt__Q217JASSimpleWaveBank11TWaveHandle
    __vt__Q217JASSimpleWaveBank11TWaveHandle:
        .4byte 0
        .4byte 0
        .4byte __dt__Q217JASSimpleWaveBank11TWaveHandleFv
        .4byte getWaveInfo__Q217JASSimpleWaveBank11TWaveHandleCFv
        .4byte getWavePtr__Q217JASSimpleWaveBank11TWaveHandleCFv
    .global __vt__17JASSimpleWaveBank
    __vt__17JASSimpleWaveBank:
        .4byte 0
        .4byte 0
        .4byte __dt__17JASSimpleWaveBankFv
        .4byte getWaveHandle__17JASSimpleWaveBankCFUl
        .4byte getWaveArc__17JASSimpleWaveBankFi
        .4byte 0
        .4byte 0
        .4byte onDispose__10JASWaveArcFv
        .4byte onLoadDone__10JASWaveArcFv
        .4byte onEraseDone__10JASWaveArcFv
        .4byte 0
*/

/*
 * --INFO--
 * Address:	8009B6C4
 * Size:	000060
 */
JASSimpleWaveBank::JASSimpleWaveBank()
    : JASWaveBank()
    , JASWaveArc()
    , m_handles(nullptr)
    , m_handleCount(0)
{
}

/*
 * --INFO--
 * Address:	8009B724
 * Size:	0000D4
 * __dt__17JASSimpleWaveBankFv
 */
JASSimpleWaveBank::~JASSimpleWaveBank() { delete[] m_handles; }

/*
 * --INFO--
 * Address:	8009B7F8
 * Size:	00005C
 * __dt__Q217JASSimpleWaveBank11TWaveHandleFv
 */
JASSimpleWaveBank::TWaveHandle::~TWaveHandle(void) { }

/*
 * --INFO--
 * Address:	8009B854
 * Size:	000084
 */
void JASSimpleWaveBank::setWaveTableSize(unsigned long tableSize)
{
	delete[] m_handles;
	m_handles     = new (getCurrentHeap(), 0) TWaveHandle[tableSize];
	m_handleCount = tableSize;
}

/*
 * --INFO--
 * Address:	8009B8D8
 * Size:	000024
 * __ct__Q217JASSimpleWaveBank11TWaveHandleFv
 */
JASSimpleWaveBank::TWaveHandle::TWaveHandle() { m_heap = nullptr; }

/*
 * --INFO--
 * Address:	8009B8FC
 * Size:	000024
 */
JASWaveHandle* JASSimpleWaveBank::getWaveHandle(unsigned long handleIndex) const
{
	if (handleIndex >= m_handleCount) {
		return nullptr;
	}
	return m_handles + handleIndex;
}

/*
 * --INFO--
 * Address:	8009B920
 * Size:	000094
 */
void JASSimpleWaveBank::setWaveInfo(unsigned long handleIndex, const JASWaveInfo& info)
{
	m_handles[handleIndex].m_info     = info;
	m_handles[handleIndex].m_info._24 = &_48;
	m_handles[handleIndex].m_heap     = &m_heap;
}

/*
 * --INFO--
 * Address:	8009B9B4
 * Size:	000020
 */
JASWaveArc* JASSimpleWaveBank::getWaveArc(int arcIndex)
{
	if (arcIndex != 0) {
		return nullptr;
	}
	return this;
}

/*
 * --INFO--
 * Address:	8009B9D4
 * Size:	000008
 */
const JASWaveInfo* JASSimpleWaveBank::TWaveHandle::getWaveInfo() const { return &m_info; }

/*
 * --INFO--
 * Address:	8009B9DC
 * Size:	000024
 */
void* JASSimpleWaveBank::TWaveHandle::getWavePtr() const
{
	if (m_heap->_38 == nullptr) {
		return nullptr;
	}
	return m_heap->_38 + m_info._08;
}

/*
 * --INFO--
 * Address:	8009BA00
 * Size:	000004
 */
void JASWaveArc::onLoadDone() { }

/*
 * --INFO--
 * Address:	8009BA04
 * Size:	000004
 */
void JASWaveArc::onEraseDone() { }
