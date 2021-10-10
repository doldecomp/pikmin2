.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global __ct__4MenuFP10JUTGamePadP7JUTFontb
__ct__4MenuFP10JUTGamePadP7JUTFontb:
/* 80456184 004530C4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80456188 004530C8  7C 08 02 A6 */	mflr r0
/* 8045618C 004530CC  90 01 00 34 */	stw r0, 0x34(r1)
/* 80456190 004530D0  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80456194 004530D4  7C DF 33 78 */	mr r31, r6
/* 80456198 004530D8  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8045619C 004530DC  7C BE 2B 78 */	mr r30, r5
/* 804561A0 004530E0  93 A1 00 24 */	stw r29, 0x24(r1)
/* 804561A4 004530E4  7C 9D 23 78 */	mr r29, r4
/* 804561A8 004530E8  93 81 00 20 */	stw r28, 0x20(r1)
/* 804561AC 004530EC  7C 7C 1B 78 */	mr r28, r3
/* 804561B0 004530F0  38 7C 00 18 */	addi r3, r28, 0x18
/* 804561B4 004530F4  4B BD 07 1D */	bl initiate__10JSUPtrListFv
/* 804561B8 004530F8  93 BC 00 00 */	stw r29, 0(r28)
/* 804561BC 004530FC  3C 80 0C 00 */	lis r4, 0xc00
/* 804561C0 00453100  38 A0 00 0F */	li r5, 0xf
/* 804561C4 00453104  38 C0 00 03 */	li r6, 3
/* 804561C8 00453108  80 7C 00 00 */	lwz r3, 0(r28)
/* 804561CC 0045310C  4B BD 86 1D */	bl setButtonRepeat__10JUTGamePadFUlUlUl
/* 804561D0 00453110  93 DC 00 04 */	stw r30, 4(r28)
/* 804561D4 00453114  38 00 00 00 */	li r0, 0
/* 804561D8 00453118  38 60 00 30 */	li r3, 0x30
/* 804561DC 0045311C  9B FC 00 08 */	stb r31, 8(r28)
/* 804561E0 00453120  90 1C 00 0C */	stw r0, 0xc(r28)
/* 804561E4 00453124  4B BC DC C1 */	bl __nw__FUl
/* 804561E8 00453128  7C 64 1B 79 */	or. r4, r3, r3
/* 804561EC 0045312C  41 82 00 18 */	beq lbl_80456204
/* 804561F0 00453130  38 80 00 00 */	li r4, 0
/* 804561F4 00453134  38 A0 00 00 */	li r5, 0
/* 804561F8 00453138  38 C2 28 88 */	addi r6, r2, lbl_80520BE8@sda21
/* 804561FC 0045313C  48 00 06 45 */	bl __ct__Q24Menu8MenuItemFQ34Menu8MenuItem9cTypeFlagiPc
/* 80456200 00453140  7C 64 1B 78 */	mr r4, r3
lbl_80456204:
/* 80456204 00453144  38 00 00 00 */	li r0, 0
/* 80456208 00453148  38 7C 00 18 */	addi r3, r28, 0x18
/* 8045620C 0045314C  98 04 00 04 */	stb r0, 4(r4)
/* 80456210 00453150  38 84 00 20 */	addi r4, r4, 0x20
/* 80456214 00453154  4B BD 06 D1 */	bl append__10JSUPtrListFP10JSUPtrLink
/* 80456218 00453158  39 00 00 00 */	li r8, 0
/* 8045621C 0045315C  38 E0 00 BE */	li r7, 0xbe
/* 80456220 00453160  91 1C 00 2C */	stw r8, 0x2c(r28)
/* 80456224 00453164  38 C0 00 DC */	li r6, 0xdc
/* 80456228 00453168  38 A0 01 04 */	li r5, 0x104
/* 8045622C 0045316C  38 80 00 01 */	li r4, 1
/* 80456230 00453170  91 1C 00 30 */	stw r8, 0x30(r28)
/* 80456234 00453174  38 00 01 00 */	li r0, 0x100
/* 80456238 00453178  C0 02 28 90 */	lfs f0, lbl_80520BF0@sda21(r2)
/* 8045623C 0045317C  7F 83 E3 78 */	mr r3, r28
/* 80456240 00453180  91 1C 00 28 */	stw r8, 0x28(r28)
/* 80456244 00453184  91 1C 00 24 */	stw r8, 0x24(r28)
/* 80456248 00453188  91 1C 00 14 */	stw r8, 0x14(r28)
/* 8045624C 0045318C  91 1C 00 10 */	stw r8, 0x10(r28)
/* 80456250 00453190  91 1C 00 4C */	stw r8, 0x4c(r28)
/* 80456254 00453194  91 1C 00 50 */	stw r8, 0x50(r28)
/* 80456258 00453198  91 1C 00 54 */	stw r8, 0x54(r28)
/* 8045625C 0045319C  90 FC 00 40 */	stw r7, 0x40(r28)
/* 80456260 004531A0  90 DC 00 44 */	stw r6, 0x44(r28)
/* 80456264 004531A4  90 BC 00 48 */	stw r5, 0x48(r28)
/* 80456268 004531A8  98 9C 00 58 */	stb r4, 0x58(r28)
/* 8045626C 004531AC  98 9C 00 59 */	stb r4, 0x59(r28)
/* 80456270 004531B0  91 1C 00 34 */	stw r8, 0x34(r28)
/* 80456274 004531B4  D0 1C 00 38 */	stfs f0, 0x38(r28)
/* 80456278 004531B8  D0 1C 00 3C */	stfs f0, 0x3c(r28)
/* 8045627C 004531BC  90 E1 00 08 */	stw r7, 8(r1)
/* 80456280 004531C0  90 C1 00 0C */	stw r6, 0xc(r1)
/* 80456284 004531C4  90 E1 00 10 */	stw r7, 0x10(r1)
/* 80456288 004531C8  90 C1 00 14 */	stw r6, 0x14(r1)
/* 8045628C 004531CC  90 1C 00 5C */	stw r0, 0x5c(r28)
/* 80456290 004531D0  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80456294 004531D4  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80456298 004531D8  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8045629C 004531DC  83 81 00 20 */	lwz r28, 0x20(r1)
/* 804562A0 004531E0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 804562A4 004531E4  7C 08 03 A6 */	mtlr r0
/* 804562A8 004531E8  38 21 00 30 */	addi r1, r1, 0x30
/* 804562AC 004531EC  4E 80 00 20 */	blr 

