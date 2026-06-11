#include "Game.h"
#include "Globals.h"
#include "Config.h"

void Game::Score_Init()
{
	score = 0; // スコア初期化
	startTime = GetNowCount();// ゲーム開始時刻を取得
	elapsedTime = 0;// 経過時間を初期化
	oldTimeScore = 0; // 前フレームの時間スコアを初期化
}

void Game::Score_Update()
{
	// ゲームオーバーまたはゲームクリア時はスコア加算を停止
	if (gameOver || gameClear)return;

	// ゲーム開始からの経過時間を取得
	elapsedTime = GetNowCount() - startTime;

	// 経過時間に応じたスコアを計算
	// （SCORE_TIME_DIVISORごとに1点加算）
	int newTimeScore = elapsedTime / SCORE_TIME_DIVISOR;

	// 前回との差分だけスコアに加算
	score += newTimeScore - oldTimeScore;

	// 現在の時間スコアを保存
	oldTimeScore = newTimeScore;
}

void Game::Result_Draw()const
{
	// ゲームオーバー画面を表示
	if (gameOver)
	{
		DrawString(
			SCREEN_WIDTH / 2 - GAMEOVER_TEXT_OFFSET_X, 
			SCREEN_HEIGHT / 2 - GAMEOVER_TEXT_OFFSET_Y, 
			"GAME OVER",
			RED
		);
		DrawString(
			SCREEN_WIDTH / 2 - GAMEINFO_TEXT_OFFSET_X, 
			SCREEN_HEIGHT / 2 + GAMEINFO_TEXT_OFFSET_Y, 
			"R: Restart ESC: Exit",
			GRAY
		);
	}

	// ゲームクリア画面を表示
	if(gameClear)
	{
		DrawString(
			SCREEN_WIDTH / 2 - GAMEOVER_TEXT_OFFSET_X, 
			SCREEN_HEIGHT / 2 - GAMEOVER_TEXT_OFFSET_Y, 
			"GAME CLEAR!", 
			YELLOW
		);
		DrawString(
			SCREEN_WIDTH / 2 - GAMEINFO_TEXT_OFFSET_X, 
			SCREEN_HEIGHT / 2 + GAMEINFO_TEXT_OFFSET_Y,
			"R: Restart ESC: Exit", 
			GRAY
		);
	}

	// フォントサイズを初期値へ戻す
	SetFontSize(DEFAULT_SIZE);
}

void Game::Score_Draw()
{
	// スコアを表示
	DrawFormatString(
		SCORE_X,
		SCORE_Y,
		WHITE, 
		"SCORE %d ",
		score
	); 

	// フォントサイズを初期値へ戻す
	SetFontSize(DEFAULT_SIZE);
}