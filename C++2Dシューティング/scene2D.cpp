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
		//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_2D *pVtx;  //頂点情報へのポインタ

					  //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;
	m_size = size;
	//頂点座標の設定

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

	//頂点バッファをアンロックする
	m_pVtxBuffer->Unlock();

	return S_OK;
}

void CScene2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuffer != NULL)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = NULL;
	}

	//オブジェクトの破棄（一番最後の行に書く）
	Release();
}

void CScene2D::Update(void)
{

	//VERTEX_2D *pVtx;  //頂点情報へのポインタ

	////頂点バッファをロックし、頂点データへのポインタを取得
	//m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	////頂点バッファをアンロックする
	//m_pVtxBuffer->Unlock();
}

void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	
	pDevice = CManager::GetRenderer()->GetDevice();  //デバイスを取得する

	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));  //頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_2D); //頂点フォーマットの設定

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
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

	VERTEX_2D *pVtx;  //頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//頂点バッファをアンロックする
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
	VERTEX_2D *pVtx;  //頂点情報へのポインタ

	m_fTexU = fTexU;
	m_fTexV = fTexV;

	//頂点座標をロック
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2((nPattern * m_fTexU) + 0.0f,    0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPattern * m_fTexU) + m_fTexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nPattern * m_fTexU) + 0.0f,    m_fTexV);
	pVtx[3].tex = D3DXVECTOR2((nPattern * m_fTexU) + m_fTexU, m_fTexV);

	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();
}

void CScene2D::SetTex(float fTexU, float fTexV,float fMoveV)
{
	VERTEX_2D *pVtx;  //頂点情報へのポインタ

	m_fTexU = fTexU;
	m_fTexV = fTexV;

	//頂点座標をロック
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2(0.0f,    fMoveV);
	pVtx[1].tex = D3DXVECTOR2(m_fTexU, fMoveV);
	pVtx[2].tex = D3DXVECTOR2(0.0f,	   fMoveV+ m_fTexV);
	pVtx[3].tex = D3DXVECTOR2(m_fTexU, fMoveV+ m_fTexV);

	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();

}

//情報を取得(設定)
void CScene2D::SetSize(float fWidth, float fHeight)
{
	m_size = D3DXVECTOR3(fWidth, fHeight,0.0f);
}

//ここでGetSizeの情報をもらう
D3DXVECTOR3 CScene2D::GetSize(void)
{
	return m_size;
}

void CScene2D::SetCol(D3DCOLORVALUE col)
{
	VERTEX_2D *pVtx;  //頂点情報へのポインタ

	m_col = col;

	//頂点座標をロック
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を更新
	pVtx[0].col = D3DCOLOR_RGBA((int)m_col.r,(int)m_col.g,(int)m_col.b,(int)m_col.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)m_col.r,(int)m_col.g,(int)m_col.b,(int)m_col.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)m_col.r,(int)m_col.g,(int)m_col.b,(int)m_col.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)m_col.r,(int)m_col.g,(int)m_col.b,(int)m_col.a);
																			
	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();
}

void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;  //頂点情報へのポインタ
	
    //頂点座標をロック
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);
	
	//テクスチャ座標を更新
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	
	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();

}