.global addOption__4MenuFiPcP18IDelegate1$$0R4Menu$$1b
addOption__4MenuFiPcP18IDelegate1$$0R4Menu$$1b:
/* 804562B0 004531F0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 804562B4 004531F4  7C 08 02 A6 */	mflr r0
/* 804562B8 004531F8  90 01 00 24 */	stw r0, 0x24(r1)
/* 804562BC 004531FC  BF 61 00 0C */	stmw r27, 0xc(r1)
/* 804562C0 00453200  7C 7B 1B 78 */	mr r27, r3
/* 804562C4 00453204  7C 9C 23 78 */	mr r28, r4
/* 804562C8 00453208  7C BD 2B 78 */	mr r29, r5
/* 804562CC 0045320C  7C DE 33 78 */	mr r30, r6
/* 804562D0 00453210  7C FF 3B 78 */	mr r31, r7
/* 804562D4 00453214  38 60 00 30 */	li r3, 0x30
/* 804562D8 00453218  4B BC DB CD */	bl __nw__FUl
/* 804562DC 0045321C  7C 60 1B 79 */	or. r0, r3, r3
/* 804562E0 00453220  41 82 00 18 */	beq lbl_804562F8
/* 804562E4 00453224  7F 85 E3 78 */	mr r5, r28
/* 804562E8 00453228  7F A6 EB 78 */	mr r6, r29
/* 804562EC 0045322C  38 80 00 01 */	li r4, 1
/* 804562F0 00453230  48 00 05 51 */	bl __ct__Q24Menu8MenuItemFQ34Menu8MenuItem9cTypeFlagiPc
/* 804562F4 00453234  7C 60 1B 78 */	mr r0, r3
lbl_804562F8:
/* 804562F8 00453238  90 1B 00 28 */	stw r0, 0x28(r27)
/* 804562FC 0045323C  38 7B 00 18 */	addi r3, r27, 0x18
/* 80456300 00453240  80 9B 00 28 */	lwz r4, 0x28(r27)
/* 80456304 00453244  9B E4 00 04 */	stb r31, 4(r4)
/* 80456308 00453248  80 9B 00 28 */	lwz r4, 0x28(r27)
/* 8045630C 0045324C  38 84 00 20 */	addi r4, r4, 0x20
/* 80456310 00453250  4B BD 05 D5 */	bl append__10JSUPtrListFP10JSUPtrLink
/* 80456314 00453254  28 1E 00 00 */	cmplwi r30, 0
/* 80456318 00453258  41 82 00 18 */	beq lbl_80456330
/* 8045631C 0045325C  80 BB 00 5C */	lwz r5, 0x5c(r27)
/* 80456320 00453260  7F 63 DB 78 */	mr r3, r27
/* 80456324 00453264  7F C6 F3 78 */	mr r6, r30
/* 80456328 00453268  38 80 00 10 */	li r4, 0x10
/* 8045632C 0045326C  48 00 00 45 */	bl addKeyEvent__4MenuFQ34Menu8KeyEvent9cTypeFlagUlP18IDelegate1$$0R4Menu$$1
lbl_80456330:
/* 80456330 00453270  80 1B 00 24 */	lwz r0, 0x24(r27)
/* 80456334 00453274  28 00 00 00 */	cmplwi r0, 0
/* 80456338 00453278  40 82 00 18 */	bne lbl_80456350
/* 8045633C 0045327C  80 7B 00 28 */	lwz r3, 0x28(r27)
/* 80456340 00453280  88 03 00 04 */	lbz r0, 4(r3)
/* 80456344 00453284  28 00 00 00 */	cmplwi r0, 0
/* 80456348 00453288  41 82 00 08 */	beq lbl_80456350
/* 8045634C 0045328C  90 7B 00 24 */	stw r3, 0x24(r27)
lbl_80456350:
/* 80456350 00453290  80 7B 00 30 */	lwz r3, 0x30(r27)
/* 80456354 00453294  38 03 00 01 */	addi r0, r3, 1
/* 80456358 00453298  90 1B 00 30 */	stw r0, 0x30(r27)
/* 8045635C 0045329C  BB 61 00 0C */	lmw r27, 0xc(r1)
/* 80456360 004532A0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80456364 004532A4  7C 08 03 A6 */	mtlr r0
/* 80456368 004532A8  38 21 00 20 */	addi r1, r1, 0x20
/* 8045636C 004532AC  4E 80 00 20 */	blr 

