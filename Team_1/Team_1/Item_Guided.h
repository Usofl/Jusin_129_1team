#pragma once
#include "Item.h"
class CItem_Guided :
	public CItem
{
public:
	CItem_Guided();
	CItem_Guided(const CItem& _rObj);
	virtual ~CItem_Guided();

	// CItem을(를) 통해 상속됨
	virtual void Render(HDC& _hDC) override;
	virtual void Release(void) override;
	virtual void Pick_Up_Set(void) override;
};

