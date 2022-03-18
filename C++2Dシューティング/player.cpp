#include "player.h"
#include"bullet.h"
#include "inputKeyboard.h"
#include "sound.h"
#include "explosion.h"
#include "life.h"
#include "game.h"
#include "enemy.h"
#include "score.h"
#include "enemybullet.h"
#include "boss_enemy.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CPlayer::m_pTexture = NULL;


CPlayer::CPlayer(int nPriority) : CScene2D(nPriority)
{
	//初期化
	m_state = PLAYER_STATE_NORMAL;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_bUse = false;
}

CPlayer::~CPlayer()
{

}

CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife)
{
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos,move,size,nLife);
		pPlayer->BindTexture(m_pTexture);
		pPlayer->SetObjType(CScene::OBJTYPE_PLAYER);
		pPlayer->m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	}
	return pPlayer;
}

HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data/player.png",
		&m_pTexture);

	return S_OK;
}

void CPlayer::Unload(void)
{

	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}


HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife)
{
	CScene::SetPlayerLife(nLife);
	CScene2D::Init(pos,size);
	m_pos = pos;
	m_size = size;
	m_move = move;
	m_state = PLAYER_STATE_NORMAL;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	return S_OK;
}

void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
	CSound *pSound;
	pSound = CManager::GetSound();

	//このBGMを止める
	pSound->StopSound(pSound->SOUND_LABEL_SHOT000);
}

void CPlayer::Update(void)
{
	//CScene2D::Update();
	CSound *pSound;
	pSound = CManager::GetSound();
	//スコア取得
	CScore *pScore;
	pScore = CGame::GetScore();
	int nScore = pScore->GetScore();


	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	//プレイヤー？
	pos = GetPosition();
	//敵？
	m_pos = GetPosition();

	SetPosition(m_pos,m_size);

	switch (m_state)
	{
	case PLAYER_STATE_NORMAL:
		CScene2D::SetCol(m_color);
		m_color.r = 255.0f;
		m_color.g = 255.0f;
		m_color.b = 255.0f;
		m_color.a = 255.0f;
		break;
	case PLAYER_STATE_DAMAGE:
		m_nInvincible++;
		CScene2D::SetCol(m_color);
		//m_color.r = 255.0f;
		//m_color.g = 255.0f;
		//m_color.b = 255.0f;
		m_color.a = 80.0f;

		//一定時間が経ったら
		if (m_nInvincible >= 180)
		{
			m_state = PLAYER_STATE_NORMAL;
			m_nInvincible = 0;
		}
		break;
	default:
		break;
	}
	
	//当たり判定
	if (m_state != PLAYER_STATE_DAMAGE)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
			{
				//オブジェクトの番号を取得（Bulletがどこにあるか探す）
				CScene *pScene;
				pScene = CScene::GetScene(nCntPriority, nCntScene);
				if (pScene != NULL)
				{
					//種類を取得
					CScene::OBJTYPE objType;
					objType = pScene->GetObjType();

					//敵の情報を持った番号を取得
					D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
					D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

					if (objType == OBJTYPE_ENEMY)
					{
						if (m_pos.x + ENEMY_SIZE_X >= pos.x - size.x && m_pos.x - ENEMY_SIZE_X < pos.x + size.x
							&& m_pos.y + ENEMY_SIZE_Y >= pos.y - size.y  && m_pos.y - ENEMY_SIZE_Y < pos.y + size.y)
						{
							//このBGMを流す
							pSound->Play(pSound->SOUND_LABEL_EXPLOSION);

							CExplosion::Create(m_pos, m_size);
							m_state = PLAYER_STATE_DAMAGE;
							CLife *pLife;
							pLife = CGame::GetLife();
							pLife->AddLife(-1);
							return;
						}
					}
					else if (objType == OBJTYPE_ENEMYBULLET)
					{
						if (m_pos.x + PLAYER_SIZE_X >= pos.x - ENEMY_BULLET_SIZE_X && m_pos.x - PLAYER_SIZE_X< pos.x + ENEMY_BULLET_SIZE_X
							&& m_pos.y + PLAYER_SIZE_Y >= pos.y - ENEMY_BULLET_SIZE_Y && m_pos.y-PLAYER_SIZE_Y < pos.y + ENEMY_BULLET_SIZE_Y)
						{
							//このBGMを流す
							pSound->Play(pSound->SOUND_LABEL_EXPLOSION);

							CExplosion::Create(pos, m_size);
							m_state = PLAYER_STATE_DAMAGE;
							CLife *pLife;
							pLife = CGame::GetLife();
							pLife->AddLife(-1);

							return;
						}
					}
					
					if (objType == OBJTYPE_BOSSENEMY)
					{
						if (m_pos.x + 25.0f >= pos.x - size.x && m_pos.x - 25.0f < pos.x + size.x
							&& m_pos.y + 10.0f >= pos.y - size.y  && m_pos.y - 10.0f < pos.y + size.y)
						{
							//このBGMを流す
							pSound->Play(pSound->SOUND_LABEL_EXPLOSION);

							CExplosion::Create(m_pos, m_size);
							//Uninit();
							//CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - PLAYER_SIZE_Y, 0.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f), PLAYER_LIFE);
							m_state = PLAYER_STATE_DAMAGE;
							CLife *pLife;
							pLife = CGame::GetLife();
							pLife->AddLife(-1);
							return;
						}
					}

				}
			}
		}

	}

