#ifndef _GAME_PELLETCONFIG_H
#define _GAME_PELLETCONFIG_H

#include "CNode.h"
#include "Vector3.h"
#include "TagParm.h"
#include "types.h"

#define PC_INDIRECTSTATE_NO  0x0
#define PC_INDIRECTSTATE_USE 0x1
#define PC_INDIRECTSTATE_YES 0x2

namespace Game {

struct PelletConfig : public CNode {
	struct TParms : public TagParameters { // _18
		TParms();
		virtual ~TParms() { }
		StringTagParm mName;              // _34
		StringTagParm mArchive;           // _44
		StringTagParm mTxtArchive;        // _54
		StringTagParm mBmd;               // _64
		StringTagParm mAnimMgr;           // _74
		StringTagParm mColltree;          // _84
		PrimTagParm<f32> mRadius;         // _94
		PrimTagParm<f32> mPRadius;        // _A4
		PrimTagParm<f32> mHeight;         // _B4
		PrimTagParm<f32> mInertiaScaling; // _C4
		StringTagParm mParticleType;      // _D4
		PrimTagParm<int> mNumParticles;   // _E4
		PrimTagParm<f32> mParticleSize;   // _F4
		PrimTagParm<f32> mFriction;       // _104
		PrimTagParm<int> mMin;            // _114
		PrimTagParm<int> mMax;            // _124
		PrimTagParm<int> mPikiCountMax;   // _134
		PrimTagParm<int> mPikiCountMin;   // _144
		StringTagParm mDynamics;          // _154
		PrimTagParm<int> mMoney;          // _164
		StringTagParm mUnique;            // _174
		StringTagParm mIndirect;          // _184
		PrimTagParm<int> mNumPMotions;    // _194
		PrimTagParm<f32> mDepth;          // _1A4
		PrimTagParm<f32> mDepthMax;       // _1B4
		PrimTagParm<f32> mDepthA;         // _1C4
		PrimTagParm<f32> mDepthB;         // _1D4
		PrimTagParm<f32> mDepthC;         // _1E4
		PrimTagParm<f32> mDepthD;         // _1F4
		PrimTagParm<Vector3f> mOffset;    // _204
		PrimTagParm<u64> mMessage;
		PrimTagParm<u16> mCode;
		PrimTagParm<u16> mDictionary;
		s16 mIndex;

		u8 mIndirectState;
	}; // struct TParms

	PelletConfig();
	virtual ~PelletConfig() { }

	TParms mParams; // _04
};

struct PelletConfigList : public CNode {
	PelletConfigList();
	virtual ~PelletConfigList() {};

	PelletConfig* getPelletConfig(char* name);
	PelletConfig* getPelletConfig(int index);
	PelletConfig* getPelletConfig_ByDictionaryNo(int dictionaryNumber);
	void read(Stream&);

	/**
	 * @fabricated
	 */
	int getConfigCount() { return mConfigCnt; }

	int mConfigCnt;         // _18
	PelletConfig* mConfigs; // _1C
};

} // namespace Game

#endif
