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
	void Update_Rect(void);

public:
	POINT Get_POINT(void) { return m_tPoint; }
	void Set_POINT(POINT p) { m_tPoint = p; }

	void Make_POINT(POINT p) // Set_Pos �Լ�
	{
		m_tInfo.fX = p.x;
		m_tInfo.fY = p.y;
	}
private:
	INFO m_tInfo;
	RECT m_tRC;
	POINT m_tPoint;// ��ǥ longŸ��.

	int m_iHP;// �Ѿ� ü�� 1
	float m_fSpeed;
	float m_fAngle;
};

