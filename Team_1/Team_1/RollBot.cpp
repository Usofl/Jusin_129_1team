#include "stdafx.h"
#include "RollBot.h"

DWORD CRollBot::m_lTime = GetTickCount();

CRollBot::CRollBot()
	: m_pBulletList(nullptr)
{
}


CRollBot::~CRollBot()
{
}

void CRollBot::Initialize(void)
{
	m_tInfo.fCX = 18.f;
	m_tInfo.fCY = 18.f;
	m_fSpeed = 5.f;
	m_iHP = 100;
}

void CRollBot::Update(void)
{
	m_fAngle += m_fSpeed;

	m_tInfo.fX = m_pPlayer->Get_fX() + (75.f * cos(m_fAngle * DEGREE));
	m_tInfo.fY = m_pPlayer->Get_fY() - (75.f * sin(m_fAngle * DEGREE));

	Update_Rect();
}

void CRollBot::Late_Update(void)
{
	if (m_lTime + 650 < GetTickCount())
	{
		m_lTime = GetTickCount();

		m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, 0.f));
		--m_iHP;
	}
}

void CRollBot::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CRollBot::Release(void)
{
}
