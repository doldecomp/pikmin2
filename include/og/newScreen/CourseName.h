#ifndef _OG_NEWSCREEN_COURSENAME_H
#define _OG_NEWSCREEN_COURSENAME_H

#include "Screen/screenObj.h"
#include "JSystem/J2D/J2DPane.h"

namespace P2DScreen {
struct Mgr_tuning;
} // namespace P2DScreen

namespace og {
namespace Screen {
struct DispMemberCourseName;
struct AnimGroup;
} // namespace Screen

namespace newScreen {
struct CourseName : public ::Screen::SceneBase {
	CourseName();

	virtual const char* getResName() const { return ""; }               // _1C (weak)
	virtual SceneType getSceneType() { return SCENE_COURSE_NAME; }      // _08 (weak)
	virtual ScreenOwnerID getOwnerID() { return OWNER_OGA; }            // _0C (weak)
	virtual ScreenMemberID getMemberID() { return MEMBER_COURSE_NAME; } // _10 (weak)

	virtual void doCreateObj(JKRArchive*);                  // _20
	virtual void doUserCallBackFunc(Resource::MgrCommand*); // _24

	void doCreateObjUserCallBackFunc(JKRArchive*);

	// unused/inline
	int getCourseNum();
	~CourseName();

	// _00      = VTBL
	// _00-_220 = Screen::SceneBase
	int mCourseIndex; // _220
};

struct ObjCourseName : public ::Screen::ObjBase {
	ObjCourseName(const char*);

	virtual ~ObjCourseName();                             // _08 (weak)
	virtual bool doStart(const ::Screen::StartSceneArg*); // _44
	virtual bool doEnd(const ::Screen::EndSceneArg*);     // _48
	virtual void doCreate(JKRArchive*);                   // _4C
	virtual bool doUpdateFadein();                        // _50
	virtual void doUpdateFadeinFinish();                  // _54
	virtual bool doUpdate();                              // _58
	virtual void doUpdateFinish();                        // _5C
	virtual bool doUpdateFadeout();                       // _60
	virtual void doUpdateFadeoutFinish();                 // _64
	virtual void doDraw(Graphics& gfx);                   // _68

	inline void drawBG(Graphics&);

	// unused/inline
	bool commonUpdate();

	// _00     = VTBL1
	// _18     = VTBL2
	// _00-_38 = Screen::ObjBase
	og::Screen::DispMemberCourseName* mDisp; // _38
	P2DScreen::Mgr_tuning* mScreen;          // _3C
	og::Screen::AnimGroup* mAnims;           // _40
	f32 mFadeLevel;                          // _44
	f32 mAlpha;                              // _48
	f32 mTimer;                              // _4C, timer?
	u8 mState;                               // _50
	u8 _51[3];                               // padding? it breaks if i dont have this?
	JUtility::TColor mColor;                 // _54
	u8 mDoEnd;                               // _58
	f32 mBackgroundAlpha;                    // _5C

	static struct StaticValues {
		inline StaticValues()
		{
			_00 = 0.3f;
			_04 = 1.0f;
			_08 = 0.2f;
			_0C = 3.0f;
		}

		f32 _00; // _00
		f32 _04; // _04
		f32 _08; // _08
		f32 _0C; // _0C
	} msVal;
};

extern const char* CourseNumToSZS[];
extern const char* bloFileNameCourse[];
extern char* animFile_Course00[];
extern char* animFile_Course01[];
extern char* animFile_Course02[];
extern char* animFile_Course03[];
extern char** animFileTableCourse[];

} // namespace newScreen
} // namespace og

#endif
