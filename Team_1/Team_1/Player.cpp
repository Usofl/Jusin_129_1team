#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
	: m_pBulletList(nullptr)
	, m_Gui(nullptr)
	, m_fBulletAngle(0)
	, m_BulletType(BULLETTYPE_DEFULT)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = PLAYER_START_X;
	m_tInfo.fY = PLAYER_START_Y;

	m_tInfo.fCX = PLAYERCX;
	m_tInfo.fCY = PLAYERCY;

	m_fSpeed = 7.f;

	m_fBSize = 50.f;

	m_iHP = 1;

	m_tPoint.x = (long)(m_tInfo.fX + m_fBSize * cosf(m_fAngle * DEGREE));
	m_tPoint.y = (long)(m_tInfo.fY - m_fBSize * sinf(m_fAngle * DEGREE));
}

void CPlayer::Update(void)
{
	Key_Input();

	if (m_Gui != nullptr)
	{
		if (0 >= m_Gui->Get_HP())
		{
			Safe_Delete<CObj*>(m_Gui);
		}
	}
	
	Update_Rect();
}

void CPlayer::Late_Update(void)
{
	m_tPoint.x = (long)(m_tInfo.fX + m_fBSize * cosf(m_fAngle * DEGREE));
	m_tPoint.y = (long)(m_tInfo.fY - m_fBSize * sinf(m_fAngle * DEGREE));

	if (m_Gui != nullptr)
	{
		if (m_dwUsing + 1000 < GetTickCount())
		{
			m_dwUsing = GetTickCount();

			m_Gui->Set_HP(m_Gui->Get_HP() - 1);
		}
	}

	Collision_Wall();
}

