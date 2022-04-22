#include "stdafx.h"
#include "Maingame.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Obj.h"


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

	//    몬스터 생성...........

	m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 65.f));
	m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 95.f));
	m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 505.f));
	m_Monsterlist.push_back(CAbstractFactory<CMonster>::Create(735.f, 535.f));
}

void CMaingame::Update(void)
{


	for (auto& iter : m_Monsterlist)
	{
		iter->Update();
	}
}

void CMaingame::Late_Update(void)
{
}

void CMaingame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, GAMESIZE, GAMESIZE, WINCX - GAMESIZE, WINCY - GAMESIZE);

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
