#ifndef _JSYSTEM_JMESSAGE_TREFERENCE_H
#define _JSYSTEM_JMESSAGE_TREFERENCE_H

#include "types.h"

namespace JMessage {
struct TReference {
	virtual ~TReference();                      // _08
	virtual char* do_word(unsigned long) const; // _0C

	void* _04;		// _04 - TResourceContainer* maybe
};
} // namespace JMessage

#endif
