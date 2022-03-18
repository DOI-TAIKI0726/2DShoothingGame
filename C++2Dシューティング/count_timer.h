#ifndef _COUNT_TIMER_H_
#define _COUNT_TIMER_H_
#include "main.h"
#include "scene.h"


#define MAX_TIMER_DIGHT (3)
#define COUNT_TIMER_POS_X 590.0f
#define COUNT_TIMER_POS_Y 50.0f
#define COUNT_TIMER_SIZE_X 50.0f
#define COUNT_TIMER_SIZE_Y 50.0f

//ëOï˚êÈåæ
class CNumber;

class CCountTimer :public CScene
{
public:
	CCountTimer(int nPriority = 6);
	~CCountTimer();
	static CCountTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCountTimer(int nLevel);
	void AddCountTimer(int nValue);
	int GetCountTimer(void);

private:
	D3DXVECTOR3 m_size;
	CNumber *m_apNumber[MAX_TIMER_DIGHT];
	int m_nCountTimer;
	bool m_bStop;
	int m_ndwCurrentTime = 0;
	int m_ndwLastTime = 0;
};
#endif



