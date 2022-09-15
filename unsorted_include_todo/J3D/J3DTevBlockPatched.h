#ifndef _J3DTEVBLOCKPATCHED_H
#define _J3DTEVBLOCKPATCHED_H

/*
    __vt__18J3DTevBlockPatched:
    .4byte 0
    .4byte 0
    .4byte reset__18J3DTevBlockPatchedFP11J3DTevBlock
    .4byte load__18J3DTevBlockPatchedFv
    .4byte diff__11J3DTevBlockFUl
    .4byte diffTexNo__18J3DTevBlockPatchedFv
    .4byte diffTevReg__18J3DTevBlockPatchedFv
    .4byte diffTexCoordScale__18J3DTevBlockPatchedFv
    .4byte diffTevStage__18J3DTevBlockPatchedFv
    .4byte diffTevStageIndirect__18J3DTevBlockPatchedFv
    .4byte patch__18J3DTevBlockPatchedFv
    .4byte patchTexNo__18J3DTevBlockPatchedFv
    .4byte patchTevReg__18J3DTevBlockPatchedFv
    .4byte patchTexNoAndTexCoordScale__18J3DTevBlockPatchedFv
    .4byte ptrToIndex__18J3DTevBlockPatchedFv
    .4byte indexToPtr__18J3DTevBlockPatchedFv
    .4byte getType__18J3DTevBlockPatchedFv
    .4byte countDLSize__18J3DTevBlockPatchedFv
    .4byte setTexNo__18J3DTevBlockPatchedFUlPCUs
    .4byte setTexNo__18J3DTevBlockPatchedFUlUs
    .4byte getTexNo__18J3DTevBlockPatchedCFUl
    .4byte setTevOrder__18J3DTevBlockPatchedFUlPC11J3DTevOrder
    .4byte setTevOrder__18J3DTevBlockPatchedFUl11J3DTevOrder
    .4byte getTevOrder__18J3DTevBlockPatchedFUl
    .4byte setTevColor__18J3DTevBlockPatchedFUlPC13J3DGXColorS10
    .4byte setTevColor__18J3DTevBlockPatchedFUl13J3DGXColorS10
    .4byte getTevColor__18J3DTevBlockPatchedFUl
    .4byte setTevKColor__18J3DTevBlockPatchedFUlPC10J3DGXColor
    .4byte setTevKColor__18J3DTevBlockPatchedFUl10J3DGXColor
    .4byte getTevKColor__18J3DTevBlockPatchedFUl
    .4byte setTevKColorSel__18J3DTevBlockPatchedFUlPCUc
    .4byte setTevKColorSel__18J3DTevBlockPatchedFUlUc
    .4byte getTevKColorSel__18J3DTevBlockPatchedFUl
    .4byte setTevKAlphaSel__11J3DTevBlockFUlPCUc
    .4byte setTevKAlphaSel__11J3DTevBlockFUlUc
    .4byte getTevKAlphaSel__11J3DTevBlockFUl
    .4byte setTevStageNum__18J3DTevBlockPatchedFPCUc
    .4byte setTevStageNum__18J3DTevBlockPatchedFUc
    .4byte getTevStageNum__18J3DTevBlockPatchedCFv
    .4byte setTevStage__18J3DTevBlockPatchedFUlPC11J3DTevStage
    .4byte setTevStage__18J3DTevBlockPatchedFUl11J3DTevStage
    .4byte getTevStage__18J3DTevBlockPatchedFUl
    .4byte setTevSwapModeInfo__11J3DTevBlockFUlPC18J3DTevSwapModeInfo
    .4byte setTevSwapModeInfo__11J3DTevBlockFUl18J3DTevSwapModeInfo
    .4byte setTevSwapModeTable__11J3DTevBlockFUlPC19J3DTevSwapModeTable
    .4byte setTevSwapModeTable__11J3DTevBlockFUl19J3DTevSwapModeTable
    .4byte getTevSwapModeTable__11J3DTevBlockFUl
    .4byte setIndTevStage__18J3DTevBlockPatchedFUlPC14J3DIndTevStage
    .4byte setIndTevStage__18J3DTevBlockPatchedFUl14J3DIndTevStage
    .4byte getIndTevStage__18J3DTevBlockPatchedFUl
    .4byte getTexNoOffset__18J3DTevBlockPatchedCFv
    .4byte getTevRegOffset__18J3DTevBlockPatchedCFv
    .4byte setTexNoOffset__11J3DTevBlockFUl
    .4byte setTevRegOffset__18J3DTevBlockPatchedFUl
    .4byte __dt__18J3DTevBlockPatchedFv
*/

