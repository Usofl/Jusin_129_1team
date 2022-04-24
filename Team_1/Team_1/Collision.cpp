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

void CCollision::Collision_Ult(std::list<CObj*> _Ult, std::list<CObj*> _Temp)
{
	RECT rc{};

	for (auto& Ult : _Ult)
	{
		for (auto& Temp : _Temp)
		{
			if (0 < Temp->Get_HP())
			{
				if (IntersectRect(&rc, &(Ult->Get_Rect()), &(Temp->Get_Rect())))
				{
					Temp->Set_Hit_Ult();

					if (0 >= Ult->Get_HP())
					{
						break;
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

void CCollision::Collision_Player(std::list<CObj*> _Monster, std::list<CObj*> _Player)
{
	for (auto& Monster : _Monster)
	{
		for (auto& Player : _Player)
		{
			if (0 < Player->Get_HP())
			{
				if (Cheak_Circle(Monster, Player))
				{
					Player->Hit_Obj();

					if (0 >= Player->Get_HP())
					{
						return;
					}
				}
			}
		}
	}
}

void CCollision::Collision_Item(std::list<CObj*> _Item, std::list<CObj*> _Player)
{
	for (auto& Player : _Player)
	{
		for (auto& Item : _Item)
		{
			if (0 < Item->Get_HP())
			{
				if (Cheak_Circle(Item, Player))
				{
					Item->Hit_Obj();

					if (0 >= Item->Get_HP())
					{
						return;
					}
				}
			}
		}
	}
}

