#ifndef _INPUT_H_
#define _INPUT_H_
#include"manager.h"


//プロトタイプ宣言

class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;  //DirectInputオブジェクトのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevice;  //入力デバイス（キーボード）へのポインタ
};

#endif _INPUT_H_
