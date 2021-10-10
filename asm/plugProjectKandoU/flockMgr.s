.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global update__Q24Game12BaseFlockMgrFv
update__Q24Game12BaseFlockMgrFv:
/* 8020EADC 0020BA1C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8020EAE0 0020BA20  7C 08 02 A6 */	mflr r0
/* 8020EAE4 0020BA24  90 01 00 24 */	stw r0, 0x24(r1)
/* 8020EAE8 0020BA28  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8020EAEC 0020BA2C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8020EAF0 0020BA30  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8020EAF4 0020BA34  93 81 00 10 */	stw r28, 0x10(r1)
/* 8020EAF8 0020BA38  7C 7C 1B 78 */	mr r28, r3
/* 8020EAFC 0020BA3C  81 83 00 00 */	lwz r12, 0(r3)
/* 8020EB00 0020BA40  81 8C 00 20 */	lwz r12, 0x20(r12)
/* 8020EB04 0020BA44  7D 89 03 A6 */	mtctr r12
/* 8020EB08 0020BA48  4E 80 04 21 */	bctrl 
/* 8020EB0C 0020BA4C  80 6D 9A EC */	lwz r3, sys@sda21(r13)
/* 8020EB10 0020BA50  3B A0 00 00 */	li r29, 0
/* 8020EB14 0020BA54  83 C3 00 24 */	lwz r30, 0x24(r3)
/* 8020EB18 0020BA58  48 00 00 64 */	b lbl_8020EB7C
lbl_8020EB1C:
/* 8020EB1C 0020BA5C  7F C3 F3 78 */	mr r3, r30
/* 8020EB20 0020BA60  7F A4 EB 78 */	mr r4, r29
/* 8020EB24 0020BA64  48 21 6A CD */	bl getViewport__8GraphicsFi
/* 8020EB28 0020BA68  7C 7F 1B 78 */	mr r31, r3
/* 8020EB2C 0020BA6C  48 21 67 15 */	bl viewable__8ViewportFv
/* 8020EB30 0020BA70  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020EB34 0020BA74  40 82 00 14 */	bne lbl_8020EB48
/* 8020EB38 0020BA78  38 1D 00 1C */	addi r0, r29, 0x1c
/* 8020EB3C 0020BA7C  38 60 00 00 */	li r3, 0
/* 8020EB40 0020BA80  7C 7C 01 AE */	stbx r3, r28, r0
/* 8020EB44 0020BA84  48 00 00 34 */	b lbl_8020EB78
lbl_8020EB48:
/* 8020EB48 0020BA88  80 7F 00 44 */	lwz r3, 0x44(r31)
/* 8020EB4C 0020BA8C  38 9C 00 0C */	addi r4, r28, 0xc
/* 8020EB50 0020BA90  48 20 B6 41 */	bl isVisible__9CullPlaneFRQ23Sys6Sphere
/* 8020EB54 0020BA94  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020EB58 0020BA98  41 82 00 14 */	beq lbl_8020EB6C
/* 8020EB5C 0020BA9C  38 1D 00 1C */	addi r0, r29, 0x1c
/* 8020EB60 0020BAA0  38 60 00 01 */	li r3, 1
/* 8020EB64 0020BAA4  7C 7C 01 AE */	stbx r3, r28, r0
/* 8020EB68 0020BAA8  48 00 00 10 */	b lbl_8020EB78
lbl_8020EB6C:
/* 8020EB6C 0020BAAC  38 1D 00 1C */	addi r0, r29, 0x1c
/* 8020EB70 0020BAB0  38 60 00 00 */	li r3, 0
/* 8020EB74 0020BAB4  7C 7C 01 AE */	stbx r3, r28, r0
lbl_8020EB78:
/* 8020EB78 0020BAB8  3B BD 00 01 */	addi r29, r29, 1
lbl_8020EB7C:
/* 8020EB7C 0020BABC  80 1E 02 64 */	lwz r0, 0x264(r30)
/* 8020EB80 0020BAC0  7C 1D 00 00 */	cmpw r29, r0
/* 8020EB84 0020BAC4  41 80 FF 98 */	blt lbl_8020EB1C
/* 8020EB88 0020BAC8  7F 83 E3 78 */	mr r3, r28
/* 8020EB8C 0020BACC  81 9C 00 00 */	lwz r12, 0(r28)
/* 8020EB90 0020BAD0  81 8C 00 1C */	lwz r12, 0x1c(r12)
/* 8020EB94 0020BAD4  7D 89 03 A6 */	mtctr r12
/* 8020EB98 0020BAD8  4E 80 04 21 */	bctrl 
/* 8020EB9C 0020BADC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8020EBA0 0020BAE0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8020EBA4 0020BAE4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8020EBA8 0020BAE8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8020EBAC 0020BAEC  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8020EBB0 0020BAF0  7C 08 03 A6 */	mtlr r0
/* 8020EBB4 0020BAF4  38 21 00 20 */	addi r1, r1, 0x20
/* 8020EBB8 0020BAF8  4E 80 00 20 */	blr 

