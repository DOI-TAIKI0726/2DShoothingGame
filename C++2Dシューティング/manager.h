#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//各々のヘッダーで管理したほうがよい

//エフェクト
#define EFFECT_SIZE_X 20.0f
#define EFFECT_SIZE_Y 20.0f


//ロゴ
#define LOGO_POS_X 50.0f
#define LOGO_POS_Y 50.0f
#define LOGO_SIZE_X 250.0f
#define LOGO_SIZE_Y 250.0f

#define TIMER (500)


//前方宣言(ポインタだけなら前方宣言)
class CInputKeyboard;
class CRenderer;
class CSound;
class CTitle;
class CGame;
class CResult;
class CFade;
class CTutorial;
class CTutorial2;

class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_TUTORIAL2,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	} MODE;
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update(void);
	void Draw(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void);
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CSound *GetSound(void);
	static CFade *GetFade(void);

private:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CSound *m_pSound;
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static MODE m_mode; //モード
	static CFade *m_pFade;  //フェード
	static CTutorial *m_pTutorial;
	static CTutorial2 *m_pTutorial2;

};

#endif
