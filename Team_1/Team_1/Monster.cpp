#include "stdafx.h"
#include "Monster.h"



CMonster::CMonster()
{
}

CMonster::CMonster(CObj * _player)
	: m_pPlayer(_player)
{
}

CMonster::~CMonster()
{
}

void CMonster::Late_Update(void)
{
	if (m_pPlayer != nullptr)
	{
		if (0 < m_pPlayer->Get_fX() - m_tInfo.fX)
		{
			LONG temp = m_tRC.left;
			m_tRC.left = m_tRC.right;
			m_tRC.right = temp;

			m_iReverse = -1;
		}
		else
		{
			m_iReverse = 1;
		}
	}
}

void CMonster::Render(HDC _hDC)
{
	if (MONSTERTYPE_A == m_MonType)
	{
		Ellipse(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.top + 10, m_tRC.right - (5 * m_iReverse), m_tRC.bottom - 10);

		MoveToEx(_hDC, m_tRC.left, m_tRC.top + 10, nullptr);
		LineTo(_hDC, m_tRC.left + (10 * m_iReverse), m_tRC.top + 10);
		LineTo(_hDC, m_tRC.left + (10 * m_iReverse), m_tRC.top - 7);
		LineTo(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.top - 7);
		LineTo(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.top + 10);

		LineTo(_hDC, m_tRC.right + (5 * m_iReverse), m_tRC.top + 10);
		LineTo(_hDC, m_tRC.right + (10 * m_iReverse), m_tRC.top + 5);
		LineTo(_hDC, m_tRC.right + (10 * m_iReverse), m_tRC.bottom - 5);
		LineTo(_hDC, m_tRC.right + (5 * m_iReverse), m_tRC.bottom - 10);

		LineTo(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.bottom - 10);
		LineTo(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.bottom + 7);
		LineTo(_hDC, m_tRC.left + (10 * m_iReverse), m_tRC.bottom + 7);
		LineTo(_hDC, m_tRC.left + (10 * m_iReverse), m_tRC.bottom - 10);
		LineTo(_hDC, m_tRC.left, m_tRC.bottom - 10);
		LineTo(_hDC, m_tRC.left, m_tRC.top + 10);

	}

	else if (MONSTERTYPE_B == m_MonType)
	{
		Ellipse(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.top, m_tRC.right, m_tRC.bottom - 15);

		MoveToEx(_hDC, m_tRC.left + (22 * m_iReverse), m_tRC.bottom - 15, nullptr);
		LineTo(_hDC, m_tRC.left + (22 * m_iReverse), m_tRC.bottom - 3);
		LineTo(_hDC, m_tRC.left + (15 * m_iReverse), m_tRC.bottom);
		MoveToEx(_hDC, m_tRC.left + (22 * m_iReverse), m_tRC.bottom - 3, nullptr);
		LineTo(_hDC, m_tRC.right, m_tRC.bottom);

		MoveToEx(_hDC, m_tRC.left + (22 * m_iReverse), m_tInfo.fY, nullptr);
		LineTo(_hDC, m_tRC.left + (3 * m_iReverse), m_tInfo.fY);
		MoveToEx(_hDC, m_tRC.left + (22 * m_iReverse), m_tInfo.fY + 5, nullptr);
		LineTo(_hDC, m_tRC.left + (8 * m_iReverse), m_tInfo.fY);
	}

	else if (MONSTERTYPE_C == m_MonType)
	{
		Rectangle(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
	}
}

void CMonster::Release(void)
{
}

void CMonster::Move_Monster(void)
{
	switch (m_MonType)
	{
	case MONSTERTYPE_A:
		// 플레이어를 따라가는 움직임. 몬스터 타입 : A
		if (m_pPlayer != nullptr)
		{
			if (0.5 * PLAYERCX < abs(m_tInfo.fX - m_pPlayer->Get_fX()))
			{
				m_fAngle = Find_MonPlr_CosAngle();
				m_tInfo.fX -= 0.2f * m_fSpeed * cos(m_fAngle);
			}
			if (0.5 * PLAYERCY < abs(m_tInfo.fY - m_pPlayer->Get_fY()))
			{
				m_fAngle = Find_MonPlr_SinAngle();
				m_tInfo.fY -= 0.2f * m_fSpeed * sin(m_fAngle);
			}

			if ((m_tInfo.fY + 0.5*Monster_C) >= (WINCY - GAMESIZE)) // 몬스터가 프레임 밖으로 벗어나지 못하게 함.
			{
				m_tInfo.fY = WINCY - GAMESIZE - 0.5*Monster_C;
			}
			if ((m_tInfo.fY - 0.5*Monster_C) <= GAMESIZE)
			{
				m_tInfo.fY = GAMESIZE + 0.5*Monster_C;
			}
			if ((m_tInfo.fX + 0.5*Monster_C) >= (WINCX - GAMESIZE))
			{
				m_tInfo.fX = WINCX - GAMESIZE - 0.5*Monster_C;
			}
			if ((m_tInfo.fX - 0.5*Monster_C) <= GAMESIZE)
			{
				m_tInfo.fX = GAMESIZE + 0.5*Monster_C;
			}
		}
		break;

	case MONSTERTYPE_B:
		// 오른쪽 화면에서의 이동(총알). 몬스터 타입 : B
		if (((m_tInfo.fY + 0.5*Monster_C) >= (WINCY - GAMESIZE)) || ((m_tInfo.fY - 0.5*Monster_C) <= GAMESIZE))
		{
			m_fSpeed *= -1;
		}
		if (((m_tInfo.fX + 0.5*Monster_C) >= (WINCX - GAMESIZE)) || ((m_tInfo.fX - 0.5*Monster_C) <= 0.5 * WINCX + GAMESIZE))
		{
			m_fSpeed *= -1;
		}

		if (dwTime + 1000 < GetTickCount())
		{
			theta += PI * 0.3;

			dwTime = GetTickCount();
		}

		m_tInfo.fY += 0.15f * m_fSpeed * cos(theta);
		m_tInfo.fX -= 0.15f * m_fSpeed * sin(theta);
		break;

	case MONSTERTYPE_C:
		// 오른쪽 화면에서의 포물선 총알. 몬스터 타입 : C
		if (((m_tInfo.fY + 0.5*Monster_C) >= (WINCY - GAMESIZE)) || ((m_tInfo.fY - 0.5*Monster_C) <= GAMESIZE))
		{
			m_fSpeed *= -1;
		}
		if (((m_tInfo.fX + 0.5*Monster_C) >= (WINCX - GAMESIZE)) || ((m_tInfo.fX - 0.5*Monster_C) <= 0.6 * WINCX))
		{
			m_fSpeed *= -1;
		}

		if (dwTime + 1000 < GetTickCount())
		{
			theta += PI;

			dwTime = GetTickCount();
		}

		if (m_tInfo.fY > 0.5*WINCY)
		{
			m_tInfo.fY -= 0.05f * m_fSpeed * cos(theta);
		}
		if (m_tInfo.fY < 0.5*WINCY)
		{
			m_tInfo.fY += 0.05f * m_fSpeed * cos(theta);
		}
		break;
	}
	
}