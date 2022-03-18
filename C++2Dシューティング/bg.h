#ifndef _BG_H_
#define _BG_H_

#include <stdio.h>
#include "main.h"
#include "scene.h"
#include "manager.h"

//•¡”‚Ìƒ|ƒŠƒSƒ“‚ğg‚¤‚È‚çCscene‚ğg‚¤
class CBg : public CScene
{
public:
	CBg(int nPriority = 0);
	~CBg();
	static HRESULT Load(void);
	static void Unload(void);
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[3];
	CScene2D *m_apScene2D[3];
	float m_fMoveU[3];
	float m_fMoveV[3];
	D3DXVECTOR3 m_pos[3];
	D3DXVECTOR3 m_size[3];
	int m_nPriority;
};


#endif