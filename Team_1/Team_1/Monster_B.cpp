#include "stdafx.h"
#include "Monster_B.h"
#include "BulletMonster.h"

CMonster_B::CMonster_B()
{
}

CMonster_B::CMonster_B(CObj * _player)
	: CMonster(_player)
{
}


CMonster_B::~CMonster_B()
{
}

void CMonster_B::Initialize(void)
{
	dwTime = 0;
	dwTime_bullet = 0;
	theta = 0.f;

	m_tInfo.fCX = Monster_C;
	m_tInfo.fCY = Monster_C;

	m_iHP = 2;

	m_iReverse = 1;

	m_fSpeed = 10.f;
}

void CMonster_B::Update(void)
{
	Move_Monster();

	if (dwTime_bullet + 1500 < GetTickCount())
	{
		float m_MonPlr_Angle = 0.f;

		Mon_Bulletlist->push_back(CAbstractFactory<CBulletMonster>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle, MONSTERTYPE_B));

		dwTime_bullet = GetTickCount();
	}

	Update_Rect();
}

//void CMonster_B::Late_Update(void)
//{
//}

void CMonster_B::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.top - 10, m_tRC.right, m_tRC.bottom - 20);
	Ellipse(_hDC, m_tRC.left + (10 * m_iReverse), m_tRC.top - 5, m_tRC.right + (5 * m_iReverse), m_tRC.bottom - 20);
	Ellipse(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.top, m_tRC.right, m_tRC.bottom - 15);

	MoveToEx(_hDC, m_tRC.left + (22 * m_iReverse), m_tRC.bottom - 15, nullptr);
	LineTo(_hDC, m_tRC.left + (22 * m_iReverse), m_tRC.bottom - 3);
	LineTo(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.bottom);
	MoveToEx(_hDC, m_tRC.left + (22 * m_iReverse), m_tRC.bottom - 3, nullptr);
	LineTo(_hDC, m_tRC.right, m_tRC.bottom);

	MoveToEx(_hDC, m_tRC.left + (22 * m_iReverse), (int)m_tInfo.fY, nullptr);
	LineTo(_hDC, m_tRC.left + (3 * m_iReverse), (int)m_tInfo.fY);
	MoveToEx(_hDC, m_tRC.left + (22 * m_iReverse), (int)m_tInfo.fY + 5, nullptr);
	LineTo(_hDC, m_tRC.left + (8 * m_iReverse), (int)m_tInfo.fY);
}

void CMonster_B::Release(void)
{
}

void CMonster_B::Move_Monster(void)
{
	// 오른쪽 화면에서의 이동(총알). 몬스터 타입 : B
	if (((m_tInfo.fY + 0.5f * Monster_C) >= (WINCY - GAMESIZE)) || ((m_tInfo.fY - 0.5f * Monster_C) <= GAMESIZE))
	{
		m_fSpeed *= -1.f;
	}
	if (((m_tInfo.fX + 0.5f * Monster_C) >= (WINCX - GAMESIZE)) || ((m_tInfo.fX - 0.5f * Monster_C) <= 0.5 * WINCX + GAMESIZE))
	{
		m_fSpeed *= -1.f;
	}

	if (dwTime + 1000 < GetTickCount())
	{
		theta += PI * 0.3f;

		dwTime = GetTickCount();
	}

	m_tInfo.fY += 0.15f * m_fSpeed * cos(theta);
	m_tInfo.fX -= 0.15f * m_fSpeed * sin(theta);
}
