#ifndef _JSYSTEM_J2D_J2DPANE_H
#define _JSYSTEM_J2D_J2DPANE_H

#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "JSystem/JGeometry.h"
#include "JSystem/JSupport/JSUTree.h"
#include "JSystem/JUtility.h"

struct J2DAnmBase;
struct J2DAnmColor;
struct J2DAnmTevRegKey;
struct J2DAnmTexPattern;
struct J2DAnmTextureSRTKey;
struct J2DAnmTransform;
struct J2DAnmVisibilityFull;
struct J2DAnmVtxColor;
struct J2DGrafContext;
struct J2DMaterial;
struct JKRArchive;
struct JSURandomInputStream;
struct JUTFont;
struct JUTNameTab;
struct JUTPalette;
struct JUTResFont;
struct JUTTexture;
struct ResFONT;
struct ResTIMG;
struct ResTLUT;
struct TMaterial;

typedef u32 J2DRotateAxis;

// Intended to be size 0x1.
enum J2DBasePosition {
	POS_TOP_LEFT = 0,
	POS_TOP_CENTER,
	POS_TOP_RIGHT,
	POS_CENTER_LEFT,
	POS_CENTER,
	POS_CENTER_RIGHT,
	POS_BOTTOM_LEFT,
	POS_BOTTOM_CENTER,
	POS_BOTTOM_RIGHT
};

struct J2DScrnBlockHeader {
	u32 m_bloBlockType;
	int m_blockLength;
};

// Size: 0x100
struct J2DPane {
	J2DPane();
	J2DPane(J2DPane*, bool, u64, const JGeometry::TBox2f&);
	J2DPane(u64, const JGeometry::TBox2f&);
	J2DPane(J2DPane*, JSURandomInputStream*, u8);

	virtual ~J2DPane();                                                  // _08
	virtual u32 getTypeID() const;                                       // _0C (weak)
	virtual void move(float, float);                                     // _10
	virtual void add(float, float);                                      // _14
	virtual void resize(float, float);                                   // _18
	virtual void setCullBack(bool);                                      // _1C (weak)
	virtual void setCullBack(GXCullMode);                                // _20
	virtual void setAlpha(u8);                                           // _24 (weak)
	virtual bool setConnectParent(bool);                                 // _28 (weak)
	virtual void calcMtx();                                              // _2C (weak)
	virtual void update();                                               // _30 (weak)
	virtual void drawSelf(float, float);                                 // _34 (weak)
	virtual void drawSelf(float, float, float (*)[3][4]);                // _38 (weak)
	virtual J2DPane* search(u64);                                        // _3C
	virtual J2DPane* searchUserInfo(u64);                                // _40
	virtual void makeMatrix(float, float);                               // _44 (weak)
	virtual void makeMatrix(float, float, float, float);                 // _48
	virtual bool isUsed(const ResTIMG*);                                 // _4C
	virtual bool isUsed(const ResFONT*);                                 // _50
	virtual void clearAnmTransform();                                    // _54
	virtual void rewriteAlpha();                                         // _58 (weak)
	virtual void setAnimation(J2DAnmBase*);                              // _5C
	virtual void setAnimation(J2DAnmTransform*);                         // _60
	virtual void setAnimation(J2DAnmColor*);                             // _64 (weak)
	virtual void setAnimation(J2DAnmTexPattern*);                        // _68 (weak)
	virtual void setAnimation(J2DAnmTextureSRTKey*);                     // _6C (weak)
	virtual void setAnimation(J2DAnmTevRegKey*);                         // _70 (weak)
	virtual void setAnimation(J2DAnmVisibilityFull*);                    // _74 (weak)
	virtual void setAnimation(J2DAnmVtxColor*);                          // _78 (weak)
	virtual J2DAnmTransform* animationTransform(const J2DAnmTransform*); // _7C
	virtual void setVisibileAnimation(J2DAnmVisibilityFull*);            // _80
	virtual void setAnimationVF(J2DAnmVisibilityFull*);                  // _84 (weak)
	virtual void setVtxColorAnimation(J2DAnmVtxColor*);                  // _88
	virtual void setAnimationVC(J2DAnmVtxColor*);                        // _8C (weak)
	virtual void animationPane(const J2DAnmTransform*);                  // _90
	// virtual void _8C() = 0;                                           // _94
	// /* This is just (automatic?) padding. */

