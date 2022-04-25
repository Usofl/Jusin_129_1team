#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Item.h"
#include "AbstractFactory.h"
#include "ItemFactory.h"

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

	void Pick_Up_Bullet(void);
	void Pick_Up_Ulti(void);
	void Pick_Up_Guided(void);
	
	const bool Use_Ult(void);
	
public:
	void Key_Input(void);
	void Collision_Wall(void); // 벽에 충돌시 이벤트 변경하려면 여기로

private:
	std::list<CObj*> m_Item_List;
	std::list<CObj*> m_Ulti_List;

	CObj* m_Gui;
	TCHAR m_szUsingGui[64];
	DWORD m_dwUsing;

	float m_fBSize; // 총신 길이
	std::list<CObj*>* m_pBulletList;
	DWORD m_dwTime;
	float m_fBulletAngle; // 총알 앵글 각도 
	BULLETTYPE m_BulletType;
	
};
