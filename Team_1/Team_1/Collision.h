#pragma once
#include "Obj.h"

class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static bool		Check_Sphere(CObj* pDest, CObj* pSour);
	static void		Collision_Rect(std::list<CObj*> _Dest, std::list<CObj*> _Sour);
	static void		Collision_Sphere(std::list<CObj*> _Dest, std::list<CObj*> _Sour);
};
