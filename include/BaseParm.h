#ifndef _BASEPARM_H
#define _BASEPARM_H

#include "types.h"
#include "id32.h"
#include "Parameters.h"

struct BaseParm {
	BaseParm(Parameters*, ulong, char*);
	inline virtual int size() = 0;
	inline virtual void write(Stream&) { return; }
	inline virtual void read(Stream&) { return; }

	// _00 vtbl
	ID32 m_id;        // _04
	BaseParm* m_next; // _10
	char* m_comment;  // _14
};

template <typename T> struct Parm : public BaseParm {
	inline Parm(Parameters* parameters, ulong id, char* comment, T value, T min,
	            T max)
	    : BaseParm(parameters, id, comment)
	    , m_value(value)
	    , m_min(min)
	    , m_max(max) {};
	// Parm(Parameters*, ulong, char*);
	virtual int size();
	virtual void write(Stream&);
	virtual void read(Stream&);
	inline T operator()() { return m_value; }

	T m_value; // _18
	T _1C;     // _1C
	T m_min;   // _20
	T m_max;   // _24
};

struct ParmString : public BaseParm {
	ParmString(Parameters*, char*, int, unsigned long, char*);
	inline virtual int size() { return -1; }
	virtual void write(Stream&);
	virtual void read(Stream&);

	char* m_value; // _18
	int m_length;  // _1C
};

struct ParmEnum : public BaseParm {
	ParmEnum(Parameters*, char**, ulong, int, long, char*);
	inline virtual int size() { return 4; }
	virtual void write(Stream&);
	virtual void read(Stream&);

	ulong m_value; // _18
	int _1C;       // _1C
	char** _20;    // _20
};

#endif
