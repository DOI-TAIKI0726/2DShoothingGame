#include "tutorial2.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "logo.h"
#include "fade.h"
#include "sound.h"
LPDIRECT3DTEXTURE9 CTutorial2::m_pTexture = NULL;
//CBg *CTutorial2::m_pBg = NULL;
CLogo *CTutorial2::m_pLogo = NULL;

CTutorial2::CTutorial2()
{

}

CTutorial2::~CTutorial2()
{

}


HRESULT CTutorial2::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBg::Load();
	CLogo::Load();

	//m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pLogo = CLogo::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y , 0.0f), D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGHT/2, 0.0f), CLogo::TYPE_LOGO_03);

	return S_OK;
}

void CTutorial2::Uninit(void)
{
	//CBg::Unload();
	CSound *pSound;
	pSound = CManager::GetSound();

	//‚±‚ÌBGM‚ðŽ~‚ß‚é
	pSound->StopSound(pSound->SOUND_LABEL_BGM_MAOUDMASHI02);


	Release();
}

void CTutorial2::Update(void)
{
	CFade *pFade = CManager::GetFade();
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAME);
		}
	}

}

void CTutorial2::Draw(void)
{

}

CTutorial2 * CTutorial2::Create(void)
{
	CTutorial2 *pTutorial2 = NULL;
	pTutorial2 = new CTutorial2;
	if (pTutorial2 != NULL)
	{
		pTutorial2->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	}
	return pTutorial2;

}

//CBg *CTutorial2::GetBg(void)
//{
//	return m_pBg;
//}

CLogo *CTutorial2::GetLogo(void)
{
	return m_pLogo;
}
