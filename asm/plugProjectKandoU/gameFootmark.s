.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global __ct__Q24Game8FootmarkFv
__ct__Q24Game8FootmarkFv:
/* 801B4794 001B16D4  C0 02 B0 B8 */	lfs f0, lbl_80519418@sda21(r2)
/* 801B4798 001B16D8  38 00 00 00 */	li r0, 0
/* 801B479C 001B16DC  D0 03 00 00 */	stfs f0, 0(r3)
/* 801B47A0 001B16E0  D0 03 00 04 */	stfs f0, 4(r3)
/* 801B47A4 001B16E4  D0 03 00 08 */	stfs f0, 8(r3)
/* 801B47A8 001B16E8  90 03 00 0C */	stw r0, 0xc(r3)
/* 801B47AC 001B16EC  4E 80 00 20 */	blr 

.global __ct__Q24Game9FootmarksFv
__ct__Q24Game9FootmarksFv:
/* 801B47B0 001B16F0  38 00 00 00 */	li r0, 0
/* 801B47B4 001B16F4  90 03 00 00 */	stw r0, 0(r3)
/* 801B47B8 001B16F8  90 03 00 0C */	stw r0, 0xc(r3)
/* 801B47BC 001B16FC  90 03 00 08 */	stw r0, 8(r3)
/* 801B47C0 001B1700  90 03 00 04 */	stw r0, 4(r3)
/* 801B47C4 001B1704  90 03 00 10 */	stw r0, 0x10(r3)
/* 801B47C8 001B1708  4E 80 00 20 */	blr 

.global alloc__Q24Game9FootmarksFi
alloc__Q24Game9FootmarksFi:
/* 801B47CC 001B170C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 801B47D0 001B1710  7C 08 02 A6 */	mflr r0
/* 801B47D4 001B1714  90 01 00 14 */	stw r0, 0x14(r1)
/* 801B47D8 001B1718  93 E1 00 0C */	stw r31, 0xc(r1)
/* 801B47DC 001B171C  7C 9F 23 78 */	mr r31, r4
/* 801B47E0 001B1720  93 C1 00 08 */	stw r30, 8(r1)
/* 801B47E4 001B1724  7C 7E 1B 78 */	mr r30, r3
/* 801B47E8 001B1728  54 83 20 36 */	slwi r3, r4, 4
/* 801B47EC 001B172C  38 63 00 10 */	addi r3, r3, 0x10
/* 801B47F0 001B1730  4B E6 F7 BD */	bl __nwa__FUl
/* 801B47F4 001B1734  3C 80 80 1B */	lis r4, __ct__Q24Game8FootmarkFv@ha
/* 801B47F8 001B1738  7F E7 FB 78 */	mr r7, r31
/* 801B47FC 001B173C  38 84 47 94 */	addi r4, r4, __ct__Q24Game8FootmarkFv@l
/* 801B4800 001B1740  38 A0 00 00 */	li r5, 0
/* 801B4804 001B1744  38 C0 00 10 */	li r6, 0x10
/* 801B4808 001B1748  4B F0 D1 E9 */	bl __construct_new_array
/* 801B480C 001B174C  90 7E 00 00 */	stw r3, 0(r30)
/* 801B4810 001B1750  38 00 00 00 */	li r0, 0
/* 801B4814 001B1754  93 FE 00 0C */	stw r31, 0xc(r30)
/* 801B4818 001B1758  90 1E 00 08 */	stw r0, 8(r30)
/* 801B481C 001B175C  90 1E 00 04 */	stw r0, 4(r30)
/* 801B4820 001B1760  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 801B4824 001B1764  83 C1 00 08 */	lwz r30, 8(r1)
/* 801B4828 001B1768  80 01 00 14 */	lwz r0, 0x14(r1)
/* 801B482C 001B176C  7C 08 03 A6 */	mtlr r0
/* 801B4830 001B1770  38 21 00 10 */	addi r1, r1, 0x10
/* 801B4834 001B1774  4E 80 00 20 */	blr 

