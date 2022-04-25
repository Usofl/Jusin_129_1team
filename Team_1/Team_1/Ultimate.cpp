#include "stdafx.h"
#include "Ultimate.h"


CUltimate::CUltimate()
{
}


CUltimate::~CUltimate()
{
}

void CUltimate::Initialize(void)
{
	/*m_tInfo.fCX = ULTCX;
	m_tInfo.fCY = ULTCY;

	m_tInfo.fX = ULT_START_X;
	m_tInfo.fY = ULT_START_Y;*/

	//m_iHP = 65;

	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 100.f;
	m_iHP = 250;
	m_fTemp = 5.f;

	m_lDest = 2;
}

void CUltimate::Update(void)
{
	//Update_Rect();
	//m_tInfo.fX += m_fSpeed;
	//--m_iHP;
	m_tInfo.fCX += 2.f;
	m_tInfo.fCY += 2.f;

	m_fAngle += m_fSpeed;

	m_tInfo.fX = m_pPlayer->Get_fX() + (m_fTemp * cosf(m_fAngle * DEGREE));
	m_tInfo.fY = m_pPlayer->Get_fY() - (m_fTemp * sinf(m_fAngle * DEGREE));
	m_fTemp += 2.f;
	m_iHP -= 1;

	Update_Rect();
}

void CUltimate::Late_Update(void)
{
}

void CUltimate::Render(HDC& _hDC)
{
	//Rectangle(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);

	Arc(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom, (m_tRC.right / 2), m_tRC.top, (m_tRC.right / 2), m_tRC.top);
}

void CUltimate::Release(void)
{
}
