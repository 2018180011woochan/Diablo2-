#pragma once

#ifndef __ENUM_H__
#define __ENUM_H__

enum OBJID { OBJ_STARTTILE, OBJ_STARTMAPOBJ, OBJ_TERRAIN, OBJ_POTAL, OBJ_WRAITH, OBJ_SK, OBJ_SK2, OBJ_DEMON, OBJ_MONSTER, OBJ_PLAYER, OBJ_PLAYERSK, OBJ_PLAYERSK2, OBJ_BLOODGOLEM, OBJ_FIREGOLEM, OBJ_STONEGOLEM, OBJ_MAPOBJECT, OBJ_EFFECT, OBJ_BONESPEAR, OBJ_POISONNOVA, OBJ_MONSTERATTACK, OBJ_SUMMONSK2ATTACK, OBJ_SUMMONATTACK, OBJ_POISONEXPLOSION, OBJ_CORPSEEXPLODEGUTS, OBJ_SK2ATTACK, OBJ_DIABLOATTACK, OBJ_HARRYCAIN, OBJ_DIABLO, OBJ_UI, OBJ_END };

enum SCENEID { SCENE_LOADING, SCENE_MENU, SCENE_STARTMAP, SCENE_STAGE, SCENE_END };

enum OBJDIR {OBJ_LEFT, OBJ_LEFT_TOP, OBJ_TOP, OBJ_RIGHT_TOP, OBJ_RIGHT, OBJ_RIGHT_BOTTOM, OBJ_BOTTOM, OBJ_LEFT_BOTTOM, OBJDIR_END};

enum OBJSTATE {OBJ_ATTACK, OBJ_HIT, OBJ_DASH, OBJ_SKILLATTACK, OBJ_STAND, OBJ_WALK, OBJ_DEATH, OBJ_BURROW, OBJ_CREATE, OBJ_FIRESPREAD, OBJ_BREATH, OBJ_GROUNDFIRE, OBJSTATE_END};

enum NECROMANCERSKILL {SKILL_BONESHILED, SKILL_TEETH, SKILL_POISONNOVA, SKILL_POISONEXPLOSION, SKILL_BONESPEAR, SKILL_BONESPIRIT, SKILL_CORPSEEXPLODEGUTS, SKILL_RAISESKELETON, SKILL_CLAYGOLEM, SKILL_RAISESKELETONMAGE, SKILL_BLOODGOLEM, SKILL_FIREGOLEM, SKILL_END};

enum DIABLOMONSTER { DIABLOMONSTER_WRAITH, DIABLOMONSTER_SK2, DIABLOMONSTER_SK, DIABLOMONSTER_DIABLO, DIABLOMONSTER_DEMON, DIABLOMONSTER_END};

enum SCROLL { SCROLL_X, SCROLL_Y };

#endif // !__ENUM_H__