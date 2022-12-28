#ifndef _JSYSTEM_JKR_JKRFILECACHE_H
#define _JSYSTEM_JKR_JKRFILECACHE_H

#include "JSystem/JKR/JKRFileLoader.h"
#include "JSystem/JSupport/JSUList.h"

struct JKRArchive;
struct JKRFileCache : public JKRFileLoader {
	struct CCacheBlock : JSULink<CCacheBlock> {
		CCacheBlock(unsigned long, unsigned long, const void*);

		// JSULink<CCacheBlock> _00; // _00
		int _10;         // _10
		u32 _14;         // _14
		u32 _18;         // _18
		const void* _1C; // _1C
	};

	JKRFileCache(const char*, const char*);

	virtual ~JKRFileCache();                                                                         // _08
	virtual bool becomeCurrent(const char*);                                                         // _10
	virtual void* getResource(const char*);                                                          // _14
	virtual void* getResource(unsigned long, const char*);                                           // _18
	virtual size_t readResource(void* resourceBuffer, u32 bufferSize, const char* path);             // _1C
	virtual size_t readResource(void* resourceBuffer, u32 bufferSize, u32 type, const char* name);   // _20
	virtual void removeResourceAll();                                                                // _24
	virtual bool removeResource(void*);                                                              // _28
	virtual bool detachResource(void*);                                                              // _2C
	virtual long getResSize(const void*) const;                                                      // _30
	virtual u32 countFile(const char*) const;                                                        // _34
	virtual JKRFileFinder* getFirstFile(const char*) const;                                          // _38
	virtual void* getFsResource(const char*);                                                        // _3C (weak)
	virtual void* getNameResource(unsigned long, const char*);                                       // _40 (weak)
	virtual long readFsResource(void* resourceBuffer, u32 bufferSize, const char* path);             // _44 (weak)
	virtual long readNameResource(void* resourceBuffer, u32 bufferSize, u32 type, const char* name); // _48 (weak)

	// +4 bytes vtable padding

	CCacheBlock* findCacheBlock(const void*) const;
	CCacheBlock* findCacheBlock(unsigned long) const;
	bool findFile(char*, const char*) const;
	char* getDvdPathName(const char*) const;
	void convStrLower(char*) const;

	static JKRFileCache* mount(char const*, JKRHeap*, const char*);

	// unused/inlined:
	void* getRelResource(const char*);
	u32 readRelResource(void* p1, u32 p2, const char* p3);

	JKRHeap* _38;                          // _38
	JSUList<CCacheBlock> m_cacheBlockList; // _3C
	char* _48;                             // _48
	char* m_directoryPath;                 // _4C
	char* _50;                             // _50
};

#endif
