#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "game.h"
#include "player.h"
#include "fade.h"
#include "explosion.h"
#include "boss_enemy.h"
#include "sound.h"
//静的メンバ変数
LPDIRECT3DTEXTURE9	CBullet::m_apTexture[TYPE_MAX] = {};

CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	
}

CBullet::~CBullet()
{

}

CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 exsize, TYPE type)
{
	CBullet *pBullet = NULL;
 	pBullet = new CBullet;
	if (pBullet != NULL)
	{
		pBullet->Init(pos, move,size,exsize,type);
		pBullet->m_Type = type;
		pBullet->BindTexture(m_apTexture[type]);
		//オブジェクトの種類の設定
		pBullet->SetObjType(CScene::OBJTYPE_BULLET);
	}
	return pBullet;

}

HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data/bullet0.png",
		&m_apTexture[TYPE_NORMAL]);

	D3DXCreateTextureFromFile(pDevice,
		"data/bullet0.png",
		&m_apTexture[TYPE_STRAIGHT]);

	D3DXCreateTextureFromFile(pDevice,
		"data/bullet0.png",
		&m_apTexture[TYPE_LEFT]);

	D3DXCreateTextureFromFile(pDevice,
		"data/bullet0.png",
		&m_apTexture[TYPE_RIGHT]);


	D3DXCreateTextureFromFile(pDevice,
		"data/bullet0.png",
		&m_apTexture[TYPE_LEFTUP]);

	D3DXCreateTextureFromFile(pDevice,
		"data/bullet0.png",
		&m_apTexture[TYPE_RIGHTUP]);

	D3DXCreateTextureFromFile(pDevice,
		"data/slime.png",
		&m_apTexture[TYPE_BEAM]);


	return S_OK;
}

void CBullet::Unload(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}



HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 exsize, TYPE type)
{
	CScene2D::Init(pos,size);
	

	//弾の初期設定
	m_size = size;
	m_exsize = exsize;
	m_move = move;

	//弾の寿命
	m_nLife = 720.0f;


	return S_OK;
}

void CBullet::Uninit(void)
{
	CScene2D::Uninit();

	CSound *pSound;
	pSound = CManager::GetSound();
	//このBGMを止める
	pSound->StopSound(pSound->SOUND_LABEL_EXPLOSION);

}

void CBullet::Update(void)
{
	CSound *pSound;
	pSound = CManager::GetSound();


	if (m_Type == TYPE_NORMAL)
	{
		m_col.a = 40.0f;
		m_col.r = 255.0f;
		m_col.b = 0.0f;
		m_col.g = 0.0f;
	}
	else if (m_Type == TYPE_STRAIGHT || m_Type == TYPE_LEFT || m_Type == TYPE_RIGHT ||
			 m_Type == TYPE_RIGHTUP || m_Type == TYPE_LEFTUP)
	{
		m_col.a = 40.0f;
		m_col.r = 0.0f;
		m_col.b = 255.0f;
		m_col.g = 0.0f;
	}

	m_pos = GetPosition();

	//通常弾
	if (m_Type == TYPE_NORMAL)
	{
		m_pos += m_move;
		m_nActTime++;

		m_nLife--;
		//位置を更新
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}

	//直進弾
	if (m_Type == TYPE_STRAIGHT)
	{
		m_pos += m_move;
		m_nActTime++;

		m_nLife--;
		//位置を更新
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}

	//左上弾
	if (m_Type == TYPE_LEFTUP)
	{
		m_pos += m_move;
		m_pos.x -= 10.0f;

		m_nLife--;
		//位置を更新
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}

	//右上弾
	if (m_Type == TYPE_RIGHTUP)
	{
		m_pos += m_move;
		m_pos.x += 10.0f;

		m_nLife--;
		//位置を更新
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}

	//左弾
	if (m_Type == TYPE_LEFT)
	{
		m_pos.x -= BULLET_MOVE_X;
		m_nActTime++;

		m_nLife--;
		//位置を更新
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}

	//右弾
	if (m_Type == TYPE_RIGHT)
	{
		m_pos.x += BULLET_MOVE_X;
		m_nActTime++;

		m_nLife--;
		//位置を更新
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}



	//ビーム
	if (m_Type == TYPE_BEAM)
	{
		m_pos += m_move;
		m_nActTime++;

		m_nLife--;
		//位置を更新
		SetPosition(m_pos, m_size);
		//CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}


	//寿命が0になったら弾を消す
	if (m_nLife <= 0)
	{
		CExplosion::Create(m_pos,m_size);
		Uninit();
		return;
	}

	if (m_pos.y <= -6.0f)
	{
		Uninit();
	}

	//当たり判定
	for (int nCntScene = 0; nCntScene < MAX_SCENE;nCntScene++)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			//オブジェクトの番号を取得（Bulletがどこにあるか探す）
			CScene *pScene;
			pScene = CScene::GetScene(nCntPriority,nCntScene);
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
					if (m_pos.x >= pos.x - size.x && m_pos.x < pos.x + size.x
						&& m_pos.y >= pos.y - size.y && m_pos.y < pos.y + size.y)
					{
						CExplosion::Create(pos,m_exsize);

						int nEnemyLife = pScene->GetEnemyLife();
						//--は-=1と同じ
						nEnemyLife--;
						pScene->SetEnemyLife(nEnemyLife);
						Uninit();

						if (nEnemyLife <= 0)
						{
							CScore *pScore;
							pScore = CGame::GetScore();
							pScore->AddScore(ENEMY_SCORE);

							//敵を消す
							pScene->Uninit();
							//このBGMを流す
							pSound->Play(pSound->SOUND_LABEL_EXPLOSION);

							return;
						}
					}
				}
				else if (objType == OBJTYPE_BOSSENEMY)
				{
					if (m_pos.x >= pos.x - size.x && m_pos.x < pos.x + size.x
						&& m_pos.y >= pos.y - size.y && m_pos.y < pos.y + size.y)
					{
						CExplosion::Create(m_pos, D3DXVECTOR3(BOSS_EXPLOSION_SIZE_X, BOSS_EXPLOSION_SIZE_Y, 0.0f));

						int nEnemyLife = pScene->GetEnemyLife();
						//--は-=1と同じ
						nEnemyLife--;
						pScene->SetEnemyLife(nEnemyLife);
						Uninit();

						if (nEnemyLife <= 0)
						{
							CScore *pScore;
							pScore = CGame::GetScore();
							pScore->AddScore(BOSSENEMY_SCORE);
							//フェード
							CFade *pFade = CManager::GetFade();
							//フェードの処理の時は必須
							if (pFade->GetFade() == CFade::FADE_NONE)
							{
								pFade->SetFade(CManager::MODE_RESULT);
							}

							//敵を消す
							pScene->Uninit();
							//このBGMを流す
							pSound->Play(pSound->SOUND_LABEL_EXPLOSION);

							return;
						}
					}

				}
			}
		}

	}

}

void CBullet::Draw(void)
{
	CScene2D::Draw();
}

