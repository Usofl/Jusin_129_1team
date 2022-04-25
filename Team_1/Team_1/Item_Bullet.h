#pragma once
#include "Item.h"
class CItem_Bullet :
	public CItem
{
public:
	CItem_Bullet();
	CItem_Bullet(const CItem& _rObj);
	virtual ~CItem_Bullet();

	// CItem��(��) ���� ��ӵ�
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
	virtual void Pick_Up_Set(void) override;

private:
	static int m_GetBullet;
};

