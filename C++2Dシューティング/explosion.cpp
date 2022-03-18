#include "explosion.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CExplosion::m_pTexture = NULL;

CExplosion::CExplosion(int nPriority) : CScene2D(nPriority)
{

}

CExplosion::~CExplosion()
{

}

CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion *pExplosion = NULL;
	pExplosion = new CExplosion;
	if (pExplosion != NULL)
	{
		pExplosion->Init(pos,size);
		pExplosion->BindTexture(m_pTexture);
		pExplosion->SetObjType(CScene::OBJTYPE_EXPLOSION);

	}
	return pExplosion;

}

HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data/explosion.png",
		&m_pTexture);

	return S_OK;
}

void CExplosion::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}



HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//m_size = size;
	CScene2D::Init(pos,size);
	SetTex(m_nPatternAnim, 0.125f, 1.0f);
	return S_OK;
}

void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

void CExplosion::Update(void)
{

	m_nCounterAnim++;

	if (m_nCounterAnim % 4 == 0)
	{
		m_nPatternAnim++;
		SetTex(m_nPatternAnim,0.125f,1.0f);

		//CScene2D::Update();

		if (m_nPatternAnim >= 8)
		{
			Uninit();
			return;
		}
	}
}

void CExplosion::Draw(void)
{
	CScene2D::Draw();
}