.global addKeyEvent__4MenuFQ34Menu8KeyEvent9cTypeFlagUlP18IDelegate1$$0R4Menu$$1
addKeyEvent__4MenuFQ34Menu8KeyEvent9cTypeFlagUlP18IDelegate1$$0R4Menu$$1:
/* 80456370 004532B0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80456374 004532B4  7C 08 02 A6 */	mflr r0
/* 80456378 004532B8  90 01 00 24 */	stw r0, 0x24(r1)
/* 8045637C 004532BC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80456380 004532C0  7C DF 33 78 */	mr r31, r6
/* 80456384 004532C4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80456388 004532C8  7C BE 2B 78 */	mr r30, r5
/* 8045638C 004532CC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80456390 004532D0  7C 9D 23 78 */	mr r29, r4
/* 80456394 004532D4  93 81 00 10 */	stw r28, 0x10(r1)
/* 80456398 004532D8  7C 7C 1B 78 */	mr r28, r3
/* 8045639C 004532DC  38 60 00 1C */	li r3, 0x1c
/* 804563A0 004532E0  4B BC DB 05 */	bl __nw__FUl
/* 804563A4 004532E4  7C 64 1B 79 */	or. r4, r3, r3
/* 804563A8 004532E8  41 82 00 18 */	beq lbl_804563C0
/* 804563AC 004532EC  7F A4 EB 78 */	mr r4, r29
/* 804563B0 004532F0  7F C5 F3 78 */	mr r5, r30
/* 804563B4 004532F4  7F E6 FB 78 */	mr r6, r31
/* 804563B8 004532F8  48 00 04 21 */	bl __ct__Q24Menu8KeyEventFQ34Menu8KeyEvent9cTypeFlagUlP18IDelegate1$$0R4Menu$$1
/* 804563BC 004532FC  7C 64 1B 78 */	mr r4, r3
lbl_804563C0:
/* 804563C0 00453300  80 7C 00 28 */	lwz r3, 0x28(r28)
/* 804563C4 00453304  28 03 00 00 */	cmplwi r3, 0
/* 804563C8 00453308  41 82 00 14 */	beq lbl_804563DC
/* 804563CC 0045330C  38 63 00 14 */	addi r3, r3, 0x14
/* 804563D0 00453310  38 84 00 0C */	addi r4, r4, 0xc
/* 804563D4 00453314  4B BD 05 11 */	bl append__10JSUPtrListFP10JSUPtrLink
/* 804563D8 00453318  48 00 00 40 */	b lbl_80456418
lbl_804563DC:
/* 804563DC 0045331C  80 7C 00 18 */	lwz r3, 0x18(r28)
/* 804563E0 00453320  28 03 00 00 */	cmplwi r3, 0
/* 804563E4 00453324  41 82 00 18 */	beq lbl_804563FC
/* 804563E8 00453328  80 63 00 00 */	lwz r3, 0(r3)
/* 804563EC 0045332C  38 84 00 0C */	addi r4, r4, 0xc
/* 804563F0 00453330  38 63 00 14 */	addi r3, r3, 0x14
/* 804563F4 00453334  4B BD 04 F1 */	bl append__10JSUPtrListFP10JSUPtrLink
/* 804563F8 00453338  48 00 00 20 */	b lbl_80456418
lbl_804563FC:
/* 804563FC 0045333C  3C 60 80 4A */	lis r3, lbl_8049CD78@ha
/* 80456400 00453340  3C A0 80 4A */	lis r5, lbl_8049CD84@ha
/* 80456404 00453344  38 63 CD 78 */	addi r3, r3, lbl_8049CD78@l
/* 80456408 00453348  38 80 00 B7 */	li r4, 0xb7
/* 8045640C 0045334C  38 A5 CD 84 */	addi r5, r5, lbl_8049CD84@l
/* 80456410 00453350  4C C6 31 82 */	crclr 6
/* 80456414 00453354  4B BD 42 2D */	bl panic_f__12JUTExceptionFPCciPCce
lbl_80456418:
/* 80456418 00453358  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8045641C 0045335C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80456420 00453360  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80456424 00453364  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80456428 00453368  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8045642C 0045336C  7C 08 03 A6 */	mtlr r0
/* 80456430 00453370  38 21 00 20 */	addi r1, r1, 0x20
/* 80456434 00453374  4E 80 00 20 */	blr 

