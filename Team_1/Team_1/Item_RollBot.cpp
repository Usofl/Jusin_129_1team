#include "stdafx.h"
#include "Item_RollBot.h"


CItem_RollBot::CItem_RollBot()
	: CItem(ITEM_ROLLBOT)
{
}

CItem_RollBot::CItem_RollBot(const CItem & _rObj)
	: CItem(_rObj)
{
}


CItem_RollBot::~CItem_RollBot()
{
}

void CItem_RollBot::Render(HDC& _hDC)
{
	Ellipse(_hDC, m_tRC.left - 2, m_tRC.top - 2, m_tRC.right + 1, m_tRC.bottom + 1);
	DrawText(_hDC, L"R", 1, &m_tRC, DT_CENTER);
}

void CItem_RollBot::Release(void)
{
}

void CItem_RollBot::Pick_Up_Set(void)
{
}
