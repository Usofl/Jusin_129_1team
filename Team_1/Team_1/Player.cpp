#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = PLAYER_START_X;
	m_tInfo.fY = PLAYER_START_Y;

	m_tInfo.fCX = PLAYERCX;
	m_tInfo.fCY = PLAYERCY;

	m_fSpeed = 7.f;

	m_fBSize = 50.f;

	m_iHP = 100;

	m_tPoint.x = (long)(m_tInfo.fX + m_fBSize * cosf((m_fAngle * PI) / 180.f));
	m_tPoint.y = (long)(m_tInfo.fY - m_fBSize * sinf((m_fAngle * PI) / 180.f));
}

void CPlayer::Update(void)
{
	Key_Input();

	Update_Rect();
}

void CPlayer::Late_Update(void)
{
	m_tPoint.x = (long)(m_tInfo.fX + m_fBSize * cosf((m_fAngle * PI) / 180.f));
	m_tPoint.y = (long)(m_tInfo.fY - m_fBSize * sinf((m_fAngle * PI) / 180.f));
}

void CPlayer::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);

	MoveToEx(_hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(_hDC, (int)m_tPoint.x, (int)m_tPoint.y);
}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / nLog;
			m_tInfo.fY -= m_fSpeed / nLog;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / nLog;
			m_tInfo.fY += m_fSpeed / nLog;
		}
		else
		{
			m_tInfo.fX -= m_fSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / nLog;
			m_tInfo.fY -= m_fSpeed / nLog;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / nLog;
			m_tInfo.fY += m_fSpeed / nLog;
		}
		else
		{
			m_tInfo.fX += m_fSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}

	if (GetAsyncKeyState('W'))
	{
		if (8 <= m_fAngle)
		{
			m_fAngle = 8.f;
		}
		else
		{
			m_fAngle += 1.f;
		}
	}

	if (GetAsyncKeyState('S'))
	{
		if (-8 >= m_fAngle)
		{
			m_fAngle = -8.f;
		}
		else
		{
			m_fAngle -= 1.f;
		}
	}

	if (GetAsyncKeyState('D'))
	{
		m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPoint.x, (float)m_tPoint.y, m_fAngle));
	}
}
