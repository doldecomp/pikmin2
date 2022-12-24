#include "types.h"
#include "og/Screen/anime.h"
#include "JSystem/J2D/J2DPane.h"
#include "JSystem/J2D/J2DAnm.h"
#include "JSystem/JUT/JUTException.h"
#include "JSystem/JKR/JKRArchive.h"
#include "og/Screen/ogScreen.h"
#include "System.h"

namespace og {
namespace Screen {

/*
 * __ct__Q32og6Screen12AnimBaseBaseFv
 *
 * --INFO--
 * Address:	........
 * Size:	000088
 */
AnimBaseBase::AnimBaseBase()
{
	// UNUSED FUNCTION
	m_type      = 0;
	m_frame     = 0.0f;
	m_lastFrame = 1.0f;
	m_speed     = 1.0f;
	_24         = 1.0f;
	_38         = true;
	_39         = false;
	_2C         = 0.0f;
	_30         = 1.0f;
	_34         = _30 - _2C;
	// TODO: Could this calculation be an inlined function of System?
	_28            = sys->m_deltaTime / 0.016666668f;
	m_anm          = nullptr;
	m_resourcePath = nullptr;
	_08            = false;
	_0C            = 0.0f;
	_10            = 1;
	m_alpha        = 255;
	m_doSetAlpha   = 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000020
 */
void AnimBaseBase::setArea(f32 frame, f32 p2)
{
	// UNUSED FUNCTION
	_2C     = frame;
	_30     = p2;
	_34     = p2 - frame;
	m_frame = frame;
	_10     = 1;
}

/*
 * init__Q32og6Screen12AnimBaseBaseFP10JKRArchivePc
 *
 * --INFO--
 * Address:	........
 * Size:	00010C
 */
void AnimBaseBase::init(JKRArchive* archive, char* resourcePath)
{
	m_resourcePath = resourcePath;
	void* resource = JKRFileLoader::getGlbResource(resourcePath, archive);
	JUT_ASSERTLINE(87, resource, "no name resource (%s) \n", resourcePath);
	m_anm       = J2DAnmLoaderDataBase::load(resource);
	m_lastFrame = m_anm->m_maxFrame - 1;
	_2C         = 0.0f;
	_30         = m_lastFrame;
	_34         = _30 - _2C;
	_08         = false;
	_0C         = 0.0f;
	_10         = 1;

	OSInitFastCast();
}

/*
 * --INFO--
 * Address:	80304CB0
 * Size:	000010
 */
void AnimBaseBase::start(f32 p1)
{
	_08 = true;
	_0C = p1;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000024
 */
void AnimBaseBase::setAllArea()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80304CC0
 * Size:	000150
 */
bool AnimBaseBase::updateSub()
{
	bool result = true;
	_39         = false;
	if (_10 != 0) {
		_10 = 0;
	} else {
		m_frame += m_speed * _28 * _24;
		if (m_frame > _30) {
			if (_38) {
				f32 temp = m_frame - _30;
				if (temp >= _34) {
					temp = 0.0f;
				}
				m_frame = _2C + temp;
				_39     = true;
			} else {
				m_frame = _30;
				moveAnim();
				result = false;
			}
		} else {
			if (m_frame < _2C) {
				if (_38) {
					f32 temp = _2C - m_frame;
					if (temp >= _34) {
						temp = 0.0f;
					}
					m_frame = _30 - temp;
					_39     = true;
				} else {
					m_frame = _2C;
					moveAnim();
					result = false;
				}
			}
		}
	}
	if (result) {
		moveAnim();
	}
	return result;
}

/*
 * update__Q32og6Screen12AnimBaseBaseFv
 *
 * --INFO--
 * Address:	80304E10
 * Size:	000078
 */
bool AnimBaseBase::update()
{
	if (_08) {
		_0C -= sys->m_deltaTime;
		if (_0C <= 0.0f) {
			_08 = false;
			_0C = 0.0f;
			start();
		}
		return true;
	}
	return updateSub();
}

/*
 * __ct__Q32og6Screen10AnimScreenFv
 *
 * --INFO--
 * Address:	80304E88
 * Size:	00009C
 */
AnimScreen::AnimScreen()
{
	m_screen = nullptr;
	m_type   = 1;
}

/*
 * init__Q32og6Screen10AnimScreenFP10JKRArchiveP9J2DScreenPc
 *
 * --INFO--
 * Address:	80304F24
 * Size:	000164
 */
void AnimScreen::init(JKRArchive* archive, J2DScreen* screen, char* resourcePath)
{
	AnimBaseBase::init(archive, resourcePath);
	updateScreen(screen, m_anm);
	moveAnim();
}

/*
 * start__Q32og6Screen10AnimScreenFv
 *
 * --INFO--
 * Address:	80305088
 * Size:	000090
 */
void AnimScreen::start()
{
	if (m_screen) {
		_08 = false;
		_0C = 0.0f;
		_10 = 1;
		update();
	}
}

/*
 * --INFO--
 * Address:	80305118
 * Size:	000060
 */
void AnimScreen::moveAnim()
{
	m_anm->m_currentFrame = m_frame;
	m_screen->animation();
	if (m_doSetAlpha != 0) {
		m_screen->setAlpha(m_alpha);
	}
}

/*
 * __ct__Q32og6Screen8AnimPaneFv
 *
 * --INFO--
 * Address:	80305178
 * Size:	0000A0
 */
AnimPane::AnimPane()
{
	m_pane = nullptr;
	m_type = 2;
}

/*
 * init__Q32og6Screen8AnimPaneFP10JKRArchiveP9J2DScreenUxPc
 *
 * --INFO--
 * Address:	80305218
 * Size:	000150
 */
void AnimPane::init(JKRArchive* archive, J2DScreen* parentScreen, u64 tag, char* resourcePath)
{
	AnimBaseBase::init(archive, resourcePath);
	updatePane(parentScreen, tag, m_anm);
}

/*
 * start__Q32og6Screen8AnimPaneFv
 *
 * --INFO--
 * Address:	80305368
 * Size:	000090
 */
void AnimPane::start()
{
	if (m_pane) {
		_08 = false;
		_0C = 0.0f;
		_10 = 1;
		update();
	}
}

/*
 * moveAnim__Q32og6Screen8AnimPaneFv
 *
 * --INFO--
 * Address:	803053F8
 * Size:	000060
 */
void AnimPane::moveAnim()
{
	m_anm->m_currentFrame = m_frame;
	m_pane->animationTransform();
	if (m_doSetAlpha != 0) {
		m_pane->setAlpha(m_alpha);
	}
}

/*
 * __ct__Q32og6Screen9AnimGroupFi
 *
 * --INFO--
 * Address:	80305458
 * Size:	000090
 */
AnimGroup::AnimGroup(int limit)
{
	m_animPanes = new AnimBaseBase*[limit];
	m_paneCount = 0;
	m_paneLimit = limit;
	for (int i = 0; i < m_paneLimit; i++) {
		m_animPanes[i] = nullptr;
	}
	_0C = 0;
	_10 = 0.0f;
	_14 = 0.0f;
	_18 = 0.0f;
}

/* setAnim__Q32og6Screen9AnimGroup
 * --INFO--
 * Address:	........
 * Size:	000064
 */
void AnimGroup::setAnim(og::Screen::AnimBaseBase* newAnim)
{
	int count = m_paneCount;
	if (count >= m_paneLimit) {
		JUT_PANICLINE(323, "anim group is overflow!!\n");
	} else {
		m_animPanes[count] = newAnim;
		m_paneCount++;
	}
}

/*
 * update__Q32og6Screen9AnimGroupFv
 *
 * --INFO--
 * Address:	803054E8
 * Size:	0001C0
 */
bool AnimGroup::update()
{
	bool anyUpdated = false;
	for (int i = 0; i < m_paneLimit; i++) {
		if (m_animPanes[i]) {
			bool updateResult = true;
			switch (m_animPanes[i]->m_type) {
			case 1:
				updateResult = m_animPanes[i]->update();
				break;
			case 2:
				updateResult = m_animPanes[i]->update();
				break;
			default:
				break;
			}
			if (updateResult) {
				anyUpdated = true;
			}
		}
	}

	// TODO: Fix naming of getVal inline when we know what _10 is in AnimGroup
	if (_0C != 0 && ((int)getFrame() == (int)getVal())) {
		setArea(_14, _18);
		start();
		_0C = 0;
	}
	return anyUpdated;
}

/*
 * --INFO--
 * Address:	803056A8
 * Size:	00005C
 */
void AnimGroup::setSpeed(f32 speed)
{
	for (int i = 0; i < m_paneLimit; i++) {
		if (m_animPanes[i]) {
			switch (m_animPanes[i]->m_type) {
			case 1:
				m_animPanes[i]->m_speed = speed;
				break;
			case 2:
				m_animPanes[i]->m_speed = speed;
				break;
			default:
				break;
			}
		}
	}
}

/*
 * --INFO--
 * Address:	80305704
 * Size:	00005C
 */
void AnimGroup::setRepeat(bool repeat)
{
	for (int i = 0; i < m_paneLimit; i++) {
		if (m_animPanes[i]) {
			switch (m_animPanes[i]->m_type) {
			case 1:
				m_animPanes[i]->_38 = repeat;
				break;
			case 2:
				m_animPanes[i]->_38 = repeat;
				break;
			default:
				break;
			}
		}
	}
}

/*
 * --INFO--
 * Address:	80305760
 * Size:	00005C
 */
void AnimGroup::setFrame(f32 frame)
{
	for (int i = 0; i < m_paneLimit; i++) {
		if (m_animPanes[i]) {
			switch (m_animPanes[i]->m_type) {
			case 1:
				m_animPanes[i]->m_frame = frame;
				break;
			case 2:
				m_animPanes[i]->m_frame = frame;
				break;
			default:
				break;
			}
		}
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	000040
 */
void AnimGroup::setAlpha(u8 alpha)
{
	// UNUSED FUNCTION
	// TODO: Confirm size.
	for (int i = 0; i < m_paneLimit; i++) {
		if (m_animPanes[i]) {
			m_animPanes[i]->m_alpha = alpha;
		}
	}
}

/*
 * setAllArea__Q32og6Screen9AnimGroupFv
 *
 * --INFO--
 * Address:	803057BC
 * Size:	000054
 */
void AnimGroup::setAllArea()
{
	for (int i = 0; i < m_paneLimit; i++) {
		AnimBaseBase* pane = m_animPanes[i];
		if (pane) {
			pane->_2C = 0.0f;
			pane->_30 = pane->m_lastFrame;
			pane->_34 = pane->_30 - pane->_2C;
		}
	}
}

/*
 * --INFO--
 * Address:	80305810
 * Size:	000020
 */
f32 AnimGroup::getFrame()
{
	// if (0 >= m_paneCount) {
	// 	return 0.0f;
	// } else {
	// 	return m_animPanes[0]->m_frame;
	// }
	f32 result = 0.0f;
	if (m_paneCount > 0) {
		result = m_animPanes[0]->m_frame;
	}
	return result;
	// return (m_paneCount <= 0) ? 0.0f : m_animPanes[0]->m_frame;
	// return (0 >= m_paneCount) ? 0.0f : m_animPanes[0]->m_frame;
	// if (m_paneCount > 0) {
	// 	return m_animPanes[0]->m_frame;
	// }
	// return 0.0f;
}

/*
 * setArea__Q32og6Screen9AnimGroupFff
 *
 * --INFO--
 * Address:	80305830
 * Size:	000088
 */
void AnimGroup::setArea(f32 frame, f32 p2)
{
	for (int i = 0; i < m_paneLimit; i++) {
		if (m_animPanes[i]) {
			switch (m_animPanes[i]->m_type) {
			case 1:
				m_animPanes[i]->setArea(frame, p2);
				break;
			case 2:
				m_animPanes[i]->setArea(frame, p2);
				break;
			default:
				break;
			}
		}
	}
}

/*
 * start__Q32og6Screen9AnimGroupFv
 *
 * --INFO--
 * Address:	803058B8
 * Size:	0000A8
 */
void AnimGroup::start()
{
	for (int i = 0; i < m_paneLimit; i++) {
		if (m_animPanes[i]) {
			switch (m_animPanes[i]->m_type) {
			case 1:
				m_animPanes[i]->start();
				break;
			case 2:
				m_animPanes[i]->start();
				break;
			default:
				break;
			}
		}
	}
}

/*
 * --INFO--
 * Address:	80305960
 * Size:	000018
 */
void AnimGroup::reservAnim(f32 p1, f32 p2, f32 p3)
{
	_0C = 1;
	_10 = p1;
	_14 = p2;
	_18 = p3;
}

/*
 * --INFO--
 * Address:	80305978
 * Size:	000020
 */
f32 AnimGroup::getLastFrame()
{
	f32 result = 0.0f;
	if (m_paneCount > 0) {
		result = m_animPanes[0]->m_lastFrame;
	}
	return result;
}

/*
 * --INFO--
 * Address:	80305998
 * Size:	000254
 */
void registAnimGroupScreen(AnimGroup* group, JKRArchive* archive, J2DScreen* screen, char* resourcePath, f32 p5)
{
	AnimScreen* newGroupScreen = new AnimScreen();
	newGroupScreen->init(archive, screen, resourcePath);
	newGroupScreen->_24 = p5;
	group->setAnim(newGroupScreen);
}

/*
 * --INFO--
 * Address:	80305BEC
 * Size:	00025C
 */
void registAnimGroupPane(AnimGroup* group, JKRArchive* archive, J2DScreen* parentScreen, u64 tag, char* resourcePath, f32 p6)
{
	AnimPane* newGroupPane = new AnimPane();
	newGroupPane->init(archive, parentScreen, tag, resourcePath);
	newGroupPane->_24 = p6;
	group->setAnim(newGroupPane);
}

} // namespace Screen
} // namespace og
