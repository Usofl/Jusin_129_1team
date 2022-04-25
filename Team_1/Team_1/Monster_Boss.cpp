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

	m_fSpeed = 10.f;
}

void CMonster_Boss::Update(void)
{
	Move_Monster();

	//���� ����.

	if (0 < m_iHP)
	{
		if (dwTime_bullet + 1000 < GetTickCount())
		{
			
			//1. ��ũ�� �Ѿ�.
			if (200 < m_iHP)
			{
				float m_MonPlr_Angle = 90.f;
				Mon_Bulletlist->push_back(CAbstractFactory<CBulletMonster>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle, MONSTERTYPE_BOSS));// �Ѿ� ������ ���� �ޱ�.
			}
			else if ((200 >= m_iHP)&&(50 < m_iHP))
			{
				float m_MonPlr_Angle = 0.f;
				Mon_Bulletlist->push_back(CAbstractFactory<CBulletMonster>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle, MONSTERTYPE_BOSS));
			}
			

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
	LineTo(_hDC, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f + 30.f, m_tRC.top + 2.f * (m_tRC.bottom - m_tRC.top) / 3.f);
	//LineTo(_hDC, m_tRC.right, m_tRC.top + 2.f * (m_tRC.bottom - m_tRC.top) / 3.f);
	//LineTo(_hDC, m_tRC.right, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f);

	//LineTo(_hDC, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f);

	MoveToEx(_hDC, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f + 30.f, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f,nullptr);
	LineTo(_hDC, m_tRC.right,m_tRC.top);
	LineTo(_hDC, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top);
	LineTo(_hDC, m_tRC.left + (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f);
	//��
	Ellipse(_hDC, m_tRC.left + 0.5 * (m_tRC.right - m_tRC.left) + 20.f, m_tRC.top + 3.f * (m_tRC.bottom - m_tRC.top) / 9.f, m_tRC.right - 20.f, m_tRC.top + 4.f * (m_tRC.bottom - m_tRC.top) / 9.f);
	Ellipse(_hDC, m_tRC.left + 0.5 * (m_tRC.right - m_tRC.left) + 20.f, m_tRC.top + 4.f * (m_tRC.bottom - m_tRC.top) / 9.f, m_tRC.right - 20.f, m_tRC.top + 5.f * (m_tRC.bottom - m_tRC.top) / 9.f);
	Ellipse(_hDC, m_tRC.left + 0.5 * (m_tRC.right - m_tRC.left) + 20.f, m_tRC.top + 5.f * (m_tRC.bottom - m_tRC.top) / 9.f, m_tRC.right - 20.f, m_tRC.top + 6.f * (m_tRC.bottom - m_tRC.top) / 9.f);
	//�߽ɺ� ����.
	Rectangle(_hDC, m_tRC.left + (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f + 30.f, m_tRC.top + 2.f * (m_tRC.bottom - m_tRC.top) / 3.f);
	//�߽ɺ� ���� ��ġ.
	MoveToEx(_hDC, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + 2.f * (m_tRC.bottom - m_tRC.top) / 3.f, NULL);
	LineTo(_hDC, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f);

	Rectangle(_hDC, m_tRC.left + 0.5 * (m_tRC.right - m_tRC.left), m_tRC.top + 0.5 * (m_tRC.bottom - m_tRC.top) - (m_tRC.bottom - m_tRC.top) / 36.f, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + 0.5 * (m_tRC.bottom - m_tRC.top) + (m_tRC.bottom - m_tRC.top) / 36.f);
	Ellipse(_hDC, m_tRC.left + 0.5 * (m_tRC.right - m_tRC.left) - (m_tRC.right - m_tRC.left) / 36.f, m_tRC.top + 0.5 * (m_tRC.bottom - m_tRC.top) - (m_tRC.bottom - m_tRC.top) / 36.f, m_tRC.left + 0.5 * (m_tRC.right - m_tRC.left) + (m_tRC.right - m_tRC.left) / 36.f, m_tRC.top + 0.5 * (m_tRC.bottom - m_tRC.top) + (m_tRC.bottom - m_tRC.top) / 36.f);



}

void CMonster_Boss::Release(void)
{
}

void CMonster_Boss::Move_Monster(void)
{
	//1.������ ������ ���� 1����.
	/*if((m_tRC.bottom >= WINCY - GAMESIZE - 10)||(m_tRC.top <= GAMESIZE + 10))
	{
		m_fSpeed *= -1.f;
	}
	if((m_tRC.right >= (WINCX - GAMESIZE - 10))||(m_tRC.left <= 30 + GAMESIZE))
	{
		m_fSpeed *= -1.f;
	}*/
	//1.������ ������ ���� 2����.
	if ((m_tInfo.fY >= WINCY) || (m_tInfo.fY <= 0.f))
	{
		m_fSpeed *= -1.f;
	}
	if ((m_tInfo.fX >= WINCX) || (m_tInfo.fX <= 30.f))
	{
		m_fSpeed *= -1.f;
	}

	//                              xxxxxxxxxxxxxxxxxxxxxxxx           �߱��� ������ ��� ����......
	//50�� ���Ϸ� ���� ���� �߱���.
	if (50 >= m_iHP)
	{
		int rand_motion = 0;
		rand_motion = rand() % 30 + 60;
		
		m_tInfo.fX -= 0.5f * m_fSpeed * sinf ((float)rand_motion);
	}

	// �⺻ ������.
	m_tInfo.fY += 0.15f * m_fSpeed;
}
