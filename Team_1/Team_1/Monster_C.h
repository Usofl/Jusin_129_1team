#pragma once
#include "Monster.h"

class CMonster_C final:
	public CMonster
{
public:
	CMonster_C();
	CMonster_C(CObj* _player);
	virtual ~CMonster_C();

	virtual void Initialize(void) override;
	virtual void Update(void) override;
	//virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

	virtual void Move_Monster(void) override;
};

