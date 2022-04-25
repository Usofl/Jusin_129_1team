#include "stdafx.h"
#include "Maingame.h"

CMaingame::CMaingame()
	: m_dwTime(GetTickCount())
	, m_dwPlayer(GetTickCount())
	, m_iFPS(0)
	, m_iScore(0)
	, m_iLife(0)
	, m_bCheak(true)
	, m_bBossCheck(false)
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	ZeroMemory(m_szScore, sizeof(TCHAR) * 64);
	ZeroMemory(m_szLife, sizeof(TCHAR) * 64);
}

CMaingame::~CMaingame()
{
	Release();
}

void CMaingame::Initialize(void)
{
	srand((unsigned int)time((nullptr)));

	m_hDC = GetDC(g_hWnd);

	m_Objlist[OBJ_PLAYER].push_back(new CPlayer);
	m_Objlist[OBJ_PLAYER].front()->Initialize();
	static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Set_BulletList(&m_Objlist[OBJ_BULLET]);
	m_iLife = 3;

	m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create_Item_Bullet
		(m_Objlist[OBJ_PLAYER].front()->Get_fX(), (m_Objlist[OBJ_PLAYER].front()->Get_fY() - 200.f)));

	m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create_Item_Shield
		(m_Objlist[OBJ_PLAYER].front()->Get_fX() + 200.f, (m_Objlist[OBJ_PLAYER].front()->Get_fY() + 200.f)));

	m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create_Item_RollBot
	(m_Objlist[OBJ_PLAYER].front()->Get_fX() + 50.f, (m_Objlist[OBJ_PLAYER].front()->Get_fY() + 200.f)));

	m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create_Item_Guided
		(m_Objlist[OBJ_PLAYER].front()->Get_fX() + 100.f, (m_Objlist[OBJ_PLAYER].front()->Get_fY() + 200.f)));

	m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create_Item_UltiMate
		(m_Objlist[OBJ_PLAYER].front()->Get_fX(), (m_Objlist[OBJ_PLAYER].front()->Get_fY() + 200.f)));


	Get_MONPOINT();
}

