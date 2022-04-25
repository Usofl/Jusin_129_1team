#include "stdafx.h"
#include "GuiBullet.h"


CGuiBullet::CGuiBullet()
{
}

CGuiBullet::~CGuiBullet()
{
	Release();
}

void CGuiBullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 5.f;

	m_iHP = 1;
}

void CGuiBullet::Update(void)
{
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * DEGREE);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * DEGREE);

	m_tPoint.x = (long)(m_tInfo.fX + m_fSpeed * cosf(m_fBulletAngle * DEGREE));
	m_tPoint.y = (long)(m_tInfo.fY + m_fSpeed * sinf(m_fBulletAngle * DEGREE));

	Update_Rect();
}

void CGuiBullet::Late_Update(void)
{
	if (50 >= m_tRC.left || WINCX - 50 <= m_tRC.right
		|| 50 >= m_tRC.top || WINCY - 50 <= m_tRC.bottom)
	{
		m_iHP = 0;
	}

	for (auto& iter : *m_pMonsterList)
	{
		float fWidth = iter->Get_fX() - m_tInfo.fX;
		float fHeight = iter->Get_fY() - m_tInfo.fY;
		float fDiagonal = Diagonal(fWidth, fHeight);

		if (fDiagonal < 100.f)
		{
			float fRadian = acosf(fWidth / fDiagonal);
			m_fAngle = (fRadian * 180.f) / PI;

			if (iter->Get_fY() > m_tInfo.fY)
				m_fAngle *= -1.f;

			break;
		}
	}
}

void CGuiBullet::Render(HDC _hDC)
{
	Ellipse(_hDC, (int)m_tRC.left, (int)m_tRC.top, (int)m_tRC.right, (int)m_tRC.bottom);

	Rectangle(_hDC, (int)(m_tRC.left - (m_tInfo.fCX * 0.5f)), (int)(m_tRC.top),
		(int)(m_tRC.right - (m_tInfo.fCX * 0.5f)), (int)(m_tRC.bottom));

	Rectangle(_hDC, (int)(m_tRC.left - (m_tInfo.fCX * 0.5f) - 3.f), (int)(m_tRC.top - 1.f),
		(int)(m_tRC.left - (m_tInfo.fCX * 0.5f)), (int)(m_tRC.bottom + 1.f));
}

void CGuiBullet::Release(void)
{
}
