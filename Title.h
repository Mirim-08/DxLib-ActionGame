#pragma once
#include "DxLib.h"

// タイトル画面の表示と入力処理を管理するクラス
class Title
{
public:
	// ゲーム開始状態
	bool isStarted = FALSE; // Enterキーが押されたらTRUEになる
	

	void Title_Init();      // タイトル画面の初期化
	void Title_Update();    // タイトル画面の更新
	void Title_Draw();      // タイトル画面の描画
};
