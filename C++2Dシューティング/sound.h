//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
// �T�E���h���� [sound.h]
// Author : �y���@��P
//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include "manager.h"

class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_BGM002,			// BGM2
		SOUND_LABEL_BGM003,			// BGM3
		SOUND_LABEL_BGM004,			// BGM4
		SOUND_LABEL_SHOT000,		// �V���b�g��
		SOUND_LABEL_EXPLOSION,      //������
		SOUND_LABEL_BGM_MAOUDMASHI,  //������001
		SOUND_LABEL_BGM_MAOUDMASHI02,  //������002
		SOUND_LABEL_BGM_MAOUDMASHI03,  //������002


		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	//�p�����[�^�\����
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	static PARAM	m_aParam[SOUND_LABEL_MAX];
};

#endif