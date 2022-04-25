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

CObj::CObj(const CObj & _rObj)
	: m_iHP(_rObj.m_iHP)
	, m_fSpeed(_rObj.m_fSpeed)
	, m_fAngle(_rObj.m_fAngle)
	, m_tInfo(_rObj.m_tInfo)
	, m_tRC(_rObj.m_tRC)
	, m_tPoint(_rObj.m_tPoint)
{
}

CObj::CObj(CObj * _rObj)
	: m_iHP(_rObj->m_iHP)
	, m_fSpeed(_rObj->m_fSpeed)
	, m_fAngle(_rObj->m_fAngle)
	, m_tInfo(_rObj->m_tInfo)
	, m_tRC(_rObj->m_tRC)
	, m_tPoint(_rObj->m_tPoint)
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