	void animationTransform();
	void changeUseTrans(J2DPane*);
	void clip(const JGeometry::TBox2f&);
	void draw(float, float, const J2DGrafContext*, bool, bool);
	void gather(J2DPane**, u64, u64, int, int&);

	JGeometry::TBox2f* getBounds();
	JGeometry::TVec3f getGlbVtx(u8) const;
	void* getPointer(JSURandomInputStream*, u32, JKRArchive*);
	u64 getTagName() const { return m_tag; }
	float getTranslateX() const;
	float getTranslateY() const;

	/**
	 * @reifiedAddress{80309D98}
	 * @reifiedFile{plugProjectOgawaU/ogCallBackMessage.cpp}
	 */
	u64 getUserInfo() const { return m_messageID; }

	J2DPane* getFirstChildPane();
	J2DPane* getNextChildPane();
	J2DPane* getParentPane();
	JSUTree<J2DPane>* getPaneTree() { return &m_tree; }

	void initiate();
	void initialize(J2DPane*, bool, u64, const JGeometry::TBox2f&);
	void initialize(u64, const JGeometry::TBox2f&);
	void makePaneStream(J2DPane*, JSURandomInputStream*);
	void makePaneExStream(J2DPane*, JSURandomInputStream*);
	void place(const JGeometry::TBox2f&);
	void rotate(float, float, J2DRotateAxis, float);
	void rotate(float);
	void updateTransform(const J2DAnmTransform*);

	/**
	 * @reifiedAddress{80309A74}
	 * @reifiedFile{plugProjectOgawaU/ogCallBackMessage.cpp}
	 */
	bool isVisible() const { return m_isVisible; }

	/**
	 * @reifiedAddress{803CA760}
	 * @reifiedFile{plugProjectEbisawaU/ebi2DGraph.cpp}
	 */
	inline void show() { m_isVisible = true; }

	/**
	 * @reifiedAddress{803CA910}
	 * @reifiedFile{plugProjectEbisawaU/ebi2DGraph.cpp}
	 */
	inline void hide() { m_isVisible = false; };

	void setBasePosition(J2DBasePosition);
	void setInfluencedAlpha(bool, bool);

	/**
	 * @fabricated
	 */
	void centerWithScale(float width, float height)
	{
		setBasePosition(POS_CENTER);
		m_scale.x = width;
		m_scale.y = height;
		calcMtx();
	}

	// /**
	//  * @fabricated
	//  */
	// void setScale(float width, float height) {
	// 	m_scale.x = width;
	// 	m_scale.y = height;
	// }

	u32 appendChild(J2DPane*);
	u32 prependChild(J2DPane*);
	u32 removeChild(J2DPane*);

	s16 J2DCast_F32_to_S16(f32, u8);

	// Unused/inlined:
	void insertChild(J2DPane*, J2DPane*);
	float getRotate() const;
	void gatherUserInfo(J2DPane**, u64, u64, int, int&);

