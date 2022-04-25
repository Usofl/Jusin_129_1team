#pragma once
#include "Obj.h"
#include "Player.h"
#include "BulletMonster.h"

class CMonster :
	public CObj
{
public:
	CMonster();
	CMonster(CObj*& _player);
	virtual ~CMonster();

	// Inherited via CObj
	virtual void Initialize(void) PURE;
	virtual void Update(void) PURE;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release(void) PURE;

	virtual void Move_Monster(void) PURE;

public:
	void Set_Mon_Type(MONSTERTYPE& _type) { m_MonType = _type; }
	MONSTERTYPE Get_Mon_Type(void) { return m_MonType; }

	inline void Set_Player(CObj* m_PA) { m_pPlayer = m_PA; }

	//���� �Ѿ˿� ���� �Լ�.
	inline void Set_BulletList_Mon(std::list<CObj*>* _pBulletList) { Mon_Bulletlist = _pBulletList; }
	inline void Set_Speed(float& _speed) { m_fSpeed = _speed; }

protected:
	CObj* m_pPlayer;

	std::list<CObj*>* Mon_Bulletlist;

	DWORD dwTime;
	DWORD dwTime_bullet;
	float theta;

	int m_iReverse;

	MONSTERTYPE m_MonType;
};
