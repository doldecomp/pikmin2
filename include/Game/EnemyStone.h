#ifndef _GAME_ENEMYSTONE_H
#define _GAME_ENEMYSTONE_H

#include "CNode.h"
#include "Game/StateMachine.h"
#include "JSystem/J3D/J3DModel.h"
#include "Viewport.h"
#include "BitFlag.h"
#include "Matrixf.h"
#include "types.h"

namespace Game {
struct EnemyBase;

namespace EnemyStone {
struct ObjInfo {
	ObjInfo();

	char* m_name;          // _00
	s32 _04;               // _04
	Matrixf m_modelMatrix; // _08
};

struct Info {
	void setup(Stream& stream);

	u8 m_infoCnt;       // _00
	ObjInfo* m_infoArr; // _04
};

struct DrawInfo : CNode {
	DrawInfo(bool); // also has a defctor, so :shrug:

	virtual ~DrawInfo() { } // _08 (weak)

	void reset();
	void update(EnemyBase*);
	void makeMatrix(Matrixf*, bool);
	void getStateID();
	bool getPosAndScale(Vector3f*, float*);
	void appear(EnemyBase*, float);
	void fit(EnemyBase*);
	void shake(EnemyBase*, float);
	void disappear(EnemyBase*);
	void dead(EnemyBase*);

	u8 _18[0x1C];                       // _18
	FSMState<DrawInfo>* m_currentState; // _34
	float _38;                          // _38
	float _3C;                          // _3C
	ObjInfo* _40;                       // _40
	Matrixf* _44;                       // _44
};

struct Obj : CNode {
	Obj(EnemyBase*, Info*);
	virtual ~Obj(); // _08 (weak)
	// virtual void _10() = 0;	// _10 - possibly?

	bool start();
	void shake();
	void update();
	void checkDrawInfoState(int);
	void dead();

	// _00		= VTABLE
	// _04-_18	= CNode
	Info* m_info;         // _18
	CNode m_nodeArray[2]; // _1C
	EnemyBase* m_enemy;   // _4C
	u8 _50;               // _50
	u8 _51[3];            // _51 - possibly padding.
};

/**
 * @size{0x38}
 */
struct Mgr {
	Mgr();

	void loadResource();
	bool regist(Obj*);
	void release(Obj*);
	void draw(Viewport*);

	// Inlined/Unused:
	void getDrawInfo();
	void addDrawInfo(DrawInfo*);
	// ~Mgr();

	J3DModelData** _00;   // _00 - could be an array of pointers
	BitFlag<u32> _04;     // _04
	CNode m_drawInfo;     // _08 - treat as DrawInfo
	CNode m_obj;          // _20 - treat as Obj
};

} // namespace EnemyStone
} // namespace Game

#endif
