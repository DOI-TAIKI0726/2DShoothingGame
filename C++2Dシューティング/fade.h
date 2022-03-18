#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"

class CFade : public CScene2D
{
public:
	//フェードの状態
	typedef enum
	{
		FADE_NONE = 0,  //何もしていない
		FADE_IN,
		FADE_OUT,  //フェードイン
		FADE_MAX  //フェードアウト
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
	//グローバル変数
	static LPDIRECT3DTEXTURE9 m_pTexture;  //テクスチャ
	FADE m_fade;  //フェードの状態
	CManager::MODE m_mode;  //次の画面(モード)
	D3DXCOLOR m_color;  //フェードの色
};


#endif _FADE_H_

