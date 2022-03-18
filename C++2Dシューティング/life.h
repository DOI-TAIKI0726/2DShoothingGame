#ifndef _LIFE_H_
#define _LIFE_H_
#include "main.h"
#include "scene.h"

//ÉâÉCÉt
#define LIFE_POS_X 250.0f
#define LIFE_POS_Y 50.0f
#define LIFE_SIZE_X 50.0f
#define LIFE_SIZE_Y 50.0f


#define MAX_LIFE (4)

//ëOï˚êÈåæ
class CLifePolygon;

class CLife :public CScene
{
public:
	CLife(int nPriority = 5);
	~CLife();
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int nScore);
	void AddLife(int nValue);
	int GetLife(void);

private:
	D3DXVECTOR3 m_size;

	CLifePolygon *m_apLifePolygon[MAX_LIFE];

	int m_nLife;
};
#endif
