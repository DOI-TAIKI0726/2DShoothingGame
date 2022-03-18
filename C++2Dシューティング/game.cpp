#include "game.h"
#include "player.h"
#include "inputKeyboard.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "enemybullet.h"
#include "score.h"
#include "number.h"
#include "life.h"
#include "life_polygon.h"
#include "effect.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "time.h"
#include "LevelUI.h"
#include "count_timer.h"
#include "boss_enemy.h"
#include "sound.h"

//静的メンバ変数
CPlayer *CGame::m_pPlayer = NULL;
CBg *CGame::m_pBg = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CScore *CGame::m_pScore = NULL;
CLife *CGame::m_pLife = NULL;
CEffect *CGame::m_pEffect = NULL;
CLevel *CGame::m_pLevel = NULL;
CCountTimer *CGame::m_pCountTimer = NULL;
CBossEnemy *CGame::m_pBossEnemy = NULL;

CGame::CGame()
{
	srand((unsigned int)time(NULL));
	m_nCntEnemy = 0;
	m_bEnemy = true;

}

CGame::~CGame()
{

}

HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//ロード
	CPlayer::Load();
	CBullet::Load();
	CExplosion::Load();
	CBg::Load();
	CEnemy::Load();
	CEnemyBullet::Load();
	CNumber::Load();
	CLifePolygon::Load();
	CEffect::Load();
	CBossEnemy::Load();


	//CLevelNumber::Load();
	D3DXVECTOR3 move;
	move = D3DXVECTOR3(0.0f, PLAYER_SPEED, 0.0f);

	//2Dポリゴンクラス(プレイヤー)の生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - PLAYER_SIZE_Y, 0.0f),move, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f), PLAYER_LIFE);  ////プレイヤーのクリエイトに切り替える
	//ライフの生成																																				   //ライフクラスの生成
	m_pLife = CLife::Create(D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y, 0.0f), D3DXVECTOR3(LIFE_SIZE_X, LIFE_SIZE_Y, 0.0f));
	//スコアクラスの生成
	m_pScore = CScore::Create(D3DXVECTOR3(SCORE_POS_X, SCORE_POS_Y, 0.0f), D3DXVECTOR3(SCORE_SIZE_X, SCORE_SIZE_Y, 0.0f));
	//BGクラスの生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//レベルクラスの生成
	m_pLevel = CLevel::Create(D3DXVECTOR3(LEVEL_POS_X, LEVEL_POS_Y, 0.0f), D3DXVECTOR3(LEVEL_SIZE_X, LEVEL_SIZE_Y, 0.0f));
	//タイマークラスの生成
	m_pCountTimer = CCountTimer::Create(D3DXVECTOR3(COUNT_TIMER_POS_X, COUNT_TIMER_POS_Y, 0.0f), D3DXVECTOR3(COUNT_TIMER_SIZE_X, COUNT_TIMER_SIZE_Y, 0.0f));

	//サウンド
	CSound *pSound;
	pSound = CManager::GetSound();
	//このBGMを流す
	pSound->Play(pSound->SOUND_LABEL_BGM_MAOUDMASHI);




	return S_OK;
}

void CGame::Uninit(void)
{

	//アンロード
	CPlayer::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CBg::Unload();
	CEnemy::Unload();
	CEnemyBullet::Unload();
	CNumber::Unload();
	CLifePolygon::Unload();
	CEffect::Unload();
	CBossEnemy::Unload();
	
	CSound *pSound;
	pSound = CManager::GetSound();

	//このBGMを止める
	pSound->StopSound(pSound->SOUND_LABEL_BGM_MAOUDMASHI);

	Release();
}

