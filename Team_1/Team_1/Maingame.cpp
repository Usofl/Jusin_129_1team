#include "stdafx.h"
#include "Maingame.h"
#include "Collision.h"

CMaingame::CMaingame()
	: m_dwTime(GetTickCount())
	, m_iFPS(0)
	, m_iScore(0)
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	ZeroMemory(m_szScore, sizeof(TCHAR) * 64);
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

	m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create(ITEM_BULLET,
		m_Objlist[OBJ_PLAYER].front()->Get_fX(), m_Objlist[OBJ_PLAYER].front()->Get_fY()));

	m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create(ITEM_SHIELD,
		m_Objlist[OBJ_PLAYER].front()->Get_fX(), (m_Objlist[OBJ_PLAYER].front()->Get_fY() - 100.f)));

	m_tMonsterPoint.push_back({ WINCX - GAMESIZE - 15, 65 });
	m_tMonsterPoint.push_back({ 735, 95 });
	m_tMonsterPoint.push_back({ 735, 505 });
	m_tMonsterPoint.push_back({ 735, 535 });
}

void CMaingame::Update(void)
{
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

	for (int i = OBJ_PLAYER; i < OBJ_END; ++i)
	{
		for (auto iter = m_Objlist[i].begin(); iter != m_Objlist[i].end();)
		{
			if (0 >= (*iter)->Get_HP())
			{
				if (i == OBJ_MONSTER) // 삭제되는 OBJ가 몬스터일 경우 score 증가
				{
					m_iScore += 10;
				}

				if (i == OBJ_ITEM)
				{
					static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Pick_Up_Item(*iter);
				}

				Safe_Delete<CObj*>(*iter);
				iter = list_iter.erase(iter);

				if (m_Objlist[OBJ_PLAYER].empty())
				{
					m_Objlist[OBJ_PLAYER].push_back(new CPlayer);
					m_Objlist[OBJ_PLAYER].front()->Initialize();
					static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Set_BulletList(&m_Objlist[OBJ_BULLET]);
				}
			}

			else
			{
				(*iter)->Update();
				++iter;
			}
		}
	}
}

void CMaingame::Late_Update(void)
{
	CCollision::Collision_Circle(m_Objlist[OBJ_MONSTER], m_Objlist[OBJ_BULLET]);
	CCollision::Collision_Circle(m_Objlist[OBJ_PLAYER], m_Objlist[OBJ_ITEM]);
	CCollision::Collision_Player(m_Objlist[OBJ_MONSTER], m_Objlist[OBJ_PLAYER]);

	for (auto& list_iter : m_Objlist)
	{
		for (auto& iter : list_iter)
		{
			iter->Late_Update();
		}
	}
}

void CMaingame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, GAMESIZE, GAMESIZE, WINCX - GAMESIZE, WINCY - GAMESIZE);
	swprintf_s(m_szScore, L"Score : %d", m_iScore);
	TextOutW(m_hDC, GAMESIZE, OUTGAMESIZE, m_szScore, lstrlen(m_szScore));

	for (auto& list_iter : m_Objlist)
	{
		for (auto& iter : list_iter)
		{
			iter->Render(m_hDC);
		}
	}

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())   // GetTickCount() 1000분의 1초
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}
	
void CMaingame::Release(void)
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}
