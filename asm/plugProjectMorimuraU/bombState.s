.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global init__Q34Game4Bomb3FSMFPQ24Game9EnemyBase
init__Q34Game4Bomb3FSMFPQ24Game9EnemyBase:
/* 803493F8 00346338  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 803493FC 0034633C  7C 08 02 A6 */	mflr r0
/* 80349400 00346340  38 80 00 02 */	li r4, 2
/* 80349404 00346344  90 01 00 14 */	stw r0, 0x14(r1)
/* 80349408 00346348  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8034940C 0034634C  7C 7F 1B 78 */	mr r31, r3
/* 80349410 00346350  4B DE 74 55 */	bl create__Q24Game17EnemyStateMachineFi
/* 80349414 00346354  38 60 00 14 */	li r3, 0x14
/* 80349418 00346358  4B CD AA 8D */	bl __nw__FUl
/* 8034941C 0034635C  7C 64 1B 79 */	or. r4, r3, r3
/* 80349420 00346360  41 82 00 10 */	beq lbl_80349430
/* 80349424 00346364  38 80 00 00 */	li r4, 0
/* 80349428 00346368  48 00 00 49 */	bl __ct__Q34Game4Bomb9StateWaitFi
/* 8034942C 0034636C  7C 64 1B 78 */	mr r4, r3
lbl_80349430:
/* 80349430 00346370  7F E3 FB 78 */	mr r3, r31
/* 80349434 00346374  4B DE 74 D5 */	bl registerState__Q24Game17EnemyStateMachineFPQ24Game13EnemyFSMState
/* 80349438 00346378  38 60 00 14 */	li r3, 0x14
/* 8034943C 0034637C  4B CD AA 69 */	bl __nw__FUl
/* 80349440 00346380  7C 64 1B 79 */	or. r4, r3, r3
/* 80349444 00346384  41 82 00 10 */	beq lbl_80349454
/* 80349448 00346388  38 80 00 01 */	li r4, 1
/* 8034944C 0034638C  48 00 02 05 */	bl __ct__Q34Game4Bomb9StateBombFi
/* 80349450 00346390  7C 64 1B 78 */	mr r4, r3
lbl_80349454:
/* 80349454 00346394  7F E3 FB 78 */	mr r3, r31
/* 80349458 00346398  4B DE 74 B1 */	bl registerState__Q24Game17EnemyStateMachineFPQ24Game13EnemyFSMState
/* 8034945C 0034639C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80349460 003463A0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80349464 003463A4  7C 08 03 A6 */	mtlr r0
/* 80349468 003463A8  38 21 00 10 */	addi r1, r1, 0x10
/* 8034946C 003463AC  4E 80 00 20 */	blr 

.global __ct__Q34Game4Bomb9StateWaitFi
__ct__Q34Game4Bomb9StateWaitFi:
/* 80349470 003463B0  3C A0 80 4B */	lis r5, __vt__Q24Game13EnemyFSMState@ha
/* 80349474 003463B4  3C C0 80 4E */	lis r6, __vt__Q34Game4Bomb5State@ha
/* 80349478 003463B8  38 05 F9 A4 */	addi r0, r5, __vt__Q24Game13EnemyFSMState@l
/* 8034947C 003463BC  3C A0 80 4E */	lis r5, __vt__Q34Game4Bomb9StateWait@ha
/* 80349480 003463C0  90 03 00 00 */	stw r0, 0(r3)
/* 80349484 003463C4  38 E0 00 00 */	li r7, 0
/* 80349488 003463C8  38 C6 BA 08 */	addi r6, r6, __vt__Q34Game4Bomb5State@l
/* 8034948C 003463CC  38 A5 B9 E4 */	addi r5, r5, __vt__Q34Game4Bomb9StateWait@l
/* 80349490 003463D0  90 83 00 04 */	stw r4, 4(r3)
/* 80349494 003463D4  38 02 FF A0 */	addi r0, r2, lbl_8051E300@sda21
/* 80349498 003463D8  90 E3 00 08 */	stw r7, 8(r3)
/* 8034949C 003463DC  90 C3 00 00 */	stw r6, 0(r3)
/* 803494A0 003463E0  90 A3 00 00 */	stw r5, 0(r3)
/* 803494A4 003463E4  90 03 00 0C */	stw r0, 0xc(r3)
/* 803494A8 003463E8  4E 80 00 20 */	blr 

.global init__Q34Game4Bomb9StateWaitFPQ24Game9EnemyBasePQ24Game8StateArg
init__Q34Game4Bomb9StateWaitFPQ24Game9EnemyBasePQ24Game8StateArg:
/* 803494AC 003463EC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 803494B0 003463F0  7C 08 02 A6 */	mflr r0
/* 803494B4 003463F4  38 A0 00 00 */	li r5, 0
/* 803494B8 003463F8  90 01 00 14 */	stw r0, 0x14(r1)
/* 803494BC 003463FC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 803494C0 00346400  7C 9F 23 78 */	mr r31, r4
/* 803494C4 00346404  38 80 00 00 */	li r4, 0
/* 803494C8 00346408  93 C1 00 08 */	stw r30, 8(r1)
/* 803494CC 0034640C  7C 7E 1B 78 */	mr r30, r3
/* 803494D0 00346410  7F E3 FB 78 */	mr r3, r31
/* 803494D4 00346414  4B DB BB 31 */	bl startMotion__Q24Game9EnemyBaseFiPQ28SysShape14MotionListener
/* 803494D8 00346418  7F E3 FB 78 */	mr r3, r31
/* 803494DC 0034641C  4B DB DE 05 */	bl stopMotion__Q24Game9EnemyBaseFv
/* 803494E0 00346420  7F E3 FB 78 */	mr r3, r31
/* 803494E4 00346424  4B DB 84 99 */	bl setEmotionCaution__Q24Game9EnemyBaseFv
/* 803494E8 00346428  38 00 00 00 */	li r0, 0
/* 803494EC 0034642C  90 1E 00 10 */	stw r0, 0x10(r30)
/* 803494F0 00346430  80 01 00 14 */	lwz r0, 0x14(r1)
/* 803494F4 00346434  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 803494F8 00346438  83 C1 00 08 */	lwz r30, 8(r1)
/* 803494FC 0034643C  7C 08 03 A6 */	mtlr r0
/* 80349500 00346440  38 21 00 10 */	addi r1, r1, 0x10
/* 80349504 00346444  4E 80 00 20 */	blr 

