#include "Dolphin/mtx.h"
#include "Sys/GridDivider.h"
#include "Sys/TriangleTable.h"
#include "Sys/TriDivider.h"
#include "types.h"

/*
    Generated from dpostproc

    .section .data, "wa"  # 0x8049E220 - 0x804EFC20
    .global __vt__Q23Sys10TriDivider
    __vt__Q23Sys10TriDivider:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23Sys10TriDividerFv
        .4byte getChildCount__5CNodeFv
        .4byte 0
        .4byte 0
        .4byte 0
        .4byte 0
        .4byte createTriangles__Q23Sys10TriDividerFRQ23Sys17CreateTriangleArg
        .4byte 0
        .4byte clone__Q23Sys10TriDividerFR7Matrixf
        .4byte
   do_clone__Q23Sys10TriDividerFR7MatrixfPQ23Sys11VertexTablePQ23Sys13TriangleTable

    .section .sdata2, "a"     # 0x80516360 - 0x80520E40
    .global lbl_805203F8
    lbl_805203F8:
        .float 32768.0
    .global lbl_805203FC
    lbl_805203FC:
        .float -32768.0
*/

namespace Sys {

/*
 * --INFO--
 * Address:	80421ACC
 * Size:	000120
 */
TriDivider* TriDivider::clone(Matrixf& p1)
{
	VertexTable* vtxTable = new VertexTable();
	vtxTable->cloneFrom(p1, m_vertexTable);
	TriangleTable* triTable = new TriangleTable();
	triTable->cloneFrom(p1, m_triangleTable, vtxTable);
	return do_clone(&p1, vtxTable, triTable);
}

/*
 * --INFO--
 * Address:	80421BEC
 * Size:	000160
 */
void VertexTable::cloneFrom(Matrixf& p1, Sys::VertexTable* other)
{
	alloc(other->m_limit);
	m_count = other->m_count;
	for (int i = 0; i < m_limit; i++) {
		Vector3f v1;
		PSMTXMultVec(p1.m_matrix.mtxView, (Vec*)&other->m_objects[i], (Vec*)&v1);
		m_objects[i] = v1;
	}
	_28.m_min = 32768.0f;
	_28.m_max = -32768.0f;
	for (int i = 0; i < m_limit; i++) {
		_28.include(m_objects[i]);
	}
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stmw     r27, 0x1c(r1)
	mr       r28, r4
	mr       r29, r5
	mr       r27, r3
	lwz      r12, 0(r3)
	lwz      r4, 0x20(r5)
	lwz      r12, 0x3c(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x1c(r29)
	li       r30, 0
	li       r31, 0
	stw      r0, 0x1c(r27)
	b        lbl_80421C6C

lbl_80421C30:
	lwz      r0, 0x24(r29)
	mr       r3, r28
	addi     r5, r1, 8
	add      r4, r0, r31
	bl       PSMTXMultVec
	lwz      r0, 0x24(r27)
	addi     r30, r30, 1
	lfs      f1, 0xc(r1)
	add      r3, r0, r31
	lfs      f2, 0x10(r1)
	lfs      f0, 8(r1)
	addi     r31, r31, 0xc
	stfs     f0, 0(r3)
	stfs     f1, 4(r3)
	stfs     f2, 8(r3)

lbl_80421C6C:
	lwz      r0, 0x20(r27)
	cmpw     r30, r0
	blt      lbl_80421C30
	lfs      f1, lbl_805203F8@sda21(r2)
	li       r3, 0
	lfs      f0, lbl_805203FC@sda21(r2)
	mr       r5, r3
	stfs     f1, 0x28(r27)
	stfs     f1, 0x2c(r27)
	stfs     f1, 0x30(r27)
	stfs     f0, 0x34(r27)
	stfs     f0, 0x38(r27)
	stfs     f0, 0x3c(r27)
	b        lbl_80421D2C

lbl_80421CA4:
	lwz      r0, 0x24(r27)
	lfs      f0, 0x28(r27)
	add      r4, r0, r5
	lfs      f1, 0(r4)
	fcmpo    cr0, f1, f0
	bge      lbl_80421CC0
	stfs     f1, 0x28(r27)

lbl_80421CC0:
	lfs      f1, 4(r4)
	lfs      f0, 0x2c(r27)
	fcmpo    cr0, f1, f0
	bge      lbl_80421CD4
	stfs     f1, 0x2c(r27)

lbl_80421CD4:
	lfs      f1, 8(r4)
	lfs      f0, 0x30(r27)
	fcmpo    cr0, f1, f0
	bge      lbl_80421CE8
	stfs     f1, 0x30(r27)

lbl_80421CE8:
	lfs      f1, 0(r4)
	lfs      f0, 0x34(r27)
	fcmpo    cr0, f1, f0
	ble      lbl_80421CFC
	stfs     f1, 0x34(r27)

lbl_80421CFC:
	lfs      f1, 4(r4)
	lfs      f0, 0x38(r27)
	fcmpo    cr0, f1, f0
	ble      lbl_80421D10
	stfs     f1, 0x38(r27)

lbl_80421D10:
	lfs      f1, 8(r4)
	lfs      f0, 0x3c(r27)
	fcmpo    cr0, f1, f0
	ble      lbl_80421D24
	stfs     f1, 0x3c(r27)

lbl_80421D24:
	addi     r5, r5, 0xc
	addi     r3, r3, 1

lbl_80421D2C:
	lwz      r0, 0x1c(r27)
	cmpw     r3, r0
	blt      lbl_80421CA4
	lmw      r27, 0x1c(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * cloneFrom__Q23Sys13TriangleTableFR7MatrixfPQ23Sys13TriangleTablePQ23Sys11VertexTable
 * --INFO--
 * Address:	80421D4C
 * Size:	0000B4
 */
void TriangleTable::cloneFrom(Matrixf& p1, Sys::TriangleTable* other, Sys::VertexTable* vertices)
{
	alloc(other->m_limit);
	m_count = other->m_count;
	for (int i = 0; i < m_limit; i++) {
		m_objects[i].m_vertices = other->m_objects[i].m_vertices;
		m_objects[i].m_code     = other->m_objects[i].m_code;
		m_objects[i].makePlanes(*vertices);
		m_objects[i].createSphere(*vertices);
	}
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stmw     r26, 8(r1)
	mr       r27, r5
	mr       r26, r3
	mr       r28, r6
	lwz      r12, 0(r3)
	lwz      r4, 0x20(r5)
	lwz      r12, 0x3c(r12)
	mtctr    r12
	bctrl
	lwz      r0, 0x1c(r27)
	li       r29, 0
	li       r30, 0
	stw      r0, 0x1c(r26)
	b        lbl_80421DE0

lbl_80421D90:
	lwz      r0, 0x24(r27)
	mr       r4, r28
	lwz      r3, 0x24(r26)
	add      r5, r0, r30
	lwz      r0, 0(r5)
	add      r31, r3, r30
	mr       r3, r31
	stw      r0, 0(r31)
	lwz      r0, 4(r5)
	stw      r0, 4(r31)
	lwz      r0, 8(r5)
	stw      r0, 8(r31)
	lbz      r0, 0x5c(r5)
	stb      r0, 0x5c(r31)
	bl       makePlanes__Q23Sys8TriangleFRQ23Sys11VertexTable
	mr       r3, r31
	mr       r4, r28
	bl       createSphere__Q23Sys8TriangleFRQ23Sys11VertexTable
	addi     r30, r30, 0x60
	addi     r29, r29, 1

lbl_80421DE0:
	lwz      r0, 0x20(r26)
	cmpw     r29, r0
	blt      lbl_80421D90
	lmw      r26, 8(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80421E00
 * Size:	0000C4
 */
TriDivider* GridDivider::do_clone(Matrixf& p1, Sys::VertexTable* vertices, Sys::TriangleTable* triangles)
{
	GridDivider* copy = new GridDivider();
	copy->create(vertices->_28, _20, _24, vertices, triangles);
	return copy;
}
} // namespace Sys
