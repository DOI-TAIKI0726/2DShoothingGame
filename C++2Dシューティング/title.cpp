#include "title.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "logo.h"
#include "fade.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;
CBg *CTitle::m_pBg = NULL;
CLogo *CTitle::m_pLogo = NULL;

CTitle::CTitle()
{

}

CTitle::~CTitle()
{

}

//HRESULT CTitle::Load(void)
//{
//	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//	//D3DXCreateTextureFromFile(pDevice,
//	//	"data/自機.png",
//	//	&m_pTexture);
//
//	return S_OK;
//}
//
//void CTitle::Unload(void)
//{
//	//テクスチャの破棄
//	if (m_pTexture != NULL)
//	{
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//
//}

HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBg::Load();
	CLogo::Load();

	//m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pLogo = CLogo::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y , 0.0f), D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), CLogo::TYPE_LOGO_01);

	//サウンド
	CSound *pSound;
	pSound = CManager::GetSound();
	//このBGMを流す
	pSound->Play(pSound->SOUND_LABEL_BGM_MAOUDMASHI03);


	return S_OK;
}

void CTitle::Uninit(void)
{
	CBg::Unload();

	CSound *pSound;
	pSound = CManager::GetSound();

	//このBGMを止める
	pSound->StopSound(pSound->SOUND_LABEL_BGM_MAOUDMASHI03);

	

	Release();
}

void CTitle::Update(void)
{
	CFade *pFade = CManager::GetFade();
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_TUTORIAL);
		}
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAME);
		}
	}

}

void CTitle::Draw(void)
{

}

CTitle * CTitle::Create(void)
{
	CTitle *pTitle = NULL;
	pTitle = new CTitle;
	if (pTitle != NULL)
	{
		pTitle->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	}
	return pTitle;

}

CBg *CTitle::GetBg(void)
{
	return m_pBg;
}

CLogo *CTitle::GetLogo(void)
{
	return m_pLogo;
}
