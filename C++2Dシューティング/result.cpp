#include "result.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "fade.h"
#include "ranking.h"
#include "number.h"

LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
CBg *CResult::m_pBg = NULL;
CRanking *CResult::m_pRanking = NULL;


CResult::CResult()
{

}

CResult::~CResult()
{

}

HRESULT CResult::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data/自機.png",
		&m_pTexture);

	return S_OK;
}

void CResult::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBg::Load();
	CNumber::Load();

	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pRanking = CRanking::Create(D3DXVECTOR3(380, 200.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f));


	return S_OK;
}

void CResult::Uninit(void)
{
	CBg::Unload();
	CNumber::Unload();

	Release();
}

void CResult::Update(void)
{
	CFade *pFade = CManager::GetFade();
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{
		pFade->SetFade(CManager::MODE_TITLE);
	}
}

void CResult::Draw(void)
{

}

CResult * CResult::Create(void)
{
	CResult *pResult = NULL;
	pResult = new CResult;
	if (pResult != NULL)
	{
		pResult->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	}
	return pResult;

}

CBg *CResult::GetBg(void)
{
	return m_pBg;
}

CRanking *CResult::GetRanking(void)
{
	return m_pRanking;
}