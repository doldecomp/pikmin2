#ifndef _GAME_IKSYSTEMBASE_H
#define _GAME_IKSYSTEMBASE_H

#include "Vector3.h"
#include "Matrixf.h"
#include "Dolphin/mtx.h"

struct CollPart;

namespace SysShape {
struct Model;
} // namespace SysShape

namespace Game {
struct EnemyBase;
struct JointGroundCallBack;

struct IKSystemParms {
	inline IKSystemParms()
	{
		_00           = -1;
		_04           = 0.0f;
		_08           = 0.0f;
		_0C           = 0.75f;
		mHeightOffset = 120.0f;
		_14           = 3.0f;
		_18           = -0.15f;
		_1C           = 0.5f;
		_20           = 10.0f;
		_24           = -2.0f;
		_28           = 0.0f;
		_2C           = 75.0f;
		_30           = 0.0f;
		_34           = 30.0f;
		_38           = 60.0f;
		_3C           = 0.1f;
		_40           = 0.7f;
		_44           = -1.5f;
	}

	int _00;           // _00
	f32 _04;           // _04
	f32 _08;           // _08
	f32 _0C;           // _0C
	f32 mHeightOffset; // _10
	f32 _14;           // _14
	f32 _18;           // _18
	f32 _1C;           // _1C
	f32 _20;           // _20
	f32 _24;           // _24
	f32 _28;           // _28
	f32 _2C;           // _2C
	f32 _30;           // _30
	f32 _34;           // _34
	f32 _38;           // _38
	f32 _3C;           // _3C
	f32 _40;           // _40
	f32 _44;           // _44
};

struct IKSystemBase {
	IKSystemBase();

	void init();
	void setLegJointMatrix(int, Matrixf*);
	void setParameters(IKSystemParms*);

	void startProgramedIK();
	void startMovePosition(Vector3f&);

	void startBlendMotion();
	void finishBlendMotion();
	void checkJointScaleOn();

	void update();

	void makeBendRatio();
	void moveBottomJointPosition();
	bool onGroundPosition();

	bool mEnabled;               // _00
	bool mBlendMotion;           // _01
	bool mOnGround;              // _02
	bool _03;                    // _03
	bool mScaleJoints;           // _04
	f32 mBendRatio;              // _08, aka rotation in radians
	f32 mMoveRatio;              // _0C
	f32 mTimer;                  // _10
	f32 mDistance1;              // _14, some distance I'm not sure of
	f32 mDistance2;              // _18, same as above
	Vector3f mTargetPosition;    // _1C
	Vector3f mIkPositions[3];    // _28
	Matrixf** mLegJointMatrices; // _4C
	Matrixf _50;                 // _50
	Matrixf mBottomMtx;          // _54
	IKSystemParms* mParameters;  // _58
};

struct IKSystemMgr {
	IKSystemMgr();

	void init(EnemyBase*, JointGroundCallBack*);
	void setupJoint(SysShape::Model*, int, char**);
	void setupCallBack(SysShape::Model*, char*);
	void setParameters(IKSystemParms*);
	void startProgramedIK();
	void startIKMotion();
	void finishIKMotion();
	void forceFinishIKMotion();
	void startBlendMotion();
	void finishBlendMotion();
	void checkJointScaleOn();
	void checkJointScaleOff();
	bool isFinishIKMotion();
	void resetAnimationCallBack();
	void setAnimationCallBack();
	void doUpdate();
	void makeMatrix();
	Vector3f getCollisionCentre(int);
	bool isCollisionCheck(CollPart*);
	void updateController();
	void setNextCentrePosition();
	void calcFaceDir();
	void calcCentrePosition();
	void calcTraceCentrePosition();

	u8 _00;                                    // _00, unknown
	u8 _01;                                    // _01
	u8 _02;                                    // _02
	f32 mFaceDir;                              // _04
	f32 _08;                                   // _08
	f32 _0C;                                   // _0C
	f32 _10;                                   // _10
	f32 _14;                                   // _14
	f32 _18;                                   // _18
	u32 _1C;                                   // _1C
	u32 _20;                                   // _20
	u32 _24;                                   // _24
	u32 _28;                                   // _28
	Vector3f mTargetPosition;                  // _2C
	Vector3f _38;                              // _38, position of something
	Vector3f mTraceCentrePosition;             // _44
	f32 _50;                                   // _50
	f32 _54;                                   // _54
	f32 _58;                                   // _58
	u8 _5C[0x30];                              // _5C, unknown
	IKSystemBase* mSystemBase;                 // _8C
	EnemyBase* mOwner;                         // _90
	JointGroundCallBack* mJointGroundCallBack; // _94
	u32 _98;                                   // _98, unknown
};

} // namespace Game

#endif
