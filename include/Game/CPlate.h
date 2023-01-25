#ifndef _GAME_CPLATE_H
#define _GAME_CPLATE_H

#include "Container.h"
#include "Game/Creature.h"
#include "Game/SlotChangeListener.h"
#include "SysShape/KeyEvent.h"
#include "Parameters.h"
#include "BaseParm.h"
#include "types.h"

namespace Game {
// @size{0x114}
struct CPlate : public Container<Creature> {
	// @size{0x20}
	struct Slot {
		Slot();

		Vector3f _00;        // _00
		Vector3f _0C;        // _0C
		Creature* mCreature; // _18
		u32 _1C;             // _1C
	};

	// @fabricatedName
	struct Parms : public Parameters {
		inline Parms()
		    : Parameters(nullptr, "Navi::Parms")
		    , p000(this, 'p000', "先�?�オフセ�?�?", 17.5f, 0.0f, 100.0f)
		    , p001(this, 'p001', "長さリミッ�?", 130.0f, 10.0f, 1000.0f)
		    , p002(this, 'p002', "ポジションの大きさ(最大)", 6.0f, 1.0f, 50.0f)
		{
		}
		Parm<f32> p000; // _0C
		Parm<f32> p001; // _34
		Parm<f32> p002; // _5C
	};

	CPlate(int);

	virtual ~CPlate();            // _08 (weak)
	virtual void* getNext(void*); // _14
	virtual void* getStart();     // _18
	virtual void* getEnd();       // _1C
	virtual Creature* get(void*); // _20

	void changeFlower(Creature*);
	void directDraw(Graphics&);
	int getSlot(Creature*, SlotChangeListener*, bool);
	void getSlotPosition(int, Vector3f&);
	void rearrangeSlot(Vector3f&, f32, Vector3f&);
	void refresh(int, f32);
	void refreshSlot(f32);
	void releaseSlot(Creature*, int);
	void setPos(Vector3f&, f32, Vector3f&, f32);
	void setPosGray(Vector3f&, f32, Vector3f&, f32);
	void setPosNeutral(Vector3f&, f32, Vector3f&, f32);
	void shrink();
	void sortByColor(Creature*, int);
	void swapSlot(int, int);
	void update();
	void updateShrink();
	bool validSlot(int);

	Parms mParms;       // _1C
	Vector3f _A4;       // _A4
	f32 _B0;            // _B0
	f32 _B4;            // _B4
	f32 _B8;            // _B8
	int _BC;            // _BC
	Slot* mSlots;       // _C0
	int mSlotLimit;     // _C4
	int mSlotCount;     // _C8
	Vector3f mPosition; // _CC
	Vector3f _D8;       // _D8
	Vector3f mVelocity; // _E4
	f32 _F0;            // _F0
	f32 _F4;            // _F4
	f32 _F8;            // _F8
	f32 _FC;            // _FC
	u8 _100;            // _100
	u32* _104;          // _104
	u32 _108;           // _108
	u32 _10C;           // _10C
	u8 _110;            // _110
	u8 _111;            // _111
};
} // namespace Game

#endif
