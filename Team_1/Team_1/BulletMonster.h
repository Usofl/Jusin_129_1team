#pragma once
#include "Obj.h"
#include "Monster.h"

class CBulletMonster :
	public CObj
{
public:
	CBulletMonster();
	virtual ~CBulletMonster();

	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

public:
	inline void Set_Monster_Type(MONSTERTYPE _m_TYPE) { m_TYPE = _m_TYPE; }
	inline void Set_Monster_FirstYPos(float fA) { m_Ypos = fA; }
	inline MONSTERTYPE Get_Monster_Type(void) { return m_TYPE; }

	void Set_Size(float fa, float fb);
	

private:
	MONSTERTYPE m_TYPE;

	float theta;
	float m_Ypos;
};