.global getNearestFlock__Q24Game12BaseFlockMgrFR10Vector3$$0f$$1
getNearestFlock__Q24Game12BaseFlockMgrFR10Vector3$$0f$$1:
/* 8020EBBC 0020BAFC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8020EBC0 0020BB00  7C 08 02 A6 */	mflr r0
/* 8020EBC4 0020BB04  90 01 00 34 */	stw r0, 0x34(r1)
/* 8020EBC8 0020BB08  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8020EBCC 0020BB0C  F3 E1 00 28 */	psq_st f31, 40(r1), 0, qr0
/* 8020EBD0 0020BB10  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8020EBD4 0020BB14  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8020EBD8 0020BB18  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8020EBDC 0020BB1C  93 81 00 10 */	stw r28, 0x10(r1)
/* 8020EBE0 0020BB20  C3 E2 BB 88 */	lfs f31, lbl_80519EE8@sda21(r2)
/* 8020EBE4 0020BB24  7C 7C 1B 78 */	mr r28, r3
/* 8020EBE8 0020BB28  7C 9D 23 78 */	mr r29, r4
/* 8020EBEC 0020BB2C  3B E0 FF FF */	li r31, -1
/* 8020EBF0 0020BB30  3B C0 00 00 */	li r30, 0
/* 8020EBF4 0020BB34  48 00 00 D4 */	b lbl_8020ECC8
lbl_8020EBF8:
/* 8020EBF8 0020BB38  7F 83 E3 78 */	mr r3, r28
/* 8020EBFC 0020BB3C  7F C4 F3 78 */	mr r4, r30
/* 8020EC00 0020BB40  81 9C 00 00 */	lwz r12, 0(r28)
/* 8020EC04 0020BB44  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8020EC08 0020BB48  7D 89 03 A6 */	mtctr r12
/* 8020EC0C 0020BB4C  4E 80 04 21 */	bctrl 
/* 8020EC10 0020BB50  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020EC14 0020BB54  41 82 00 B0 */	beq lbl_8020ECC4
/* 8020EC18 0020BB58  7F 83 E3 78 */	mr r3, r28
/* 8020EC1C 0020BB5C  7F C4 F3 78 */	mr r4, r30
/* 8020EC20 0020BB60  81 9C 00 00 */	lwz r12, 0(r28)
/* 8020EC24 0020BB64  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8020EC28 0020BB68  7D 89 03 A6 */	mtctr r12
/* 8020EC2C 0020BB6C  4E 80 04 21 */	bctrl 
/* 8020EC30 0020BB70  81 83 00 0C */	lwz r12, 0xc(r3)
/* 8020EC34 0020BB74  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8020EC38 0020BB78  7D 89 03 A6 */	mtctr r12
/* 8020EC3C 0020BB7C  4E 80 04 21 */	bctrl 
/* 8020EC40 0020BB80  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020EC44 0020BB84  41 82 00 80 */	beq lbl_8020ECC4
/* 8020EC48 0020BB88  7F 83 E3 78 */	mr r3, r28
/* 8020EC4C 0020BB8C  7F C4 F3 78 */	mr r4, r30
/* 8020EC50 0020BB90  81 9C 00 00 */	lwz r12, 0(r28)
/* 8020EC54 0020BB94  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8020EC58 0020BB98  7D 89 03 A6 */	mtctr r12
/* 8020EC5C 0020BB9C  4E 80 04 21 */	bctrl 
/* 8020EC60 0020BBA0  C0 23 00 04 */	lfs f1, 4(r3)
/* 8020EC64 0020BBA4  C0 1D 00 04 */	lfs f0, 4(r29)
/* 8020EC68 0020BBA8  C0 63 00 08 */	lfs f3, 8(r3)
/* 8020EC6C 0020BBAC  EC 81 00 28 */	fsubs f4, f1, f0
/* 8020EC70 0020BBB0  C0 5D 00 08 */	lfs f2, 8(r29)
/* 8020EC74 0020BBB4  C0 23 00 00 */	lfs f1, 0(r3)
/* 8020EC78 0020BBB8  C0 1D 00 00 */	lfs f0, 0(r29)
/* 8020EC7C 0020BBBC  EC 43 10 28 */	fsubs f2, f3, f2
/* 8020EC80 0020BBC0  EC 64 01 32 */	fmuls f3, f4, f4
/* 8020EC84 0020BBC4  EC 21 00 28 */	fsubs f1, f1, f0
/* 8020EC88 0020BBC8  C0 02 BB 8C */	lfs f0, lbl_80519EEC@sda21(r2)
/* 8020EC8C 0020BBCC  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8020EC90 0020BBD0  EC 21 18 7A */	fmadds f1, f1, f1, f3
/* 8020EC94 0020BBD4  EC 22 08 2A */	fadds f1, f2, f1
/* 8020EC98 0020BBD8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8020EC9C 0020BBDC  40 81 00 14 */	ble lbl_8020ECB0
/* 8020ECA0 0020BBE0  40 81 00 14 */	ble lbl_8020ECB4
/* 8020ECA4 0020BBE4  FC 00 08 34 */	frsqrte f0, f1
/* 8020ECA8 0020BBE8  EC 20 00 72 */	fmuls f1, f0, f1
/* 8020ECAC 0020BBEC  48 00 00 08 */	b lbl_8020ECB4
lbl_8020ECB0:
/* 8020ECB0 0020BBF0  FC 20 00 90 */	fmr f1, f0
lbl_8020ECB4:
/* 8020ECB4 0020BBF4  FC 01 F8 40 */	fcmpo cr0, f1, f31
/* 8020ECB8 0020BBF8  40 80 00 0C */	bge lbl_8020ECC4
/* 8020ECBC 0020BBFC  FF E0 08 90 */	fmr f31, f1
/* 8020ECC0 0020BC00  7F DF F3 78 */	mr r31, r30
lbl_8020ECC4:
/* 8020ECC4 0020BC04  3B DE 00 01 */	addi r30, r30, 1
lbl_8020ECC8:
/* 8020ECC8 0020BC08  7F 83 E3 78 */	mr r3, r28
/* 8020ECCC 0020BC0C  81 9C 00 00 */	lwz r12, 0(r28)
/* 8020ECD0 0020BC10  81 8C 00 08 */	lwz r12, 8(r12)
/* 8020ECD4 0020BC14  7D 89 03 A6 */	mtctr r12
/* 8020ECD8 0020BC18  4E 80 04 21 */	bctrl 
/* 8020ECDC 0020BC1C  7C 1E 18 00 */	cmpw r30, r3
/* 8020ECE0 0020BC20  41 80 FF 18 */	blt lbl_8020EBF8
/* 8020ECE4 0020BC24  7F E3 FB 78 */	mr r3, r31
/* 8020ECE8 0020BC28  E3 E1 00 28 */	psq_l f31, 40(r1), 0, qr0
/* 8020ECEC 0020BC2C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8020ECF0 0020BC30  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8020ECF4 0020BC34  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8020ECF8 0020BC38  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8020ECFC 0020BC3C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8020ED00 0020BC40  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8020ED04 0020BC44  7C 08 03 A6 */	mtlr r0
/* 8020ED08 0020BC48  38 21 00 30 */	addi r1, r1, 0x30
/* 8020ED0C 0020BC4C  4E 80 00 20 */	blr 

