#pragma once
#include "Obj.h"
class CBulletMonster :
	public CObj
{
public:
	CBulletMonster();
	virtual ~CBulletMonster();

	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

};

