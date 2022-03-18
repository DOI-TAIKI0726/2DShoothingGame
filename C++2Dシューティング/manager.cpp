#include "manager.h"
#include "inputKeyboard.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "bg.h"
#include "enemy.h"
#include "enemybullet.h"
#include "score.h"
#include "number.h"
#include "life.h"
#include "life_polygon.h"
#include "effect.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "tutorial.h"
#include "tutorial2.h"

//�ÓI�����o�ϐ�
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CTitle *CManager::m_pTitle = NULL;
CGame*CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CManager::MODE CManager::m_mode = MODE_GAME;  //�ŏ��̃Q�[�����[�h
CFade *CManager::m_pFade = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CTutorial2 *CManager::m_pTutorial2 = NULL;


CManager::CManager()
{

}

CManager::~CManager()
{

}

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{

	//�����_���[�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return-1;
		}

	}

	//�L�[�{�[�h�̐���
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;
		
		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	//�T�E���h�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;

		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}

	//���[�h�؂�ւ�
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), MODE_TITLE);
	//SetMode(m_mode);

	return S_OK;
}

void CManager::Uninit(void)
{
	
	CScene::ReleaseAll();

	//�L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�T�E���h�̔j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

}

void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	//�����_���[�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

}

void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

CSound *CManager::GetSound(void)
{
	return m_pSound;
}

void CManager::SetMode(CManager::MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;
	case MODE_TUTORIAL2:
		if (m_pTutorial2 != NULL)
		{
			m_pTutorial2->Uninit();
			m_pTutorial2 = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	default:
		break;
	}

	//�O�̉�ʂ�j��
	CScene::ReleaseAll();
	
	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_TUTORIAL:
		m_pTutorial = CTutorial::Create();
		break;
	case MODE_TUTORIAL2:
		m_pTutorial2 = CTutorial2::Create();
		break;
	case MODE_GAME:
		m_pGame = CGame::Create();
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create();
		break;
	default:
		break;
	}
	m_mode = mode;
}

//���[�h�擾
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

CFade *CManager::GetFade(void)
{
	return m_pFade;
}

