#pragma once
class CObj abstract
{
public:
	CObj();
	CObj(const CObj& _rObj);
	CObj(CObj* _rObj);
	virtual ~CObj();

public:
	virtual void Initialize(void) PURE;
	virtual void Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC& _hDC) PURE;
	virtual void Release(void) PURE;

	inline const POINT& Get_POINT(void) { return m_tPoint; }
	inline const INFO& Get_Info(void) { return m_tInfo; }
	inline const RECT& Get_Rect(void) { return m_tRC; }
	inline const int& Get_HP(void) { return m_iHP; }
	inline const float& Get_Angle(void) { return m_fAngle; }
	inline const float& Get_fX(void) { return m_tInfo.fX; }
	inline const float& Get_fY(void) { return m_tInfo.fY; }

	inline const void Hit_Obj(void) { --m_iHP; }

	inline void Set_HP(const int& _hp) { m_iHP = _hp; }
	inline void Set_POINT(const POINT& p) { m_tPoint = p; }
	inline void Set_Pos(float& _fX, float& _fY){ m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	inline void Set_Angle(const float& _fAngle) { m_fAngle = _fAngle; }
	inline void Set_Hit_Ult(void) { m_iHP -= 50; } // 얼티메이트 타격 시 데미지

	inline void Make_POINT(POINT& p) { m_tInfo.fX = (float)p.x; m_tInfo.fY = (float)p.y; }


protected:
	void Update_Rect(void);

protected:
	INFO m_tInfo;
	RECT m_tRC;
	POINT m_tPoint; // 좌표 long타입.

	int m_iHP;

	float m_fSpeed;
	float m_fAngle;
};