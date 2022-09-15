#ifndef _JKRARCHIVE_H
#define _JKRARCHIVE_H

/*
    __vt__10JKRArchive:
    .4byte 0
    .4byte 0
    .4byte __dt__10JKRArchiveFv
    .4byte unmount__13JKRFileLoaderFv
    .4byte becomeCurrent__10JKRArchiveFPCc
    .4byte getResource__10JKRArchiveFPCc
    .4byte getResource__10JKRArchiveFUlPCc
    .4byte readResource__10JKRArchiveFPvUlPCc
    .4byte readResource__10JKRArchiveFPvUlUlPCc
    .4byte removeResourceAll__10JKRArchiveFv
    .4byte removeResource__10JKRArchiveFPv
    .4byte detachResource__10JKRArchiveFPv
    .4byte getResSize__10JKRArchiveCFPCv
    .4byte countFile__10JKRArchiveCFPCc
    .4byte getFirstFile__10JKRArchiveCFPCc
    .4byte getExpandedResSize__10JKRArchiveCFPCv
    .4byte 0
    .4byte 0
    .4byte setExpandSize__10JKRArchiveFPQ210JKRArchive12SDIFileEntryUl
    .4byte getExpandSize__10JKRArchiveCFPQ210JKRArchive12SDIFileEntry
*/

struct JKRFileLoader {
	virtual ~JKRFileLoader(); // _08
	virtual void unmount();   // _0C
};

struct JKRArchive : public JKRFileLoader {
	virtual ~JKRArchive();                                                       // _08
	virtual void becomeCurrent(const char*);                                     // _10
	virtual void getResource(const char*);                                       // _14
	virtual void getResource(unsigned long, const char*);                        // _18
	virtual void readResource(void*, unsigned long, const char*);                // _1C
	virtual void readResource(void*, unsigned long, unsigned long, const char*); // _20
	virtual void removeResourceAll();                                            // _24
	virtual void removeResource(void*);                                          // _28
	virtual void detachResource(void*);                                          // _2C
	virtual void getResSize(const void*) const;                                  // _30
	virtual void countFile(const char*) const;                                   // _34
	virtual void getFirstFile(const char*) const;                                // _38
	virtual void getExpandedResSize(const void*) const;                          // _3C (weak)
	virtual void _40() = 0;                                                      // _40
	virtual void _44() = 0;                                                      // _44
	virtual void setExpandSize(SDIFileEntry*, unsigned long);                    // _48
	virtual void getExpandSize(SDIFileEntry*) const;                             // _4C

	JKRArchive(long, JKRArchive::EMountMode);
	void isSameName(JKRArchive::CArcName&, unsigned long, unsigned short) const;
	void findDirectory(const char*, unsigned long) const;
	void findTypeResource(unsigned long, const char*) const;
	void findFsResource(const char*, unsigned long) const;
	void findIdxResource(unsigned long) const;
	void findNameResource(const char*) const;
	void findPtrResource(const void*) const;
	void findIdResource(unsigned short) const;
	void mount(const char*, JKRArchive::EMountMode, JKRHeap*, JKRArchive::EMountDirection);
	void mount(void*, JKRHeap*, JKRArchive::EMountDirection);
	void mount(long, JKRArchive::EMountMode, JKRHeap*, JKRArchive::EMountDirection);
	void getDirEntry(JKRArchive::SDirEntry*, unsigned long) const;
	void getGlbResource(unsigned long, const char*, JKRArchive*);
	void getIdxResource(unsigned long);
	void readResource(void*, unsigned long, unsigned short);
};

#endif
