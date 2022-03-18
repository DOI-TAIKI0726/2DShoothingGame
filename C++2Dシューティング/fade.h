#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"

class CFade : public CScene2D
{
public:
	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,  //�������Ă��Ȃ�
		FADE_IN,
		FADE_OUT,  //�t�F�[�h�C��
		FADE_MAX  //�t�F�[�h�A�E�g
	} FADE;

	CFade(int nPriority = 7);
	~CFade();

	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CManager::MODE mode);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFade(CManager::MODE modeNext);
	FADE GetFade(void);

private:
	//�O���[�o���ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;  //�e�N�X�`��
	FADE m_fade;  //�t�F�[�h�̏��
	CManager::MODE m_mode;  //���̉��(���[�h)
	D3DXCOLOR m_color;  //�t�F�[�h�̐F
};


#endif _FADE_H_

