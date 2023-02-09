#ifndef _GAME_GAMEGENERATOR_H
#define _GAME_GAMEGENERATOR_H

#include "IDelegate.h"
#include "Matrixf.h"
#include "Graphics.h"
#include "Parameters.h"
#include "stream.h"
#include "CNode.h"
#include "id32.h"
#include "Game/EnemyBase.h"
#include "Game/enemyInfo.h"
#include "Game/EnemyPelletInfo.h"
#include "Game/pelletMgr.h"

struct J3DModelData;

namespace Game {
struct Creature;
struct GeneratorMgr;
struct GenObject;

struct Generator : public CNode {
	Generator();
	Generator(int);

	virtual ~Generator();                       // _08
	virtual void doAnimation();                 // _10
	virtual void doEntry();                     // _14
	virtual void doSetView(int viewportNumber); // _18
	virtual void doViewCalc();                  // _1C

	static void initialiseSystem();
	void generate();
	void render(Graphics&);
	void update();
	void updateUseList();

	bool isExpired();
	bool need_saveCreature();

	bool loadCreature(Stream&);
	void saveCreature(Stream&);

	void read(Stream&);
	void write(Stream&);

	void informDeath(Creature*);

	GenObject* _18;            // _18
	u32 _1C;                   // _1C /* Initialized to '____' */
	char mGenObjName[32];      // _20 /* shift-jis name given in generator files */
	ID32 _40;                  // _40
	ID32 mVersion;             // _4C
	u8 _58[4];                 // _58
	u16 mReservedNum;          // _5C
	Generator* _60;            // _60 /* mPrev */
	Generator* _64;            // _64 /* mNext */
	GeneratorMgr* mMgr;        // _68
	Creature* mCreature;       // _6C
	int mDaysTillRessurection; // _70
	u32 _74;                   // _74
	u32 _78;                   // _78
	u32 _7C;                   // _7C
	u8 _80[4];                 // _80
	int mDayLimitMaybe;        // _84
	u8 _88[12];                // _88
	Vector3f mPosition;        // _94
	Vector3f mOffset;          // _A0
	u8 _AC;                    // _AC
	int mGeneratorIndexMaybe;  // _B0

	//  0: format of the generator files on disc
	// !0: format of the gencache?
	static u8 ramMode;
};

struct GeneratorMgr : public CNode {
	GeneratorMgr();

	virtual ~GeneratorMgr();                    // _08
	virtual void doAnimation();                 // _10
	virtual void doEntry();                     // _14
	virtual void doSetView(int viewportNumber); // _18
	virtual void doViewCalc();                  // _1C

	void addMgr(GeneratorMgr*);
	void generate();
	GeneratorMgr* getNext();
	GeneratorMgr* getChild();
	bool isRootMgr();
	void read(Stream&, bool);
	void write(Stream&);
	void render(Graphics&);
	void setDayLimit(int);
	void update();
	void updateCursorPos(Vector3f&);
	void updateUseList();
	// TODO: Data members

	GeneratorMgr* mNextMgr;   // _18
	GeneratorMgr* mChildMgr;  // _1C
	GeneratorMgr* mParentMgr; // _20
	Vector3f mCursorPosition; // _24
	Generator* mGenerator;    // _28
	ID32 _34;                 // _34
	ID32 mVersionID;          // _40
	int mGeneratorCount;      // _4C
	ID32 _50;                 // _50
	Vector3f mStartPos;       // _5C
	f32 mStartDir;            // _68, v0.1 adds the start direction
	u8 _6C;                   // _6C
	u8 _6D;                   // _6D

	static Delegate1<struct BaseGameSection, Vector3f&>* cursorCallback;
};

struct GenArg : public CreatureInitArg {

	inline GenArg(Vector3f& vec) { mPosition = vec; }

	inline GenArg() { }

	virtual const char* getName(); // _08 (weak)

	// _00 VTBL
	Vector3f mPosition; // _04
};

struct GenBase : public Parameters {
	GenBase(u32, char*, char*);

	virtual void doWrite(Stream&);              // _08 (weak)
	virtual void ramSaveParameters(Stream&);    // _0C
	virtual void ramLoadParameters(Stream&);    // _10
	virtual void doEvent(u32);                  // _14 (weak)
	virtual void doRead(Stream&);               // _18 (weak)
	virtual void update(Generator*);            // _1C (weak)
	virtual void render(Graphics&, Generator*); // _20 (weak)
	virtual u32 getLatestVersion();             // _24 (weak)
	virtual J3DModelData* getShape();           // _28 (weak)

