#pragma once
#include "Obj.h"
class CScrewBullet :
	public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC& _hDC);
	virtual void Release(void);

private:
	float m_fBulletAngle;
};

