#pragma once
#include "Monster.h"
#include "MONSTER_A.h"
#include "Monster_B.h"
#include "Monster_C.h"
#include "Monster_Boss.h"
#include "Obj.h"

//template<typename T>
class CMonsterFactory
{
public:

	CMonsterFactory()
	{
	}

	~CMonsterFactory()
	{
	}

public:
	static CObj* Create_Mon_BOSS(CObj*& _player)
	{
		CObj*    pObj = new CMonster_Boss;
		pObj->Initialize();
		POINT p = {};
		p.x = (LONG)(WINCX - GAMESIZE - 170);
		p.y = (LONG)(0.5 * WINCY);
		pObj->Make_POINT(p);
		static_cast<CMonster_Boss*>(pObj)->Initialize();

		return pObj;
	}

	static CObj* Create_Mon_A(POINT& _tPoint, CObj*& _player)
	{
		CObj*    pObj = new CMonster_A(_player);
		pObj->Initialize();
		pObj->Make_POINT(_tPoint);
		static_cast<CMonster_A*>(pObj)->Initialize();

		return pObj;
	}

	static CObj* Create_Mon_B(POINT& _tPoint, CObj*& _player)
	{
		CObj*    pObj = new CMonster_B;
		pObj->Initialize();
		pObj->Make_POINT(_tPoint);
		static_cast<CMonster_B*>(pObj)->Initialize();

		return pObj;
	}

	static CObj* Create_Mon_C(POINT& _tPoint, CObj*& _player)
	{
		CObj*    pObj = new CMonster_C;
		pObj->Initialize();
		pObj->Make_POINT(_tPoint);
		static_cast<CMonster_C*>(pObj)->Initialize();

		return pObj;
	}
};