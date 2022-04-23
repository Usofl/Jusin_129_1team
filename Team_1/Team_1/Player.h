#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Item.h"
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

	inline void Set_BulletList(std::list<CObj*>* _pBulletList) { m_pBulletList = _pBulletList; }

	void Pick_Up_Item(CObj* _Item);

public:
	void Key_Input(void);

private:
	std::list<CObj*> m_Item_List;

	float m_fBSize; // √—Ω≈ ±Ê¿Ã
	std::list<CObj*>* m_pBulletList;
};
