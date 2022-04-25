#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(BULLETTYPE _eType)
	:m_BulletType(_eType)
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

	switch (m_BulletType)
	{
	case BULLETTYPE_DEFULT:
		m_tPoint.x = (long)(m_tInfo.fX + m_fSpeed * cosf(m_fBulletAngle * DEGREE));
		m_tPoint.y = (long)(m_tInfo.fY + m_fSpeed * sinf(m_fBulletAngle * DEGREE));
		break;

	case BULLETTYPE_SCREW:
		m_tPoint.x = (long)(m_tInfo.fX + 20 * cosf(m_fBulletAngle * DEGREE));
		m_tPoint.y = (long)(m_tInfo.fY - 20 * sinf(m_fBulletAngle * DEGREE));
		m_fBulletAngle += 5.f;
		break;
	}

	Update_Rect();
}

void CBullet::Late_Update(void)
{
	// 맵 충돌처리
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

	switch (m_BulletType)
	{
	case BULLETTYPE_DEFULT:
		break;

	case BULLETTYPE_SCREW:
		m_tRC.left = LONG(m_tPoint.x - (m_tInfo.fCX * 0.5f));
		m_tRC.top = LONG(m_tPoint.y - (m_tInfo.fCY * 0.5f));
		m_tRC.right = LONG(m_tPoint.x + (m_tInfo.fCX * 0.5f));
		m_tRC.bottom = LONG(m_tPoint.y + (m_tInfo.fCY * 0.5f));
		break;
	}

	Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
	Rectangle(_hDC, m_tRC.left - (int)(m_tInfo.fCX * 0.5f), m_tRC.top, m_tRC.right - (int)(m_tInfo.fCX * 0.5f), m_tRC.bottom);
	Rectangle(_hDC, m_tRC.left - (int)(m_tInfo.fCX * 0.5f) - 3, m_tRC.top - 1, m_tRC.left - (int)(m_tInfo.fCX * 0.5f), m_tRC.bottom + 1);
}

void CBullet::Release(void)
{
}
