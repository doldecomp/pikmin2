#ifndef _JKRSOLIDHEAP_H
#define _JKRSOLIDHEAP_H

/*
    __vt__12JKRSolidHeap:
    .4byte 0
    .4byte 0
    .4byte __dt__12JKRSolidHeapFv
    .4byte callAllDisposer__7JKRHeapFv
    .4byte getHeapType__12JKRSolidHeapFv
    .4byte check__12JKRSolidHeapFv
    .4byte dump_sort__7JKRHeapFv
    .4byte dump__12JKRSolidHeapFv
    .4byte do_destroy__12JKRSolidHeapFv
    .4byte do_alloc__12JKRSolidHeapFUli
    .4byte do_free__12JKRSolidHeapFPv
    .4byte do_freeAll__12JKRSolidHeapFv
    .4byte do_freeTail__12JKRSolidHeapFv
    .4byte do_fillFreeArea__12JKRSolidHeapFv
    .4byte do_resize__12JKRSolidHeapFPvUl
    .4byte do_getSize__12JKRSolidHeapFPv
    .4byte do_getFreeSize__12JKRSolidHeapFv
    .4byte do_getMaxFreeBlock__12JKRSolidHeapFv
    .4byte do_getTotalFreeSize__12JKRSolidHeapFv
    .4byte do_changeGroupID__7JKRHeapFUc
    .4byte do_getCurrentGroupId__7JKRHeapFv
    .4byte state_register__12JKRSolidHeapCFPQ27JKRHeap6TStateUl
    .4byte state_compare__12JKRSolidHeapCFRCQ27JKRHeap6TStateRCQ27JKRHeap6TState
    .4byte state_dump__7JKRHeapCFRCQ27JKRHeap6TState
*/

struct JKRHeap {
	virtual ~JKRHeap();                                                               // _08
	virtual void callAllDisposer();                                                   // _0C
	virtual void getHeapType();                                                       // _10 (weak)
	virtual void check();                                                             // _14
	virtual void dump_sort();                                                         // _18 (weak)
	virtual void dump();                                                              // _1C
	virtual void do_destroy();                                                        // _20
	virtual void do_alloc(unsigned long, int);                                        // _24
	virtual void do_free(void*);                                                      // _28
	virtual void do_freeAll();                                                        // _2C
	virtual void do_freeTail();                                                       // _30
	virtual void do_fillFreeArea();                                                   // _34
	virtual void do_resize(void*, unsigned long);                                     // _38
	virtual void do_getSize(void*);                                                   // _3C
	virtual void do_getFreeSize();                                                    // _40 (weak)
	virtual void do_getMaxFreeBlock();                                                // _44 (weak)
	virtual void do_getTotalFreeSize();                                               // _48 (weak)
	virtual void do_changeGroupID(unsigned char);                                     // _4C (weak)
	virtual void do_getCurrentGroupId();                                              // _50 (weak)
	virtual void state_register(JKRHeap::TState*, unsigned long) const;               // _54
	virtual void state_compare(const JKRHeap::TState&, const JKRHeap::TState&) const; // _58
	virtual void state_dump(const TState&) const;                                     // _5C
};

struct JKRSolidHeap : public JKRHeap {
	virtual ~JKRSolidHeap();                                                          // _08
	virtual void getHeapType();                                                       // _10 (weak)
	virtual void check();                                                             // _14
	virtual void dump();                                                              // _1C
	virtual void do_destroy();                                                        // _20
	virtual void do_alloc(unsigned long, int);                                        // _24
	virtual void do_free(void*);                                                      // _28
	virtual void do_freeAll();                                                        // _2C
	virtual void do_freeTail();                                                       // _30
	virtual void do_fillFreeArea();                                                   // _34
	virtual void do_resize(void*, unsigned long);                                     // _38
	virtual void do_getSize(void*);                                                   // _3C
	virtual void do_getFreeSize();                                                    // _40 (weak)
	virtual void do_getMaxFreeBlock();                                                // _44 (weak)
	virtual void do_getTotalFreeSize();                                               // _48 (weak)
	virtual void state_register(JKRHeap::TState*, unsigned long) const;               // _54
	virtual void state_compare(const JKRHeap::TState&, const JKRHeap::TState&) const; // _58

	void create(unsigned long, JKRHeap*, bool);
	JKRSolidHeap(void*, unsigned long, JKRHeap*, bool);
	void adjustSize();
	void allocFromHead(unsigned long, int);
	void allocFromTail(unsigned long, int);
};

#endif
