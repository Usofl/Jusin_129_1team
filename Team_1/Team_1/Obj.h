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

private:
	INFO m_tInfo;
	RECT m_tRC;
	int m_iHP;// �Ѿ� ü�� 1
	float m_fSpeed;
	float m_fAngle;
	POINT m_tPoint;// ��ǥ longŸ��.


};

