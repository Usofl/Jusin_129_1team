#include "stdafx.h"
#include "Maingame.h"


CMaingame::CMaingame()
	: m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
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

}

void CMaingame::Update(void)
{
	// ÃÑ¾Ë
	for (std::list<CObj*>::iterator iter = m_pBulletList.begin();
		iter != m_pBulletList.end();)
	{
		(*iter)->Update();
	}
}

void CMaingame::Late_Update(void)
{
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

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
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
}
