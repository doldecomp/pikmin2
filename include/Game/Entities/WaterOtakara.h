#ifndef _GAME_ENTITIES_WATEROTAKARA_H
#define _GAME_ENTITIES_WATEROTAKARA_H

#include "Game/Entities/OtakaraBase.h"

/**
 * --Header for Caustic Dweevil (WaterOtakara)--
 */

namespace efx {
struct TChaseMtxT2;
};

namespace Game {
namespace WaterOtakara {
struct Obj : public OtakaraBase::Obj {
	Obj();

	//////////////// VTABLE
	virtual ~Obj();                                     // _1BC (weak)
	virtual void changeMaterial();                      // _200
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID(); // _258 (weak)
	virtual void interactCreature(Creature*);           // _2FC
	virtual void createEffect();                        // _300
	virtual void setupEffect();                         // _304
	virtual void startChargeEffect();                   // _308
	virtual void finishChargeEffect();                  // _30C
	virtual void createDisChargeEffect();               // _310
	virtual void effectDrawOn();                        // _314
	virtual void effectDrawOff();                       // _318
	virtual void startDisChargeSE();                    // _320
	                                                    //////////////// VTABLE END

	// _00 		= VTBL
	// _00-_2F4 = OtakaraBase::Obj
};

struct Mgr : public OtakaraBase::Mgr {
	Mgr(int, u8);

	virtual ~Mgr();                                     // _58 (weak)
	virtual void createObj(int);                        // _A0
	virtual EnemyBase* getEnemy(int);                   // _A4
	virtual void doAlloc();                             // _A8
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID(); // _AC (weak)
	virtual void loadTexData();                         // _D0
	virtual void getChangeTexture();                    // _E0 (weak)

	// _00 		= VTBL
	// _00-_48	= OtakaraBase::Mgr
	Obj* m_obj; // _48, array of Objs
};
} // namespace WaterOtakara
} // namespace Game

#endif