	// _00 VTBL
	short _004;                      // _004
	short _006;                      // _006
	u32 m_bloBlockType;              // _008
	u8 _00C[4];                      // _00C
	u64 m_tag;                       // _010
	u64 m_messageID;                 // _018
	JGeometry::TBox2f _020;          // _020
	float _030;                      // _030
	float _034;                      // _034
	float _038;                      // _038
	float _03C;                      // _03C
	float _040;                      // _040
	float _044;                      // _044
	float _048;                      // _048
	float _04C;                      // _04C
	Mtx _050;                        // _050
	Mtx _080;                        // _080
	bool m_isVisible;                // _0B0
	u8 m_cullMode;                   // _0B1
	u8 m_alpha;                      // _0B2
	u8 _0B3;                         // _0B3
	bool _0B4;                       // _0B4
	u8 _0B5;                         // _0B5
	u8 m_rotationAxisMaybe;          // _0B6
	u8 m_basePosition;               // _0B7
	float _0B8;                      // _0B8
	float _0BC;                      // _0BC
	float _0C0;                      // _0C0
	JGeometry::TVec2f m_anchorPoint; // _0C4
	JGeometry::TVec2f m_scale;       // _0CC
	JGeometry::TVec2f _0D4;          // _0D4 /* offset X,Y? */
	JSUTree<J2DPane> m_tree;         // _0DC
	J2DAnmTransform* m_transform;    // _0F8
	u8 _0FC[4];                      // _0FC

	static JGeometry::TBox2f static_mBounds;
};

struct J2DScreen : public J2DPane {
	J2DScreen();

	virtual ~J2DScreen();                                                                                  // _00
	virtual void calcMtx();                                                                                // _24
	virtual void drawSelf(float, float, float (*)[3][4]);                                                  // _30
	virtual J2DPane* search(u64);                                                                          // _34
	virtual J2DPane* searchUserInfo(u64);                                                                  // _38
	virtual bool isUsed(const ResTIMG*);                                                                   // _44
	virtual bool isUsed(const ResFONT*);                                                                   // _48
	virtual void clearAnmTransform();                                                                      // _4C
	virtual void setAnimation(J2DAnmBase*);                                                                // _54
	virtual void setAnimation(J2DAnmTransform*);                                                           // _58
	virtual void setAnimation(J2DAnmColor*);                                                               // _5C
	virtual void setAnimation(J2DAnmTexPattern*);                                                          // _60
	virtual void setAnimation(J2DAnmTextureSRTKey*);                                                       // _64
	virtual void setAnimation(J2DAnmTevRegKey*);                                                           // _68
	virtual void setAnimation(J2DAnmVisibilityFull*);                                                      // _6C
	virtual void setAnimation(J2DAnmVtxColor*);                                                            // _70
	virtual void setAnimationVF(J2DAnmVisibilityFull*);                                                    // _7C
	virtual void setAnimationVC(J2DAnmVtxColor*);                                                          // _84
	virtual void createPane(const J2DScrnBlockHeader&, JSURandomInputStream*, J2DPane*, u32);              // _8C
	virtual void createPane(const J2DScrnBlockHeader&, JSURandomInputStream*, J2DPane*, u32, JKRArchive*); // _90
	// virtual void _94() = 0;                                // _94

	void animation();
	bool checkSignature(JSURandomInputStream*);
	void clean();
	bool createMaterial(JSURandomInputStream*, u32, JKRArchive*);
	void draw(float, float, const J2DGrafContext*);
	u32 gather(J2DPane**, u64, u64, int);
	J2DMaterial* getMaterial(u16);
	void* getResReference(JSURandomInputStream*, u32);
	bool getScreenInformation(JSURandomInputStream*);
	u32 makeHierarchyPanes(J2DPane*, JSURandomInputStream*, u32, JKRArchive*);
	bool set(const char*, u32, JKRArchive*);
	bool set(JSURandomInputStream*, u32);
	bool private_set(JSURandomInputStream*, u32, JKRArchive*);

	static void* getNameResource(const char*);

	// J2DPane _000
	bool _100;                // _100
	u16 m_materialCount;      // _102
	J2DMaterial* m_materials; // _104
	void* _108;               // _108
	void* _10C;               // _10C
	JUTNameTab* m_nameTab;    // _110
	int _114;                 // _114

	static void* mDataManage; // unknown type
};

// Size: 0x168
struct J2DPicture : public J2DPane {
	J2DPicture();
	J2DPicture(J2DPane*, JSURandomInputStream*, JKRArchive*);
	J2DPicture(J2DPane*, JSURandomInputStream*, J2DMaterial*);
	J2DPicture(const ResTIMG*);
	J2DPicture(const char*);
	J2DPicture(JUTTexture*);
	J2DPicture(u64, const JGeometry::TBox2f&);

