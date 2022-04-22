#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_iHP(0), m_fSpeed(0.f), m_fAngle(0.f)
{
}


CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRC.left = (m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRC.top = (m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRC.right = (m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRC.bottom = (m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Update_Rect(void)
{
	m_tRC.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRC.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRC.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRC.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