.global exec__Q34Game4Bomb9StateWaitFPQ24Game9EnemyBase
exec__Q34Game4Bomb9StateWaitFPQ24Game9EnemyBase:
/* 80349508 00346448  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8034950C 0034644C  7C 08 02 A6 */	mflr r0
/* 80349510 00346450  90 01 00 14 */	stw r0, 0x14(r1)
/* 80349514 00346454  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80349518 00346458  7C 9F 23 78 */	mr r31, r4
/* 8034951C 0034645C  93 C1 00 08 */	stw r30, 8(r1)
/* 80349520 00346460  7C 7E 1B 78 */	mr r30, r3
/* 80349524 00346464  88 04 02 BC */	lbz r0, 0x2bc(r4)
/* 80349528 00346468  28 00 00 00 */	cmplwi r0, 0
/* 8034952C 0034646C  41 82 00 34 */	beq lbl_80349560
/* 80349530 00346470  80 1F 00 B8 */	lwz r0, 0xb8(r31)
/* 80349534 00346474  28 00 00 00 */	cmplwi r0, 0
/* 80349538 00346478  40 82 00 28 */	bne lbl_80349560
/* 8034953C 0034647C  80 7E 00 10 */	lwz r3, 0x10(r30)
/* 80349540 00346480  38 03 00 01 */	addi r0, r3, 1
/* 80349544 00346484  90 1E 00 10 */	stw r0, 0x10(r30)
/* 80349548 00346488  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8034954C 0034648C  2C 00 00 C8 */	cmpwi r0, 0xc8
/* 80349550 00346490  40 81 00 10 */	ble lbl_80349560
/* 80349554 00346494  7F E3 FB 78 */	mr r3, r31
/* 80349558 00346498  38 80 00 00 */	li r4, 0
/* 8034955C 0034649C  4B DF 1B 95 */	bl kill__Q24Game8CreatureFPQ24Game15CreatureKillArg
lbl_80349560:
/* 80349560 003464A0  7F E3 FB 78 */	mr r3, r31
/* 80349564 003464A4  4B DB DD D5 */	bl isStopMotion__Q24Game9EnemyBaseFv
/* 80349568 003464A8  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8034956C 003464AC  40 82 00 38 */	bne lbl_803495A4
/* 80349570 003464B0  80 8D 9A EC */	lwz r4, sys@sda21(r13)
/* 80349574 003464B4  7F E3 FB 78 */	mr r3, r31
/* 80349578 003464B8  C0 42 FF A8 */	lfs f2, lbl_8051E308@sda21(r2)
/* 8034957C 003464BC  C0 24 00 54 */	lfs f1, 0x54(r4)
/* 80349580 003464C0  4B DB CA AD */	bl addDamage__Q24Game9EnemyBaseFff
/* 80349584 003464C4  80 7F 02 8C */	lwz r3, 0x28c(r31)
/* 80349588 003464C8  38 80 50 09 */	li r4, 0x5009
/* 8034958C 003464CC  38 A0 00 00 */	li r5, 0
/* 80349590 003464D0  81 83 00 28 */	lwz r12, 0x28(r3)
/* 80349594 003464D4  81 8C 00 88 */	lwz r12, 0x88(r12)
/* 80349598 003464D8  7D 89 03 A6 */	mtctr r12
/* 8034959C 003464DC  4E 80 04 21 */	bctrl 
/* 803495A0 003464E0  48 00 00 3C */	b lbl_803495DC
lbl_803495A4:
/* 803495A4 003464E4  7F E3 FB 78 */	mr r3, r31
/* 803495A8 003464E8  48 00 1C 0D */	bl isAnimStart__Q34Game4Bomb3ObjFv
/* 803495AC 003464EC  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 803495B0 003464F0  41 82 00 2C */	beq lbl_803495DC
/* 803495B4 003464F4  80 1F 01 E0 */	lwz r0, 0x1e0(r31)
/* 803495B8 003464F8  7F E3 FB 78 */	mr r3, r31
/* 803495BC 003464FC  64 00 00 20 */	oris r0, r0, 0x20
/* 803495C0 00346500  90 1F 01 E0 */	stw r0, 0x1e0(r31)
/* 803495C4 00346504  4B DB DC 41 */	bl startMotion__Q24Game9EnemyBaseFv
/* 803495C8 00346508  80 1F 01 E0 */	lwz r0, 0x1e0(r31)
/* 803495CC 0034650C  7F E3 FB 78 */	mr r3, r31
/* 803495D0 00346510  54 00 06 B0 */	rlwinm r0, r0, 0, 0x1a, 0x18
/* 803495D4 00346514  90 1F 01 E0 */	stw r0, 0x1e0(r31)
/* 803495D8 00346518  4B DB 83 F5 */	bl setEmotionExcitement__Q24Game9EnemyBaseFv
lbl_803495DC:
/* 803495DC 0034651C  80 7F 01 88 */	lwz r3, 0x188(r31)
/* 803495E0 00346520  88 03 00 24 */	lbz r0, 0x24(r3)
/* 803495E4 00346524  28 00 00 00 */	cmplwi r0, 0
/* 803495E8 00346528  41 82 00 50 */	beq lbl_80349638
/* 803495EC 0034652C  80 03 00 1C */	lwz r0, 0x1c(r3)
/* 803495F0 00346530  2C 00 03 E8 */	cmpwi r0, 0x3e8
/* 803495F4 00346534  41 82 00 24 */	beq lbl_80349618
/* 803495F8 00346538  40 80 00 40 */	bge lbl_80349638
/* 803495FC 0034653C  2C 00 00 02 */	cmpwi r0, 2
/* 80349600 00346540  41 82 00 08 */	beq lbl_80349608
/* 80349604 00346544  48 00 00 34 */	b lbl_80349638
lbl_80349608:
/* 80349608 00346548  80 1F 01 E0 */	lwz r0, 0x1e0(r31)
/* 8034960C 0034654C  54 00 02 D2 */	rlwinm r0, r0, 0, 0xb, 9
/* 80349610 00346550  90 1F 01 E0 */	stw r0, 0x1e0(r31)
/* 80349614 00346554  48 00 00 24 */	b lbl_80349638
lbl_80349618:
/* 80349618 00346558  7F C3 F3 78 */	mr r3, r30
/* 8034961C 0034655C  7F E4 FB 78 */	mr r4, r31
/* 80349620 00346560  81 9E 00 00 */	lwz r12, 0(r30)
/* 80349624 00346564  38 A0 00 01 */	li r5, 1
/* 80349628 00346568  38 C0 00 00 */	li r6, 0
/* 8034962C 0034656C  81 8C 00 1C */	lwz r12, 0x1c(r12)
/* 80349630 00346570  7D 89 03 A6 */	mtctr r12
/* 80349634 00346574  4E 80 04 21 */	bctrl 
lbl_80349638:
/* 80349638 00346578  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8034963C 0034657C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80349640 00346580  83 C1 00 08 */	lwz r30, 8(r1)
/* 80349644 00346584  7C 08 03 A6 */	mtlr r0
/* 80349648 00346588  38 21 00 10 */	addi r1, r1, 0x10
/* 8034964C 0034658C  4E 80 00 20 */	blr 

