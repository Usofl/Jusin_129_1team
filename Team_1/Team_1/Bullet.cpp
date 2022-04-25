#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 5.f;
	m_iHP = 1;

	m_fBulletAngle = 0.f;
}

void CBullet::Update(void)
{
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * DEGREE);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * DEGREE);

	m_tPoint.x = (long)(m_tInfo.fX + m_fSpeed * cosf(m_fBulletAngle * DEGREE));
	m_tPoint.y = (long)(m_tInfo.fY + m_fSpeed * sinf(m_fBulletAngle * DEGREE));

	Update_Rect();
}

void CBullet::Late_Update(void)
{
	if (50 >= m_tRC.left || WINCX - 50 <= m_tRC.right
		|| 50 >= m_tRC.top || WINCY - 50 <= m_tRC.bottom)
	{
		m_iHP = 0;
	}
}

void CBullet::Render(HDC _hDC)
{
	// 총알 테스트용
	/*MoveToEx(_hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(_hDC, m_tPoint.x, m_tPoint.y);*/

	Ellipse(_hDC, (int)m_tRC.left, (int)m_tRC.top, (int)m_tRC.right, (int)m_tRC.bottom);

	Rectangle(_hDC, (int)(m_tRC.left - (m_tInfo.fCX * 0.5f)), (int)(m_tRC.top),
		(int)(m_tRC.right - (m_tInfo.fCX * 0.5f)), (int)(m_tRC.bottom));

	Rectangle(_hDC, (int)(m_tRC.left - (m_tInfo.fCX * 0.5f) - 3.f), (int)(m_tRC.top - 1.f),
		(int)(m_tRC.left - (m_tInfo.fCX * 0.5f)), (int)(m_tRC.bottom + 1.f));
}

void CBullet::Release(void)
{
}
