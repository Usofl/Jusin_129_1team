#pragma once
#include "Obj.h"

class CShield :
	public CObj
{
public:
	CShield();
	virtual ~CShield();

	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC& _hDC);
	virtual void Release(void);

	inline void Set_Player(CObj* _player) { m_pPlayer = _player; }

private:
	CObj* m_pPlayer;
};

