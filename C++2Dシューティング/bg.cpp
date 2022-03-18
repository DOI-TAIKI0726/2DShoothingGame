#include "bg.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CBg::m_apTexture[3] = {};


CBg::CBg(int nPriority) : CScene(nPriority)
{
	m_nPriority = nPriority;
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}
}

CBg::~CBg()
{

}

HRESULT CBg::Load(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data/bg100.png",
		&m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/bg101.png",
		&m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/bg102.png",
		&m_apTexture[2]);


	return S_OK;
}

void CBg::Unload(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{				
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBg *pBg;
	pBg = new CBg;
	pBg->Init(pos,size);
	pBg->SetObjType(CScene::OBJTYPE_BG);

	return pBg;
}

HRESULT CBg::Init(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_size[nCnt] = size;
	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_fMoveV[nCnt] = 1.0f;
	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D(m_nPriority);

		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Init(pos,size);
			m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
		}
	}

	return S_OK;
}

void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt <3; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}

	Release();
}

void CBg::Update(void)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_pos[nCnt] = m_apScene2D[nCnt]->GetPosition();
		m_pos[nCnt] = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		m_apScene2D[nCnt]->SetPosition(m_pos[nCnt],m_size[nCnt]);
	}

	//一つ目
	m_fMoveV[0] -= 0.0015f;
	if (m_fMoveV[0] <= 0.0f)
	{
		m_fMoveV[0] += 1.0f;
	}

	//二つ目
	m_fMoveV[1] -= 0.002f;
	if (m_fMoveV[1] <= 0.0f)
	{
		m_fMoveV[1] += 1.0f;
	}

	//三つ目
	m_fMoveV[2] -= 0.001f;
	if (m_fMoveV[2] <= 0.0f)
	{
		m_fMoveV[2] += 1.0f;
	}

	m_apScene2D[0]->SetTex(1.0f, 1.0f, m_fMoveV[0]);
	m_apScene2D[1]->SetTex(1.0f, 1.0f, m_fMoveV[1]);
	m_apScene2D[2]->SetTex(1.0f, 1.0f, m_fMoveV[2]);

}

void CBg::Draw(void)
{

}