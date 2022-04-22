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
}

void CMaingame::Update(void)
{
}

void CMaingame::Late_Update(void)
{
	m_pPlayer->Late_Update();
}

void CMaingame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, GAMESIZE, GAMESIZE, WINCX - GAMESIZE, WINCY - GAMESIZE);
	swprintf_s(m_szScore, L"Score : %d", m_iScore);
	TextOutW(m_hDC, 25, 25, m_szScore, lstrlen(m_szScore));

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())   //        ???????????
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
}

void CMaingame::Release(void)
{
}
