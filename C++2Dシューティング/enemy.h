#include "manager.h"

#define MAX_ENEMY (3)
//“G
#define ENEMY_SIZE_X 30.0f
#define ENEMY_SIZE_Y 30.0f
#define ENEMY_LIFE 1
#define ENEMY_SPEED 0.5f
#define ENEMY_SCREEN_LIMIT_X 2000.0f
#define ENEMY_SCORE 100
#define BOSSENEMY_SCORE 10000


class CEnemy :public CScene2D
{
public:
	typedef enum
	{
		TYPE_BONE,
		TYPE_SLIME,
		TYPE_FIGHTER01,
		TYPE_FIGHTER02,
		TYPE_FIGHTER03,
		TYPE_FIGHTER04,
		TYPE_FIGHTER05,
		TYPE_MAX
	} TYPE;

	CEnemy(int nPriority = 3);
	~CEnemy();
	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move ,D3DXVECTOR3 size, int nLife,TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;  //ˆÚ“®—Ê
	D3DXVECTOR3 m_size;
	int m_nActTime = 0;
	int m_interval = 0;

	TYPE m_Type;
};
