#include "tutorial.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "logo.h"
#include "fade.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;
//CBg *CTutorial::m_pBg = NULL;
CLogo *CTutorial::m_pLogo = NULL;

CTutorial::CTutorial()
{

}

CTutorial::~CTutorial()
{

}


HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBg::Load();
	CLogo::Load();

	//m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pLogo = CLogo::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y , 0.0f), D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGHT/2, 0.0f),CLogo::TYPE_LOGO_02);

	//ƒTƒEƒ“ƒh
	CSound *pSound;
	pSound = CManager::GetSound();
	//‚±‚ÌBGM‚ð—¬‚·
	pSound->Play(pSound->SOUND_LABEL_BGM_MAOUDMASHI02);

	return S_OK;
}

void CTutorial::Uninit(void)
{
	//CBg::Unload();

	Release();
}

void CTutorial::Update(void)
{
	CFade *pFade = CManager::GetFade();
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_TUTORIAL2);
		}
	}

}

void CTutorial::Draw(void)
{

}

CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial = NULL;
	pTutorial = new CTutorial;
	if (pTutorial != NULL)
	{
		pTutorial->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	}
	return pTutorial;

}

//CBg *CTutorial::GetBg(void)
//{
//	return m_pBg;
//}

CLogo *CTutorial::GetLogo(void)
{
	return m_pLogo;
}
