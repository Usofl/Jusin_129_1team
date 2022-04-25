#pragma once
#include "Item.h"
#include "Item_Bullet.h"
#include "Item_Shield.h"
#include "Item_RollBot.h"
#include "Item_UltiMate.h"
#include "Item_Guided.h"

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
	static CObj*    Create_Item_Bullet(const float& fA, const float& fB)
	{
		CObj*    pObj = new CItem_Bullet();
		pObj->Initialize();

		POINT p{ (long)fA, (long)fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(45.f);

		return pObj;
	}

	static CObj*    Create_Item_Shield(const float& fA, const float& fB)
	{
		CObj*    pObj = new CItem_Shield();
		pObj->Initialize();

		POINT p{ (long)fA, (long)fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(45.f);

		return pObj;
	}

	static CObj*    Create_Item_RollBot(const float& fA, const float& fB)
	{
		CObj*    pObj = new CItem_RollBot();
		pObj->Initialize();

		POINT p{ (long)fA, (long)fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(45.f);

		return pObj;
	}

	static CObj*    Create_Item_UltiMate(const float& fA, const float& fB)
	{
		CObj*    pObj = new CItem_UltiMate();
		pObj->Initialize();

		POINT p{ (long)fA, (long)fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(45.f);

		return pObj;
	}

	static CObj*    Create_Item_Guided(const float& fA, const float& fB)
	{
		CObj*    pObj = new CItem_Guided();
		pObj->Initialize();

		POINT p{ (long)fA, (long)fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(45.f);

		return pObj;
	}
};