	virtual ~J2DPicture();                                                                                                          // _00
	virtual u32 getTypeID() const;                                                                                                  // _04
	virtual void drawSelf(float, float);                                                                                            // _2C
	virtual void drawSelf(float, float, float (*)[3][4]);                                                                           // _30
	virtual void initiate(const ResTIMG*, const ResTLUT*);                                                                          // _8C
	virtual void prepareTexture(u8);                                                                                                // _90
	virtual bool append(const ResTIMG*, float);                                                                                     // _94
	virtual bool append(const ResTIMG*, JUTPalette*, float);                                                                        // _98
	virtual bool append(const char*, float);                                                                                        // _9C
	virtual bool append(const char*, JUTPalette*, float);                                                                           // _A0
	virtual bool append(JUTTexture*, float);                                                                                        // _A4
	virtual bool prepend(const ResTIMG*, float);                                                                                    // _A8
	virtual bool prepend(const ResTIMG*, JUTPalette*, float);                                                                       // _AC
	virtual bool prepend(const char*, float);                                                                                       // _B0
	virtual bool prepend(const char*, JUTPalette*, float);                                                                          // _B4
	virtual bool prepend(JUTTexture*, float);                                                                                       // _B8
	virtual bool insert(const ResTIMG*, u8, float);                                                                                 // _BC
	virtual bool insert(const ResTIMG*, JUTPalette*, u8, float);                                                                    // _C0
	virtual bool insert(const char*, u8, float);                                                                                    // _C4
	virtual bool insert(const char*, JUTPalette*, u8, float);                                                                       // _C8
	virtual bool insert(JUTTexture*, u8, float);                                                                                    // _CC
	virtual int remove(u8);                                                                                                         // _D0
	virtual int remove();                                                                                                           // _D4
	virtual int remove(JUTTexture*);                                                                                                // _D8
	virtual void draw(float, float, bool, bool, bool);                                                                              // _DC
	virtual void draw(float, float, u8, bool, bool, bool);                                                                          // _E0
	virtual void draw(float, float, float, float, bool, bool, bool);                                                                // _E4
	virtual void drawOut(float, float, float, float, float, float);                                                                 // _E8
	virtual void drawOut(float, float, float, float, float, float, float, float);                                                   // _EC
	virtual void drawOut(const JGeometry::TBox2f&, const JGeometry::TBox2f&);                                                       // _F0
	virtual void load(GXTexMapID, u8);                                                                                              // _F4
	virtual void load(u8);                                                                                                          // _F8
	virtual void setBlendRatio(float, float, float, float, float, float, float, float);                                             // _FC
	virtual void setBlendColorRatio(float, float, float, float, float, float, float, float);                                        // _100
	virtual void setBlendAlphaRatio(float, float, float, float, float, float, float, float);                                        // _104
	virtual ResTIMG* changeTexture(const ResTIMG*, u8);                                                                             // _108
	virtual ResTIMG* changeTexture(const char*, u8);                                                                                // _10C
	virtual ResTIMG* changeTexture(const ResTIMG*, u8, JUTPalette*);                                                                // _110
	virtual ResTIMG* changeTexture(const char*, u8, JUTPalette*);                                                                   // _114
	virtual JUTTexture* getTexture(u8) const;                                                                                       // _118
	virtual u8 getTextureCount() const;                                                                                             // _11C
	virtual bool setBlack(JUtility::TColor);                                                                                        // _120
	virtual bool setWhite(JUtility::TColor);                                                                                        // _124
	virtual bool setBlackWhite(JUtility::TColor, JUtility::TColor);                                                                 // _128
	virtual JUtility::TColor getBlack() const;                                                                                      // _12C
	virtual JUtility::TColor getWhite() const;                                                                                      // _130
	virtual J2DMaterial* getMaterial() const;                                                                                       // _134
	virtual void drawFullSet(float, float, float, float, float (*)[3][4]);                                                          // _138
	virtual void drawTexCoord(float, float, float, float, short, short, short, short, short, short, short, short, float (*)[3][4]); // _13C
	virtual u8 getUsableTlut(u8);                                                                                                   // _140
	virtual void _144() = 0;                                                                                                        // _144

