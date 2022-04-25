#pragma once
#include "Obj.h"

class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static void Collision_Rect(std::list<CObj*>& _Temp, std::list<CObj*>& _Dest);
	static void Collision_Ult(std::list<CObj*>& _Ult, std::list<CObj*>& _Dest);
	static bool Cheak_Circle(CObj*& _Temp, CObj*& _Dest);
	static void Collision_Circle(std::list<CObj*>& _Temp, std::list<CObj*>& _Dest);
	static void Collision_Player(std::list<CObj*>& _Monster, std::list<CObj*>& _Player);
	static void Collision_Item(std::list<CObj*>& _Item, std::list<CObj*>& _Player);
};
