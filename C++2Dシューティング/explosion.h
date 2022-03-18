#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#define EXPLOSION_SIZE_X 50.0f
#define EXPLOSION_SIZE_Y 50.0f
#define BOSS_EXPLOSION_SIZE_X 80.0f
#define BOSS_EXPLOSION_SIZE_Y 80.0f

#include "manager.h"

class CExplosion : public CScene2D
{
public:
	CExplosion(int nPriority = 5);
	~CExplosion();
	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nCounterAnim;
	int m_nPatternAnim;
	D3DXVECTOR3 m_size;
};

#endif