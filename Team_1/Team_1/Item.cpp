#include "stdafx.h"
#include "Item.h"


CItem::CItem()
{
}

CItem::CItem(const CItem& _rObj)
	: CObj(_rObj)
	, m_eItemID(_rObj.m_eItemID)
	, m_X_Reverse(_rObj.m_X_Reverse)
	, m_Y_Reverse(_rObj.m_Y_Reverse)
{
}

CItem::CItem(const ITEMID& _itemID)
	: m_eItemID(_itemID)
	, m_X_Reverse(1)
	, m_Y_Reverse(1)
{
}


CItem::~CItem()
{
	Release();
}

void CItem::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 3.f;

	m_iHP = 1;
}

void CItem::Update(void)
{
	m_tInfo.fX += m_fSpeed * cosf((m_fAngle * DEGREE)) * m_X_Reverse;
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * DEGREE)) * m_Y_Reverse;

	Update_Rect();
}

void CItem::Late_Update(void)
{
	if (GAMESIZE >= m_tRC.top || WINCY - GAMESIZE <= m_tRC.bottom)
	{
		m_Y_Reverse *= -1.f;
	}

	if (GAMESIZE >= m_tRC.left || WINCX - GAMESIZE <= m_tRC.right)
	{
		m_X_Reverse *= -1.f;
	}
}

void CItem::Release(void)
{
}