void CGame::Update(void)
{
	int nScore = m_pScore->GetScore();
	CFade *pFade = CManager::GetFade();
	
	
	D3DXVECTOR3 move;
	move = D3DXVECTOR3(0.0f, ENEMY_SPEED, 0.0f);

	m_nFrame++;
	//float fPosX = (float)(rand() % 1190 + 50);
	//m_nEnemyFrame++;
	m_nEnemyInterval++;

	//雑魚エネミー
	//縦移動系
	if (m_nFrame >= 0 && m_nFrame < 600)
	{
		if (m_nEnemyInterval >= 120 && m_bEnemy == true)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(250.0f, 0.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER01);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(250.0f, -60.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER01);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(250.0f, -120.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER01);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(250.0f, -180.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER01);

			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1050.0f, 0.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER02);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1050.0f, -60.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER02);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1050.0f, -120.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER02);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1050.0f, -180.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER02);

			m_pEnemy = CEnemy::Create(D3DXVECTOR3(450.0f, 0.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER01);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(450.0f, -60.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER01);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(850.0f, 0.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER02);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(850.0f, -60.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER02);


			m_nCntEnemy++;
			if (m_nCntEnemy > 1)
			{
				m_nCntEnemy = 1;
				m_nCntEnemy = 0;
				m_bEnemy = false;
			}
			m_nEnemyInterval = 0;

		}
	}

	else if (m_nFrame >= 1500 && m_nFrame <= 1860)
	{
		m_bEnemy = true;
		if (m_nEnemyInterval >= 120 && m_bEnemy == true)
		{
			//横移動系
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(0.0f,    50.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER03);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-25.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER03);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-50.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER03);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-75.0f, 350.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER03);

			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1280.0f, 50.0f,  0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER04);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1305.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER04);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1330.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER04);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1355.0f, 350.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER04);


			m_nCntEnemy++;
			if (m_nCntEnemy > 1)
			{
				m_nCntEnemy = 1;
				m_nCntEnemy = 0;
				m_bEnemy = false;
			}

			m_nEnemyInterval = 0;
		}
	}


	else if (m_nFrame >= 2820 && m_nFrame <= 3000)
	{
		m_bEnemy = true;
		if (m_nEnemyInterval >= 120 && m_bEnemy == true)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(250.0f,    0.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER01);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(250.0f, -60.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER01);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(250.0f, -120.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER01);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(250.0f, -180.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER01);

			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1050.0f,    0.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER02);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1050.0f,  -60.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER02);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1050.0f, -120.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER02);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1050.0f, -180.0f, 0.0f), move, D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER02);

			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-50.0f,  250.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER03);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-75.0f,  350.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER03);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1330.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER04);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1355.0f, 350.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), ENEMY_LIFE, CEnemy::TYPE_FIGHTER04);


			m_nCntEnemy++;
			if (m_nCntEnemy > 1)
			{
				m_nCntEnemy = 1;
				m_nCntEnemy = 0;
				m_bEnemy = false;
			}

			m_nEnemyInterval = 0;
		}
	}

	//ボス
	else if (m_nFrame >= 4200 && m_nFrame <= 4380)
	{
		m_bEnemy = true;
		if (m_nEnemyInterval >= 120 && m_bEnemy == true)
		{
			//ボスエネミークラスの生成
			m_pBossEnemy = CBossEnemy::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y - 300.0f, 0.0f), D3DXVECTOR3(BOSS_ENEMY_SIZE_X, BOSS_ENEMY_SIZE_Y, 0.0f), BOSS_ENEMY_LIFE);
			//側近
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(300.0f,  400.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), 30, CEnemy::TYPE_FIGHTER05);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(980.0f,  400.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), 30, CEnemy::TYPE_FIGHTER05);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(300.0f,  200.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), 30, CEnemy::TYPE_FIGHTER05);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(980.0f,  200.0f, 0.0f), D3DXVECTOR3(0.0f, ENEMY_SPEED - 0.2f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f), 30, CEnemy::TYPE_FIGHTER05);


			m_nCntEnemy++;
			if (m_nCntEnemy > 1)
			{
				m_nCntEnemy = 1;
				m_nCntEnemy = 0;
				m_bEnemy = false;
			}

			m_nEnemyInterval = 0;
		}
	}




}

void CGame::Draw(void)
{

}

CGame *CGame::Create(void)
{
	CGame *pGame = NULL;
	pGame = new CGame;
	if (pGame != NULL)
	{
		pGame->Init(D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0));
	}
	return pGame;

}


CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

CEnemy *CGame::GetEnemy(void)
{
	return m_pEnemy;
}

CBg *CGame::GetBg(void)
{
	return m_pBg;
}


CScore *CGame::GetScore(void)
{
	return m_pScore;
}

CLife *CGame::GetLife(void)
{
	return m_pLife;
}

CEffect *CGame::GetEffect(void)
{
	return m_pEffect;
}

CLevel *CGame::GetLevel(void)
{
	return m_pLevel;
}

CCountTimer *CGame::GetCountTimer(void)
{
	return m_pCountTimer;
}

CBossEnemy *CGame::GetBossEnemy(void)
{
	return m_pBossEnemy;
}