#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hdc) override;
	virtual void Release(void) override;
};

