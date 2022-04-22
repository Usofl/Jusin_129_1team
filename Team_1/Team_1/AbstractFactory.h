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

	static CObj*	Create(float fA,float fB)
	{
		CObj*	pObj = new T;
		pObj->Initialize();

		POINT p;
		p.x = (long)fA;
		p.y = (long)fB;
		pObj->Make_POINT(p);

		return pObj;
	}
};

