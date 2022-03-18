#ifndef _INPUT_H_
#define _INPUT_H_
#include"manager.h"


//�v���g�^�C�v�錾

class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;  //DirectInput�I�u�W�F�N�g�̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;  //���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
};

#endif _INPUT_H_