.global __ct__Q34Game4Bomb9StateBombFi
__ct__Q34Game4Bomb9StateBombFi:
/* 80349650 00346590  3C A0 80 4B */	lis r5, __vt__Q24Game13EnemyFSMState@ha
/* 80349654 00346594  3C C0 80 4E */	lis r6, __vt__Q34Game4Bomb5State@ha
/* 80349658 00346598  38 05 F9 A4 */	addi r0, r5, __vt__Q24Game13EnemyFSMState@l
/* 8034965C 0034659C  3C A0 80 4E */	lis r5, __vt__Q34Game4Bomb9StateBomb@ha
/* 80349660 003465A0  90 03 00 00 */	stw r0, 0(r3)
/* 80349664 003465A4  38 E0 00 00 */	li r7, 0
/* 80349668 003465A8  38 C6 BA 08 */	addi r6, r6, __vt__Q34Game4Bomb5State@l
/* 8034966C 003465AC  38 A5 B9 C0 */	addi r5, r5, __vt__Q34Game4Bomb9StateBomb@l
/* 80349670 003465B0  90 83 00 04 */	stw r4, 4(r3)
/* 80349674 003465B4  38 02 FF AC */	addi r0, r2, lbl_8051E30C@sda21
/* 80349678 003465B8  90 E3 00 08 */	stw r7, 8(r3)
/* 8034967C 003465BC  90 C3 00 00 */	stw r6, 0(r3)
/* 80349680 003465C0  90 A3 00 00 */	stw r5, 0(r3)
/* 80349684 003465C4  90 03 00 0C */	stw r0, 0xc(r3)
/* 80349688 003465C8  4E 80 00 20 */	blr 

.global init__Q34Game4Bomb9StateBombFPQ24Game9EnemyBasePQ24Game8StateArg
init__Q34Game4Bomb9StateBombFPQ24Game9EnemyBasePQ24Game8StateArg:
/* 8034968C 003465CC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80349690 003465D0  7C 08 02 A6 */	mflr r0
/* 80349694 003465D4  38 A0 00 00 */	li r5, 0
/* 80349698 003465D8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8034969C 003465DC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 803496A0 003465E0  7C 9F 23 78 */	mr r31, r4
/* 803496A4 003465E4  93 C1 00 08 */	stw r30, 8(r1)
/* 803496A8 003465E8  7C 7E 1B 78 */	mr r30, r3
/* 803496AC 003465EC  7F E3 FB 78 */	mr r3, r31
/* 803496B0 003465F0  80 04 01 E0 */	lwz r0, 0x1e0(r4)
/* 803496B4 003465F4  38 80 00 01 */	li r4, 1
/* 803496B8 003465F8  54 00 06 B0 */	rlwinm r0, r0, 0, 0x1a, 0x18
/* 803496BC 003465FC  90 1F 01 E0 */	stw r0, 0x1e0(r31)
/* 803496C0 00346600  4B DB B9 45 */	bl startMotion__Q24Game9EnemyBaseFiPQ28SysShape14MotionListener
/* 803496C4 00346604  7F E3 FB 78 */	mr r3, r31
/* 803496C8 00346608  4B DB 83 05 */	bl setEmotionExcitement__Q24Game9EnemyBaseFv
/* 803496CC 0034660C  38 00 00 00 */	li r0, 0
/* 803496D0 00346610  90 1E 00 10 */	stw r0, 0x10(r30)
/* 803496D4 00346614  80 01 00 14 */	lwz r0, 0x14(r1)
/* 803496D8 00346618  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 803496DC 0034661C  83 C1 00 08 */	lwz r30, 8(r1)
/* 803496E0 00346620  7C 08 03 A6 */	mtlr r0
/* 803496E4 00346624  38 21 00 10 */	addi r1, r1, 0x10
/* 803496E8 00346628  4E 80 00 20 */	blr 

