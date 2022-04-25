#include "stdafx.h"
#include "Item_UltiMate.h"

int CItem_UltiMate::m_GetUlt = 0;

CItem_UltiMate::CItem_UltiMate()
	: CItem(ITEM_ULTIMATE)
{
}

CItem_UltiMate::CItem_UltiMate(const CItem & _rObj)
	: CItem(_rObj)
{
}

CItem_UltiMate::~CItem_UltiMate()
{
	m_GetUlt -= 25;
}

void CItem_UltiMate::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRC.left - 2, m_tRC.top - 2, m_tRC.right + 1, m_tRC.bottom + 1);
	DrawText(_hDC, L"U", 1, &m_tRC, DT_CENTER);
}

void CItem_UltiMate::Release(void)
{
}

void CItem_UltiMate::Pick_Up_Set(void)
{
	POINT p{ (WINCX - GAMESIZE) - m_GetUlt, WINCY - OUTGAMESIZE };
	Make_POINT(p);

	m_GetUlt += 25;

	Update_Rect();
}
