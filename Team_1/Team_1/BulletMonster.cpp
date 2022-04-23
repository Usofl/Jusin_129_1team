#include "stdafx.h"
#include "BulletMonster.h"


CBulletMonster::CBulletMonster()
{
}

CBulletMonster::~CBulletMonster()
{
}

void CBulletMonster::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 5.f;
	m_iHP = 1;
}

void CBulletMonster::Update(void)
{
	m_tInfo.fX -= m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY += m_fSpeed * sinf((m_fAngle * PI) / 180.f);

	Update_Rect();
}

void CBulletMonster::Late_Update(void)
{
	// 맵 충돌처리
	if (50 >= m_tRC.left || WINCX - 50 <= m_tRC.right
		|| 50 >= m_tRC.top || WINCY - 50 <= m_tRC.bottom)
	{
		m_iHP = 0;
	}
}

void CBulletMonster::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CBulletMonster::Release(void)
{
}


//void CMonster::Move_Mon_Bullet(void)
//{
//	//몬스터가 총알을 생성.(1. 총알이 몬스터 위치얻음 2. 그리기)
//	//총알이 플레이어 방향만 얻어옴.(1. 방향변환은 없음: ㄱ. 플레이어 순간 좌표 1번만 대입)
//	//총알 생성시 각도 라디안각->디그리각도 바꾸기.
//
//	/*float m_MonPlr_Angle =0.f;
//
//	if (m_MonPlr_Angle == 0.f)
//	{
//	m_MonPlr_Angle = Find_MonPlr_CosAngle() * 180 / PI;
//	}
//
//	if (m_MonType == MONSTERTYPE_B)
//	{
//	Mon_Bulletlist->push_back(CAbstractFactory<CBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle));
//	for (auto& iter : (*Mon_Bulletlist))
//	{
//	iter->Update();
//	}
//	}*/
//
//}