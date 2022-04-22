#pragma once
#include "Obj.h"
#include "Player.h"

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
	void Move_Monster(void);
	float Find_MonPlr_CosAngle(void);
	float Find_MonPlr_SinAngle(void);

	inline void Set_Player(CObj* m_PA) { m_pPlayer2 = m_PA; }

private:
	CObj* m_pPlayer2;

};
