#include "JSystem/JAudio/JAS/JASOscillator.h"
#include "JSystem/JAudio/JAS/JASDriver.h"
#include "JSystem/JMath.h"
#include "types.h"

const f32 JASOscillator::relTableSampleCell[17] = { 1.0f,
	                                                0.9704890251159668f,
	                                                0.7812740206718445f,
	                                                0.5462809801101685f,
	                                                0.39979198575019836f,
	                                                0.28931498527526855f,
	                                                0.21210399270057678f,
	                                                0.15747599303722382f,
	                                                0.1126129999756813f,
	                                                0.08178959786891937f,
	                                                0.057985201478004456f,
	                                                0.04364150017499924f,
	                                                0.03082370012998581f,
	                                                0.023712899535894394f,
	                                                0.015259300358593464f,
	                                                0.00915555004030466f,
	                                                0.0f };
const f32 JASOscillator::relTableSqRoot[17]
    = { 1.0f,      0.8789060115814209f,  0.765625f, 0.6601560115814209f, 0.5625f,   0.4726560115814209f,
	    0.390625f, 0.3164060115814209f,  0.25f,     0.1914059966802597f, 0.140625f, 0.09765619784593582f,
	    0.0625f,   0.03515620157122612f, 0.015625f, 0.00390625f,         0.0f };
const f32 JASOscillator::relTableSquare[17] = {
	1.0f,
	0.9682459831237793f,
	0.9354140162467957f,
	0.9013879895210266f,
	0.8660249710083008f,
	0.8291559815406799f,
	0.790569007396698f,
	0.75f,
	0.7071070075035095f,
	0.66143798828125f,
	0.6123719811439514f,
	0.55901700258255f,
	0.5f,
	0.433012992143631f,
	0.35355299711227417f,
	0.25f,
	0.0f,
};

const s16 JASOscillator::oscTableForceStop[6] = { 0, 15, 0, 15, 0, 0 };

/**
 * @note Address: 0x800A2B78
 * @note Size: 0x34
 */
void JASOscillator::init()
{
	mData = nullptr;
	_1C   = 0;
	_1D   = 0;
	_18   = 0;
	_04   = 0.0f;
	_08   = 0.0f;
	_0C   = 0.0f;
	_10   = 0.0f;
	_1A   = 0;
	_14   = 0.0f;
}

/**
 * @note Address: 0x800A2BAC
 * @note Size: 0x88
 */
void JASOscillator::initStart(const Data* data)
{
	if (!data) {
		_1C = 0;
	} else {
		_1C   = 1;
		mData = data;
		_1A   = 0;
		if (!mData->_08) {
			_08 = 0.0f;
		} else {
			_18 = 0;
			_04 = 0.0f;
			_0C = 0.0f;
			_04 -= mData->_04;
			incCounter();
		}
	}
}

/**
 * @note Address: 0x800A2C34
 * @note Size: 0xC8
 */
void JASOscillator::incCounter()
{
	const s16* v1;
	switch (_1C) {
	case 0:
	case 2:
		return;
	case 1:
		break;
	}
	if (_1C == 3) {
		v1 = mData->_0C;
	} else if (_1C == 4) {
		v1 = oscTableForceStop;
	} else {
		v1 = mData->_08;
	}
	if (v1 == nullptr && _1C != 5) {
		_08 = 1.0f;
	} else {
		if (_1C == 4) {
			_04 -= 1.0f;
		} else {
			_04 -= mData->_04;
		}
		calc(v1);
	}
}

/**
 * @note Address: 0x800A2CFC
 * @note Size: 0x2C
 */
f32 JASOscillator::getValue() const
{
	if (_1C == 0) {
		return 1.0f;
	}
	return _08 * mData->_10 + mData->_14;
}

/**
 * @note Address: N/A
 * @note Size: 0x3C
 */
void JASOscillator::forceStop()
{
	// UNUSED FUNCTION
}

/**
 * @note Address: 0x800A2D28
 * @note Size: 0x168
 */
