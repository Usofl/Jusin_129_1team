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
	virtual void Render(HDC _hDC) PURE;
	virtual void Release(void) PURE;

public:
	

protected:
	void Update_Rect(void);

protected:
	INFO m_tInfo;
	RECT m_tRC;
	POINT m_tPoint;// ÁÂÇ¥ longÅ¸ÀÔ.

	int m_iHP;// ÃÑ¾Ë Ã¼·Â 1
	float m_fSpeed;
	float m_fAngle;
};

