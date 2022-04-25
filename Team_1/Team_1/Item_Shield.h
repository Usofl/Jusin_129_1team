#pragma once
#include "Item.h"
class CItem_Shield :
	public CItem
{
public:
	CItem_Shield();
	CItem_Shield(const CItem & _rObj);
	virtual ~CItem_Shield();

	// CItem을(를) 통해 상속됨
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
	virtual void Pick_Up_Set(void) override;
};