	void initinfo();
	void private_readStream(J2DPane*, JSURandomInputStream*, JKRArchive*);
	void private_initiate(const ResTIMG*, const ResTLUT*);

	// J2DPane _000
	JUTTexture* m_textures[4]; // _100
	u8 m_textureCount;         // _110
	u8 _111;                   // _111
	short _112[2][4];          // _112 /* TODO: Does using TVec2<short>[4] here mess with alignment? */
	u8 _122[2];                // _122
	u32 _124[4];               // _124
	u32 _134[4];               // _134
	JUTPalette* m_palette;     // _144
	JUtility::TColor m_white;  // _148
	JUtility::TColor m_black;  // _14C
	JUtility::TColor _150[4];  // _150
	u32 _160;                  // _160
	u32 _164;                  // _164
};

// Size: 0x1A8
struct J2DPictureEx : public J2DPicture {
	J2DPictureEx();
	J2DPictureEx(const ResTIMG*, u32);
	J2DPictureEx(J2DPane*, JSURandomInputStream*, u32, JKRArchive*);
	J2DPictureEx(u64, const JGeometry::TBox2f&, const ResTIMG*, u32);
	J2DPictureEx(u64, const JGeometry::TBox2f&, const char*, u32);

	virtual ~J2DPictureEx();                                                                                                        // _00
	virtual void setCullBack(bool);                                                                                                 // _14
	virtual void setCullBack(GXCullMode);                                                                                           // _18
	virtual void setAlpha(u8);                                                                                                      // _1C
	virtual void drawSelf(float, float, float (*)[3][4]);                                                                           // _30
	virtual bool isUsed(const ResTIMG*);                                                                                            // _44
	virtual bool isUsed(const ResFONT*);                                                                                            // _48
	virtual void rewriteAlpha();                                                                                                    // _50
	virtual void setAnimation(J2DAnmBase*);                                                                                         // _54
	virtual void setAnimation(J2DAnmTransform*);                                                                                    // _58
	virtual void setAnimation(J2DAnmColor*);                                                                                        // _5C
	virtual void setAnimation(J2DAnmTexPattern*);                                                                                   // _60
	virtual void setAnimation(J2DAnmTextureSRTKey*);                                                                                // _64
	virtual void setAnimation(J2DAnmTevRegKey*);                                                                                    // _68
	virtual void setAnimation(J2DAnmVisibilityFull*);                                                                               // _6C
	virtual void setAnimation(J2DAnmVtxColor*);                                                                                     // _70
	virtual void animationPane(const J2DAnmTransform*);                                                                             // _88
	virtual void initiate(const ResTIMG*, const ResTLUT*);                                                                          // _8C
	virtual void prepareTexture(u8);                                                                                                // _90
	virtual bool append(const ResTIMG*, float);                                                                                     // _94
	virtual bool append(const ResTIMG*, JUTPalette*, float);                                                                        // _98
	virtual bool append(const char*, float);                                                                                        // _9C
	virtual bool append(const char*, JUTPalette*, float);                                                                           // _A0
	virtual bool append(JUTTexture*, float);                                                                                        // _A4
	virtual bool prepend(const ResTIMG*, float);                                                                                    // _A8
	virtual bool prepend(const ResTIMG*, JUTPalette*, float);                                                                       // _AC
	virtual bool prepend(const char*, float);                                                                                       // _B0
	virtual bool prepend(const char*, JUTPalette*, float);                                                                          // _B4
	virtual bool prepend(JUTTexture*, float);                                                                                       // _B8
	virtual bool insert(const ResTIMG*, u8, float);                                                                                 // _BC
	virtual bool insert(const ResTIMG*, JUTPalette*, u8, float);                                                                    // _C0
	virtual bool insert(const char*, u8, float);                                                                                    // _C4
	virtual bool insert(const char*, JUTPalette*, u8, float);                                                                       // _C8
	virtual bool insert(JUTTexture*, u8, float);                                                                                    // _CC
	virtual int remove(u8);                                                                                                         // _D0
	virtual int remove();                                                                                                           // _D4
	virtual int remove(JUTTexture*);                                                                                                // _D8
	virtual void draw(float, float, bool, bool, bool);                                                                              // _DC
	virtual void draw(float, float, u8, bool, bool, bool);                                                                          // _E0
	virtual void draw(float, float, float, float, bool, bool, bool);                                                                // _E4
	virtual void drawOut(float, float, float, float, float, float);                                                                 // _E8
	virtual void drawOut(float, float, float, float, float, float, float, float);                                                   // _EC
	virtual void drawOut(const JGeometry::TBox2f&, const JGeometry::TBox2f&);                                                       // _F0
	virtual void load(GXTexMapID, u8);                                                                                              // _F4
	virtual void load(u8);                                                                                                          // _F8
	virtual void setBlendColorRatio(float, float, float, float, float, float, float, float);                                        // _100
	virtual void setBlendAlphaRatio(float, float, float, float, float, float, float, float);                                        // _104
	virtual ResTIMG* changeTexture(const ResTIMG*, u8);                                                                             // _108
	virtual ResTIMG* changeTexture(const char*, u8);                                                                                // _10C
	virtual ResTIMG* changeTexture(const ResTIMG*, u8, JUTPalette*);                                                                // _110
	virtual ResTIMG* changeTexture(const char*, u8, JUTPalette*);                                                                   // _114
	virtual JUTTexture* getTexture(u8) const;                                                                                       // _118
	virtual u8 getTextureCount() const;                                                                                             // _11C
	virtual bool setBlack(JUtility::TColor);                                                                                        // _120
	virtual bool setWhite(JUtility::TColor);                                                                                        // _124
	virtual bool setBlackWhite(JUtility::TColor, JUtility::TColor);                                                                 // _128
	virtual JUtility::TColor getBlack() const;                                                                                      // _12C
	virtual JUtility::TColor getWhite() const;                                                                                      // _130
	virtual J2DMaterial* getMaterial() const;                                                                                       // _134
	virtual void drawFullSet(float, float, float, float, float (*)[3][4]);                                                          // _138
	virtual void drawTexCoord(float, float, float, float, short, short, short, short, short, short, short, short, float (*)[3][4]); // _13C
	virtual u8 getUsableTlut(u8);                                                                                                   // _140
	virtual void _144() = 0;                                                                                                        // _144

