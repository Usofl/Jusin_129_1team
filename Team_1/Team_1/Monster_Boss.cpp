#include "stdafx.h"
#include "Monster_Boss.h"


CMonster_Boss::CMonster_Boss()
{
}


CMonster_Boss::~CMonster_Boss()
{
}

void CMonster_Boss::Initialize(void)
{
	dwTime = 0;
	dwTime_bullet = 0;
	theta = 0.f;

	m_tInfo.fCX = 10.f * Monster_C;
	m_tInfo.fCY = 10.f * Monster_C;

	m_iHP = 300;

	//m_iReverse = 1;

	m_fSpeed = 13.f;
}

void CMonster_Boss::Update(void)
{
	Move_Monster();

	//���� ����.

	int rand_motion = 0;
	rand_motion = rand() % 100 + 1;

	if (0 < m_iHP)
	{
		if (dwTime_bullet + 500 < GetTickCount())
		{
			//if (Mon_Bulletlist->empty())
			//{
				float m_MonPlr_Angle = 90.f;
				Mon_Bulletlist->push_back(CAbstractFactory<CBulletMonster>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle, MONSTERTYPE_BOSS));// �Ѿ� ������ ���� �ޱ�.
			//}

			dwTime_bullet = GetTickCount();
		}
	}
	
	Update_Rect();
}

void CMonster_Boss::Render(HDC _hDC)
{
	// ������ ����.
	//Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);

	// ������ ������ ����.
	MoveToEx(_hDC, m_tRC.left, m_tRC.top + (m_tRC.bottom - m_tRC.top) * 0.5f, NULL);
	LineTo(_hDC, m_tRC.left + (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f);
	LineTo(_hDC, m_tRC.left + (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + 2.f * (m_tRC.bottom - m_tRC.top) / 3.f);
	LineTo(_hDC, m_tRC.left, m_tRC.top + (m_tRC.bottom - m_tRC.top) * 0.5f);
	MoveToEx(_hDC, m_tRC.left + (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + 2.f * (m_tRC.bottom - m_tRC.top) / 3.f, NULL);
	LineTo(_hDC, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f, m_tRC.bottom);
	LineTo(_hDC, m_tRC.right, m_tRC.bottom);
	LineTo(_hDC, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + 2.f * (m_tRC.bottom - m_tRC.top) / 3.f);
	LineTo(_hDC, m_tRC.right, m_tRC.top + 2.f * (m_tRC.bottom - m_tRC.top) / 3.f);
	LineTo(_hDC, m_tRC.right, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f);
	LineTo(_hDC, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f);
	LineTo(_hDC, m_tRC.right,m_tRC.top);
	LineTo(_hDC, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top);
	LineTo(_hDC, m_tRC.left + (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f);

}

void CMonster_Boss::Release(void)
{
}

void CMonster_Boss::Move_Monster(void)
{
	//1. ������ ���������� �����δ�. 2. ������ ��. �Ѿ�   ��. �� ����(?)  ��. ��ũ��
	//if (((m_tInfo.fY + 0.5f * 10.f * Monster_C) >= (WINCY - GAMESIZE - 10)) || ((m_tInfo.fY - 0.5f * 10.f * Monster_C) <= GAMESIZE + 10))
	if((m_tRC.bottom >= WINCY - GAMESIZE - 10)||(m_tRC.top <= GAMESIZE + 10))
	{
		m_fSpeed *= -1.f;
	}
	//if (((m_tInfo.fX + 0.5f * 10.f * Monster_C) >= (WINCX - GAMESIZE - 10)) || ((m_tInfo.fX - 0.5f * 10.f * Monster_C) <= 50 + GAMESIZE))
	if((m_tRC.right >= (WINCX - GAMESIZE - 10))||(m_tRC.left <= 50 + GAMESIZE))
	{
		m_fSpeed *= -1.f;
	}

	//                              xxxxxxxxxxxxxxxxxxxxxxxx           �߱��� ������ ��� ����......

	//int rand_motion = 0;
	//rand_motion = rand() % 100 + 1;

	//50�� ���Ϸ� ���� ���� �߱���.
	if (100 >= m_iHP)
	{
		int rand_motion = 0;
		rand_motion = rand() % 180 + 1;
		
		m_tInfo.fX -= 0.5f * m_fSpeed * sin (rand_motion);
	}

	// �⺻ ������.
	m_tInfo.fY += 0.15f * m_fSpeed;
}
