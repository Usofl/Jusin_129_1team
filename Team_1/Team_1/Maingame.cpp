#include "stdafx.h"
#include "Maingame.h"

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

	m_pPlayer = new CPlayer;
	m_pPlayer->Initialize();
	static_cast<CPlayer*>(m_pPlayer)->Set_BulletList(&m_BulletList);

}

void CMaingame::Update(void)
{
	m_pPlayer->Update();

	if (m_dwTime + 1000 < GetTickCount())   // GetTickCount() 1000분의 1초 //  xxxxx 한번만 1초뒤에 생성할려고 함.
	{
		m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(WINCX - GAMESIZE - 15.f , 65.f));// 몬스터의 반지름.
		m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 95.f));
		m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 505.f));
		m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 535.f));
	}

	for (std::list<CObj*>::iterator iter = m_Monsterlist.begin();
		iter != m_Monsterlist.end();++iter)
	{
		dynamic_cast<CMonster*>(*iter)->Set_Player(m_pPlayer);
	}

	for (std::list<CObj*>::iterator iter = m_Monsterlist.begin();
		iter != m_Monsterlist.end();++iter)
	{
		(*iter)->Update();
	}

	// 총알
	for (std::list<CObj*>::iterator iter = m_BulletList.begin();
		iter != m_BulletList.end(); ++iter)
	{
		(*iter)->Update();
	}

}

void CMaingame::Late_Update(void)
{

	m_pPlayer->Late_Update();

	// 총알
	for (std::list<CObj*>::iterator iter = m_BulletList.begin();
		iter != m_BulletList.end(); ++iter)
	{
		(*iter)->Late_Update();
	}
}

void CMaingame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, GAMESIZE, GAMESIZE, WINCX - GAMESIZE, WINCY - GAMESIZE);
	swprintf_s(m_szScore, L"Score : %d", m_iScore);
	TextOutW(m_hDC, 25, 25, m_szScore, lstrlen(m_szScore));

	m_pPlayer->Render(m_hDC);

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())   // GetTickCount() 1000분의 1초
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	//몬스터 출력
	for (auto& iter : m_Monsterlist)
	{
		iter->Render(m_hDC);
	}

	// 총알
	for (std::list<CObj*>::iterator iter = m_BulletList.begin();
		iter != m_BulletList.end(); ++iter)
	{
		(*iter)->Render(m_hDC);
	}
}

void CMaingame::Release(void)
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}