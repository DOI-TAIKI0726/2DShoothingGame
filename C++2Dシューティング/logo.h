#include "manager.h"

#define MAX_LOGO (3)

class CLogo :public CScene2D
{
public:
	typedef enum
	{
		TYPE_LOHO_NONE = 0,
		TYPE_LOGO_01,
		TYPE_LOGO_02,
		TYPE_LOGO_03,
		TYPE_LOGO_MAX
	} TYPE;
	CLogo(int nPriority = 3);
	~CLogo();

	static HRESULT Load(void);
	static void Unload(void);
	static CLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_LOGO_MAX];
	D3DXVECTOR3 m_pos;

	TYPE m_Type;
};

