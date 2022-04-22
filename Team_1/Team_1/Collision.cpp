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

void CCollision::Collision_Sphere(std::list<CObj*> _lObjList, std::list<CObj*> _rObjList)
{
	for (auto& Dest : _lObjList)
	{
		for (auto& Sour : _rObjList)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Hit_Obj();
				Sour->Hit_Obj();
			}
		}
	}
}

bool CCollision::Check_Sphere(CObj * pDest, CObj * pSour)
{
	if (0 != pDest->Get_HP() && 0 != pSour->Get_HP())
	{
		return false;
	}

	float fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX); // µÎ ÁÂÇ¥ÀÇ ³ÐÀÌ
	float fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY); // µÎ ÁÂÇ¥ÀÇ ³ôÀÌ

	float fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight)); // µÎ ÁÂÇ¥ÀÇ °Å¸®

	if (fDiagonal < ((pDest->Get_Info().fCX * 0.5) + (pSour->Get_Info().fCX * 0.5)))
	{
		return true;
	}

	return false;
}
