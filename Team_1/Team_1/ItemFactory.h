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
	static CObj*    Create_Item_Bullet(const float& _fX, const float& _fY, const float& _fAngle = 45.f)
	{
		CObj*    pObj = new CItem_Bullet();
		pObj->Initialize();

		POINT p{ (long)_fX, (long)_fY };
		pObj->Make_POINT(p);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj*    Create_Item_Shield(const float& _fX, const float& _fY, const float& _fAngle = 45.f)
	{
		CObj*    pObj = new CItem_Shield();
		pObj->Initialize();

		POINT p{ (long)_fX, (long)_fY };
		pObj->Make_POINT(p);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj*    Create_Item_RollBot(const float& _fX, const float& _fY, const float& _fAngle = 45.f)
	{
		CObj*    pObj = new CItem_RollBot();
		pObj->Initialize();

		POINT p{ (long)_fX, (long)_fY };
		pObj->Make_POINT(p);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj*    Create_Item_UltiMate(const float& _fX, const float& _fY, const float& _fAngle = 45.f)
	{
		CObj*    pObj = new CItem_UltiMate();
		pObj->Initialize();

		POINT p{ (long)_fX, (long)_fY };
		pObj->Make_POINT(p);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj*    Create_Item_Guided(const float& _fX, const float& _fY, const float& _fAngle = 45.f)
	{
		CObj*    pObj = new CItem_Guided();
		pObj->Initialize();

		POINT p{ (long)_fX, (long)_fY };
		pObj->Make_POINT(p);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
};

