#include "input.h"

//静的メンバ変数
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//インストラクタ
CInput::CInput()
{
	m_pDevice = NULL;
}

//デストラクタ
CInput::~CInput()
{

}

//初期化処理
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_FALSE;
	if (m_pInput == NULL)
	{
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}
	return hr;
}

//終了処理
void CInput::Uninit(void)
{
	//デバイスオブジェクトの開放
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	if (m_pInput != NULL)
	{	   
		m_pInput->Release();
		m_pInput = NULL;
	}

}

