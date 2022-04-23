#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	: m_dwTime(GetTickCount())
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
	// �Ϲ� �Ѿ� �̵�ó��
	/*m_tInfo.fX += m_fSpeed * cosf(m_fAngle * DEGREE);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * DEGREE);*/

	// ��ũ�� �Ѿ� �̵�ó��
	/*m_tInfo.fX += m_fSpeed * cosf(m_fAngle * DEGREE);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * DEGREE);
	m_tPoint.x = (long)(m_tInfo.fX + 20 * cosf(m_fBulletAngle * DEGREE));
	m_tPoint.y = (long)(m_tInfo.fY - 20 * sinf(m_fBulletAngle * DEGREE));
	m_fBulletAngle += 5.f;*/

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * DEGREE);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * DEGREE);
	m_tPoint.x = (long)(m_tInfo.fX + 20 * cosf(m_fBulletAngle * DEGREE));
	m_tPoint.y = (long)(m_tInfo.fY + 20 * sinf(m_fBulletAngle * DEGREE));

	Update_Rect();
}

void CBullet::Late_Update(void)
{
	// �� �浹ó��
	if (50 >= m_tRC.left || WINCX - 50 <= m_tRC.right
		|| 50 >= m_tRC.top || WINCY - 50 <= m_tRC.bottom)
	{
		m_iHP = 0;
	}
}

void CBullet::Render(HDC _hDC)
{
	if (m_dwTime + 50 < GetTickCount())
	{
		// �Ѿ� �׽�Ʈ��
		/*MoveToEx(_hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
		LineTo(_hDC, m_tPoint.x, m_tPoint.y);*/

		// ��ũ�� �Ѿ�
		/*m_tRC.left = LONG(m_tPoint.x - (m_tInfo.fCX * 0.5f));
		m_tRC.top = LONG(m_tPoint.y - (m_tInfo.fCY * 0.5f));
		m_tRC.right = LONG(m_tPoint.x + (m_tInfo.fCX * 0.5f));
		m_tRC.bottom = LONG(m_tPoint.y + (m_tInfo.fCY * 0.5f));

		Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);*/

		m_tRC.left = LONG(m_tPoint.x - (m_tInfo.fCX * 0.5f));
		m_tRC.top = LONG(m_tPoint.y - (m_tInfo.fCY * 0.5f));
		m_tRC.right = LONG(m_tPoint.x + (m_tInfo.fCX * 0.5f));
		m_tRC.bottom = LONG(m_tPoint.y + (m_tInfo.fCY * 0.5f));

		// �Ϲ� �Ѿ�
		Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);

		m_dwTime = GetTickCount();
	}
}

void CBullet::Release(void)
{
}