	void readVersion(Stream&);
	void read(Stream&);
	void writeVersion(Stream&);
	void write(Stream&);

	// _00 - _0C: Parameters
	// _0C: vtable
	u32 mTypeID;        // _10
	u32 mRawID;         // _14
	char* mLabelData;   // _18
	char* mObjTypeName; // _1C
	u32 _20;            // _20
};

struct EnemyGeneratorBase : public CNode {
	EnemyGeneratorBase(char* name)
	    : CNode(name)
	    , mVersion('????')
	{
	}

	virtual ~EnemyGeneratorBase() {};         // _08 (weak)
	virtual void doWrite(Stream&);            // _10 (weak)
	virtual void doRead(Stream&);             // _14 (weak)
	virtual u32 getLatestVersion();           // _18 (weak)
	virtual void draw(Graphics&, Generator*); // _1C (weak)
	virtual void* getInitialParam();          // _20 (weak)

	// _00 VTBL

	ID32 mVersion; // _18
};

struct GenObject : public GenBase {
	GenObject(u32 tag, char* description, char* t)
	    : GenBase(tag, description, t)
	{
	}

	virtual void update(Game::Generator*);                 // _1C (weak)
	virtual void render(Graphics&, Generator*);            // _20 (weak)
	virtual u32 getLatestVersion();                        // _24
	virtual void updateUseList(Generator*, int);           // _2C
	virtual Creature* generate(Generator*);                // _30 (weak)
	virtual Creature* birth(GenArg*) = 0;                  // _34
	virtual void generatorMakeMatrix(Matrixf&, Vector3f&); // _38 (weak)
	virtual void getDebugInfo(char*);                      // _3C (weak)

	// _0C     = VTBL
	// _00-_24 = GenBase
};

struct BaseItemMgr;
struct GenItemParm {
	virtual int getShapeID() { return 0; } // _08 (weak)

	// _00 VTBL
};

struct GenPelletParm {
	// virtual int getShapeID() { return 0; } // _08 (weak)
	int mIndex;
	int mColor;
	int mSize;
};

/**
 * @size{0x40}
 */
struct GenItem : public GenObject {
	inline GenItem()
	    : GenObject('item', "object type", "ITEM ���Z�b�g")
	{
		mMgrIndex   = -1;
		mRotation.z = 0.0f;
		mRotation.y = 0.0f;
		mRotation.x = 0.0f;
		mItemMgr    = nullptr;
		mParm       = nullptr;
	}

	virtual void doWrite(Stream&);                         // _08
	virtual void ramSaveParameters(Stream&);               // _0C
	virtual void ramLoadParameters(Stream&);               // _10
	virtual void doEvent(u32);                             // _14
	virtual void doRead(Stream&);                          // _18
	virtual J3DModelData* getShape();                      // _28
	virtual void updateUseList(Generator*, int);           // _2C
	virtual Creature* generate(Generator*);                // _30
	virtual Creature* birth(GenArg*);                      // _34
	virtual void generatorMakeMatrix(Matrixf&, Vector3f&); // _38

	static void initialise();

	// _0C     = VTBL
	// _00-_24 = GenObject
	int mMgrIndex;         // _24
	Vector3f mRotation;    // _28
	BaseItemMgr* mItemMgr; // _34
	GenItemParm* mParm;    // _38
};

struct GenPellet : public GenObject {
	inline GenPellet()
	    : GenObject('pelt', "object type", "PELLET ���Z�b�g")
	{
		mPelType    = 255;
		mRotation.z = 0.0f;
		mRotation.y = 0.0f;
		mRotation.x = 0.0f;
		mManager    = nullptr;
		mGenParm    = nullptr;
	}

	virtual void doWrite(Stream&);                         // _08
	virtual void ramSaveParameters(Stream&);               // _0C
	virtual void ramLoadParameters(Stream&);               // _10
	virtual void doEvent(unsigned long);                   // _14
	virtual void doRead(Stream&);                          // _18
	virtual J3DModelData* getShape();                      // _28
	virtual void updateUseList(Generator*, int);           // _2C
	virtual Creature* generate(Generator*);                // _30 (weak)
	virtual Creature* birth(GenArg*);                      // _34
	virtual void generatorMakeMatrix(Matrixf&, Vector3f&); // _38
	virtual void getDebugInfo(char*);                      // _3C

