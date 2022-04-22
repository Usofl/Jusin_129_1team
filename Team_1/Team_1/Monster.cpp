#include "stdafx.h"
#include "Monster.h"



CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{

	m_tInfo.fCX = Monster_C;
	m_tInfo.fCY = Monster_C;

	m_fSpeed = 10.f;
}

void CMonster::Update(void)
{
	Move_Monster();

	Update_Rect();
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CMonster::Release(void)
{
}

void CMonster::Move_Monster(void)
{
	m_fAngle = Find_MonPlr_CosAngle();
	m_tInfo.fX -= 0.2 * m_fSpeed * cos(m_fAngle);
	m_fAngle = Find_MonPlr_SinAngle();
	m_tInfo.fY -= 0.2 * m_fSpeed * sin(m_fAngle);
}

float CMonster::Find_MonPlr_CosAngle(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;
	
	fXX = m_tInfo.fX - (*m_pPlayer2).Get_fX();
	fYY = m_tInfo.fY - (*m_pPlayer2).Get_fY();

	fAngle = acos(fXX / sqrtf(fXX*fXX + fYY*fYY));

	return fAngle;
}

float CMonster::Find_MonPlr_SinAngle(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;

	fXX = m_tInfo.fX - (*m_pPlayer2).Get_fX();
	fYY = m_tInfo.fY - (*m_pPlayer2).Get_fY();

	fAngle = asin(fYY / sqrtf(fXX*fXX + fYY*fYY));

	return fAngle;
}
