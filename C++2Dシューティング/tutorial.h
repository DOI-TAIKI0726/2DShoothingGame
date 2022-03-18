#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "main.h"
#include "scene.h"
#include "manager.h"

//class CBg;
class CLogo;

class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();
	//static HRESULT Load(void);
	//static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTutorial *Create(void);
	//static CBg *GetBg(void);
	static CLogo *GetLogo(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2D *m_pScene2D;
	D3DXVECTOR3 m_size;
	//static CBg *m_pBg;
	static CLogo *m_pLogo;

};

#endif

