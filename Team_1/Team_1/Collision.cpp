#include "stdafx.h"
#include "Collision.h"


CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

void CCollision::Collision_Rect(std::list<CObj*> _lObjList, std::list<CObj*> _rObjList)
{
	RECT		rc{};

	for (auto& Dest : _lObjList)
	{
		for (auto& Sour : _rObjList)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				if (0 != Dest->Get_HP() && 0 != Sour->Get_HP())
				{
					Dest->Hit_Obj();
					Sour->Hit_Obj();
				}
			}
		}
	}
}
