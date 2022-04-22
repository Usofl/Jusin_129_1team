#pragma once
#include "Monster.h"

class CMonster_A : public CMonster
{
public:
	CMonster_A();
	~CMonster_A();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;


};

