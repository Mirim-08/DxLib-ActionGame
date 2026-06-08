#pragma once
#include "DxLib.h"

class Background;

class Game
{
public:
	Background* background = nullptr;

	bool gameOver = FALSE; // ゲームオーバーフラグ
	bool gameClear = FALSE; // ゲームクリアフラグ
	int score = 0; // スコア

	int startTime = 0; // ゲーム開始時刻
	int elapsedTime = 0;
	int oldTimeScore = 0;

	void Score_Init();// スコア初期化
	void Update_Score();
	void Draw_Result()const;// ゲームオーバーとゲームクリアの表示
	void Draw_Score();// スコア表示
};