struct J3DTevBlock {
	virtual void reset(J3DTevBlock*);                                            // _08
	virtual void load();                                                         // _0C (weak)
	virtual void diff(unsigned long);                                            // _10
	virtual void diffTexNo();                                                    // _14
	virtual void diffTevReg();                                                   // _18
	virtual void diffTexCoordScale();                                            // _1C
	virtual void diffTevStage();                                                 // _20
	virtual void diffTevStageIndirect();                                         // _24
	virtual void patch();                                                        // _28
	virtual void patchTexNo();                                                   // _2C
	virtual void patchTevReg();                                                  // _30
	virtual void patchTexNoAndTexCoordScale();                                   // _34
	virtual void ptrToIndex();                                                   // _38
	virtual void indexToPtr();                                                   // _3C (weak)
	virtual void getType();                                                      // _40 (weak)
	virtual void countDLSize();                                                  // _44
	virtual void setTexNo(unsigned long, const unsigned short*);                 // _48 (weak)
	virtual void setTexNo(unsigned long, unsigned short);                        // _4C (weak)
	virtual void getTexNo(unsigned long) const;                                  // _50 (weak)
	virtual void setTevOrder(unsigned long, const J3DTevOrder*);                 // _54 (weak)
	virtual void setTevOrder(unsigned long, J3DTevOrder);                        // _58 (weak)
	virtual void getTevOrder(unsigned long);                                     // _5C (weak)
	virtual void setTevColor(unsigned long, const J3DGXColorS10*);               // _60 (weak)
	virtual void setTevColor(unsigned long, J3DGXColorS10);                      // _64 (weak)
	virtual void getTevColor(unsigned long);                                     // _68 (weak)
	virtual void setTevKColor(unsigned long, const J3DGXColor*);                 // _6C (weak)
	virtual void setTevKColor(unsigned long, J3DGXColor);                        // _70 (weak)
	virtual void getTevKColor(unsigned long);                                    // _74 (weak)
	virtual void setTevKColorSel(unsigned long, const unsigned char*);           // _78 (weak)
	virtual void setTevKColorSel(unsigned long, unsigned char);                  // _7C (weak)
	virtual void getTevKColorSel(unsigned long);                                 // _80 (weak)
	virtual void setTevKAlphaSel(unsigned long, const unsigned char*);           // _84 (weak)
	virtual void setTevKAlphaSel(unsigned long, unsigned char);                  // _88 (weak)
	virtual void getTevKAlphaSel(unsigned long);                                 // _8C (weak)
	virtual void setTevStageNum(const unsigned char*);                           // _90 (weak)
	virtual void setTevStageNum(unsigned char);                                  // _94 (weak)
	virtual void getTevStageNum() const;                                         // _98 (weak)
	virtual void setTevStage(unsigned long, const J3DTevStage*);                 // _9C (weak)
	virtual void setTevStage(unsigned long, J3DTevStage);                        // _A0 (weak)
	virtual void getTevStage(unsigned long);                                     // _A4 (weak)
	virtual void setTevSwapModeInfo(unsigned long, const J3DTevSwapModeInfo*);   // _A8 (weak)
	virtual void setTevSwapModeInfo(unsigned long, J3DTevSwapModeInfo);          // _AC (weak)
	virtual void setTevSwapModeTable(unsigned long, const J3DTevSwapModeTable*); // _B0 (weak)
	virtual void setTevSwapModeTable(unsigned long, J3DTevSwapModeTable);        // _B4 (weak)
	virtual void getTevSwapModeTable(unsigned long);                             // _B8 (weak)
	virtual void setIndTevStage(unsigned long, const J3DIndTevStage*);           // _BC (weak)
	virtual void setIndTevStage(unsigned long, J3DIndTevStage);                  // _C0 (weak)
	virtual void getIndTevStage(unsigned long);                                  // _C4 (weak)
	virtual void getTexNoOffset() const;                                         // _C8 (weak)
	virtual void getTevRegOffset() const;                                        // _CC (weak)
	virtual void setTexNoOffset(unsigned long);                                  // _D0 (weak)
};

