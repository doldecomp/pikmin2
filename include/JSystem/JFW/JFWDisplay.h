#ifndef _JSYSTEM_JFW_JFWDISPLAY_H
#define _JSYSTEM_JFW_JFWDISPLAY_H

#include "JSystem/JUT/TColor.h"
#include "JSystem/JUT/JUTXfb.h"

struct JUTFader;
struct JKRHeap;

struct JFWDisplay {
	// all ctors are unused/inlined
	JFWDisplay(JKRHeap*, JUTXfb::EXfbNumber, bool);
	JFWDisplay(void*, bool);
	JFWDisplay(void*, void*, bool);
	JFWDisplay(void*, void*, void*, bool);

	virtual void beginRender(); // _08
	virtual void endRender();   // _0C
	virtual void endFrame();    // _10
	virtual ~JFWDisplay();      // _14

	static JFWDisplay* createManager(const _GXRenderModeObj*, JKRHeap*, JUTXfb::EXfbNumber, bool);
	static void destroyManager();
	void waitBlanking(int);
	void threadSleep(long long);
	void clearEfb_init();
	void clearEfb(_GXColor);
	void clearEfb(int, int, int, int, _GXColor);
	void calcCombinationRatio();
	static void setForOSResetSystem();

	// Unused/inlined:
	void ctor_subroutine(bool);
	static JFWDisplay* createManager(const _GXRenderModeObj*, void*, bool);
	static JFWDisplay* createManager(const _GXRenderModeObj*, void*, void*, bool);
	static JFWDisplay* createManager(const _GXRenderModeObj*, void*, void*, void*, bool);
	void prepareCopyDisp();
	void drawendXfb_single();
	void exchangeXfb_double();
	void exchangeXfb_triple();
	void copyXfb_triple();
	void preGX();
	void endGX();
	void changeToSingleXfb(int);
	void changeToDoubleXfb();
	void deleteToSingleXfb(int);
	void deleteToSingleXfb(void*);
	void addToDoubleXfb(void*, bool);
	void addToDoubleXfb(JKRHeap*);
	void clearEfb();
	void clearAllXfb();
	void frameToTick(f32);

	// _00 VTBL
	JUTFader* mFader;     // _04
	JUtility::TColor _08; // _08
	u32 _0C;              // _0C
	JUTXfb* mXfb;         // _10
	u16 _14;              // _14
	u32 _18;              // _18

	/// PikDecomp calls this "fpsDivider".
	u16 mSecondsPer60Frames; // _1C

	u32 _20;  // _20
	bool _24; // _24
	u16 _26;  // _26
	f32 _28;  // _28
	int _2C;  // _2C
	int _30;  // _30
	int _34;  // _34
	u16 _38;  // _38
	u8 _3A;   // _3A

	static JFWDisplay* sManager;
};

#endif