	static void initialise();

	u8 mPelType;             // _24
	Vector3f mRotation;      // _28
	BasePelletMgr* mManager; // _34
	GenPelletParm* mGenParm; // _38
};

struct GenObjectPiki : public GenObject {
	GenObjectPiki()
	    : GenObject('piki', "object type", "PIKMIN ���Z�b�g")
	    , mColourParm(this, 'p000', "�F", 0, 0, PikiColorCount)
	    , mAmountParm(this, 'p001', "��", 1, 1, 100)
	    , mIsWildPikminParm(this, 'p002', "����(1=yes)", 0, 0, 1)
	{
	}

	virtual void ramSaveParameters(Stream&); // _0C
	virtual void ramLoadParameters(Stream&); // _10
	virtual Creature* generate(Generator*);  // _30
	virtual Creature* birth(GenArg*);        // _34

	static void initialise();

	Parm<int> mColourParm;       // _24
	Parm<int> mAmountParm;       // _4C
	Parm<int> mIsWildPikminParm; // _74, assumed name
};

struct GenObjectEnemy : public GenObject {
	GenObjectEnemy();

	virtual void doWrite(Stream&);               // _08
	virtual void ramSaveParameters(Stream&);     // _0C
	virtual void ramLoadParameters(Stream&);     // _10
	virtual void doRead(Stream&);                // _18
	virtual void render(Graphics&, Generator*);  // _20
	virtual J3DModelData* getShape();            // _28
	virtual void updateUseList(Generator*, int); // _2C
	virtual Creature* generate(Generator*);      // _30
	virtual Creature* birth(GenArg*);            // _34

	static void initialise();
	void createEnemyGenerator();
	void doReadOldVersion(Stream&);

	EnemyTypeID::EEnemyTypeID mEnemyID;          // _24
	u8 mSpawnType;                               // _28 // 0: point, 1: circle
	u8 mTekiBirthType;                           // _29
	s16 mTekiNum;                                // _2A
	f32 mAppearRadius;                           // _2C
	f32 mDirection;                              // _30
	f32 mEnemySize;                              // _34
	PelletMgr::OtakaraItemCode mOtakaraItemCode; // _38
	EnemyPelletInfo mPelletInfo;                 // _3C
	EnemyGeneratorBase* mEnemyGenerator;         // _48
	u8 _4C;                                      // _4C
};

GenObject* makeObjectEnemy();

/**
 * @size{0x10}
 */
struct GenObjectFactory {
	typedef GenObject* MakeFunction();
	void createInstance();

	u32 mTypeID;                 // _00
	MakeFunction* mMakeFunction; // _04
	char* mName;                 // _08
	u32 mVersion;                // _0C

	static struct GenObjectFactoryFactory* factory;
};

/**
 * @fabricatedName
 * @size{0x10}
 */
struct GenObjectFactoryFactory {
	inline GenObjectFactoryFactory()
	{
		mFactories = new GenObjectFactory[12];
		mLimit     = 12;
		mCount     = 0;
	}

	int mCount;                   // _00
	int mLimit;                   // _04
	GenObjectFactory* mFactories; // _08
	u8 _0C[4];                    // _0C
};

struct GenObjectNavi : public GenObject {
	GenObjectNavi()
	    : GenObject('navi', "object type", "NAVI ���Z�b�g")  // set the NAVI
	    , mRotation(this, 'p000', "�X�^�[�g����", 0, 0, 360) // start direction
	{
	}

	virtual void ramSaveParameters(Stream&); // _0C
	virtual void ramLoadParameters(Stream&); // _10
	virtual Creature* generate(Generator*);  // _30
	virtual Creature* birth(GenArg*);        // _34

	static void initialise();

	Parm<f32> mRotation; // _24
};

extern GeneratorMgr* generatorMgr;
extern GeneratorMgr* onceGeneratorMgr;
extern GeneratorMgr* limitGeneratorMgr;
extern GeneratorMgr* plantsGeneratorMgr;
extern GeneratorMgr* dayGeneratorMgr;
} // namespace Game

Game::GenPellet* makePellet();

extern u32 GeneratorCurrentVersion;

#endif