//--------------------------------------------------//
//弾の管理
//-------------------------------------------------//

	//----------------//
	//通常弾
	//---------------//
	if (nScore >= 0  && nScore <= PLAYER_EVOSCORE1 -1)
	{
		if (CManager::GetInputKeyboard()->GetPress(DIK_SPACE) == true)
		{
			m_interval++;
			if (m_interval >= 20)
			{
				//弾の生成
				move = D3DXVECTOR3(0.0f, -BULLET_MOVE_Y, 0.0f);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_X, 0.0f), CBullet::TYPE_NORMAL);

				//このBGMを流す
				pSound->Play(pSound->SOUND_LABEL_SHOT000);

				m_interval = 0;
			}
		}
	}
	//----------------//
	//散弾(2発)
	//---------------//

	
	else if (nScore >= PLAYER_EVOSCORE1 && nScore <= PLAYER_EVOSCORE2 - 1)
	{
		if (CManager::GetInputKeyboard()->GetPress(DIK_SPACE) == true)
		{
			m_interval++;
			if (m_interval >= 30)
			{
				//弾の生成
				move = D3DXVECTOR3(0.0f, -BULLET_MOVE_Y, 0.0f);
				CBullet::Create(pos - D3DXVECTOR3(20.0f, 0.0f, 0.0f), move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_STRAIGHT);
				CBullet::Create(pos + D3DXVECTOR3(20.0f, 0.0f, 0.0f), move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_STRAIGHT);

				//CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_LEFTUP);
				//CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_RIGHTUP);

				//このBGMを流す
				pSound->Play(pSound->SOUND_LABEL_SHOT000);

				m_interval = 0;
			}
		}

	}


	//----------------//
	//散弾(3発)
	//---------------//

	else if (nScore >= PLAYER_EVOSCORE2 && nScore <= PLAYER_EVOSCORE3 - 1)
	{
		if (CManager::GetInputKeyboard()->GetPress(DIK_SPACE) == true)
		{
			m_interval++;
			if (m_interval >= 30)
			{
				//弾の生成
				move = D3DXVECTOR3(0.0f, -BULLET_MOVE_Y, 0.0f);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_STRAIGHT);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_LEFTUP);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_RIGHTUP);

				//このBGMを流す
				pSound->Play(pSound->SOUND_LABEL_SHOT000);

				m_interval = 0;
			}
		}

	}


	//----------------//
	//散弾(3発)(高レート)
	//---------------//

	else if (nScore >= PLAYER_EVOSCORE3)
	{
		if (CManager::GetInputKeyboard()->GetPress(DIK_SPACE) == true)
		{
			m_interval++;
			if (m_interval >= 15)
			{
				//弾の生成
				move = D3DXVECTOR3(0.0f, -BULLET_MOVE_Y, 0.0f);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_STRAIGHT);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_LEFTUP);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_RIGHTUP);

				//このBGMを流す
				pSound->Play(pSound->SOUND_LABEL_SHOT000);

				m_interval = 0;
			}
		}

	}








	//Aキー（左）
	if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true)
	{
		//左上
		if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true)
		{
			pos.y += cosf(-3.14f*0.75f) / 0.2f;
		}
		//左下
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true)
		{
			pos.y += cosf(-3.14f*0.25f) / 0.2f;
		}
		//キー入力処理
		pos.x -= PLAYER_SPEED;
	}

	//Dキー（右）
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D) == true)
	{
		//右上
		if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true)
		{
			pos.y += cosf(3.14f*0.75f) / 0.2f;
		}
		//右下
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true)
		{
			pos.y += cosf(3.14f*0.25) / 0.2f;
		}

		pos.x += PLAYER_SPEED;

	}

	else if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true)
	{
		pos.y -= PLAYER_SPEED;

	}

	else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true)
	{
		pos.y += PLAYER_SPEED;

	}

	//移動制限処理
	if (pos.y - PLAYER_SIZE_Y <= 0)
	{
		pos.y = 0 + PLAYER_SIZE_Y;
	}
	else if (pos.y + PLAYER_SIZE_Y >= SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - PLAYER_SIZE_Y;
	}
	if (pos.x - PLAYER_SIZE_X <= 0)
	{
		pos.x = 0 + PLAYER_SIZE_X;
	}
	else if (pos.x+ PLAYER_SIZE_X >= SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - PLAYER_SIZE_X;
	}





	SetPosition(pos,m_size);
}

void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

void CPlayer::SetState(CPlayer::PLAYER_STATE state) 
{
	m_state = state;
}

