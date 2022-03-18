#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include <stdio.h>
#include "main.h"
#include "renderer.h"
#include "scene.h"

//�}�N����`
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define SCREEN_CENTER_X (640)
#define SCREEN_CENTER_Y (360)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//�\����
typedef struct
{
	D3DXVECTOR3 pos;  //���_���W
	float rhw;  //1.0f�ŌŒ�
	D3DCOLOR col;  //���_�J���[
	D3DXVECTOR2 tex;  //�e�N�X�`�����W
} VERTEX_2D;


class CScene2D : public CScene
{
public:
	//typedef enum
	//{
	//	TYPE_2DBLUE,
	//	TYPE_2DRED
	//} TYPE;
	CScene2D(int nPriority = 3);
	~CScene2D();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	D3DXVECTOR3 GetPosition(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTex(int nPattern, float fTexU, float fTexV);
	void SetTex(float fTexU, float fTexV, float fMoveV);
	void SetSize(float fWidth, float fHeight);
	D3DXVECTOR3 GetSize(void);
	void SetCol(D3DCOLORVALUE col);
	void SetCol(D3DXCOLOR col);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;
	LPDIRECT3DTEXTURE9		m_pTexture;
	D3DXVECTOR3				m_pos;			//�|���S���̈ʒu
	D3DXVECTOR3				m_size;		    //�|���S���̃T�C�Y
	D3DXVECTOR3				m_move;
	D3DCOLORVALUE		    m_col;
	//TYPE m_Type;

	int m_nNumAll;
	float m_fTexU;
	float m_fTexV;
	float m_fWidth;
	float m_fHeight;

};

#endif


