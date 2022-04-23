#pragma once
#include "Item.h"

class CItemFactory
{
public:
	CItemFactory()
	{
	}

	~CItemFactory()
	{
	}

public:
	static CObj*    Create(const ITEMID& _itemID, const float& fA, const float& fB)
	{
		CObj*    pObj = new CItem(_itemID);
		pObj->Initialize();

		POINT p{ (long)fA, (long)fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(45.f);

		return pObj;
	}
};

