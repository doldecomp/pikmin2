#include "trig.h"
#include "Game/generalEnemyMgr.h"

#include "Game/Entities/Pelplant.h"
#include "Game/Entities/Qurione.h"
#include "Game/Entities/Rock.h"
#include "Game/Entities/ElecHiba.h"
#include "Game/PelletBirthBuffer.h"
#include "Game/MapMgr.h"
#include "Dolphin/rand.h"

namespace Game {

static const char unusedGenEnemyName[] = "genEnemy";

/**
 * @note Address: 0x80124778
 * @note Size: 0x3C
 */
static GenObject* makeObjectEnemy() { return new GenObjectEnemy; }

/**
 * @note Address: 0x801247B4
 * @note Size: 0xD0
 */
GenObjectEnemy::GenObjectEnemy()
    : GenObject('teki', "object type", "�G���Z�b�g")
    , mEnemyID(EnemyTypeID::EnemyID_Pelplant)
    , mSpawnType(1)
    , mTekiBirthType(0)
    , mTekiNum(1)
    , mAppearRadius(100.0f)
    , mDirection(0)
    , mEnemySize(0)
    , mOtakaraItemCode(0)
    , mEnemyGenerator(nullptr)
    , mFlagBit()
{
	createEnemyGenerator();
	mFlagBit.set(1);
}

/**
 * @note Address: 0x80124884
 * @note Size: 0x8C
 */
void GenObjectEnemy::initialise()
{
	GenObjectFactoryFactory* metafactory = GenObjectFactory::factory;

	// Make sure we don't create a new factory over the limit
	if (metafactory->mCount >= metafactory->mLimit) {
		return;
	}

	// Initialise the new factory with default teki parameters
	metafactory->mFactories[metafactory->mCount].mTypeID       = 'teki';
	metafactory->mFactories[metafactory->mCount].mMakeFunction = &makeObjectEnemy;
	metafactory->mFactories[metafactory->mCount].mName         = "�G�𔭐�";
	metafactory->mFactories[metafactory->mCount].mVersion      = '0005';
	metafactory->mCount++;
}

/**
 * @note Address: 0x80124910
 * @note Size: 0x4
 */
void GenObjectEnemy::ramSaveParameters(Stream&) { }

/**
 * @note Address: 0x80124914
 * @note Size: 0x4
 */
void GenObjectEnemy::ramLoadParameters(Stream&) { }

/**
 * @note Address: 0x80124918
 * @note Size: 0x6B4
 */
Creature* GenObjectEnemy::generate(Game::Generator* gen)
{
	Vector3f startpos;

	// Grab initial starting positions
	f32 x, y, z;
	x = gen->mPosition.x + gen->mOffset.x; // f31
	y = gen->mPosition.y + gen->mOffset.y; // f30
	z = gen->mPosition.z + gen->mOffset.z; // f29

	startpos.x = x;
	startpos.y = y;
	startpos.z = z;

	// Grab the number of tekis we're spawning
	int tekicount = mTekiNum - gen->mDeathCount;

	Vector3f posVector[10];  // holds initial positions
	Vector3f corrVector[10]; // holds corrections if too close to other tekis
	Vector3f vector;
	f32 ox, oz, offR, oa;

	for (int i = 0; i < tekicount; i++) {
		// If teki is Type 1, don't do any random adjustments
		if (mSpawnType == 1) {
			posVector[i] = startpos;
			// copy(&posVector[i], &startpos);
			continue;
		}
		// If teki isn't Type 1, jiggle it a bit
		oa   = TAU * randFloat();           // random angle between 0 and 360 degrees
		offR = mAppearRadius * randFloat(); // random distance between 0 and m_appearRadius
		oz   = offR * pikmin2_cosf(oa);
		ox   = offR * pikmin2_sinf(oa);

		posVector[i].x = ox;
		posVector[i].y = 0.0f;
		posVector[i].z = oz;

		vector = posVector[i];
		vector += startpos;
		posVector[i] = vector;
	}

	// Default enemy territory size is 35 units, unless overwritten by m_enemySize
	// f32 enemy_territory = 35.0f;
	// f32 dz, dx, dy;
	f32 dx, dy, dz;
	f32 enemy_territory = 35.0f;
	if (mEnemySize > 0.0f) {
		enemy_territory = mEnemySize;
	}

	// iteratively calculate corrections 5x, to make sure
	// Teki A doesn't force Teki B into Teki C accidentally
	// (I guess).
	for (int j = 0; j < 5; j++) {
		// Initialise the corrections as 0
		for (int i = 0; i < tekicount; i++) {
			corrVector[i].z = 0.0f;
			corrVector[i].y = 0.0f;
			corrVector[i].x = 0.0f;
		}
		// Push the enemies away from each other if too close
		for (int i = 0; i < tekicount; i++) {
			for (int k = i + 1; k < tekicount; k++) {
				// loop over all unique pairings of teki
				Vector3f& position            = posVector[i];  // position of teki i
				Vector3f& position2           = posVector[k];  // position of teki k
				Vector3f& positionCorrection  = corrVector[i]; // correction for teki i
				Vector3f& positionCorrection2 = corrVector[k]; // correction for teki k
				// calculate delta components from initial positions
				dy = position.y - position2.y;
				dx = position.x - position2.x;
				dz = position.z - position2.z;

				f32 sq_dist = dx * dx + dy * dy + dz * dz;
				f32 dist    = pikmin2_sqrtf(sq_dist); // euclidean distance between teki i and k

				// Calculate corrections if too close
				// (if tekis are closer than the 'enemy territory', shove 'em so they're a 'territory' apart)
				if (dist < enemy_territory) {
					// idk why it re-calculates the distance here but it seems to, go figure
					f32 newdist = pikmin2_sqrtf(sq_dist);
					// dist needs to be non-zero to use as denominator
					// dist should always be >= 0 because square root
					if (newdist > 0.0f) {
						f32 c0 = 1.0f / newdist;
						dx     = dx * c0;
						dy     = dy * c0;
						dz     = dz * c0;
					}
					// assuming distance =/= 0, corrected delta component is
					// delta_2 = (1/2) * delta_1 * (enemy_territory - dist) / dist
					// basically has the effect of making new separation equal to 'enemy territory' size
					f32 c1 = (enemy_territory - dist) * 0.5f;
					dx     = dx * c1;
					dy     = dy * c1;
					dz     = dz * c1;
					// corrections for teki i
					positionCorrection.x += dx;
					positionCorrection.y += dy;
					positionCorrection.z += dz;
					// corrections for teki k
					positionCorrection2.x -= dx;
					positionCorrection2.y -= dy;
					positionCorrection2.z -= dz;
				}
			}
		}
		// adjust initial positions by corrections
		for (int i = 0; i < tekicount; i++) {
			Vector3f& positionCorrection = corrVector[i];
			Vector3f& position           = posVector[i];

			position.x += positionCorrection.x;
			position.y += positionCorrection.y;
			position.z += positionCorrection.z;
		}
	}

	// Spawn the teki (on the ground)
	for (int i = 0; i < tekicount; i++) {

		if (mapMgr) {
			posVector[i].y = mapMgr->getMinY(posVector[i]); // makes sure teki is placed on floor
		}

		GenArg initVars(posVector[i]);
		birth(&initVars)->mGenerator = gen; // spawn teki
	}
	return nullptr;
}

/**
 * @note Address: 0x80124FCC
 * @note Size: 0xE0
 */
Creature* GenObjectEnemy::birth(Game::GenArg* genArg)
{
	getLatestVersion();
	EnemyBirthArg birthArg;
	birthArg.mPosition                = genArg->mPosition;
	birthArg.mFaceDir                 = TORADIANS(mDirection);
	birthArg.mTekiBirthType           = mTekiBirthType;
	birthArg.mGenerator               = mEnemyGenerator;
	birthArg.mOtakaraItemCode         = mOtakaraItemCode;
	birthArg.mPelletInfo.mColor       = mPelletInfo.mColor;
	birthArg.mPelletInfo.mSize        = mPelletInfo.mSize;
	birthArg.mPelletInfo.mMinPellets  = mPelletInfo.mMinPellets;
	birthArg.mPelletInfo.mMaxPellets  = mPelletInfo.mMaxPellets;
	birthArg.mPelletInfo.mSpawnChance = mPelletInfo.mSpawnChance;
	EnemyBase* enemy                  = generalEnemyMgr->birth(mEnemyID, birthArg);
	if (enemy) {
		enemy->init(nullptr);
	}
	return enemy;
}

/**
 * @note Address: 0x801250AC
 * @note Size: 0x218
 */
void GenObjectEnemy::doWrite(Stream& stream)
{
	stream.textWriteTab(stream.mTabCount);
	stream.writeShort((u16)mEnemyID);
	stream.textWriteText("\t\t# %s \r\n", "teki");

	stream.textWriteTab(stream.mTabCount);
	stream.writeByte(mTekiBirthType);
	stream.textWriteText("\t\t# %s \r\n", "teki_birth_type");

	stream.textWriteTab(stream.mTabCount);
	stream.writeShort((u16)mTekiNum);
	stream.textWriteText("\t\t# %s \r\n", "teki_num");

	stream.textWriteTab(stream.mTabCount);
	stream.writeFloat(mDirection);
	stream.textWriteText("\t\t# %s \r\n", "face direction");

	stream.textWriteTab(stream.mTabCount);
	stream.writeByte(mSpawnType);
	stream.textWriteText("\t\t# %s \r\n", "0:point 1:circle");

	stream.textWriteTab(stream.mTabCount);
	stream.writeFloat(mAppearRadius);
	stream.textWriteText("\t\t# %s \r\n", "appear radius");

	stream.textWriteTab(stream.mTabCount);
	stream.writeFloat(mEnemySize);
	stream.textWriteText("\t\t# %s \r\n", "enemy size");

	mOtakaraItemCode.write(stream);

	mPelletInfo.write(stream);

	EnemyGeneratorBase* gen = mEnemyGenerator;
	if (gen) {
		gen->mVersion = gen->getLatestVersion();

		stream.textWriteTab(stream.mTabCount);
		gen->mVersion.write(stream);
		stream.textWriteText("\t\t# Version \r\n");
		gen->doWrite(stream);
	}
}

/**
 * @note Address: 0x801252D4
 * @note Size: 0x1E4
 */
void GenObjectEnemy::doRead(Stream& stream)
{
	mEnemyID       = EnemyTypeID::EnemyID_Pelplant;
	mTekiNum       = 1;
	mTekiBirthType = 0;
	mDirection     = 0.0f;
	mSpawnType     = 1;
	mAppearRadius  = 100.0f;
	mEnemySize     = 0.0f;

	if (mRawID == getLatestVersion()) {
		mEnemyID       = static_cast<EnemyTypeID::EEnemyTypeID>((u16)stream.readShort());
		mTekiBirthType = stream.readByte();
		mTekiNum       = stream.readShort();
		mDirection     = stream.readFloat();
		mSpawnType     = stream.readByte();
		mAppearRadius  = stream.readFloat();
		mEnemySize     = stream.readFloat();
		mOtakaraItemCode.read(stream);
		mPelletInfo.read(stream);

		createEnemyGenerator();

		EnemyGeneratorBase* gen = mEnemyGenerator;
		if (gen) {
			gen->mVersion.read(stream);
			gen->doRead(stream);
		}

		if (pelletMgr) {
			PelletInitArg initArg;
			if (pelletMgr->makePelletInitArg(initArg, mOtakaraItemCode)) {
				if (pelletMgr->setUse(&initArg)) {
					PelletBirthBuffer::entry(initArg);
				} else {
					mOtakaraItemCode.mValue = 0;
				}
			}
		}
	} else {
		doReadOldVersion(stream);
	}
}

/**
 * @note Address: 0x801254BC
 * @note Size: 0x470
 */
void GenObjectEnemy::doReadOldVersion(Stream& stream)
{
	switch (mRawID) {
	case '0000': {
		mEnemyID = static_cast<EnemyTypeID::EEnemyTypeID>((u16)stream.readShort());
		break;
	}
	case '0001': {
		mEnemyID      = static_cast<EnemyTypeID::EEnemyTypeID>((u16)stream.readShort());
		mTekiNum      = stream.readShort();
		mDirection    = stream.readFloat();
		mSpawnType    = stream.readByte();
		mAppearRadius = stream.readFloat();

		createEnemyGenerator();

		EnemyGeneratorBase* gen = mEnemyGenerator;
		if (gen) {
			gen->mVersion.read(stream);
			gen->doRead(stream);
		}

		if (generalEnemyMgr) {
			generalEnemyMgr->addEnemyNum(mEnemyID, mTekiNum, nullptr);
		}
		break;
	}
	case '0002': {
		mEnemyID      = static_cast<EnemyTypeID::EEnemyTypeID>((u16)stream.readShort());
		mTekiNum      = stream.readShort();
		mDirection    = stream.readFloat();
		mSpawnType    = stream.readByte();
		mAppearRadius = stream.readFloat();
		mEnemySize    = stream.readFloat();

		createEnemyGenerator();

		EnemyGeneratorBase* gen = mEnemyGenerator;
		if (gen) {
			gen->mVersion.read(stream);
			gen->doRead(stream);
		}

		if (generalEnemyMgr) {
			generalEnemyMgr->addEnemyNum(mEnemyID, mTekiNum, nullptr);
		}
		break;
	}
	case '0003': {
		mEnemyID      = static_cast<EnemyTypeID::EEnemyTypeID>((u16)stream.readShort());
		mTekiNum      = stream.readShort();
		mDirection    = stream.readFloat();
		mSpawnType    = stream.readByte();
		mAppearRadius = stream.readFloat();
		mEnemySize    = stream.readFloat();

		mOtakaraItemCode.read(stream);

		createEnemyGenerator();

		EnemyGeneratorBase* gen = mEnemyGenerator;
		if (gen) {
			gen->mVersion.read(stream);
			gen->doRead(stream);
		}

		if (generalEnemyMgr) {
			generalEnemyMgr->addEnemyNum(mEnemyID, mTekiNum, nullptr);
		}

		if (pelletMgr) {
			PelletInitArg initArg;
			if (pelletMgr->makePelletInitArg(initArg, mOtakaraItemCode)) {
				if (pelletMgr->setUse(&initArg)) {
					PelletBirthBuffer::entry(initArg);
				} else {
					mOtakaraItemCode.mValue = 0;
				}
			}
		}
		break;
	}
	case '0004': {
		mEnemyID       = static_cast<EnemyTypeID::EEnemyTypeID>((u16)stream.readShort());
		mTekiBirthType = 0;
		mTekiNum       = stream.readShort();
		mDirection     = stream.readFloat();
		mSpawnType     = stream.readByte();
		mAppearRadius  = stream.readFloat();
		mEnemySize     = stream.readFloat();
		mOtakaraItemCode.read(stream);
		mPelletInfo.read(stream);

		createEnemyGenerator();

		EnemyGeneratorBase* gen = mEnemyGenerator;
		if (gen) {
			gen->mVersion.read(stream);
			gen->doRead(stream);
		}

		if (pelletMgr) {
			PelletInitArg initArg;
			if (pelletMgr->makePelletInitArg(initArg, mOtakaraItemCode)) {
				if (pelletMgr->setUse(&initArg)) {
					PelletBirthBuffer::entry(initArg);
				} else {
					mOtakaraItemCode.mValue = 0;
				}
			}
		}

		break;
	}
	}
}

#define GENERATOR_CASE(id, name)                        \
	case id: {                                          \
		mEnemyGenerator = new EnemyGeneratorBase(name); \
		break;                                          \
	}

/**
 * @note Address: 0x8012592C
 * @note Size: 0xE38
 * TODO: The EnemyGeneratorBase ctor shouldn't be inlined
 */
EnemyGeneratorBase* GenObjectEnemy::createEnemyGenerator()
{
	switch (mEnemyID) {
	case EnemyTypeID::EnemyID_Pelplant:
		mEnemyGenerator = new Pelplant::Generator();
		break;

		GENERATOR_CASE(EnemyTypeID::EnemyID_Kochappy, "�ԃR�`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_BlueKochappy, "�R�`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_YellowKochappy, "���R�`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Chappy, "�ԃ`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_BlueChappy, "�`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_YellowChappy, "���`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_BluePom, "�|���K�V��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_RedPom, "�ԃ|���K�V��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_YellowPom, "���|���K�V��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_BlackPom, "���|���K�V��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_WhitePom, "���|���K�V��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_RandPom, "�|�|�K�V��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Kogane, "�R�K�l")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Wealthy, "�I�I�K�l���`")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Fart, "�o�o�R�K�l")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Frog, "�C���K�G��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_MaroFrog, "�}���K�G��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_UjiA, "�E�W���R��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Tobi, "�g�r���R")
		GENERATOR_CASE(EnemyTypeID::EnemyID_UjiB, "�E�W���R��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Armor, "�����C���V")

	case EnemyTypeID::EnemyID_Qurione:
		mEnemyGenerator = new Qurione::Generator();
		break;

	case EnemyTypeID::EnemyID_Rock:
		mEnemyGenerator = new Game::Rock::Generator();
		break;

		GENERATOR_CASE(EnemyTypeID::EnemyID_Hiba, "�q�o")
		GENERATOR_CASE(EnemyTypeID::EnemyID_GasHiba, "�K�X�q�o")

	case EnemyTypeID::EnemyID_ElecHiba:
		mEnemyGenerator = new Game::ElecHiba::Generator();
		break;

		GENERATOR_CASE(EnemyTypeID::EnemyID_Sarai, "�T���C���V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Tank, "�u�^�h�b�N��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Wtank, "�~�Y�u�^�h�b�N��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Catfish, "�i�}�Y")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Tadpole, "�I�^�}")
		GENERATOR_CASE(EnemyTypeID::EnemyID_ElecBug, "�f���L���V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Mar, "�t�E�Z���h�b�N��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Queen, "�N�C�[���`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Baby, "�x�r�[�`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Demon, "�I�j�T���C")
		GENERATOR_CASE(EnemyTypeID::EnemyID_FireChappy, "���L�`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_SnakeCrow, "�w�r�K���X")
		GENERATOR_CASE(EnemyTypeID::EnemyID_KumaChappy, "�N�}�`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Bomb, "�o�N�_��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Egg, "�n�e�i�^�}�S")
		GENERATOR_CASE(EnemyTypeID::EnemyID_PanModoki, "�p�����h�L")
		GENERATOR_CASE(EnemyTypeID::EnemyID_OoPanModoki, "��p�����h�L")
		GENERATOR_CASE(EnemyTypeID::EnemyID_PanModokiNest, "�p�����h�L��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Fuefuki, "�t�G�t�L")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Tanpopo, "�^���|�|")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Watage, "�킽��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Clover, "�N���[�o�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_HikariKinoko, "�q�J���L�m�R")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Ooinu_s, "�������ʂӂ���i���j")
		GENERATOR_CASE(EnemyTypeID::EnemyID_KareOoinu_s, "�͂ꂨ�����ʂӂ���i���j")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Ooinu_l, "�������ʂӂ���i��j")
		GENERATOR_CASE(EnemyTypeID::EnemyID_KareOoinu_l, "�͂ꂨ�����ʂӂ���i��j")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Wakame_s, "���i���j")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Wakame_l, "���i��j")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Tukushi, "����")
		GENERATOR_CASE(EnemyTypeID::EnemyID_DaiodoRed, "�ԃ_�C�I�[�h")
		GENERATOR_CASE(EnemyTypeID::EnemyID_DaiodoGreen, "�_�C�I�[�h")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Magaret, "�}�[�K���b�g")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Nekojarashi, "�˂�����炵")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Chiyogami, "��㎆")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Zenmai, "����܂�")
		GENERATOR_CASE(EnemyTypeID::EnemyID_KingChappy, "�L���O�`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Miulin, "�~�E����")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Hanachirashi, "�t�E�Z���n�i�`���V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Damagumo, "�_�}�O��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Kurage, "�N���Q�h�b�N��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_BombSarai, "�o�N�_���T���C")
		GENERATOR_CASE(EnemyTypeID::EnemyID_FireOtakara, "�΃I�^�J�����V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_WaterOtakara, "���I�^�J�����V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_GasOtakara, "�K�X�I�^�J�����V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_ElecOtakara, "�d�C�I�^�J�����V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_BombOtakara, "���e�I�^�J�����V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Jigumo, "�W�O��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_JigumoNest, "�W�O����")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Imomushi, "�C�����V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Houdai, "�z�E�_�C�_�}�O��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_LeafChappy, "�n�b�p�`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_TamagoMushi, "�^�}�S���V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_BigFoot, "�I�I�A�V�_�}�O��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_SnakeWhole, "�w�r�K���X�S�g")
		GENERATOR_CASE(EnemyTypeID::EnemyID_UmiMushi, "�E�~���V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_UmiMushiBlind, "�ڂȂ��E�~���V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_OniKurage, "�I�j�N���Q")
		GENERATOR_CASE(EnemyTypeID::EnemyID_BigTreasure, "�I�I�I�^�J�����V")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Kabuto, "�O���[���J�u�g�c��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Rkabuto, "���b�h�J�u�g�c��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Fkabuto, "�Œ�J�u�g�c��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_KumaKochappy, "�N�}�R�`���b�s�[")
		GENERATOR_CASE(EnemyTypeID::EnemyID_ShijimiChou, "�V�W�~��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_MiniHoudai, "�`�r�z�E�_�C")
		GENERATOR_CASE(EnemyTypeID::EnemyID_FminiHoudai, "�Œ�`�r�z�E�_�C")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Sokkuri, "�\\�b�N��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Hana, "�n�i�h�b�N��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_BlackMan, "�����l")
		GENERATOR_CASE(EnemyTypeID::EnemyID_Tyre, "�����l�^�C��")
		GENERATOR_CASE(EnemyTypeID::EnemyID_DangoMushi, "�_���S���V")

	case EnemyTypeID::EnemyID_Pom:
	case EnemyTypeID::EnemyID_PanHouse:
	case EnemyTypeID::EnemyID_UmiMushiBase:
	case EnemyTypeID::EnemyID_Stone:
	default:
		mEnemyGenerator = new EnemyGeneratorBase("���o�^");
		break;
	}

	return mEnemyGenerator;
}

