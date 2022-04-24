#pragma once
#include "Obj.h"
#include "Player.h"
#include "BulletMonster.h"

class CMonster :
	public CObj
{
public:
	CMonster();
	CMonster(CObj* _player);
	virtual ~CMonster();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

public:
	void Set_Mon_Type(MONSTERTYPE _type) { m_MonType = _type; }	

	void Move_Monster(void);
	float Find_MonPlr_CosAngle(void);
	float Find_MonPlr_SinAngle(void);

	inline void Set_Player(CObj* m_PA) { m_pPlayer = m_PA; }

	//���� �Ѿ˿� ���� �Լ�.
	inline void Set_BulletList_Mon(std::list<CObj*>* _pBulletList) { Mon_Bulletlist = _pBulletList; }
	inline void Set_Speed(float _speed) { m_fSpeed = _speed; }

protected:
	CObj* m_pPlayer;

	std::list<CObj*>* Mon_Bulletlist;

	DWORD dwTime;
	DWORD dwTime_bullet;
	float theta;

	MONSTERTYPE m_MonType;
};
