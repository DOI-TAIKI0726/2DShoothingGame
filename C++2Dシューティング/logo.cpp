#include "logo.h"

LPDIRECT3DTEXTURE9 CLogo::m_apTexture[TYPE_LOGO_MAX] = {};

CLogo::CLogo(int nPriority) : CScene2D(nPriority)
{

}

CLogo::~CLogo()
{

}

HRESULT CLogo::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data/title.png",
		&m_apTexture[TYPE_LOGO_01]);

	D3DXCreateTextureFromFile(pDevice,
		"data/Tutorial01.png",
		&m_apTexture[TYPE_LOGO_02]);

	D3DXCreateTextureFromFile(pDevice,
		"data/Tutorial02.png",
		&m_apTexture[TYPE_LOGO_03]);



	return S_OK;
}

void CLogo::Unload(void)
{
	for (int nCnt = 0; nCnt < TYPE_LOGO_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{			  
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

CLogo *CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	CLogo *pLogo;
	pLogo = new CLogo;
	pLogo->Init(pos, size);
	pLogo->m_Type = type;
	pLogo->BindTexture(m_apTexture[type]);

	pLogo->SetObjType(CScene::OBJTYPE_LOGO);
	return pLogo;
}

HRESULT CLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	m_pos = pos;

	return S_OK;
}

void CLogo::Uninit(void)
{
	CScene2D::Uninit();
}

void CLogo::Update(void)
{
	CScene2D::Update();
}

void CLogo::Draw(void)
{
	CScene2D::Draw();
}
