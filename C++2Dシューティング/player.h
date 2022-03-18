#ifndef _PLAYER_H_
#define _PLAYER_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "manager.h"


//プレイヤー
#define PLAYER_SIZE_X 25.0f
#define PLAYER_SIZE_Y 25.0f
#define PLAYER_SPEED 5.0f
#define PLAYER_LIFE 1
#define PLAYER_EVOSCORE1 2000
#define PLAYER_EVOSCORE2 5000
#define PLAYER_EVOSCORE3 7000



class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		PLAYER_STATE_NONE = 0,
		PLAYER_STATE_NORMAL,
		PLAYER_STATE_DAMAGE,
	} PLAYER_STATE;

	CPlayer(int nPriority = 4);
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR3 size,int nLife);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetState(CPlayer::PLAYER_STATE state);
private:
	D3DXVECTOR3 m_move;  //移動量
	static LPDIRECT3DTEXTURE9		m_pTexture;
	int m_interval = 0;
	int m_nBulletItv = 0;
	int m_nInvincible = 0;
	D3DXVECTOR3 m_pos;  //サイズ
	D3DXVECTOR3 m_size;
	PLAYER_STATE m_state;
	D3DCOLORVALUE m_color;
	bool m_bUse;
};

#endif