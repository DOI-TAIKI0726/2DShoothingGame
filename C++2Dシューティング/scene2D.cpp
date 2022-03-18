#include "scene2D.h"
#include "manager.h"


CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{

}

CScene2D::~CScene2D()
{

}

HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
		//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_2D *pVtx;  //���_���ւ̃|�C���^

					  //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;
	m_size = size;
	//���_���W�̐ݒ�

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffer->Unlock();

	return S_OK;
}

void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffer != NULL)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = NULL;
	}

	//�I�u�W�F�N�g�̔j���i��ԍŌ�̍s�ɏ����j
	Release();
}

void CScene2D::Update(void)
{

	//VERTEX_2D *pVtx;  //���_���ւ̃|�C���^

	////���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	//m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuffer->Unlock();
}

void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	
	pDevice = CManager::GetRenderer()->GetDevice();  //�f�o�C�X���擾����

	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D); //���_�t�H�[�}�b�g�̐ݒ�

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;
	if (pScene2D != NULL)
	{
		pScene2D->Init(pos,size);
	}
	return pScene2D;
}

void CScene2D::SetPosition(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	VERTEX_2D *pVtx;  //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffer->Unlock();

}

D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

void CScene2D::SetTex(int nPattern,float fTexU,float fTexV)
{
	VERTEX_2D *pVtx;  //���_���ւ̃|�C���^

	m_fTexU = fTexU;
	m_fTexV = fTexV;

	//���_���W�����b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W���X�V
	pVtx[0].tex = D3DXVECTOR2((nPattern * m_fTexU) + 0.0f,    0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPattern * m_fTexU) + m_fTexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nPattern * m_fTexU) + 0.0f,    m_fTexV);
	pVtx[3].tex = D3DXVECTOR2((nPattern * m_fTexU) + m_fTexU, m_fTexV);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();
}

void CScene2D::SetTex(float fTexU, float fTexV,float fMoveV)
{
	VERTEX_2D *pVtx;  //���_���ւ̃|�C���^

	m_fTexU = fTexU;
	m_fTexV = fTexV;

	//���_���W�����b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W���X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f,    fMoveV);
	pVtx[1].tex = D3DXVECTOR2(m_fTexU, fMoveV);
	pVtx[2].tex = D3DXVECTOR2(0.0f,	   fMoveV+ m_fTexV);
	pVtx[3].tex = D3DXVECTOR2(m_fTexU, fMoveV+ m_fTexV);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();

}

//�����擾(�ݒ�)
void CScene2D::SetSize(float fWidth, float fHeight)
{
	m_size = D3DXVECTOR3(fWidth, fHeight,0.0f);
}

//������GetSize�̏������炤
D3DXVECTOR3 CScene2D::GetSize(void)
{
	return m_size;
}

void CScene2D::SetCol(D3DCOLORVALUE col)
{
	VERTEX_2D *pVtx;  //���_���ւ̃|�C���^

	m_col = col;

	//���_���W�����b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W���X�V
	pVtx[0].col = D3DCOLOR_RGBA((int)m_col.r,(int)m_col.g,(int)m_col.b,(int)m_col.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)m_col.r,(int)m_col.g,(int)m_col.b,(int)m_col.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)m_col.r,(int)m_col.g,(int)m_col.b,(int)m_col.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)m_col.r,(int)m_col.g,(int)m_col.b,(int)m_col.a);
																			
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();
}

void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;  //���_���ւ̃|�C���^
	
    //���_���W�����b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);
	
	//�e�N�X�`�����W���X�V
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();

}




