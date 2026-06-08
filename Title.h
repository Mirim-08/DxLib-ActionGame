#pragma once
#include "DxLib.h"

class Title
{
public:
	bool isStarted = FALSE; // ゲーム開始フラグ
	

	void Title_Init();      // タイトル画面初期化
	void Title_Update();    // タイトル画面更新
	void Title_Draw();      // タイトル画面描画
};

