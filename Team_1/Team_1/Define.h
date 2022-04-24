#pragma once

#define WINCX 800
#define WINCY 600


#define ULT_START_X 75.f
#define ULT_START_Y 300.f
#define ULTCX 50.f
#define ULTCY 500.f

#define OUTGAMESIZE 25
#define GAMESIZE 50

#define PLAYER_START_X 200.f
#define PLAYER_START_Y 300.f
#define PLAYERCX 50.f
#define PLAYERCY 50.f

#define SHILED_INTERVAL 45.f

#define PURE =0

#define PI 3.1415926535f
#define DEGREE (PI / 180.f)
#define nLog sqrtf(2.f)

extern HWND g_hWnd;

#define Monster_C 30.f

#define Diagonal(x,y) sqrtf((x * x) + (y * y))

#define acos(x,y) acos(x / sqrtf((x * x) + (y * y)))
#define asin(x,y) asin(y / sqrtf((x * x) + (y * y)))