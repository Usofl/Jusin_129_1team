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

	CObj* m_pBullet = new CBullet;
	m_pBullet->Initialize();

	m_pPlayer = new CPlayer;
	m_pPlayer->Initialize();

	m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 65.f));
	m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 95.f));
	m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 505.f));
	m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 535.f));
}

void CMaingame::Update(void)
{
	m_pPlayer->Update();

	for (auto& iter : m_Monsterlist)
	{
		iter->Update();
	}

	// ÃÑ¾Ë
	for (std::list<CObj*>::iterator iter = m_pBulletList.begin();
		iter != m_pBulletList.end();)
	{
		(*iter)->Update();
	}
}

void CMaingame::Late_Update(void)
{

	m_pPlayer->Late_Update();
	// ÃÑ¾Ë
	for (std::list<CObj*>::iterator iter = m_pBulletList.begin();
		iter != m_pBulletList.end();)
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

	if (m_dwTime + 1000 < GetTickCount())   // GetTickCount() 1000ºÐÀÇ 1ÃÊ
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	//¸ó½ºÅÍ Ãâ·Â
	for (auto& iter : m_Monsterlist)
	{
		iter->Render(m_hDC);
	}

	// ÃÑ¾Ë
	for (std::list<CObj*>::iterator iter = m_pBulletList.begin();
		iter != m_pBulletList.end();)
	{
		(*iter)->Render(m_hDC);
	}
}

void CMaingame::Release(void)
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}