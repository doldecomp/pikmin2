.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global THPGXRestore
THPGXRestore:
/* 8044D684 0044A5C4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8044D688 0044A5C8  7C 08 02 A6 */	mflr r0
/* 8044D68C 0044A5CC  38 60 00 01 */	li r3, 1
/* 8044D690 0044A5D0  38 80 00 07 */	li r4, 7
/* 8044D694 0044A5D4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8044D698 0044A5D8  38 A0 00 00 */	li r5, 0
/* 8044D69C 0044A5DC  4B C9 BA E9 */	bl GXSetZMode
/* 8044D6A0 0044A5E0  38 60 00 00 */	li r3, 0
/* 8044D6A4 0044A5E4  38 80 00 01 */	li r4, 1
/* 8044D6A8 0044A5E8  38 A0 00 00 */	li r5, 0
/* 8044D6AC 0044A5EC  38 C0 00 0F */	li r6, 0xf
/* 8044D6B0 0044A5F0  4B C9 BA 29 */	bl GXSetBlendMode
/* 8044D6B4 0044A5F4  38 60 00 01 */	li r3, 1
/* 8044D6B8 0044A5F8  4B C9 78 E5 */	bl GXSetNumTexGens
/* 8044D6BC 0044A5FC  38 60 00 00 */	li r3, 0
/* 8044D6C0 0044A600  4B C9 97 A5 */	bl GXSetNumChans
/* 8044D6C4 0044A604  38 60 00 01 */	li r3, 1
/* 8044D6C8 0044A608  4B C9 B4 F1 */	bl GXSetNumTevStages
/* 8044D6CC 0044A60C  38 60 00 00 */	li r3, 0
/* 8044D6D0 0044A610  38 80 00 00 */	li r4, 0
/* 8044D6D4 0044A614  38 A0 00 00 */	li r5, 0
/* 8044D6D8 0044A618  38 C0 00 FF */	li r6, 0xff
/* 8044D6DC 0044A61C  4B C9 B3 41 */	bl GXSetTevOrder
/* 8044D6E0 0044A620  38 60 00 00 */	li r3, 0
/* 8044D6E4 0044A624  38 80 00 03 */	li r4, 3
/* 8044D6E8 0044A628  4B C9 AD 95 */	bl GXSetTevOp
/* 8044D6EC 0044A62C  38 60 00 00 */	li r3, 0
/* 8044D6F0 0044A630  38 80 00 00 */	li r4, 0
/* 8044D6F4 0044A634  38 A0 00 00 */	li r5, 0
/* 8044D6F8 0044A638  4B C9 B1 8D */	bl GXSetTevSwapMode
/* 8044D6FC 0044A63C  38 60 00 01 */	li r3, 1
/* 8044D700 0044A640  38 80 00 00 */	li r4, 0
/* 8044D704 0044A644  38 A0 00 00 */	li r5, 0
/* 8044D708 0044A648  4B C9 B1 7D */	bl GXSetTevSwapMode
/* 8044D70C 0044A64C  38 60 00 02 */	li r3, 2
/* 8044D710 0044A650  38 80 00 00 */	li r4, 0
/* 8044D714 0044A654  38 A0 00 00 */	li r5, 0
/* 8044D718 0044A658  4B C9 B1 6D */	bl GXSetTevSwapMode
/* 8044D71C 0044A65C  38 60 00 03 */	li r3, 3
/* 8044D720 0044A660  38 80 00 00 */	li r4, 0
/* 8044D724 0044A664  38 A0 00 00 */	li r5, 0
/* 8044D728 0044A668  4B C9 B1 5D */	bl GXSetTevSwapMode
/* 8044D72C 0044A66C  38 60 00 00 */	li r3, 0
/* 8044D730 0044A670  38 80 00 00 */	li r4, 0
/* 8044D734 0044A674  38 A0 00 01 */	li r5, 1
/* 8044D738 0044A678  38 C0 00 02 */	li r6, 2
/* 8044D73C 0044A67C  38 E0 00 03 */	li r7, 3
/* 8044D740 0044A680  4B C9 B1 8D */	bl GXSetTevSwapModeTable
/* 8044D744 0044A684  38 60 00 01 */	li r3, 1
/* 8044D748 0044A688  38 80 00 00 */	li r4, 0
/* 8044D74C 0044A68C  38 A0 00 00 */	li r5, 0
/* 8044D750 0044A690  38 C0 00 00 */	li r6, 0
/* 8044D754 0044A694  38 E0 00 03 */	li r7, 3
/* 8044D758 0044A698  4B C9 B1 75 */	bl GXSetTevSwapModeTable
/* 8044D75C 0044A69C  38 60 00 02 */	li r3, 2
/* 8044D760 0044A6A0  38 80 00 01 */	li r4, 1
/* 8044D764 0044A6A4  38 A0 00 01 */	li r5, 1
/* 8044D768 0044A6A8  38 C0 00 01 */	li r6, 1
/* 8044D76C 0044A6AC  38 E0 00 03 */	li r7, 3
/* 8044D770 0044A6B0  4B C9 B1 5D */	bl GXSetTevSwapModeTable
/* 8044D774 0044A6B4  38 60 00 03 */	li r3, 3
/* 8044D778 0044A6B8  38 80 00 02 */	li r4, 2
/* 8044D77C 0044A6BC  38 A0 00 02 */	li r5, 2
/* 8044D780 0044A6C0  38 C0 00 02 */	li r6, 2
/* 8044D784 0044A6C4  38 E0 00 03 */	li r7, 3
/* 8044D788 0044A6C8  4B C9 B1 45 */	bl GXSetTevSwapModeTable
/* 8044D78C 0044A6CC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8044D790 0044A6D0  7C 08 03 A6 */	mtlr r0
/* 8044D794 0044A6D4  38 21 00 10 */	addi r1, r1, 0x10
/* 8044D798 0044A6D8  4E 80 00 20 */	blr 

