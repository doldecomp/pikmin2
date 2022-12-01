#ifndef _KH_CAVERESULT_H
#define _KH_CAVERESULT_H

#include "kh/khUtil.h"
#include "Game/Result.h"
#include "ebi/Save.h"
#include "efx2d/T2DCavecomp.h"
#include "og/Screen/DispMember.h"
#include "og/Screen/callbackNodes.h"
#include "Screen/Bases.h"
#include "P2DScreen.h"

namespace og {
namespace Screen {
struct StickAnimMgr;
} // namespace Screen
} // namespace og

namespace kh {
namespace Screen {
struct DispCaveResult : public og::Screen::DispMemberBase {
	DispCaveResult(Game::Result::TNode*, u32, u32, u32, u32, bool, JKRHeap*, bool);

	virtual u32 getSize();     // _08 (weak)
	virtual u32 getOwnerID();  // _0C (weak)
	virtual u64 getMemberID(); // _10 (weak)

	void init(Game::Result::TNode*, u32, bool);

	// _00     = VTBL
	// _00-_08 = DispMemberBase
	JKRHeap* m_heap;                   // _08
	Game::Result::TNode* m_resultNode; // _0C
	u32 m_treasureNodeCount;           // _10, unknown
	u32 _14;                           // _14, unknown
	u32 m_lostTreasures;                           // _18, unknown
	u32 m_collectedOtakara;               // _1C
	u32 m_maxOtakara;                  // _20
	u32 m_cavePokos;                            // _24, unknown
	u32 m_totalPokos;                          // _28
	u32 m_deadPikis;                           // _2C
	bool m_debtPayed;                          // _30
	bool m_caveComp;                          // _31
	u32 m_isFinished;                           // _34, unknown
};

struct ObjCaveResult : public ::Screen::ObjBase {
	ObjCaveResult();

	virtual ~ObjCaveResult();            // _08 (weak)
	virtual void doCreate(JKRArchive*);  // _4C
	virtual bool doUpdateFadein();       // _50
	virtual void doUpdateFadeinFinish(); // _54
	virtual bool doUpdate();             // _58
	virtual bool doUpdateFadeout();      // _60
	virtual void doDraw(Graphics& gfx);  // _68

	void statusNormal();
	void statusScrollUp();
	void statusScrollDown();
	void statusForceScroll();
	void statusDrumRoll();
	void statusAllMoney();
	void statusDecP();
	void statusLost();
	void statusEffect();
	void updateAnimation();
	void setAlpha(int, u8);
	void pikminSE();

	// _00     = VTBL1
	// _18     = VTBL2
	// _00-_38 = Screen::ObjBase
	ebi::Save::TMgr* m_saveMgr;                           // _38
	Game::Result::TNode* m_resultNode;                    // _3C
	P2DScreen::Mgr_tuning* m_screenMain;                  // _40
	P2DScreen::Mgr_tuning* m_screenDropItem;              // _44
	P2DScreen::Mgr_tuning* m_screenComplete;              // _48
	J2DAnmTransform* m_mainAnim;                          // _4C
	J2DAnmTransform* m_completeAnim;                      // _50
	J2DAnmColor* m_mainAnimColor;                         // _54
	J2DAnmColor* m_completeAnimColor;                     // _58
	J2DAnmTextureSRTKey* m_animTexSRT;                    // _5C
	J2DAnmTevRegKey* m_animTevReg;                        // _60
	f32 m_animTimers[6];                                  // _64
	efx2d::T2DCavecompLoop* m_efxComp;                    // _7C
	og::Screen::StickAnimMgr* m_stickAnim;                // _80
	og::Screen::ScaleMgr* m_scaleMgr;                     // _84
	khUtilFadePane* m_fadePane1;                           // _88
	khUtilFadePane* m_fadePane2;                                  // _8C
	khUtilFadePane* m_fadePane3;                                  // _90
	khUtilFadePane* m_fadePane4;                                  // _94
	og::Screen::CallBack_CounterRV* m_counterCavePokos;                  // _98
	og::Screen::CallBack_CounterRV* m_counterDeadPiki;                  // _9C
	og::Screen::CallBack_CounterRV* _A0;                  // _A0
	og::Screen::CallBack_CounterRV* _A4;                  // _A4
	og::Screen::CallBack_CounterRV* m_counterTreasureCollected;                  // _A8
	og::Screen::CallBack_CounterRV* m_counterTreasureMax;                  // _AC
	og::Screen::CallBack_CounterRV* m_counterTotalPokos;                  // _B0
	u32 m_cavePokos;                                              // _B4, unknown
	u32 m_deadPiki;                                              // _B8
	u32 _BC;                                          // _BC, unknown
	u32 _C0;												// _C0
	u32 m_otakaraCount;                                              // _C4, unknown
	u32 m_maxOtakara;                                          // _C8, unknown
	u32 m_totalPokos;                                              // _CC
	f32 m_scrollPos;                                              // _D0
	f32 m_scrollUpDown;                                              // _D4
	int m_scrollIndex;                                             // _D8
	u32 m_scrollIndexNew;                                              // _DC
	uint _E0;                                             // _E0
	uint _E4;                                             // _E4
	u32 _E8;                                              // _E8, unknown
	u32 _EC;                                              // _EC, unknown
	int m_status;                                              // _F0, state or status?
	int _F4;                                              // _F4
	u32 _F8;                                          // _F8, unknown
	f32 _FC;                                              // _FC
	f32 _100;                                             // _100
	u8 m_flag;                                              // _104
	u8 m_alpha;                                              // _105
	u8 _106;                                              // _106
	u8 _107;                                              // _107

	static struct StaticValues {
		f32 _00; // _00
		f32 _04; // _04
		f32 _08; // _08
		f32 _0C; // _0C
		f32 _10; // _10
		f32 _14; // _14
		f32 _18; // _18
		f32 _1C; // _1C
		f32 _20; // _20
		f32 _24[5]; // _24
		u8  _38;    // _38
		u8  _39;
		u8  _3A;
		u8  _3B;
	} msVal;

};

struct SceneCaveResult : public ::Screen::SceneBase {
	virtual SceneType getSceneType();                       // _08 (weak)
	virtual ScreenOwnerID getOwnerID();                     // _0C (weak)
	virtual ScreenMemberID getMemberID();                   // _10 (weak)
	virtual const char* getResName() const;                 // _1C (weak)
	virtual void doCreateObj(JKRArchive*);                  // _20 (weak)
	virtual void doUserCallBackFunc(Resource::MgrCommand*); // _24

	// _00      = VTBL
	// _00-_220 = Screen::SceneBase
};
} // namespace Screen
} // namespace kh

#endif