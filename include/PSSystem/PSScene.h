#ifndef _PSSYSTEM_SCENE_H
#define _PSSYSTEM_SCENE_H

#include "JSystem/JKR/JKRDisposer.h"
#include "JSystem/JAS/JASTrack.h"
#include "SoundID.h"
#include "PSSystem/Seq.h"
#include "PSSystem/WaveScene.h"

namespace PSSystem {

/**
 * @size = 0x24
 */
struct Scene {
	Scene(u8);

	virtual void init();                 // _08 (weak)
	virtual ~Scene();                    // _0C
	virtual void scene1st(TaskChecker*); // _10
	virtual void scene1stLoadSync();     // _14
	virtual void exec();                 // _18
	virtual void startMainSeq();         // _1C
	virtual void stopMainSeq(u32);       // _20
	virtual void stopAllSound(u32);      // _24

	void adaptChildScene(Scene*);
	void adaptTo(Scene**);
	void detach();
	void appendSeq(SeqBase*);
	void getSeqMgr();
	void getChildScene();

	Scene* mChild;           // _04
	WaveLoader* mWaveLoader; // _08
	Scene** _0C;             // _0C
	SeqMgr _10;              // _10
};

/**
 * @size{0x4}
 */
struct SceneMgr {
	virtual void exec(); // _08 (weak)

	void refreshCurEndScene();
	void findSeq(JASTrack*);
	void getPlayingSeq(JASTrack*);
	void deleteScene(Scene*);
	void deleteCurrentScene();

	// inline/unused
	void deleteGlobalScene();

	inline void checkScene() { P2ASSERTLINE(199, mScenes != nullptr); }

	inline Scene* getChildScene()
	{
		P2ASSERTLINE(207, mScenes != nullptr);
		Scene* child = mScenes->mChild;
		JUT_ASSERTLINE(209, child != nullptr, "get sound scene at\ninvalid timming\n");
		return child;
	}

	inline void doFirstLoad()
	{
		checkScene();
		mScenes->mChild->scene1stLoadSync();
	}

	inline void doStartMainSeq()
	{
		checkScene();
		mScenes->mChild->startMainSeq();
	}

	// _00	= VTBL
	Scene* mScenes; // _04
	Scene* mEndScene;
};

inline Scene* checkChildScene(Scene* scene)
{
	P2ASSERTLINE(90, scene->mChild);
	return scene->mChild;
}

extern SceneMgr* spSceneMgr;
} // namespace PSSystem

#endif