/**
 * @note Address: 0x801267D0
 * @note Size: 0x2C
 */
J3DModelData* GenObjectEnemy::getShape() { return generalEnemyMgr->getJ3DModelData((int)mEnemyID); }

/**
 * @note Address: 0x801267FC
 * @note Size: 0x40
 */
void GenObjectEnemy::updateUseList(Game::Generator* gen, int listIdx)
{
	if (generalEnemyMgr) {
		generalEnemyMgr->addEnemyNum((int)mEnemyID, (u8)mTekiNum, this);
	}
}

/**
 * @note Address: 0x8012683C
 * @note Size: 0x31C
 * TODO
 */
void GenObjectEnemy::render(Graphics& gfx, Game::Generator* gen)
{
	if (mFlagBit.isSet(1)) {
		Vector3f position = gen->mPosition + gen->mOffset;

		gfx.initPrimDraw(nullptr);
		GXSetLineWidth(18, GX_TO_ZERO);

		gfx.mDrawColor = Color4(115, 16, 16, 255);

		f32 dirRadians = mDirection * DEG2RAD * PI;
		Vector3f rotation(0.0f, dirRadians, 0.0f);

		Matrixf rotationMtx;
		rotationMtx.makeTR(position, rotation);

		gfx.mCurrentViewport->getMatrix(false);

		Matrixf* gfxMatrix = gfx.mCurrentViewport->getMatrix(false);

		Mtx finalMtx;
		PSMTXConcat(gfxMatrix->mMatrix.mtxView, rotationMtx.mMatrix.mtxView, finalMtx);
		GXLoadPosMtxImm(finalMtx, 0);

		Vector3f pos1(0.0f, 100.0f, 0.0f);
		Vector3f pos2(0.0f, 100.0f, 50.0f);
		gfx.drawLine(pos1, pos2);

		pos1 = Vector3f(10.0f, 100.0f, 40.0f);
		gfx.drawLine(pos1, pos2);

		pos1 = Vector3f(-10.0f, 100.0f, 40.0f);
		gfx.drawLine(pos1, pos2);

		GXSetLineWidth(6, GX_TO_ZERO);

		rotationMtx.makeT(position);

		if (mSpawnType == 2) { // Circle spawn type
			gfx.mDrawColor = Color4(255, 255, 255, 155);
			gfx.drawSphere(mAppearRadius, &rotationMtx);
		}

		PerspPrintfInfo info;
		info.mScale = 0.5f;

		gfx.initPrimDraw(nullptr);

		info.mColorA = Color4(50, 100, 255, 255);
		info.mColorB = Color4(50, 50, 150, 255);

		gfx.initPerspPrintf(gfx.getViewport(0));

		Vector3f perspPos = gen->mPosition + gen->mOffset;
		perspPos.y += 100.0f;

		gfx.perspPrintf(info, perspPos, "%s x %d", gEnemyInfo[mEnemyID].mName, mTekiNum);

		if (mEnemyGenerator) {
			mEnemyGenerator->draw(gfx, gen);
		}
	}
}

} // namespace Game
