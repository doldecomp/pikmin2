#ifndef _GAME_GENERALENEMYMGR_H
#define _GAME_GENERALENEMYMGR_H

#include "CNode.h"
#include "Game/enemyInfo.h"
#include "Game/EnemyMgrBase.h"
#include "Game/EnemyStone.h"
#include "GenericObjectMgr.h"
#include "JSystem/JKR/JKRHeap.h"
#include "Sys/Sphere.h"

namespace Game {
struct CreatureKillArg;

struct EnemyMgrNode : public CNode, GenericObjectMgr {
	inline EnemyMgrNode()
	    : CNode("�}�l�[�W���m�[�h")
	    , mEnemyID(EnemyTypeID::EnemyID_NULL)
	    , mMgr(nullptr)
	{
	}

	inline EnemyMgrNode(int enemyID, char* name, EnemyMgrBase* mgr)
	    : CNode(name)
	    , mEnemyID((EnemyTypeID::EEnemyTypeID)enemyID)
	    , mMgr(mgr)
	{
	}

	// vtable 1 (CNode, _00, _08-_0C)
	virtual ~EnemyMgrNode() { } // _08 (weak)
	// vtable2 (GenericObjectMgr + self, _18, _18-_80)
	// _18-_34 = thunks
	// _34-_44 = GenericObjectMgr
	// _44 = thunk
	virtual void doAnimation() // _48 (weak)
	{
		mMgr->doAnimation();
	}
	virtual void doEntry() // _4C (weak)
	{
		mMgr->doEntry();
	}
	virtual void doSetView(int a) // _50 (weak)
	{
		mMgr->doSetView(a);
	}
	virtual void doViewCalc() // _54 (weak)
	{
		mMgr->doViewCalc();
	}
	virtual void doSimulation(f32 constraint) // _58 (weak)
	{
		mMgr->doSimulation(constraint);
	}
	virtual void doDirectDraw(Graphics& gfx) // _5C (weak)
	{
		mMgr->doDirectDraw(gfx);
	}
	virtual void doSimpleDraw(Viewport* viewport) // _60 (weak)
	{
		mMgr->doSimpleDraw(viewport);
	}
	virtual void killAll(CreatureKillArg* killArg) // _64 (weak)
	{
		mMgr->killAll(killArg);
	}
	virtual void setupSoundViewerAndBas() // _68 (weak)
	{
		mMgr->setupSoundViewerAndBas();
	}
	virtual void setDebugParm(u32 p1) // _6C (weak)
	{
		mMgr->setDebugParm(p1);
	}
	virtual void resetDebugParm(u32 p1) // _70 (weak)
	{
		mMgr->resetDebugParm(p1);
	}
	virtual void startMovie() // _74 (weak)
	{
		mMgr->startMovie();
	}
	virtual void endMovie() // _78 (weak)
	{
		mMgr->endMovie();
	}
	virtual u32 getMatrixLoadType() { return 1; } // _7C (weak)

	// _00 		= (CNode) VTABLE
	// _04-_18 	= CNode
	// _18 		= (GenericObjectMgr+EnemyMgrNode) VTABLE
	EnemyTypeID::EEnemyTypeID mEnemyID; // _1C
	EnemyMgrBase* mMgr;                 // _20
};

struct EnemyBirthArg;
struct GenObjectEnemy;

struct GeneralEnemyMgr : public GenericObjectMgr, public CNode {
	GeneralEnemyMgr();

	// vtable 1 (GenericObjectMgr, _00, _08-_38)
	virtual void doAnimation();                 // _08
	virtual void doEntry();                     // _0C
	virtual void doSetView(int viewportNumber); // _10
	virtual void doViewCalc();                  // _14
	virtual void doSimulation(f32 rate);        // _18
	virtual void doDirectDraw(Graphics& gfx);   // _1C
	virtual void doSimpleDraw(Viewport*);       // _20
	// vtable 2 (CNode, _04, _40-_4C)
	// _40 = dtor thunk, _44 = getChildCount
	virtual ~GeneralEnemyMgr() { } // _48 (weak)

	void createEnemyMgr(u8, int, int);
	void killAll();
	void setupSoundViewerAndBas();
	J3DModelData* getJ3DModelData(int);
	EnemyBase* birth(int, EnemyBirthArg&);
	char* getEnemyName(int, int);
	int getEnemyID(char*, int);
	IEnemyMgrBase* getIEnemyMgrBase(int);
	void allocateEnemys(u8, int);
	void resetEnemyNum();
	void addEnemyNum(int, u8, GenObjectEnemy*);
	u8 getEnemyNum(int, bool);
	JKRHeap* useHeap();
	EnemyMgrBase* getEnemyMgr(int);
	void setMovieDraw(bool);
	void prepareDayendEnemies();
	void createDayendEnemies(Sys::Sphere&);

	inline void setEnemyIDs()
	{
		for (int i = 0; i < gEnemyInfoNum; i++) {
			mEnemyNumList[i].mEnemyID = (EnemyTypeID::EEnemyTypeID)gEnemyInfo[i].mId;
		}
	}

	inline void setEnemyNums(int val)
	{
		for (int i = 0; i < gEnemyInfoNum; i++) {
			mEnemyNumList[i].mCount = val;
		}
	}

	inline u8 getEnemyCount(u8 num, int enemyID)
	{
		for (int i = num; i < gEnemyInfoNum; i++) {
			if (enemyID == mEnemyNumList[i].mEnemyID) {
				num = mEnemyNumList[i].mCount;
				break;
			}
		}
		return num;
	}

	inline u8 getTotalEnemyCount(u8 num, int enemyID)
	{
		if (mEnemyNumList) {
			int mgrID = getEnemyMgrID(enemyID);

			for (int i = 0; i < gEnemyInfoNum; i++) {
				EnemyTypeID* typeID = &mEnemyNumList[i];
				int id              = ((u8)(enemyID == mgrID) != 0) ? getEnemyMgrID(typeID->mEnemyID) : typeID->mEnemyID;
				if (id == enemyID) {
					num += typeID->mCount;
				}
			}
		}
		return num;
	}

	// _00		= (GenericObjectMgr) VTABLE
	// _04-_1C	= CNode
	u8 _1C;                     // _1C
	EnemyMgrNode mEnemyMgrNode; // _20
	u8 _44[4];                  // _44
	EnemyTypeID* mEnemyNumList; // _48
	JKRHeap* mHeap;             // _4C
	u32 mHeapSize;              // _50
	BitFlag<u32> mFlags;        // _54
	EnemyStone::Mgr mStoneMgr;  // _58

	static int mTotalCount;
	static int mCullCount;
};

extern GeneralEnemyMgr* generalEnemyMgr;

}; // namespace Game

template <typename T>
struct GeneralMgrIterator {
	GeneralMgrIterator(CNode* node)
	{
		mNode      = node;
		mCondition = nullptr;
		mContainer = nullptr;
		mIndex     = nullptr;
	}

	void next();

	void first();

	void setFirst();

	inline T* getObject() { return static_cast<T*>(mContainer->getObject(mIndex)); }

	Container<T>* mContainer; // _00
	void* mIndex;             // _04
	CNode* mNode;             // _08
	Condition<T>* mCondition; // _0C
};

#endif
