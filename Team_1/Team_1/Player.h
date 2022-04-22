#pragma once
#include "Obj.h"
#include "Bullet.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hdc) override;
	virtual void Release(void) override;

	void Set_pBulletList(std::list<CObj*>* _pBulletList) { m_pBulletList = _pBulletList; }

private:
	std::list<CObj*>* m_pBulletList;
};

