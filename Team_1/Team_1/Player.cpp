#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
	: m_fGetItem(0.f)
	, m_pBulletList(nullptr)
	, m_fBulletAngle(0)
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

	Update_Rect();
}

void CPlayer::Late_Update(void)
{
	m_tPoint.x = (long)(m_tInfo.fX + m_fBSize * cosf(m_fAngle * DEGREE));
	m_tPoint.y = (long)(m_tInfo.fY - m_fBSize * sinf(m_fAngle * DEGREE));

	Collision_Wall();
}

void CPlayer::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);

	MoveToEx(_hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(_hDC, (int)m_tPoint.x, (int)m_tPoint.y);

	for (auto& iter : m_Item_List)
	{
		iter->Render(_hDC);
	}
}

void CPlayer::Release(void)
{
	for (auto iter = m_Item_List.begin(); iter != m_Item_List.end();)
	{
		if (*iter != nullptr)
		{
			delete *iter;
			*iter = nullptr;
		}

		iter = m_Item_List.erase(iter);
	}
}

void CPlayer::Pick_Up_Item(CObj * _Item)
{
	CItem* item = new CItem(*static_cast<CItem*>(_Item));
	item->Pick_Up_Set(m_fGetItem);
	
	m_fGetItem += 25.f;

	m_Item_List.push_back(item);
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
			if (m_Item_List.empty()) // 아이템 리스트 비어있을 때
			{
				m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPoint.x, (float)m_tPoint.y, m_fAngle));
			}
			else 
			{
				m_fBulletAngle = m_Item_List.size();
				for (unsigned int i = 0; i <= m_Item_List.size(); ++i)
				{
					m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPoint.x, (float)m_tPoint.y, m_fBulletAngle));
					m_fBulletAngle -= 2 ;
				}
			}
			m_dwTime = GetTickCount();
		}
	}

	if (GetAsyncKeyState('E'))
	{
		if (m_dwTime + 100 < GetTickCount())
		{
			m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPoint.x, (float)m_tPoint.y, m_fAngle - 3));
			m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPoint.x, (float)m_tPoint.y, m_fAngle - 1));
			m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPoint.x, (float)m_tPoint.y, m_fAngle + 1));
			m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPoint.x, (float)m_tPoint.y, m_fAngle + 3));
			m_dwTime = GetTickCount();
		}
	}
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