.global doUpdate__4MenuFb
doUpdate__4MenuFb:
/* 80456438 00453378  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8045643C 0045337C  7C 08 02 A6 */	mflr r0
/* 80456440 00453380  C0 42 28 98 */	lfs f2, lbl_80520BF8@sda21(r2)
/* 80456444 00453384  90 01 00 24 */	stw r0, 0x24(r1)
/* 80456448 00453388  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8045644C 0045338C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80456450 00453390  7C 7E 1B 78 */	mr r30, r3
/* 80456454 00453394  7F DF F3 78 */	mr r31, r30
/* 80456458 00453398  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8045645C 0045339C  93 C3 00 10 */	stw r30, 0x10(r3)
/* 80456460 004533A0  80 6D 9A EC */	lwz r3, sys@sda21(r13)
/* 80456464 004533A4  C0 1E 00 3C */	lfs f0, 0x3c(r30)
/* 80456468 004533A8  C0 23 00 54 */	lfs f1, 0x54(r3)
/* 8045646C 004533AC  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 80456470 004533B0  D0 1E 00 3C */	stfs f0, 0x3c(r30)
/* 80456474 004533B4  80 1E 00 34 */	lwz r0, 0x34(r30)
/* 80456478 004533B8  2C 00 00 02 */	cmpwi r0, 2
/* 8045647C 004533BC  41 82 00 98 */	beq lbl_80456514
/* 80456480 004533C0  40 80 00 10 */	bge lbl_80456490
/* 80456484 004533C4  2C 00 00 01 */	cmpwi r0, 1
/* 80456488 004533C8  40 80 00 14 */	bge lbl_8045649C
/* 8045648C 004533CC  48 00 03 2C */	b lbl_804567B8
lbl_80456490:
/* 80456490 004533D0  2C 00 00 04 */	cmpwi r0, 4
/* 80456494 004533D4  40 80 03 24 */	bge lbl_804567B8
/* 80456498 004533D8  48 00 00 40 */	b lbl_804564D8
lbl_8045649C:
/* 8045649C 004533DC  80 6D 9A EC */	lwz r3, sys@sda21(r13)
/* 804564A0 004533E0  C0 62 28 9C */	lfs f3, lbl_80520BFC@sda21(r2)
/* 804564A4 004533E4  C0 43 00 54 */	lfs f2, 0x54(r3)
/* 804564A8 004533E8  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 804564AC 004533EC  C0 02 28 94 */	lfs f0, lbl_80520BF4@sda21(r2)
/* 804564B0 004533F0  EC 23 08 BA */	fmadds f1, f3, f2, f1
/* 804564B4 004533F4  D0 3E 00 38 */	stfs f1, 0x38(r30)
/* 804564B8 004533F8  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 804564BC 004533FC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 804564C0 00453400  4C 41 13 82 */	cror 2, 1, 2
/* 804564C4 00453404  40 82 02 F4 */	bne lbl_804567B8
/* 804564C8 00453408  D0 1E 00 38 */	stfs f0, 0x38(r30)
/* 804564CC 0045340C  38 00 00 02 */	li r0, 2
/* 804564D0 00453410  90 1E 00 34 */	stw r0, 0x34(r30)
/* 804564D4 00453414  48 00 02 E4 */	b lbl_804567B8
lbl_804564D8:
/* 804564D8 00453418  80 6D 9A EC */	lwz r3, sys@sda21(r13)
/* 804564DC 0045341C  C0 62 28 9C */	lfs f3, lbl_80520BFC@sda21(r2)
/* 804564E0 00453420  C0 43 00 54 */	lfs f2, 0x54(r3)
/* 804564E4 00453424  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 804564E8 00453428  C0 02 28 90 */	lfs f0, lbl_80520BF0@sda21(r2)
/* 804564EC 0045342C  EC 23 08 BC */	fnmsubs f1, f3, f2, f1
/* 804564F0 00453430  D0 3E 00 38 */	stfs f1, 0x38(r30)
/* 804564F4 00453434  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 804564F8 00453438  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 804564FC 0045343C  40 80 02 BC */	bge lbl_804567B8
/* 80456500 00453440  D0 1E 00 38 */	stfs f0, 0x38(r30)
/* 80456504 00453444  38 00 00 00 */	li r0, 0
/* 80456508 00453448  90 1E 00 34 */	stw r0, 0x34(r30)
/* 8045650C 0045344C  83 FE 00 14 */	lwz r31, 0x14(r30)
/* 80456510 00453450  48 00 02 A8 */	b lbl_804567B8
lbl_80456514:
/* 80456514 00453454  54 80 06 3F */	clrlwi. r0, r4, 0x18
/* 80456518 00453458  41 82 00 0C */	beq lbl_80456524
/* 8045651C 0045345C  38 00 00 01 */	li r0, 1
/* 80456520 00453460  98 1E 00 59 */	stb r0, 0x59(r30)
lbl_80456524:
/* 80456524 00453464  80 9E 00 00 */	lwz r4, 0(r30)
/* 80456528 00453468  3C 60 04 00 */	lis r3, 0x04000004@ha
/* 8045652C 0045346C  38 03 00 04 */	addi r0, r3, 0x04000004@l
/* 80456530 00453470  80 84 00 30 */	lwz r4, 0x30(r4)
/* 80456534 00453474  7C 80 00 39 */	and. r0, r4, r0
/* 80456538 00453478  41 82 00 94 */	beq lbl_804565CC
/* 8045653C 0045347C  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 80456540 00453480  7F C4 F3 78 */	mr r4, r30
/* 80456544 00453484  38 A0 00 02 */	li r5, 2
/* 80456548 00453488  48 00 03 B1 */	bl checkEvents__Q24Menu8MenuItemFP4Menui
/* 8045654C 0045348C  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 80456550 00453490  48 00 03 71 */	bl getNext__Q24Menu8MenuItemFv
/* 80456554 00453494  90 7E 00 24 */	stw r3, 0x24(r30)
/* 80456558 00453498  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 8045655C 0045349C  28 00 00 00 */	cmplwi r0, 0
/* 80456560 004534A0  40 82 00 34 */	bne lbl_80456594
/* 80456564 004534A4  80 7E 00 18 */	lwz r3, 0x18(r30)
/* 80456568 004534A8  80 03 00 00 */	lwz r0, 0(r3)
/* 8045656C 004534AC  90 1E 00 24 */	stw r0, 0x24(r30)
/* 80456570 004534B0  48 00 00 24 */	b lbl_80456594
lbl_80456574:
/* 80456574 004534B4  48 00 03 4D */	bl getNext__Q24Menu8MenuItemFv
/* 80456578 004534B8  90 7E 00 24 */	stw r3, 0x24(r30)
/* 8045657C 004534BC  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 80456580 004534C0  28 00 00 00 */	cmplwi r0, 0
/* 80456584 004534C4  40 82 00 10 */	bne lbl_80456594
/* 80456588 004534C8  80 7E 00 18 */	lwz r3, 0x18(r30)
/* 8045658C 004534CC  80 03 00 00 */	lwz r0, 0(r3)
/* 80456590 004534D0  90 1E 00 24 */	stw r0, 0x24(r30)
lbl_80456594:
/* 80456594 004534D4  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 80456598 004534D8  80 03 00 08 */	lwz r0, 8(r3)
/* 8045659C 004534DC  28 00 00 00 */	cmplwi r0, 0
/* 804565A0 004534E0  41 82 FF D4 */	beq lbl_80456574
/* 804565A4 004534E4  88 03 00 04 */	lbz r0, 4(r3)
/* 804565A8 004534E8  28 00 00 00 */	cmplwi r0, 0
/* 804565AC 004534EC  41 82 FF C8 */	beq lbl_80456574
/* 804565B0 004534F0  38 00 00 01 */	li r0, 1
/* 804565B4 004534F4  38 80 18 02 */	li r4, 0x1802
/* 804565B8 004534F8  98 1E 00 59 */	stb r0, 0x59(r30)
/* 804565BC 004534FC  38 A0 00 00 */	li r5, 0
/* 804565C0 00453500  80 6D 98 58 */	lwz r3, spSysIF__8PSSystem@sda21(r13)
/* 804565C4 00453504  4B EE 20 6D */	bl playSystemSe__Q28PSSystem5SysIFFUlUl
/* 804565C8 00453508  48 00 00 98 */	b lbl_80456660
lbl_804565CC:
/* 804565CC 0045350C  3C 60 08 00 */	lis r3, 0x08000008@ha
/* 804565D0 00453510  38 03 00 08 */	addi r0, r3, 0x08000008@l
/* 804565D4 00453514  7C 80 00 39 */	and. r0, r4, r0
/* 804565D8 00453518  41 82 00 88 */	beq lbl_80456660
/* 804565DC 0045351C  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 804565E0 00453520  7F C4 F3 78 */	mr r4, r30
/* 804565E4 00453524  38 A0 00 02 */	li r5, 2
/* 804565E8 00453528  48 00 03 11 */	bl checkEvents__Q24Menu8MenuItemFP4Menui
/* 804565EC 0045352C  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 804565F0 00453530  48 00 02 ED */	bl getPrev__Q24Menu8MenuItemFv
/* 804565F4 00453534  90 7E 00 24 */	stw r3, 0x24(r30)
/* 804565F8 00453538  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 804565FC 0045353C  28 00 00 00 */	cmplwi r0, 0
/* 80456600 00453540  40 82 00 34 */	bne lbl_80456634
/* 80456604 00453544  80 7E 00 1C */	lwz r3, 0x1c(r30)
/* 80456608 00453548  80 03 00 00 */	lwz r0, 0(r3)
/* 8045660C 0045354C  90 1E 00 24 */	stw r0, 0x24(r30)
/* 80456610 00453550  48 00 00 24 */	b lbl_80456634
lbl_80456614:
/* 80456614 00453554  48 00 02 C9 */	bl getPrev__Q24Menu8MenuItemFv
/* 80456618 00453558  90 7E 00 24 */	stw r3, 0x24(r30)
/* 8045661C 0045355C  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 80456620 00453560  28 00 00 00 */	cmplwi r0, 0
/* 80456624 00453564  40 82 00 10 */	bne lbl_80456634
/* 80456628 00453568  80 7E 00 1C */	lwz r3, 0x1c(r30)
/* 8045662C 0045356C  80 03 00 00 */	lwz r0, 0(r3)
/* 80456630 00453570  90 1E 00 24 */	stw r0, 0x24(r30)
lbl_80456634:
/* 80456634 00453574  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 80456638 00453578  80 03 00 08 */	lwz r0, 8(r3)
/* 8045663C 0045357C  28 00 00 00 */	cmplwi r0, 0
/* 80456640 00453580  41 82 FF D4 */	beq lbl_80456614
/* 80456644 00453584  88 03 00 04 */	lbz r0, 4(r3)
/* 80456648 00453588  28 00 00 00 */	cmplwi r0, 0
/* 8045664C 0045358C  41 82 FF C8 */	beq lbl_80456614
/* 80456650 00453590  80 6D 98 58 */	lwz r3, spSysIF__8PSSystem@sda21(r13)
/* 80456654 00453594  38 80 18 02 */	li r4, 0x1802
/* 80456658 00453598  38 A0 00 00 */	li r5, 0
/* 8045665C 0045359C  4B EE 1F D5 */	bl playSystemSe__Q28PSSystem5SysIFFUlUl
lbl_80456660:
/* 80456660 004535A0  88 1E 00 58 */	lbz r0, 0x58(r30)
/* 80456664 004535A4  28 00 00 00 */	cmplwi r0, 0
/* 80456668 004535A8  41 82 00 34 */	beq lbl_8045669C
/* 8045666C 004535AC  80 7E 00 4C */	lwz r3, 0x4c(r30)
/* 80456670 004535B0  28 03 00 00 */	cmplwi r3, 0
/* 80456674 004535B4  41 82 00 18 */	beq lbl_8045668C
/* 80456678 004535B8  81 83 00 00 */	lwz r12, 0(r3)
/* 8045667C 004535BC  7F C4 F3 78 */	mr r4, r30
/* 80456680 004535C0  81 8C 00 08 */	lwz r12, 8(r12)
/* 80456684 004535C4  7D 89 03 A6 */	mtctr r12
/* 80456688 004535C8  4E 80 04 21 */	bctrl 
lbl_8045668C:
/* 8045668C 004535CC  38 60 00 00 */	li r3, 0
/* 80456690 004535D0  38 00 00 01 */	li r0, 1
/* 80456694 004535D4  98 7E 00 58 */	stb r3, 0x58(r30)
/* 80456698 004535D8  98 1E 00 59 */	stb r0, 0x59(r30)
lbl_8045669C:
/* 8045669C 004535DC  88 1E 00 59 */	lbz r0, 0x59(r30)
/* 804566A0 004535E0  3C 60 00 01 */	lis r3, 0x0000FFFC@ha
/* 804566A4 004535E4  3B A3 FF FC */	addi r29, r3, 0x0000FFFC@l
/* 804566A8 004535E8  28 00 00 00 */	cmplwi r0, 0
/* 804566AC 004535EC  41 82 00 38 */	beq lbl_804566E4
/* 804566B0 004535F0  80 7E 00 54 */	lwz r3, 0x54(r30)
/* 804566B4 004535F4  63 BD 00 01 */	ori r29, r29, 1
/* 804566B8 004535F8  28 03 00 00 */	cmplwi r3, 0
/* 804566BC 004535FC  41 82 00 18 */	beq lbl_804566D4
/* 804566C0 00453600  81 83 00 00 */	lwz r12, 0(r3)
/* 804566C4 00453604  7F C4 F3 78 */	mr r4, r30
/* 804566C8 00453608  81 8C 00 08 */	lwz r12, 8(r12)
/* 804566CC 0045360C  7D 89 03 A6 */	mtctr r12
/* 804566D0 00453610  4E 80 04 21 */	bctrl 
lbl_804566D4:
/* 804566D4 00453614  C0 02 28 90 */	lfs f0, lbl_80520BF0@sda21(r2)
/* 804566D8 00453618  38 00 00 00 */	li r0, 0
/* 804566DC 0045361C  D0 1E 00 3C */	stfs f0, 0x3c(r30)
/* 804566E0 00453620  98 1E 00 59 */	stb r0, 0x59(r30)
lbl_804566E4:
/* 804566E4 00453624  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 804566E8 00453628  7F C4 F3 78 */	mr r4, r30
/* 804566EC 0045362C  7F A5 EB 78 */	mr r5, r29
/* 804566F0 00453630  48 00 02 09 */	bl checkEvents__Q24Menu8MenuItemFP4Menui
/* 804566F4 00453634  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 804566F8 00453638  40 82 00 18 */	bne lbl_80456710
/* 804566FC 0045363C  80 7E 00 18 */	lwz r3, 0x18(r30)
/* 80456700 00453640  7F C4 F3 78 */	mr r4, r30
/* 80456704 00453644  7F A5 EB 78 */	mr r5, r29
/* 80456708 00453648  80 63 00 00 */	lwz r3, 0(r3)
/* 8045670C 0045364C  48 00 01 ED */	bl checkEvents__Q24Menu8MenuItemFP4Menui
lbl_80456710:
/* 80456710 00453650  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 80456714 00453654  7C 00 F0 40 */	cmplw r0, r30
/* 80456718 00453658  41 82 00 A0 */	beq lbl_804567B8
/* 8045671C 0045365C  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 80456720 00453660  7F C4 F3 78 */	mr r4, r30
/* 80456724 00453664  38 A0 00 02 */	li r5, 2
/* 80456728 00453668  48 00 01 D1 */	bl checkEvents__Q24Menu8MenuItemFP4Menui
/* 8045672C 0045366C  80 7E 00 50 */	lwz r3, 0x50(r30)
/* 80456730 00453670  28 03 00 00 */	cmplwi r3, 0
/* 80456734 00453674  41 82 00 18 */	beq lbl_8045674C
/* 80456738 00453678  81 83 00 00 */	lwz r12, 0(r3)
/* 8045673C 0045367C  7F C4 F3 78 */	mr r4, r30
/* 80456740 00453680  81 8C 00 08 */	lwz r12, 8(r12)
/* 80456744 00453684  7D 89 03 A6 */	mtctr r12
/* 80456748 00453688  4E 80 04 21 */	bctrl 
lbl_8045674C:
/* 8045674C 0045368C  80 7E 00 10 */	lwz r3, 0x10(r30)
/* 80456750 00453690  28 03 00 00 */	cmplwi r3, 0
/* 80456754 00453694  41 82 00 3C */	beq lbl_80456790
/* 80456758 00453698  C0 02 28 90 */	lfs f0, lbl_80520BF0@sda21(r2)
/* 8045675C 0045369C  38 00 00 01 */	li r0, 1
/* 80456760 004536A0  D0 03 00 38 */	stfs f0, 0x38(r3)
/* 80456764 004536A4  90 03 00 34 */	stw r0, 0x34(r3)
/* 80456768 004536A8  80 03 00 24 */	lwz r0, 0x24(r3)
/* 8045676C 004536AC  28 00 00 00 */	cmplwi r0, 0
/* 80456770 004536B0  40 82 00 18 */	bne lbl_80456788
/* 80456774 004536B4  80 83 00 18 */	lwz r4, 0x18(r3)
/* 80456778 004536B8  28 04 00 00 */	cmplwi r4, 0
/* 8045677C 004536BC  40 82 00 0C */	bne lbl_80456788
/* 80456780 004536C0  80 04 00 00 */	lwz r0, 0(r4)
/* 80456784 004536C4  90 03 00 24 */	stw r0, 0x24(r3)
lbl_80456788:
/* 80456788 004536C8  83 FE 00 10 */	lwz r31, 0x10(r30)
/* 8045678C 004536CC  48 00 00 24 */	b lbl_804567B0
lbl_80456790:
/* 80456790 004536D0  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 80456794 004536D4  28 00 00 00 */	cmplwi r0, 0
/* 80456798 004536D8  40 82 00 08 */	bne lbl_804567A0
/* 8045679C 004536DC  90 1E 00 10 */	stw r0, 0x10(r30)
lbl_804567A0:
/* 804567A0 004536E0  C0 02 28 94 */	lfs f0, lbl_80520BF4@sda21(r2)
/* 804567A4 004536E4  38 00 00 03 */	li r0, 3
/* 804567A8 004536E8  D0 1E 00 38 */	stfs f0, 0x38(r30)
/* 804567AC 004536EC  90 1E 00 34 */	stw r0, 0x34(r30)
lbl_804567B0:
/* 804567B0 004536F0  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 804567B4 004536F4  90 1E 00 14 */	stw r0, 0x14(r30)
lbl_804567B8:
/* 804567B8 004536F8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 804567BC 004536FC  7F E3 FB 78 */	mr r3, r31
/* 804567C0 00453700  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 804567C4 00453704  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 804567C8 00453708  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 804567CC 0045370C  7C 08 03 A6 */	mtlr r0
/* 804567D0 00453710  38 21 00 20 */	addi r1, r1, 0x20
/* 804567D4 00453714  4E 80 00 20 */	blr 