.global add__Q24Game9FootmarksFRQ24Game8Footmark
add__Q24Game9FootmarksFRQ24Game8Footmark:
/* 801B4838 001B1778  C0 04 00 00 */	lfs f0, 0(r4)
/* 801B483C 001B177C  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 801B4840 001B1780  C0 04 00 04 */	lfs f0, 4(r4)
/* 801B4844 001B1784  D0 03 00 18 */	stfs f0, 0x18(r3)
/* 801B4848 001B1788  C0 04 00 08 */	lfs f0, 8(r4)
/* 801B484C 001B178C  D0 03 00 1C */	stfs f0, 0x1c(r3)
/* 801B4850 001B1790  80 03 00 08 */	lwz r0, 8(r3)
/* 801B4854 001B1794  2C 00 00 02 */	cmpwi r0, 2
/* 801B4858 001B1798  41 80 00 8C */	blt lbl_801B48E4
/* 801B485C 001B179C  80 E3 00 0C */	lwz r7, 0xc(r3)
/* 801B4860 001B17A0  80 A3 00 04 */	lwz r5, 4(r3)
/* 801B4864 001B17A4  38 07 FF FF */	addi r0, r7, -1
/* 801B4868 001B17A8  80 C3 00 00 */	lwz r6, 0(r3)
/* 801B486C 001B17AC  7C A5 02 14 */	add r5, r5, r0
/* 801B4870 001B17B0  C0 44 00 04 */	lfs f2, 4(r4)
/* 801B4874 001B17B4  7C 05 3B D6 */	divw r0, r5, r7
/* 801B4878 001B17B8  C0 84 00 08 */	lfs f4, 8(r4)
/* 801B487C 001B17BC  C0 24 00 00 */	lfs f1, 0(r4)
/* 801B4880 001B17C0  C0 02 B0 B8 */	lfs f0, lbl_80519418@sda21(r2)
/* 801B4884 001B17C4  7C 00 39 D6 */	mullw r0, r0, r7
/* 801B4888 001B17C8  7C 00 28 50 */	subf r0, r0, r5
/* 801B488C 001B17CC  54 00 20 36 */	slwi r0, r0, 4
/* 801B4890 001B17D0  7C A6 02 14 */	add r5, r6, r0
/* 801B4894 001B17D4  C0 65 00 04 */	lfs f3, 4(r5)
/* 801B4898 001B17D8  C0 A5 00 08 */	lfs f5, 8(r5)
/* 801B489C 001B17DC  EC 63 10 28 */	fsubs f3, f3, f2
/* 801B48A0 001B17E0  C0 45 00 00 */	lfs f2, 0(r5)
/* 801B48A4 001B17E4  EC 85 20 28 */	fsubs f4, f5, f4
/* 801B48A8 001B17E8  EC 22 08 28 */	fsubs f1, f2, f1
/* 801B48AC 001B17EC  EC 43 00 F2 */	fmuls f2, f3, f3
/* 801B48B0 001B17F0  EC 64 01 32 */	fmuls f3, f4, f4
/* 801B48B4 001B17F4  EC 21 10 7A */	fmadds f1, f1, f1, f2
/* 801B48B8 001B17F8  EC 23 08 2A */	fadds f1, f3, f1
/* 801B48BC 001B17FC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 801B48C0 001B1800  40 81 00 14 */	ble lbl_801B48D4
/* 801B48C4 001B1804  40 81 00 14 */	ble lbl_801B48D8
/* 801B48C8 001B1808  FC 00 08 34 */	frsqrte f0, f1
/* 801B48CC 001B180C  EC 20 00 72 */	fmuls f1, f0, f1
/* 801B48D0 001B1810  48 00 00 08 */	b lbl_801B48D8
lbl_801B48D4:
/* 801B48D4 001B1814  FC 20 00 90 */	fmr f1, f0
lbl_801B48D8:
/* 801B48D8 001B1818  C0 02 B0 BC */	lfs f0, lbl_8051941C@sda21(r2)
/* 801B48DC 001B181C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 801B48E0 001B1820  4D 80 00 20 */	bltlr 
lbl_801B48E4:
/* 801B48E4 001B1824  80 CD 93 E8 */	lwz r6, gameSystem__4Game@sda21(r13)
/* 801B48E8 001B1828  80 03 00 04 */	lwz r0, 4(r3)
/* 801B48EC 001B182C  80 A3 00 00 */	lwz r5, 0(r3)
/* 801B48F0 001B1830  54 00 20 36 */	slwi r0, r0, 4
/* 801B48F4 001B1834  80 C6 00 50 */	lwz r6, 0x50(r6)
/* 801B48F8 001B1838  C0 04 00 00 */	lfs f0, 0(r4)
/* 801B48FC 001B183C  7C A5 02 14 */	add r5, r5, r0
/* 801B4900 001B1840  D0 05 00 00 */	stfs f0, 0(r5)
/* 801B4904 001B1844  C0 04 00 04 */	lfs f0, 4(r4)
/* 801B4908 001B1848  D0 05 00 04 */	stfs f0, 4(r5)
/* 801B490C 001B184C  C0 04 00 08 */	lfs f0, 8(r4)
/* 801B4910 001B1850  D0 05 00 08 */	stfs f0, 8(r5)
/* 801B4914 001B1854  80 04 00 0C */	lwz r0, 0xc(r4)
/* 801B4918 001B1858  90 05 00 0C */	stw r0, 0xc(r5)
/* 801B491C 001B185C  80 03 00 04 */	lwz r0, 4(r3)
/* 801B4920 001B1860  80 83 00 00 */	lwz r4, 0(r3)
/* 801B4924 001B1864  54 00 20 36 */	slwi r0, r0, 4
/* 801B4928 001B1868  7C 84 02 14 */	add r4, r4, r0
/* 801B492C 001B186C  90 C4 00 0C */	stw r6, 0xc(r4)
/* 801B4930 001B1870  80 A3 00 04 */	lwz r5, 4(r3)
/* 801B4934 001B1874  80 83 00 0C */	lwz r4, 0xc(r3)
/* 801B4938 001B1878  38 A5 00 01 */	addi r5, r5, 1
/* 801B493C 001B187C  7C 05 23 D6 */	divw r0, r5, r4
/* 801B4940 001B1880  7C 00 21 D6 */	mullw r0, r0, r4
/* 801B4944 001B1884  7C 00 28 50 */	subf r0, r0, r5
/* 801B4948 001B1888  90 03 00 04 */	stw r0, 4(r3)
/* 801B494C 001B188C  80 83 00 08 */	lwz r4, 8(r3)
/* 801B4950 001B1890  80 03 00 0C */	lwz r0, 0xc(r3)
/* 801B4954 001B1894  7C 04 00 00 */	cmpw r4, r0
/* 801B4958 001B1898  40 80 00 0C */	bge lbl_801B4964
/* 801B495C 001B189C  38 04 00 01 */	addi r0, r4, 1
/* 801B4960 001B18A0  90 03 00 08 */	stw r0, 8(r3)
lbl_801B4964:
/* 801B4964 001B18A4  90 C3 00 10 */	stw r6, 0x10(r3)
/* 801B4968 001B18A8  4E 80 00 20 */	blr 

