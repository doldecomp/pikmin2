#ifndef _EFX_TBABY_H
#define _EFX_TBABY_H

#include "efx/TChasePos.h"
#include "efx/TSimple.h"

namespace efx {
struct TBabyBecha : public TSimple1 {
	// _00      = VTBL
	// _00-_0C  = TSimple1
};

struct TBabyBorn : public TChasePos {
	virtual ~TBabyBorn(); // _48 (weak)

	// _00      = VTBL
	// _00-_14  = TChasePos
};
} // namespace efx

#endif
