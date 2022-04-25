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
	m_fSpeed = 5.f;
	m_iHP = 1;
}

void CBulletMonster::Update(void)
{
	if (m_TYPE == MONSTERTYPE_B)
	{
		Set_Size(10.f, 4.f);
		m_tInfo.fX -= m_fSpeed * cosf(m_fAngle * DEGREE);
		m_tInfo.fY += m_fSpeed * sinf(m_fAngle * DEGREE);
	}
	else if (m_TYPE == MONSTERTYPE_C)
	{
		Set_Size(15.f, 8.f);
		if (0.5 * WINCY > m_Ypos)
		{
			m_tInfo.fX -= 0.1f * m_fSpeed * 5.f;
			m_tInfo.fY += 0.1f * m_fSpeed * 0.1f * m_fSpeed * 7.f;
		}
		else if (0.5 * WINCY < m_Ypos)
		{
			m_tInfo.fX -= 0.1f * m_fSpeed * 5.f;
			m_tInfo.fY -= 0.1f * m_fSpeed * 0.1f * m_fSpeed * 7.f;
		}
	}
	else if (m_TYPE == MONSTERTYPE_BOSS)
	{
		Set_Size(25.f, 25.f);
		//1. 스크류 총알 나가기.
		m_tInfo.fX -= (m_fSpeed + m_tInfo.fCX * cosf(m_fAngle * DEGREE));
		m_tInfo.fY += m_tInfo.fCY * sinf(m_fAngle * DEGREE);
		m_fAngle += +20.f;

		//2. 3방향 총알 나가기.


	}

	Update_Rect();
}

void CBulletMonster::Late_Update(void)
{
	// 맵 충돌처리
	if (GAMESIZE >= m_tRC.left || WINCX - GAMESIZE <= m_tRC.right
		|| GAMESIZE >= m_tRC.top || WINCY - GAMESIZE <= m_tRC.bottom)
	{
		m_iHP = 0;
	}
}

void CBulletMonster::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);

	// 보스 총알 따로??
}

void CBulletMonster::Release(void)
{
}

void CBulletMonster::Set_Size(const float& fa, const float& fb)  //  또는 총알의 기타 information을 바꿈.(initialiaze안의 변수)
{
	m_tInfo.fCX = fa;
	m_tInfo.fCY = fb;
}
