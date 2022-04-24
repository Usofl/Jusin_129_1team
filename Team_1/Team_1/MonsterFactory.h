#pragma once
#include "Monster.h"
#include "Obj.h"

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

	static CObj* Create_Mon_A(POINT& _tPoint, CObj* _player, int TYPE)
	{

	}

	static CObj* Create_Mon_B()
	{

	}

	static CObj* Create_Mon_C()
	{

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