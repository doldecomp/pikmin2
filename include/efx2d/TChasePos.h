#ifndef _EFX2D_TCHASEPOS_H
#define _EFX2D_TCHASEPOS_H

#include "Vector2.h"
#include "efx2d/TForever.h"

namespace efx2d {
struct TChasePos : public TForever {
	// vtable 1
	virtual bool create(Arg*); // _08
	// vtable 2
	virtual ~TChasePos();                  // _34 (weak)
	virtual void execute(JPABaseEmitter*); // _38

	Vector2f* _14;
};

struct TChasePosDir : public TForever {
	// vtable 1
	virtual bool create(Arg*); // _08
	// vtable 2
	virtual ~TChasePosDir() { }            // _34 (weak)
	virtual void execute(JPABaseEmitter*); // _38

	Vector2f* _14;
	Vector2f* _18;
};
} // namespace efx2d

#endif
