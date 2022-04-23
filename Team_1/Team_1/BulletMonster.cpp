#include "stdafx.h"
#include "BulletMonster.h"


CBulletMonster::CBulletMonster()
{
}

CBulletMonster::~CBulletMonster()
{
}

void CBulletMonster::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 5.f;
	m_iHP = 1;
}

void CBulletMonster::Update(void)
{
	m_tInfo.fX -= m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY += m_fSpeed * sinf((m_fAngle * PI) / 180.f);

	Update_Rect();
}

void CBulletMonster::Late_Update(void)
{
	// ¸Ê Ãæµ¹Ã³¸®
	if (50 >= m_tRC.left || WINCX - 50 <= m_tRC.right
		|| 50 >= m_tRC.top || WINCY - 50 <= m_tRC.bottom)
	{
		m_iHP = 0;
	}
}

void CBulletMonster::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CBulletMonster::Release(void)
{
}