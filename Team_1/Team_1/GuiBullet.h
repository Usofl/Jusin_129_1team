#pragma once
#include "Obj.h"
class CGuiBullet :
	public CObj
{
public:
	CGuiBullet();
	virtual ~CGuiBullet();

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC& _hDC);
	virtual void Release(void);

public:
	inline void Set_MonsterList(std::list<CObj*>* _pMonsterList) { m_pMonsterList = _pMonsterList; }

private:
	std::list<CObj*>* m_pMonsterList;
	float m_fBulletAngle;
};

