#pragma once
#include "stdafx.h"
#include "Include.h"
#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "AbstractFactory.h"

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

private:
	HDC		m_hDC;

	TCHAR		m_szFPS[64];	// 멀티 바이트 기반에서는 CHAR로 유니 코드 기반에서는 유니코드로 처리해주는 매크로
	int			m_iFPS;
	DWORD		m_dwTime;

	TCHAR       m_szScore[64];
	int         m_iScore;

	CObj* m_pPlayer;
	std::list<CObj*> m_Monsterlist;
	std::list<CObj*> m_pBulletList; // 총알 리스트
};