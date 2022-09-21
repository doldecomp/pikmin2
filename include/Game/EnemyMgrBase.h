#ifndef _GAME_ENEMYMGRBASE_H
#define _GAME_ENEMYMGRBASE_H

#include "Container.h"
#include "Game/EnemyPelletInfo.h"
#include "Game/EnemyStone.h"
#include "Game/pelletMgr.h"
#include "Game/enemyInfo.h"
#include "Game/gameGenerator.h"
#include "GenericObjectMgr.h"
#include "SysShape/AnimMgr.h"
#include "Game/EnemyBase.h"
#include "JSystem/J3D/J3DModelLoader.h"
#include "Vector3.h"

struct CollPartFactory;
struct J3DModelData;
struct JKRArchive;

namespace SysShape {
struct Model;
} // namespace SysShape

namespace Game {
struct EnemyGeneratorBase;
struct EnemyParmsBase;

/**
 * @size{0x49}
 */
struct EnemyBirthArg {
	EnemyBirthArg();

	Vector3f m_position;                          // _00
	float m_faceDir;                              // _0C
	u8 m_tekiBirthType;                           // _10
	EnemyGeneratorBase* m_generator;              // _14
	PelletMgr::OtakaraItemCode m_otakaraItemCode; // _18
	EnemyPelletInfo m_pelletInfo;                 // _1C
	EnemyTypeID::EEnemyTypeID m_typeID;           // _28
	float _2C;                                    // _2C
	u8 _30;                                       // _30
};

/**
 * @size{0x1C}
 */
struct IEnemyMgrBase : public GenericObjectMgr, public GenericContainer {
	// vtable 1 (GenericObjectMgr, _00, _08-_38)
	// vtable 2 (GenericContainer + self, _00, _40-_5C)
	/**
	 * @reifiedAddress{8010A960}
	 * @reifiedFile{plugProjectYamashitaU/pelplant.cpp}
	 */
	virtual ~IEnemyMgrBase() { }                          // _58 (weak)
	virtual void* getObject(void*)                   = 0; // _5C
	virtual void* getNext(void*)                     = 0; // _60
	virtual void* getStart()                         = 0; // _64
	virtual void* getEnd()                           = 0; // _68
	virtual void alloc()                             = 0; // _6C
	virtual EnemyBase* birth(EnemyBirthArg&)         = 0; // _70
	virtual J3DModelData* getJ3DModelData() const    = 0; // _74
	virtual EnemyGeneratorBase* getGenerator() const = 0; // _78
	virtual void killAll(CreatureKillArg*)           = 0; // _7C
	virtual void setupSoundViewerAndBas()            = 0; // _80
	virtual void setDebugParm(u32)                   = 0; // _84
	virtual void resetDebugParm(u32)                 = 0; // _88
	virtual int getMaxObjects() const                = 0; // _8C
	virtual void startMovie()                        = 0; // _90
	virtual void endMovie()                          = 0; // _94

	// _00		= VTABLE
	// _04-_1C	= GenericContainer
};

/**
 * @size{0x44}
 */
struct EnemyMgrBase : public IEnemyMgrBase {
	EnemyMgrBase(int, u8);

