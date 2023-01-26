#ifndef _JSYSTEM_JKR_JKRFILELOADER_H
#define _JSYSTEM_JKR_JKRFILELOADER_H

#include "JSystem/JKR/JKRHeap.h"
#include "JSystem/JSupport/JSUList.h"

struct JKRArchive;
struct JKRFileFinder;
struct JKRFileLoader : public JKRDisposer {
	JKRFileLoader();

	virtual ~JKRFileLoader();                                                                          // _08
	virtual void unmount();                                                                            // _0C
	virtual bool becomeCurrent(const char*)                                                       = 0; // _10
	virtual void* getResource(const char* path)                                                   = 0; // _14
	virtual void* getResource(u32 type, const char* name)                                         = 0; // _18
	virtual size_t readResource(void* resourceBuffer, u32 bufferSize, const char* path)           = 0; // _1C
	virtual size_t readResource(void* resourceBuffer, u32 bufferSize, u32 type, const char* name) = 0; // _20
	virtual void removeResourceAll()                                                              = 0; // _24
	virtual bool removeResource(void*)                                                            = 0; // _28
	virtual bool detachResource(void*)                                                            = 0; // _2C
	virtual long getResSize(const void*) const                                                    = 0; // _30
	virtual u32 countFile(const char*) const                                                      = 0; // _34
	virtual JKRFileFinder* getFirstFile(const char*) const                                        = 0; // _38

	static void* getGlbResource(char const*);
	static void* getGlbResource(char const*, JKRFileLoader*);
	static JKRFileLoader* findVolume(char const**);
	static void fetchVolumeName(char*, long, char const*);

	u32 getVolumeType() { return mMagicWord; }

	static JKRFileLoader* sCurrentVolume;
	static JSUList<JKRFileLoader> sVolumeList;

	// _00     = VTBL
	// _00-_18 = JKRDisposer
	JSULink<JKRFileLoader> _18; // _18
	char* _28;                  // _28
	u32 mMagicWord;             // _2C
	u8 _30;                     // _30
	u32 mMountCount;            // _34
};

#endif
