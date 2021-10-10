.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global calcLagrange__Q24Game9NsMathExpFPC10Vector3$$0f$$1fR10Vector3$$0f$$1
calcLagrange__Q24Game9NsMathExpFPC10Vector3$$0f$$1fR10Vector3$$0f$$1:
/* 8023D7B0 0023A6F0  C0 02 C2 A0 */	lfs f0, lbl_8051A600@sda21(r2)
/* 8023D7B4 0023A6F4  C0 42 C2 A4 */	lfs f2, lbl_8051A604@sda21(r2)
/* 8023D7B8 0023A6F8  C0 63 00 0C */	lfs f3, 0xc(r3)
/* 8023D7BC 0023A6FC  EC 01 00 28 */	fsubs f0, f1, f0
/* 8023D7C0 0023A700  C0 83 00 10 */	lfs f4, 0x10(r3)
/* 8023D7C4 0023A704  EC 41 10 28 */	fsubs f2, f1, f2
/* 8023D7C8 0023A708  EC C3 00 72 */	fmuls f6, f3, f1
/* 8023D7CC 0023A70C  C0 63 00 14 */	lfs f3, 0x14(r3)
/* 8023D7D0 0023A710  EC A4 00 72 */	fmuls f5, f4, f1
/* 8023D7D4 0023A714  EC 63 00 72 */	fmuls f3, f3, f1
/* 8023D7D8 0023A718  C1 82 C2 A8 */	lfs f12, lbl_8051A608@sda21(r2)
/* 8023D7DC 0023A71C  C0 E3 00 00 */	lfs f7, 0(r3)
/* 8023D7E0 0023A720  C0 83 00 04 */	lfs f4, 4(r3)
/* 8023D7E4 0023A724  ED 22 01 B2 */	fmuls f9, f2, f6
/* 8023D7E8 0023A728  ED 0C 01 F2 */	fmuls f8, f12, f7
/* 8023D7EC 0023A72C  C1 43 00 18 */	lfs f10, 0x18(r3)
/* 8023D7F0 0023A730  EC EC 01 32 */	fmuls f7, f12, f4
/* 8023D7F4 0023A734  C0 83 00 08 */	lfs f4, 8(r3)
/* 8023D7F8 0023A738  EC C2 01 72 */	fmuls f6, f2, f5
/* 8023D7FC 0023A73C  ED 6C 02 B2 */	fmuls f11, f12, f10
/* 8023D800 0023A740  ED 48 00 32 */	fmuls f10, f8, f0
/* 8023D804 0023A744  C1 03 00 1C */	lfs f8, 0x1c(r3)
/* 8023D808 0023A748  EC 8C 01 32 */	fmuls f4, f12, f4
/* 8023D80C 0023A74C  C0 A3 00 20 */	lfs f5, 0x20(r3)
/* 8023D810 0023A750  ED 0C 02 32 */	fmuls f8, f12, f8
/* 8023D814 0023A754  EC E7 00 32 */	fmuls f7, f7, f0
/* 8023D818 0023A758  EC AC 01 72 */	fmuls f5, f12, f5
/* 8023D81C 0023A75C  ED 6B 00 72 */	fmuls f11, f11, f1
/* 8023D820 0023A760  ED 22 4A B8 */	fmsubs f9, f2, f10, f9
/* 8023D824 0023A764  EC 84 00 32 */	fmuls f4, f4, f0
/* 8023D828 0023A768  EC 62 00 F2 */	fmuls f3, f2, f3
/* 8023D82C 0023A76C  ED 20 4A FA */	fmadds f9, f0, f11, f9
/* 8023D830 0023A770  ED 08 00 72 */	fmuls f8, f8, f1
/* 8023D834 0023A774  EC C2 31 F8 */	fmsubs f6, f2, f7, f6
/* 8023D838 0023A778  EC A5 00 72 */	fmuls f5, f5, f1
/* 8023D83C 0023A77C  D1 24 00 00 */	stfs f9, 0(r4)
/* 8023D840 0023A780  EC 22 19 38 */	fmsubs f1, f2, f4, f3
/* 8023D844 0023A784  EC 40 32 3A */	fmadds f2, f0, f8, f6
/* 8023D848 0023A788  EC 00 09 7A */	fmadds f0, f0, f5, f1
/* 8023D84C 0023A78C  D0 44 00 04 */	stfs f2, 4(r4)
/* 8023D850 0023A790  D0 04 00 08 */	stfs f0, 8(r4)
/* 8023D854 0023A794  4E 80 00 20 */	blr 

