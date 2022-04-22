#include "stdafx.h"
#include "Collision.h"


CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}


void CCollision::Collision_Rect(std::list<CObj*> _Dest, std::list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (0 != Dest->Get_HP() && 0 != Sour->Get_HP())
			{
				if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
				{
					Dest->Hit_Obj();
					Sour->Hit_Obj();
				}
			}
		}
	}
}

bool CCollision::Check_Sphere(CObj* pDest, CObj* pSour)
{
	// abs : 절대값을 구해주는 함수
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius > fDiagonal;
}

void CCollision::Collision_Sphere(std::list<CObj*> _Dest, std::list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (0 != Dest->Get_HP() && 0 != Sour->Get_HP())
			{
				if (Check_Sphere(Dest, Sour))
				{
					Dest->Hit_Obj();
					Sour->Hit_Obj();
				}
			}
		}
	}
}