.global get__Q24Game9FootmarksFi
get__Q24Game9FootmarksFi:
/* 801B496C 001B18AC  2C 04 00 00 */	cmpwi r4, 0
/* 801B4970 001B18B0  41 80 00 10 */	blt lbl_801B4980
/* 801B4974 001B18B4  80 03 00 08 */	lwz r0, 8(r3)
/* 801B4978 001B18B8  7C 04 00 00 */	cmpw r4, r0
/* 801B497C 001B18BC  41 80 00 0C */	blt lbl_801B4988
lbl_801B4980:
/* 801B4980 001B18C0  38 60 00 00 */	li r3, 0
/* 801B4984 001B18C4  4E 80 00 20 */	blr 
lbl_801B4988:
/* 801B4988 001B18C8  80 C3 00 0C */	lwz r6, 0xc(r3)
/* 801B498C 001B18CC  38 84 00 01 */	addi r4, r4, 1
/* 801B4990 001B18D0  80 03 00 04 */	lwz r0, 4(r3)
/* 801B4994 001B18D4  80 A3 00 00 */	lwz r5, 0(r3)
/* 801B4998 001B18D8  7C 06 02 14 */	add r0, r6, r0
/* 801B499C 001B18DC  7C 64 00 50 */	subf r3, r4, r0
/* 801B49A0 001B18E0  7C 03 33 D6 */	divw r0, r3, r6
/* 801B49A4 001B18E4  7C 00 31 D6 */	mullw r0, r0, r6
/* 801B49A8 001B18E8  7C 00 18 50 */	subf r0, r0, r3
/* 801B49AC 001B18EC  54 00 20 36 */	slwi r0, r0, 4
/* 801B49B0 001B18F0  7C 65 02 14 */	add r3, r5, r0
/* 801B49B4 001B18F4  4E 80 00 20 */	blr 

