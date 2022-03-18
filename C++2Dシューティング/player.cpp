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

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CPlayer::m_pTexture = NULL;


CPlayer::CPlayer(int nPriority) : CScene2D(nPriority)
{
	//������
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

	//�e�N�X�`���̔j��
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

	//����BGM���~�߂�
	pSound->StopSound(pSound->SOUND_LABEL_SHOT000);
}

void CPlayer::Update(void)
{
	//CScene2D::Update();
	CSound *pSound;
	pSound = CManager::GetSound();
	//�X�R�A�擾
	CScore *pScore;
	pScore = CGame::GetScore();
	int nScore = pScore->GetScore();


	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	//�v���C���[�H
	pos = GetPosition();
	//�G�H
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

		//��莞�Ԃ��o������
		if (m_nInvincible >= 180)
		{
			m_state = PLAYER_STATE_NORMAL;
			m_nInvincible = 0;
		}
		break;
	default:
		break;
	}
	
	//�����蔻��
	if (m_state != PLAYER_STATE_DAMAGE)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
			{
				//�I�u�W�F�N�g�̔ԍ����擾�iBullet���ǂ��ɂ��邩�T���j
				CScene *pScene;
				pScene = CScene::GetScene(nCntPriority, nCntScene);
				if (pScene != NULL)
				{
					//��ނ��擾
					CScene::OBJTYPE objType;
					objType = pScene->GetObjType();

					//�G�̏����������ԍ����擾
					D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
					D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

					if (objType == OBJTYPE_ENEMY)
					{
						if (m_pos.x + ENEMY_SIZE_X >= pos.x - size.x && m_pos.x - ENEMY_SIZE_X < pos.x + size.x
							&& m_pos.y + ENEMY_SIZE_Y >= pos.y - size.y  && m_pos.y - ENEMY_SIZE_Y < pos.y + size.y)
						{
							//����BGM�𗬂�
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
							//����BGM�𗬂�
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
							//����BGM�𗬂�
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
//�e�̊Ǘ�
//-------------------------------------------------//

	//----------------//
	//�ʏ�e
	//---------------//
	if (nScore >= 0  && nScore <= PLAYER_EVOSCORE1 -1)
	{
		if (CManager::GetInputKeyboard()->GetPress(DIK_SPACE) == true)
		{
			m_interval++;
			if (m_interval >= 20)
			{
				//�e�̐���
				move = D3DXVECTOR3(0.0f, -BULLET_MOVE_Y, 0.0f);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_X, 0.0f), CBullet::TYPE_NORMAL);

				//����BGM�𗬂�
				pSound->Play(pSound->SOUND_LABEL_SHOT000);

				m_interval = 0;
			}
		}
	}
	//----------------//
	//�U�e(2��)
	//---------------//

	
	else if (nScore >= PLAYER_EVOSCORE1 && nScore <= PLAYER_EVOSCORE2 - 1)
	{
		if (CManager::GetInputKeyboard()->GetPress(DIK_SPACE) == true)
		{
			m_interval++;
			if (m_interval >= 30)
			{
				//�e�̐���
				move = D3DXVECTOR3(0.0f, -BULLET_MOVE_Y, 0.0f);
				CBullet::Create(pos - D3DXVECTOR3(20.0f, 0.0f, 0.0f), move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_STRAIGHT);
				CBullet::Create(pos + D3DXVECTOR3(20.0f, 0.0f, 0.0f), move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_STRAIGHT);

				//CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_LEFTUP);
				//CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_RIGHTUP);

				//����BGM�𗬂�
				pSound->Play(pSound->SOUND_LABEL_SHOT000);

				m_interval = 0;
			}
		}

	}


	//----------------//
	//�U�e(3��)
	//---------------//

	else if (nScore >= PLAYER_EVOSCORE2 && nScore <= PLAYER_EVOSCORE3 - 1)
	{
		if (CManager::GetInputKeyboard()->GetPress(DIK_SPACE) == true)
		{
			m_interval++;
			if (m_interval >= 30)
			{
				//�e�̐���
				move = D3DXVECTOR3(0.0f, -BULLET_MOVE_Y, 0.0f);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_STRAIGHT);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_LEFTUP);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_RIGHTUP);

				//����BGM�𗬂�
				pSound->Play(pSound->SOUND_LABEL_SHOT000);

				m_interval = 0;
			}
		}

	}


	//----------------//
	//�U�e(3��)(�����[�g)
	//---------------//

	else if (nScore >= PLAYER_EVOSCORE3)
	{
		if (CManager::GetInputKeyboard()->GetPress(DIK_SPACE) == true)
		{
			m_interval++;
			if (m_interval >= 15)
			{
				//�e�̐���
				move = D3DXVECTOR3(0.0f, -BULLET_MOVE_Y, 0.0f);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_STRAIGHT);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_LEFTUP);
				CBullet::Create(pos, move, D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f), m_size, CBullet::TYPE_RIGHTUP);

				//����BGM�𗬂�
				pSound->Play(pSound->SOUND_LABEL_SHOT000);

				m_interval = 0;
			}
		}

	}








	//A�L�[�i���j
	if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true)
	{
		//����
		if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true)
		{
			pos.y += cosf(-3.14f*0.75f) / 0.2f;
		}
		//����
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true)
		{
			pos.y += cosf(-3.14f*0.25f) / 0.2f;
		}
		//�L�[���͏���
		pos.x -= PLAYER_SPEED;
	}

	//D�L�[�i�E�j
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D) == true)
	{
		//�E��
		if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true)
		{
			pos.y += cosf(3.14f*0.75f) / 0.2f;
		}
		//�E��
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

	//�ړ���������
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

