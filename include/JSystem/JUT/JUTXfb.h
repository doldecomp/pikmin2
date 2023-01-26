#ifndef _JSYSTEM_JUT_JUTXFB_H
#define _JSYSTEM_JUT_JUTXFB_H

#include "Dolphin/gx.h"
#include "types.h"

struct _GXRenderModeObj;
struct JKRHeap;

/**
 * @size{0x20}
 */
struct JUTXfb {
	enum EXfbNumber { Unset = 0, SingleBuffer = 1, DoubleBuffer = 2, TripleBuffer = 3 };

	void clearIndex();
	static JUTXfb* createManager(JKRHeap*, EXfbNumber);
	static void destroyManager();
	void initiate(u16, u16, JKRHeap*, EXfbNumber);
	static u32 accumeXfbSize();

	// Unused/inlined:
	JUTXfb(const _GXRenderModeObj*, JKRHeap*, EXfbNumber);
	JUTXfb(const _GXRenderModeObj*, void*, void*, void*, JUTXfb::EXfbNumber);
	~JUTXfb();
	void common_init(int);
	void delXfb(int);
	void exchangeXfbIndex(int, int);
	void addToDoubleXfb(void*, bool);
	void addToDoubleXfb(JKRHeap*);
	static JUTXfb* createManager(const _GXRenderModeObj*, JKRHeap*, EXfbNumber);
	static JUTXfb* createManager(const _GXRenderModeObj*, void*);
	static JUTXfb* createManager(const _GXRenderModeObj*, void*, void*);
	static JUTXfb* createManager(const _GXRenderModeObj*, void*, void*, void*);
	static JUTXfb* createManager(void*);
	static JUTXfb* createManager(void*, void*);
	static JUTXfb* createManager(void*, void*, void*);
	void initiate(void*, void*, void*, EXfbNumber);
	void switchXfb();

	inline static u16 getLineCount(const _GXRenderModeObj* gxObj)
	{
		return GXGetNumXfbLines(GXGetYScaleFactor(gxObj->efbHeight, gxObj->xfbHeight), gxObj->efbHeight);
	}
	/*void *getDrawnXfb() const {
	    return (mDrawnXfbIndex >= 0) ? mBuffer[mDrawnXfbIndex] : nullptr;
	}

	void *getDrawingXfb() const {
	    return (mDrawingXfbIndex >= 0) ? mBuffer[mDrawingXfbIndex] : nullptr;
	}

	void *getDisplayingXfb() const {
	    return (mDisplayingXfbIndex >= 0) ? mBuffer[mDisplayingXfbIndex] : nullptr;
	}*/

	EXfbNumber getBufferNum() const { return mBufferNum; }
	int getDrawingXfbIndex() const { return mDrawingXfbIndex; }
	s16 getDrawnXfbIndex() const { return mDrawnXfbIndex; }
	int getDisplayingXfbIndex() const { return mDisplayingXfbIndex; }
	int getSDrawingFlag() const { return mSDrawingFlag; }
	void setSDrawingFlag(int flag) { mSDrawingFlag = flag; }
	void setDrawnXfbIndex(s16 index) { mDrawnXfbIndex = index; }
	void setDrawingXfbIndex(s16 index) { mDrawingXfbIndex = index; }

	void* getDrawingXfb() const { return (mDrawingXfbIndex >= 0) ? mBuffers[mDrawingXfbIndex] : nullptr; }

	static JUTXfb* getManager() { return sManager; }

	static JUTXfb* sManager;

	u8* mBuffers[3];         // _00
	bool mEnabled[3];        // _0C
	EXfbNumber mBufferNum;   // _10
	s16 mDrawingXfbIndex;    // _14
	s16 mDrawnXfbIndex;      // _16
	s16 mDisplayingXfbIndex; // _18
	int mSDrawingFlag;       // _1C
};

#endif