void CMaingame::Update(void)
{
	//m_pPlayer->Update();

	// 일시정지, 키인풋 함수, 이니셜라이즈에 게임 메인화면 출력

	Key_Input();

	srand(unsigned(time(NULL)));

	if (m_Objlist[OBJ_PLAYER].empty())
	{
		if (0 < m_iLife)
		{
			if (!m_Objlist[OBJ_ULTIMATE].empty())
			{
				Safe_Delete<CObj*>(*m_Objlist[OBJ_ULTIMATE].begin());
				m_Objlist[OBJ_ULTIMATE].erase(m_Objlist[OBJ_ULTIMATE].begin());
			}
			--m_iLife; // 라이프 스코어 감소
			m_bCheak = true; // 사망시 무적 시간 부여를 위한 bool 변수
			m_iScore = (int)(m_iScore * 0.8); // 사망시 점수 감소
			m_Objlist[OBJ_PLAYER].push_back(new CPlayer);
			m_Objlist[OBJ_PLAYER].front()->Initialize();
			static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Set_BulletList(&m_Objlist[OBJ_BULLET]);

			for (auto iter = m_Objlist[OBJ_MONSTER].begin(); iter != m_Objlist[OBJ_MONSTER].end(); ++iter)
			{
				static_cast<CMonster*>(*iter)->Set_Player(m_Objlist[OBJ_PLAYER].front());
			}
			return;
		}

		else
		{
			if (GetAsyncKeyState('Q'))
			{
				PostQuitMessage(0);
			}
		}
	}
	else
	{
		if ((m_Objlist[OBJ_MONSTER].size() < 2) && (350 >= m_iScore) &&(!m_bBossCheck) ) // 스코어 판단 부호 바꾸기 xxx
		{
			if (m_dwTime + 1000 < GetTickCount())
			{
				Random_Mon();
			}
		}
		if ((m_Objlist[OBJ_MONSTER].size() < 2) && (350 < m_iScore))
		{
			if ((0 == (m_Objlist[OBJ_MONSTER].size())) && (!m_bBossCheck))
			{
				m_Objlist[OBJ_MONSTER].push_back(CMonsterFactory::Create_Mon_BOSS(m_Objlist[OBJ_PLAYER].front()));// 보스 생성.

				//for (auto& iter = m_Objlist[OBJ_MONSTER].begin(); iter != m_Objlist[OBJ_MONSTER].end(); ++iter)
					//static_cast<CMonster_Boss*>(*iter)->Set_BulletList_Mon(&m_Objlist[OBJ_BULLETMONSTER]);// 보스 총알 부여.

				m_bBossCheck = true;// 보스가 존재함.
			}
		}
	}

	for (auto& iter = m_Objlist[OBJ_MONSTER].begin(); iter != m_Objlist[OBJ_MONSTER].end();)
	{
		//if (static_cast<CMonster_Boss*>(*iter)->Get_Mon_Type != MONSTERTYPE_BOSS)
		    static_cast<CMonster*>(*iter)->Set_BulletList_Mon(&m_Objlist[OBJ_BULLETMONSTER]);

		if (0 >= (*iter)->Get_HP())
		{
			Create_Item((*iter)->Get_fX(), (*iter)->Get_fY()); // 아이템 생성
			m_iScore += 10; // score 증가


			/*if (static_cast<CMonster_Boss*>(m_Objlist[OBJ_MONSTER].front())->Get_Mon_Type() == MONSTERTYPE_BOSS)
			{
				Safe_Delete<CObj*>(*iter);
				
			}*/
			//else
			//{
				Safe_Delete<CObj*>(*iter);
				iter = m_Objlist[OBJ_MONSTER].erase(iter); //  보스가 죽을때 iter넘길 대상 없음.  xxxxxxxxxxxxxxxxxxx

			//}
		}
		else
		{
			(*iter)->Update();
			++iter;
		}
	}

	for (auto iter = m_Objlist[OBJ_PLAYER].begin(); iter != m_Objlist[OBJ_PLAYER].end();)
	{
		if (0 >= (*iter)->Get_HP())
		{
			for (auto& iter : m_Objlist[OBJ_MONSTER])
			{
				static_cast<CMonster*>(iter)->Set_Player(nullptr);
			}

			for (auto iter = m_Objlist[OBJ_SHIELD].begin(); iter != m_Objlist[OBJ_SHIELD].end();)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_Objlist[OBJ_SHIELD].erase(iter);
			}

			for (auto iter = m_Objlist[OBJ_ROLLBOT].begin(); iter != m_Objlist[OBJ_ROLLBOT].end();)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_Objlist[OBJ_ROLLBOT].erase(iter);
			}

			Safe_Delete<CObj*>(*iter);
			iter = m_Objlist[OBJ_PLAYER].erase(iter);
		}
		else
		{
			(*iter)->Update();
			++iter;
		}
	}

	for (auto iter = m_Objlist[OBJ_ITEM].begin(); iter != m_Objlist[OBJ_ITEM].end();)
	{
		if (0 >= (*iter)->Get_HP())
		{
			ITEMID eItem = static_cast<CItem*>(*iter)->Get_Item_ID();

			switch (eItem)
			{
			case ITEM_BULLET:
				static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Pick_Up_Bullet();
				break;
			case ITEM_GUIDED:
				static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Pick_Up_Guided();
				break;
			case ITEM_ULTIMATE:
				static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Pick_Up_Ulti();
				break;
			case ITEM_SHIELD:
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
				break;
			case ITEM_ROLLBOT:
			{
				CObj* rollBot = CAbstractFactory<CRollBot>::Create();
				rollBot->Initialize();
				if (!m_Objlist[OBJ_ROLLBOT].empty())
				{
					rollBot->Set_Angle(m_Objlist[OBJ_ROLLBOT].back()->Get_Angle() + SHILED_INTERVAL);
				}
				static_cast<CRollBot*>(rollBot)->Set_Player(m_Objlist[OBJ_PLAYER].front());
				static_cast<CRollBot*>(rollBot)->Set_BulletList(&m_Objlist[OBJ_BULLET]);

				m_Objlist[OBJ_ROLLBOT].push_back(rollBot);
			}
				break;
			case ITEM_END:
				break;
			}

				Safe_Delete<CObj*>(*iter);

				iter = m_Objlist[OBJ_ITEM].erase(iter);

				if (m_Objlist[OBJ_PLAYER].empty())
				{
					if (0 < m_iLife)
					{
						--m_iLife; // 라이프 스코어 감소
						m_bCheak = true; // 사망시 무적 시간 부여를 위한 bool 변수
						m_iScore = (m_iScore * 0.8); // 사망시 점수 감소
						m_Objlist[OBJ_PLAYER].push_back(new CPlayer);
						m_Objlist[OBJ_PLAYER].front()->Initialize();
						static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Set_BulletList(&m_Objlist[OBJ_BULLET]);

						for (auto iter = m_Objlist[OBJ_MONSTER].begin(); iter != m_Objlist[OBJ_MONSTER].end(); ++iter)
						{
							static_cast<CMonster*>(*iter)->Set_Player(m_Objlist[OBJ_PLAYER].front());
						}
						return;
					}

					else
					{
						if (GetAsyncKeyState('Q'))
						{
							PostQuitMessage(0);
						}
					}
				}
			}
			else
			{
				(*iter)->Update();
				++iter;
			}
		
	}


	for (int i = OBJ_BULLET; i < OBJ_END; ++i)
	{
		for (auto iter = m_Objlist[i].begin(); iter != m_Objlist[i].end();)
		{
			if (0 >= (*iter)->Get_HP())
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_Objlist[i].erase(iter);
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
	if (m_bCheak) // 플레이어에 무적 시간 부여
	{
		if (m_dwPlayer + 3000 < GetTickCount())
		{
			m_dwPlayer = GetTickCount();
			CCollision::Collision_Player(m_Objlist[OBJ_MONSTER], m_Objlist[OBJ_PLAYER]);
			CCollision::Collision_Circle(m_Objlist[OBJ_BULLETMONSTER], m_Objlist[OBJ_PLAYER]);
			m_bCheak = false;
		}
	}
	else
	{
		CCollision::Collision_Player(m_Objlist[OBJ_MONSTER], m_Objlist[OBJ_PLAYER]);
		CCollision::Collision_Circle(m_Objlist[OBJ_BULLETMONSTER], m_Objlist[OBJ_PLAYER]);
	}

	if (!m_Objlist[OBJ_ULTIMATE].empty()) // 얼티메이트 충돌 검사
	{
		CCollision::Collision_Ult(m_Objlist[OBJ_ULTIMATE], m_Objlist[OBJ_MONSTER]);
		CCollision::Collision_Ult(m_Objlist[OBJ_ULTIMATE], m_Objlist[OBJ_BULLETMONSTER]);
	}

	CCollision::Collision_Circle(m_Objlist[OBJ_MONSTER], m_Objlist[OBJ_BULLET]);
	CCollision::Collision_Circle(m_Objlist[OBJ_SHIELD], m_Objlist[OBJ_MONSTER]);
	CCollision::Collision_Player(m_Objlist[OBJ_SHIELD], m_Objlist[OBJ_BULLETMONSTER]);
	CCollision::Collision_Item(m_Objlist[OBJ_ITEM], m_Objlist[OBJ_PLAYER]);

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
	//Rectangle(m_hDC, GAMESIZE, GAMESIZE, WINCX - GAMESIZE, WINCY - GAMESIZE);
	swprintf_s(m_szScore, L"Score : %d", m_iScore);
	TextOutW(m_hDC, GAMESIZE, OUTGAMESIZE, m_szScore, lstrlen(m_szScore));
	swprintf_s(m_szLife, L"Life : %d", m_iLife);
	TextOutW(m_hDC, GAMESIZE + 100, OUTGAMESIZE, m_szLife, lstrlen(m_szLife));
	if (m_bBossCheck)
	{
		swprintf_s(m_szMonHP, L"HP : %d", m_Objlist[OBJ_MONSTER].front()->Get_HP());
		TextOutW(m_hDC, WINCX - GAMESIZE - 100, OUTGAMESIZE, m_szMonHP, lstrlen(m_szMonHP));
	}

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
}

void CMaingame::Key_Input(void)
{
	if (GetAsyncKeyState('R')) // 라이프 카운트 추가
	{
		++m_iLife;
	}

	if (GetAsyncKeyState(VK_SPACE)) // 얼티메이트 사용 데미지 50
	{
		if (m_dwTime + 1000 < GetTickCount())
		{
			if (!static_cast<CPlayer*>(m_Objlist[OBJ_PLAYER].front())->Use_Ult())
			{
				/*m_Objlist[OBJ_ULTIMATE].push_back(new CUltimate);
				m_Objlist[OBJ_ULTIMATE].front()->Initialize();*/

				CObj* Ult = CAbstractFactory<CUltimate>::Create();
				Ult->Initialize();
				static_cast<CUltimate*>(Ult)->Set_Player(m_Objlist[OBJ_PLAYER].front());
				m_Objlist[OBJ_ULTIMATE].push_back(Ult);
			}
		}
	}
}

void CMaingame::Get_MONPOINT(void)
{
	m_tMonsterPoint.push_back({ (LONG)(WINCX - GAMESIZE - 1.6 * Monster_C), (LONG)(GAMESIZE + 0.5 * Monster_C + 10) });
	m_tMonsterPoint.push_back({ (LONG)(WINCX - GAMESIZE - 3.6 * Monster_C), (LONG)(GAMESIZE + 3.5 * Monster_C) });
	m_tMonsterPoint.push_back({ (LONG)(WINCX - GAMESIZE - 3.6 * Monster_C), (LONG)(WINCY - GAMESIZE - 3.5 * Monster_C) });
	m_tMonsterPoint.push_back({ (LONG)(WINCX - GAMESIZE - 1.6 * Monster_C), (LONG)(WINCY - GAMESIZE - 0.5 * Monster_C - 10) });
}

void CMaingame::Create_Item(const float& _fA, const float& _fB)
{
	int iRanDrop = rand() % 100 + 1;
	int iRanItem = rand() % 100 + 1;

	switch (iRanDrop % 20) // 랜덤한 확률로 아이템 발생
	{
	case 1:
	{
		if(0 < iRanItem && 25 >= iRanItem)
		{
			m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create_Item_Bullet(_fA, _fB));
		}
		else if(25 < iRanItem && 50 >= iRanItem)
		{
			m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create_Item_Shield(_fA, _fB));
		}
		else if(50 < iRanItem && 75 >= iRanItem)
		{
			m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create_Item_RollBot(_fA, _fB));
		}
		else if (75 < iRanItem && 90 >= iRanItem)
		{
			m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create_Item_Guided(_fA, _fB));
		}
		else
		{
			m_Objlist[OBJ_ITEM].push_back(CItemFactory::Create_Item_UltiMate(_fA, _fB));
		}
	}
	break;
	}
}

void CMaingame::Random_Mon(void)
{
	int MON_TYPE = rand() % 4 + 1;
	for (int i = 0; i < 4; ++i)
	{
		//  몬스터 타입에 따라 즉 0~3까지에 따라 스위치 해서 부동한 몬스터 생성.
		switch (MON_TYPE)
		{
		case MONSTERTYPE_A:
			m_Objlist[OBJ_MONSTER].push_back(CMonsterFactory::Create_Mon_A(m_tMonsterPoint[i], m_Objlist[OBJ_PLAYER].front()));
			break;

		case MONSTERTYPE_B:
			m_Objlist[OBJ_MONSTER].push_back(CMonsterFactory::Create_Mon_B(m_tMonsterPoint[i], m_Objlist[OBJ_PLAYER].front()));
			break;

		case MONSTERTYPE_C:
			m_Objlist[OBJ_MONSTER].push_back(CMonsterFactory::Create_Mon_C(m_tMonsterPoint[i], m_Objlist[OBJ_PLAYER].front()));
			break;
		}
	}
}
