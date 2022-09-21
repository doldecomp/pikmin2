#ifndef _J3DTEXTURE_H
#define _J3DTEXTURE_H

#include "types.h"
#include "JSystem/ResTIMG.h"

struct ResTIMG;
struct ResTIMGPair;

struct _UnknownJ3DTextureParent {
	u16 _00;          // _00
	u16 _02;          // _02
	ResTIMGPair* _04; // _04
};

/**
 * @size{0xC}
 */
struct J3DTexture : _UnknownJ3DTextureParent {
	inline J3DTexture(u16 p1, ResTIMG* res)
	{
		_00      = p1;
		_02      = 0;
		_04->_00 = *res;
	}

	virtual ~J3DTexture(); // _00

	inline void setImageOffset(u32 format) { _04->_00.m_imageDataOffset = (int)((format + _04->_00.m_imageDataOffset) - (u32)&_04->_00); }
	inline void setImageOffset2(u32 format) { _04->_20.m_imageDataOffset = (int)((format + _04->_20.m_imageDataOffset) - (u32)&_04->_20); }

	inline void setPaletteOffset(u32 format) { _04->_00.m_paletteOffset = (int)((format + _04->_00.m_paletteOffset) - (u32)&_04->_00); }
	inline void setPaletteOffset2(u32 format) { _04->_20.m_paletteOffset = (int)((format + _04->_20.m_paletteOffset) - (u32)&_04->_20); }
	// _08 VTBL
};

#endif
