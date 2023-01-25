#ifndef _DVDTHREADCOMMAND_H
#define _DVDTHREADCOMMAND_H

#include "JSystem/JSupport/JSUList.h"
#include "Dolphin/os.h"
#include "AppThread.h"
#include "types.h"

struct JKRArchive;
struct JKRHeap;

struct DvdThreadCommand {
	DvdThreadCommand();
	// void loadUseCallBack(IDelegate*);

	~DvdThreadCommand() {};

	u32 _00;                         // _00
	u32 mLoadType;                   // _04
	char* mArcPath;                  // _08
	JKRArchive* mMountedArchive;     // _0C
	s32 _10;                         // _10
	u32 mModeFlags;                  // _14
	s32 mMode;                       // _18
	char mOs;                        // _1C
	u8 _1D[0x16];                    // _1D
	JKRHeap* mHeap;                  // _34
	OSMessageQueue mMsgQueue;        // _38
	void* mMsgBuffer;                // _58
	JSULink<DvdThreadCommand> mLink; // _5C
};

struct DvdThread : public AppThread {

	enum ESyncBlockFlag {

	};

	DvdThread(u32, int, int);

	virtual ~DvdThread() { } // _08 (weak)
	virtual void* run();     // _0C

	void loadArchive(DvdThreadCommand*);
	void loadFile(DvdThreadCommand*);
	void sendCommand(DvdThreadCommand*);
	bool sync(DvdThreadCommand*, ESyncBlockFlag);
	int syncAll(ESyncBlockFlag);

	// _00 		= VTBL
	// _00-_7C 	= AppThread
	JSUList<DvdThread> _7C; // _7C
};

#endif
