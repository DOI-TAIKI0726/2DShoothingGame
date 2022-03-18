#include "fade.h"

LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;

CFade::CFade(int nPriority) : CScene2D(nPriority)
{
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fade = FADE_NONE;
}

CFade::~CFade()
{

}


CFade * CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CManager::MODE mode)
{
	CFade *pFade;
	pFade = new CFade;
	if (pFade != NULL)
	{
		pFade->Init(pos, size);
		pFade->BindTexture(m_pTexture);
		pFade->SetPosition(pos, size);
		pFade->SetSize(size.x, size.y);
		pFade->m_fade = FADE_OUT;
		pFade->m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pFade->m_mode = mode;
	}
	return pFade;
}

HRESULT CFade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_fade = FADE_IN;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	CScene2D::Init(pos, size);

	return S_OK;
}

void CFade::Uninit(void)
{
	CScene2D::Uninit();
}

void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_color.a -= 0.01f;
			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_color.a += 0.01f;
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;
				m_fade = FADE_IN;
				CManager::SetMode(m_mode);
			}
		}
		SetCol(m_color);
	}
}

void CFade::Draw(void)
{
	CScene2D::Draw();
}

void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_mode = modeNext;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}


