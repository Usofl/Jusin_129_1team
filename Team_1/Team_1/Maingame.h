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

	TCHAR		m_szFPS[64];	// ��Ƽ ����Ʈ ��ݿ����� CHAR�� ���� �ڵ� ��ݿ����� �����ڵ�� ó�����ִ� ��ũ��
	int			m_iFPS;
	DWORD		m_dwTime;

	TCHAR       m_szScore[64];
	int         m_iScore;

	TCHAR		m_szLife[64];
	int			m_iLife; // �÷��̾� ���
	DWORD		m_dwPlayer; // �÷��̾� ���� �ð� �ο��� ���� ���
	bool		m_bCheak; // �÷��̾� ���� �ð� �ο��� ���� ���

	CObj* m_pPlayer;
	std::list<CObj*> m_Objlist[OBJ_END];
	std::vector<POINT>  m_tMonsterPoint;
};