#include "Dolphin/gx.h"

/**
 * @note Address: 0x800E5908
 * @note Size: 0x80
 */
void __GXSetDirtyState(void)
{
	u32 dirtyFlags = gx->dirtyState;

	if (dirtyFlags & 1) {
		__GXSetSUTexRegs();
	}

	if (dirtyFlags & 2) {
		__GXUpdateBPMask();
	}

	if (dirtyFlags & 4) {
		__GXSetGenMode();
	}

	if (dirtyFlags & 8) {
		__GXSetVCD();
	}

	if (dirtyFlags & 0x10) {
		__GXSetVAT();
	}

	if (dirtyFlags & 0x18) {
		__GXCalculateVLim();
	}

	gx->dirtyState = 0;
}

/**
 * @note Address: 0x800E5988
 * @note Size: 0xD0
 */
void GXBegin(GXPrimitive type, GXVtxFmt fmt, u16 vert_num)
{
	if (gx->dirtyState) {
		__GXSetDirtyState();
	}

	if (GX_CHECK_FLUSH()) {
		__GXSendFlushPrim();
	}

	GX_WRITE_U8(fmt | type);
	GX_WRITE_U16(vert_num);
}

/**
 * @note Address: 0x800E5A58
 * @note Size: 0x88
 */
void __GXSendFlushPrim(void)
{
	u32 i;
	u32 sz = (gx->vNum * gx->vLim);

	GX_WRITE_U8(0x98);
	GX_WRITE_U16(gx->vNum);

	for (i = 0; i < sz; i += 4) {
		GX_WRITE_U32(0);
	}

	gx->bpSentNot = GX_TRUE;
}

/**
 * @note Address: 0x800E5AE0
 * @note Size: 0x40
 */
void GXSetLineWidth(u8 width, GXTexOffset offsets)
{
	GX_BITFIELD_SET(gx->lpSize, 24, 8, width);
	GX_BITFIELD_SET(gx->lpSize, 13, 3, offsets);
	GX_WRITE_U8(0x61);
	GX_WRITE_U32(gx->lpSize);
	gx->bpSentNot = GX_FALSE;
}

/**
 * @note Address: 0x800E5B20
 * @note Size: 0x40
 */
void GXSetPointSize(u8 size, GXTexOffset offsets)
{
	GX_BITFIELD_SET(gx->lpSize, 16, 8, size);
	GX_BITFIELD_SET(gx->lpSize, 10, 3, offsets);
	GX_WRITE_U8(0x61);
	GX_WRITE_U32(gx->lpSize);
	gx->bpSentNot = GX_FALSE;
}

/**
 * @note Address: 0x800E5B60
 * @note Size: 0x48
 */
void GXEnableTexOffsets(GXTexCoordID coord, GXBool line, GXBool point)
{
	GX_BITFIELD_SET(gx->suTs0[coord], 13, 1, line);
	GX_BITFIELD_SET(gx->suTs0[coord], 12, 1, point);
	GX_WRITE_U8(0x61);
	GX_WRITE_U32(gx->suTs0[coord]);
	gx->bpSentNot = GX_FALSE;
}

/**
 * @note Address: 0x800E5BA8
 * @note Size: 0x44
 */
void GXSetCullMode(GXCullMode mode)
{
	switch (mode) {
	case GX_CULL_FRONT:
		mode = GX_CULL_BACK;
		break;
	case GX_CULL_BACK:
		mode = GX_CULL_FRONT;
		break;
	}

	GX_BITFIELD_SET(gx->genMode, 16, 2, mode);
	gx->dirtyState |= 4;
}

/**
 * @note Address: 0x800E5BEC
 * @note Size: 0x34
 */
void GXSetCoPlanar(GXBool enable)
{
	GX_BITFIELD_SET(gx->genMode, 12, 1, enable);
	GX_WRITE_U8(0x61);
	GX_WRITE_U32(0xFE080000);
	GX_WRITE_U8(0x61);
	GX_WRITE_U32(gx->genMode);
}

/**
 * @note Address: 0x800E5C20
 * @note Size: 0x24
 */
void __GXSetGenMode(void)
{
	GX_WRITE_U8(0x61);
	GX_WRITE_U32(gx->genMode);
	gx->bpSentNot = GX_FALSE;
}
