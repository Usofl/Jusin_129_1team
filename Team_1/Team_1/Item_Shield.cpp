#include "stdafx.h"
#include "Item_Shield.h"


CItem_Shield::CItem_Shield()
	: CItem(ITEM_SHIELD)
{
}

CItem_Shield::CItem_Shield(const CItem & _rObj)
	: CItem(_rObj)
{
}


CItem_Shield::~CItem_Shield()
{
}

void CItem_Shield::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left - 2, m_tRC.top - 2, m_tRC.right + 1, m_tRC.bottom + 1);
	DrawText(_hDC, L"S", 1, &m_tRC, DT_CENTER);
}

void CItem_Shield::Release(void)
{
}

void CItem_Shield::Pick_Up_Set(void)
{
}
