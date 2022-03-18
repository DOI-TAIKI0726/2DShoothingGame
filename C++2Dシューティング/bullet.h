#ifndef _BULLET_H_
#define _BULLET_H_
#define _CRT_SECURE_NO_WARNINGS
#include "manager.h"

//’e
#define BULLET_SIZE_X 10.0f
#define BULLET_SIZE_Y 15.0f
#define BULLET_MOVE_Y 15.0f
#define BULLET_MOVE_X 15.0f



class CBullet : public CScene2D
{
public:
	typedef enum
	{
		TYPE_NORMAL,
		TYPE_STRAIGHT,
		TYPE_LEFT,
		TYPE_RIGHT,
		TYPE_LEFTUP,
		TYPE_RIGHTUP,
		TYPE_BEAM,
		TYPE_MAX
	} TYPE;
	CBullet(int nPriority = 3);
	~CBullet();
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 exsize, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 exsize, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
private:
	D3DXVECTOR3 m_move;  //ˆÚ“®—Ê
	static LPDIRECT3DTEXTURE9		m_apTexture[TYPE_MAX];
	float m_nLife; //Žõ–½
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_exsize;
	D3DCOLORVALUE m_col;
	D3DXVECTOR3 m_pos;  //ƒTƒCƒY
	int m_nActTime = 0;
	TYPE m_Type;
};

#endif