.global __ct__Q24Menu8KeyEventFQ34Menu8KeyEvent9cTypeFlagUlP18IDelegate1$$0R4Menu$$1
__ct__Q24Menu8KeyEventFQ34Menu8KeyEvent9cTypeFlagUlP18IDelegate1$$0R4Menu$$1:
/* 804567D8 00453718  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 804567DC 0045371C  7C 08 02 A6 */	mflr r0
/* 804567E0 00453720  90 01 00 24 */	stw r0, 0x24(r1)
/* 804567E4 00453724  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 804567E8 00453728  7C DF 33 78 */	mr r31, r6
/* 804567EC 0045372C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 804567F0 00453730  7C BE 2B 78 */	mr r30, r5
/* 804567F4 00453734  93 A1 00 14 */	stw r29, 0x14(r1)
/* 804567F8 00453738  7C 9D 23 78 */	mr r29, r4
/* 804567FC 0045373C  93 81 00 10 */	stw r28, 0x10(r1)
/* 80456800 00453740  7C 7C 1B 78 */	mr r28, r3
/* 80456804 00453744  7F 84 E3 78 */	mr r4, r28
/* 80456808 00453748  38 7C 00 0C */	addi r3, r28, 0xc
/* 8045680C 0045374C  4B BC FF AD */	bl __ct__10JSUPtrLinkFPv
/* 80456810 00453750  93 BC 00 00 */	stw r29, 0(r28)
/* 80456814 00453754  7F 83 E3 78 */	mr r3, r28
/* 80456818 00453758  93 DC 00 04 */	stw r30, 4(r28)
/* 8045681C 0045375C  93 FC 00 08 */	stw r31, 8(r28)
/* 80456820 00453760  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80456824 00453764  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80456828 00453768  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8045682C 0045376C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80456830 00453770  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80456834 00453774  7C 08 03 A6 */	mtlr r0
/* 80456838 00453778  38 21 00 20 */	addi r1, r1, 0x20
/* 8045683C 0045377C  4E 80 00 20 */	blr 

