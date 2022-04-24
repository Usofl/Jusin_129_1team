#include "stdafx.h"
#include "MONSTER_A.h"


CMonster_A::CMonster_A()
{
}

CMonster_A::CMonster_A(CObj * _player)
	: CMonster(_player)
{
}

CMonster_A::~CMonster_A()
{
}

void CMonster_A::Initialize(void)
{
	dwTime = 0;
	dwTime_bullet = 0;
	theta = 0.f;

	m_tInfo.fCX = Monster_C;
	m_tInfo.fCY = Monster_C;

	m_iHP = 5;

	m_iReverse = 1;

	m_fSpeed = 15.f;
}

void CMonster_A::Update(void)
{
	Move_Monster();

	Update_Rect();
}

void CMonster_A::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.top + 10, m_tRC.right - (5 * m_iReverse), m_tRC.bottom - 10);

	MoveToEx(_hDC, m_tRC.left, m_tRC.top + 10, nullptr);
	LineTo(_hDC, m_tRC.left + (10 * m_iReverse), m_tRC.top + 10);
	LineTo(_hDC, m_tRC.left + (10 * m_iReverse), m_tRC.top - 7);
	LineTo(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.top - 7);
	LineTo(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.top + 10);

	LineTo(_hDC, m_tRC.right + (5 * m_iReverse), m_tRC.top + 10);
	LineTo(_hDC, m_tRC.right + (10 * m_iReverse), m_tRC.top + 5);
	LineTo(_hDC, m_tRC.right + (10 * m_iReverse), m_tRC.bottom - 5);
	LineTo(_hDC, m_tRC.right + (5 * m_iReverse), m_tRC.bottom - 10);

	LineTo(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.bottom - 10);
	LineTo(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.bottom + 7);
	LineTo(_hDC, m_tRC.left + (10 * m_iReverse), m_tRC.bottom + 7);
	LineTo(_hDC, m_tRC.left + (10 * m_iReverse), m_tRC.bottom - 10);
	LineTo(_hDC, m_tRC.left, m_tRC.bottom - 10);
	LineTo(_hDC, m_tRC.left, m_tRC.top + 10); 
}

void CMonster_A::Release(void)
{
}

void CMonster_A::Move_Monster(void)
{
	// 돌진 자폭형 몬스터.
	if (m_pPlayer != nullptr)
	{
		if (0.5f * PLAYERCX < abs(m_tInfo.fX - m_pPlayer->Get_fX()))
		{
			m_fAngle = Find_MonPlr_CosAngle();
			m_tInfo.fX -= 0.2f * m_fSpeed * cos(m_fAngle);
		}
		if (0.5f * PLAYERCY < abs(m_tInfo.fY - m_pPlayer->Get_fY()))
		{
			m_fAngle = Find_MonPlr_SinAngle();
			m_tInfo.fY -= 0.2f * m_fSpeed * sin(m_fAngle);
		}

		if ((m_tInfo.fY + 0.5f * Monster_C) >= (WINCY - GAMESIZE)) // 몬스터가 프레임 밖으로 벗어나지 못하게 함.
		{
			m_tInfo.fY = WINCY - GAMESIZE - 0.5f * Monster_C;
		}
		if ((m_tInfo.fY - 0.5f * Monster_C) <= GAMESIZE)
		{
			m_tInfo.fY = GAMESIZE + 0.5f * Monster_C;
		}
		if ((m_tInfo.fX + 0.5f * Monster_C) >= (WINCX - GAMESIZE))
		{
			m_tInfo.fX = WINCX - GAMESIZE - 0.5f * Monster_C;
		}
		if ((m_tInfo.fX - 0.5f * Monster_C) <= GAMESIZE)
		{
			m_tInfo.fX = GAMESIZE + 0.5f * Monster_C;
		}
	}
}
float CMonster_A::Find_MonPlr_CosAngle(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;

	fXX = m_tInfo.fX - (*m_pPlayer).Get_fX();
	fYY = m_tInfo.fY - (*m_pPlayer).Get_fY();

	fAngle = acos(fXX, fYY);

	return fAngle;
}

float CMonster_A::Find_MonPlr_SinAngle(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;

	fXX = m_tInfo.fX - (*m_pPlayer).Get_fX();
	fYY = m_tInfo.fY - (*m_pPlayer).Get_fY();

	fAngle = asin(fXX, fYY);

	return fAngle;
}