void CPlayer::Render(HDC _hDC)
{
	MoveToEx(_hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(_hDC, (int)m_tPoint.x, (int)m_tPoint.y);

	MoveToEx(_hDC, (int)m_tPoint.x, (int)m_tPoint.y, nullptr);
	LineTo(_hDC, (int)(m_tInfo.fX - (int)(m_tInfo.fCX * 0.5f)), (int)(m_tInfo.fY - (int)(m_tInfo.fCY * 0.5f)));

	MoveToEx(_hDC, (int)(m_tInfo.fX - (int)(m_tInfo.fCX * 0.5f)), (int)(m_tInfo.fY - (m_tInfo.fCY * 0.5f)), nullptr);
	LineTo(_hDC, (int)m_tInfo.fX, (int)m_tInfo.fY);

	MoveToEx(_hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(_hDC, (int)(m_tInfo.fX - (m_tInfo.fCX * 0.5f)), (int)(m_tInfo.fY + (int)(m_tInfo.fCY * 0.5f)));

	MoveToEx(_hDC, (int)(m_tInfo.fX - (int)(m_tInfo.fCX * 0.5f)), (int)(m_tInfo.fY + (int)(m_tInfo.fCY * 0.5f)), nullptr);
	LineTo(_hDC, (int)m_tPoint.x, (int)m_tPoint.y);

	MoveToEx(_hDC, (int)m_tPoint.x, (int)m_tPoint.y, nullptr);
	LineTo(_hDC, (int)m_tInfo.fX, (int)(m_tInfo.fY - (int)(m_tInfo.fCY * 0.5f)));

	MoveToEx(_hDC, (int)m_tInfo.fX, (int)(m_tInfo.fY - (int)(m_tInfo.fCY * 0.5f)), nullptr);
	LineTo(_hDC, (int)m_tInfo.fX, (int)(m_tInfo.fY + (int)(m_tInfo.fCY * 0.5f)));

	MoveToEx(_hDC, (int)m_tInfo.fX, (int)(m_tInfo.fY + (int)(m_tInfo.fCY * 0.5f)), nullptr);
	LineTo(_hDC, (int)m_tPoint.x, (int)m_tPoint.y);

	Ellipse(_hDC, m_tPoint.x - (int)(m_tInfo.fCX * 1.5f), m_tRC.top + (int)(m_tInfo.fCY * 0.25f), m_tPoint.x, m_tRC.bottom - (int)(m_tInfo.fCY * 0.25f));

	/*Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);*/

	for (auto& iter : m_Item_List)
	{
		iter->Render(_hDC);
	}

	for (auto& iter : m_Ulti_List)
	{
		iter->Render(_hDC);
	}

	if (m_Gui != nullptr)
	{
		m_Gui->Render(_hDC);

		swprintf_s(m_szUsingGui, L": %d", m_Gui->Get_HP());
		TextOutW(_hDC, (int)(WINCX * 0.5f), WINCY - OUTGAMESIZE, m_szUsingGui, lstrlen(m_szUsingGui));
	}
}

void CPlayer::Release(void)
{
	for (auto iter = m_Item_List.begin(); iter != m_Item_List.end();)
	{
		Safe_Delete<CObj*>(*iter);
		iter = m_Item_List.erase(iter);
	}

	for (auto iter = m_Ulti_List.begin(); iter != m_Ulti_List.end();)
	{
		Safe_Delete<CObj*>(*iter);
		iter = m_Ulti_List.erase(iter);
	}

	Safe_Delete<CObj*>(m_Gui);
}

void CPlayer::Pick_Up_Bullet()
{
	CObj* item = CItemFactory::Create_Item_Bullet(0.f, 0.f);
	static_cast<CItem*>(item)->Pick_Up_Set();

	m_Item_List.push_back(item);
}

void CPlayer::Pick_Up_Ulti()
{
	CObj* item = CItemFactory::Create_Item_UltiMate(0.f,0.f);
	static_cast<CItem*>(item)->Pick_Up_Set();

	m_Ulti_List.push_back(item);
}

void CPlayer::Pick_Up_Guided()
{
	if (nullptr == m_Gui)
	{
		m_Gui = CItemFactory::Create_Item_Guided(0.f, 0.f);
		static_cast<CItem*>(m_Gui)->Pick_Up_Set();
		
		m_dwUsing = GetTickCount();

		m_Gui->Set_HP(60);
	}
	else
	{
		m_Gui->Set_HP(m_Gui->Get_HP() + 60);
	}
}

const bool CPlayer::Use_Ult(void)
{
	bool bEmpty = m_Ulti_List.empty();

	if (!bEmpty)
	{
		delete m_Ulti_List.back();
		m_Ulti_List.pop_back();
	}

	return bEmpty;
}

void CPlayer::Key_Input(void)
{
	RECT rc{};
	RECT LeftWall{ GAMESIZE - 10, GAMESIZE, GAMESIZE, WINCY - GAMESIZE };
	RECT RightWall{ WINCX - GAMESIZE, GAMESIZE, WINCX - GAMESIZE + 10, WINCY - GAMESIZE };

	if (GetAsyncKeyState(VK_LEFT) && (!IntersectRect(&rc, &LeftWall, &m_tRC)))
	{
		if (GetAsyncKeyState(VK_UP))
		{
				m_tInfo.fX -= m_fSpeed / nLog;
				m_tInfo.fY -= m_fSpeed / nLog;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / nLog;
			m_tInfo.fY += m_fSpeed / nLog;
		}
		else
		{
			m_tInfo.fX -= m_fSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) && (!IntersectRect(&rc, &RightWall, &m_tRC)))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / nLog;
			m_tInfo.fY -= m_fSpeed / nLog;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / nLog;
			m_tInfo.fY += m_fSpeed / nLog;
		}
		else
		{
			m_tInfo.fX += m_fSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}

	if (GetAsyncKeyState('W'))
	{
		if (8 <= m_fAngle)
		{
			m_fAngle = 8.f;
		}
		else
		{
			m_fAngle += 1.f;
		}
	}

	if (GetAsyncKeyState('S'))
	{
		if (-8 >= m_fAngle)
		{
			m_fAngle = -8.f;
		}
		else
		{
			m_fAngle -= 1.f;
		}
	}

	if (GetAsyncKeyState('D'))
	{
		if (m_dwTime + 100 < GetTickCount())
		{
			if (m_Gui)
			{
				// 유도탄 생성하면서 몬스터 리스트 주소를 보내준다.
				m_pBulletList->push_back(CAbstractFactory<CGuiBullet>::Create_Bullet((float)m_tPoint.x, (float)m_tPoint.y, m_fAngle, m_pMonsterList));
			}
			else
			{
				if (m_Item_List.empty()) // 아이템 리스트 비어있을 때
				{
					switch (m_BulletType)
					{
					case BULLETTYPE_DEFULT:
						m_pBulletList->push_back(CAbstractFactory<CBullet>::Create_Bullet((float)m_tPoint.x, (float)m_tPoint.y, m_fAngle));
						break;

					case BULLETTYPE_SCREW:
						m_pBulletList->push_back(CAbstractFactory<CScrewBullet>::Create_Bullet((float)m_tPoint.x, (float)m_tPoint.y, m_fAngle));
						break;
					}
				}
				else
				{
					m_fBulletAngle = (float)m_Item_List.size();
					for (unsigned int i = 0; i <= m_Item_List.size(); ++i)
					{
						switch (m_BulletType)
						{
						case BULLETTYPE_DEFULT:
							m_pBulletList->push_back(CAbstractFactory<CBullet>::Create_Bullet((float)m_tPoint.x, (float)m_tPoint.y, m_fBulletAngle));
							break;

						case BULLETTYPE_SCREW:
							m_pBulletList->push_back(CAbstractFactory<CScrewBullet>::Create_Bullet((float)m_tPoint.x, (float)m_tPoint.y, m_fBulletAngle));
							break;
						}
						m_fBulletAngle -= 2;
					}
				}
			}
			m_dwTime = GetTickCount();
		}
	}

	if (GetAsyncKeyState('E'))
	{
		if (m_BulletType == BULLETTYPE_DEFULT)
		{
			m_BulletType = BULLETTYPE_SCREW;
		}
		else if (m_BulletType == BULLETTYPE_SCREW)
		{
			m_BulletType = BULLETTYPE_DEFULT;
		}
	}
}

template<typename T>
CObj * CPlayer::Create_Bullet(void)
{
	CObj* pBullet = CAbstractFactory<T>::Create((float)m_tPoint.x, (float)m_tPoint.x, m_fAngle, m_Gui);
	return pBullet;
}

void CPlayer::Collision_Wall(void)
{
	RECT rc{};
	RECT TopWall{ GAMESIZE, GAMESIZE - 10, WINCX - GAMESIZE, GAMESIZE };
	RECT BottomWall{ GAMESIZE, WINCY - GAMESIZE, WINCX - GAMESIZE, WINCY - GAMESIZE + 10 };

	if (IntersectRect(&rc, &TopWall, &m_tRC))
	{
		m_tInfo.fY = (WINCY - GAMESIZE) - (PLAYERCY / 2.f);

		m_tPoint.x = (long)(m_tInfo.fX + m_fBSize * cosf(m_fAngle * DEGREE));
		m_tPoint.y = (long)(m_tInfo.fY - m_fBSize * sinf(m_fAngle * DEGREE));
	}
	if (IntersectRect(&rc, &BottomWall, &m_tRC))
	{
		m_tInfo.fY = (GAMESIZE)+(PLAYERCY / 2.f);

		m_tPoint.x = (long)(m_tInfo.fX + m_fBSize * cosf(m_fAngle * DEGREE));
		m_tPoint.y = (long)(m_tInfo.fY - m_fBSize * sinf(m_fAngle * DEGREE));
	}
}
