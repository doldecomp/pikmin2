#ifndef _EBI_FILESELECT_H
#define _EBI_FILESELECT_H

#include "types.h"
#include "ebi/Screen/TScreenBase.h"
#include "Game/StateMachine.h"
#include "Game/MemoryCard/PlayerFileInfo.h"
#include "ebi/FS.h"
#include "ebi/CardError.h"

struct Controller;

namespace ebi {
namespace FileSelect {
struct TMgr;

enum StateID {
	FSSTATE_Standby,
	FSSTATE_EmptyUpdate,
	FSSTATE_MountCheck,
	FSState_GetPlayerHeader,
	FSSTATE_CardError,
	FSState_ScreenFileSelect
};

struct FSMStateMachine : public Game::StateMachine<TMgr> {
	virtual void init(TMgr*); // _08

	// _00     = VTBL
	// _00-_1C = Game::StateMachine
};

struct FSMState : public Game::FSMState<TMgr> {
	inline FSMState(int stateID, char* name)
	    : Game::FSMState<TMgr>(stateID)
	{
		mName = name;
	}

	virtual void init(TMgr*, Game::StateArg*);    // _08 (weak)
	virtual void exec(TMgr*);                     // _0C (weak)
	virtual void do_init(TMgr*, Game::StateArg*); // _20 (weak)
	virtual void do_exec(TMgr*);                  // _24 (weak)

	// _00     = VTBL
	// _00-_0C = Game::FSMState
	char* mName;
};

struct CardErrorStateArg : public Game::StateArg {
	int _00;
};

struct FSMState_CardError : public FSMState {
	inline FSMState_CardError()
	    : FSMState(FSSTATE_CardError, "CardError")
	{
	}

	virtual void do_init(TMgr*, Game::StateArg*); // _20
	virtual void do_exec(TMgr*);                  // _24

	// _00     = VTBL
	// _00-_0C = FSMState
};

struct FSMState_EmptyUpdate : public FSMState {
	inline FSMState_EmptyUpdate()
	    : FSMState(FSSTATE_EmptyUpdate, "EnptyUpdate") // nice devs
	{
		mCounter = 0;
		_14      = 0;
	}

	virtual void do_init(TMgr*, Game::StateArg*); // _20
	virtual void do_exec(TMgr*);                  // _24

	// _00     = VTBL
	// _00-_0C = FSMState
	u32 mCounter;
	int _14;
};

struct FSMState_ScreenFileSelect : public FSMState {
	inline FSMState_ScreenFileSelect()
	    : FSMState(FSState_ScreenFileSelect, "ScreenFileSelect")
	{
	}

	virtual void do_init(TMgr*, Game::StateArg*); // _20
	virtual void do_exec(TMgr*);                  // _24

	// _00     = VTBL
	// _00-_0C = FSMState
};

struct FSMState_CardRequest : public FSMState {
	inline FSMState_CardRequest(int id, char* name)
	    : FSMState(id, name)
	{
	}

	virtual void do_init(TMgr*, Game::StateArg*);       // _20
	virtual void do_exec(TMgr*);                        // _24
	virtual bool do_cardRequest(TMgr*);                 // _28
	virtual void do_transitCardReady(TMgr*);            // _2C
	virtual void do_transitCardNoCard(TMgr*);           // _30
	virtual void do_transitCardIOError(TMgr*);          // _34
	virtual void do_transitCardWrongDevice(TMgr*);      // _38
	virtual void do_transitCardWrongSector(TMgr*);      // _3C
	virtual void do_transitCardBroken(TMgr*);           // _40
	virtual void do_transitCardEncoding(TMgr*);         // _44
	virtual void do_transitCardNoFileSpace(TMgr*);      // _48
	virtual void do_transitCardNoFileEntry(TMgr*);      // _4C
	virtual void do_transitCardFileOpenError(TMgr*);    // _50
	virtual void do_transitCardSerialNoError(TMgr*);    // _54
	virtual void do_transitCardPlayerDataBroken(TMgr*); // _58

	// _00     = VTBL
	// _00-_0C = FSMState
	int mState;
	int mCardStatus;
};

struct FSMState_GetPlayerHeader : public FSMState_CardRequest {
	inline FSMState_GetPlayerHeader()
	    : FSMState_CardRequest(FSState_GetPlayerHeader, "GetPlayerHeader")
	{
	}

	virtual bool do_cardRequest(TMgr*);              // _28
	virtual void do_transitCardReady(TMgr*);         // _2C
	virtual void do_transitCardSerialNoError(TMgr*); // _54

	// _00     = VTBL
	// _00-_0C = FSMState_CardRequest
};

struct FSMState_MountCheck : public FSMState_CardRequest {
	inline FSMState_MountCheck()
	    : FSMState_CardRequest(FSSTATE_MountCheck, "MountCheck")
	{
	}

	virtual bool do_cardRequest(TMgr*);      // _28
	virtual void do_transitCardReady(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_CardRequest
};

struct TMgr : public JKRDisposer {
	enum enumEnd { End_0, End_1, End_2, End_3 };

	TMgr();
	virtual ~TMgr(); // _08

	static TMgr* createInstance();
	void start();
	void forceQuit();
	void update();
	void draw();
	void showInfo();
	bool isFinish();
	void goEnd_(enumEnd);
	int getStateID();

	static void onDvdErrorOccured();
	static void onDvdErrorRecovered();

	void deleteInstance();
	TMgr* getInstance();

	static TMgr* msInstance;

	// _00     = VTBL
	// _00-_18 = JKRDisposer
	FS::TMgr mMgrFS;                          // _18
	CardError::TMgr mCardErrorMgr;            // _C78
	u32 mCounter;                             // _F40
	int _F44;                                 // _F44
	Game::MemoryCard::PlayerFileInfo mPlayer; // _F48
	int mState;                               // _FE4
	bool _FE8;                                // _FE8
	bool mInError;                            // _FE9
	FSMStateMachine mFsm;                     // _FEC
	FSMState* mCurrentState;                  // _1008
};
} // namespace FileSelect
} // namespace ebi

#endif
