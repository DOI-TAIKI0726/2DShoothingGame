#ifndef _LIFE_POLYGON_H_
#define _LIFE_POLYGON_H_
#include "main.h"
#include "scene.h"
#include "manager.h"


class CLifePolygon
{
public:
	CLifePolygon();
	~CLifePolygon();

	static HRESULT Load(void);
	static void Unload(void);
	static CLifePolygon *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CLifePolygon::SetLifePolygon(int nLifePolygon);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuffer;
	D3DXVECTOR3				  m_pos;	        //�|���S���̈ʒu
	D3DXVECTOR2			      m_size;		    //�|���S���̃T�C�Y								
	float m_fTexU;
	float m_fTexV;
};

#endif
