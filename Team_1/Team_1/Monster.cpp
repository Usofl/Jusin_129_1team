#include "stdafx.h"
#include "Monster.h"



CMonster::CMonster()
{
}

CMonster::CMonster(CObj * _player)
	: m_pPlayer2(_player)
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
	int m_dwTime = 0;
	//���Ͱ� �Ѿ��� ��. 1�� �ڿ�.
	if (m_dwTime + 1000 < GetTickCount())
	{
		Move_Mon_Bullet();
	
		m_dwTime = GetTickCount();
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
		// �÷��̾ ���󰡴� ������(����..?). ���� Ÿ�� : A
		if (0.6 * PLAYERCX < abs(m_tInfo.fX - m_pPlayer2->Get_fX()))
		{
			m_fAngle = Find_MonPlr_CosAngle();
			m_tInfo.fX -= 0.2 * m_fSpeed * cos(m_fAngle);
		}
		if (0.6 * PLAYERCY < abs(m_tInfo.fY - m_pPlayer2->Get_fY()))
		{
			m_fAngle = Find_MonPlr_SinAngle();
			m_tInfo.fY -= 0.2 * m_fSpeed * sin(m_fAngle);
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

		m_tInfo.fY += 0.15 * m_fSpeed * cos(theta);
		m_tInfo.fX -= 0.15 * m_fSpeed * sin(theta);
		break;
	}

	//   �÷��̾ ���� �� ������ ������.
	/*if (m_pPlayer2 == nullptr)
	{
		if (m_tInfo.fX < 600)
		{
			m_tInfo.fX += 100;
			m_tInfo.fY -= 100 * sin((10 * PI) / 180);
		}
	}*/
}

float CMonster::Find_MonPlr_CosAngle(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;
	
	fXX = m_tInfo.fX - (*m_pPlayer2).Get_fX();
	fYY = m_tInfo.fY - (*m_pPlayer2).Get_fY();

	fAngle = acos(fXX / sqrtf(fXX*fXX + fYY*fYY));

	return fAngle;
}

float CMonster::Find_MonPlr_SinAngle(void)
{
	float fAngle;
	float fXX = 0.f, fYY = 0.f;

	fXX = m_tInfo.fX - (*m_pPlayer2).Get_fX();
	fYY = m_tInfo.fY - (*m_pPlayer2).Get_fY();

	fAngle = asin(fYY / sqrtf(fXX*fXX + fYY*fYY));

	return fAngle;
}

void CMonster::Move_Mon_Bullet(void)
{
	//���Ͱ� �Ѿ��� ����.(1. �Ѿ��� ���� ��ġ���� 2. �׸���)
	//�Ѿ��� �÷��̾� ���⸸ ����.(1. ���⺯ȯ�� ����: ��. �÷��̾� ���� ��ǥ 1���� ����)
	//�Ѿ� ������ ���� ���Ȱ�->��׸����� �ٲٱ�.
	
	/*float m_MonPlr_Angle =0.f;

	if (m_MonPlr_Angle == 0.f)
	{
		m_MonPlr_Angle = Find_MonPlr_CosAngle() * 180 / PI;
	}

	if (m_MonType == MONSTERTYPE_B)
	{
		Mon_Bulletlist->push_back(CAbstractFactory<CBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle));
		for (auto& iter : (*Mon_Bulletlist))
		{
			iter->Update();
		}
	}*/

}