.global THPGXYuv2RgbSetup
THPGXYuv2RgbSetup:
/* 8044D79C 0044A6DC  94 21 FF 40 */	stwu r1, -0xc0(r1)
/* 8044D7A0 0044A6E0  7C 08 02 A6 */	mflr r0
/* 8044D7A4 0044A6E4  38 80 00 00 */	li r4, 0
/* 8044D7A8 0044A6E8  90 01 00 C4 */	stw r0, 0xc4(r1)
/* 8044D7AC 0044A6EC  93 E1 00 BC */	stw r31, 0xbc(r1)
/* 8044D7B0 0044A6F0  93 C1 00 B8 */	stw r30, 0xb8(r1)
/* 8044D7B4 0044A6F4  A3 E3 00 04 */	lhz r31, 4(r3)
/* 8044D7B8 0044A6F8  A3 C3 00 06 */	lhz r30, 6(r3)
/* 8044D7BC 0044A6FC  38 60 00 00 */	li r3, 0
/* 8044D7C0 0044A700  4B C9 BA 2D */	bl GXSetPixelFmt
/* 8044D7C4 0044A704  3C 80 43 30 */	lis r4, 0x4330
/* 8044D7C8 0044A708  6F C3 80 00 */	xoris r3, r30, 0x8000
/* 8044D7CC 0044A70C  6F E0 80 00 */	xoris r0, r31, 0x8000
/* 8044D7D0 0044A710  90 61 00 94 */	stw r3, 0x94(r1)
/* 8044D7D4 0044A714  C0 22 27 84 */	lfs f1, lbl_80520AE4@sda21(r2)
/* 8044D7D8 0044A718  38 61 00 4C */	addi r3, r1, 0x4c
/* 8044D7DC 0044A71C  90 81 00 90 */	stw r4, 0x90(r1)
/* 8044D7E0 0044A720  C8 82 27 90 */	lfd f4, lbl_80520AF0@sda21(r2)
/* 8044D7E4 0044A724  FC 60 08 90 */	fmr f3, f1
/* 8044D7E8 0044A728  C8 01 00 90 */	lfd f0, 0x90(r1)
/* 8044D7EC 0044A72C  FC A0 08 90 */	fmr f5, f1
/* 8044D7F0 0044A730  90 01 00 9C */	stw r0, 0x9c(r1)
/* 8044D7F4 0044A734  EC 40 20 28 */	fsubs f2, f0, f4
/* 8044D7F8 0044A738  C0 C2 27 88 */	lfs f6, lbl_80520AE8@sda21(r2)
/* 8044D7FC 0044A73C  90 81 00 98 */	stw r4, 0x98(r1)
/* 8044D800 0044A740  C8 01 00 98 */	lfd f0, 0x98(r1)
/* 8044D804 0044A744  EC 80 20 28 */	fsubs f4, f0, f4
/* 8044D808 0044A748  4B C9 D5 D1 */	bl C_MTXOrtho
/* 8044D80C 0044A74C  38 61 00 4C */	addi r3, r1, 0x4c
/* 8044D810 0044A750  38 80 00 01 */	li r4, 1
/* 8044D814 0044A754  4B C9 BC 35 */	bl GXSetProjection
/* 8044D818 0044A758  3C 60 43 30 */	lis r3, 0x4330
/* 8044D81C 0044A75C  6F E4 80 00 */	xoris r4, r31, 0x8000
/* 8044D820 0044A760  6F C0 80 00 */	xoris r0, r30, 0x8000
/* 8044D824 0044A764  90 81 00 A4 */	stw r4, 0xa4(r1)
/* 8044D828 0044A768  C0 22 27 84 */	lfs f1, lbl_80520AE4@sda21(r2)
/* 8044D82C 0044A76C  90 61 00 A0 */	stw r3, 0xa0(r1)
/* 8044D830 0044A770  C8 82 27 90 */	lfd f4, lbl_80520AF0@sda21(r2)
/* 8044D834 0044A774  FC 40 08 90 */	fmr f2, f1
/* 8044D838 0044A778  C8 01 00 A0 */	lfd f0, 0xa0(r1)
/* 8044D83C 0044A77C  FC A0 08 90 */	fmr f5, f1
/* 8044D840 0044A780  90 01 00 AC */	stw r0, 0xac(r1)
/* 8044D844 0044A784  EC 60 20 28 */	fsubs f3, f0, f4
/* 8044D848 0044A788  C0 C2 27 8C */	lfs f6, lbl_80520AEC@sda21(r2)
/* 8044D84C 0044A78C  90 61 00 A8 */	stw r3, 0xa8(r1)
/* 8044D850 0044A790  C8 01 00 A8 */	lfd f0, 0xa8(r1)
/* 8044D854 0044A794  EC 80 20 28 */	fsubs f4, f0, f4
/* 8044D858 0044A798  4B C9 BF 39 */	bl GXSetViewport
/* 8044D85C 0044A79C  7F E5 FB 78 */	mr r5, r31
/* 8044D860 0044A7A0  7F C6 F3 78 */	mr r6, r30
/* 8044D864 0044A7A4  38 60 00 00 */	li r3, 0
/* 8044D868 0044A7A8  38 80 00 00 */	li r4, 0
/* 8044D86C 0044A7AC  4B C9 BF 6D */	bl GXSetScissor
/* 8044D870 0044A7B0  38 61 00 1C */	addi r3, r1, 0x1c
/* 8044D874 0044A7B4  4B C9 CA 2D */	bl PSMTXIdentity
/* 8044D878 0044A7B8  38 61 00 1C */	addi r3, r1, 0x1c
/* 8044D87C 0044A7BC  38 80 00 00 */	li r4, 0
/* 8044D880 0044A7C0  4B C9 BC F9 */	bl GXLoadPosMtxImm
/* 8044D884 0044A7C4  38 60 00 00 */	li r3, 0
/* 8044D888 0044A7C8  4B C9 BD 91 */	bl GXSetCurrentMtx
/* 8044D88C 0044A7CC  38 60 00 01 */	li r3, 1
/* 8044D890 0044A7D0  38 80 00 07 */	li r4, 7
/* 8044D894 0044A7D4  38 A0 00 00 */	li r5, 0
/* 8044D898 0044A7D8  4B C9 B8 ED */	bl GXSetZMode
/* 8044D89C 0044A7DC  38 60 00 00 */	li r3, 0
/* 8044D8A0 0044A7E0  38 80 00 01 */	li r4, 1
/* 8044D8A4 0044A7E4  38 A0 00 00 */	li r5, 0
/* 8044D8A8 0044A7E8  38 C0 00 00 */	li r6, 0
/* 8044D8AC 0044A7EC  4B C9 B8 2D */	bl GXSetBlendMode
/* 8044D8B0 0044A7F0  38 60 00 01 */	li r3, 1
/* 8044D8B4 0044A7F4  4B C9 B8 79 */	bl GXSetColorUpdate
/* 8044D8B8 0044A7F8  38 60 00 00 */	li r3, 0
/* 8044D8BC 0044A7FC  4B C9 B8 9D */	bl GXSetAlphaUpdate
/* 8044D8C0 0044A800  38 60 00 00 */	li r3, 0
/* 8044D8C4 0044A804  4B C9 8C 6D */	bl GXSetDispCopyGamma
/* 8044D8C8 0044A808  38 60 00 00 */	li r3, 0
/* 8044D8CC 0044A80C  4B C9 95 99 */	bl GXSetNumChans
/* 8044D8D0 0044A810  38 60 00 02 */	li r3, 2
/* 8044D8D4 0044A814  4B C9 76 C9 */	bl GXSetNumTexGens
/* 8044D8D8 0044A818  38 60 00 00 */	li r3, 0
/* 8044D8DC 0044A81C  38 80 00 01 */	li r4, 1
/* 8044D8E0 0044A820  38 A0 00 04 */	li r5, 4
/* 8044D8E4 0044A824  38 C0 00 3C */	li r6, 0x3c
/* 8044D8E8 0044A828  38 E0 00 00 */	li r7, 0
/* 8044D8EC 0044A82C  39 00 00 7D */	li r8, 0x7d
/* 8044D8F0 0044A830  4B C9 74 2D */	bl GXSetTexCoordGen2
/* 8044D8F4 0044A834  38 60 00 01 */	li r3, 1
/* 8044D8F8 0044A838  38 80 00 01 */	li r4, 1
/* 8044D8FC 0044A83C  38 A0 00 04 */	li r5, 4
/* 8044D900 0044A840  38 C0 00 3C */	li r6, 0x3c
/* 8044D904 0044A844  38 E0 00 00 */	li r7, 0
/* 8044D908 0044A848  39 00 00 7D */	li r8, 0x7d
/* 8044D90C 0044A84C  4B C9 74 11 */	bl GXSetTexCoordGen2
/* 8044D910 0044A850  4B C9 A0 51 */	bl GXInvalidateTexAll
/* 8044D914 0044A854  4B C9 6D BD */	bl GXClearVtxDesc
/* 8044D918 0044A858  38 60 00 09 */	li r3, 9
/* 8044D91C 0044A85C  38 80 00 01 */	li r4, 1
/* 8044D920 0044A860  4B C9 69 65 */	bl GXSetVtxDesc
/* 8044D924 0044A864  38 60 00 0D */	li r3, 0xd
/* 8044D928 0044A868  38 80 00 01 */	li r4, 1
/* 8044D92C 0044A86C  4B C9 69 59 */	bl GXSetVtxDesc
/* 8044D930 0044A870  38 60 00 07 */	li r3, 7
/* 8044D934 0044A874  38 80 00 09 */	li r4, 9
/* 8044D938 0044A878  38 A0 00 01 */	li r5, 1
/* 8044D93C 0044A87C  38 C0 00 03 */	li r6, 3
/* 8044D940 0044A880  38 E0 00 00 */	li r7, 0
/* 8044D944 0044A884  4B C9 6D C5 */	bl GXSetVtxAttrFmt
/* 8044D948 0044A888  38 60 00 07 */	li r3, 7
/* 8044D94C 0044A88C  38 80 00 0D */	li r4, 0xd
/* 8044D950 0044A890  38 A0 00 01 */	li r5, 1
/* 8044D954 0044A894  38 C0 00 02 */	li r6, 2
/* 8044D958 0044A898  38 E0 00 00 */	li r7, 0
/* 8044D95C 0044A89C  4B C9 6D AD */	bl GXSetVtxAttrFmt
/* 8044D960 0044A8A0  38 60 00 04 */	li r3, 4
/* 8044D964 0044A8A4  4B C9 B2 55 */	bl GXSetNumTevStages
/* 8044D968 0044A8A8  38 60 00 00 */	li r3, 0
/* 8044D96C 0044A8AC  38 80 00 01 */	li r4, 1
/* 8044D970 0044A8B0  38 A0 00 01 */	li r5, 1
/* 8044D974 0044A8B4  38 C0 00 FF */	li r6, 0xff
/* 8044D978 0044A8B8  4B C9 B0 A5 */	bl GXSetTevOrder
/* 8044D97C 0044A8BC  38 60 00 00 */	li r3, 0
/* 8044D980 0044A8C0  38 80 00 0F */	li r4, 0xf
/* 8044D984 0044A8C4  38 A0 00 08 */	li r5, 8
/* 8044D988 0044A8C8  38 C0 00 0E */	li r6, 0xe
/* 8044D98C 0044A8CC  38 E0 00 02 */	li r7, 2
/* 8044D990 0044A8D0  4B C9 AB 79 */	bl GXSetTevColorIn
/* 8044D994 0044A8D4  38 60 00 00 */	li r3, 0
/* 8044D998 0044A8D8  38 80 00 00 */	li r4, 0
/* 8044D99C 0044A8DC  38 A0 00 00 */	li r5, 0
/* 8044D9A0 0044A8E0  38 C0 00 00 */	li r6, 0
/* 8044D9A4 0044A8E4  38 E0 00 00 */	li r7, 0
/* 8044D9A8 0044A8E8  39 00 00 00 */	li r8, 0
/* 8044D9AC 0044A8EC  4B C9 AB E5 */	bl GXSetTevColorOp
/* 8044D9B0 0044A8F0  38 60 00 00 */	li r3, 0
/* 8044D9B4 0044A8F4  38 80 00 07 */	li r4, 7
/* 8044D9B8 0044A8F8  38 A0 00 04 */	li r5, 4
/* 8044D9BC 0044A8FC  38 C0 00 06 */	li r6, 6
/* 8044D9C0 0044A900  38 E0 00 01 */	li r7, 1
/* 8044D9C4 0044A904  4B C9 AB 89 */	bl GXSetTevAlphaIn
/* 8044D9C8 0044A908  38 60 00 00 */	li r3, 0
/* 8044D9CC 0044A90C  38 80 00 01 */	li r4, 1
/* 8044D9D0 0044A910  38 A0 00 00 */	li r5, 0
/* 8044D9D4 0044A914  38 C0 00 00 */	li r6, 0
/* 8044D9D8 0044A918  38 E0 00 00 */	li r7, 0
/* 8044D9DC 0044A91C  39 00 00 00 */	li r8, 0
/* 8044D9E0 0044A920  4B C9 AC 19 */	bl GXSetTevAlphaOp
/* 8044D9E4 0044A924  38 60 00 00 */	li r3, 0
/* 8044D9E8 0044A928  38 80 00 0C */	li r4, 0xc
/* 8044D9EC 0044A92C  4B C9 AD E1 */	bl GXSetTevKColorSel
/* 8044D9F0 0044A930  38 60 00 00 */	li r3, 0
/* 8044D9F4 0044A934  38 80 00 1C */	li r4, 0x1c
/* 8044D9F8 0044A938  4B C9 AE 31 */	bl GXSetTevKAlphaSel
/* 8044D9FC 0044A93C  38 60 00 00 */	li r3, 0
/* 8044DA00 0044A940  38 80 00 00 */	li r4, 0
/* 8044DA04 0044A944  38 A0 00 00 */	li r5, 0
/* 8044DA08 0044A948  4B C9 AE 7D */	bl GXSetTevSwapMode
/* 8044DA0C 0044A94C  38 60 00 01 */	li r3, 1
/* 8044DA10 0044A950  38 80 00 01 */	li r4, 1
/* 8044DA14 0044A954  38 A0 00 02 */	li r5, 2
/* 8044DA18 0044A958  38 C0 00 FF */	li r6, 0xff
/* 8044DA1C 0044A95C  4B C9 B0 01 */	bl GXSetTevOrder
/* 8044DA20 0044A960  38 60 00 01 */	li r3, 1
/* 8044DA24 0044A964  38 80 00 0F */	li r4, 0xf
/* 8044DA28 0044A968  38 A0 00 08 */	li r5, 8
/* 8044DA2C 0044A96C  38 C0 00 0E */	li r6, 0xe
/* 8044DA30 0044A970  38 E0 00 00 */	li r7, 0
/* 8044DA34 0044A974  4B C9 AA D5 */	bl GXSetTevColorIn
/* 8044DA38 0044A978  38 60 00 01 */	li r3, 1
/* 8044DA3C 0044A97C  38 80 00 00 */	li r4, 0
/* 8044DA40 0044A980  38 A0 00 00 */	li r5, 0
/* 8044DA44 0044A984  38 C0 00 01 */	li r6, 1
/* 8044DA48 0044A988  38 E0 00 00 */	li r7, 0
/* 8044DA4C 0044A98C  39 00 00 00 */	li r8, 0
/* 8044DA50 0044A990  4B C9 AB 41 */	bl GXSetTevColorOp
/* 8044DA54 0044A994  38 60 00 01 */	li r3, 1
/* 8044DA58 0044A998  38 80 00 07 */	li r4, 7
/* 8044DA5C 0044A99C  38 A0 00 04 */	li r5, 4
/* 8044DA60 0044A9A0  38 C0 00 06 */	li r6, 6
/* 8044DA64 0044A9A4  38 E0 00 00 */	li r7, 0
/* 8044DA68 0044A9A8  4B C9 AA E5 */	bl GXSetTevAlphaIn
/* 8044DA6C 0044A9AC  38 60 00 01 */	li r3, 1
/* 8044DA70 0044A9B0  38 80 00 01 */	li r4, 1
/* 8044DA74 0044A9B4  38 A0 00 00 */	li r5, 0
/* 8044DA78 0044A9B8  38 C0 00 00 */	li r6, 0
/* 8044DA7C 0044A9BC  38 E0 00 00 */	li r7, 0
/* 8044DA80 0044A9C0  39 00 00 00 */	li r8, 0
/* 8044DA84 0044A9C4  4B C9 AB 75 */	bl GXSetTevAlphaOp
/* 8044DA88 0044A9C8  38 60 00 01 */	li r3, 1
/* 8044DA8C 0044A9CC  38 80 00 0D */	li r4, 0xd
/* 8044DA90 0044A9D0  4B C9 AD 3D */	bl GXSetTevKColorSel
/* 8044DA94 0044A9D4  38 60 00 01 */	li r3, 1
/* 8044DA98 0044A9D8  38 80 00 1D */	li r4, 0x1d
/* 8044DA9C 0044A9DC  4B C9 AD 8D */	bl GXSetTevKAlphaSel
/* 8044DAA0 0044A9E0  38 60 00 01 */	li r3, 1
/* 8044DAA4 0044A9E4  38 80 00 00 */	li r4, 0
/* 8044DAA8 0044A9E8  38 A0 00 00 */	li r5, 0
/* 8044DAAC 0044A9EC  4B C9 AD D9 */	bl GXSetTevSwapMode
/* 8044DAB0 0044A9F0  38 60 00 02 */	li r3, 2
/* 8044DAB4 0044A9F4  38 80 00 00 */	li r4, 0
/* 8044DAB8 0044A9F8  38 A0 00 00 */	li r5, 0
/* 8044DABC 0044A9FC  38 C0 00 FF */	li r6, 0xff
/* 8044DAC0 0044AA00  4B C9 AF 5D */	bl GXSetTevOrder
/* 8044DAC4 0044AA04  38 60 00 02 */	li r3, 2
/* 8044DAC8 0044AA08  38 80 00 0F */	li r4, 0xf
/* 8044DACC 0044AA0C  38 A0 00 08 */	li r5, 8
/* 8044DAD0 0044AA10  38 C0 00 0C */	li r6, 0xc
/* 8044DAD4 0044AA14  38 E0 00 00 */	li r7, 0
/* 8044DAD8 0044AA18  4B C9 AA 31 */	bl GXSetTevColorIn
/* 8044DADC 0044AA1C  38 60 00 02 */	li r3, 2
/* 8044DAE0 0044AA20  38 80 00 00 */	li r4, 0
/* 8044DAE4 0044AA24  38 A0 00 00 */	li r5, 0
/* 8044DAE8 0044AA28  38 C0 00 00 */	li r6, 0
/* 8044DAEC 0044AA2C  38 E0 00 01 */	li r7, 1
/* 8044DAF0 0044AA30  39 00 00 00 */	li r8, 0
/* 8044DAF4 0044AA34  4B C9 AA 9D */	bl GXSetTevColorOp
/* 8044DAF8 0044AA38  38 60 00 02 */	li r3, 2
/* 8044DAFC 0044AA3C  38 80 00 04 */	li r4, 4
/* 8044DB00 0044AA40  38 A0 00 07 */	li r5, 7
/* 8044DB04 0044AA44  38 C0 00 07 */	li r6, 7
/* 8044DB08 0044AA48  38 E0 00 00 */	li r7, 0
/* 8044DB0C 0044AA4C  4B C9 AA 41 */	bl GXSetTevAlphaIn
/* 8044DB10 0044AA50  38 60 00 02 */	li r3, 2
/* 8044DB14 0044AA54  38 80 00 00 */	li r4, 0
/* 8044DB18 0044AA58  38 A0 00 00 */	li r5, 0
/* 8044DB1C 0044AA5C  38 C0 00 00 */	li r6, 0
/* 8044DB20 0044AA60  38 E0 00 01 */	li r7, 1
/* 8044DB24 0044AA64  39 00 00 00 */	li r8, 0
/* 8044DB28 0044AA68  4B C9 AA D1 */	bl GXSetTevAlphaOp
/* 8044DB2C 0044AA6C  38 60 00 02 */	li r3, 2
/* 8044DB30 0044AA70  38 80 00 00 */	li r4, 0
/* 8044DB34 0044AA74  38 A0 00 00 */	li r5, 0
/* 8044DB38 0044AA78  4B C9 AD 4D */	bl GXSetTevSwapMode
/* 8044DB3C 0044AA7C  38 60 00 03 */	li r3, 3
/* 8044DB40 0044AA80  38 80 00 FF */	li r4, 0xff
/* 8044DB44 0044AA84  38 A0 00 FF */	li r5, 0xff
/* 8044DB48 0044AA88  38 C0 00 FF */	li r6, 0xff
/* 8044DB4C 0044AA8C  4B C9 AE D1 */	bl GXSetTevOrder
/* 8044DB50 0044AA90  38 60 00 03 */	li r3, 3
/* 8044DB54 0044AA94  38 80 00 01 */	li r4, 1
/* 8044DB58 0044AA98  38 A0 00 00 */	li r5, 0
/* 8044DB5C 0044AA9C  38 C0 00 0E */	li r6, 0xe
/* 8044DB60 0044AAA0  38 E0 00 0F */	li r7, 0xf
/* 8044DB64 0044AAA4  4B C9 A9 A5 */	bl GXSetTevColorIn
/* 8044DB68 0044AAA8  38 60 00 03 */	li r3, 3
/* 8044DB6C 0044AAAC  38 80 00 00 */	li r4, 0
/* 8044DB70 0044AAB0  38 A0 00 00 */	li r5, 0
/* 8044DB74 0044AAB4  38 C0 00 00 */	li r6, 0
/* 8044DB78 0044AAB8  38 E0 00 01 */	li r7, 1
/* 8044DB7C 0044AABC  39 00 00 00 */	li r8, 0
/* 8044DB80 0044AAC0  4B C9 AA 11 */	bl GXSetTevColorOp
/* 8044DB84 0044AAC4  38 60 00 03 */	li r3, 3
/* 8044DB88 0044AAC8  38 80 00 07 */	li r4, 7
/* 8044DB8C 0044AACC  38 A0 00 07 */	li r5, 7
/* 8044DB90 0044AAD0  38 C0 00 07 */	li r6, 7
/* 8044DB94 0044AAD4  38 E0 00 06 */	li r7, 6
/* 8044DB98 0044AAD8  4B C9 A9 B5 */	bl GXSetTevAlphaIn
/* 8044DB9C 0044AADC  38 60 00 03 */	li r3, 3
/* 8044DBA0 0044AAE0  38 80 00 00 */	li r4, 0
/* 8044DBA4 0044AAE4  38 A0 00 00 */	li r5, 0
/* 8044DBA8 0044AAE8  38 C0 00 00 */	li r6, 0
/* 8044DBAC 0044AAEC  38 E0 00 01 */	li r7, 1
/* 8044DBB0 0044AAF0  39 00 00 00 */	li r8, 0
/* 8044DBB4 0044AAF4  4B C9 AA 45 */	bl GXSetTevAlphaOp
/* 8044DBB8 0044AAF8  38 60 00 03 */	li r3, 3
/* 8044DBBC 0044AAFC  38 80 00 00 */	li r4, 0
/* 8044DBC0 0044AB00  38 A0 00 00 */	li r5, 0
/* 8044DBC4 0044AB04  4B C9 AC C1 */	bl GXSetTevSwapMode
/* 8044DBC8 0044AB08  38 60 00 03 */	li r3, 3
/* 8044DBCC 0044AB0C  38 80 00 0E */	li r4, 0xe
/* 8044DBD0 0044AB10  4B C9 AB FD */	bl GXSetTevKColorSel
/* 8044DBD4 0044AB14  80 A2 27 70 */	lwz r5, lbl_80520AD0@sda21(r2)
/* 8044DBD8 0044AB18  38 81 00 14 */	addi r4, r1, 0x14
/* 8044DBDC 0044AB1C  80 02 27 74 */	lwz r0, lbl_80520AD4@sda21(r2)
/* 8044DBE0 0044AB20  38 60 00 01 */	li r3, 1
/* 8044DBE4 0044AB24  90 A1 00 14 */	stw r5, 0x14(r1)
/* 8044DBE8 0044AB28  90 01 00 18 */	stw r0, 0x18(r1)
/* 8044DBEC 0044AB2C  4B C9 AA F1 */	bl GXSetTevColorS10
/* 8044DBF0 0044AB30  80 02 27 78 */	lwz r0, lbl_80520AD8@sda21(r2)
/* 8044DBF4 0044AB34  38 81 00 10 */	addi r4, r1, 0x10
/* 8044DBF8 0044AB38  38 60 00 00 */	li r3, 0
/* 8044DBFC 0044AB3C  90 01 00 10 */	stw r0, 0x10(r1)
/* 8044DC00 0044AB40  4B C9 AB 59 */	bl GXSetTevKColor
/* 8044DC04 0044AB44  80 02 27 7C */	lwz r0, lbl_80520ADC@sda21(r2)
/* 8044DC08 0044AB48  38 81 00 0C */	addi r4, r1, 0xc
/* 8044DC0C 0044AB4C  38 60 00 01 */	li r3, 1
/* 8044DC10 0044AB50  90 01 00 0C */	stw r0, 0xc(r1)
/* 8044DC14 0044AB54  4B C9 AB 45 */	bl GXSetTevKColor
/* 8044DC18 0044AB58  80 02 27 80 */	lwz r0, lbl_80520AE0@sda21(r2)
/* 8044DC1C 0044AB5C  38 81 00 08 */	addi r4, r1, 8
/* 8044DC20 0044AB60  38 60 00 02 */	li r3, 2
/* 8044DC24 0044AB64  90 01 00 08 */	stw r0, 8(r1)
/* 8044DC28 0044AB68  4B C9 AB 31 */	bl GXSetTevKColor
/* 8044DC2C 0044AB6C  38 60 00 00 */	li r3, 0
/* 8044DC30 0044AB70  38 80 00 00 */	li r4, 0
/* 8044DC34 0044AB74  38 A0 00 01 */	li r5, 1
/* 8044DC38 0044AB78  38 C0 00 02 */	li r6, 2
/* 8044DC3C 0044AB7C  38 E0 00 03 */	li r7, 3
/* 8044DC40 0044AB80  4B C9 AC 8D */	bl GXSetTevSwapModeTable
/* 8044DC44 0044AB84  80 01 00 C4 */	lwz r0, 0xc4(r1)
/* 8044DC48 0044AB88  83 E1 00 BC */	lwz r31, 0xbc(r1)
/* 8044DC4C 0044AB8C  83 C1 00 B8 */	lwz r30, 0xb8(r1)
/* 8044DC50 0044AB90  7C 08 03 A6 */	mtlr r0
/* 8044DC54 0044AB94  38 21 00 C0 */	addi r1, r1, 0xc0
/* 8044DC58 0044AB98  4E 80 00 20 */	blr 