struct J3DTevBlockPatched : public J3DTevBlock {
	virtual void reset(J3DTevBlock*);                                  // _08
	virtual void load();                                               // _0C (weak)
	virtual void diffTexNo();                                          // _14
	virtual void diffTevReg();                                         // _18
	virtual void diffTexCoordScale();                                  // _1C
	virtual void diffTevStage();                                       // _20
	virtual void diffTevStageIndirect();                               // _24
	virtual void patch();                                              // _28
	virtual void patchTexNo();                                         // _2C
	virtual void patchTevReg();                                        // _30
	virtual void patchTexNoAndTexCoordScale();                         // _34
	virtual void ptrToIndex();                                         // _38
	virtual void indexToPtr();                                         // _3C (weak)
	virtual void getType();                                            // _40 (weak)
	virtual void countDLSize();                                        // _44
	virtual void setTexNo(unsigned long, const unsigned short*);       // _48 (weak)
	virtual void setTexNo(unsigned long, unsigned short);              // _4C (weak)
	virtual void getTexNo(unsigned long) const;                        // _50 (weak)
	virtual void setTevOrder(unsigned long, const J3DTevOrder*);       // _54 (weak)
	virtual void setTevOrder(unsigned long, J3DTevOrder);              // _58 (weak)
	virtual void getTevOrder(unsigned long);                           // _5C (weak)
	virtual void setTevColor(unsigned long, const J3DGXColorS10*);     // _60 (weak)
	virtual void setTevColor(unsigned long, J3DGXColorS10);            // _64 (weak)
	virtual void getTevColor(unsigned long);                           // _68 (weak)
	virtual void setTevKColor(unsigned long, const J3DGXColor*);       // _6C (weak)
	virtual void setTevKColor(unsigned long, J3DGXColor);              // _70 (weak)
	virtual void getTevKColor(unsigned long);                          // _74 (weak)
	virtual void setTevKColorSel(unsigned long, const unsigned char*); // _78 (weak)
	virtual void setTevKColorSel(unsigned long, unsigned char);        // _7C (weak)
	virtual void getTevKColorSel(unsigned long);                       // _80 (weak)
	virtual void setTevStageNum(const unsigned char*);                 // _90 (weak)
	virtual void setTevStageNum(unsigned char);                        // _94 (weak)
	virtual void getTevStageNum() const;                               // _98 (weak)
	virtual void setTevStage(unsigned long, const J3DTevStage*);       // _9C (weak)
	virtual void setTevStage(unsigned long, J3DTevStage);              // _A0 (weak)
	virtual void getTevStage(unsigned long);                           // _A4 (weak)
	virtual void setIndTevStage(unsigned long, const J3DIndTevStage*); // _BC (weak)
	virtual void setIndTevStage(unsigned long, J3DIndTevStage);        // _C0 (weak)
	virtual void getIndTevStage(unsigned long);                        // _C4 (weak)
	virtual void getTexNoOffset() const;                               // _C8 (weak)
	virtual void getTevRegOffset() const;                              // _CC (weak)
	virtual void setTevRegOffset(unsigned long);                       // _D4 (weak)
	virtual ~J3DTevBlockPatched();                                     // _D8 (weak)

	void initialize();
};

#endif
