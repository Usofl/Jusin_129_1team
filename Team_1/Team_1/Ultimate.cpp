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
	m_tInfo.fCX = ULTCX;
	m_tInfo.fCY = ULTCY;

	m_tInfo.fX = ULT_START_X;
	m_tInfo.fY = ULT_START_Y;

	m_fSpeed = 10.f;
	m_iHP = 65;
}

void CUltimate::Update(void)
{
	Update_Rect();
	m_tInfo.fX += m_fSpeed;
	--m_iHP;
}

void CUltimate::Late_Update(void)
{
}

void CUltimate::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CUltimate::Release(void)
{
}
