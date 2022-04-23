#include "stdafx.h"
#include "Maingame.h"
#include "Collision.h"

CMaingame::CMaingame()
	: m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	ZeroMemory(m_szScore, sizeof(TCHAR) * 64);

	m_iFPS = 0;
}

CMaingame::~CMaingame()
{
	Release();
}

void CMaingame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	m_Objlist[OBJ_PLAYER].push_back(new CPlayer);
	m_Objlist[OBJ_PLAYER].front()->Initialize();
	static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Set_BulletList(&m_Objlist[OBJ_BULLET]);

	m_tMonsterPoint.push_back({ WINCX - GAMESIZE - 15, 65 });
	m_tMonsterPoint.push_back({ 735, 95 });
	m_tMonsterPoint.push_back({ 735, 505 });
	m_tMonsterPoint.push_back({ 735, 535 });
}

void CMaingame::Update(void)
{
	//m_pPlayer->Update();

	if (m_Objlist[OBJ_MONSTER].size() < 4)
	{
		if (m_dwTime + 1000 < GetTickCount())
		{
			for (int i = 0; i < 4; ++i)
			{
				m_Objlist[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(m_tMonsterPoint[i], m_Objlist[OBJ_PLAYER].front()));
			}
		}
	}

	for (auto& list_iter : m_Objlist)
	{
		for (auto iter = list_iter.begin(); iter != list_iter.end();)
		{
			if (0 >= (*iter)->Get_HP())
			{
				Safe_Delete<CObj*>(*iter);
				iter = list_iter.erase(iter);
			}

			else
			{
				(*iter)->Update();
				++iter;
			}
		}
	}

	//for (std::list<CObj*>::iterator iter = m_Monsterlist.begin();
	//	iter != m_Monsterlist.end();++iter)
	//{
	//	dynamic_cast<CMonster*>(*iter)->Set_Player(m_pPlayer);
	//	(*iter)->Update();
	//}

	//// ÃÑ¾Ë
	//for (std::list<CObj*>::iterator iter = m_BulletList.begin();
	//	iter != m_BulletList.end();++iter)
	//{
	//	(*iter)->Update();
	//}

}

void CMaingame::Late_Update(void)
{

	//m_pPlayer->Late_Update();

	//CCollision::Collision_Rect(m_Objlist[OBJ_MONSTER], m_Objlist[OBJ_BULLET]);
	CCollision::Collision_Circle(m_Objlist[OBJ_MONSTER], m_Objlist[OBJ_BULLET]);

	for (auto& list_iter : m_Objlist)
	{
		for (auto& iter : list_iter)
		{
			iter->Late_Update();
		}
	}

	//// ÃÑ¾Ë
	//for (std::list<CObj*>::iterator iter = m_BulletList.begin();
	//	iter != m_BulletList.end();++iter)
	//{
	//	(*iter)->Late_Update();
	//}
}

void CMaingame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, GAMESIZE, GAMESIZE, WINCX - GAMESIZE, WINCY - GAMESIZE);
	swprintf_s(m_szScore, L"Score : %d", m_iScore);
	TextOutW(m_hDC, 25, 25, m_szScore, lstrlen(m_szScore));

	//m_pPlayer->Render(m_hDC);

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())   // GetTickCount() 1000ºÐÀÇ 1ÃÊ
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	for (auto& list_iter : m_Objlist)
	{
		for (auto& iter : list_iter)
		{
			iter->Render(m_hDC);
		}
	}

	////¸ó½ºÅÍ Ãâ·Â
	//for (auto& iter : m_Monsterlist)
	//{
	//	iter->Render(m_hDC);
	//}

	//// ÃÑ¾Ë
	//for (std::list<CObj*>::iterator iter = m_BulletList.begin();
	//	iter != m_BulletList.end();++iter)
	//{
	//	(*iter)->Render(m_hDC);
	//}
}
	
void CMaingame::Release(void)
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}
