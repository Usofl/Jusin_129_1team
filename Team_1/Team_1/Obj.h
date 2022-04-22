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

	inline POINT Get_POINT(void) { return m_tPoint; }
	inline void Set_POINT(const POINT& p) { m_tPoint = p; }
	// Set_Pos �Լ�
	inline void Make_POINT(const POINT& p) { m_tInfo.fX = p.x; m_tInfo.fY = p.y; }

protected:
	void Update_Rect(void);

protected:
	INFO m_tInfo;
	RECT m_tRC;
	POINT m_tPoint;// ��ǥ longŸ��.

	int m_iHP;// �Ѿ� ü�� 1

	float m_fSpeed;
	float m_fAngle;
};

