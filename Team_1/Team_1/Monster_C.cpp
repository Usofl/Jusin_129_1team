#include "stdafx.h"
#include "Monster_C.h"


CMonster_C::CMonster_C()
{
}

CMonster_C::CMonster_C(CObj * _player)
	: CMonster(_player)
{
}

CMonster_C::~CMonster_C()
{
}

void CMonster_C::Initialize(void)
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

void CMonster_C::Update(void)
{
	Move_Monster();

	if (dwTime_bullet + 2000 < GetTickCount())
	{
		float m_MonPlr_Angle = 0.f;

		Mon_Bulletlist->push_back(CAbstractFactory<CBulletMonster>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle, MONSTERTYPE_C));

		dwTime_bullet = GetTickCount();
	}
	Update_Rect();
}

//void CMonster_C::Late_Update(void)
//{
//}

void CMonster_C::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);

	Update_Rect();
}

void CMonster_C::Release(void)
{
}

void CMonster_C::Move_Monster(void)
{
	// 오른쪽 화면에서의 포물선 총알. 몬스터 타입 : C
	if (((m_tInfo.fY + 0.5*Monster_C) >= (WINCY - GAMESIZE)) || ((m_tInfo.fY - 0.5*Monster_C) <= GAMESIZE))
	{
		m_fSpeed *= -1.f;
	}
	if (((m_tInfo.fX + 0.5*Monster_C) >= (WINCX - GAMESIZE)) || ((m_tInfo.fX - 0.5*Monster_C) <= 0.6 * WINCX))
	{
		m_fSpeed *= -1.f;
	}

	if (dwTime + 1000 < GetTickCount())
	{
		theta += PI;

		dwTime = GetTickCount();
	}

	if (m_tInfo.fY > 0.5 * WINCY)
	{
		m_tInfo.fY -= 0.05f * m_fSpeed * cos(theta);
	}
	if (m_tInfo.fY < 0.5 * WINCY)
	{
		m_tInfo.fY += 0.05f * m_fSpeed * cos(theta);
	}
}