.global __ct__Q24Menu8MenuItemFQ34Menu8MenuItem9cTypeFlagiPc
__ct__Q24Menu8MenuItemFQ34Menu8MenuItem9cTypeFlagiPc:
/* 80456840 00453780  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80456844 00453784  7C 08 02 A6 */	mflr r0
/* 80456848 00453788  90 01 00 24 */	stw r0, 0x24(r1)
/* 8045684C 0045378C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80456850 00453790  7C DF 33 78 */	mr r31, r6
/* 80456854 00453794  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80456858 00453798  7C BE 2B 78 */	mr r30, r5
/* 8045685C 0045379C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80456860 004537A0  7C 9D 23 78 */	mr r29, r4
/* 80456864 004537A4  93 81 00 10 */	stw r28, 0x10(r1)
/* 80456868 004537A8  7C 7C 1B 78 */	mr r28, r3
/* 8045686C 004537AC  38 7C 00 14 */	addi r3, r28, 0x14
/* 80456870 004537B0  4B BD 00 61 */	bl initiate__10JSUPtrListFv
/* 80456874 004537B4  7F 84 E3 78 */	mr r4, r28
/* 80456878 004537B8  38 7C 00 20 */	addi r3, r28, 0x20
/* 8045687C 004537BC  4B BC FF 3D */	bl __ct__10JSUPtrLinkFPv
/* 80456880 004537C0  38 60 00 01 */	li r3, 1
/* 80456884 004537C4  38 00 00 00 */	li r0, 0
/* 80456888 004537C8  98 7C 00 04 */	stb r3, 4(r28)
/* 8045688C 004537CC  7F 83 E3 78 */	mr r3, r28
/* 80456890 004537D0  93 FC 00 08 */	stw r31, 8(r28)
/* 80456894 004537D4  93 DC 00 0C */	stw r30, 0xc(r28)
/* 80456898 004537D8  93 BC 00 10 */	stw r29, 0x10(r28)
/* 8045689C 004537DC  90 1C 00 00 */	stw r0, 0(r28)
/* 804568A0 004537E0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 804568A4 004537E4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 804568A8 004537E8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 804568AC 004537EC  83 81 00 10 */	lwz r28, 0x10(r1)
/* 804568B0 004537F0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 804568B4 004537F4  7C 08 03 A6 */	mtlr r0
/* 804568B8 004537F8  38 21 00 20 */	addi r1, r1, 0x20
/* 804568BC 004537FC  4E 80 00 20 */	blr 

