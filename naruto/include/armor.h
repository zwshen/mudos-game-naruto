// armor.h

#ifndef __ARMOR_H__
#define __ARMOR_H__

/*
      繷 繷场(F_HEAD_EQ)  羪场(F_MASK_EQ)    繴场(F_NECK_EQ)    => ㄣ, 碪, 兜铃
    ō砰 ︾狝(F_CLOTH)    馴ヒ(F_CLOTH)      竬场(F_WAIST_EQ)   => 馴ヒ, ︾狝, 竬盿
      も も磝(F_HAND_EQ)  も(F_FINGER_EQ)  も得(F_WRIST_EQ)   => も甅, з, 臔得
      竲 壳(F_PANTS)    竲磝(F_FEET_EQ)    籐(F_LEG_EQ)     => 壳, 綾, 竕籐
 */
#define F_HEAD_EQ   "/feature/armor/head_eq.c"
#define F_FACE_EQ   "/feature/armor/face_eq.c"
#define F_NECK_EQ   "/feature/armor/neck_eq.c"

#define F_CLOTH     "/feature/armor/cloth.c"
#define F_ARMOR     "/feature/armor/armor.c"
#define F_WAIST_EQ  "/feature/armor/waist_eq.c"

#define F_HAND_EQ   "/feature/armor/hand_eq.c"
#define F_FINGER_EQ "/feature/armor/finger_eq.c"
#define F_WRIST_EQ  "/feature/armor/wrist_eq.c"

#define F_PANTS     "/feature/armor/pants.c"
#define F_FEET_EQ   "/feature/armor/feet_eq.c"
#define F_LEG_EQ    "/feature/armor/leg_eq.c"
	
#ifndef __WEAPON_H__
//inherit COMBINED_ITEM;
inherit ITEM;
inherit F_ATTRIBUTE;
inherit F_EQUIP;
inherit F_STATISTIC;
#endif

#endif
