#pragma once
#include "Obj.h"
#include "Player.h"

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
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	float m_fBulletAngle;
	DWORD m_dwTime;

};

