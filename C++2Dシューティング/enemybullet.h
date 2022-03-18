#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_
#define _CRT_SECURE_NO_WARNINGS
#include "manager.h"
#include "time.h"

#define ENEMY_BULLET_MOVE_X 5.0f
#define ENEMY_BULLET_MOVE_Y 3.0f
#define ENEMY_BULLET_SIZE_X 10.0f
#define ENEMY_BULLET_SIZE_Y 15.0f


class CEnemyBullet : public CScene2D
{
public:
	typedef enum
	{
		TYPE_NORMAL,
		TYPE_STRAIGHT,
		TYPE_LEFTUP,
		TYPE_RIGHTUP,
		TYPE_LEFT,
		TYPE_RIGHT,
		TYPE_BEAM,
		TYPE_MAX
	} TYPE;
	typedef enum
	{
		PLAYER_ENEMYBULLET_STATE_NONE = 0,
		PLAYER_ENEMYBULLET_STATE_NORMAL,
		PLAYER_ENEMYBULLET_STATE_DAMAGE,

	} PLAYER_ENEMYBULLET_STATE;
	
	CEnemyBullet(int nPriority = 3);
	~CEnemyBullet();
	static CEnemyBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 exsize, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 exsize, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_move;  //ˆÚ“®—Ê
	static LPDIRECT3DTEXTURE9		m_apTexture[TYPE_MAX];
	float m_nLife; //Žõ–½
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_exsize;  //”š”­‚Ì‘å‚«‚³
	D3DCOLORVALUE m_col;
	D3DXVECTOR3 m_pos;  //ƒTƒCƒY
	int m_nActTime = 0;
	DWORD m_dwCurrentTime;
	DWORD m_dwLastTime;
	int m_ResTimer;
	PLAYER_ENEMYBULLET_STATE m_PlayerEnemyState;
	
	//int m_Resinterval = 0;
	TYPE m_Type;
};

#endif

