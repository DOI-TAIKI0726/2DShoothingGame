//=============================================================================
//
// メイン処理 [main.h]
// Author : 土居大輝
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#define DIRECTINPUT_VERSION (0x0800)//ビルド時の警告対処用マクロ
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "d3dx9.h"
#include "dinput.h"
#include "xaudio2.h"
#include <stdio.h>




//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")      //描画に必要
#pragma comment(lib,"d3dx9.lib")     //[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")   //DirectXコンポーネント使用に必要
#pragma comment(lib,"dinput8.lib")  //入力処理に必要
#pragma comment(lib,"winmm.lib")
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define SCREEN_CENTER_X (640)
#define SCREEN_CENTER_Y (360)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
//構造体の定義

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int GetFPS(void);

#endif


