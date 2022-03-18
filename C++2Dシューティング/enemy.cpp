#include "enemy.h"
#include "bg.h"
#include "inputKeyboard.h"
#include "explosion.h"
#include "enemybullet.h"
#include "sound.h"


LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TYPE_MAX] = {};

CEnemy::CEnemy(int nPriority) : CScene2D(nPriority)
{

}

CEnemy::~CEnemy()
{

}

HRESULT CEnemy::Load(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data/enemy001.png",
		&m_apTexture[TYPE_BONE]);

	D3DXCreateTextureFromFile(pDevice,
		"data/enemy002.png",
		&m_apTexture[TYPE_SLIME]);

	D3DXCreateTextureFromFile(pDevice,
		"data/enemy003.png",
		&m_apTexture[TYPE_FIGHTER01]);

	D3DXCreateTextureFromFile(pDevice,
		"data/enemy004.png",
		&m_apTexture[TYPE_FIGHTER02]);

	D3DXCreateTextureFromFile(pDevice,
		"data/enemy005.png",
		&m_apTexture[TYPE_FIGHTER03]);

	D3DXCreateTextureFromFile(pDevice,
		"data/enemy006.png",
		&m_apTexture[TYPE_FIGHTER04]);

	D3DXCreateTextureFromFile(pDevice,
		"data/enemy007.png",
		&m_apTexture[TYPE_FIGHTER05]);



	return S_OK;
}

void CEnemy::Unload(void)
{
	//ƒeƒNƒXƒ`ƒƒ‚Ì”jŠü
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, TYPE type)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy;
	pEnemy->Init(pos,move, size, nLife);
	pEnemy->m_Type = type;
	pEnemy->BindTexture(m_apTexture[type]);

	pEnemy->SetObjType(CScene::OBJTYPE_ENEMY);
	return pEnemy;
}

HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife)
{
	CScene::SetEnemyLife(nLife);
	CScene2D::Init(pos, size);
	m_pos = pos;
	m_size = size;
	m_move = move;

	return S_OK;
}

void CEnemy::Uninit(void)
{
	CScene2D::Uninit();

	CSound *pSound;
	pSound = CManager::GetSound();

	//‚±‚ÌBGM‚ðŽ~‚ß‚é
	pSound->StopSound(pSound->SOUND_LABEL_EXPLOSION);

}

void CEnemy::Update(void)
{
	CSound *pSound;
	pSound = CManager::GetSound();

	//CScene2D::Update();
	//D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	//pos = GetPosition();
	SetPosition(m_pos, m_size);

	//“G‚Ìs“®
	if (m_Type == TYPE_BONE)
	{
		m_interval++;
		m_pos.y += 1.0f;
		if (m_interval >= 200)
		{
			//’e‚Ìmove
			move = D3DXVECTOR3(0.0f, -ENEMY_BULLET_MOVE_Y, 0.0f);
			CEnemyBullet::Create(D3DXVECTOR3(m_pos.x,m_pos.y + 30.0f,0.0f), move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 0.0f), m_size, CEnemyBullet::TYPE_NORMAL);

			m_interval = 0;
		}
	}

	if (m_Type == TYPE_SLIME)
	{
		m_pos.y += 1.0f;
		m_nActTime++;
		if (m_nActTime >= 100)
		{
			m_pos.y += 1.0f;
			m_pos.x -= 1.0f;

			if (m_nActTime >= 200)
			{
				m_pos.x += 1.0f;
				m_pos.y -= 1.0f;
			}
		}
	}

	if (m_Type == TYPE_FIGHTER01)
	{
		m_interval++;
		m_pos += m_move;

		if (m_interval >= 300)
		{	
			m_move.x = ENEMY_SPEED;
			m_move.y = ENEMY_SPEED;
			//’e‚Ìmove
			move = D3DXVECTOR3(0.0f, -ENEMY_BULLET_MOVE_Y, 0.0f);
			CEnemyBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, 0.0f), move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 0.0f), m_size, CEnemyBullet::TYPE_NORMAL);
			m_interval= 0;
		}
		
	}

	if (m_Type == TYPE_FIGHTER02)
	{
		m_interval++;
		m_pos += m_move;

		if (m_interval >= 300)
		{
			m_move.x = -ENEMY_SPEED;
			m_move.y = ENEMY_SPEED;
			//’e‚Ìmove
			move = D3DXVECTOR3(0.0f, -ENEMY_BULLET_MOVE_Y, 0.0f);
			CEnemyBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, 0.0f), move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 0.0f), m_size, CEnemyBullet::TYPE_NORMAL);
			m_interval = 0;
		}
	}

	if (m_Type == TYPE_FIGHTER03)
	{
		m_interval++;
		//m_pos += m_move;
		m_pos.x += 1.0f;

		if (m_interval >= 420)
		{
			m_move.x = -ENEMY_SPEED;
			m_move.y = ENEMY_SPEED;
			//’e‚Ìmove
			move = D3DXVECTOR3(0.0f, -ENEMY_BULLET_MOVE_Y, 0.0f);
			CEnemyBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, 0.0f), move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 0.0f), m_size, CEnemyBullet::TYPE_NORMAL);
			m_interval = 0;
		}
	}

	if (m_Type == TYPE_FIGHTER04)
	{
		m_interval++;
		m_pos.x -= 1.0f;

		if (m_interval >= 420)
		{
			m_move.x = -ENEMY_SPEED;
			m_move.y = ENEMY_SPEED;
			//’e‚Ìmove
			move = D3DXVECTOR3(0.0f, -ENEMY_BULLET_MOVE_Y, 0.0f);
			CEnemyBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, 0.0f), move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, 0.0f), m_size, CEnemyBullet::TYPE_NORMAL);
			m_interval = 0;
		}
	}

	if (m_Type == TYPE_FIGHTER05)
	{
		m_interval++;
		if (m_interval >= 480)
		{
			//’e‚Ìmove
			move = D3DXVECTOR3(0.0f, -ENEMY_BULLET_MOVE_Y, 0.0f);
			CEnemyBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, 0.0f), -move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, 10.0f, 0.0f), m_size, CEnemyBullet::TYPE_LEFTUP);
			CEnemyBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, 0.0f), -move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, 10.0f, 0.0f), m_size, CEnemyBullet::TYPE_RIGHTUP);
			CEnemyBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, 0.0f), -move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, 10.0f, 0.0f), m_size, CEnemyBullet::TYPE_LEFT);
			CEnemyBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, 0.0f), -move, D3DXVECTOR3(ENEMY_BULLET_SIZE_X, 10.0f, 0.0f), m_size, CEnemyBullet::TYPE_RIGHT);

			m_interval = 0;
		}
	}



	//“G‚ª”ÍˆÍŠO‚Éo‚½‚çÁ‚·
	if (m_pos.y >= SCREEN_HEIGHT + ENEMY_SIZE_Y || m_pos.x >= SCREEN_WIDTH +ENEMY_SCREEN_LIMIT_X || m_pos.x <= -ENEMY_SCREEN_LIMIT_X)
	{
		Uninit();
		return;
	}



}

void CEnemy::Draw(void)
{
	CScene2D::Draw();
}



