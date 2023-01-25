#ifndef _EBI_CARDERROR_H
#define _EBI_CARDERROR_H

#include "types.h"
#include "ebi/Screen/TScreenBase.h"
#include "ebi/Screen/TMemoryCard.h"
#include "Game/StateMachine.h"

struct Controller;

namespace ebi {
namespace CardError {
struct TMgr;

enum StateID {
	CARDERROR_Standby,
	CARDERROR_EmptyScreen,
	CARDERROR_NoCard,
	CARDERROR_IOError,
	CARDERROR_WrongDevice,
	CARDERROR_WrongSector,
	CARDERROR_OverCapacity,
	CARDERROR_InitCardOnIPL,
	CARDERROR_CardNotUsable,
	CARDERROR_NoFileForSave,
	CARDERROR_FinishFormat,
	CARDERROR_FinishCreateNewFile,
	CARDERROR_SerialNoError,
	CARDERROR_FailToFormat_NoCard,
	CARDERROR_FailToFormat_IOError,
	CARDERROR_FailToCreateNewFile_NoCard,
	CARDERROR_FailToCreateNewFile_IOError,
	CARDERROR_FailToSave_NoCard,
	CARDERROR_FailToSave_IOError,
	CARDERROR_DataBrokenAndDoYouFormat,
	CARDERROR_DoYouOpenIPL,
	CARDERROR_DoYouFormat,
	CARDERROR_DoYouCreateNewFile,
	CARDERROR_DoYouStartGameWithoutSave,
	CARDERROR_GameCantSave,
	CARDERROR_NowFormat,
	CARDERROR_NowCreateNewFile,
	CARDERROR_StateCount // NOT A REAL STATE
};

struct FSMStateMachine : public Game::StateMachine<TMgr> {
	virtual void init(TMgr*); // _08

	// _00     = VTBL
	// _00-_1C = Game::StateMachine
};

////////////////////////////////////////////////////////////
// BASE STATES
struct FSMState : public Game::FSMState<TMgr> {
	inline FSMState(int stateID)
	    : Game::FSMState<TMgr>(stateID)
	{
	}

	virtual void init(TMgr*, Game::StateArg*);    // _08 (weak)
	virtual void exec(TMgr*);                     // _0C (weak)
	virtual void do_init(TMgr*, Game::StateArg*); // _20 (weak)
	virtual void do_exec(TMgr*);                  // _24 (weak)

	// _00     = VTBL
	// _00-_0C = Game::FSMState
	char* mName;
};

struct FSMState_Standby : public FSMState {
	FSMState_Standby()
	    : FSMState(CARDERROR_Standby)
	{
		mName = "Standby";
	}

	// doesnt have its own vtable?

	// _00     = VTBL
	// _00-_10 = FSMState
};

struct FSMState_EmptyScreen : public FSMState {
	FSMState_EmptyScreen()
	    : FSMState(CARDERROR_EmptyScreen)
	{
		mName = "EmptyScreen";
	}

	// doesnt have its own vtable?

	// _00     = VTBL
	// _00-_10 = FSMState
};

struct FSMState_NoCard : public FSMState {
	FSMState_NoCard(int id)
	    : FSMState(id)
	{
	}

	virtual void do_init(TMgr*, Game::StateArg*); // _20
	virtual void do_exec(TMgr*);                  // _24
	virtual void do_open(TMgr*)          = 0;     // _28
	virtual void do_transit(TMgr*)       = 0;     // _2C
	virtual void do_transitOnCard(TMgr*) = 0;     // _30

	// _00     = VTBL
	// _00-_10 = FSMState
	bool mIsClosed;
};

struct FSMState_CardRequest : public FSMState {
	FSMState_CardRequest(int id)
	    : FSMState(id)
	{
	}

