#ifndef _JKRHEAP_H
#define _JKRHEAP_H

/*
    __vt__7JKRHeap:
    .4byte 0
    .4byte 0
    .4byte __dt__7JKRHeapFv
    .4byte callAllDisposer__7JKRHeapFv
    .4byte 0
    .4byte 0
    .4byte dump_sort__7JKRHeapFv
    .4byte 0
    .4byte 0
    .4byte 0
    .4byte 0
    .4byte 0
    .4byte 0
    .4byte 0
    .4byte 0
    .4byte 0
    .4byte 0
    .4byte 0
    .4byte 0
    .4byte do_changeGroupID__7JKRHeapFUc
    .4byte do_getCurrentGroupId__7JKRHeapFv
    .4byte state_register__7JKRHeapCFPQ27JKRHeap6TStateUl
    .4byte state_compare__7JKRHeapCFRCQ27JKRHeap6TStateRCQ27JKRHeap6TState
    .4byte state_dump__7JKRHeapCFRCQ27JKRHeap6TState
*/

struct JKRHeap {
	virtual ~JKRHeap();                                             // _08
	virtual void callAllDisposer();                                 // _0C
	virtual void _10() = 0;                                         // _10
	virtual void _14() = 0;                                         // _14
	virtual void dump_sort();                                       // _18 (weak)
	virtual void _1C() = 0;                                         // _1C
	virtual void _20() = 0;                                         // _20
	virtual void _24() = 0;                                         // _24
	virtual void _28() = 0;                                         // _28
	virtual void _2C() = 0;                                         // _2C
	virtual void _30() = 0;                                         // _30
	virtual void _34() = 0;                                         // _34
	virtual void _38() = 0;                                         // _38
	virtual void _3C() = 0;                                         // _3C
	virtual void _40() = 0;                                         // _40
	virtual void _44() = 0;                                         // _44
	virtual void _48() = 0;                                         // _48
	virtual void do_changeGroupID(unsigned char);                   // _4C (weak)
	virtual void do_getCurrentGroupId();                            // _50 (weak)
	virtual void state_register(TState*, unsigned long) const;      // _54
	virtual void state_compare(const TState&, const TState&) const; // _58
	virtual void state_dump(const TState&) const;                   // _5C

	JKRHeap(void*, unsigned long, JKRHeap*, bool);
	void initArena(char**, unsigned long*, int);
	void becomeSystemHeap();
	void becomeCurrentHeap();
	void destroy();
	void alloc(unsigned long, int, JKRHeap*);
	void alloc(unsigned long, int);
	void free(void*, JKRHeap*);
	void free(void*);
	void freeAll();
	void freeTail();
	void resize(void*, unsigned long);
	void getFreeSize();
	void getTotalFreeSize();
	void changeGroupID(unsigned char);
	void getCurrentGroupId();
	void getMaxAllocatableSize(int);
	void findFromRoot(void*);
	void find(void*) const;
	void dispose(void*, unsigned long);
	void dispose(void*, void*);
	void dispose();
	void copyMemory(void*, void*, unsigned long);
	void setErrorHandler(void (*)(void*, unsigned long, int));
	void state_dumpDifference(const JKRHeap::TState&, const JKRHeap::TState&);
};

#endif
