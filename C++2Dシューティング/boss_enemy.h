#include "manager.h"

//“G
#define BOSS_ENEMY_SIZE_X 300.0f
#define BOSS_ENEMY_SIZE_Y 150.0f
#define BOSS_ENEMY_LIFE 150


class CBossEnemy :public CScene2D
{
public:
	CBossEnemy(int nPriority = 3);
	~CBossEnemy();
	static HRESULT Load(void);
	static void Unload(void);
	static CBossEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	typedef enum
	{
		BOSS_BULLET_NONE = 0,
		BOSS_BULLET_STRAIGHT,
		BOSS_BULLET_SG,
	} BOSS_BULLET;
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;  //ˆÚ“®—Ê
	D3DXVECTOR3 m_size;
	int m_nActTime = 0;
	int m_interval = 0;
	int m_nBossFrame= 0;
	int m_nCntBoss;
	bool m_bBoss;
	BOSS_BULLET m_BossBullet;
	//TYPE m_Type;
};

