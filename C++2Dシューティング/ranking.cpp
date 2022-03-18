#include "score.h"
#include "number.h"
#include "ranking.h"

CScore *CRanking::m_apScore[MAX_RANKING] = {};


CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	memset(&m_nScore[0], 0, sizeof(m_nScore));
	m_nRanking = 0;
}

CRanking::~CRanking()
{

}

CRanking *CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CRanking *pRanking = NULL;
	pRanking = new CRanking;

	if (pRanking != NULL)
	{
		pRanking->Init(pos, size);
		pRanking->SetObjType(CScene::OBJTYPE_SCORE);
	}
	return pRanking;
}

HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{


	m_size = size;
	for (int nCntRank = 0; nCntRank < MAX_RANKING - 1; nCntRank++)
	{
		m_apScore[nCntRank] = CScore::Create(D3DXVECTOR3(pos.x, pos.y + m_size.y*nCntRank, 0.0f), D3DXVECTOR3(m_size.x, m_size.y,0.0f));
	}

	FILE *pFile;
	pFile = fopen("Ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
		{
			fscanf(pFile, "%d", &m_nScore[nCnt]);
		}
	}

	else
	{
		printf("ファイルが読み込めません");
	}
	fclose(pFile);

	pFile = fopen("NowScore.txt", "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nRanking);
	}
	else
	{
		printf("ファイルが読み込めません");
	}
	fclose(pFile);

	m_nScore[MAX_RANKING - 1] = m_nRanking;

	for (int nCnt = 0; nCnt < MAX_RANKING-1; nCnt++)
	{
		for (int nCntRank = 0; nCntRank < MAX_RANKING-1; nCntRank++)
		{
			if (m_nScore[nCntRank] < m_nScore[nCntRank + 1])
			{
				int nSubData = m_nScore[nCntRank];
				m_nScore[nCntRank] = m_nScore[nCntRank + 1];
				m_nScore[nCntRank + 1] = nSubData;
			}
		}
	}

	for (int nCnt = 0; nCnt < MAX_RANKING - 1;nCnt++)
	{
		m_apScore[nCnt]->SetScore(m_nScore[nCnt]);
	}

	m_nScore[MAX_RANKING - 1] = 0;

	pFile = fopen("Ranking.txt", "w");
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
		{
			fprintf(pFile, "%d\n", m_nScore[nCnt]);
		}
	}
	else
	{
		printf("ファイルが読み込めません");
	}
	fclose(pFile);

	

	return S_OK;
}

void CRanking::Uninit(void)
{
}

void CRanking::Update(void)
{

}

void CRanking::Draw(void)
{
}


