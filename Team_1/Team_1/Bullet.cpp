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
}

void CBullet::Update(void)
{
	m_tInfo.fX += m_fSpeed;
	m_tInfo.fY += m_fSpeed;

	Update_Rect();
}

void CBullet::Late_Update(void)
{
	// 총알 충돌 처리 
}

void CBullet::Render(HDC _hDC)
{
	// 총알 그리기
	Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CBullet::Release(void)
{
}
