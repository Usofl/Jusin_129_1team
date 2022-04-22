#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 7.f;

	m_fBSize = 50.f;
}

void CPlayer::Update(void)
{
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC _hdc)
{
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
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}

		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
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
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}

		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
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
		if (10 <= m_fAngle)
		{
			m_fAngle = 10.f;
		}
		else
		{
			m_fAngle += 2.f;
		}
	}

	if (GetAsyncKeyState('S'))
	{
		if (-10 >= m_fAngle)
		{
		m_fAngle = -10.f;
		}
		else
		{
			m_fAngle -= 2.f;
		}
	}
}
