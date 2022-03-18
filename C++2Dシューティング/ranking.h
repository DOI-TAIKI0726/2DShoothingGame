#ifndef _RANKING_H_
#define _RANKING_H_
#include "main.h"
#include "scene.h"

#define MAX_RANKING (6)

class CScore;

class CRanking :public CScene
{
public:
	CRanking(int nPriority = 6);
	~CRanking();
	static CRanking *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_size;
	static CScore *m_apScore[MAX_RANKING];
	int m_nRanking;
	int m_nScore[MAX_RANKING];
	D3DXVECTOR3 m_pos;
	//D3DCOLORVALUE m_color;

};
#endif

