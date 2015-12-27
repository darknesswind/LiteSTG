#include "DxLib.h"

/*#include "baseFrame.h"
#include "Fps.h"*/

#define GAMESTATE_TITLE 0
#define GAMESTATE_START 1
#define GAMESTATE_PAUSE 2

#pragma region Menu_Select_Define
#define MENU_SELECT_NUM 9
#define MENU_GAME_START 0
#define MENU_EXTRA_START 1
#define MENU_PRACTICE_START 2
#define MENU_SPELL_PRACTICE 3
#define MENU_REPLAY	4
#define MENU_PLAYER_DATA	5
#define MENU_MUSIC_ROOM	6
#define MENU_OPTION	7
#define MENU_QUIT	8
#pragma endregion Menu_Select_Define

extern bool isStateChange;
extern int gameState;
extern int menuSelect;
extern int timeCount;
