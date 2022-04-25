#include "stdafx.h"
#include "Shield.h"

CShield::CShield()
{
}


CShield::~CShield()
{
}

void CShield::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 7.f;
	m_iHP = 1;
}

void CShield::Update(void)
{
	m_fAngle += m_fSpeed;

	m_tInfo.fX = m_pPlayer->Get_fX() + (50.f * cos(m_fAngle * DEGREE));
	m_tInfo.fY = m_pPlayer->Get_fY() - (50.f * sin(m_fAngle * DEGREE));

	Update_Rect();
}

void CShield::Late_Update(void)
{
}

void CShield::Render(HDC& _hDC)
{
	Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
	Ellipse(_hDC, m_tRC.left + 5, m_tRC.top + 5, m_tRC.right - 5, m_tRC.bottom - 5);
	Ellipse(_hDC, m_tRC.left + 10, m_tRC.top + 10, m_tRC.right - 10, m_tRC.bottom - 10);
}

void CShield::Release(void)
{
}
