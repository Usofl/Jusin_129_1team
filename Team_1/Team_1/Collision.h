#pragma once
#include "Obj.h"

class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static void Collision_Rect(std::list<CObj*> _Temp, std::list<CObj*> _Dest);
	static bool Cheak_Circle(CObj* _Temp, CObj* _Dest);
	static void Collision_Circle(std::list<CObj*> _Temp, std::list<CObj*> _Dest);
};