.global exec__Q34Game4Bomb9StateBombFPQ24Game9EnemyBase
exec__Q34Game4Bomb9StateBombFPQ24Game9EnemyBase:
/* 803496EC 0034662C  94 21 FE 10 */	stwu r1, -0x1f0(r1)
/* 803496F0 00346630  7C 08 02 A6 */	mflr r0
/* 803496F4 00346634  90 01 01 F4 */	stw r0, 0x1f4(r1)
/* 803496F8 00346638  DB E1 01 E0 */	stfd f31, 0x1e0(r1)
/* 803496FC 0034663C  F3 E1 01 E8 */	psq_st f31, 488(r1), 0, qr0
/* 80349700 00346640  DB C1 01 D0 */	stfd f30, 0x1d0(r1)
/* 80349704 00346644  F3 C1 01 D8 */	psq_st f30, 472(r1), 0, qr0
/* 80349708 00346648  DB A1 01 C0 */	stfd f29, 0x1c0(r1)
/* 8034970C 0034664C  F3 A1 01 C8 */	psq_st f29, 456(r1), 0, qr0
/* 80349710 00346650  DB 81 01 B0 */	stfd f28, 0x1b0(r1)
/* 80349714 00346654  F3 81 01 B8 */	psq_st f28, 440(r1), 0, qr0
/* 80349718 00346658  DB 61 01 A0 */	stfd f27, 0x1a0(r1)
/* 8034971C 0034665C  F3 61 01 A8 */	psq_st f27, 424(r1), 0, qr0
/* 80349720 00346660  DB 41 01 90 */	stfd f26, 0x190(r1)
/* 80349724 00346664  F3 41 01 98 */	psq_st f26, 408(r1), 0, qr0
/* 80349728 00346668  DB 21 01 80 */	stfd f25, 0x180(r1)
/* 8034972C 0034666C  F3 21 01 88 */	psq_st f25, 392(r1), 0, qr0
/* 80349730 00346670  DB 01 01 70 */	stfd f24, 0x170(r1)
/* 80349734 00346674  F3 01 01 78 */	psq_st f24, 376(r1), 0, qr0
/* 80349738 00346678  BE E1 01 4C */	stmw r23, 0x14c(r1)
/* 8034973C 0034667C  7C 9D 23 78 */	mr r29, r4
/* 80349740 00346680  7C 77 1B 78 */	mr r23, r3
/* 80349744 00346684  80 64 02 8C */	lwz r3, 0x28c(r4)
/* 80349748 00346688  38 80 50 09 */	li r4, 0x5009
/* 8034974C 0034668C  38 A0 00 00 */	li r5, 0
/* 80349750 00346690  81 83 00 28 */	lwz r12, 0x28(r3)
/* 80349754 00346694  81 8C 00 88 */	lwz r12, 0x88(r12)
/* 80349758 00346698  7D 89 03 A6 */	mtctr r12
/* 8034975C 0034669C  4E 80 04 21 */	bctrl 
/* 80349760 003466A0  80 8D 9A EC */	lwz r4, sys@sda21(r13)
/* 80349764 003466A4  7F A3 EB 78 */	mr r3, r29
/* 80349768 003466A8  C0 42 FF A8 */	lfs f2, lbl_8051E308@sda21(r2)
/* 8034976C 003466AC  C0 24 00 54 */	lfs f1, 0x54(r4)
/* 80349770 003466B0  4B DB C8 BD */	bl addDamage__Q24Game9EnemyBaseFff
/* 80349774 003466B4  C0 3D 02 00 */	lfs f1, 0x200(r29)
/* 80349778 003466B8  C0 02 FF B4 */	lfs f0, lbl_8051E314@sda21(r2)
/* 8034977C 003466BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80349780 003466C0  4C 40 13 82 */	cror 2, 0, 2
/* 80349784 003466C4  40 82 04 D8 */	bne lbl_80349C5C
/* 80349788 003466C8  80 77 00 10 */	lwz r3, 0x10(r23)
/* 8034978C 003466CC  38 03 00 01 */	addi r0, r3, 1
/* 80349790 003466D0  90 17 00 10 */	stw r0, 0x10(r23)
/* 80349794 003466D4  80 17 00 10 */	lwz r0, 0x10(r23)
/* 80349798 003466D8  2C 00 00 0A */	cmpwi r0, 0xa
/* 8034979C 003466DC  41 80 04 C0 */	blt lbl_80349C5C
/* 803497A0 003466E0  38 00 00 00 */	li r0, 0
/* 803497A4 003466E4  7F A3 EB 78 */	mr r3, r29
/* 803497A8 003466E8  90 17 00 10 */	stw r0, 0x10(r23)
/* 803497AC 003466EC  4B DB 81 D1 */	bl setEmotionCaution__Q24Game9EnemyBaseFv
/* 803497B0 003466F0  7F A3 EB 78 */	mr r3, r29
/* 803497B4 003466F4  38 81 00 48 */	addi r4, r1, 0x48
/* 803497B8 003466F8  81 9D 00 00 */	lwz r12, 0(r29)
/* 803497BC 003466FC  81 8C 02 04 */	lwz r12, 0x204(r12)
/* 803497C0 00346700  7D 89 03 A6 */	mtctr r12
/* 803497C4 00346704  4E 80 04 21 */	bctrl 
/* 803497C8 00346708  7F A3 EB 78 */	mr r3, r29
/* 803497CC 0034670C  81 9D 00 00 */	lwz r12, 0(r29)
/* 803497D0 00346710  81 8C 02 58 */	lwz r12, 0x258(r12)
/* 803497D4 00346714  7D 89 03 A6 */	mtctr r12
/* 803497D8 00346718  4E 80 04 21 */	bctrl 
/* 803497DC 0034671C  80 C1 00 48 */	lwz r6, 0x48(r1)
/* 803497E0 00346720  3C 80 80 4B */	lis r4, __vt__Q23efx5TBase@ha
/* 803497E4 00346724  3B 24 A7 F8 */	addi r25, r4, __vt__Q23efx5TBase@l
/* 803497E8 00346728  80 A1 00 4C */	lwz r5, 0x4c(r1)
/* 803497EC 0034672C  80 01 00 50 */	lwz r0, 0x50(r1)
/* 803497F0 00346730  3C 80 80 4B */	lis r4, __vt__Q23efx3Arg@ha
/* 803497F4 00346734  90 C1 00 2C */	stw r6, 0x2c(r1)
/* 803497F8 00346738  3F 60 80 4E */	lis r27, __vt__Q23efx8TSimple4@ha
/* 803497FC 0034673C  3B E4 A7 EC */	addi r31, r4, __vt__Q23efx3Arg@l
/* 80349800 00346740  C0 02 FF A8 */	lfs f0, lbl_8051E308@sda21(r2)
/* 80349804 00346744  39 40 00 00 */	li r10, 0
/* 80349808 00346748  90 A1 00 30 */	stw r5, 0x30(r1)
/* 8034980C 0034674C  C0 61 00 2C */	lfs f3, 0x2c(r1)
/* 80349810 00346750  3F 00 80 4B */	lis r24, __vt__Q23efx12ArgEnemyType@ha
/* 80349814 00346754  90 01 00 34 */	stw r0, 0x34(r1)
/* 80349818 00346758  3F 40 80 4E */	lis r26, __vt__Q23efx9TBombrock@ha
/* 8034981C 0034675C  C0 41 00 30 */	lfs f2, 0x30(r1)
/* 80349820 00346760  3D 20 80 4E */	lis r9, __vt__Q23efx13TBombrockABCD@ha
/* 80349824 00346764  C0 21 00 34 */	lfs f1, 0x34(r1)
/* 80349828 00346768  3C 80 80 4E */	lis r4, __vt__Q23efx13TBombrockEFGH@ha
/* 8034982C 0034676C  3B 80 00 08 */	li r28, 8
/* 80349830 00346770  3B C0 00 09 */	li r30, 9
/* 80349834 00346774  39 80 00 0A */	li r12, 0xa
/* 80349838 00346778  39 60 00 0B */	li r11, 0xb
/* 8034983C 0034677C  39 00 00 0C */	li r8, 0xc
/* 80349840 00346780  38 E0 00 0D */	li r7, 0xd
/* 80349844 00346784  38 C0 00 0E */	li r6, 0xe
/* 80349848 00346788  38 A0 00 0F */	li r5, 0xf
/* 8034984C 0034678C  93 21 00 C0 */	stw r25, 0xc0(r1)
/* 80349850 00346790  3B 7B 6A 3C */	addi r27, r27, __vt__Q23efx8TSimple4@l
/* 80349854 00346794  3B 18 A7 E0 */	addi r24, r24, __vt__Q23efx12ArgEnemyType@l
/* 80349858 00346798  3B 5A B9 AC */	addi r26, r26, __vt__Q23efx9TBombrock@l
/* 8034985C 0034679C  93 21 00 DC */	stw r25, 0xdc(r1)
/* 80349860 003467A0  39 29 B9 98 */	addi r9, r9, __vt__Q23efx13TBombrockABCD@l
/* 80349864 003467A4  38 04 B9 84 */	addi r0, r4, __vt__Q23efx13TBombrockEFGH@l
/* 80349868 003467A8  3A E1 00 C0 */	addi r23, r1, 0xc0
/* 8034986C 003467AC  93 E1 00 A4 */	stw r31, 0xa4(r1)
/* 80349870 003467B0  3B E1 00 DC */	addi r31, r1, 0xdc
/* 80349874 003467B4  38 81 00 A4 */	addi r4, r1, 0xa4
/* 80349878 003467B8  93 21 00 BC */	stw r25, 0xbc(r1)
/* 8034987C 003467BC  93 61 00 C0 */	stw r27, 0xc0(r1)
/* 80349880 003467C0  93 61 00 DC */	stw r27, 0xdc(r1)
/* 80349884 003467C4  90 61 00 B4 */	stw r3, 0xb4(r1)
/* 80349888 003467C8  7E E3 BB 78 */	mr r3, r23
/* 8034988C 003467CC  D0 61 00 A8 */	stfs f3, 0xa8(r1)
/* 80349890 003467D0  D0 41 00 AC */	stfs f2, 0xac(r1)
/* 80349894 003467D4  D0 21 00 B0 */	stfs f1, 0xb0(r1)
/* 80349898 003467D8  93 01 00 A4 */	stw r24, 0xa4(r1)
/* 8034989C 003467DC  D0 01 00 B8 */	stfs f0, 0xb8(r1)
/* 803498A0 003467E0  93 41 00 BC */	stw r26, 0xbc(r1)
/* 803498A4 003467E4  B3 81 00 C4 */	sth r28, 0xc4(r1)
/* 803498A8 003467E8  B3 C1 00 C6 */	sth r30, 0xc6(r1)
/* 803498AC 003467EC  B1 81 00 C8 */	sth r12, 0xc8(r1)
/* 803498B0 003467F0  B1 61 00 CA */	sth r11, 0xca(r1)
/* 803498B4 003467F4  91 41 00 CC */	stw r10, 0xcc(r1)
/* 803498B8 003467F8  91 41 00 D0 */	stw r10, 0xd0(r1)
/* 803498BC 003467FC  91 41 00 D4 */	stw r10, 0xd4(r1)
/* 803498C0 00346800  91 41 00 D8 */	stw r10, 0xd8(r1)
/* 803498C4 00346804  91 21 00 C0 */	stw r9, 0xc0(r1)
/* 803498C8 00346808  B1 01 00 E0 */	sth r8, 0xe0(r1)
/* 803498CC 0034680C  B0 E1 00 E2 */	sth r7, 0xe2(r1)
/* 803498D0 00346810  B0 C1 00 E4 */	sth r6, 0xe4(r1)
/* 803498D4 00346814  B0 A1 00 E6 */	sth r5, 0xe6(r1)
/* 803498D8 00346818  91 41 00 E8 */	stw r10, 0xe8(r1)
/* 803498DC 0034681C  91 41 00 EC */	stw r10, 0xec(r1)
/* 803498E0 00346820  91 41 00 F0 */	stw r10, 0xf0(r1)
/* 803498E4 00346824  91 41 00 F4 */	stw r10, 0xf4(r1)
/* 803498E8 00346828  90 01 00 DC */	stw r0, 0xdc(r1)
/* 803498EC 0034682C  81 97 00 00 */	lwz r12, 0(r23)
/* 803498F0 00346830  81 8C 00 08 */	lwz r12, 8(r12)
/* 803498F4 00346834  7D 89 03 A6 */	mtctr r12
/* 803498F8 00346838  4E 80 04 21 */	bctrl 
/* 803498FC 0034683C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80349900 00346840  41 82 00 1C */	beq lbl_8034991C
/* 80349904 00346844  7F E3 FB 78 */	mr r3, r31
/* 80349908 00346848  38 81 00 A4 */	addi r4, r1, 0xa4
/* 8034990C 0034684C  81 9F 00 00 */	lwz r12, 0(r31)
/* 80349910 00346850  81 8C 00 08 */	lwz r12, 8(r12)
/* 80349914 00346854  7D 89 03 A6 */	mtctr r12
/* 80349918 00346858  4E 80 04 21 */	bctrl 
lbl_8034991C:
/* 8034991C 0034685C  80 7D 02 D4 */	lwz r3, 0x2d4(r29)
/* 80349920 00346860  81 83 00 00 */	lwz r12, 0(r3)
/* 80349924 00346864  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80349928 00346868  7D 89 03 A6 */	mtctr r12
/* 8034992C 0034686C  4E 80 04 21 */	bctrl 
/* 80349930 00346870  80 7D 02 8C */	lwz r3, 0x28c(r29)
/* 80349934 00346874  38 80 58 00 */	li r4, 0x5800
/* 80349938 00346878  38 A0 00 00 */	li r5, 0
/* 8034993C 0034687C  81 83 00 28 */	lwz r12, 0x28(r3)
/* 80349940 00346880  81 8C 00 88 */	lwz r12, 0x88(r12)
/* 80349944 00346884  7D 89 03 A6 */	mtctr r12
/* 80349948 00346888  4E 80 04 21 */	bctrl 
/* 8034994C 0034688C  80 1D 02 80 */	lwz r0, 0x280(r29)
/* 80349950 00346890  28 00 00 00 */	cmplwi r0, 0
/* 80349954 00346894  41 82 00 0C */	beq lbl_80349960
/* 80349958 00346898  7F A3 EB 78 */	mr r3, r29
/* 8034995C 0034689C  48 00 17 D5 */	bl bombEffInWater__Q34Game4Bomb3ObjFv
lbl_80349960:
/* 80349960 003468A0  80 6D 96 A0 */	lwz r3, cameraMgr__4Game@sda21(r13)
/* 80349964 003468A4  38 A1 00 48 */	addi r5, r1, 0x48
/* 80349968 003468A8  38 80 00 0C */	li r4, 0xc
/* 8034996C 003468AC  38 C0 00 02 */	li r6, 2
/* 80349970 003468B0  4B F0 88 CD */	bl startVibration__Q24Game9CameraMgrFiR10Vector3$$0f$$1i
/* 80349974 003468B4  80 6D 96 A8 */	lwz r3, rumbleMgr__4Game@sda21(r13)
/* 80349978 003468B8  38 A1 00 48 */	addi r5, r1, 0x48
/* 8034997C 003468BC  38 80 00 0F */	li r4, 0xf
/* 80349980 003468C0  38 C0 00 02 */	li r6, 2
/* 80349984 003468C4  4B F0 9D FD */	bl startRumble__Q24Game9RumbleMgrFiR10Vector3$$0f$$1i
/* 80349988 003468C8  7F A4 EB 78 */	mr r4, r29
/* 8034998C 003468CC  38 61 00 20 */	addi r3, r1, 0x20
/* 80349990 003468D0  81 9D 00 00 */	lwz r12, 0(r29)
/* 80349994 003468D4  81 8C 00 08 */	lwz r12, 8(r12)
/* 80349998 003468D8  7D 89 03 A6 */	mtctr r12
/* 8034999C 003468DC  4E 80 04 21 */	bctrl 
/* 803499A0 003468E0  80 BD 00 C0 */	lwz r5, 0xc0(r29)
/* 803499A4 003468E4  38 61 00 84 */	addi r3, r1, 0x84
/* 803499A8 003468E8  C3 A1 00 20 */	lfs f29, 0x20(r1)
/* 803499AC 003468EC  38 81 00 38 */	addi r4, r1, 0x38
/* 803499B0 003468F0  C0 05 08 44 */	lfs f0, 0x844(r5)
/* 803499B4 003468F4  C3 E1 00 24 */	lfs f31, 0x24(r1)
/* 803499B8 003468F8  C3 C1 00 28 */	lfs f30, 0x28(r1)
/* 803499BC 003468FC  D3 A1 00 38 */	stfs f29, 0x38(r1)
/* 803499C0 00346900  EF 9F 00 2A */	fadds f28, f31, f0
/* 803499C4 00346904  EF 7F 00 28 */	fsubs f27, f31, f0
/* 803499C8 00346908  D3 E1 00 3C */	stfs f31, 0x3c(r1)
/* 803499CC 0034690C  D3 C1 00 40 */	stfs f30, 0x40(r1)
/* 803499D0 00346910  C0 05 05 B4 */	lfs f0, 0x5b4(r5)
/* 803499D4 00346914  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 803499D8 00346918  4B EE 49 C9 */	bl __ct__Q24Game15CellIteratorArgFRQ23Sys6Sphere
/* 803499DC 0034691C  38 00 00 01 */	li r0, 1
/* 803499E0 00346920  38 61 00 F8 */	addi r3, r1, 0xf8
/* 803499E4 00346924  90 01 00 98 */	stw r0, 0x98(r1)
/* 803499E8 00346928  38 81 00 84 */	addi r4, r1, 0x84
/* 803499EC 0034692C  4B EE 49 F5 */	bl __ct__Q24Game12CellIteratorFRQ24Game15CellIteratorArg
/* 803499F0 00346930  38 61 00 F8 */	addi r3, r1, 0xf8
/* 803499F4 00346934  4B EE 4A 69 */	bl first__Q24Game12CellIteratorFv
/* 803499F8 00346938  3C 60 80 51 */	lis r3, "zero__10Vector3<f>"@ha
/* 803499FC 0034693C  3B E3 41 E4 */	addi r31, r3, "zero__10Vector3<f>"@l
/* 80349A00 00346940  48 00 02 40 */	b lbl_80349C40
lbl_80349A04:
/* 80349A04 00346944  38 61 00 F8 */	addi r3, r1, 0xf8
/* 80349A08 00346948  4B EE 4B 3D */	bl __ml__Q24Game12CellIteratorFv
/* 80349A0C 0034694C  81 83 00 00 */	lwz r12, 0(r3)
/* 80349A10 00346950  7C 7E 1B 78 */	mr r30, r3
/* 80349A14 00346954  81 8C 00 A8 */	lwz r12, 0xa8(r12)
/* 80349A18 00346958  7D 89 03 A6 */	mtctr r12
/* 80349A1C 0034695C  4E 80 04 21 */	bctrl 
/* 80349A20 00346960  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80349A24 00346964  41 82 02 14 */	beq lbl_80349C38
/* 80349A28 00346968  7C 1E E8 40 */	cmplw r30, r29
/* 80349A2C 0034696C  41 82 02 0C */	beq lbl_80349C38
/* 80349A30 00346970  7F C4 F3 78 */	mr r4, r30
/* 80349A34 00346974  38 61 00 14 */	addi r3, r1, 0x14
/* 80349A38 00346978  81 9E 00 00 */	lwz r12, 0(r30)
/* 80349A3C 0034697C  81 8C 00 08 */	lwz r12, 8(r12)
/* 80349A40 00346980  7D 89 03 A6 */	mtctr r12
/* 80349A44 00346984  4E 80 04 21 */	bctrl 
/* 80349A48 00346988  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 80349A4C 0034698C  FC 00 E0 40 */	fcmpo cr0, f0, f28
/* 80349A50 00346990  41 81 01 E8 */	bgt lbl_80349C38
/* 80349A54 00346994  FC 00 D8 40 */	fcmpo cr0, f0, f27
/* 80349A58 00346998  41 80 01 E0 */	blt lbl_80349C38
/* 80349A5C 0034699C  7F C3 F3 78 */	mr r3, r30
/* 80349A60 003469A0  81 9E 00 00 */	lwz r12, 0(r30)
/* 80349A64 003469A4  81 8C 00 7C */	lwz r12, 0x7c(r12)
/* 80349A68 003469A8  7D 89 03 A6 */	mtctr r12
/* 80349A6C 003469AC  4E 80 04 21 */	bctrl 
/* 80349A70 003469B0  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80349A74 003469B4  41 82 00 78 */	beq lbl_80349AEC
/* 80349A78 003469B8  80 DD 00 C0 */	lwz r6, 0xc0(r29)
/* 80349A7C 003469BC  3C A0 80 4B */	lis r5, __vt__Q24Game11Interaction@ha
/* 80349A80 003469C0  3C 80 80 4B */	lis r4, __vt__Q24Game12InteractWind@ha
/* 80349A84 003469C4  3C 60 80 51 */	lis r3, "zero__10Vector3<f>"@ha
/* 80349A88 003469C8  C0 06 08 1C */	lfs f0, 0x81c(r6)
/* 80349A8C 003469CC  38 05 A3 00 */	addi r0, r5, __vt__Q24Game11Interaction@l
/* 80349A90 003469D0  C0 22 FF A8 */	lfs f1, lbl_8051E308@sda21(r2)
/* 80349A94 003469D4  38 84 49 74 */	addi r4, r4, __vt__Q24Game12InteractWind@l
/* 80349A98 003469D8  90 01 00 6C */	stw r0, 0x6c(r1)
/* 80349A9C 003469DC  EC 61 00 32 */	fmuls f3, f1, f0
/* 80349AA0 003469E0  C0 43 41 E4 */	lfs f2, "zero__10Vector3<f>"@l(r3)
/* 80349AA4 003469E4  C0 3F 00 04 */	lfs f1, 4(r31)
/* 80349AA8 003469E8  3C 60 80 4B */	lis r3, __vt__Q24Game12InteractBomb@ha
/* 80349AAC 003469EC  C0 1F 00 08 */	lfs f0, 8(r31)
/* 80349AB0 003469F0  38 03 49 2C */	addi r0, r3, __vt__Q24Game12InteractBomb@l
/* 80349AB4 003469F4  90 81 00 6C */	stw r4, 0x6c(r1)
/* 80349AB8 003469F8  7F C3 F3 78 */	mr r3, r30
/* 80349ABC 003469FC  38 81 00 6C */	addi r4, r1, 0x6c
/* 80349AC0 00346A00  93 A1 00 70 */	stw r29, 0x70(r1)
/* 80349AC4 00346A04  D0 61 00 74 */	stfs f3, 0x74(r1)
/* 80349AC8 00346A08  D0 41 00 78 */	stfs f2, 0x78(r1)
/* 80349ACC 00346A0C  D0 21 00 7C */	stfs f1, 0x7c(r1)
/* 80349AD0 00346A10  D0 01 00 80 */	stfs f0, 0x80(r1)
/* 80349AD4 00346A14  90 01 00 6C */	stw r0, 0x6c(r1)
/* 80349AD8 00346A18  81 9E 00 00 */	lwz r12, 0(r30)
/* 80349ADC 00346A1C  81 8C 01 A4 */	lwz r12, 0x1a4(r12)
/* 80349AE0 00346A20  7D 89 03 A6 */	mtctr r12
/* 80349AE4 00346A24  4E 80 04 21 */	bctrl 
/* 80349AE8 00346A28  48 00 01 50 */	b lbl_80349C38
lbl_80349AEC:
/* 80349AEC 00346A2C  7F C3 F3 78 */	mr r3, r30
/* 80349AF0 00346A30  81 9E 00 00 */	lwz r12, 0(r30)
/* 80349AF4 00346A34  81 8C 00 1C */	lwz r12, 0x1c(r12)
/* 80349AF8 00346A38  7D 89 03 A6 */	mtctr r12
/* 80349AFC 00346A3C  4E 80 04 21 */	bctrl 
/* 80349B00 00346A40  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80349B04 00346A44  40 82 00 20 */	bne lbl_80349B24
/* 80349B08 00346A48  7F C3 F3 78 */	mr r3, r30
/* 80349B0C 00346A4C  81 9E 00 00 */	lwz r12, 0(r30)
/* 80349B10 00346A50  81 8C 00 18 */	lwz r12, 0x18(r12)
/* 80349B14 00346A54  7D 89 03 A6 */	mtctr r12
/* 80349B18 00346A58  4E 80 04 21 */	bctrl 
/* 80349B1C 00346A5C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80349B20 00346A60  41 82 01 18 */	beq lbl_80349C38
lbl_80349B24:
/* 80349B24 00346A64  80 1D 02 CC */	lwz r0, 0x2cc(r29)
/* 80349B28 00346A68  28 00 00 00 */	cmplwi r0, 0
/* 80349B2C 00346A6C  7C 17 03 78 */	mr r23, r0
/* 80349B30 00346A70  40 82 00 08 */	bne lbl_80349B38
/* 80349B34 00346A74  7F B7 EB 78 */	mr r23, r29
lbl_80349B38:
/* 80349B38 00346A78  7F C4 F3 78 */	mr r4, r30
/* 80349B3C 00346A7C  38 61 00 08 */	addi r3, r1, 8
/* 80349B40 00346A80  81 9E 00 00 */	lwz r12, 0(r30)
/* 80349B44 00346A84  81 8C 00 08 */	lwz r12, 8(r12)
/* 80349B48 00346A88  7D 89 03 A6 */	mtctr r12
/* 80349B4C 00346A8C  4E 80 04 21 */	bctrl 
/* 80349B50 00346A90  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 80349B54 00346A94  C3 41 00 08 */	lfs f26, 8(r1)
/* 80349B58 00346A98  EC 21 F8 28 */	fsubs f1, f1, f31
/* 80349B5C 00346A9C  C3 21 00 10 */	lfs f25, 0x10(r1)
/* 80349B60 00346AA0  EF 5A E8 28 */	fsubs f26, f26, f29
/* 80349B64 00346AA4  C0 02 FF B4 */	lfs f0, lbl_8051E314@sda21(r2)
/* 80349B68 00346AA8  EF 39 F0 28 */	fsubs f25, f25, f30
/* 80349B6C 00346AAC  EC 21 00 72 */	fmuls f1, f1, f1
/* 80349B70 00346AB0  EC 59 06 72 */	fmuls f2, f25, f25
/* 80349B74 00346AB4  EC 3A 0E BA */	fmadds f1, f26, f26, f1
/* 80349B78 00346AB8  EC 22 08 2A */	fadds f1, f2, f1
/* 80349B7C 00346ABC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80349B80 00346AC0  40 81 00 14 */	ble lbl_80349B94
/* 80349B84 00346AC4  40 81 00 14 */	ble lbl_80349B98
/* 80349B88 00346AC8  FC 00 08 34 */	frsqrte f0, f1
/* 80349B8C 00346ACC  EC 20 00 72 */	fmuls f1, f0, f1
/* 80349B90 00346AD0  48 00 00 08 */	b lbl_80349B98
lbl_80349B94:
/* 80349B94 00346AD4  FC 20 00 90 */	fmr f1, f0
lbl_80349B98:
/* 80349B98 00346AD8  C0 02 FF B4 */	lfs f0, lbl_8051E314@sda21(r2)
/* 80349B9C 00346ADC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80349BA0 00346AE0  40 81 00 14 */	ble lbl_80349BB4
/* 80349BA4 00346AE4  C0 02 FF A8 */	lfs f0, lbl_8051E308@sda21(r2)
/* 80349BA8 00346AE8  EC 00 08 24 */	fdivs f0, f0, f1
/* 80349BAC 00346AEC  EF 5A 00 32 */	fmuls f26, f26, f0
/* 80349BB0 00346AF0  EF 39 00 32 */	fmuls f25, f25, f0
lbl_80349BB4:
/* 80349BB4 00346AF4  7F C3 F3 78 */	mr r3, r30
/* 80349BB8 00346AF8  C3 02 FF B8 */	lfs f24, lbl_8051E318@sda21(r2)
/* 80349BBC 00346AFC  81 9E 00 00 */	lwz r12, 0(r30)
/* 80349BC0 00346B00  81 8C 00 18 */	lwz r12, 0x18(r12)
/* 80349BC4 00346B04  7D 89 03 A6 */	mtctr r12
/* 80349BC8 00346B08  4E 80 04 21 */	bctrl 
/* 80349BCC 00346B0C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80349BD0 00346B10  41 82 00 08 */	beq lbl_80349BD8
/* 80349BD4 00346B14  C3 02 FF BC */	lfs f24, lbl_8051E31C@sda21(r2)
lbl_80349BD8:
/* 80349BD8 00346B18  80 DD 00 C0 */	lwz r6, 0xc0(r29)
/* 80349BDC 00346B1C  3C A0 80 4B */	lis r5, __vt__Q24Game11Interaction@ha
/* 80349BE0 00346B20  3C 80 80 4B */	lis r4, __vt__Q24Game12InteractWind@ha
/* 80349BE4 00346B24  3C 60 80 4B */	lis r3, __vt__Q24Game12InteractBomb@ha
/* 80349BE8 00346B28  C0 06 06 04 */	lfs f0, 0x604(r6)
/* 80349BEC 00346B2C  38 05 A3 00 */	addi r0, r5, __vt__Q24Game11Interaction@l
/* 80349BF0 00346B30  EF 5A 06 32 */	fmuls f26, f26, f24
/* 80349BF4 00346B34  38 84 49 74 */	addi r4, r4, __vt__Q24Game12InteractWind@l
/* 80349BF8 00346B38  90 01 00 54 */	stw r0, 0x54(r1)
/* 80349BFC 00346B3C  EF 39 06 32 */	fmuls f25, f25, f24
/* 80349C00 00346B40  38 03 49 2C */	addi r0, r3, __vt__Q24Game12InteractBomb@l
/* 80349C04 00346B44  7F C3 F3 78 */	mr r3, r30
/* 80349C08 00346B48  90 81 00 54 */	stw r4, 0x54(r1)
/* 80349C0C 00346B4C  38 81 00 54 */	addi r4, r1, 0x54
/* 80349C10 00346B50  92 E1 00 58 */	stw r23, 0x58(r1)
/* 80349C14 00346B54  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 80349C18 00346B58  D3 41 00 60 */	stfs f26, 0x60(r1)
/* 80349C1C 00346B5C  D3 01 00 64 */	stfs f24, 0x64(r1)
/* 80349C20 00346B60  D3 21 00 68 */	stfs f25, 0x68(r1)
/* 80349C24 00346B64  90 01 00 54 */	stw r0, 0x54(r1)
/* 80349C28 00346B68  81 9E 00 00 */	lwz r12, 0(r30)
/* 80349C2C 00346B6C  81 8C 01 A4 */	lwz r12, 0x1a4(r12)
/* 80349C30 00346B70  7D 89 03 A6 */	mtctr r12
/* 80349C34 00346B74  4E 80 04 21 */	bctrl 
lbl_80349C38:
/* 80349C38 00346B78  38 61 00 F8 */	addi r3, r1, 0xf8
/* 80349C3C 00346B7C  4B EE 48 C5 */	bl next__Q24Game12CellIteratorFv
lbl_80349C40:
/* 80349C40 00346B80  38 61 00 F8 */	addi r3, r1, 0xf8
/* 80349C44 00346B84  4B EE 48 F1 */	bl isDone__Q24Game12CellIteratorFv
/* 80349C48 00346B88  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80349C4C 00346B8C  41 82 FD B8 */	beq lbl_80349A04
/* 80349C50 00346B90  7F A3 EB 78 */	mr r3, r29
/* 80349C54 00346B94  38 80 00 00 */	li r4, 0
/* 80349C58 00346B98  4B DF 14 99 */	bl kill__Q24Game8CreatureFPQ24Game15CreatureKillArg
lbl_80349C5C:
/* 80349C5C 00346B9C  E3 E1 01 E8 */	psq_l f31, 488(r1), 0, qr0
/* 80349C60 00346BA0  CB E1 01 E0 */	lfd f31, 0x1e0(r1)
/* 80349C64 00346BA4  E3 C1 01 D8 */	psq_l f30, 472(r1), 0, qr0
/* 80349C68 00346BA8  CB C1 01 D0 */	lfd f30, 0x1d0(r1)
/* 80349C6C 00346BAC  E3 A1 01 C8 */	psq_l f29, 456(r1), 0, qr0
/* 80349C70 00346BB0  CB A1 01 C0 */	lfd f29, 0x1c0(r1)
/* 80349C74 00346BB4  E3 81 01 B8 */	psq_l f28, 440(r1), 0, qr0
/* 80349C78 00346BB8  CB 81 01 B0 */	lfd f28, 0x1b0(r1)
/* 80349C7C 00346BBC  E3 61 01 A8 */	psq_l f27, 424(r1), 0, qr0
/* 80349C80 00346BC0  CB 61 01 A0 */	lfd f27, 0x1a0(r1)
/* 80349C84 00346BC4  E3 41 01 98 */	psq_l f26, 408(r1), 0, qr0
/* 80349C88 00346BC8  CB 41 01 90 */	lfd f26, 0x190(r1)
/* 80349C8C 00346BCC  E3 21 01 88 */	psq_l f25, 392(r1), 0, qr0
/* 80349C90 00346BD0  CB 21 01 80 */	lfd f25, 0x180(r1)
/* 80349C94 00346BD4  E3 01 01 78 */	psq_l f24, 376(r1), 0, qr0
/* 80349C98 00346BD8  CB 01 01 70 */	lfd f24, 0x170(r1)
/* 80349C9C 00346BDC  BA E1 01 4C */	lmw r23, 0x14c(r1)
/* 80349CA0 00346BE0  80 01 01 F4 */	lwz r0, 0x1f4(r1)
/* 80349CA4 00346BE4  7C 08 03 A6 */	mtlr r0
/* 80349CA8 00346BE8  38 21 01 F0 */	addi r1, r1, 0x1f0
/* 80349CAC 00346BEC  4E 80 00 20 */	blr 

