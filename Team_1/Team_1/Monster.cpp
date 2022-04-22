#include "stdafx.h"
#include "Monster.h"
#include "Player.h"


CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{

	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 10.f;
}

void CMonster::Update(void)
{
	Update_Rect();


}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC _hdc)
{
	Rectangle(_hdc, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CMonster::Release(void)
{
}

void CMonster::Move_Monster(void)
{

}
