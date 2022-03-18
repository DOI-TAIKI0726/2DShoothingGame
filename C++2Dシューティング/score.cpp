#include "score.h"
#include "number.h"
#include "count_timer.h"
#include "game.h"
#include "fade.h"

CScore::CScore(int nPriority) : CScene(nPriority)
{
	memset(&m_apNumber[0], 0, sizeof(m_apNumber));
	m_nScore = 0;
}

CScore::~CScore()
{

}

CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScore *pScore = NULL;
	pScore = new CScore;

	if (pScore != NULL)
	{
		pScore->Init(pos,size);
		pScore->SetObjType(CScene::OBJTYPE_SCORE);
	}
	return pScore;
}

HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_size = size;
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore]= CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCntScore, pos.y, 0.0f), m_size.x, m_size.y);
	}

	return S_OK;
}

void CScore::Uninit(void)
{
	//タイム分をスコアに加算
	CCountTimer *pCountTimer;
	pCountTimer = CGame::GetCountTimer();
	m_nScore += pCountTimer->GetCountTimer() * 10;


	FILE *pFile;
	pFile = fopen("NowScore.txt", "w");
	if (pFile != NULL)
	{
		fprintf(pFile, "%d", m_nScore);
	}
	else
	{
		printf("ファイルが読み込めません");
	}
	fclose(pFile);


	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		if (m_apNumber[nCntScore] != NULL)
		{
			m_apNumber[nCntScore]->Uninit();
			delete m_apNumber[nCntScore];
			m_apNumber[nCntScore] = NULL;
		}
	}
	Release();
}

void CScore::Update(void)
{
	m_apNumber[0]->SetNumber(m_nScore % 100000000 / 10000000);
	m_apNumber[1]->SetNumber(m_nScore % 10000000 / 1000000);
	m_apNumber[2]->SetNumber(m_nScore % 1000000 / 100000);
	m_apNumber[3]->SetNumber(m_nScore % 100000 / 10000);
	m_apNumber[4]->SetNumber(m_nScore % 10000 / 1000);
	m_apNumber[5]->SetNumber(m_nScore % 1000 / 100);
	m_apNumber[6]->SetNumber(m_nScore % 100 / 10);
	m_apNumber[7]->SetNumber(m_nScore % 10 / 1);

	
}

void CScore::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore]->Draw();
	}


}

//スコアのセット
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

int CScore::GetScore(void)
{
	return m_nScore;
}

