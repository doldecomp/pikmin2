#ifndef _GAME_GAMEMESSAGE_H
#define _GAME_GAMEMESSAGE_H

#include "types.h"
#include "Vector3.h"

namespace Game {
struct BaseGameSection;
struct SingleGameSection;
struct VsGameSection;

struct GameMessage {
    virtual bool actCommon(BaseGameSection*);   // _08 (weak)
    virtual bool actSingle(SingleGameSection*); // _0C (weak)
    virtual bool actVs(VsGameSection*);         // _10 (weak)
};

struct GameMessagePelletBorn : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10
};

struct GameMessagePelletDead : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10
};

struct GameMessageVsAddEnemy : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10

    // _00      = VTABLE
    int _04;    // _04
    int _08;    // _08
};

struct GameMessageVsBattleFinished : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10
    
    // _00      = VTABLE
    int _04;    // _04
};

struct GameMessageVsBirthTekiTreasure : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10

    Vector3f m_position;    // _04
    int _10;                // _10
    bool _14;               // _14
};

struct GameMessageVsGetDoping : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10

    // _00      = VTABLE
    int _04;    // _04, player ID?
    int _08;    // _08, spray type? 0 = bitter, 1 = spicy, maybe an enum?
};

struct GameMessageVsGetOtakara : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10

    // _00      = VTABLE
    u32 _04;    // _04, onyon type according to ghidra, but that enum is meant to be a short
    int _08;    // _08
};

struct GameMessageVsGotCard : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10

    // _00      = VTABLE
    u32 _04;    // _04, onyon type according to ghidra, but that enum is meant to be a short
};

struct GameMessageVsPikminDead : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10
};

struct GameMessageVsRedOrSuckStart : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10

    int _04;    // _04
    u8 _08;     // _08 - unknown
};

struct GameMessageVsUseCard : public GameMessage {
    virtual bool actVs(VsGameSection*); // _10
};

} // namespace Game

#endif