#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	CBullet(BULLETTYPE _eType);
	virtual ~CBullet();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	float m_fBulletAngle;
	int m_BulletType;
};