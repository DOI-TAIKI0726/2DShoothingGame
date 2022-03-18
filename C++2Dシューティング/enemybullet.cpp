#include "enemybullet.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "game.h"
#include "player.h"
#include "life.h"
#include "fade.h"


//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CEnemyBullet::m_apTexture[TYPE_MAX] = {};

CEnemyBullet::CEnemyBullet(int nPriority) : CScene2D(nPriority)
{

}

CEnemyBullet::~CEnemyBullet()
{

}

CEnemyBullet *CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,D3DXVECTOR3 exsize, TYPE type)
{
	CEnemyBullet *pEnemyBullet = NULL;
	pEnemyBullet = new CEnemyBullet;
	if (pEnemyBullet != NULL)
	{
		pEnemyBullet->Init(pos, move, size,exsize, type);
		pEnemyBullet->m_Type = type;
		pEnemyBullet->BindTexture(m_apTexture[type]);
		//�I�u�W�F�N�g�̎�ނ̐ݒ�
		pEnemyBullet->SetObjType(CScene::OBJTYPE_ENEMYBULLET);
	}
	return pEnemyBullet;
}

HRESULT CEnemyBullet::Load(void)
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
		&m_apTexture[TYPE_LEFTUP]);

	D3DXCreateTextureFromFile(pDevice,
		"data/bullet0.png",
		&m_apTexture[TYPE_RIGHTUP]);

	D3DXCreateTextureFromFile(pDevice,
		"data/bullet0.png",
		&m_apTexture[TYPE_LEFT]);

	D3DXCreateTextureFromFile(pDevice,
		"data/bullet0.png",
		&m_apTexture[TYPE_RIGHT]);


	D3DXCreateTextureFromFile(pDevice,
		"data/slime.png",
		&m_apTexture[TYPE_BEAM]);

	return S_OK;
}

void CEnemyBullet::Unload(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}



HRESULT CEnemyBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 exsize, TYPE type)
{
	CScene2D::Init(pos, size);

	m_size = size;
	m_exsize = exsize;


	//�e�̏����ݒ�
	m_move = move;

	//�e�̎���
	m_nLife = 720.0f;

	return S_OK;
}

void CEnemyBullet::Uninit(void)
{
	CScene2D::Uninit();
}

void CEnemyBullet::Update(void)
{
	
	if (m_Type == TYPE_NORMAL)
	{
		m_col.a = 40.0f;
		m_col.r = 255.0f;
		m_col.b = 0.0f;
		m_col.g = 0.0f;
	}
	else if (m_Type == TYPE_STRAIGHT || m_Type == TYPE_RIGHTUP || m_Type == TYPE_LEFTUP)
	{
		m_col.a = 40.0f;
		m_col.r = 255.0f;
		m_col.b = 0.0f;
		m_col.g = 0.0f;
	}

	m_pos = GetPosition();

	//�ʏ�e
	if (m_Type == TYPE_NORMAL)
	{
		m_pos -= m_move;
		m_nActTime++;
		m_nLife--;
		//�ʒu���X�V
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}

	//���i�e
	if (m_Type == TYPE_STRAIGHT)
	{
		m_pos += m_move;
		m_nActTime++;

		m_nLife--;
		//�ʒu���X�V
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}

	//����e
	if (m_Type == TYPE_LEFTUP)
	{
		m_pos += m_move;
		m_pos.x -= 3.0f;

		m_nLife--;
		//�ʒu���X�V
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}

	//�E��e
	if (m_Type == TYPE_RIGHTUP)
	{
		m_pos += m_move;
		m_pos.x += 3.0f;
		m_nLife--;

		//�ʒu���X�V
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);

	}

	//���e
	if (m_Type == TYPE_LEFT)
	{
		m_pos.x -= ENEMY_BULLET_MOVE_X;
		m_nActTime++;

		m_nLife--;
		//�ʒu���X�V
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}

	//�E�e
	if (m_Type == TYPE_RIGHT)
	{
		m_pos.x += ENEMY_BULLET_MOVE_X;
		m_nActTime++;

		m_nLife--;
		//�ʒu���X�V
		SetPosition(m_pos, m_size);
		CEffect::Create(m_pos, D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), m_col);
	}



	//�e���͈͊O�ɏo�������
	if (m_pos.y <= 0 || m_pos.y >= 1280)
	{
		Uninit();
		return;
	}

	//������0�ɂȂ�����e������
	if (m_nLife <= 0)
	{
		CExplosion::Create(m_pos, m_size);
		Uninit();
		return;
	}

	if (m_pos.y >= +725.0f)
	{
		Uninit();
	}



}

void CEnemyBullet::Draw(void)
{
	CScene2D::Draw();
}