bool JASOscillator::release()
{
	f32 temp_f31;

	if ((u8)_1C == 4) {
		return false;
	}
	mData = mData;
	if ((u32)mData->_08 != (u32)mData->_0C) {
		_18 = 0;
		_04 = 0.0f;
		_0C = _08;
	}
	if (((u32)mData->_0C == 0) && ((u16)_1A == 0)) {
		_1A = 0x10;
	}
	if ((u16)_1A != 0) {
		_1C      = 5;
		_1D      = (u8)((_1A >> 0xE) & 3);
		temp_f31 = (f32)(_1A & 0x3FFF);
		temp_f31 *= ((JASDriver::getDacRate() / 80.0f) / 600.0f);
		_04 = temp_f31;
		if (_04 < 1.0f) {
			_04 = 1.0f;
		}
		_14 = (f32)_04;
		_0C = (f32)0.0f;
		if ((u8)_1D == 0) {
			_10 = (f32)((_0C - _08) / _04);
		} else {
			_10 = (f32)(_0C - _08);
		}
	} else {
		_1C = 3;
	}
	return true;
}

/**
 * @note Address: 0x800A2E90
 * @note Size: 0x374
 */
f32 JASOscillator::calc(const s16* p1)
{
	f32 val31 = 0.0f;
	while (_04 <= 0.0f) {
		int idx = _18 * 3;
		_08     = _0C;
		if (_1C == 5) {
			_1C = 0;
			break;
		}

		int val  = p1[idx];
		int val2 = p1[idx + 1];
		int val3 = p1[idx + 2];
		if (val == 13) {
			_18 = val3;
			continue;
		}

		if (val == 15) {
			_1C = 0;
			break;
		}

		if (val == 14) {
			_1C = 2;
			return _08 * mData->_10 + mData->_14;
		}

		_1D = val;

		if ((s16)val2 == 0) {
			_0C = val3 / 32768.0f;
			_18++;
			continue;
		}

		_04 = (f32)val2 * ((JASDriver::getDacRate() / 80.0f) / 600.0f);
		_14 = _04;
		_0C = val3 / 32768.0f;

		if (_1D == 0) {
			_10 = (_0C - _08) / _04;
		} else {
			_10 = _0C - _08;
		}

		_18++;
	}

	if (mData->_10 == 0.0f) {
		return mData->_14;
	}

	f32 factor;       // f2
	if (_14 == 0.0) { // yes this is a double. someone forgot an f
		factor = _0C;
		_08    = _0C;
	} else {
		if (_1D == 0 || (val31 = _10) == 0.0f) {
			factor = _0C - (_10 * _04);
			_08    = factor;
		} else if (_1D == 3 || _1D == 1 || _1D == 2) {
			const f32* table = nullptr; // r27
			switch (_1D) {
			case 3:
				table = relTableSampleCell;
				break;
			case 1:
				table = relTableSquare;
				break;
			case 2:
				table = relTableSqRoot;
				break;
			}

			f32 val30;

			if (val31 < 0.0f) {
				val30 = 16.0f * (1.0f - (_04 / _14));
			} else {
				val30 = 16.0f * (_04 / _14);
			}

			u32 idx  = val30;
			f32 val4 = val30 - (f32)idx;
			if (idx >= 16) {
				idx  = 15;
				val4 = 1.0f;
			}

			f32 valAbs = JMAAbs(val31 * (val4 * (table[idx + 1] - table[idx]) + table[idx]));

			if (_10 < 0.0f) {
				factor = _0C + valAbs;
			} else {
				factor = _0C - (_10 - valAbs);
			}

			_08 = factor;
		} else {
			factor = _0C - val31 * _04;
			_08    = factor;
		}
	}

	return factor * mData->_10 + mData->_14;
	/*
	stwu     r1, -0x50(r1)
	mflr     r0
	stw      r0, 0x54(r1)
	stfd     f31, 0x40(r1)
	psq_st   f31, 72(r1), 0, qr0
	stfd     f30, 0x30(r1)
	psq_st   f30, 56(r1), 0, qr0
	stmw     r27, 0x1c(r1)
	lis      r5, relTableSampleCell__13JASOscillator@ha
	lfs      f31, lbl_80516DD8@sda21(r2)
	mr       r29, r3
	mr       r30, r4
	addi     r31, r5, relTableSampleCell__13JASOscillator@l
	b        lbl_800A3038

lbl_800A2EC8:
	lhz      r0, 0x18(r29)
	lfs      f0, 0xc(r29)
	mulli    r3, r0, 3
	stfs     f0, 8(r29)
	lbz      r0, 0x1c(r29)
	cmplwi   r0, 5
	bne      lbl_800A2EF0
	li       r0, 0
	stb      r0, 0x1c(r29)
	b        lbl_800A3048

lbl_800A2EF0:
	slwi     r0, r3, 1
	add      r3, r30, r0
	lha      r4, 0(r3)
	lha      r28, 2(r3)
	cmpwi    r4, 0xd
	lha      r27, 4(r3)
	bne      lbl_800A2F14
	sth      r27, 0x18(r29)
	b        lbl_800A3038

lbl_800A2F14:
	cmpwi    r4, 0xf
	bne      lbl_800A2F28
	li       r0, 0
	stb      r0, 0x1c(r29)
	b        lbl_800A3048

lbl_800A2F28:
	cmpwi    r4, 0xe
	bne      lbl_800A2F50
	li       r0, 2
	stb      r0, 0x1c(r29)
	lwz      r3, 0(r29)
	lfs      f2, 8(r29)
	lfs      f1, 0x10(r3)
	lfs      f0, 0x14(r3)
	fmadds   f1, f2, f1, f0
	b        lbl_800A31E0

lbl_800A2F50:
	extsh.   r0, r28
	stb      r4, 0x1d(r29)
	bne      lbl_800A2F94
	xoris    r3, r27, 0x8000
	lis      r0, 0x4330
	stw      r3, 0xc(r1)
	lfd      f2, lbl_80516DE8@sda21(r2)
	stw      r0, 8(r1)
	lfs      f0, lbl_80516DF0@sda21(r2)
	lfd      f1, 8(r1)
	fsubs    f1, f1, f2
	fdivs    f0, f1, f0
	stfs     f0, 0xc(r29)
	lhz      r3, 0x18(r29)
	addi     r0, r3, 1
	sth      r0, 0x18(r29)
	b        lbl_800A3038

lbl_800A2F94:
	bl       getDacRate__9JASDriverFv
	lfs      f0, lbl_80516DE0@sda21(r2)
	lis      r3, 0x4330
	xoris    r0, r27, 0x8000
	xoris    r4, r28, 0x8000
	fdivs    f2, f1, f0
	lfs      f1, lbl_80516DE4@sda21(r2)
	stw      r0, 0x14(r1)
	lfd      f3, lbl_80516DE8@sda21(r2)
	stw      r3, 0x10(r1)
	lfs      f0, lbl_80516DF0@sda21(r2)
	fdivs    f4, f2, f1
	lfd      f1, 0x10(r1)
	stw      r4, 0xc(r1)
	stw      r3, 8(r1)
	lfd      f2, 8(r1)
	fsubs    f1, f1, f3
	fsubs    f2, f2, f3
	fdivs    f0, f1, f0
	fmuls    f1, f2, f4
	stfs     f1, 4(r29)
	lfs      f1, 4(r29)
	stfs     f1, 0x14(r29)
	stfs     f0, 0xc(r29)
	lbz      r0, 0x1d(r29)
	cmplwi   r0, 0
	bne      lbl_800A301C
	lfs      f2, 0xc(r29)
	lfs      f1, 8(r29)
	lfs      f0, 4(r29)
	fsubs    f1, f2, f1
	fdivs    f0, f1, f0
	stfs     f0, 0x10(r29)
	b        lbl_800A302C

lbl_800A301C:
	lfs      f1, 0xc(r29)
	lfs      f0, 8(r29)
	fsubs    f0, f1, f0
	stfs     f0, 0x10(r29)

lbl_800A302C:
	lhz      r3, 0x18(r29)
	addi     r0, r3, 1
	sth      r0, 0x18(r29)

lbl_800A3038:
	lfs      f0, 4(r29)
	fcmpo    cr0, f0, f31
	cror     2, 0, 2
	beq      lbl_800A2EC8

lbl_800A3048:
	lwz      r3, 0(r29)
	lfs      f1, lbl_80516DD8@sda21(r2)
	lfs      f0, 0x10(r3)
	fcmpu    cr0, f1, f0
	bne      lbl_800A3064
	lfs      f1, 0x14(r3)
	b        lbl_800A31E0

lbl_800A3064:
	lfd      f0, lbl_80516DF8@sda21(r2)
	lfs      f2, 0x14(r29)
	fcmpu    cr0, f0, f2
	bne      lbl_800A3084
	lfs      f0, 0xc(r29)
	fmr      f2, f0
	stfs     f0, 8(r29)
	b        lbl_800A31D0

lbl_800A3084:
	lbz      r0, 0x1d(r29)
	cmplwi   r0, 0
	beq      lbl_800A309C
	lfs      f31, 0x10(r29)
	fcmpu    cr0, f1, f31
	bne      lbl_800A30B4

lbl_800A309C:
	lfs      f2, 0x10(r29)
	lfs      f1, 4(r29)
	lfs      f0, 0xc(r29)
	fnmsubs  f2, f2, f1, f0
	stfs     f2, 8(r29)
	b        lbl_800A31D0

lbl_800A30B4:
	cmplwi   r0, 3
	beq      lbl_800A30CC
	cmplwi   r0, 1
	beq      lbl_800A30CC
	cmplwi   r0, 2
	bne      lbl_800A31C0

lbl_800A30CC:
	cmpwi    r0, 2
	li       r27, 0
	beq      lbl_800A3100
	bge      lbl_800A30E8
	cmpwi    r0, 1
	bge      lbl_800A30F8
	b        lbl_800A3104

lbl_800A30E8:
	cmpwi    r0, 4
	bge      lbl_800A3104
	addi     r27, r31, 0
	b        lbl_800A3104

lbl_800A30F8:
	addi     r27, r31, 0x88
	b        lbl_800A3104

lbl_800A3100:
	addi     r27, r31, 0x44

lbl_800A3104:
	lfs      f0, lbl_80516DD8@sda21(r2)
	fcmpo    cr0, f31, f0
	bge      lbl_800A312C
	lfs      f0, 4(r29)
	lfs      f1, lbl_80516DDC@sda21(r2)
	fdivs    f0, f0, f2
	lfs      f2, lbl_80516E00@sda21(r2)
	fsubs    f0, f1, f0
	fmuls    f30, f2, f0
	b        lbl_800A313C

lbl_800A312C:
	lfs      f0, 4(r29)
	lfs      f1, lbl_80516E00@sda21(r2)
	fdivs    f0, f0, f2
	fmuls    f30, f1, f0

lbl_800A313C:
	fmr      f1, f30
	bl       __0Cvt_fp2unsigned
	lis      r0, 0x4330
	stw      r3, 0x14(r1)
	lfd      f1, lbl_80516E08@sda21(r2)
	cmplwi   r3, 0x10
	stw      r0, 0x10(r1)
	lfd      f0, 0x10(r1)
	fsubs    f0, f0, f1
	fsubs    f4, f30, f0
	blt      lbl_800A3170
	li       r3, 0xf
	lfs      f4, lbl_80516DDC@sda21(r2)

lbl_800A3170:
	slwi     r0, r3, 2
	lfs      f3, 0x10(r29)
	add      r3, r27, r0
	lfs      f0, lbl_80516DD8@sda21(r2)
	lfsx     f2, r27, r0
	lfs      f1, 4(r3)
	fcmpo    cr0, f3, f0
	fsubs    f0, f1, f2
	fmadds   f0, f4, f0, f2
	fmuls    f0, f31, f0
	fabs     f1, f0
	bge      lbl_800A31AC
	lfs      f0, 0xc(r29)
	fadds    f2, f0, f1
	b        lbl_800A31B8

lbl_800A31AC:
	fsubs    f0, f3, f1
	lfs      f1, 0xc(r29)
	fsubs    f2, f1, f0

lbl_800A31B8:
	stfs     f2, 8(r29)
	b        lbl_800A31D0

lbl_800A31C0:
	lfs      f1, 4(r29)
	lfs      f0, 0xc(r29)
	fnmsubs  f2, f31, f1, f0
	stfs     f2, 8(r29)

lbl_800A31D0:
	lwz      r3, 0(r29)
	lfs      f1, 0x10(r3)
	lfs      f0, 0x14(r3)
	fmadds   f1, f2, f1, f0

lbl_800A31E0:
	psq_l    f31, 72(r1), 0, qr0
	lfd      f31, 0x40(r1)
	psq_l    f30, 56(r1), 0, qr0
	lfd      f30, 0x30(r1)
	lmw      r27, 0x1c(r1)
	lwz      r0, 0x54(r1)
	mtlr     r0
	addi     r1, r1, 0x50
	blr
	*/
}