.global create__Q23efx9TBombrockFPQ23efx3Arg
create__Q23efx9TBombrockFPQ23efx3Arg:
/* 80349CB0 00346BF0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80349CB4 00346BF4  7C 08 02 A6 */	mflr r0
/* 80349CB8 00346BF8  90 01 00 24 */	stw r0, 0x24(r1)
/* 80349CBC 00346BFC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80349CC0 00346C00  3B E0 00 00 */	li r31, 0
/* 80349CC4 00346C04  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80349CC8 00346C08  7C 9E 23 78 */	mr r30, r4
/* 80349CCC 00346C0C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80349CD0 00346C10  7C 7D 1B 78 */	mr r29, r3
/* 80349CD4 00346C14  38 7D 00 04 */	addi r3, r29, 4
/* 80349CD8 00346C18  81 9D 00 04 */	lwz r12, 4(r29)
/* 80349CDC 00346C1C  81 8C 00 08 */	lwz r12, 8(r12)
/* 80349CE0 00346C20  7D 89 03 A6 */	mtctr r12
/* 80349CE4 00346C24  4E 80 04 21 */	bctrl 
/* 80349CE8 00346C28  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80349CEC 00346C2C  41 82 00 28 */	beq lbl_80349D14
/* 80349CF0 00346C30  38 7D 00 20 */	addi r3, r29, 0x20
/* 80349CF4 00346C34  7F C4 F3 78 */	mr r4, r30
/* 80349CF8 00346C38  81 9D 00 20 */	lwz r12, 0x20(r29)
/* 80349CFC 00346C3C  81 8C 00 08 */	lwz r12, 8(r12)
/* 80349D00 00346C40  7D 89 03 A6 */	mtctr r12
/* 80349D04 00346C44  4E 80 04 21 */	bctrl 
/* 80349D08 00346C48  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80349D0C 00346C4C  41 82 00 08 */	beq lbl_80349D14
/* 80349D10 00346C50  3B E0 00 01 */	li r31, 1
lbl_80349D14:
/* 80349D14 00346C54  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80349D18 00346C58  7F E3 FB 78 */	mr r3, r31
/* 80349D1C 00346C5C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80349D20 00346C60  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80349D24 00346C64  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80349D28 00346C68  7C 08 03 A6 */	mtlr r0
/* 80349D2C 00346C6C  38 21 00 20 */	addi r1, r1, 0x20
/* 80349D30 00346C70  4E 80 00 20 */	blr 

