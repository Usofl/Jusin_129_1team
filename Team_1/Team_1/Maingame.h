#pragma once
#include "stdafx.h"
#include "Include.h"
#include "Obj.h"

class CMaingame
{
public:
	CMaingame();
	~CMaingame();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(void);
	void Release(void);


private:
	HDC		m_hDC;

	TCHAR		m_szFPS[64];	// ��Ƽ ����Ʈ ��ݿ����� CHAR�� ���� �ڵ� ��ݿ����� �����ڵ�� ó�����ִ� ��ũ��
	int			m_iFPS;
	DWORD		m_dwTime;

	std::list<CObj*> m_Monsterlist;

};

