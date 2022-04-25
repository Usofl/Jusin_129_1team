#include "stdafx.h"
#include "Item_Bullet.h"

int CItem_Bullet::m_GetBullet = 0;

CItem_Bullet::CItem_Bullet()
	: CItem(ITEM_BULLET)
{
}

CItem_Bullet::CItem_Bullet(const CItem & _rObj)
	: CItem(_rObj)
{
}

CItem_Bullet::~CItem_Bullet()
{
}

void CItem_Bullet::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left - 2, m_tRC.top - 10, m_tRC.right + 1, m_tRC.bottom - 4);
	Rectangle(_hDC, m_tRC.left - 2, m_tRC.top - 2, m_tRC.right + 1, m_tRC.bottom + 1);
	DrawText(_hDC, L"B", 1, &m_tRC, DT_CENTER);
}

void CItem_Bullet::Release(void)
{
}

void CItem_Bullet::Pick_Up_Set(void)
{
	POINT p{ GAMESIZE + m_GetBullet, WINCY - OUTGAMESIZE };
	Make_POINT(p);

	m_GetBullet += 25.f;

	Update_Rect();
}
