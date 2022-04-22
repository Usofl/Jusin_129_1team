#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_iHP(0)
	, m_fSpeed(0.f)
	, m_fAngle(0.f)
	, m_tInfo({0,0,0,0})
	, m_tRC({ 0,0,0,0 })
	, m_tPoint({0,0})
{
}


CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRC.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRC.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRC.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRC.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}