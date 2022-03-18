#ifndef _SCENE_H_
#define _SCENE_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "main.h"

#define MAX_SCENE 3090
#define PRIORITY_MAX 10

//�I�u�W�F�N�g�N���X
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		//�v���C���[
		OBJTYPE_ENEMY,		//�G
		OBJTYPE_ENEMYBULLET,  //�G�̒e
		OBJTYPE_BOSSENEMY,  //�{�X�G�l�~�[
		OBJTYPE_BULLET,		//�e
		OBJTYPE_EXPLOSION, //����
		OBJTYPE_BG,  //�w�i
		OBJTYPE_LIFE,  //�̗�
		OBJTYPE_SCORE,  //�X�R�A
		OBJTYPE_EFFECT,  //�G�t�F�N�g
		OBJTYPE_LOGO,  //���S
		OBJTYPE_LEVEL,  //���x���\�L
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
	//�����F�D�揇�ʍő吔�A�E�F�I�u�W�F�N�g�ő吔
	static CScene *m_apScene[PRIORITY_MAX][MAX_SCENE];
	static int m_nNumAll;
	int m_nID;
	int m_nEnemyLife;
	int m_nPlayerLife;
	int m_nPriority;  //�D�揇�ʂ̔ԍ�
	OBJTYPE m_objType; //�I�u�W�F�N�g�̎��
};

#endif
