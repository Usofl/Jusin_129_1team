#include "stdafx.h"
#include "Maingame.h"

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
	m_iLife = 3;

	m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create(ITEM_BULLET,
		m_Objlist[OBJ_PLAYER].front()->Get_fX(), m_Objlist[OBJ_PLAYER].front()->Get_fY()));

	m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create(ITEM_SHIELD,
		m_Objlist[OBJ_PLAYER].front()->Get_fX(), (m_Objlist[OBJ_PLAYER].front()->Get_fY() - 100.f)));

	m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create(ITEM_ROLLBOT,
		m_Objlist[OBJ_PLAYER].front()->Get_fX(), (m_Objlist[OBJ_PLAYER].front()->Get_fY() - 200.f)));

	Get_MONPOINT();
}

void CMaingame::Update(void)
{
	//m_pPlayer->Update();

	srand(unsigned(time(NULL)));

	if (m_Objlist[OBJ_MONSTER].size() < 4)
	{
		if (m_dwTime + 1000 < GetTickCount())
		{
			int MON_TYPE = rand() % 2 + 1;
			for (int i = 0; i < 4; ++i)
			{
				m_Objlist[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(m_tMonsterPoint[i], m_Objlist[OBJ_PLAYER].front(), MON_TYPE));
			}
		}
	}

	for (auto& iter = m_Objlist[OBJ_MONSTER].begin(); iter != m_Objlist[OBJ_MONSTER].end(); ++iter)
		static_cast<CMonster*>(*iter)->Set_BulletList_Mon(&m_Objlist[OBJ_BULLETMONSTER]);

	for (int i = OBJ_PLAYER; i < OBJ_END; ++i)
	{
		for (auto iter = m_Objlist[i].begin(); iter != m_Objlist[i].end();)
		{
			if (0 >= (*iter)->Get_HP())
			{
				if (i == OBJ_PLAYER)
				{
					for (auto iter = m_Objlist[OBJ_SHIELD].begin(); iter != m_Objlist[OBJ_SHIELD].end();)
					{
						delete *iter;
						iter = m_Objlist[OBJ_SHIELD].erase(iter);
					}

					for (auto iter = m_Objlist[ITEM_ROLLBOT].begin(); iter != m_Objlist[ITEM_ROLLBOT].end();)
					{
						delete *iter;
						iter = m_Objlist[ITEM_ROLLBOT].erase(iter);
					}
				}

				if (i == OBJ_MONSTER) // 삭제되는 OBJ가 몬스터일 경우 score 증가
				{
					m_iScore += 10;
				}

				if (i == OBJ_ITEM)
				{
					if(ITEM_BULLET == static_cast<CItem*>(*iter)->Get_Item_ID())
					{
						static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Pick_Up_Item(*iter);
					}
					else if (ITEM_SHIELD == static_cast<CItem*>(*iter)->Get_Item_ID())
					{
						CObj* shield = CAbstractFactory<CShield>::Create();
						shield->Initialize();
						if (!m_Objlist[OBJ_SHIELD].empty())
						{
							shield->Set_Angle(m_Objlist[OBJ_SHIELD].back()->Get_Angle() + SHILED_INTERVAL);
						}
						static_cast<CShield*>(shield)->Set_Player(m_Objlist[OBJ_PLAYER].front());

						m_Objlist[OBJ_SHIELD].push_back(shield);
					}
					else if (ITEM_ROLLBOT == static_cast<CItem*>(*iter)->Get_Item_ID())
					{
						CObj* rollBot = CAbstractFactory<CRollBot>::Create();
						if (!m_Objlist[OBJ_ROLLBOT].empty())
						{
							rollBot->Set_Angle(m_Objlist[OBJ_ROLLBOT].back()->Get_Angle() + SHILED_INTERVAL);
						}
						static_cast<CRollBot*>(rollBot)->Set_Player(m_Objlist[OBJ_PLAYER].front());
						static_cast<CRollBot*>(rollBot)->Set_BulletList(&m_Objlist[OBJ_BULLET]);

						m_Objlist[OBJ_ROLLBOT].push_back(rollBot);
					}
				}
				Safe_Delete<CObj*>(*iter);
				iter = m_Objlist[i].erase(iter);

				if (m_Objlist[OBJ_PLAYER].empty())
				{
					if (0 < m_iLife)
					{
						if (GetAsyncKeyState('R')) 
						{
							--m_iLife;
							m_Objlist[OBJ_PLAYER].push_back(new CPlayer);
							m_Objlist[OBJ_PLAYER].front()->Initialize();
							static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Set_BulletList(&m_Objlist[OBJ_BULLET]);
						}
					}
					else
					{

					}
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
	CCollision::Collision_Circle(m_Objlist[OBJ_SHIELD], m_Objlist[OBJ_MONSTER]);
	CCollision::Collision_Item(m_Objlist[OBJ_ITEM], m_Objlist[OBJ_PLAYER]);
	CCollision::Collision_Player(m_Objlist[OBJ_MONSTER], m_Objlist[OBJ_PLAYER]);
	CCollision::Collision_Player(m_Objlist[OBJ_BULLETMONSTER], m_Objlist[OBJ_PLAYER]);

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
	swprintf_s(m_szLife, L"Life : %d", m_iLife);
	TextOutW(m_hDC, GAMESIZE + 100, OUTGAMESIZE, m_szLife, lstrlen(m_szLife));

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

void CMaingame::Get_MONPOINT(void)
{
	m_tMonsterPoint.push_back({ (LONG)(WINCX - GAMESIZE - 1.6 * Monster_C), (LONG)(GAMESIZE + 0.5 * Monster_C + 1) });
	m_tMonsterPoint.push_back({ (LONG)(WINCX - GAMESIZE - 3.6 * Monster_C), (LONG)(GAMESIZE + 3.5 * Monster_C) });
	m_tMonsterPoint.push_back({ (LONG)(WINCX - GAMESIZE - 3.6 * Monster_C), (LONG)(WINCY - GAMESIZE - 3.5 * Monster_C) });
	m_tMonsterPoint.push_back({ (LONG)(WINCX - GAMESIZE - 1.6 * Monster_C), (LONG)(WINCY - GAMESIZE - 0.5 * Monster_C - 1) });
}
