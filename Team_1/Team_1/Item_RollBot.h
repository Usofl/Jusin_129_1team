#pragma once
#include "Item.h"
class CItem_RollBot :
	public CItem
{
public:
	CItem_RollBot();
	CItem_RollBot(const CItem & _rObj);
	virtual ~CItem_RollBot();

	// CItem��(��) ���� ��ӵ�
	virtual void Render(HDC& _hDC) override;
	virtual void Release(void) override;
	virtual void Pick_Up_Set(void) override;
};