.global findNearest2__Q24Game9FootmarksFR10Vector3$$0f$$1i
findNearest2__Q24Game9FootmarksFR10Vector3$$0f$$1i:
/* 801B49B8 001B18F8  80 C3 00 08 */	lwz r6, 8(r3)
/* 801B49BC 001B18FC  39 00 FF FF */	li r8, -1
/* 801B49C0 001B1900  C0 A2 B0 C0 */	lfs f5, lbl_80519420@sda21(r2)
/* 801B49C4 001B1904  39 20 00 00 */	li r9, 0
/* 801B49C8 001B1908  34 06 FF FF */	addic. r0, r6, -1
/* 801B49CC 001B190C  7C 09 03 A6 */	mtctr r0
/* 801B49D0 001B1910  40 81 00 90 */	ble lbl_801B4A60
lbl_801B49D4:
/* 801B49D4 001B1914  80 03 00 04 */	lwz r0, 4(r3)
/* 801B49D8 001B1918  2C 05 FF FF */	cmpwi r5, -1
/* 801B49DC 001B191C  80 C3 00 0C */	lwz r6, 0xc(r3)
/* 801B49E0 001B1920  7C E0 4A 14 */	add r7, r0, r9
/* 801B49E4 001B1924  7C 07 33 D6 */	divw r0, r7, r6
/* 801B49E8 001B1928  7C 00 31 D6 */	mullw r0, r0, r6
/* 801B49EC 001B192C  7D 40 38 50 */	subf r10, r0, r7
/* 801B49F0 001B1930  41 82 00 1C */	beq lbl_801B4A0C
/* 801B49F4 001B1934  55 46 20 36 */	slwi r6, r10, 4
/* 801B49F8 001B1938  80 E3 00 00 */	lwz r7, 0(r3)
/* 801B49FC 001B193C  38 06 00 0C */	addi r0, r6, 0xc
/* 801B4A00 001B1940  7C 07 00 2E */	lwzx r0, r7, r0
/* 801B4A04 001B1944  7C 00 28 00 */	cmpw r0, r5
/* 801B4A08 001B1948  40 81 00 50 */	ble lbl_801B4A58
lbl_801B4A0C:
/* 801B4A0C 001B194C  80 C3 00 00 */	lwz r6, 0(r3)
/* 801B4A10 001B1950  55 40 20 36 */	slwi r0, r10, 4
/* 801B4A14 001B1954  C0 64 00 04 */	lfs f3, 4(r4)
/* 801B4A18 001B1958  7C C6 02 14 */	add r6, r6, r0
/* 801B4A1C 001B195C  C0 24 00 00 */	lfs f1, 0(r4)
/* 801B4A20 001B1960  C0 46 00 04 */	lfs f2, 4(r6)
/* 801B4A24 001B1964  C0 06 00 00 */	lfs f0, 0(r6)
/* 801B4A28 001B1968  EC 83 10 28 */	fsubs f4, f3, f2
/* 801B4A2C 001B196C  C0 64 00 08 */	lfs f3, 8(r4)
/* 801B4A30 001B1970  C0 46 00 08 */	lfs f2, 8(r6)
/* 801B4A34 001B1974  EC 21 00 28 */	fsubs f1, f1, f0
/* 801B4A38 001B1978  EC 04 01 32 */	fmuls f0, f4, f4
/* 801B4A3C 001B197C  EC 43 10 28 */	fsubs f2, f3, f2
/* 801B4A40 001B1980  EC 01 00 7A */	fmadds f0, f1, f1, f0
/* 801B4A44 001B1984  EC 02 00 BA */	fmadds f0, f2, f2, f0
/* 801B4A48 001B1988  FC 00 28 40 */	fcmpo cr0, f0, f5
/* 801B4A4C 001B198C  40 80 00 0C */	bge lbl_801B4A58
/* 801B4A50 001B1990  FC A0 00 90 */	fmr f5, f0
/* 801B4A54 001B1994  7D 48 53 78 */	mr r8, r10
lbl_801B4A58:
/* 801B4A58 001B1998  39 29 00 01 */	addi r9, r9, 1
/* 801B4A5C 001B199C  42 00 FF 78 */	bdnz lbl_801B49D4
lbl_801B4A60:
/* 801B4A60 001B19A0  2C 08 FF FF */	cmpwi r8, -1
/* 801B4A64 001B19A4  41 82 00 14 */	beq lbl_801B4A78
/* 801B4A68 001B19A8  80 63 00 00 */	lwz r3, 0(r3)
/* 801B4A6C 001B19AC  55 00 20 36 */	slwi r0, r8, 4
/* 801B4A70 001B19B0  7C 63 02 14 */	add r3, r3, r0
/* 801B4A74 001B19B4  4E 80 00 20 */	blr 
lbl_801B4A78:
/* 801B4A78 001B19B8  38 60 00 00 */	li r3, 0
/* 801B4A7C 001B19BC  4E 80 00 20 */	blr 
