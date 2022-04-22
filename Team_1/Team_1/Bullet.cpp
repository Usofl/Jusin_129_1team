#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	// 총알 크기, 스피드, 체력 초기화
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
	m_iHP = 1;

	m_tInfo.fX = 100;
	m_tInfo.fY = 300;

}

void CBullet::Update(void)
{
	if (!m_iHP)
	{
		// 총알 없애는 처리
	}

	// 총알 위치 업데이트 (포신 끝 방향)

	Update_Rect();
}

void CBullet::Late_Update(void)
{
	// 총알 충돌 처리
}

void CBullet::Render(HDC _hdc)
{
	// 원 그리기
	Ellipse(_hdc, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CBullet::Release(void)
{
}

void CBullet::Update_Rect(void)
{
	m_tRC.left = (long)m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRC.top = (long)m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRC.right = (long)m_tInfo.fCX + (m_tInfo.fCX * 0.5f);
	m_tRC.bottom = (long)m_tInfo.fCY + (m_tInfo.fCY * 0.5f);
}
