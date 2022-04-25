#pragma once
#include "Item.h"
class CItem_UltiMate :
	public CItem
{
public:
	CItem_UltiMate();
	CItem_UltiMate(const CItem & _rObj);
	virtual ~CItem_UltiMate();

	// CItem을(를) 통해 상속됨
	virtual void Render(HDC& _hDC) override;
	virtual void Release(void) override;
	virtual void Pick_Up_Set(void) override;
private:
	static int m_GetUlt;
};