.global attackFlock__Q24Game12BaseFlockMgrFif
attackFlock__Q24Game12BaseFlockMgrFif:
/* 8020ED10 0020BC50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8020ED14 0020BC54  7C 08 02 A6 */	mflr r0
/* 8020ED18 0020BC58  90 01 00 24 */	stw r0, 0x24(r1)
/* 8020ED1C 0020BC5C  DB E1 00 18 */	stfd f31, 0x18(r1)
/* 8020ED20 0020BC60  FF E0 08 90 */	fmr f31, f1
/* 8020ED24 0020BC64  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8020ED28 0020BC68  3B E0 00 00 */	li r31, 0
/* 8020ED2C 0020BC6C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8020ED30 0020BC70  7C 9E 23 79 */	or. r30, r4, r4
/* 8020ED34 0020BC74  93 A1 00 0C */	stw r29, 0xc(r1)
/* 8020ED38 0020BC78  7C 7D 1B 78 */	mr r29, r3
/* 8020ED3C 0020BC7C  41 80 00 20 */	blt lbl_8020ED5C
/* 8020ED40 0020BC80  81 83 00 00 */	lwz r12, 0(r3)
/* 8020ED44 0020BC84  81 8C 00 08 */	lwz r12, 8(r12)
/* 8020ED48 0020BC88  7D 89 03 A6 */	mtctr r12
/* 8020ED4C 0020BC8C  4E 80 04 21 */	bctrl 
/* 8020ED50 0020BC90  7C 1E 18 00 */	cmpw r30, r3
/* 8020ED54 0020BC94  40 80 00 08 */	bge lbl_8020ED5C
/* 8020ED58 0020BC98  3B E0 00 01 */	li r31, 1
lbl_8020ED5C:
/* 8020ED5C 0020BC9C  57 E0 06 3F */	clrlwi. r0, r31, 0x18
/* 8020ED60 0020BCA0  40 82 00 20 */	bne lbl_8020ED80
/* 8020ED64 0020BCA4  3C 60 80 48 */	lis r3, lbl_80481FA0@ha
/* 8020ED68 0020BCA8  3C A0 80 48 */	lis r5, lbl_80481FB0@ha
/* 8020ED6C 0020BCAC  38 63 1F A0 */	addi r3, r3, lbl_80481FA0@l
/* 8020ED70 0020BCB0  38 80 00 5D */	li r4, 0x5d
/* 8020ED74 0020BCB4  38 A5 1F B0 */	addi r5, r5, lbl_80481FB0@l
/* 8020ED78 0020BCB8  4C C6 31 82 */	crclr 6
/* 8020ED7C 0020BCBC  4B E1 B8 C5 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_8020ED80:
/* 8020ED80 0020BCC0  7F A3 EB 78 */	mr r3, r29
/* 8020ED84 0020BCC4  7F C4 F3 78 */	mr r4, r30
/* 8020ED88 0020BCC8  81 9D 00 00 */	lwz r12, 0(r29)
/* 8020ED8C 0020BCCC  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8020ED90 0020BCD0  7D 89 03 A6 */	mtctr r12
/* 8020ED94 0020BCD4  4E 80 04 21 */	bctrl 
/* 8020ED98 0020BCD8  7C 60 1B 78 */	mr r0, r3
/* 8020ED9C 0020BCDC  7F A3 EB 78 */	mr r3, r29
/* 8020EDA0 0020BCE0  81 9D 00 00 */	lwz r12, 0(r29)
/* 8020EDA4 0020BCE4  7C 1F 03 78 */	mr r31, r0
/* 8020EDA8 0020BCE8  7F C4 F3 78 */	mr r4, r30
/* 8020EDAC 0020BCEC  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8020EDB0 0020BCF0  7D 89 03 A6 */	mtctr r12
/* 8020EDB4 0020BCF4  4E 80 04 21 */	bctrl 
/* 8020EDB8 0020BCF8  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020EDBC 0020BCFC  41 82 00 4C */	beq lbl_8020EE08
/* 8020EDC0 0020BD00  7F E3 FB 78 */	mr r3, r31
/* 8020EDC4 0020BD04  FC 20 F8 90 */	fmr f1, f31
/* 8020EDC8 0020BD08  81 9F 00 0C */	lwz r12, 0xc(r31)
/* 8020EDCC 0020BD0C  81 8C 00 1C */	lwz r12, 0x1c(r12)
/* 8020EDD0 0020BD10  7D 89 03 A6 */	mtctr r12
/* 8020EDD4 0020BD14  4E 80 04 21 */	bctrl 
/* 8020EDD8 0020BD18  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020EDDC 0020BD1C  41 82 00 24 */	beq lbl_8020EE00
/* 8020EDE0 0020BD20  7F A3 EB 78 */	mr r3, r29
/* 8020EDE4 0020BD24  7F E4 FB 78 */	mr r4, r31
/* 8020EDE8 0020BD28  81 9D 00 00 */	lwz r12, 0(r29)
/* 8020EDEC 0020BD2C  81 8C 00 18 */	lwz r12, 0x18(r12)
/* 8020EDF0 0020BD30  7D 89 03 A6 */	mtctr r12
/* 8020EDF4 0020BD34  4E 80 04 21 */	bctrl 
/* 8020EDF8 0020BD38  38 60 00 01 */	li r3, 1
/* 8020EDFC 0020BD3C  48 00 00 10 */	b lbl_8020EE0C
lbl_8020EE00:
/* 8020EE00 0020BD40  38 60 00 00 */	li r3, 0
/* 8020EE04 0020BD44  48 00 00 08 */	b lbl_8020EE0C
lbl_8020EE08:
/* 8020EE08 0020BD48  38 60 00 02 */	li r3, 2
lbl_8020EE0C:
/* 8020EE0C 0020BD4C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8020EE10 0020BD50  CB E1 00 18 */	lfd f31, 0x18(r1)
/* 8020EE14 0020BD54  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8020EE18 0020BD58  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8020EE1C 0020BD5C  83 A1 00 0C */	lwz r29, 0xc(r1)
/* 8020EE20 0020BD60  7C 08 03 A6 */	mtlr r0
/* 8020EE24 0020BD64  38 21 00 20 */	addi r1, r1, 0x20
/* 8020EE28 0020BD68  4E 80 00 20 */	blr 

