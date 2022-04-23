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
	if (m_TYPE == MONSTERTYPE_B)
	{
		m_tInfo.fX -= m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY += m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}
	else if (m_TYPE == MONSTERTYPE_C)
	{
		if (0.5 * WINCY > m_Ypos)
		{
			m_tInfo.fX -= 0.1*m_fSpeed * 2.5;
			m_tInfo.fY += 0.1*m_fSpeed * 0.1*m_fSpeed * 3;
		}
		else if (0.5 * WINCY < m_Ypos)
		{
			m_tInfo.fX -= 0.1*m_fSpeed * 2.5;
			m_tInfo.fY -= 0.1*m_fSpeed * 0.1*m_fSpeed * 3;
		}
	
	}

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