.global forceKill__Q23efx9TBombrockFv
forceKill__Q23efx9TBombrockFv:
/* 80349D34 00346C74  4E 80 00 20 */	blr 

.global fade__Q23efx9TBombrockFv
fade__Q23efx9TBombrockFv:
/* 80349D38 00346C78  4E 80 00 20 */	blr 

.global __sinit_bombState_cpp
__sinit_bombState_cpp:
/* 80349D3C 00346C7C  3C 80 80 51 */	lis r4, __float_nan@ha
/* 80349D40 00346C80  38 00 FF FF */	li r0, -1
/* 80349D44 00346C84  C0 04 48 B0 */	lfs f0, __float_nan@l(r4)
/* 80349D48 00346C88  3C 60 80 4E */	lis r3, lbl_804DB978@ha
/* 80349D4C 00346C8C  90 0D 98 A8 */	stw r0, lbl_80515F28@sda21(r13)
/* 80349D50 00346C90  D4 03 B9 78 */	stfsu f0, lbl_804DB978@l(r3)
/* 80349D54 00346C94  D0 0D 98 AC */	stfs f0, lbl_80515F2C@sda21(r13)
/* 80349D58 00346C98  D0 03 00 04 */	stfs f0, 4(r3)
/* 80349D5C 00346C9C  D0 03 00 08 */	stfs f0, 8(r3)
/* 80349D60 00346CA0  4E 80 00 20 */	blr 