.global resolveCollision__Q24Game12BaseFlockMgrFf
resolveCollision__Q24Game12BaseFlockMgrFf:
/* 8020EE2C 0020BD6C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8020EE30 0020BD70  7C 08 02 A6 */	mflr r0
/* 8020EE34 0020BD74  90 01 00 44 */	stw r0, 0x44(r1)
/* 8020EE38 0020BD78  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 8020EE3C 0020BD7C  F3 E1 00 38 */	psq_st f31, 56(r1), 0, qr0
/* 8020EE40 0020BD80  DB C1 00 20 */	stfd f30, 0x20(r1)
/* 8020EE44 0020BD84  F3 C1 00 28 */	psq_st f30, 40(r1), 0, qr0
/* 8020EE48 0020BD88  BF 61 00 0C */	stmw r27, 0xc(r1)
/* 8020EE4C 0020BD8C  FF C0 08 90 */	fmr f30, f1
/* 8020EE50 0020BD90  C0 02 BB 90 */	lfs f0, lbl_80519EF0@sda21(r2)
/* 8020EE54 0020BD94  7C 7B 1B 78 */	mr r27, r3
/* 8020EE58 0020BD98  3B C0 00 00 */	li r30, 0
/* 8020EE5C 0020BD9C  EF E0 07 B2 */	fmuls f31, f0, f30
lbl_8020EE60:
/* 8020EE60 0020BDA0  3B A0 00 00 */	li r29, 0
/* 8020EE64 0020BDA4  48 00 01 A0 */	b lbl_8020F004
lbl_8020EE68:
/* 8020EE68 0020BDA8  7F 63 DB 78 */	mr r3, r27
/* 8020EE6C 0020BDAC  7F A4 EB 78 */	mr r4, r29
/* 8020EE70 0020BDB0  81 9B 00 00 */	lwz r12, 0(r27)
/* 8020EE74 0020BDB4  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8020EE78 0020BDB8  7D 89 03 A6 */	mtctr r12
/* 8020EE7C 0020BDBC  4E 80 04 21 */	bctrl 
/* 8020EE80 0020BDC0  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020EE84 0020BDC4  41 82 01 7C */	beq lbl_8020F000
/* 8020EE88 0020BDC8  3B 80 00 00 */	li r28, 0
/* 8020EE8C 0020BDCC  48 00 01 58 */	b lbl_8020EFE4
lbl_8020EE90:
/* 8020EE90 0020BDD0  7F 63 DB 78 */	mr r3, r27
/* 8020EE94 0020BDD4  7F 84 E3 78 */	mr r4, r28
/* 8020EE98 0020BDD8  81 9B 00 00 */	lwz r12, 0(r27)
/* 8020EE9C 0020BDDC  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8020EEA0 0020BDE0  7D 89 03 A6 */	mtctr r12
/* 8020EEA4 0020BDE4  4E 80 04 21 */	bctrl 
/* 8020EEA8 0020BDE8  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020EEAC 0020BDEC  41 82 01 34 */	beq lbl_8020EFE0
/* 8020EEB0 0020BDF0  7C 1D E0 00 */	cmpw r29, r28
/* 8020EEB4 0020BDF4  41 82 01 2C */	beq lbl_8020EFE0
/* 8020EEB8 0020BDF8  7F 63 DB 78 */	mr r3, r27
/* 8020EEBC 0020BDFC  7F A4 EB 78 */	mr r4, r29
/* 8020EEC0 0020BE00  81 9B 00 00 */	lwz r12, 0(r27)
/* 8020EEC4 0020BE04  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8020EEC8 0020BE08  7D 89 03 A6 */	mtctr r12
/* 8020EECC 0020BE0C  4E 80 04 21 */	bctrl 
/* 8020EED0 0020BE10  7C 7F 1B 78 */	mr r31, r3
/* 8020EED4 0020BE14  7F 63 DB 78 */	mr r3, r27
/* 8020EED8 0020BE18  81 9B 00 00 */	lwz r12, 0(r27)
/* 8020EEDC 0020BE1C  7F 84 E3 78 */	mr r4, r28
/* 8020EEE0 0020BE20  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8020EEE4 0020BE24  7D 89 03 A6 */	mtctr r12
/* 8020EEE8 0020BE28  4E 80 04 21 */	bctrl 
/* 8020EEEC 0020BE2C  C0 FF 00 08 */	lfs f7, 8(r31)
/* 8020EEF0 0020BE30  C0 03 00 08 */	lfs f0, 8(r3)
/* 8020EEF4 0020BE34  C1 3F 00 00 */	lfs f9, 0(r31)
/* 8020EEF8 0020BE38  EC A7 00 28 */	fsubs f5, f7, f0
/* 8020EEFC 0020BE3C  C0 23 00 00 */	lfs f1, 0(r3)
/* 8020EF00 0020BE40  C0 02 BB 8C */	lfs f0, lbl_80519EEC@sda21(r2)
/* 8020EF04 0020BE44  EC 69 08 28 */	fsubs f3, f9, f1
/* 8020EF08 0020BE48  C1 1F 00 04 */	lfs f8, 4(r31)
/* 8020EF0C 0020BE4C  EC 45 01 72 */	fmuls f2, f5, f5
/* 8020EF10 0020BE50  EC C3 00 F2 */	fmuls f6, f3, f3
/* 8020EF14 0020BE54  EC 26 10 2A */	fadds f1, f6, f2
/* 8020EF18 0020BE58  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8020EF1C 0020BE5C  40 81 00 1C */	ble lbl_8020EF38
/* 8020EF20 0020BE60  EC 23 10 FA */	fmadds f1, f3, f3, f2
/* 8020EF24 0020BE64  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8020EF28 0020BE68  40 81 00 14 */	ble lbl_8020EF3C
/* 8020EF2C 0020BE6C  FC 00 08 34 */	frsqrte f0, f1
/* 8020EF30 0020BE70  EC 20 00 72 */	fmuls f1, f0, f1
/* 8020EF34 0020BE74  48 00 00 08 */	b lbl_8020EF3C
lbl_8020EF38:
/* 8020EF38 0020BE78  FC 20 00 90 */	fmr f1, f0
lbl_8020EF3C:
/* 8020EF3C 0020BE7C  FC 01 F0 40 */	fcmpo cr0, f1, f30
/* 8020EF40 0020BE80  40 80 00 A0 */	bge lbl_8020EFE0
/* 8020EF44 0020BE84  C0 82 BB 8C */	lfs f4, lbl_80519EEC@sda21(r2)
/* 8020EF48 0020BE88  EC 06 20 2A */	fadds f0, f6, f4
/* 8020EF4C 0020BE8C  EC 02 00 2A */	fadds f0, f2, f0
/* 8020EF50 0020BE90  FC 00 20 40 */	fcmpo cr0, f0, f4
/* 8020EF54 0020BE94  40 81 00 20 */	ble lbl_8020EF74
/* 8020EF58 0020BE98  EC 03 20 FA */	fmadds f0, f3, f3, f4
/* 8020EF5C 0020BE9C  EC 22 00 2A */	fadds f1, f2, f0
/* 8020EF60 0020BEA0  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 8020EF64 0020BEA4  40 81 00 14 */	ble lbl_8020EF78
/* 8020EF68 0020BEA8  FC 00 08 34 */	frsqrte f0, f1
/* 8020EF6C 0020BEAC  EC 20 00 72 */	fmuls f1, f0, f1
/* 8020EF70 0020BEB0  48 00 00 08 */	b lbl_8020EF78
lbl_8020EF74:
/* 8020EF74 0020BEB4  FC 20 20 90 */	fmr f1, f4
lbl_8020EF78:
/* 8020EF78 0020BEB8  C0 02 BB 8C */	lfs f0, lbl_80519EEC@sda21(r2)
/* 8020EF7C 0020BEBC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8020EF80 0020BEC0  40 81 00 18 */	ble lbl_8020EF98
/* 8020EF84 0020BEC4  C0 02 BB 94 */	lfs f0, lbl_80519EF4@sda21(r2)
/* 8020EF88 0020BEC8  EC 00 08 24 */	fdivs f0, f0, f1
/* 8020EF8C 0020BECC  EC 63 00 32 */	fmuls f3, f3, f0
/* 8020EF90 0020BED0  EC 84 00 32 */	fmuls f4, f4, f0
/* 8020EF94 0020BED4  EC A5 00 32 */	fmuls f5, f5, f0
lbl_8020EF98:
/* 8020EF98 0020BED8  EC 63 07 F2 */	fmuls f3, f3, f31
/* 8020EF9C 0020BEDC  EC 84 07 F2 */	fmuls f4, f4, f31
/* 8020EFA0 0020BEE0  EC A5 07 F2 */	fmuls f5, f5, f31
/* 8020EFA4 0020BEE4  EC 49 18 28 */	fsubs f2, f9, f3
/* 8020EFA8 0020BEE8  EC 28 20 28 */	fsubs f1, f8, f4
/* 8020EFAC 0020BEEC  EC 07 28 28 */	fsubs f0, f7, f5
/* 8020EFB0 0020BEF0  D0 5F 00 00 */	stfs f2, 0(r31)
/* 8020EFB4 0020BEF4  D0 3F 00 04 */	stfs f1, 4(r31)
/* 8020EFB8 0020BEF8  D0 1F 00 08 */	stfs f0, 8(r31)
/* 8020EFBC 0020BEFC  C0 03 00 00 */	lfs f0, 0(r3)
/* 8020EFC0 0020BF00  C0 23 00 04 */	lfs f1, 4(r3)
/* 8020EFC4 0020BF04  EC 00 18 2A */	fadds f0, f0, f3
/* 8020EFC8 0020BF08  C0 43 00 08 */	lfs f2, 8(r3)
/* 8020EFCC 0020BF0C  EC 21 20 2A */	fadds f1, f1, f4
/* 8020EFD0 0020BF10  EC 42 28 2A */	fadds f2, f2, f5
/* 8020EFD4 0020BF14  D0 03 00 00 */	stfs f0, 0(r3)
/* 8020EFD8 0020BF18  D0 23 00 04 */	stfs f1, 4(r3)
/* 8020EFDC 0020BF1C  D0 43 00 08 */	stfs f2, 8(r3)
lbl_8020EFE0:
/* 8020EFE0 0020BF20  3B 9C 00 01 */	addi r28, r28, 1
lbl_8020EFE4:
/* 8020EFE4 0020BF24  7F 63 DB 78 */	mr r3, r27
/* 8020EFE8 0020BF28  81 9B 00 00 */	lwz r12, 0(r27)
/* 8020EFEC 0020BF2C  81 8C 00 08 */	lwz r12, 8(r12)
/* 8020EFF0 0020BF30  7D 89 03 A6 */	mtctr r12
/* 8020EFF4 0020BF34  4E 80 04 21 */	bctrl 
/* 8020EFF8 0020BF38  7C 1C 18 00 */	cmpw r28, r3
/* 8020EFFC 0020BF3C  41 80 FE 94 */	blt lbl_8020EE90
lbl_8020F000:
/* 8020F000 0020BF40  3B BD 00 01 */	addi r29, r29, 1
lbl_8020F004:
/* 8020F004 0020BF44  7F 63 DB 78 */	mr r3, r27
/* 8020F008 0020BF48  81 9B 00 00 */	lwz r12, 0(r27)
/* 8020F00C 0020BF4C  81 8C 00 08 */	lwz r12, 8(r12)
/* 8020F010 0020BF50  7D 89 03 A6 */	mtctr r12
/* 8020F014 0020BF54  4E 80 04 21 */	bctrl 
/* 8020F018 0020BF58  7C 1D 18 00 */	cmpw r29, r3
/* 8020F01C 0020BF5C  41 80 FE 4C */	blt lbl_8020EE68
/* 8020F020 0020BF60  3B DE 00 01 */	addi r30, r30, 1
/* 8020F024 0020BF64  2C 1E 00 04 */	cmpwi r30, 4
/* 8020F028 0020BF68  41 80 FE 38 */	blt lbl_8020EE60
/* 8020F02C 0020BF6C  3B 80 00 00 */	li r28, 0
/* 8020F030 0020BF70  48 00 00 50 */	b lbl_8020F080
lbl_8020F034:
/* 8020F034 0020BF74  7F 63 DB 78 */	mr r3, r27
/* 8020F038 0020BF78  7F 84 E3 78 */	mr r4, r28
/* 8020F03C 0020BF7C  81 9B 00 00 */	lwz r12, 0(r27)
/* 8020F040 0020BF80  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8020F044 0020BF84  7D 89 03 A6 */	mtctr r12
/* 8020F048 0020BF88  4E 80 04 21 */	bctrl 
/* 8020F04C 0020BF8C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020F050 0020BF90  41 82 00 2C */	beq lbl_8020F07C
/* 8020F054 0020BF94  7F 63 DB 78 */	mr r3, r27
/* 8020F058 0020BF98  7F 84 E3 78 */	mr r4, r28
/* 8020F05C 0020BF9C  81 9B 00 00 */	lwz r12, 0(r27)
/* 8020F060 0020BFA0  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8020F064 0020BFA4  7D 89 03 A6 */	mtctr r12
/* 8020F068 0020BFA8  4E 80 04 21 */	bctrl 
/* 8020F06C 0020BFAC  81 83 00 0C */	lwz r12, 0xc(r3)
/* 8020F070 0020BFB0  81 8C 00 08 */	lwz r12, 8(r12)
/* 8020F074 0020BFB4  7D 89 03 A6 */	mtctr r12
/* 8020F078 0020BFB8  4E 80 04 21 */	bctrl 
lbl_8020F07C:
/* 8020F07C 0020BFBC  3B 9C 00 01 */	addi r28, r28, 1
lbl_8020F080:
/* 8020F080 0020BFC0  7F 63 DB 78 */	mr r3, r27
/* 8020F084 0020BFC4  81 9B 00 00 */	lwz r12, 0(r27)
/* 8020F088 0020BFC8  81 8C 00 08 */	lwz r12, 8(r12)
/* 8020F08C 0020BFCC  7D 89 03 A6 */	mtctr r12
/* 8020F090 0020BFD0  4E 80 04 21 */	bctrl 
/* 8020F094 0020BFD4  7C 1C 18 00 */	cmpw r28, r3
/* 8020F098 0020BFD8  41 80 FF 9C */	blt lbl_8020F034
/* 8020F09C 0020BFDC  E3 E1 00 38 */	psq_l f31, 56(r1), 0, qr0
/* 8020F0A0 0020BFE0  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 8020F0A4 0020BFE4  E3 C1 00 28 */	psq_l f30, 40(r1), 0, qr0
/* 8020F0A8 0020BFE8  CB C1 00 20 */	lfd f30, 0x20(r1)
/* 8020F0AC 0020BFEC  BB 61 00 0C */	lmw r27, 0xc(r1)
/* 8020F0B0 0020BFF0  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8020F0B4 0020BFF4  7C 08 03 A6 */	mtlr r0
/* 8020F0B8 0020BFF8  38 21 00 40 */	addi r1, r1, 0x40
/* 8020F0BC 0020BFFC  4E 80 00 20 */	blr 

