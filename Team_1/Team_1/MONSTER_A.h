#pragma once
#include "Monster.h"
class CMONSTER_A final:
	public CMonster
{
public:
	CMONSTER_A();
	virtual ~CMONSTER_A();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
};

