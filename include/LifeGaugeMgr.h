#ifndef _LIFEGAUGEMGR_H
#define _LIFEGAUGEMGR_H

#include "Color4.h"
#include "JSystem/JKernel/JKRDisposer.h"
#include "Game/Creature.h"
#include "Vector3.h"
#include "types.h"

struct Graphics;
struct JUTTexture;

struct LifeGauge {
#define LIFEGAUGE_SEGMENTS 32 // (More segments = more detailed hp wheel, also changes slower)
	LifeGauge();

	void draw(f32, f32, f32);
	void drawOneTri(Vector3f*, Color4&);
	void init(u8);
	void update(f32);

	static void initLifeGaugeDraw();

	f32 mTimer;             // _00
	Color4 mLifeGaugeColor; // _04 // might be TColor
	u8 mSegmentCount;       // _08
	u8 mCircleResolution;   // _09
};

/**
 * @size{0x48}
 */
struct LifeGaugeList : public JKRDisposer {
	inline LifeGaugeList(Game::Creature* obj = nullptr)
	    : mParam()
	{
		mGameObject          = obj;
		mNext                = nullptr;
		mPrev                = nullptr;
		mParam.mIsGaugeShown = false;

		mLifeGauge.mTimer            = 0.0f;
		mLifeGauge.mCircleResolution = 32;
		mLifeGauge.mSegmentCount     = 32;
	}
	virtual ~LifeGaugeList() { clearRelations(); } // _08 (weak)

	inline void clearRelations()
	{
		if (mPrev) {
			mPrev->mNext = mNext;
		}
		if (mNext) {
			mNext->mPrev = mPrev;
		}
		mNext = nullptr;
		mPrev = nullptr;
	}

	inline LifeGaugeList* search(Game::Creature* obj)
	{
		for (LifeGaugeList* list = mNext; list; list = list->mNext) {
			if (list->mGameObject != obj) {
				continue;
			}

			return list;
		}

		return nullptr;
	}

	void draw(Graphics&);

	LifeGaugeList* mPrev;        // _18
	LifeGaugeList* mNext;        // _1C
	Game::Creature* mGameObject; // _20
	Game::LifeGaugeParam mParam; // _24
	LifeGauge mLifeGauge;        // _28
};

/**
 * @todo This is so close to being an InfoMgr. Perhaps lessons can be learned from that, or the other way around?
 * @size{0x94}
 */
struct LifeGaugeMgr {
	LifeGaugeMgr();

	LifeGaugeList* createLifeGauge(Game::Creature*);
	void activeLifeGauge(Game::Creature*, f32);
	void inactiveLifeGauge(Game::Creature*);
	void loadResource();
	void update();
	void draw(Graphics&);

	LifeGaugeList mListActive;   // _00
	LifeGaugeList mListInactive; // _04
	JUTTexture* mTexture;        // _90
};

extern LifeGaugeMgr* lifeGaugeMgr;

#endif
