#pragma once
#include "Obj.h"

class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hdc) override;
	virtual void Release(void) override;

	void Update_Rect(void);
};

