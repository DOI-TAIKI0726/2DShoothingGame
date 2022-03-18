#include "count_timer.h"
#include "number.h"
#include "score.h"
#include "game.h"
#include "fade.h"

CCountTimer::CCountTimer(int nPriority) : CScene(nPriority)
{
	memset(&m_apNumber[0], 0, sizeof(m_apNumber));
	m_nCountTimer = 100;
	m_bStop = true;
}

CCountTimer::~CCountTimer()
{

}

CCountTimer *CCountTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CCountTimer *pCountTimer = NULL;
	pCountTimer = new CCountTimer;

	if (pCountTimer != NULL)
	{
		pCountTimer->Init(pos, size);
		pCountTimer->SetObjType(CScene::OBJTYPE_COUNTTIMER);
	}
	return pCountTimer;
}

HRESULT CCountTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_size = size;
	for (int nCntCountTimer = 0; nCntCountTimer < MAX_TIMER_DIGHT; nCntCountTimer++)
	{
		m_apNumber[nCntCountTimer] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCntCountTimer, pos.y, 0.0f), m_size.x, m_size.y);
	}
	m_ndwCurrentTime = timeGetTime();
	m_ndwLastTime = timeGetTime();

	return S_OK;
}

void CCountTimer::Uninit(void)
{


	for (int nCntCountTimer = 0; nCntCountTimer < MAX_TIMER_DIGHT; nCntCountTimer++)
	{
		if (m_apNumber[nCntCountTimer] != NULL)
		{
			m_apNumber[nCntCountTimer]->Uninit();
			delete m_apNumber[nCntCountTimer];
			m_apNumber[nCntCountTimer] = NULL;
		}
	}
	Release();
}

void CCountTimer::Update(void)
{
	m_apNumber[0]->SetNumber(m_nCountTimer % 1000 / 100);
	m_apNumber[1]->SetNumber(m_nCountTimer % 100 / 10);
	m_apNumber[2]->SetNumber(m_nCountTimer % 10 / 1);

	m_ndwCurrentTime = timeGetTime();
	if (m_ndwCurrentTime - m_ndwLastTime >= 1000 && m_bStop == true)
	{
		m_nCountTimer--;
		m_ndwLastTime = m_ndwCurrentTime;
	}
	
	if (m_nCountTimer <= 0)
	{
		m_nCountTimer = 0;
		//フェード
		CFade *pFade = CManager::GetFade();
		//フェードの処理の時は必須
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_RESULT);
		}

	}
}

void CCountTimer::Draw(void)
{
	for (int nCntCountTimer = 0; nCntCountTimer < MAX_TIMER_DIGHT; nCntCountTimer++)
	{
		m_apNumber[nCntCountTimer]->Draw();
	}
}

//スコアのセット
void CCountTimer::SetCountTimer(int nCountTimer)
{
	m_nCountTimer = nCountTimer;
}

void CCountTimer::AddCountTimer(int nValue)
{
	m_nCountTimer += nValue;
}

int CCountTimer::GetCountTimer(void)
{
	return m_nCountTimer;
}
