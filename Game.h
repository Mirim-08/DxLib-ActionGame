#pragma once
#include "DxLib.h"

class Background;

// ゲーム状態とスコア管理を行うクラス
class Game
{
public:
	Background* background = nullptr; // 背景クラスへの参照

	// ゲーム状態
	bool gameOver = FALSE;              // ゲームオーバーフラグ
	bool gameClear = FALSE;             // ゲームクリアフラグ
	bool isGameOverSoundPlayed = FALSE; // ゲームオーバー音再生フラグ

	// スコア関連
	int Score = 0; // 現在のスコア

	// 時間計測関連
	int startTime = 0;    // ゲーム開始時刻
	int elapsedTime = 0;  // 経過時間
	int oldTimeScore = 0; // 前フレームの時間スコア
	int timeLimit = 0;       // 制限時間
	int remainingTime = 0;   // 残り時間

	void Score_Init();       // スコア・時間の初期化
	void Score_Update();     // スコア更新
	void Result_Draw()const; // GAME OVER / GAME CLEAR表示
	void UI_Draw();       // UI表示
};