#pragma once
#include "stdafx.h"
#include "Include.h"
#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "Shield.h"
#include "RollBot.h"
#include "AbstractFactory.h"
#include "ItemFactory.h"
#include "Collision.h"

class CMaingame
{
public:
	CMaingame();
	~CMaingame();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(void);
	void Release(void);

public:
	void Get_MONPOINT(void);


private:
	HDC		m_hDC;

	TCHAR		m_szFPS[64];	// 멀티 바이트 기반에서는 CHAR로 유니 코드 기반에서는 유니코드로 처리해주는 매크로
	int			m_iFPS;
	DWORD		m_dwTime;

	TCHAR       m_szScore[64];
	int         m_iScore;

	TCHAR		m_szLife[64];
	int			m_iLife; // 플레이어 목숨
	DWORD		m_dwPlayer; // 플레이어 무적 시간 부여를 위한 멤버
	bool		m_bCheak; // 플레이어 무적 시간 부여를 위한 멤버

	CObj* m_pPlayer;
	std::list<CObj*> m_Objlist[OBJ_END];
	std::vector<POINT>  m_tMonsterPoint;
};