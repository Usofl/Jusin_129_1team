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

	//보스 공격.

	if (0 < m_iHP)
	{
		if (dwTime_bullet + 1000 < GetTickCount())
		{
			
			//1. 스크류 총알.
			if (200 < m_iHP)
			{
				float m_MonPlr_Angle = 90.f;
				Mon_Bulletlist->push_back(CAbstractFactory<CBulletMonster>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle, MONSTERTYPE_BOSS));// 총알 생성시 난수 받기.
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
	// 보스의 형태.
	//Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);

	// 보스의 진정한 형태.
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
	//불
	Ellipse(_hDC, m_tRC.left + 0.5 * (m_tRC.right - m_tRC.left) + 20.f, m_tRC.top + 3.f * (m_tRC.bottom - m_tRC.top) / 9.f, m_tRC.right - 20.f, m_tRC.top + 4.f * (m_tRC.bottom - m_tRC.top) / 9.f);
	Ellipse(_hDC, m_tRC.left + 0.5 * (m_tRC.right - m_tRC.left) + 20.f, m_tRC.top + 4.f * (m_tRC.bottom - m_tRC.top) / 9.f, m_tRC.right - 20.f, m_tRC.top + 5.f * (m_tRC.bottom - m_tRC.top) / 9.f);
	Ellipse(_hDC, m_tRC.left + 0.5 * (m_tRC.right - m_tRC.left) + 20.f, m_tRC.top + 5.f * (m_tRC.bottom - m_tRC.top) / 9.f, m_tRC.right - 20.f, m_tRC.top + 6.f * (m_tRC.bottom - m_tRC.top) / 9.f);
	//중심부 몸통.
	Rectangle(_hDC, m_tRC.left + (m_tRC.right - m_tRC.left) / 3.f, m_tRC.top + (m_tRC.bottom - m_tRC.top) / 3.f, m_tRC.left + 2.f * (m_tRC.right - m_tRC.left) / 3.f + 30.f, m_tRC.top + 2.f * (m_tRC.bottom - m_tRC.top) / 3.f);
	//중심부 포신 위치.
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
	//1.보스의 움직임 범위 1버전.
	/*if((m_tRC.bottom >= WINCY - GAMESIZE - 10)||(m_tRC.top <= GAMESIZE + 10))
	{
		m_fSpeed *= -1.f;
	}
	if((m_tRC.right >= (WINCX - GAMESIZE - 10))||(m_tRC.left <= 30 + GAMESIZE))
	{
		m_fSpeed *= -1.f;
	}*/
	//1.보스의 움직임 범위 2버전.
	if ((m_tInfo.fY >= WINCY) || (m_tInfo.fY <= 0.f))
	{
		m_fSpeed *= -1.f;
	}
	if ((m_tInfo.fX >= WINCX) || (m_tInfo.fX <= 30.f))
	{
		m_fSpeed *= -1.f;
	}

	//                              xxxxxxxxxxxxxxxxxxxxxxxx           발광시 프레임 벗어남 버그......
	//50피 이하로 내려 가면 발광함.
	if (50 >= m_iHP)
	{
		int rand_motion = 0;
		rand_motion = rand() % 30 + 60;
		
		m_tInfo.fX -= 0.5f * m_fSpeed * sinf ((float)rand_motion);
	}

	// 기본 움직임.
	m_tInfo.fY += 0.15f * m_fSpeed;
}
