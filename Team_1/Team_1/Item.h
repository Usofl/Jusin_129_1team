#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	CItem(const CItem& _rObj);
	CItem(const ITEMID& _itemID);
	virtual ~CItem();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release(void) PURE;

	virtual void Pick_Up_Set(void) PURE;

	inline const ITEMID& Get_Item_ID(void) const { return m_eItemID; }

private:
	ITEMID m_eItemID;
	float m_X_Reverse;
	float m_Y_Reverse;
};

