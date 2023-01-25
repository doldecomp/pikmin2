#include "Game/Entities/KumaChappy.h"

namespace Game {
namespace KumaChappy {

static const char kumaChappyMgrName[] = "246-KumaChappyMgr";

/*
 * --INFO--
 * Address:	802992B4
 * Size:	000050
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBase(objLimit, modelType)
{
	mName = "�N�}�`���b�s�[�}�l�[�W��"; // bear chappy manager
}

/*
 * --INFO--
 * Address:	80299304
 * Size:	000048
 */
void Mgr::doAlloc() { init(new Parms); }

/*
 * --INFO--
 * Address:	80299464
 * Size:	000060
 */
void Mgr::createObj(int count) { mObj = new Obj[count]; }

/*
 * --INFO--
 * Address:	80299580
 * Size:	000010
 */
EnemyBase* Mgr::getEnemy(int index) { return &mObj[index]; }

} // namespace KumaChappy
} // namespace Game
