#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "Player.h"

class CRollBot :
	public CObj
{
public:
	CRollBot();
	~CRollBot();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

	inline void Set_BulletList(std::list<CObj*>* _pBulletList) { m_pBulletList = _pBulletList; }
	inline void Set_Player(CObj*& _player) { m_pPlayer = _player; }

private:
	DWORD m_dwTime;

	CObj* m_pPlayer;
	std::list<CObj*>* m_pBulletList;
};