	virtual void do_init(TMgr*, Game::StateArg*);    // _20
	virtual void do_exec(TMgr*);                     // _24
	virtual void do_open(TMgr*)             = 0;     // _28
	virtual bool do_cardRequest()           = 0;     // _2C
	virtual void do_transitCardReady(TMgr*) = 0;     // _30
	virtual void do_transitCardNoCard(TMgr*);        // _34
	virtual void do_transitCardIOError(TMgr*);       // _38
	virtual void do_transitCardWrongDevice(TMgr*);   // _3C
	virtual void do_transitCardWrongSector(TMgr*);   // _40
	virtual void do_transitCardBroken(TMgr*);        // _44
	virtual void do_transitCardEncoding(TMgr*);      // _48
	virtual void do_transitCardNoFileSpace(TMgr*);   // _4C
	virtual void do_transitCardNoFileEntry(TMgr*);   // _50
	virtual void do_transitCardFileOpenError(TMgr*); // _54
	virtual void do_transitCardSerialNoError(TMgr*); // _58

	// _00     = VTBL
	// _00-_10 = FSMState
	int mState;
	int mCardStatus;
};

struct FSMState_Question : public FSMState {
	inline FSMState_Question(int id)
	    : FSMState(id)
	{
	}

	virtual void do_init(TMgr*, Game::StateArg*); // _20
	virtual void do_exec(TMgr*);                  // _24
	virtual void do_open(TMgr*)       = 0;        // _28
	virtual void do_transitYes(TMgr*) = 0;        // _2C
	virtual void do_transitNo(TMgr*)  = 0;        // _30

	// _00     = VTBL
	// _00-_10 = FSMState
	bool mDoCheckCard;
};

struct FSMState_Warning : public FSMState {
	inline FSMState_Warning(int id)
	    : FSMState(id)
	{
	}

	virtual void do_init(TMgr*, Game::StateArg*); // _20
	virtual void do_exec(TMgr*);                  // _24
	virtual void do_open(TMgr*)    = 0;           // _28
	virtual void do_transit(TMgr*) = 0;           // _2C

	// _00     = VTBL
	// _00-_10 = FSMState
	bool mCanClose;    // _10
	bool mIsClosed;    // _11
	bool mDoCheckCard; // _12
};
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// QUESTION STATES
struct FSMState_Q00_DataBrokenAndDoYouFormat : public FSMState_Question {
	inline FSMState_Q00_DataBrokenAndDoYouFormat()
	    : FSMState_Question(CARDERROR_DataBrokenAndDoYouFormat)
	{
		mName = "Q00_DataBrokenAndDoYouFormat";
	}

	virtual void do_open(TMgr*);       // _28
	virtual void do_transitYes(TMgr*); // _2C
	virtual void do_transitNo(TMgr*);  // _30

	// _00     = VTBL
	// _00-_0C = FSMState_Question
};

struct FSMState_Q01_DoYouOpenIPL : public FSMState_Question {
	inline FSMState_Q01_DoYouOpenIPL()
	    : FSMState_Question(CARDERROR_DoYouOpenIPL)
	{
		mName = "Q01_DoYouOpenIPL";
	}

	virtual void do_open(TMgr*);       // _28
	virtual void do_transitYes(TMgr*); // _2C
	virtual void do_transitNo(TMgr*);  // _30

	// _00     = VTBL
	// _00-_0C = FSMState_Question
};

struct FSMState_Q02_DoYouFormat : public FSMState_Question {
	inline FSMState_Q02_DoYouFormat()
	    : FSMState_Question(CARDERROR_DoYouFormat)
	{
		mName = "Q02_DoYouFormat";
	}

	virtual void do_open(TMgr*);       // _28
	virtual void do_transitYes(TMgr*); // _2C
	virtual void do_transitNo(TMgr*);  // _30

	// _00     = VTBL
	// _00-_0C = FSMState_Question
};

struct FSMState_Q03_DoYouCreateNewFile : public FSMState_Question {
	inline FSMState_Q03_DoYouCreateNewFile()
	    : FSMState_Question(CARDERROR_DoYouCreateNewFile)
	{
		mName = "Q03_DoYouCreateNewFile";
	}

	virtual void do_open(TMgr*);       // _28
	virtual void do_transitYes(TMgr*); // _2C
	virtual void do_transitNo(TMgr*);  // _30

	// _00     = VTBL
	// _00-_0C = FSMState_Question
};

struct FSMState_Q04_DoYouStartGameWithoutSave : public FSMState_Question {
	inline FSMState_Q04_DoYouStartGameWithoutSave()
	    : FSMState_Question(CARDERROR_DoYouStartGameWithoutSave)
	{
		mName = "Q04_DoYouStartGameWithoutSave";
	}

