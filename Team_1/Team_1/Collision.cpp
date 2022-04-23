#include "stdafx.h"
#include "Collision.h"


CCollision::CCollision()
{
}

CCollision::~CCollision()
{
}

void CCollision::Collision_Rect(std::list<CObj*> _Temp, std::list<CObj*> _Dest)
{
	RECT rc{};
	
	for (auto& Temp : _Temp)
	{
		if (0 < Temp->Get_HP())
		{
			for (auto& Dest : _Dest)
			{
				if (0 < Dest->Get_HP())
				{
					if (IntersectRect(&rc, &(Temp->Get_Rect()), &(Dest->Get_Rect())))
					{
						Temp->Hit_Obj();
						Dest->Hit_Obj();

						if (0 >= Temp->Get_HP())
						{
							break;
						}
					}
				}
			}
		}
	}
}

bool CCollision::Cheak_Circle(CObj * _Temp, CObj * _Dest)
{
	float fWidth = fabs(_Temp->Get_fX() - _Dest->Get_fX());
	float fHeight = fabs(_Temp->Get_fY() - _Dest->Get_fY());

	float fDigonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight));
	float fRadius = (_Temp->Get_Info().fCX + _Dest->Get_Info().fCX) / 2.f;

	return fRadius > fDigonal;
}

void CCollision::Collision_Circle(std::list<CObj*> _Temp, std::list<CObj*> _Dest)
{
	for (auto& Temp : _Temp)
	{
		if (0 < Temp->Get_HP())
		{
			for (auto& Dest : _Dest)
			{
				if (0 < Dest->Get_HP())
				{
					if (Cheak_Circle(Temp, Dest))
					{
						Temp->Hit_Obj();
						Dest->Hit_Obj();

						if (0 >= Temp->Get_HP())
						{
							break;
						}
					}
				}
			}
		}
	}
}

