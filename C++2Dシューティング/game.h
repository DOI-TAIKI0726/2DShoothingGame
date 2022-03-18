#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "scene.h"
#include "manager.h"

#define ENEMY_SPAWN_X 
#define RESPAWN_TIME1 10

//ëOï˚êÈåæ
class CPlayer;
class CBg;
class CEnemy;
class CScore;
class CLife;
class CEffect;
class CLogo;
class CLevel;
class CCountTimer;
class CBossEnemy;

class CGame : public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGame *Create(void);
	static CBg *GetBg(void);
	static CPlayer *GetPlayer(void);
	static CEnemy *GetEnemy(void);
	static CScore *GetScore(void);
	static CLife *GetLife(void);
	static CEffect *GetEffect(void);
	static CLevel *GetLevel(void);
	static CCountTimer *GetCountTimer(void);
	static CBossEnemy *GetBossEnemy(void);

private:
	static CBg *m_pBg;
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy;
	static CScore *m_pScore;
	static CLife *m_pLife;
	static CEffect *m_pEffect;
	static CLevel *m_pLevel;
	static CCountTimer *m_pCountTimer;
	static CBossEnemy *m_pBossEnemy;

	static CTitle *m_pTitle;
	static CResult *m_pResult;

	int m_nResCnt = 0;
	int m_nFrame = 0;
	int m_nEnemyInterval = 0;
	int m_nEnemyFrame = 0;
	int m_nCntEnemy;
	bool m_bEnemy;
};

#endif
