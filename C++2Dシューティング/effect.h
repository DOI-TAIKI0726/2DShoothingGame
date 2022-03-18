#ifndef _EFFECT_H_
#define _EFFECT_H_
#define _CRT_SECURE_NO_WARNINGS
#include "manager.h"


class CEffect : public CScene2D
{
public:
	typedef enum
	{
		TYPE_BLUE,
		TYPE_RED,
		TYPE_MAX
	} TYPE;
	CEffect(int nPriority = 4);
	~CEffect();
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DCOLORVALUE col);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DCOLORVALUE col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static PDIRECT3DTEXTURE9		m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;
	//LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)

	float m_nLife; //寿命

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DCOLORVALUE m_col;
	float m_nEffectLife;
};

#endif

