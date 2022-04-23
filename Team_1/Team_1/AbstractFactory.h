#pragma once

#include"Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory()
	{
	}
	~CAbstractFactory()
	{
	}

public:
	static CObj* Create(void)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*    Create(float fA, float fB)
	{
		CObj*    pObj = new T;
		pObj->Initialize();

		POINT p{ (long)fA, (long)fB };
		pObj->Make_POINT(p);

		return pObj;
	}

	static CObj*    Create(POINT& _tPoint, CObj* _player, int TYPE) // type �߰�
	{
		CObj*    pObj = new T(_player);
		pObj->Initialize();
		dynamic_cast<CMonster*>(pObj)->Set_Mon_Type((MONSTERTYPE)TYPE);

		pObj->Make_POINT(_tPoint);

		return pObj;
	}

	static CObj*    Create(float fA, float fB, float fAngle)
	{
		CObj*    pObj = new T;
		pObj->Initialize();

		POINT p{ (long)fA, (long)fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(fAngle);

		return pObj;
	}
};