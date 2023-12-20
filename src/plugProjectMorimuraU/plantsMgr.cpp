#include "Game/plantsMgr.h"

namespace Game {
/**
 * @note Address: 0x80353D4C
 * @note Size: 0x64
 */
Tanpopo::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�^���|�|�}�l�[�W��"; // dandelion manager
}

/**
 * @note Address: 0x80353DB0
 * @note Size: 0x48
 */
void Tanpopo::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x80353DF8
 * @note Size: 0x20
 */
EnemyBase* Tanpopo::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80353E18
 * @note Size: 0x64
 */
Clover::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�N���[�o�[�}�l�[�W��"; // clover manager
}

/**
 * @note Address: 0x80353E7C
 * @note Size: 0x48
 */
void Clover::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x80353EC4
 * @note Size: 0x20
 */
EnemyBase* Clover::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80353EE4
 * @note Size: 0x64
 */
HikariKinoko::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�q�J���L�m�R�}�l�[�W��"; // hikari mushroom manager
}

/**
 * @note Address: 0x80353F48
 * @note Size: 0x48
 */
void HikariKinoko::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x80353F90
 * @note Size: 0x20
 */
EnemyBase* HikariKinoko::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80353FB0
 * @note Size: 0x64
 */
Ooinu_s::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�������ʂӂ���i���j�}�l�[�W��"; // oinu fuguri (small) manager
}

/**
 * @note Address: 0x80354014
 * @note Size: 0x48
 */
void Ooinu_s::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x8035405C
 * @note Size: 0x20
 */
EnemyBase* Ooinu_s::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x8035407C
 * @note Size: 0x64
 */
KareOoinu_s::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�͂ꂨ�����ʂӂ���i���j�}�l�[�W��"; // withered dog fuguri (small) manager
}

/**
 * @note Address: 0x803540E0
 * @note Size: 0x48
 */
void KareOoinu_s::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x80354128
 * @note Size: 0x20
 */
EnemyBase* KareOoinu_s::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80354148
 * @note Size: 0x64
 */
Ooinu_l::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�������ʂӂ���i��j�}�l�[�W��"; // big dog fuguri (large) manager
}

/**
 * @note Address: 0x803541AC
 * @note Size: 0x48
 */
void Ooinu_l::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x803541F4
 * @note Size: 0x20
 */
EnemyBase* Ooinu_l::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80354214
 * @note Size: 0x64
 */
KareOoinu_l::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�͂ꂨ�����ʂӂ���i��j�}�l�[�W��"; // withered dog fuguri (large) manager
}

/**
 * @note Address: 0x80354278
 * @note Size: 0x48
 */
void KareOoinu_l::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x803542C0
 * @note Size: 0x20
 */
EnemyBase* KareOoinu_l::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x803542E0
 * @note Size: 0x64
 */
Wakame_s::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "���i���j�}�l�[�W��"; // sprout (small) manager
}

/**
 * @note Address: 0x80354344
 * @note Size: 0x48
 */
void Wakame_s::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x8035438C
 * @note Size: 0x20
 */
EnemyBase* Wakame_s::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x803543AC
 * @note Size: 0x64
 */
Wakame_l::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "���i��j�}�l�[�W��"; // sprout (large) manager
}

/**
 * @note Address: 0x80354410
 * @note Size: 0x48
 */
void Wakame_l::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x80354458
 * @note Size: 0x20
 */
EnemyBase* Wakame_l::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80354478
 * @note Size: 0x64
 */
Tukushi::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�����}�l�[�W��"; // tsukushi manager
}

/**
 * @note Address: 0x803544DC
 * @note Size: 0x48
 */
void Tukushi::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x80354524
 * @note Size: 0x20
 */
EnemyBase* Tukushi::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80354544
 * @note Size: 0x64
 */
Watage::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�Ȗу}�l�[�W��"; // fluff manager
}

/**
 * @note Address: 0x803545A8
 * @note Size: 0x48
 */
void Watage::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x803545F0
 * @note Size: 0x20
 */
EnemyBase* Watage::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80354610
 * @note Size: 0x64
 */
DiodeRed::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�ԃ_�C�I�[�h�}�l�[�W��"; // red diode manager
}

/**
 * @note Address: 0x80354674
 * @note Size: 0x48
 */
void DiodeRed::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x803546BC
 * @note Size: 0x20
 */
EnemyBase* DiodeRed::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x803546DC
 * @note Size: 0x64
 */
DiodeGreen::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�_�C�I�[�h�}�l�[�W��"; // blue diode manager
}

/**
 * @note Address: 0x80354740
 * @note Size: 0x48
 */
void DiodeGreen::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x80354788
 * @note Size: 0x20
 */
EnemyBase* DiodeGreen::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x803547A8
 * @note Size: 0x64
 */
Margaret::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�}�[�K���b�g�}�l�[�W��"; // margaret manager
}

/**
 * @note Address: 0x8035480C
 * @note Size: 0x48
 */
void Margaret::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x80354854
 * @note Size: 0x20
 */
EnemyBase* Margaret::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80354874
 * @note Size: 0x64
 */
Nekojarashi::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "�˂�����炵�}�l�[�W��"; // nekojyarashi manager
}

/**
 * @note Address: 0x803548D8
 * @note Size: 0x48
 */
void Nekojarashi::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x80354920
 * @note Size: 0x20
 */
EnemyBase* Nekojarashi::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80354940
 * @note Size: 0x64
 */
Chiyogami::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "��㎆�}�l�[�W��"; // chiyogami manager
}

/**
 * @note Address: 0x803549A4
 * @note Size: 0x48
 */
void Chiyogami::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x803549EC
 * @note Size: 0x20
 */
EnemyBase* Chiyogami::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }

/**
 * @note Address: 0x80354A0C
 * @note Size: 0x64
 */
Zenmai::Mgr::Mgr(int objLimit, u8 modelType)
    : EnemyMgrBaseAlwaysMovieActor(objLimit, modelType)
{
	mName = "����܂��}�l�[�W��"; // mainspring manager
}

/**
 * @note Address: 0x80354A70
 * @note Size: 0x48
 */
void Zenmai::Mgr::doAlloc() { init(new EnemyParmsBase); }

/**
 * @note Address: 0x80354AB8
 * @note Size: 0x20
 */
EnemyBase* Zenmai::Mgr::birth(EnemyBirthArg& birthArg) { return EnemyMgrBase::birth(birthArg); }
} // namespace Game
