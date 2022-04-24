#pragma once
#include "stdafx.h"
#include "Include.h"
#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "Shield.h"
#include "RollBot.h"
#include "Ultimate.h"
#include "AbstractFactory.h"
#include "ItemFactory.h"
#include "MonsterFactory.h"
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
	void Key_Input(void);
	void Get_MONPOINT(void);
	void Create_Item(const float& _fA, const float& _fB);


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

	/*CObj* m_pPlayer;
	CObj* m_pUlt;*/
	std::list<CObj*> m_Objlist[OBJ_END];
	std::vector<POINT>  m_tMonsterPoint;
};