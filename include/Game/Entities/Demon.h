#ifndef _GAME_ENTITIES_DEMON_H
#define _GAME_ENTITIES_DEMON_H

#include "Game/Entities/Sarai.h"

/**
 * --Header for Bumbling Snitchbug (Demon)--
 */

namespace Game {
namespace Demon {
struct Obj : public Sarai::Obj {
	Obj();

	virtual ~Obj();                                     // _1BC (weak)
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID(); // _258 (weak)
	virtual void getStickPikminNum();                   // _2FC (weak)
	virtual void getAttackableTarget();                 // _300
	virtual void catchTarget();                         // _304
	virtual void resetAttackableTimer(f32);             // _308 (weak)

	// _00 		= VTBL
	// _00-_2D8	= Sarai::Obj
	f32 _2D8; // _2D8, attackable timer?
	          // _2DC = PelletView
};

struct Mgr : public EnemyMgrBase {
	Mgr(int objLimit, u8 modelType);

	virtual ~Mgr();                                     // _58 (weak)
	virtual void createObj(int);                        // _A0
	virtual EnemyBase* getEnemy(int);                   // _A4
	virtual void doAlloc();                             // _A8
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID(); // _AC (weak)
	virtual void loadModelData();                       // _C8
	virtual J3DModelData* doLoadBmd(void*);             // _D4 (weak)

	// _00 		= VTBL
	// _00-_44	= EnemyMgrBase
	Obj* m_obj; // _44, array of Objs, probably
};
} // namespace Demon
} // namespace Game

#endif
