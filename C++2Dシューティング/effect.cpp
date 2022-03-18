#include "effect.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CEffect::m_pTexture = NULL;



CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{

}

CEffect::~CEffect()
{

}

CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DCOLORVALUE col)
{
	CEffect *pEffect = NULL;
	pEffect = new CEffect;
	if (pEffect != NULL)
	{
		pEffect->Init(pos, size, col);
		pEffect->BindTexture(m_pTexture);
		//�I�u�W�F�N�g�̎�ނ̐ݒ�
		pEffect->SetObjType(CScene::OBJTYPE_EFFECT);
	}
	return pEffect;

}

HRESULT CEffect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data/effect000.jpg",
		&m_pTexture);

	return S_OK;
}

void CEffect::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}



HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DCOLORVALUE col)
{
	CScene2D::Init(pos, size);
	m_pos = pos;
	m_size = size;
	m_col = col;

	m_nEffectLife = 60.0f;
	return S_OK;
}

void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

void CEffect::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	m_size.x -= 0.2f;
	m_size.y -= 0.6f;
	m_nEffectLife--;

	CScene2D::Update();

	if (m_size.x <= 0.0f || m_size.y <= 0.0f)
	{
		Uninit();
		return;
	}
	if (m_nEffectLife <= 0.0f)
	{
		Uninit();
		return;
	}

	CScene2D::SetCol(m_col);
	CScene2D::SetPosition(pos, m_size);
}

void CEffect::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