.global doSimpleDraw__Q24Game12BaseFlockMgrFP8ViewportPP12J3DModelDatai
doSimpleDraw__Q24Game12BaseFlockMgrFP8ViewportPP12J3DModelDatai:
/* 8020F0C0 0020C000  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 8020F0C4 0020C004  7C 08 02 A6 */	mflr r0
/* 8020F0C8 0020C008  90 01 00 64 */	stw r0, 0x64(r1)
/* 8020F0CC 0020C00C  BE E1 00 3C */	stmw r23, 0x3c(r1)
/* 8020F0D0 0020C010  7C 7D 1B 78 */	mr r29, r3
/* 8020F0D4 0020C014  7C 9E 23 78 */	mr r30, r4
/* 8020F0D8 0020C018  7C DF 33 78 */	mr r31, r6
/* 8020F0DC 0020C01C  A0 04 00 18 */	lhz r0, 0x18(r4)
/* 8020F0E0 0020C020  7C 7D 02 14 */	add r3, r29, r0
/* 8020F0E4 0020C024  88 03 00 1C */	lbz r0, 0x1c(r3)
/* 8020F0E8 0020C028  28 00 00 00 */	cmplwi r0, 0
/* 8020F0EC 0020C02C  41 82 01 58 */	beq lbl_8020F244
/* 8020F0F0 0020C030  3C 60 80 51 */	lis r3, j3dSys@ha
/* 8020F0F4 0020C034  7C BB 2B 78 */	mr r27, r5
/* 8020F0F8 0020C038  3B 83 F2 30 */	addi r28, r3, j3dSys@l
/* 8020F0FC 0020C03C  3B 40 00 00 */	li r26, 0
/* 8020F100 0020C040  48 00 01 3C */	b lbl_8020F23C
lbl_8020F104:
/* 8020F104 0020C044  80 BB 00 00 */	lwz r5, 0(r27)
/* 8020F108 0020C048  38 00 00 00 */	li r0, 0
/* 8020F10C 0020C04C  80 85 00 28 */	lwz r4, 0x28(r5)
/* 8020F110 0020C050  80 65 00 A0 */	lwz r3, 0xa0(r5)
/* 8020F114 0020C054  80 84 00 00 */	lwz r4, 0(r4)
/* 8020F118 0020C058  83 24 00 58 */	lwz r25, 0x58(r4)
/* 8020F11C 0020C05C  90 7C 01 0C */	stw r3, 0x10c(r28)
/* 8020F120 0020C060  80 65 00 A4 */	lwz r3, 0xa4(r5)
/* 8020F124 0020C064  90 7C 01 10 */	stw r3, 0x110(r28)
/* 8020F128 0020C068  80 65 00 AC */	lwz r3, 0xac(r5)
/* 8020F12C 0020C06C  90 7C 01 14 */	stw r3, 0x114(r28)
/* 8020F130 0020C070  90 0D 89 70 */	stw r0, sOldVcdVatCmd__8J3DShape@sda21(r13)
/* 8020F134 0020C074  48 00 00 F8 */	b lbl_8020F22C
lbl_8020F138:
/* 8020F138 0020C078  7F 23 CB 78 */	mr r3, r25
/* 8020F13C 0020C07C  81 99 00 00 */	lwz r12, 0(r25)
/* 8020F140 0020C080  81 8C 00 1C */	lwz r12, 0x1c(r12)
/* 8020F144 0020C084  7D 89 03 A6 */	mtctr r12
/* 8020F148 0020C088  4E 80 04 21 */	bctrl 
/* 8020F14C 0020C08C  80 79 00 08 */	lwz r3, 8(r25)
/* 8020F150 0020C090  4B E5 1C F1 */	bl loadPreDrawSetting__8J3DShapeCFv
/* 8020F154 0020C094  3B 00 00 00 */	li r24, 0
/* 8020F158 0020C098  48 00 00 B4 */	b lbl_8020F20C
lbl_8020F15C:
/* 8020F15C 0020C09C  7F A3 EB 78 */	mr r3, r29
/* 8020F160 0020C0A0  7F 04 C3 78 */	mr r4, r24
/* 8020F164 0020C0A4  81 9D 00 00 */	lwz r12, 0(r29)
/* 8020F168 0020C0A8  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8020F16C 0020C0AC  7D 89 03 A6 */	mtctr r12
/* 8020F170 0020C0B0  4E 80 04 21 */	bctrl 
/* 8020F174 0020C0B4  7C 60 1B 78 */	mr r0, r3
/* 8020F178 0020C0B8  7F A3 EB 78 */	mr r3, r29
/* 8020F17C 0020C0BC  81 9D 00 00 */	lwz r12, 0(r29)
/* 8020F180 0020C0C0  7C 17 03 78 */	mr r23, r0
/* 8020F184 0020C0C4  7F 04 C3 78 */	mr r4, r24
/* 8020F188 0020C0C8  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8020F18C 0020C0CC  7D 89 03 A6 */	mtctr r12
/* 8020F190 0020C0D0  4E 80 04 21 */	bctrl 
/* 8020F194 0020C0D4  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020F198 0020C0D8  41 82 00 70 */	beq lbl_8020F208
/* 8020F19C 0020C0DC  7E E3 BB 78 */	mr r3, r23
/* 8020F1A0 0020C0E0  81 97 00 0C */	lwz r12, 0xc(r23)
/* 8020F1A4 0020C0E4  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8020F1A8 0020C0E8  7D 89 03 A6 */	mtctr r12
/* 8020F1AC 0020C0EC  4E 80 04 21 */	bctrl 
/* 8020F1B0 0020C0F0  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8020F1B4 0020C0F4  41 82 00 54 */	beq lbl_8020F208
/* 8020F1B8 0020C0F8  88 17 00 40 */	lbz r0, 0x40(r23)
/* 8020F1BC 0020C0FC  7C 00 D0 00 */	cmpw r0, r26
/* 8020F1C0 0020C100  40 82 00 48 */	bne lbl_8020F208
/* 8020F1C4 0020C104  7F C3 F3 78 */	mr r3, r30
/* 8020F1C8 0020C108  38 80 00 01 */	li r4, 1
/* 8020F1CC 0020C10C  48 21 5F 91 */	bl getMatrix__8ViewportFb
/* 8020F1D0 0020C110  38 97 00 10 */	addi r4, r23, 0x10
/* 8020F1D4 0020C114  38 A1 00 08 */	addi r5, r1, 8
/* 8020F1D8 0020C118  4B ED B1 29 */	bl PSMTXConcat
/* 8020F1DC 0020C11C  38 61 00 08 */	addi r3, r1, 8
/* 8020F1E0 0020C120  38 80 00 00 */	li r4, 0
/* 8020F1E4 0020C124  4B ED A3 95 */	bl GXLoadPosMtxImm
/* 8020F1E8 0020C128  38 61 00 08 */	addi r3, r1, 8
/* 8020F1EC 0020C12C  38 80 00 00 */	li r4, 0
/* 8020F1F0 0020C130  4B ED A3 D9 */	bl GXLoadNrmMtxImm
/* 8020F1F4 0020C134  80 79 00 08 */	lwz r3, 8(r25)
/* 8020F1F8 0020C138  81 83 00 00 */	lwz r12, 0(r3)
/* 8020F1FC 0020C13C  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8020F200 0020C140  7D 89 03 A6 */	mtctr r12
/* 8020F204 0020C144  4E 80 04 21 */	bctrl 
lbl_8020F208:
/* 8020F208 0020C148  3B 18 00 01 */	addi r24, r24, 1
lbl_8020F20C:
/* 8020F20C 0020C14C  7F A3 EB 78 */	mr r3, r29
/* 8020F210 0020C150  81 9D 00 00 */	lwz r12, 0(r29)
/* 8020F214 0020C154  81 8C 00 08 */	lwz r12, 8(r12)
/* 8020F218 0020C158  7D 89 03 A6 */	mtctr r12
/* 8020F21C 0020C15C  4E 80 04 21 */	bctrl 
/* 8020F220 0020C160  7C 18 18 00 */	cmpw r24, r3
/* 8020F224 0020C164  41 80 FF 38 */	blt lbl_8020F15C
/* 8020F228 0020C168  83 39 00 04 */	lwz r25, 4(r25)
lbl_8020F22C:
/* 8020F22C 0020C16C  28 19 00 00 */	cmplwi r25, 0
/* 8020F230 0020C170  40 82 FF 08 */	bne lbl_8020F138
/* 8020F234 0020C174  3B 7B 00 04 */	addi r27, r27, 4
/* 8020F238 0020C178  3B 5A 00 01 */	addi r26, r26, 1
lbl_8020F23C:
/* 8020F23C 0020C17C  7C 1A F8 00 */	cmpw r26, r31
/* 8020F240 0020C180  41 80 FE C4 */	blt lbl_8020F104
lbl_8020F244:
/* 8020F244 0020C184  BA E1 00 3C */	lmw r23, 0x3c(r1)
/* 8020F248 0020C188  80 01 00 64 */	lwz r0, 0x64(r1)
/* 8020F24C 0020C18C  7C 08 03 A6 */	mtlr r0
/* 8020F250 0020C190  38 21 00 60 */	addi r1, r1, 0x60
/* 8020F254 0020C194  4E 80 00 20 */	blr 

.global __sinit_flockMgr_cpp
__sinit_flockMgr_cpp:
/* 8020F258 0020C198  3C 80 80 51 */	lis r4, __float_nan@ha
/* 8020F25C 0020C19C  38 00 FF FF */	li r0, -1
/* 8020F260 0020C1A0  C0 04 48 B0 */	lfs f0, __float_nan@l(r4)
/* 8020F264 0020C1A4  3C 60 80 4C */	lis r3, lbl_804BFB60@ha
/* 8020F268 0020C1A8  90 0D 95 50 */	stw r0, lbl_80515BD0@sda21(r13)
/* 8020F26C 0020C1AC  D4 03 FB 60 */	stfsu f0, lbl_804BFB60@l(r3)
/* 8020F270 0020C1B0  D0 0D 95 54 */	stfs f0, lbl_80515BD4@sda21(r13)
/* 8020F274 0020C1B4  D0 03 00 04 */	stfs f0, 4(r3)
/* 8020F278 0020C1B8  D0 03 00 08 */	stfs f0, 8(r3)
/* 8020F27C 0020C1BC  4E 80 00 20 */	blr 