.global calcJointPos__Q24Game9NsMathExpFRC10Vector3$$0f$$1RC10Vector3$$0f$$1ffR10Vector3$$0f$$1R10Vector3$$0f$$1
calcJointPos__Q24Game9NsMathExpFRC10Vector3$$0f$$1RC10Vector3$$0f$$1ffR10Vector3$$0f$$1R10Vector3$$0f$$1:
/* 8023D858 0023A798  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8023D85C 0023A79C  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8023D860 0023A7A0  F3 E1 00 28 */	psq_st f31, 40(r1), 0, qr0
/* 8023D864 0023A7A4  DB C1 00 10 */	stfd f30, 0x10(r1)
/* 8023D868 0023A7A8  F3 C1 00 18 */	psq_st f30, 24(r1), 0, qr0
/* 8023D86C 0023A7AC  C0 04 00 04 */	lfs f0, 4(r4)
/* 8023D870 0023A7B0  EC A1 00 72 */	fmuls f5, f1, f1
/* 8023D874 0023A7B4  C1 03 00 04 */	lfs f8, 4(r3)
/* 8023D878 0023A7B8  EC 82 00 B2 */	fmuls f4, f2, f2
/* 8023D87C 0023A7BC  C0 64 00 00 */	lfs f3, 0(r4)
/* 8023D880 0023A7C0  EC 20 40 28 */	fsubs f1, f0, f8
/* 8023D884 0023A7C4  C0 E3 00 00 */	lfs f7, 0(r3)
/* 8023D888 0023A7C8  C0 44 00 08 */	lfs f2, 8(r4)
/* 8023D88C 0023A7CC  EC 03 38 28 */	fsubs f0, f3, f7
/* 8023D890 0023A7D0  C1 43 00 08 */	lfs f10, 8(r3)
/* 8023D894 0023A7D4  EC C1 00 72 */	fmuls f6, f1, f1
/* 8023D898 0023A7D8  EC 42 50 28 */	fsubs f2, f2, f10
/* 8023D89C 0023A7DC  C0 62 C2 AC */	lfs f3, lbl_8051A60C@sda21(r2)
/* 8023D8A0 0023A7E0  EC C0 30 3A */	fmadds f6, f0, f0, f6
/* 8023D8A4 0023A7E4  ED 62 30 BA */	fmadds f11, f2, f2, f6
/* 8023D8A8 0023A7E8  FC 0B 18 40 */	fcmpo cr0, f11, f3
/* 8023D8AC 0023A7EC  41 80 01 00 */	blt lbl_8023D9AC
/* 8023D8B0 0023A7F0  C0 C2 C2 A8 */	lfs f6, lbl_8051A608@sda21(r2)
/* 8023D8B4 0023A7F4  EC 65 20 28 */	fsubs f3, f5, f4
/* 8023D8B8 0023A7F8  C1 22 C2 B0 */	lfs f9, lbl_8051A610@sda21(r2)
/* 8023D8BC 0023A7FC  EC C6 58 24 */	fdivs f6, f6, f11
/* 8023D8C0 0023A800  EC 6B 18 2A */	fadds f3, f11, f3
/* 8023D8C4 0023A804  EC 66 00 F2 */	fmuls f3, f6, f3
/* 8023D8C8 0023A808  ED 83 38 3A */	fmadds f12, f3, f0, f7
/* 8023D8CC 0023A80C  ED A3 40 7A */	fmadds f13, f3, f1, f8
/* 8023D8D0 0023A810  EC 63 50 BA */	fmadds f3, f3, f2, f10
/* 8023D8D4 0023A814  EC CC 38 28 */	fsubs f6, f12, f7
/* 8023D8D8 0023A818  EC ED 40 28 */	fsubs f7, f13, f8
/* 8023D8DC 0023A81C  ED 03 50 28 */	fsubs f8, f3, f10
/* 8023D8E0 0023A820  EC C6 29 BC */	fnmsubs f6, f6, f6, f5
/* 8023D8E4 0023A824  EC C7 31 FC */	fnmsubs f6, f7, f7, f6
/* 8023D8E8 0023A828  EF C8 32 3C */	fnmsubs f30, f8, f8, f6
/* 8023D8EC 0023A82C  FC 1E 48 40 */	fcmpo cr0, f30, f9
/* 8023D8F0 0023A830  4C 40 13 82 */	cror 2, 0, 2
/* 8023D8F4 0023A834  41 82 00 B8 */	beq lbl_8023D9AC
/* 8023D8F8 0023A838  C3 E5 00 00 */	lfs f31, 0(r5)
/* 8023D8FC 0023A83C  C1 65 00 04 */	lfs f11, 4(r5)
/* 8023D900 0023A840  EC FF 00 B2 */	fmuls f7, f31, f2
/* 8023D904 0023A844  C1 45 00 08 */	lfs f10, 8(r5)
/* 8023D908 0023A848  EC CB 00 32 */	fmuls f6, f11, f0
/* 8023D90C 0023A84C  ED 0A 00 72 */	fmuls f8, f10, f1
/* 8023D910 0023A850  ED 4A 38 38 */	fmsubs f10, f10, f0, f7
/* 8023D914 0023A854  EF FF 30 78 */	fmsubs f31, f31, f1, f6
/* 8023D918 0023A858  ED 6B 40 B8 */	fmsubs f11, f11, f2, f8
/* 8023D91C 0023A85C  ED 02 02 B2 */	fmuls f8, f2, f10
/* 8023D920 0023A860  EC E0 07 F2 */	fmuls f7, f0, f31
/* 8023D924 0023A864  EC C1 02 F2 */	fmuls f6, f1, f11
/* 8023D928 0023A868  ED 01 47 F8 */	fmsubs f8, f1, f31, f8
/* 8023D92C 0023A86C  EC E2 3A F8 */	fmsubs f7, f2, f11, f7
/* 8023D930 0023A870  EC C0 32 B8 */	fmsubs f6, f0, f10, f6
/* 8023D934 0023A874  D1 05 00 00 */	stfs f8, 0(r5)
/* 8023D938 0023A878  D0 E5 00 04 */	stfs f7, 4(r5)
/* 8023D93C 0023A87C  D0 C5 00 08 */	stfs f6, 8(r5)
/* 8023D940 0023A880  C1 45 00 00 */	lfs f10, 0(r5)
/* 8023D944 0023A884  C0 C5 00 04 */	lfs f6, 4(r5)
/* 8023D948 0023A888  EC EA 02 B2 */	fmuls f7, f10, f10
/* 8023D94C 0023A88C  C1 05 00 08 */	lfs f8, 8(r5)
/* 8023D950 0023A890  EC C6 01 B2 */	fmuls f6, f6, f6
/* 8023D954 0023A894  ED 08 02 32 */	fmuls f8, f8, f8
/* 8023D958 0023A898  EC C7 30 2A */	fadds f6, f7, f6
/* 8023D95C 0023A89C  EC C8 30 2A */	fadds f6, f8, f6
/* 8023D960 0023A8A0  FC 09 30 00 */	fcmpu cr0, f9, f6
/* 8023D964 0023A8A4  41 82 00 48 */	beq lbl_8023D9AC
/* 8023D968 0023A8A8  EC 3E 30 24 */	fdivs f1, f30, f6
/* 8023D96C 0023A8AC  FC 01 48 40 */	fcmpo cr0, f1, f9
/* 8023D970 0023A8B0  40 81 00 14 */	ble lbl_8023D984
/* 8023D974 0023A8B4  40 81 00 14 */	ble lbl_8023D988
/* 8023D978 0023A8B8  FC 00 08 34 */	frsqrte f0, f1
/* 8023D97C 0023A8BC  EC 20 00 72 */	fmuls f1, f0, f1
/* 8023D980 0023A8C0  48 00 00 08 */	b lbl_8023D988
lbl_8023D984:
/* 8023D984 0023A8C4  FC 20 48 90 */	fmr f1, f9
lbl_8023D988:
/* 8023D988 0023A8C8  EC 01 62 BA */	fmadds f0, f1, f10, f12
/* 8023D98C 0023A8CC  D0 06 00 00 */	stfs f0, 0(r6)
/* 8023D990 0023A8D0  C0 05 00 04 */	lfs f0, 4(r5)
/* 8023D994 0023A8D4  EC 01 68 3A */	fmadds f0, f1, f0, f13
/* 8023D998 0023A8D8  D0 06 00 04 */	stfs f0, 4(r6)
/* 8023D99C 0023A8DC  C0 05 00 08 */	lfs f0, 8(r5)
/* 8023D9A0 0023A8E0  EC 01 18 3A */	fmadds f0, f1, f0, f3
/* 8023D9A4 0023A8E4  D0 06 00 08 */	stfs f0, 8(r6)
/* 8023D9A8 0023A8E8  48 00 00 70 */	b lbl_8023DA18
lbl_8023D9AC:
/* 8023D9AC 0023A8EC  C0 E2 C2 B0 */	lfs f7, lbl_8051A610@sda21(r2)
/* 8023D9B0 0023A8F0  FC 05 38 40 */	fcmpo cr0, f5, f7
/* 8023D9B4 0023A8F4  40 81 00 18 */	ble lbl_8023D9CC
/* 8023D9B8 0023A8F8  40 81 00 10 */	ble lbl_8023D9C8
/* 8023D9BC 0023A8FC  FC 60 28 34 */	frsqrte f3, f5
/* 8023D9C0 0023A900  EC E3 01 72 */	fmuls f7, f3, f5
/* 8023D9C4 0023A904  48 00 00 08 */	b lbl_8023D9CC
lbl_8023D9C8:
/* 8023D9C8 0023A908  FC E0 28 90 */	fmr f7, f5
lbl_8023D9CC:
/* 8023D9CC 0023A90C  C0 62 C2 B0 */	lfs f3, lbl_8051A610@sda21(r2)
/* 8023D9D0 0023A910  FC 04 18 40 */	fcmpo cr0, f4, f3
/* 8023D9D4 0023A914  40 81 00 18 */	ble lbl_8023D9EC
/* 8023D9D8 0023A918  40 81 00 10 */	ble lbl_8023D9E8
/* 8023D9DC 0023A91C  FC 60 20 34 */	frsqrte f3, f4
/* 8023D9E0 0023A920  EC 63 01 32 */	fmuls f3, f3, f4
/* 8023D9E4 0023A924  48 00 00 08 */	b lbl_8023D9EC
lbl_8023D9E8:
/* 8023D9E8 0023A928  FC 60 20 90 */	fmr f3, f4
lbl_8023D9EC:
/* 8023D9EC 0023A92C  EC C7 18 2A */	fadds f6, f7, f3
/* 8023D9F0 0023A930  C0 A3 00 00 */	lfs f5, 0(r3)
/* 8023D9F4 0023A934  C0 83 00 04 */	lfs f4, 4(r3)
/* 8023D9F8 0023A938  C0 63 00 08 */	lfs f3, 8(r3)
/* 8023D9FC 0023A93C  EC C7 30 24 */	fdivs f6, f7, f6
/* 8023DA00 0023A940  EC A6 28 3A */	fmadds f5, f6, f0, f5
/* 8023DA04 0023A944  EC 26 20 7A */	fmadds f1, f6, f1, f4
/* 8023DA08 0023A948  EC 06 18 BA */	fmadds f0, f6, f2, f3
/* 8023DA0C 0023A94C  D0 A6 00 00 */	stfs f5, 0(r6)
/* 8023DA10 0023A950  D0 26 00 04 */	stfs f1, 4(r6)
/* 8023DA14 0023A954  D0 06 00 08 */	stfs f0, 8(r6)
lbl_8023DA18:
/* 8023DA18 0023A958  E3 E1 00 28 */	psq_l f31, 40(r1), 0, qr0
/* 8023DA1C 0023A95C  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8023DA20 0023A960  E3 C1 00 18 */	psq_l f30, 24(r1), 0, qr0
/* 8023DA24 0023A964  CB C1 00 10 */	lfd f30, 0x10(r1)
/* 8023DA28 0023A968  38 21 00 30 */	addi r1, r1, 0x30
/* 8023DA2C 0023A96C  4E 80 00 20 */	blr 
