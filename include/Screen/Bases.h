#ifndef _SCREEN_BASES_H
#define _SCREEN_BASES_H

#include "Dolphin/gx.h"
#include "Dolphin/stl.h"
#include "JSystem/JKR/JKRDisposer.h"
#include "JSystem/JUT/TColor.h"
#include "Resource.h"
#include "Screen/Enums.h"
#include "og/Screen/DispMemberDummy.h"
#include "Graphics.h"
#include "types.h"
#include "CNode.h"

struct Controller;
struct Graphics;
struct JKRArchive;
struct JKRSolidHeap;

namespace og {
namespace Screen {
struct DispMemberBase;
} // namespace Screen
} // namespace og

namespace Resource {
struct MgrCommand;
} // namespace Resource

namespace Screen {
struct IObjBase;
struct ObjBase;
struct ObjMgrBase;
struct Mgr;

struct SceneArgBase {
	virtual SceneType getSceneType() const; // _00
	virtual int getClassSize() = 0;         // _04
};

struct StartSceneArg : public SceneArgBase {
	float _04; // _04
};

struct SetSceneArg : public SceneArgBase {
	/**
	 * @fabricated
	 * Unsure if p3 and p4 exist or are hardcoded.
	 * Remove p3 and p4 if they appear to never be set to anything else by a ctor.
	 */
	inline SetSceneArg(SceneType sceneType, og::Screen::DispMemberBase* dispMember, u8 p3 = 0, bool p4 = true)
	    : m_sceneType(sceneType)
	    , m_dispMember(dispMember)
	{
		// _08 = p3;
		// _09 = p4;
	}

	virtual SceneType getSceneType() const; // _00
	virtual int getClassSize();             // _04

	SceneType m_sceneType;                    // _04
	u8 _08;                                   // _08
	bool _09;                                 // _09
	og::Screen::DispMemberBase* m_dispMember; // _0C
};

struct EndSceneArg : public SceneArgBase {
	virtual int getClassSize(); // _04

	u8 _04; // _04
};

struct SceneBase {
	enum StateID { Unknown0 = 0, Unknown1, Unknown2, Unknown3, Unknown4 };

	SceneBase();
	~SceneBase();

	virtual SceneType getSceneType()     = 0;                           // _08
	virtual ScreenOwnerID getOwnerID()   = 0;                           // _0C
	virtual ScreenMemberID getMemberID() = 0;                           // _10
	virtual bool isUseBackupSceneInfo() { return false; }               // _14 (weak)
	virtual bool isDrawInDemo() const { return true; }                  // _18 (weak)
	virtual const char* getResName() const = 0;                         // _1C
	virtual void doCreateObj(JKRArchive*)  = 0;                         // _20
	virtual void doUserCallBackFunc(Resource::MgrCommand*);             // _24 (weak)
	virtual void setPort(Graphics& gfx) { gfx.m_perspGraph.setPort(); } // _28 (weak)
	virtual void doUpdateActive();                                      // _2C
	virtual bool doConfirmSetScene(SetSceneArg&) { return true; }       // _30 (weak)
	virtual bool doConfirmStartScene(StartSceneArg*) { return true; }   // _34 (weak)
	virtual bool doConfirmEndScene(EndSceneArg*&) { return true; }      // _38 (weak)
	virtual bool doStart(StartSceneArg*);                               // _3C
	virtual bool doEnd(EndSceneArg*);                                   // _40
	virtual bool setDefaultDispMember()                                 // _44 (weak)
	{
		og::Screen::DispMemberDummy disp;
		memcpy(m_dispMemberBuffer, (void*)&disp, sizeof(disp));
		return true;
	}
	virtual void doSetBackupScene(SetSceneArg&) { } // _48 (weak)
	virtual int doGetFinishState() { return -3; }   // _4C (weak)

	bool confirmEndScene(EndSceneArg*);
	bool confirmSetScene(SetSceneArg&);
	bool confirmStartScene(StartSceneArg*);
	void create();
	void createObj(JKRArchive*);
	void destroy();
	void draw(Graphics&);
	bool end(EndSceneArg*);
	void endScene(EndSceneArg*);
	int getFinishState();
	Controller* getGamePad() const;
	void registObj(ObjBase*, JKRArchive*);
	IObjBase* searchObj(char*);
	bool setBackupScene();
	void setColorBG(u8, u8, u8, u8);
	void setScene(SetSceneArg&);
	bool setDispMember(og::Screen::DispMemberBase*);
	bool start(StartSceneArg*);
	void startScene(StartSceneArg*);
	void update();
	bool updateActive();
	void userCallBackFunc(Resource::MgrCommand*);

	// Unused/inlined:
	u32 getBackupSceneType();
	void setBGMode(int);

