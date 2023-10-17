#include "string.h"
#include "JSystem/JParticle/JPABlock.h"
#include "JSystem/JParticle/JPAResource.h"
#include "JSystem/JUtility/JUTTexture.h"
#include "JSystem/ResTIMG.h"

/*
 * --INFO--
 * Address:	........
 * Size:	000074
 */
JPAResourceManager::JPAResourceManager(u16, u16, JKRHeap*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800984D0
 * Size:	000058
 */
JPAResourceManager::JPAResourceManager(const void* p1, JKRHeap* heap)
    : mResources(nullptr)
    , mTextures(nullptr)
    , mResourceSlotCount(0)
    , mResourceCount(0)
    , mTextureSlotCount(0)
    , mTextureCount(0)
{
	mHeap = heap;
	JPAResourceLoader loader((const u8*)p1, this); // needs to not have dtor?

	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	li       r0, 0
	stw      r31, 0x1c(r1)
	mr       r31, r3
	stw      r0, 4(r3)
	addi     r3, r1, 8
	stw      r0, 8(r31)
	sth      r0, 0xc(r31)
	sth      r0, 0xe(r31)
	sth      r0, 0x10(r31)
	sth      r0, 0x12(r31)
	stw      r5, 0(r31)
	mr       r5, r31
	bl       __ct__17JPAResourceLoaderFPCUcP18JPAResourceManager
	lwz      r0, 0x24(r1)
	mr       r3, r31
	lwz      r31, 0x1c(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	00004C
 */
void JPAResourceManager::load(const char*, u16)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void JPAResourceManager::load(const void*, u16)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
JPAResourceLoader::~JPAResourceLoader()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80098528
 * Size:	000040
 */
JPAResource* JPAResourceManager::getResource(u16 p1) const
{
	for (u16 i = 0; i < mResourceCount; i++) {
		JPAResource* resource = mResources[i];
		if (p1 == resource->mUsrIdx) {
			return resource;
		}
	}
	return nullptr;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000040
 */
void JPAResourceManager::checkUserIndexDuplication(u16) const
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80098568
 * Size:	00009C
 */
const ResTIMG* JPAResourceManager::swapTexture(const ResTIMG* img, const char* swapName)
{
	const ResTIMG* ret = nullptr;

	for (s32 i = 0; i < mTextureCount; i++) {
		if (strcmp(swapName, mTextures[i]->getName()) == 0) {
			JUTTexture* tex = mTextures[i]->getJUTTexture();
			ret             = tex->getTexInfo();
			tex->storeTIMG(img, (u8)0);
			break;
		}
	}
	return ret;
}

/*
 * --INFO--
 * Address:	80098604
 * Size:	000020
 */
void JPAResourceManager::registRes(JPAResource* resource)
{
	mResources[mResourceCount] = resource;
	mResourceCount++;
}

/*
 * --INFO--
 * Address:	80098624
 * Size:	000020
 */
void JPAResourceManager::registTex(JPATexture* texture)
{
	mTextures[mTextureCount] = texture;
	mTextureCount++;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000C0
 */
void JPAResourceManager::registTexDupCheck(const u8*, JKRHeap*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80098644
 * Size:	00005C
 */
u32 JPAResourceManager::getResUserWork(u16 usrIdx) const
{
	u32 ret = 0;

	JPAResource* res = getResource(usrIdx);
	if (res != nullptr)
		ret = res->getDyn()->getResUserWork();

	return ret;
}
