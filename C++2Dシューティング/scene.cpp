#include "scene.h"
#include "renderer.h"

//ê√ìIÉÅÉìÉoïœêî
CScene *CScene::m_apScene[PRIORITY_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			//é©ï™ÇÃî‘çÜÇê›íË
			m_nID = nCntScene;
			m_nPriority = nPriority;
			m_nNumAll++;
			break;
		}
	}
	m_objType = OBJTYPE_NONE;
}

CScene::~CScene()
{

}

void CScene::UpdateAll()
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScore = 0; nCntScore < MAX_SCENE; nCntScore++)
		{
			if (m_apScene[nCntPriority][nCntScore] != NULL)
			{
				m_apScene[nCntPriority][nCntScore]->Update();
			}
		}
	}
}




void CScene::ReleaseAll()
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				if (nCntPriority != 7)
				{
					m_apScene[nCntPriority][nCntScene]->Uninit();
					delete m_apScene[nCntPriority][nCntScene];
					m_apScene[nCntPriority][nCntScene] = NULL;
				}
			}
		}
	}
}

void CScene::DrawAll()
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScore = 0; nCntScore < MAX_SCENE; nCntScore++)
		{
			if (m_apScene[nCntPriority][nCntScore] != NULL)
			{
				m_apScene[nCntPriority][nCntScore]->Draw();
			}
		}
	}
}

void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

CScene *CScene::GetScene(int nPriority,int nIndex)
{
	return m_apScene[nPriority][nIndex];
}

int CScene::GetEnemyLife(void)
{
	return m_nEnemyLife;
}

void CScene::SetEnemyLife(int nLife)
{
	m_nEnemyLife = nLife;
}

int CScene::GetPlayerLife(void)
{
	return m_nPlayerLife;
}

void CScene::SetPlayerLife(int nLife)
{
	m_nPlayerLife = nLife;
}