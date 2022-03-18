//Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{
// ÉTÉEÉìÉhèàóù [sound.h]
// Author : ìyãèÅ@ëÂãP
//Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include "manager.h"

class CSound
{
public:
	CSound();
	~CSound();

	// ÉTÉEÉìÉhÉtÉ@ÉCÉã
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_BGM002,			// BGM2
		SOUND_LABEL_BGM003,			// BGM3
		SOUND_LABEL_BGM004,			// BGM4
		SOUND_LABEL_SHOT000,		// ÉVÉáÉbÉgâπ
		SOUND_LABEL_EXPLOSION,      //îöî≠âπ
		SOUND_LABEL_BGM_MAOUDMASHI,  //ñÇâ§ç∞001
		SOUND_LABEL_BGM_MAOUDMASHI02,  //ñÇâ§ç∞002
		SOUND_LABEL_BGM_MAOUDMASHI03,  //ñÇâ§ç∞002


		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	//ÉpÉâÉÅÅ[É^ç\ë¢ëÃ
	typedef struct
	{
		char *filename;		// ÉtÉ@ÉCÉãñº
		int nCntLoop;		// ÉãÅ[ÉvÉJÉEÉìÉg
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2ÉIÉuÉWÉFÉNÉgÇ÷ÇÃÉCÉìÉ^Å[ÉtÉFÉCÉX
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// É}ÉXÉ^Å[É{ÉCÉX
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// É\Å[ÉXÉ{ÉCÉX
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// ÉIÅ[ÉfÉBÉIÉfÅ[É^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// ÉIÅ[ÉfÉBÉIÉfÅ[É^ÉTÉCÉY

	static PARAM	m_aParam[SOUND_LABEL_MAX];
};

#endif