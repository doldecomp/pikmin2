#ifndef _EFX_TEGGDOWN_H
#define _EFX_TEGGDOWN_H

#include "efx/TSimple.h"

namespace efx {
struct TEggdown : public TSimple1 {
	// _00      = VTBL
	// _00-_0C  = TSimple1
};
} // namespace efx

#endif
