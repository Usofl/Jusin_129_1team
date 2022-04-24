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

void CMonster::Initialize(void)
{

	m_tInfo.fCX = Monster_C;
	m_tInfo.fCY = Monster_C;

	m_iHP = 2;

	m_fSpeed = 10.f;
}

void CMonster::Update(void)
{
	Move_Monster();      // ���Ͱ� ������.

	//B Ÿ�� ���Ͱ� �Ѿ��� ��. 1�� �ڿ�.
	if (m_MonType == MONSTERTYPE_B)
	{
		if (dwTime_bullet + 1500 < GetTickCount())
		{
			float m_MonPlr_Angle = 0.f;

			Mon_Bulletlist->push_back(CAbstractFactory<CBulletMonster>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle, m_MonType));

			dwTime_bullet = GetTickCount();
		}
	}

	//C Ÿ�� ���Ͱ� �Ѿ��� ��. 3�� �ڿ�.
	if (m_MonType == MONSTERTYPE_C)
	{
		if (dwTime_bullet + 3000 < GetTickCount())
		{
			float m_MonPlr_Angle = 0.f;

			Mon_Bulletlist->push_back(CAbstractFactory<CBulletMonster>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle, m_MonType));

			dwTime_bullet = GetTickCount();
		}
	}

	Update_Rect();
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CMonster::Release(void)
{
}

void CMonster::Move_Monster(void)
{
	switch (m_MonType)
	{
	case MONSTERTYPE_A:
		// �÷��̾ ���󰡴� ������. ���� Ÿ�� : A
		
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

		if ((m_tInfo.fY + 0.5*Monster_C) >= (WINCY - GAMESIZE)) // ���Ͱ� ������ ������ ����� ���ϰ� ��.
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
		break;

	case MONSTERTYPE_B:
		// ������ ȭ�鿡���� �̵�(�Ѿ�). ���� Ÿ�� : B
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
		// ������ ȭ�鿡���� ������ �Ѿ�. ���� Ÿ�� : C
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

float CMonster::Find_MonPlr_CosAngle(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;
	
	fXX = m_tInfo.fX - (*m_pPlayer).Get_fX();
	fYY = m_tInfo.fY - (*m_pPlayer).Get_fY();

	fAngle = acos(fXX / sqrtf(fXX*fXX + fYY*fYY));

	return fAngle;
}

float CMonster::Find_MonPlr_SinAngle(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;

	fXX = m_tInfo.fX - (*m_pPlayer).Get_fX();
	fYY = m_tInfo.fY - (*m_pPlayer).Get_fY();

	fAngle = asin(fYY / sqrtf(fXX*fXX + fYY*fYY));

	return fAngle;
}