	// J2DPane _000
	J2DMaterial* _168;                     // _168
	short _16C;                            // _16C
	short _16E;                            // _16E
	short _170[2][2];                      // _170
	float _178;                            // _178
	float _17C;                            // _17C
	float _180;                            // _180
	float _184;                            // _184
	float _188;                            // _188
	float _18C;                            // _18C
	float _190;                            // _190
	float _194;                            // _194
	u8 _198;                               // _198
	J2DAnmVisibilityFull* m_anmVisibility; // _19C
	void* _1A0;                            // _1A0
	u8 _1A4;                               // _1A4
};

typedef u32 J2DTextBoxHBinding;
typedef u32 J2DTextBoxVBinding;

// Size: 0x138
struct J2DTextBox : public J2DPane {
	J2DTextBox();
	J2DTextBox(J2DPane*, JSURandomInputStream*, JKRArchive*);
	J2DTextBox(J2DPane*, JSURandomInputStream*, unsigned long, J2DMaterial*);
	J2DTextBox(unsigned long long, const JGeometry::TBox2f&, const ResFONT*, const char*, short, J2DTextBoxHBinding, J2DTextBoxVBinding);
	virtual void draw(float, float);                                // _8C
	virtual void draw(float, float, float, J2DTextBoxHBinding);     // _90
	virtual void setFont(JUTFont*);                                 // _94
	virtual JUTResFont* getFont() const;                            // _98
	virtual bool setBlack(JUtility::TColor);                        // _9C
	virtual bool setWhite(JUtility::TColor);                        // _A0
	virtual bool setBlackWhite(JUtility::TColor, JUtility::TColor); // _A4
	virtual JUtility::TColor getBlack() const;                      // _A8
	virtual JUtility::TColor getWhite() const;                      // _AC
	virtual J2DMaterial* getMaterial() const;                       // _B0
	virtual void _B4() = 0;                                         // _B4

