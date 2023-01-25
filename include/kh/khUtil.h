#ifndef _KH_KHUTIL_H
#define _KH_KHUTIL_H

#include "P2DScreen.h"
#include "efx2d/T2DCountKira.h"
#include "og/Screen/callbackNodes.h"

struct Graphics;
struct J2DAnmBase;
struct J2DPane;
struct J2DScreen;
struct ResTIMG;

namespace kh {
namespace Screen {
struct WorldMap;
u64 getSerialTagName(u64, int);
void setTex(J2DScreen*, u64, const ResTIMG*);
void setTex(J2DScreen*, u64, const char*);
void setMatAnm(J2DPane*, J2DAnmBase*);
void setInfAlpha(J2DPane*);
f32 getPaneCenterX(J2DPane*);
f32 getPaneCenterY(J2DPane*);

struct khUtilFadePane : public P2DScreen::CallBackNode {
	struct khPaneNode {
		inline khPaneNode(J2DPane* pane)
		    : mPane(pane)
		    , mNext(nullptr)
		{
		}

		virtual ~khPaneNode() { } // _08 (weak)

		// _00 = VTBL
		J2DPane* mPane;    // _04
		khPaneNode* mNext; // _08
	};

	khUtilFadePane(u8);

	virtual ~khUtilFadePane() { }     // _08 (weak)
	virtual void update();            // _10
	virtual void fadein_finish() { }  // _1C (weak)
	virtual void fadeout_finish() { } // _20 (weak)

	bool add(J2DPane*);
	void fadein();
	void fadeout();
	void set_init_alpha(u8);

	static khUtilFadePane* create(P2DScreen::Mgr*, u64, u8);

	// _00     = VTBL
	// _00-_1C = P2DScreen::CallBackNode
	khPaneNode mPaneNode; // _1C
	int mState;           // _28
	u8 mCurrentAlpha;     // _2C
	u8 mChangeAlpha;      // _2D
};

struct khUtilFadePaneWM : public khUtilFadePane {
	virtual ~khUtilFadePaneWM() { } // _08 (weak)
	virtual void fadeout_finish();  // _20

	// _00     = VTBL
	// _00-_30 = khUtilFadePane
	kh::Screen::WorldMap* mMapObj; // _34
	bool mFinish;
};

struct khUtilColorAnm : public P2DScreen::CallBackNode {
	khUtilColorAnm(P2DScreen::Mgr*, u64, int, int);

	virtual ~khUtilColorAnm() { } // _08 (weak)
	virtual void update();        // _10 (weak)
	virtual void do_update() { }  // _1C (weak)

	// _00     = VTBL
	// _00-_1C = P2DScreen::Node
	JUtility::TColor* mColorList; // _1C
	JUtility::TColor mColor1;     // _20
	JUtility::TColor mColor2;     // _24
	int mPaneNum;                 // _28
	int mMaxFrame;                // _2C
	int mCounter;                 // _30
	u8 mUpdateMode;               // _34
};

struct khUtilColorAnmWM : public khUtilColorAnm {
	virtual ~khUtilColorAnmWM() { } // _08 (weak)
	virtual void do_update();       // _14

	// _00     = VTBL
	// _00-_38 = khUtilColorAnm
	J2DPane* mPaneList[4];                     // _38
	efx2d::T2DCountKira* mEfx[4];              // _48
	og::Screen::CallBack_CounterRV* mCounter1; //_4C
	og::Screen::CallBack_CounterRV* mCounter2; // _50
};

} // namespace Screen
} // namespace kh

#endif