	// vtable 1 (GenericObjectMgr, _00, _08-_38)
	virtual void doAnimation();           // _08
	virtual void doEntry();               // _0C
	virtual void doSetView(int);          // _10
	virtual void doViewCalc();            // _14
	virtual void doSimulation(float);     // _18
	virtual void doDirectDraw(Graphics&); // _1C
	// vtable 2 (GenericContainer + IEnemyMgrBase + self, _00, _40-_E0)
	// GenericContainer thunks _40-_58
	virtual ~EnemyMgrBase() { } // _58 (weak)
	/**
	 * @reifiedAddress{8010A820}
	 * @reifiedFile{plugProjectYamashitaU/pelplant.cpp}
	 */
	virtual void* getObject(void* index) { return get(index); }; // _5C (weak)
	virtual void* getNext(void* index);                          // _60
	/**
	 * @reifiedAddress{8010A7F0}
	 * @reifiedFile{plugProjectYamashitaU/pelplant.cpp}
	 */
	virtual void* getStart() { return getNext((void*)-1); } // _64 (weak)
	/**
	 * @reifiedAddress{8010A7E8}
	 * @reifiedFile{plugProjectYamashitaU/pelplant.cpp}
	 */
	virtual void* getEnd() { return (void*)m_objLimit; } // _68 (weak)
	virtual void alloc();                                // _6C
	virtual EnemyBase* birth(EnemyBirthArg&);            // _70
	/**
	 * @reifiedAddress{8010A7AC}
	 * @reifiedFile{plugProjectYamashitaU/pelplant.cpp}
	 */
	virtual J3DModelData* getJ3DModelData() const // _74 (weak)
	{
		return m_modelData;
	}
	/**
	 * @reifiedAddress{8010A7B4}
	 * @reifiedFile{plugProjectYamashitaU/pelplant.cpp}
	 */
	virtual EnemyGeneratorBase* getGenerator() const // _78 (weak)
	{
		return m_generator;
	}
	virtual void killAll(CreatureKillArg*); // _7C
	virtual void setupSoundViewerAndBas();  // _80
	virtual void setDebugParm(u32);         // _84
	virtual void resetDebugParm(u32);       // _88
	/**
	 * @reifiedAddress{8010A7BC}
	 * @reifiedFile{plugProjectYamashitaU/pelplant.cpp}
	 */
	virtual int getMaxObjects() const // _8C
	{
		return m_objLimit;
	}
	virtual void startMovie(); // _90
	virtual void endMovie();   // _94
	/**
	 * @reifiedAddress{8010A780}
	 * @reifiedFile{plugProjectYamashitaU/pelplant.cpp}
	 */
	virtual EnemyBase* get(void* index) // _98 (weak)
	{
		return getEnemy((int)index);
	}
	/**
	 * @reifiedAddress{801074BC}
	 * @reifiedFile{plugProjectYamashitaU/enemyBase.cpp}
	 */
	virtual bool isAlwaysMovieActor() // _9C (weak)
	{
		return false;
	}
	virtual void createObj(int)      = 0;              // _A0
	virtual EnemyBase* getEnemy(int) = 0;              // _A4
	virtual void doAlloc() { }                         // _A8 (weak)
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID() // _AC (weak)
	{
		return (EnemyTypeID::EEnemyTypeID)-1;
	}
	virtual SysShape::Model* createModel();           // _B0
	virtual void initParms();                         // _B4
	virtual void loadResource();                      // _B8
	virtual void initObjects();                       // _BC
	virtual void initStoneSetting();                  // _C0
	virtual J3DModelData* loadModelData(JKRArchive*); // _C4
	virtual void loadModelData();                     // _C8
	virtual void loadAnimData();                      // _CC
	virtual void loadTexData();                       // _D0
	virtual J3DModelData* doLoadBmd(void*);           // _D4
	virtual J3DModelData* doLoadBdl(void*);           // _D8
	virtual void initGenerator();                     // _DC

	void init(EnemyParmsBase*);
	bool isValidEnemyTypeID();
	void loadStoneSetting(const char*);
	bool setupParms(const char*);
	void doAnimationAlwaysMovieActor();
	void doEntryAlwaysMovieActor();
	void doSimulationAlwaysMovieActor(float);
	void doDirectDrawAlwaysMovieActor(Graphics&);
	void kill(EnemyBase*);

	inline EnemyBase* getEnemyByID(EnemyTypeID::EEnemyTypeID id)
	{
		EnemyBase* enemy = nullptr;
		for (int i = 0; i < m_objLimit; i++) {
			EnemyBase* currEnemy = getEnemy(i);
			if (id == currEnemy->getEnemyTypeID() && !(currEnemy->m_events.m_flags[0].typeView & 0x10000000)) {
				enemy = currEnemy;
				break;
			}
		}
		return enemy;
	}

	// _00		= VTABLE
	// _04-_1C	= GenericContainer
	J3DModelData* m_modelData;          // _1C
	SysShape::AnimMgr* m_animMgr;       // _20
	u8 m_modelType;                     // _24
	CollPartFactory* m_collPartFactory; // _28
	int m_objLimit;                     // _2C
	int m_objCount;                     // _30
	EnemyParmsBase* m_parms;            // _34
	EnemyGeneratorBase* m_generator;    // _38
	EnemyStone::Info m_stoneInfo;       // _3C
};

struct EnemyMgrBaseAlwaysMovieActor : public EnemyMgrBase {
	inline EnemyMgrBaseAlwaysMovieActor(int p1, u8 p2)
	    : EnemyMgrBase(p1, p2)
	{
	}

	virtual void doAnimation();                 // _08 (weak)
	virtual void doEntry();                     // _0C (weak)
	virtual void doSimulation(f32);             // _18 (weak)
	virtual void doDirectDraw(Graphics&);       // _1C (weak)
	virtual ~EnemyMgrBaseAlwaysMovieActor() { } // _58 (weak)
	virtual bool isAlwaysMovieActor();          // _9C (weak)

	// _00		= VTABLE
	// _00-_44	= EnemyMgrBase
};

extern JKRArchive* gParmArc;
} // namespace Game

#endif
