#include "LevelUI.h"
#include "number.h"
#include "score.h"
#include "game.h"
#include "player.h"

CLevel::CLevel(int nPriority) : CScene(nPriority)
{
	memset(&m_apNumber[0], 0, sizeof(m_apNumber));
	m_nLevel = 0;
}

CLevel::~CLevel()
{

}

CLevel *CLevel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CLevel *pLevel = NULL;
	pLevel = new CLevel;

	if (pLevel != NULL)
	{
		pLevel->Init(pos, size);
		pLevel->SetObjType(CScene::OBJTYPE_LEVEL);
	}
	return pLevel;
}

HRESULT CLevel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_size = size;
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		m_apNumber[nCntLevel] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCntLevel, pos.y, 0.0f), m_size.x, m_size.y);
	}

	return S_OK;
}

void CLevel::Uninit(void)
{

	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		if (m_apNumber[nCntLevel] != NULL)
		{
			m_apNumber[nCntLevel]->Uninit();
			delete m_apNumber[nCntLevel];
			m_apNumber[nCntLevel] = NULL;
		}
	}
	Release();
}

void CLevel::Update(void)
{
	//スコア取得
	CScore *pScore;
	pScore = CGame::GetScore();
	int nScore = pScore->GetScore();
	if (nScore >= 0 && nScore <= PLAYER_EVOSCORE1 - 1)
	{
		m_nLevel = 0;
	}
	else if (nScore >= PLAYER_EVOSCORE1 && nScore <= PLAYER_EVOSCORE2 - 1)
	{
		m_nLevel = 1;
	}
	else if (nScore >= PLAYER_EVOSCORE2 && nScore <= PLAYER_EVOSCORE3 - 1)
	{
		m_nLevel = 2;
	}
	else if (nScore >= PLAYER_EVOSCORE3)
	{
		m_nLevel = 3;
	}

	m_apNumber[0]->SetNumber(m_nLevel % 10 / 1);

}

void CLevel::Draw(void)
{
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		m_apNumber[nCntLevel]->Draw();
	}
}

//スコアのセット
void CLevel::SetLevel(int nLevel)
{
	m_nLevel = nLevel;
}

void CLevel::AddLevel(int nValue)
{
	m_nLevel += nValue;
}

int CLevel::GetLevel(void)
{
	return m_nLevel;
}