	// VTBL _00
	char m_name[256];                                 // _004
	Controller* m_controller;                         // _104
	Mgr* m_screenMgr;                                 // _108
	Delegate1<SceneBase, Resource::MgrCommand*> _10C; // _10C
	int m_stateID;                                    // _120
	float m_someTime;                                 // _124
	Resource::MgrCommand m_command;                   // _128
	ObjMgrBase* m_objMgr;                             // _218
	u8* m_dispMemberBuffer;                           // _21C
};

struct IObjBase : public CNode, JKRDisposer {
	IObjBase()
	    : CNode("No Name")
	    , JKRDisposer()
	{
	}
	// vtable 2
	virtual ~IObjBase();                          // _00
	virtual bool update()                    = 0; // _04
	virtual void draw(Graphics&)             = 0; // _08
	virtual bool start(const StartSceneArg*) = 0; // _0C
	virtual bool end(const EndSceneArg*)     = 0; // _10
	virtual void setOwner(SceneBase*)        = 0; // _14
	virtual SceneBase* getOwner() const      = 0; // _18
	virtual void create(JKRArchive*)         = 0; // _1C
};

struct ObjBase : public IObjBase {
	ObjBase();

	// vtable 2
	virtual ~ObjBase();                               // _00
	virtual bool update();                            // _04
	virtual void draw(Graphics&);                     // _08
	virtual bool start(const StartSceneArg*);         // _0C
	virtual bool end(const EndSceneArg*);             // _10
	virtual void setOwner(SceneBase*);                // _14
	virtual SceneBase* getOwner() const;              // _18
	virtual void create(JKRArchive*);                 // _1C
	virtual bool confirmSetScene(SetSceneArg&);       // _20
	virtual bool confirmStartScene(StartSceneArg*);   // _24
	virtual bool confirmEndScene(EndSceneArg*);       // _28
	virtual bool doStart(const StartSceneArg*);       // _2C
	virtual bool doEnd(const EndSceneArg*);           // _30
	virtual void doCreate(JKRArchive*);               // _34
	virtual bool doUpdateFadein();                    // _38
	virtual void doUpdateFadeinFinish();              // _3C
	virtual bool doUpdate();                          // _40
	virtual void doUpdateFinish();                    // _44
	virtual bool doUpdateFadeout();                   // _48
	virtual void doUpdateFadeoutFinish();             // _4C
	virtual void doDraw(Graphics&);                   // _50
	virtual bool doConfirmSetScene(SetSceneArg&);     // _54
	virtual bool doConfirmStartScene(StartSceneArg*); // _58
	virtual bool doConfirmEndScene(EndSceneArg*&);    // _5C

	og::Screen::DispMemberBase* getDispMember();
	Controller* getGamePad() const;

	int _30;            // _30
	SceneBase* m_owner; // _34
};

struct MgrBase : public JKRDisposer {
	virtual ~MgrBase();                          // _08
	virtual bool setScene(SetSceneArg&)     = 0; // _0C
	virtual bool startScene(StartSceneArg*) = 0; // _10
	virtual void endScene(EndSceneArg*)     = 0; // _14
};

struct Mgr : public MgrBase {
	Mgr();

	virtual ~Mgr() { }                          // _08 (weak)
	virtual bool setScene(SetSceneArg&);        // _0C
	virtual bool startScene(StartSceneArg*);    // _10
	virtual void endScene(EndSceneArg*);        // _14
	virtual void reset();                       // _18
	virtual void setColorBG(JUtility::TColor&); // _1C (weak)
	virtual void setBGMode(int);                // _20 (weak)
	virtual void doGetSceneBase(long);          // _24
	virtual void drawBG(Graphics&);             // _28
	virtual void drawWipe(Graphics&);           // _2C (weak)

	u8 _18;                     // _18
	u8 _19;                     // _19
	u8 _1A;                     // _1A
	u8 _1B;                     // _1B
	SceneBase* m_backupScene;   // _1C
	Controller* m_controller;   // _20
	u8 _24[8];                  // _24
	CNode _2C;                  // _2C
	CNode _44;                  // _44
	JKRSolidHeap* _5C;          // _5C
	CNode _60;                  // _60
	CNode m_sceneInfoListNode;  // _78
	u8 _90;                     // _90
	u8 _91;                     // _91
	u8 _92;                     // _92
	u32 _94;                    // _94
	u32 _98;                    // _98
	JUtility::TColor m_bgColor; // _9C
	JUtility::TColor _A0;       // _A0
	int m_bgMode;               // _A4
};
struct ObjMgrBase {
	ObjMgrBase();

	bool confirmSetScene(SetSceneArg&);
	bool confirmStartScene(StartSceneArg*);
	bool confirmEndScene(EndSceneArg*);
	void draw(Graphics&);
	void registObj(IObjBase*, SceneBase*);
	IObjBase* search(SceneBase*, char*);

	bool start(StartSceneArg*);
	bool update();
	bool end(EndSceneArg*);

	CNode _00;
};
} // namespace Screen

namespace newScreen {
struct Mgr : public Screen::Mgr {
	virtual ~Mgr();                             // _08 (weak)
	virtual void reset();                       // _18
	virtual void setColorBG(JUtility::TColor&); // _1C (weak)
	virtual void setBGMode(int);                // _20 (weak)
	virtual void doGetSceneBase(long);          // _24
	virtual void drawBG(Graphics&);             // _28

	void create();
};

} // namespace newScreen

#endif