.global THPGXYuv2RgbDraw
THPGXYuv2RgbDraw:
/* 8044DC5C 0044AB9C  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 8044DC60 0044ABA0  7C 08 02 A6 */	mflr r0
/* 8044DC64 0044ABA4  90 01 00 94 */	stw r0, 0x94(r1)
/* 8044DC68 0044ABA8  BF 01 00 70 */	stmw r24, 0x70(r1)
/* 8044DC6C 0044ABAC  7C 98 23 78 */	mr r24, r4
/* 8044DC70 0044ABB0  7C B9 2B 78 */	mr r25, r5
/* 8044DC74 0044ABB4  7C DE 33 78 */	mr r30, r6
/* 8044DC78 0044ABB8  7C FF 3B 78 */	mr r31, r7
/* 8044DC7C 0044ABBC  7D 5A 53 78 */	mr r26, r10
/* 8044DC80 0044ABC0  7C 64 1B 78 */	mr r4, r3
/* 8044DC84 0044ABC4  AB 61 00 9A */	lha r27, 0x9a(r1)
/* 8044DC88 0044ABC8  7D 1D 43 78 */	mr r29, r8
/* 8044DC8C 0044ABCC  55 05 04 3E */	clrlwi r5, r8, 0x10
/* 8044DC90 0044ABD0  7D 3C 4B 78 */	mr r28, r9
/* 8044DC94 0044ABD4  55 26 04 3E */	clrlwi r6, r9, 0x10
/* 8044DC98 0044ABD8  38 61 00 48 */	addi r3, r1, 0x48
/* 8044DC9C 0044ABDC  38 E0 00 01 */	li r7, 1
/* 8044DCA0 0044ABE0  39 00 00 00 */	li r8, 0
/* 8044DCA4 0044ABE4  39 20 00 00 */	li r9, 0
/* 8044DCA8 0044ABE8  39 40 00 00 */	li r10, 0
/* 8044DCAC 0044ABEC  4B C9 94 D1 */	bl GXInitTexObj
/* 8044DCB0 0044ABF0  C0 22 27 84 */	lfs f1, lbl_80520AE4@sda21(r2)
/* 8044DCB4 0044ABF4  38 61 00 48 */	addi r3, r1, 0x48
/* 8044DCB8 0044ABF8  38 80 00 00 */	li r4, 0
/* 8044DCBC 0044ABFC  38 A0 00 00 */	li r5, 0
/* 8044DCC0 0044AC00  FC 40 08 90 */	fmr f2, f1
/* 8044DCC4 0044AC04  38 C0 00 00 */	li r6, 0
/* 8044DCC8 0044AC08  FC 60 08 90 */	fmr f3, f1
/* 8044DCCC 0044AC0C  38 E0 00 00 */	li r7, 0
/* 8044DCD0 0044AC10  39 00 00 00 */	li r8, 0
/* 8044DCD4 0044AC14  4B C9 97 3D */	bl GXInitTexObjLOD
/* 8044DCD8 0044AC18  38 61 00 48 */	addi r3, r1, 0x48
/* 8044DCDC 0044AC1C  38 80 00 00 */	li r4, 0
/* 8044DCE0 0044AC20  4B C9 9A 31 */	bl GXLoadTexObj
/* 8044DCE4 0044AC24  7F A3 07 34 */	extsh r3, r29
/* 8044DCE8 0044AC28  7F 80 07 34 */	extsh r0, r28
/* 8044DCEC 0044AC2C  7C 7C 0E 70 */	srawi r28, r3, 1
/* 8044DCF0 0044AC30  7F 04 C3 78 */	mr r4, r24
/* 8044DCF4 0044AC34  7C 1D 0E 70 */	srawi r29, r0, 1
/* 8044DCF8 0044AC38  38 61 00 28 */	addi r3, r1, 0x28
/* 8044DCFC 0044AC3C  57 85 04 3E */	clrlwi r5, r28, 0x10
/* 8044DD00 0044AC40  38 E0 00 01 */	li r7, 1
/* 8044DD04 0044AC44  57 A6 04 3E */	clrlwi r6, r29, 0x10
/* 8044DD08 0044AC48  39 00 00 00 */	li r8, 0
/* 8044DD0C 0044AC4C  39 20 00 00 */	li r9, 0
/* 8044DD10 0044AC50  39 40 00 00 */	li r10, 0
/* 8044DD14 0044AC54  4B C9 94 69 */	bl GXInitTexObj
/* 8044DD18 0044AC58  C0 22 27 84 */	lfs f1, lbl_80520AE4@sda21(r2)
/* 8044DD1C 0044AC5C  38 61 00 28 */	addi r3, r1, 0x28
/* 8044DD20 0044AC60  38 80 00 00 */	li r4, 0
/* 8044DD24 0044AC64  38 A0 00 00 */	li r5, 0
/* 8044DD28 0044AC68  FC 40 08 90 */	fmr f2, f1
/* 8044DD2C 0044AC6C  38 C0 00 00 */	li r6, 0
/* 8044DD30 0044AC70  FC 60 08 90 */	fmr f3, f1
/* 8044DD34 0044AC74  38 E0 00 00 */	li r7, 0
/* 8044DD38 0044AC78  39 00 00 00 */	li r8, 0
/* 8044DD3C 0044AC7C  4B C9 96 D5 */	bl GXInitTexObjLOD
/* 8044DD40 0044AC80  38 61 00 28 */	addi r3, r1, 0x28
/* 8044DD44 0044AC84  38 80 00 01 */	li r4, 1
/* 8044DD48 0044AC88  4B C9 99 C9 */	bl GXLoadTexObj
/* 8044DD4C 0044AC8C  7F 24 CB 78 */	mr r4, r25
/* 8044DD50 0044AC90  38 61 00 08 */	addi r3, r1, 8
/* 8044DD54 0044AC94  57 85 04 3E */	clrlwi r5, r28, 0x10
/* 8044DD58 0044AC98  57 A6 04 3E */	clrlwi r6, r29, 0x10
/* 8044DD5C 0044AC9C  38 E0 00 01 */	li r7, 1
/* 8044DD60 0044ACA0  39 00 00 00 */	li r8, 0
/* 8044DD64 0044ACA4  39 20 00 00 */	li r9, 0
/* 8044DD68 0044ACA8  39 40 00 00 */	li r10, 0
/* 8044DD6C 0044ACAC  4B C9 94 11 */	bl GXInitTexObj
/* 8044DD70 0044ACB0  C0 22 27 84 */	lfs f1, lbl_80520AE4@sda21(r2)
/* 8044DD74 0044ACB4  38 61 00 08 */	addi r3, r1, 8
/* 8044DD78 0044ACB8  38 80 00 00 */	li r4, 0
/* 8044DD7C 0044ACBC  38 A0 00 00 */	li r5, 0
/* 8044DD80 0044ACC0  FC 40 08 90 */	fmr f2, f1
/* 8044DD84 0044ACC4  38 C0 00 00 */	li r6, 0
/* 8044DD88 0044ACC8  FC 60 08 90 */	fmr f3, f1
/* 8044DD8C 0044ACCC  38 E0 00 00 */	li r7, 0
/* 8044DD90 0044ACD0  39 00 00 00 */	li r8, 0
/* 8044DD94 0044ACD4  4B C9 96 7D */	bl GXInitTexObjLOD
/* 8044DD98 0044ACD8  38 61 00 08 */	addi r3, r1, 8
/* 8044DD9C 0044ACDC  38 80 00 02 */	li r4, 2
/* 8044DDA0 0044ACE0  4B C9 99 71 */	bl GXLoadTexObj
/* 8044DDA4 0044ACE4  38 60 00 80 */	li r3, 0x80
/* 8044DDA8 0044ACE8  38 80 00 07 */	li r4, 7
/* 8044DDAC 0044ACEC  38 A0 00 04 */	li r5, 4
/* 8044DDB0 0044ACF0  4B C9 7B D9 */	bl GXBegin
/* 8044DDB4 0044ACF4  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 8044DDB8 0044ACF8  7F E0 07 34 */	extsh r0, r31
/* 8044DDBC 0044ACFC  B3 C4 80 00 */	sth r30, 0xCC008000@l(r4)
/* 8044DDC0 0044AD00  7C C0 DA 14 */	add r6, r0, r27
/* 8044DDC4 0044AD04  38 60 00 00 */	li r3, 0
/* 8044DDC8 0044AD08  7F C5 07 34 */	extsh r5, r30
/* 8044DDCC 0044AD0C  B3 E4 80 00 */	sth r31, -0x8000(r4)
/* 8044DDD0 0044AD10  7F 40 07 34 */	extsh r0, r26
/* 8044DDD4 0044AD14  7C A5 02 14 */	add r5, r5, r0
/* 8044DDD8 0044AD18  B0 64 80 00 */	sth r3, -0x8000(r4)
/* 8044DDDC 0044AD1C  38 00 00 01 */	li r0, 1
/* 8044DDE0 0044AD20  B0 64 80 00 */	sth r3, -0x8000(r4)
/* 8044DDE4 0044AD24  B0 64 80 00 */	sth r3, -0x8000(r4)
/* 8044DDE8 0044AD28  B0 A4 80 00 */	sth r5, -0x8000(r4)
/* 8044DDEC 0044AD2C  B3 E4 80 00 */	sth r31, -0x8000(r4)
/* 8044DDF0 0044AD30  B0 64 80 00 */	sth r3, -0x8000(r4)
/* 8044DDF4 0044AD34  B0 04 80 00 */	sth r0, -0x8000(r4)
/* 8044DDF8 0044AD38  B0 64 80 00 */	sth r3, -0x8000(r4)
/* 8044DDFC 0044AD3C  B0 A4 80 00 */	sth r5, -0x8000(r4)
/* 8044DE00 0044AD40  B0 C4 80 00 */	sth r6, -0x8000(r4)
/* 8044DE04 0044AD44  B0 64 80 00 */	sth r3, -0x8000(r4)
/* 8044DE08 0044AD48  B0 04 80 00 */	sth r0, -0x8000(r4)
/* 8044DE0C 0044AD4C  B0 04 80 00 */	sth r0, -0x8000(r4)
/* 8044DE10 0044AD50  B3 C4 80 00 */	sth r30, -0x8000(r4)
/* 8044DE14 0044AD54  B0 C4 80 00 */	sth r6, -0x8000(r4)
/* 8044DE18 0044AD58  B0 64 80 00 */	sth r3, -0x8000(r4)
/* 8044DE1C 0044AD5C  B0 64 80 00 */	sth r3, -0x8000(r4)
/* 8044DE20 0044AD60  B0 04 80 00 */	sth r0, -0x8000(r4)
/* 8044DE24 0044AD64  BB 01 00 70 */	lmw r24, 0x70(r1)
/* 8044DE28 0044AD68  80 01 00 94 */	lwz r0, 0x94(r1)
/* 8044DE2C 0044AD6C  7C 08 03 A6 */	mtlr r0
/* 8044DE30 0044AD70  38 21 00 90 */	addi r1, r1, 0x90
/* 8044DE34 0044AD74  4E 80 00 20 */	blr 
