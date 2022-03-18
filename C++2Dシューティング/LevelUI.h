#ifndef _LEVELUI_H_
#define _LEVELUI_H_
#include "main.h"
#include "scene.h"


#define MAX_LEVEL (1)
#define LEVEL_POS_X 80.0f
#define LEVEL_POS_Y 50.0f
#define LEVEL_SIZE_X 50.0f
#define LEVEL_SIZE_Y 50.0f

//ëOï˚êÈåæ
class CNumber;

class CLevel :public CScene
{
public:
	CLevel(int nPriority = 6);
	~CLevel();
	static CLevel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLevel(int nLevel);
	void AddLevel(int nValue);
	int GetLevel(void);

private:
	D3DXVECTOR3 m_size;
	CNumber *m_apNumber[MAX_LEVEL];

	int m_nLevel;
};
#endif


