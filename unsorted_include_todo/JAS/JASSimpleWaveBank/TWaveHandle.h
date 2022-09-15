#ifndef _JASSIMPLEWAVEBANK_TWAVEHANDLE_H
#define _JASSIMPLEWAVEBANK_TWAVEHANDLE_H

/*
    __vt__Q217JASSimpleWaveBank11TWaveHandle:
    .4byte 0
    .4byte 0
    .4byte __dt__Q217JASSimpleWaveBank11TWaveHandleFv
    .4byte getWaveInfo__Q217JASSimpleWaveBank11TWaveHandleCFv
    .4byte getWavePtr__Q217JASSimpleWaveBank11TWaveHandleCFv
*/

namespace JASSimpleWaveBank {
struct TWaveHandle {
	virtual ~TWaveHandle();           // _08 (weak)
	virtual void getWaveInfo() const; // _0C (weak)
	virtual void getWavePtr() const;  // _10 (weak)

	TWaveHandle();
};
} // namespace JASSimpleWaveBank

#endif
