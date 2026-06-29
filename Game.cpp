#include "Game.h"
#include "Globals.h"
#include "Config.h"
#include <cmath>

void Game::Score_Init()
{
	Score = 0;                 // スコア初期化
	startTime = GetNowCount(); // ゲーム開始時刻を取得
	elapsedTime = 0;           // 経過時間を初期化
	oldTimeScore = 0;          // 前フレームの時間スコアを初期化

	timeLimit = 60;            // 制限時間60秒
	remainingTime = timeLimit; // 残り時間を初期化
}

void Game::Score_Update()
{
	// ゲームオーバーまたはゲームクリア時は更新停止
	if (gameOver || gameClear)return;
	// ゲーム開始からの経過時間を取得(ミリ秒)
	elapsedTime = GetNowCount() - startTime;
	// 残り時間を計算(秒)
	remainingTime = timeLimit - (elapsedTime / 1000);

	// 制限時間終了
	if (remainingTime <= 0)
	{
		remainingTime = 0;
		gameOver = TRUE;

		if (!isGameOverSoundPlayed)
		{
			// BGM停止
			StopSoundMem(bgmSound);
			// ゲームオーバー音再生
			PlaySoundMem(overSound, DX_PLAYTYPE_BACK);
			// ゲームオーバー音再生フラグ
			isGameOverSoundPlayed = TRUE;
		}

		return;
	}
	// 経過時間に応じたスコアを計算（SCORE_TIME_DIVISORごとに1点加算）
	int newTimeScore = elapsedTime / SCORE_TIME_DIVISOR;
	// 前回との差分だけスコアに加算
	Score += newTimeScore - oldTimeScore;
	// 現在の時間スコアを保存
	oldTimeScore = newTimeScore;
}

void Game::Result_Draw()const
{ // 0～255を往復するアルファ値
	int alpha = (int)((sin(GetNowCount() * RESULT_FADE_SPEED) + 1.0) * (ALPHA_MAX / 2.0));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	if (gameOver)
	{
		DrawString(
			SCREEN_WIDTH / 2 - GAMEOVER_TEXT_OFFSET_X,
			SCREEN_HEIGHT / 2 - GAME_TEXT_OFFSET_Y,
			"GAME OVER",
			RED
		);
	}
	if (gameClear)
	{
		DrawString(
			SCREEN_WIDTH / 2 - GAMECLEAR_TEXT_OFFSET_X,
			SCREEN_HEIGHT / 2 - GAME_TEXT_OFFSET_Y,
			"GAME CLEAR!",
			YELLOW
		);
	}
	// 他の描画に影響しないよう戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (gameClear || gameOver)
	{
		DrawString(
			SCREEN_WIDTH / 2 - GAMEINFO_TEXT_OFFSET_X,
			SCREEN_HEIGHT / 2 + GAMEINFO_TEXT_OFFSET_Y,
			"R: Restart ESC: Exit",
			GRAY
		);
	}
}

void Game::UI_Draw()
{
	// スコアを表示
	DrawFormatString(
		SCORE_X,
		SCORE_Y,
		WHITE,
		"SCORE %06d",
		Score
	);

	// 制限時間表示
	DrawFormatString(
		SCORE_X,
		TIME_Y,
		WHITE,
		"TIME %02d",
		remainingTime
	);

	// フォントサイズを初期値へ戻す
	SetFontSize(DEFAULT_SIZE);
}
