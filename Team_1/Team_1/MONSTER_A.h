#pragma once
#include "Monster.h"
#include "Obj.h"

class CMonster_A final:
	public CMonster
{
public:
	CMonster_A();
	CMonster_A(CObj* _player);
	virtual ~CMonster_A();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	//virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

	virtual void Move_Monster(void) override;

public:
	float Find_MonPlr_CosAngle(void);
	float Find_MonPlr_SinAngle(void);
};