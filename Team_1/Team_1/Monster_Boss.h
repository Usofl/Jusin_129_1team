#pragma once
#include "Monster.h"
class CMonster_Boss final:
	public CMonster
{
public:
	CMonster_Boss();
	virtual ~CMonster_Boss();

	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

	virtual void Move_Monster(void) override;
};

