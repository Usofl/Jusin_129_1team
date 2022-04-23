#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "AbstractFactory.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

	void Set_BulletList(std::list<CObj*>* _pBulletList) { m_pBulletList = _pBulletList; }

public:
	void Key_Input(void);
	void Collision_Wall(void); // 벽에 충돌시 이벤트 변경하려면 여기로

private:
	float m_fBSize; // 총신 길이
	std::list<CObj*>* m_pBulletList;
};
