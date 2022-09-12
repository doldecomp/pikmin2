#ifndef _GAME_VSGAMESECTION_H
#define _GAME_VSGAMESECTION_H

#include "types.h"
#include "Game/BaseGameSection.h"
#include "Vector3.h"

namespace Game {
struct PikiContainer;
struct MovieConfig;

namespace ItemHole {
struct Item;
} // namespace ItemHole

namespace ItemBigFountain {
struct Item;
} // namespace ItemBigFountain

struct VsGameSection : public BaseGameSection {
	struct DropCardArg {
	};

	VsGameSection(JKRHeap*, bool);

	virtual ~VsGameSection();											   // _08
	virtual bool doUpdate();										       // _3C
	virtual void doDraw(Graphics&);										   // _40
	virtual void sendMessage(GameMessage&);                                // _50
	virtual void pre2dDraw(Graphics&);                                     // _54
	virtual void getCurrFloor();                                           // _58
	virtual void addChallengeScore(int);                                   // _60
	virtual void startMainBgm();                                           // _64
	virtual void section_fadeout();                                        // _68
	virtual void goNextFloor(ItemHole::Item*);                             // _6C
	virtual void challengeDisablePelplant();                               // _80 (weak)
	virtual void getCaveFilename();                                        // _84 (weak)
	virtual void getEditorFilename();                                      // _88 (weak)
	virtual void getVsEditNumber();                                        // _8C (weak)
	virtual void onMovieStart(MovieConfig*, u32, u32); 					   // _B0
	virtual void onMovieDone(MovieConfig*, u32, u32);  					   // _B4
	virtual void gmOrimaDown(int);                                         // _D0
	virtual void gmPikminZero();                                           // _D4
	virtual void openCaveMoreMenu(ItemHole::Item*, Controller*);           // _DC
	virtual void openKanketuMenu(ItemBigFountain::Item*, Controller*);     // _E0
	virtual void onInit();                                                 // _F0
	virtual void onSetupFloatMemory();                                     // _120
	virtual void postSetupFloatMemory();                                   // _124
	virtual void onSetSoundScene();                                        // _128
	virtual void onClearHeap();                                            // _130
	virtual void player2enabled();                                         // _134 (weak)

	void calcVsScores();
	void clearCaveMenus();
	void clearGetCherryCount();
	void clearGetDopeCount();
	void createFallPikmins(PikiContainer&, int);
	void createRedBlueBedamas(Vector3f&);
	void createVsPikmins();
	void createYellowBedamas(int);
	void dropCard(DropCardArg&);
	u32 getGetCherryCount(int);
	void getGetDopeCount(int, int);
	void initCardGeneration();
	void initCardPellets();
	void initPlayData();
	void loadChallengeStageList();
	void loadVsStageList();
	void updateCardGeneration();
	void updateCaveMenus();
	void useCard();
};
} // namespace Game

#endif
