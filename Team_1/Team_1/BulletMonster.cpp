#include "stdafx.h"
#include "BulletMonster.h"


CBulletMonster::CBulletMonster()
{
}

CBulletMonster::~CBulletMonster()
{
}

void CBulletMonster::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 5.f;
	m_iHP = 1;
}

void CBulletMonster::Update(void)
{
	m_tInfo.fX -= m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY += m_fSpeed * sinf((m_fAngle * PI) / 180.f);

	Update_Rect();
}

void CBulletMonster::Late_Update(void)
{
	// �� �浹ó��
	if (50 >= m_tRC.left || WINCX - 50 <= m_tRC.right
		|| 50 >= m_tRC.top || WINCY - 50 <= m_tRC.bottom)
	{
		m_iHP = 0;
	}
}

void CBulletMonster::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRC.left, m_tRC.top, m_tRC.right, m_tRC.bottom);
}

void CBulletMonster::Release(void)
{
}


//void CMonster::Move_Mon_Bullet(void)
//{
//	//���Ͱ� �Ѿ��� ����.(1. �Ѿ��� ���� ��ġ���� 2. �׸���)
//	//�Ѿ��� �÷��̾� ���⸸ ����.(1. ���⺯ȯ�� ����: ��. �÷��̾� ���� ��ǥ 1���� ����)
//	//�Ѿ� ������ ���� ���Ȱ�->��׸����� �ٲٱ�.
//
//	/*float m_MonPlr_Angle =0.f;
//
//	if (m_MonPlr_Angle == 0.f)
//	{
//	m_MonPlr_Angle = Find_MonPlr_CosAngle() * 180 / PI;
//	}
//
//	if (m_MonType == MONSTERTYPE_B)
//	{
//	Mon_Bulletlist->push_back(CAbstractFactory<CBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_MonPlr_Angle));
//	for (auto& iter : (*Mon_Bulletlist))
//	{
//	iter->Update();
//	}
//	}*/
//
//}