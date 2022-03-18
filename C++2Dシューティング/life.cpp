#include "life.h"
#include "life_polygon.h"
#include "enemy.h"
#include "fade.h"
#include "game.h"
//#include "enemybullet.h"


CLife::CLife(int nPriority) : CScene(nPriority)
{
	memset(&m_apLifePolygon[0], 0, sizeof(m_apLifePolygon));
}

CLife::~CLife()
{

}

CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CLife *pLife = NULL;
	pLife = new CLife;

	if (pLife != NULL)
	{	 
		pLife->Init(pos,size);
		pLife->SetObjType(CScene::OBJTYPE_LIFE);
	}
	return pLife;
}

HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_size = size;

	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		m_apLifePolygon[nCntLife] = CLifePolygon::Create(D3DXVECTOR3(pos.x + m_size.x * nCntLife, pos.y, 0.0f), m_size.x, m_size.y);
	}
	m_nLife = MAX_LIFE;

	return S_OK;
}

void CLife::Uninit(void)
{
	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (m_apLifePolygon[nCntLife] != NULL)
		{
			m_apLifePolygon[nCntLife]->Uninit();
			delete m_apLifePolygon[nCntLife];
			m_apLifePolygon[nCntLife] = NULL;
		}
	}
	Release();
}

void CLife::Update(void)
{  
	//"enemybullet.h"
	//	"enemy.h"
	//	"bullet.h"
	//	"effect.h"
	//	"life.h"
	//	"player.h"
	//	"explosion.h"
	//	"score.h"
	CFade *pFade = CManager::GetFade();
	
	if (m_nLife == 0)
	{
		pFade->SetFade(CManager::MODE_RESULT);
	}

}

void CLife::Draw(void)
{
	for (int nCntLife = 0; nCntLife < m_nLife; nCntLife++)
	{
		m_apLifePolygon[nCntLife]->Draw();
	}
}

//void CLife::SetLife(int nLife)
//{
//	m_nLife = nLife;
//
//	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
//	{
//		m_apLifePolygon[nCntLife]->SetLifePolygon(m_nLife);
//	}
//}

void CLife::AddLife(int nValue)
{
	m_nLife += nValue;
}

int CLife::GetLife(void)
{
	return m_nLife;
}