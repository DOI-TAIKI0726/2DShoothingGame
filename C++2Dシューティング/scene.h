#ifndef _SCENE_H_
#define _SCENE_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "main.h"

#define MAX_SCENE 3090
#define PRIORITY_MAX 10

//オブジェクトクラス
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		//プレイヤー
		OBJTYPE_ENEMY,		//敵
		OBJTYPE_ENEMYBULLET,  //敵の弾
		OBJTYPE_BOSSENEMY,  //ボスエネミー
		OBJTYPE_BULLET,		//弾
		OBJTYPE_EXPLOSION, //爆発
		OBJTYPE_BG,  //背景
		OBJTYPE_LIFE,  //体力
		OBJTYPE_SCORE,  //スコア
		OBJTYPE_EFFECT,  //エフェクト
		OBJTYPE_LOGO,  //ロゴ
		OBJTYPE_LEVEL,  //レベル表記
		OBJTYPE_COUNTTIMER,
		OBJTYPE_MAX			
	}OBJTYPE;

	CScene(int nPriority = 3);
	virtual ~CScene();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void DrawAll(void);
	static void UpdateAll(void);

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nPriority, int nIndex);
	int GetEnemyLife(void);
	void SetEnemyLife(int nLife);
	int GetPlayerLife(void);
	void SetPlayerLife(int nLife);


protected:
	void Release(void);
private:
	//↓左：優先順位最大数、右：オブジェクト最大数
	static CScene *m_apScene[PRIORITY_MAX][MAX_SCENE];
	static int m_nNumAll;
	int m_nID;
	int m_nEnemyLife;
	int m_nPlayerLife;
	int m_nPriority;  //優先順位の番号
	OBJTYPE m_objType; //オブジェクトの種類
};

#endif
