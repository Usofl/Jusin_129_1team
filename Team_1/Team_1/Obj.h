#pragma once
class CObj abstract
{
public:
	CObj();
	CObj(const CObj& _rObj);
	virtual ~CObj();

public:
	virtual void Initialize(void) PURE;
	virtual void Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release(void) PURE;

	inline const POINT& Get_POINT(void) { return m_tPoint; }
	inline const INFO& Get_Info(void) { return m_tInfo; }
	inline const RECT& Get_Rect(void) { return m_tRC; }
	inline const int& Get_HP(void) { return m_iHP; }
	inline const float& Get_Angle(void) { return m_fAngle; }
	inline const float& Get_fX(void) { return m_tInfo.fX; }
	inline const float& Get_fY(void) { return m_tInfo.fY; }

	//inline const int& Get_Life(void) { return m_iLife; } // ÇÃ·¹ÀÌ¾î ¸ñ¼û

	inline const void Hit_Obj(void) { --m_iHP; }

	inline void Set_POINT(const POINT& p) { m_tPoint = p; }
	inline void Set_Pos(float _fX, float _fY){ m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	inline void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }

	inline void Make_POINT(POINT& p) { m_tInfo.fX = (float)p.x; m_tInfo.fY = (float)p.y; }


protected:
	void Update_Rect(void);

protected:
	INFO m_tInfo;
	RECT m_tRC;
	POINT m_tPoint;// ÁÂÇ¥ longÅ¸ÀÔ.

	int m_iHP;// ÃÑ¾Ë Ã¼·Â 1

	//int m_iLife; // ÇÃ·¹ÀÌ¾î ¸ñ¼û

	float m_fSpeed;
	float m_fAngle;
};