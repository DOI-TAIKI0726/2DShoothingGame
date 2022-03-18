#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "scene.h"


#define MAX_SCORE (8)
//スコア
#define SCORE_POS_X 880.0f
#define SCORE_POS_Y 50.0f
#define SCORE_SIZE_X 50.0f
#define SCORE_SIZE_Y 50.0f

//前方宣言
class CNumber;

class CScore :public CScene
{
public:
	CScore(int nPriority=6);
	~CScore();
	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore(void);

private:
	D3DXVECTOR3 m_size;
	CNumber *m_apNumber[MAX_SCORE];

	int m_nScore;
};
#endif

