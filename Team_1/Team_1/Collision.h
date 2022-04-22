#pragma once
#include "Obj.h"

class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	void Collision_Rect(std::list<CObj*> _lObjList, std::list<CObj*> _rObjList);
};
