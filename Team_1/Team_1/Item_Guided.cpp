#include "stdafx.h"
#include "Item_Guided.h"


CItem_Guided::CItem_Guided()
	: CItem(ITEM_GUIDED)
{
}

CItem_Guided::CItem_Guided(const CItem & _rObj)
	: CItem(_rObj)
{
}


CItem_Guided::~CItem_Guided()
{
}

void CItem_Guided::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left - 2, m_tRC.top - 10, m_tRC.right + 1, m_tRC.bottom + 5);
	DrawText(_hDC, L"G", 1, &m_tRC, DT_CENTER);
}

void CItem_Guided::Release(void)
{
}

void CItem_Guided::Pick_Up_Set(void)
{
	POINT p{ (WINCX * 0.5f - 15), WINCY - OUTGAMESIZE };
	Make_POINT(p);

	Update_Rect();
}