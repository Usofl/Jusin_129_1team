#include "stdafx.h"
#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::CMonster(CObj *& _player)
	: m_pPlayer(_player)
{
}

CMonster::~CMonster()
{
}

void CMonster::Late_Update(void)
{
	if (m_pPlayer != nullptr)
	{
		if (0 < m_pPlayer->Get_fX() - m_tInfo.fX)
		{
			LONG temp = m_tRC.left;
			m_tRC.left = m_tRC.right;
			m_tRC.right = temp;

			m_iReverse = -1;
		}
		else
		{
			m_iReverse = 1;
		}
	}
}

void CMonster::Release(void)
{
}