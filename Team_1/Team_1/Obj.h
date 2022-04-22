#pragma once
class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize(void) PURE;
	virtual void Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC _hdc) PURE;
	virtual void Release(void) PURE;

	inline const RECT& Get_Rect() { return m_tRC; }
	inline const int& Get_HP() { return m_iHP; }
	inline void  Hit_Obj() { --m_iHP; }

protected:
	void Update_Rect(void);

public:
	POINT Get_POINT(void) { return m_tPoint; }
	void Set_POINT(POINT p) { m_tPoint = p; }

	void Make_POINT(POINT p) // Set_Pos ÇÔ¼ö
	{
		m_tInfo.fX = p.x;
		m_tInfo.fY = p.y;
	}


protected:
	INFO m_tInfo;
	RECT m_tRC;
	int m_iHP;// ÃÑ¾Ë Ã¼·Â 1
	float m_fSpeed;
	float m_fAngle;
	POINT m_tPoint;// ÁÂÇ¥ longÅ¸ÀÔ.


};

