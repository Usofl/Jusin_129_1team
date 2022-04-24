#include "stdafx.h"
#include "Monster_B.h"


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

		Mon_Bulletlist->push_back(CAbstractFactory<CBulletMonster>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle, m_MonType));

		dwTime_bullet = GetTickCount();
	}

	Update_Rect();
}

//void CMonster_B::Late_Update(void)
//{
//}

void CMonster_B::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CMonster_B::Release(void)
{
}

void CMonster_B::Move_Monster(void)
{
	// ������ ȭ�鿡���� �̵�(�Ѿ�). ���� Ÿ�� : B
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