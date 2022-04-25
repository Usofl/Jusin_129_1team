#pragma once
#include "Obj.h"
class CUltimate :
	public CObj
{
public:
	CUltimate();
	~CUltimate();

	// CObj을(를) 통해 상속됨
public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

public:
	inline void Set_Player(CObj*& _pPlayer) { m_pPlayer = _pPlayer; } // 원본값을 그대로 가져다 쓰기 때문에 연산이 한단계 줄어듦

private:
	CObj* m_pPlayer;
	float m_fTemp;
	long m_lDest;
};

