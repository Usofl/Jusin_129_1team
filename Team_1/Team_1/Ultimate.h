#pragma once
#include "Obj.h"
class CUltimate :
	public CObj
{
public:
	CUltimate();
	~CUltimate();

	// CObj��(��) ���� ��ӵ�
public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

public:
	inline void Set_Player(CObj*& _pPlayer) { m_pPlayer = _pPlayer; } // �������� �״�� ������ ���� ������ ������ �Ѵܰ� �پ��

private:
	CObj* m_pPlayer;
	float m_fTemp;
	long m_lDest;
};