.global getNext__Q24Menu8MenuItemFv
getNext__Q24Menu8MenuItemFv:
/* 804568C0 00453800  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 804568C4 00453804  28 03 00 00 */	cmplwi r3, 0
/* 804568C8 00453808  41 82 00 0C */	beq lbl_804568D4
/* 804568CC 0045380C  80 63 00 00 */	lwz r3, 0(r3)
/* 804568D0 00453810  4E 80 00 20 */	blr 
lbl_804568D4:
/* 804568D4 00453814  38 60 00 00 */	li r3, 0
/* 804568D8 00453818  4E 80 00 20 */	blr 

.global getPrev__Q24Menu8MenuItemFv
getPrev__Q24Menu8MenuItemFv:
/* 804568DC 0045381C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 804568E0 00453820  28 03 00 00 */	cmplwi r3, 0
/* 804568E4 00453824  41 82 00 0C */	beq lbl_804568F0
/* 804568E8 00453828  80 63 00 00 */	lwz r3, 0(r3)
/* 804568EC 0045382C  4E 80 00 20 */	blr 
lbl_804568F0:
/* 804568F0 00453830  38 60 00 00 */	li r3, 0
/* 804568F4 00453834  4E 80 00 20 */	blr 

.global checkEvents__Q24Menu8MenuItemFP4Menui
checkEvents__Q24Menu8MenuItemFP4Menui:
/* 804568F8 00453838  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 804568FC 0045383C  7C 08 02 A6 */	mflr r0
/* 80456900 00453840  90 01 00 24 */	stw r0, 0x24(r1)
/* 80456904 00453844  BF 41 00 08 */	stmw r26, 8(r1)
/* 80456908 00453848  7C 7A 1B 78 */	mr r26, r3
/* 8045690C 0045384C  7C 9B 23 78 */	mr r27, r4
/* 80456910 00453850  7C BC 2B 78 */	mr r28, r5
/* 80456914 00453854  3B C0 00 00 */	li r30, 0
/* 80456918 00453858  83 E3 00 14 */	lwz r31, 0x14(r3)
/* 8045691C 0045385C  48 00 01 BC */	b lbl_80456AD8
lbl_80456920:
/* 80456920 00453860  80 9F 00 00 */	lwz r4, 0(r31)
/* 80456924 00453864  3B A0 00 00 */	li r29, 0
/* 80456928 00453868  80 A4 00 00 */	lwz r5, 0(r4)
/* 8045692C 0045386C  7F 80 28 39 */	and. r0, r28, r5
/* 80456930 00453870  41 82 01 A4 */	beq lbl_80456AD4
/* 80456934 00453874  28 05 00 20 */	cmplwi r5, 0x20
/* 80456938 00453878  41 81 01 94 */	bgt lbl_80456ACC
/* 8045693C 0045387C  3C 60 80 4F */	lis r3, lbl_804EDCC8@ha
/* 80456940 00453880  54 A0 10 3A */	slwi r0, r5, 2
/* 80456944 00453884  38 63 DC C8 */	addi r3, r3, lbl_804EDCC8@l
/* 80456948 00453888  7C 03 00 2E */	lwzx r0, r3, r0
/* 8045694C 0045388C  7C 09 03 A6 */	mtctr r0
/* 80456950 00453890  4E 80 04 20 */	bctr 
/* 80456954 00453894  80 64 00 08 */	lwz r3, 8(r4)
/* 80456958 00453898  7F 64 DB 78 */	mr r4, r27
/* 8045695C 0045389C  81 83 00 00 */	lwz r12, 0(r3)
/* 80456960 004538A0  81 8C 00 08 */	lwz r12, 8(r12)
/* 80456964 004538A4  7D 89 03 A6 */	mtctr r12
/* 80456968 004538A8  4E 80 04 21 */	bctrl 
/* 8045696C 004538AC  48 00 01 60 */	b lbl_80456ACC
/* 80456970 004538B0  80 64 00 08 */	lwz r3, 8(r4)
/* 80456974 004538B4  7F 64 DB 78 */	mr r4, r27
/* 80456978 004538B8  81 83 00 00 */	lwz r12, 0(r3)
/* 8045697C 004538BC  81 8C 00 08 */	lwz r12, 8(r12)
/* 80456980 004538C0  7D 89 03 A6 */	mtctr r12
/* 80456984 004538C4  4E 80 04 21 */	bctrl 
/* 80456988 004538C8  48 00 01 44 */	b lbl_80456ACC
/* 8045698C 004538CC  80 7B 00 00 */	lwz r3, 0(r27)
/* 80456990 004538D0  80 04 00 04 */	lwz r0, 4(r4)
/* 80456994 004538D4  80 63 00 18 */	lwz r3, 0x18(r3)
/* 80456998 004538D8  7C 60 00 39 */	and. r0, r3, r0
/* 8045699C 004538DC  41 82 01 30 */	beq lbl_80456ACC
/* 804569A0 004538E0  80 64 00 08 */	lwz r3, 8(r4)
/* 804569A4 004538E4  7F 64 DB 78 */	mr r4, r27
/* 804569A8 004538E8  81 83 00 00 */	lwz r12, 0(r3)
/* 804569AC 004538EC  81 8C 00 08 */	lwz r12, 8(r12)
/* 804569B0 004538F0  7D 89 03 A6 */	mtctr r12
/* 804569B4 004538F4  4E 80 04 21 */	bctrl 
/* 804569B8 004538F8  48 00 01 14 */	b lbl_80456ACC
/* 804569BC 004538FC  80 7B 00 00 */	lwz r3, 0(r27)
/* 804569C0 00453900  80 04 00 04 */	lwz r0, 4(r4)
/* 804569C4 00453904  80 63 00 1C */	lwz r3, 0x1c(r3)
/* 804569C8 00453908  7C 60 00 39 */	and. r0, r3, r0
/* 804569CC 0045390C  41 82 01 00 */	beq lbl_80456ACC
/* 804569D0 00453910  80 64 00 08 */	lwz r3, 8(r4)
/* 804569D4 00453914  7F 64 DB 78 */	mr r4, r27
/* 804569D8 00453918  81 83 00 00 */	lwz r12, 0(r3)
/* 804569DC 0045391C  81 8C 00 08 */	lwz r12, 8(r12)
/* 804569E0 00453920  7D 89 03 A6 */	mtctr r12
/* 804569E4 00453924  4E 80 04 21 */	bctrl 
/* 804569E8 00453928  3B C0 00 01 */	li r30, 1
/* 804569EC 0045392C  3B A0 00 01 */	li r29, 1
/* 804569F0 00453930  48 00 00 DC */	b lbl_80456ACC
/* 804569F4 00453934  80 7B 00 00 */	lwz r3, 0(r27)
/* 804569F8 00453938  80 04 00 04 */	lwz r0, 4(r4)
/* 804569FC 0045393C  80 63 00 1C */	lwz r3, 0x1c(r3)
/* 80456A00 00453940  7C 60 00 39 */	and. r0, r3, r0
/* 80456A04 00453944  41 82 00 C8 */	beq lbl_80456ACC
/* 80456A08 00453948  80 7B 00 24 */	lwz r3, 0x24(r27)
/* 80456A0C 0045394C  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80456A10 00453950  2C 00 00 02 */	cmpwi r0, 2
/* 80456A14 00453954  40 82 00 98 */	bne lbl_80456AAC
/* 80456A18 00453958  7F 43 D3 78 */	mr r3, r26
/* 80456A1C 0045395C  7F 64 DB 78 */	mr r4, r27
/* 80456A20 00453960  38 A0 00 02 */	li r5, 2
/* 80456A24 00453964  4B FF FE D5 */	bl checkEvents__Q24Menu8MenuItemFP4Menui
/* 80456A28 00453968  80 1B 00 0C */	lwz r0, 0xc(r27)
/* 80456A2C 0045396C  28 00 00 00 */	cmplwi r0, 0
/* 80456A30 00453970  40 82 00 08 */	bne lbl_80456A38
/* 80456A34 00453974  90 1B 00 10 */	stw r0, 0x10(r27)
lbl_80456A38:
/* 80456A38 00453978  C0 22 28 94 */	lfs f1, lbl_80520BF4@sda21(r2)
/* 80456A3C 0045397C  38 60 00 03 */	li r3, 3
/* 80456A40 00453980  C0 02 28 90 */	lfs f0, lbl_80520BF0@sda21(r2)
/* 80456A44 00453984  38 00 00 01 */	li r0, 1
/* 80456A48 00453988  D0 3B 00 38 */	stfs f1, 0x38(r27)
/* 80456A4C 0045398C  90 7B 00 34 */	stw r3, 0x34(r27)
/* 80456A50 00453990  93 7B 00 10 */	stw r27, 0x10(r27)
/* 80456A54 00453994  80 7B 00 24 */	lwz r3, 0x24(r27)
/* 80456A58 00453998  80 63 00 00 */	lwz r3, 0(r3)
/* 80456A5C 0045399C  90 7B 00 14 */	stw r3, 0x14(r27)
/* 80456A60 004539A0  80 7B 00 14 */	lwz r3, 0x14(r27)
/* 80456A64 004539A4  D0 03 00 38 */	stfs f0, 0x38(r3)
/* 80456A68 004539A8  90 03 00 34 */	stw r0, 0x34(r3)
/* 80456A6C 004539AC  80 03 00 24 */	lwz r0, 0x24(r3)
/* 80456A70 004539B0  28 00 00 00 */	cmplwi r0, 0
/* 80456A74 004539B4  40 82 00 18 */	bne lbl_80456A8C
/* 80456A78 004539B8  80 83 00 18 */	lwz r4, 0x18(r3)
/* 80456A7C 004539BC  28 04 00 00 */	cmplwi r4, 0
/* 80456A80 004539C0  40 82 00 0C */	bne lbl_80456A8C
/* 80456A84 004539C4  80 04 00 00 */	lwz r0, 0(r4)
/* 80456A88 004539C8  90 03 00 24 */	stw r0, 0x24(r3)
lbl_80456A8C:
/* 80456A8C 004539CC  38 00 00 01 */	li r0, 1
/* 80456A90 004539D0  3B C0 00 00 */	li r30, 0
/* 80456A94 004539D4  98 1B 00 58 */	stb r0, 0x58(r27)
/* 80456A98 004539D8  3B A0 00 01 */	li r29, 1
/* 80456A9C 004539DC  80 7B 00 24 */	lwz r3, 0x24(r27)
/* 80456AA0 004539E0  80 63 00 00 */	lwz r3, 0(r3)
/* 80456AA4 004539E4  98 03 00 58 */	stb r0, 0x58(r3)
/* 80456AA8 004539E8  48 00 00 24 */	b lbl_80456ACC
lbl_80456AAC:
/* 80456AAC 004539EC  80 64 00 08 */	lwz r3, 8(r4)
/* 80456AB0 004539F0  7F 64 DB 78 */	mr r4, r27
/* 80456AB4 004539F4  81 83 00 00 */	lwz r12, 0(r3)
/* 80456AB8 004539F8  81 8C 00 08 */	lwz r12, 8(r12)
/* 80456ABC 004539FC  7D 89 03 A6 */	mtctr r12
/* 80456AC0 00453A00  4E 80 04 21 */	bctrl 
/* 80456AC4 00453A04  3B C0 00 01 */	li r30, 1
/* 80456AC8 00453A08  3B A0 00 01 */	li r29, 1
lbl_80456ACC:
/* 80456ACC 00453A0C  57 A0 06 3F */	clrlwi. r0, r29, 0x18
/* 80456AD0 00453A10  40 82 00 10 */	bne lbl_80456AE0
lbl_80456AD4:
/* 80456AD4 00453A14  83 FF 00 0C */	lwz r31, 0xc(r31)
lbl_80456AD8:
/* 80456AD8 00453A18  28 1F 00 00 */	cmplwi r31, 0
/* 80456ADC 00453A1C  40 82 FE 44 */	bne lbl_80456920
lbl_80456AE0:
/* 80456AE0 00453A20  7F C3 F3 78 */	mr r3, r30
/* 80456AE4 00453A24  BB 41 00 08 */	lmw r26, 8(r1)
/* 80456AE8 00453A28  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80456AEC 00453A2C  7C 08 03 A6 */	mtlr r0
/* 80456AF0 00453A30  38 21 00 20 */	addi r1, r1, 0x20
/* 80456AF4 00453A34  4E 80 00 20 */	blr 
