#ifndef _J3DTEXTURE_H
#define _J3DTEXTURE_H

#include "types.h"
#include "JSystem/ResTIMG.h"

struct ResTIMG;

struct _UnknownJ3DTextureParent {
	u16 _00;      // _00
	u16 _02;      // _02
	ResTIMG* _04; // _04
};

/**
 * @size{0xC}
 */
struct J3DTexture : _UnknownJ3DTextureParent {
	virtual ~J3DTexture(); // _00

    inline void setImageOffset(u32 format) {
        _04->m_imageDataOffset = (int) ((format + _04->m_imageDataOffset) - (u32) _04);
    }

    inline void setPaletteOffset(u32 format) {
        _04->m_paletteOffset = (int) ((format + _04->m_paletteOffset) - (u32) _04);
    }

	// _08 VTBL
};

#endif
