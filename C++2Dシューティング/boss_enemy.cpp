#include "boss_enemy.h"
#include "bg.h"
#include "inputKeyboard.h"
#include "explosion.h"
#include "enemybullet.h"
#include "sound.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CBossEnemy::m_pTexture = NULL;

CBossEnemy::CBossEnemy(int nPriority) : CScene2D(nPriority)
{
	m_BossBullet = BOSS_BULLET_NONE;
}

CBossEnemy::~CBossEnemy()
{

}

HRESULT CBossEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data/BossEnemy.png",
		&m_pTexture);

	return S_OK;
}

void CBossEnemy::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	
}

CBossEnemy *CBossEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife)
{
	CBossEnemy *pBossEnemy;
	pBossEnemy = new CBossEnemy;
	if (pBossEnemy != NULL)
	{
		pBossEnemy->Init(pos, size, nLife);
		pBossEnemy->BindTexture(m_pTexture);
		pBossEnemy->SetObjType(CScene::OBJTYPE_BOSSENEMY);
	}
	return pBossEnemy;
}

HRESULT CBossEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife)
{
	m_BossBullet = BOSS_BULLET_STRAIGHT;
	CScene::SetEnemyLife(nLife);
	CScene2D::Init(pos, size);
	m_pos = pos;
	m_size = size;
	return S_OK;
}

void CBossEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

void CBossEnemy::Update(void)
{
	CSound *pSound;
	pSound = CManager::GetSound();

	//CScene2D::Update();
	//D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	//pos = GetPosition();
	SetPosition(m_pos, m_size);

	//敵の行動
	m_interval++;
	m_nBossFrame++;

	switch (m_BossBullet)
	{
	case BOSS_BULLET_STRAIGHT:
		if (m_interval >= 120)
		{
			//弾のmove
			move = D3DXVECTOR3(0.0f, -ENEMY_BULLET_MOVE_Y, 0.0f);
			CEnemyBullet::Create(m_pos, move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 0.0f), m_size, CEnemyBullet::TYPE_NORMAL);
			m_interval = 0;
		}
		if (m_nBossFrame >= 120)
		{
			m_nBossFrame = 0;
			m_interval = 0;
			m_BossBullet = BOSS_BULLET_SG;
		}
		break;
	case BOSS_BULLET_SG:
		if (m_interval >= 120)
		{
			//弾のmove
			move = D3DXVECTOR3(0.0f, -ENEMY_BULLET_MOVE_Y, 0.0f);
			CEnemyBullet::Create(m_pos, move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 0.0f), m_size, CEnemyBullet::TYPE_NORMAL);
			CEnemyBullet::Create(m_pos, -move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 0.0f), m_size, CEnemyBullet::TYPE_LEFTUP);
			CEnemyBullet::Create(m_pos,-move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 0.0f), m_size, CEnemyBullet::TYPE_RIGHTUP);
			m_interval = 0;
		}
		if (m_nBossFrame >= 240)
		{
			m_nBossFrame = 0;
			m_interval = 0;
			m_BossBullet = BOSS_BULLET_STRAIGHT;
		}
		break;
	default:
		break;
	}
	
	//敵が範囲外に出たら消す
	if (m_pos.y <= 0 || m_pos.y >= SCREEN_HEIGHT + BOSS_ENEMY_SIZE_Y)
	{
		Uninit();
		return;
	}

}

void CBossEnemy::Draw(void)
{
	CScene2D::Draw();
}
