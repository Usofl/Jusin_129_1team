#pragma once
#include "Monster.h"
#include "MONSTER_A.h"
#include "Monster_B.h"
#include "Monster_C.h"
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
	static CObj* Create_Mon_BOSS()
	{

	}

	static CObj* Create_Mon_A(POINT& _tPoint, CObj* _player)
	{
		CObj*    pObj = new CMonster_A(_player);
		pObj->Initialize();
		pObj->Make_POINT(_tPoint);
		static_cast<CMonster_A*>(pObj)->Initialize();

		return pObj;
	}

	static CObj* Create_Mon_B(POINT& _tPoint, CObj* _player)
	{
		CObj*    pObj = new CMonster_B;
		pObj->Initialize();
		pObj->Make_POINT(_tPoint);
		static_cast<CMonster_B*>(pObj)->Initialize();

		return pObj;
	}

	static CObj* Create_Mon_C(POINT& _tPoint, CObj* _player)
	{
		CObj*    pObj = new CMonster_C;
		pObj->Initialize();
		pObj->Make_POINT(_tPoint);
		static_cast<CMonster_C*>(pObj)->Initialize();

		return pObj;
	}
};

// 참고용.
//static CObj*    Create(POINT& _tPoint, CObj* _player, int TYPE) // type 추가
//{
//	CObj*    pObj = new T(_player);
//	pObj->Initialize();
//	dynamic_cast<CMonster*>(pObj)->Set_Mon_Type((MONSTERTYPE)TYPE);
//
//	pObj->Make_POINT(_tPoint);
//
//	return pObj;
//}