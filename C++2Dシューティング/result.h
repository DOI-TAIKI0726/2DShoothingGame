#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"
#include "scene.h"
#include "manager.h"
#include "ranking.h"

class CBg;

class CResult : public CScene
{
public:
	CResult();
	~CResult();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CResult *Create(void);
	static CBg *GetBg(void);
	static CRanking *GetRanking(void);


private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2D *m_pScene2D;
	static CBg *m_pBg;
	static CRanking *m_pRanking;
};

#endif

