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

	//static CObj*    Create(POINT& _tPoint, CObj* _player, int TYPE) // type 추가
	//{
	//	CObj*    pObj = new T(_player);
	//	pObj->Initialize();
	//	dynamic_cast<CMonster*>(pObj)->Set_Mon_Type((MONSTERTYPE)TYPE);

	//	pObj->Make_POINT(_tPoint);

	//	return pObj;
	//}

	static CObj* Create(float fA, float fB, float fAngle)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		POINT p{ (long)fA, (long)fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(fAngle);

		return pObj;
	}

	// 총알 생성
	static CObj* Create_Bullet(float _fA, float _fB, float _fAngle)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		POINT p{ (long)_fA, (long)_fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	// 유도탄 생성
	static CObj* Create_Bullet(float _fA, float _fB, float _fAngle, std::list<CObj*>* _pMonsterList)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		POINT p{ (long)_fA, (long)_fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(_fAngle);
		static_cast<CGuiBullet*>(pObj)->Set_MonsterList(_pMonsterList);

		return pObj;
	}

	static CObj*    Create(float fA, float fB, float fAngle, MONSTERTYPE _type)
	{
		CObj*    pObj = new T;
		pObj->Initialize();

		POINT p{ (long)fA, (long)fB };
		pObj->Make_POINT(p);
		pObj->Set_Angle(fAngle);
		static_cast<CBulletMonster*>(pObj)->Set_Monster_Type(_type);
		static_cast<CBulletMonster*>(pObj)->Set_Monster_FirstYPos(fB);

		return pObj;
	}
};