	// J2DPane _000
	JUTResFont* m_font;       // _100
	JUtility::TColor _104;    // _104
	JUtility::TColor _108;    // _108
	float _10C;               // _10C
	float _110;               // _110
	float _114;               // _114
	float _118;               // _118
	float _11C;               // _11C
	float _120;               // _120
	char* _124;               // _124
	JUtility::TColor m_white; // _128
	JUtility::TColor m_black; // _12C
	u8 _130;                  // _130
	u8 _131;                  // _131
	short _132;               // _132
	u8 _134[4];               // _134
};

// Size: 0x148
struct J2DTextBoxEx : public J2DTextBox {

	// J2DTextBox _000
	J2DMaterial* _138;                     // _138
	u16 _13C;                              // _13C
	u16 _13E;                              // _13E
	u8 _140[4];                            // _140
	J2DAnmVisibilityFull* m_anmVisibility; // _144
};

// Size: 0x148
struct J2DWindow : public J2DPane {
	virtual void draw(const JGeometry::TBox2f&);                           // _8C
	virtual void draw(const JGeometry::TBox2f&, const JGeometry::TBox2f&); // _90
	virtual void draw(float, float, float, float);                         // _94
	virtual bool setBlack(JUtility::TColor);                               // _98
	virtual bool setWhite(JUtility::TColor);                               // _9C
	virtual bool setBlackWhite(JUtility::TColor, JUtility::TColor);        // _A0
	virtual JUtility::TColor getBlack() const;                             // _A4
	virtual JUtility::TColor getWhite() const;                             // _A8
	virtual JUTTexture* getFrameTexture(u8, u8) const;                     // _AC
	virtual JUTTexture* getContentsTexture(u8) const;                      // _B0
	virtual void getMaterial(TMaterial&) const;                            // _B4
	virtual J2DMaterial* getFrameMaterial(u8) const;                       // _B8
	virtual J2DMaterial* getContentsMaterial() const;                      // _BC
	virtual void drawContents(const JGeometry::TBox2f&);                   // _C0
	virtual void _C4() = 0;                                                // _C4

	// J2DPane _000
	JUTTexture* _100;              // _100
	JUTTexture* _104;              // _104
	JUTTexture* _108;              // _108
	JUTTexture* _10C;              // _10C
	JUTTexture* m_contentsTexture; // _110
	JGeometry::TBox2f _114;        // _114
	JUTPalette* m_palette;         // _124
	u8 _128[0x10];                 // _128
	JUtility::TColor m_white;      // _138
	JUtility::TColor m_black;      // _13C
	u16 _140;                      // _140
	u16 _142;                      // _142
	u8 _144;                       // _144
	u8 _145;                       // _145
};

// Size: 0x180
struct J2DWindowEx : public J2DWindow {

	// J2DWindow _000
	J2DMaterial* _148[2];                  // _148
	J2DMaterial* _150;                     // _150
	J2DMaterial* _154;                     // _154
	u16 _158[2];                           // _158
	u8 _15C[4];                            // _15C
	J2DMaterial* m_contentsMaterial;       // _160
	u16 _164;                              // _164
	u16 _166;                              // _166
	u8 _168[8];                            // _168
	u8 _170;                               // _170
	J2DAnmVisibilityFull* m_anmVisibility; // _174
	J2DAnmVtxColor* m_anmVtxColor;         // _178
	u8 _17C;                               // _17C
};

#endif