	virtual void do_open(TMgr*);       // _28
	virtual void do_transitYes(TMgr*); // _2C
	virtual void do_transitNo(TMgr*);  // _30

	// _00     = VTBL
	// _00-_0C = FSMState_Question
};

struct FSMState_Q05_GameCantSave : public FSMState_Question {
	inline FSMState_Q05_GameCantSave()
	    : FSMState_Question(CARDERROR_GameCantSave)
	{
		mName = "Q05_GameCantSave";
	}

	virtual void do_open(TMgr*);       // _28
	virtual void do_transitYes(TMgr*); // _2C
	virtual void do_transitNo(TMgr*);  // _30

	// _00     = VTBL
	// _00-_0C = FSMState_Question
};
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// WARNING STATES
struct FSMState_W00_NoCard : public FSMState_NoCard {
	inline FSMState_W00_NoCard()
	    : FSMState_NoCard(CARDERROR_NoCard)
	{
		mName = "W00_NoCard";
	}

	virtual void do_open(TMgr*);          // _28
	virtual void do_transit(TMgr*);       // _2C
	virtual void do_transitOnCard(TMgr*); // _30

	// _00     = VTBL
	// _00-_0C = FSMState_NoCard
};

struct FSMState_W01_IOError : public FSMState_Warning {
	inline FSMState_W01_IOError()
	    : FSMState_Warning(CARDERROR_IOError)
	{
		mName = "W01_IOError";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_W02_WrongDevice : public FSMState_Warning {
	inline FSMState_W02_WrongDevice()
	    : FSMState_Warning(CARDERROR_WrongDevice)
	{
		mName = "W02_WrongDevice";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_W03_WrongSector : public FSMState_Warning {
	inline FSMState_W03_WrongSector()
	    : FSMState_Warning(CARDERROR_WrongSector)
	{
		mName = "W03_WrongSector";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_W04_OverCapacity : public FSMState_Warning {
	inline FSMState_W04_OverCapacity()
	    : FSMState_Warning(CARDERROR_OverCapacity)
	{
		mName = "W04_OverCapacity";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_W05_InitCardOnIPL : public FSMState_Warning {
	inline FSMState_W05_InitCardOnIPL()
	    : FSMState_Warning(CARDERROR_InitCardOnIPL)
	{
		mName = "W05_InitCardOnIPL";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_W06_CardNotUsable : public FSMState_Warning {
	inline FSMState_W06_CardNotUsable()
	    : FSMState_Warning(CARDERROR_CardNotUsable)
	{
		mName = "W06_CardNotUsable";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_W07_NoFileForSave : public FSMState_Warning {
	inline FSMState_W07_NoFileForSave()
	    : FSMState_Warning(CARDERROR_NoFileForSave)
	{
		mName = "W07_NoFileForSave";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_W08_FinishFormat : public FSMState_Warning {
	inline FSMState_W08_FinishFormat()
	    : FSMState_Warning(CARDERROR_FinishFormat)
	{
		mName = "W08_FinishFormat";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_W09_FinishCreateNewFile : public FSMState_Warning {
	inline FSMState_W09_FinishCreateNewFile()
	    : FSMState_Warning(CARDERROR_FinishCreateNewFile)
	{
		mName = "W09_FinishCreateNewFile";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_W10_SerialNoError : public FSMState_Warning {
	inline FSMState_W10_SerialNoError()
	    : FSMState_Warning(CARDERROR_SerialNoError)
	{
		mName = "W10_SerialNoError";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// WARNING FAIL STATES
struct FSMState_WF0_FailToFormat_NoCard : public FSMState_Warning {
	inline FSMState_WF0_FailToFormat_NoCard()
	    : FSMState_Warning(CARDERROR_FailToFormat_NoCard)
	{
		mName = "WF0_FailToFormat_NoCard";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_WF1_FailToFormat_IOError : public FSMState_Warning {
	inline FSMState_WF1_FailToFormat_IOError()
	    : FSMState_Warning(CARDERROR_FailToFormat_IOError)
	{
		mName = "WF1_FailToFormat_IOError";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_WF2_FailToCreateNewFile_NoCard : public FSMState_Warning {
	inline FSMState_WF2_FailToCreateNewFile_NoCard()
	    : FSMState_Warning(CARDERROR_FailToCreateNewFile_NoCard)
	{
		mName = "WF2_FailToCreateNewFile_NoCard";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_WF3_FailToCreateNewFile_IOError : public FSMState_Warning {
	inline FSMState_WF3_FailToCreateNewFile_IOError()
	    : FSMState_Warning(CARDERROR_FailToCreateNewFile_IOError)
	{
		mName = "WF3_FailToCreateNewFile_IOError";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_WF4_FailToSave_NoCard : public FSMState_Warning {
	inline FSMState_WF4_FailToSave_NoCard()
	    : FSMState_Warning(CARDERROR_FailToSave_NoCard)
	{
		mName = "WF4_FailToSave_NoCard";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};

struct FSMState_WF5_FailToSave_IOError : public FSMState_Warning {
	inline FSMState_WF5_FailToSave_IOError()
	    : FSMState_Warning(CARDERROR_FailToSave_IOError)
	{
		mName = "WF5_FailToSave_IOError";
	}

	virtual void do_open(TMgr*);    // _28
	virtual void do_transit(TMgr*); // _2C

	// _00     = VTBL
	// _00-_0C = FSMState_Warning
};
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// CARD REQUEST STATES
struct FSMState_WN0_NowFormat : public FSMState_CardRequest {
	inline FSMState_WN0_NowFormat()
	    : FSMState_CardRequest(CARDERROR_NowFormat)
	{
		mName = "WN0_NowFormat";
	}

	virtual void do_open(TMgr*);               // _28
	virtual bool do_cardRequest();             // _2C
	virtual void do_transitCardReady(TMgr*);   // _30
	virtual void do_transitCardNoCard(TMgr*);  // _34
	virtual void do_transitCardIOError(TMgr*); // _38

	// _00     = VTBL
	// _00-_0C = FSMState_CardRequest
};

struct FSMState_WN1_NowCreateNewFile : public FSMState_CardRequest {
	inline FSMState_WN1_NowCreateNewFile()
	    : FSMState_CardRequest(CARDERROR_NowCreateNewFile)
	{
		mName = "WN1_NowCreateNewFile";
	}

	virtual void do_open(TMgr*);               // _28
	virtual bool do_cardRequest();             // _2C
	virtual void do_transitCardReady(TMgr*);   // _30
	virtual void do_transitCardNoCard(TMgr*);  // _34
	virtual void do_transitCardIOError(TMgr*); // _38

	// _00     = VTBL
	// _00-_0C = FSMState_CardRequest
};
////////////////////////////////////////////////////////////

struct TMgr : Screen::TMemoryCard {
	enum enumStart {
		Start_NoCard,
		Start_IOError,
		Start_WrongDevice,
		Start_WrongSector,
		Start_DataBrokenAndDoYouFormat,
		Start_OverCapacity,
		Start_DoYouCreateNewFile,
		Start_NoCard2,
		Start_IOError2,
		Start_WrongDevice2,
		Start_WrongSector2,
		Start_DataBrokenAndDoYouFormat2,
		Start_OverCapacity2,
		Start_DoYouCreateNewFile2,
		Start_SerialNoError,
		Start_FailToSave_NoCard,
		Start_FailToSave_IOError
	};

	enum enumEnd { End_0, End_1, End_2, End_3, End_4 };

	void startSeq(enumStart);
	void forceQuitSeq();
	void goEnd_(enumEnd);
	void checkAndTransitNoCard_();
	void update();
	void draw();
	bool isGetEnd();
	bool isFinish();
	void showInfo(long, long, long, long);
	int getStateID();

	TMgr();
	~TMgr();

	// _00-_298 = TMemoryCard
	u32 mCounter;                  // _298
	int _29C;                      // _29C
	u32 mEndStat;                  // _2A0, unknown
	int mIsBroken;                 // _2A4
	FSMStateMachine mStateMachine; // _2A8
	FSMState* mCurrentState;       // _2C4
};
} // namespace CardError
} // namespace ebi

#endif
