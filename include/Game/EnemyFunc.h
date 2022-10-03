#ifndef _GAME_ENEMYFUNC_H
#define _GAME_ENEMYFUNC_H

#include "Game/Piki.h"
#include "types.h"

namespace Game {
struct Creature;
struct EnemyBase;
struct Piki;
struct Navi;
} // namespace Game

template <typename T> struct Condition;

namespace Game {
namespace EnemyFunc {

Navi* getNearestNavi(Creature*, f32, f32, f32*, Condition<Navi>*);
Piki* getNearestPikmin(Creature*, f32, f32, f32*, Condition<Piki>*);
Creature* getNearestPikminOrNavi(Creature*, f32, f32, f32*, Condition<Navi>*, Condition<Piki>*);

void flickStickPikmin(Creature*, f32, f32, f32, f32, Condition<Piki>*);
void flickNearbyPikmin(Creature*, f32, f32, f32, f32, Condition<Piki>*);
void flickNearbyNavi(Creature*, f32, f32, f32, f32, Condition<Navi>*);

void eatPikmin(EnemyBase*, Condition<Piki>*);
void swallowPikmin(Creature*, f32, Condition<Piki>*);
void attackNavi(Creature*, f32, f32, f32, CollPart*, Condition<Navi>*);

bool isStartFlick(EnemyBase*, bool);
bool isTherePikmin(Creature*, f32, Condition<Piki>*);
bool isThereOlimar(Creature*, f32, Condition<Navi>*);

int getSurroundPikminNum(Creature*, f32, Condition<Piki>*);
int getStickPikminColorNum(Creature*, int);

void walkToTarget(EnemyBase*, Creature*, f32, f32, f32);
void walkToTarget(EnemyBase*, Vector3f&, f32, f32, f32);
} // namespace EnemyFunc
} // namespace Game

#endif
