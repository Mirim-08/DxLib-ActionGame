#include "Game.h"
#include "Globals.h"
#include "Config.h"

void Game::Score_Init()
{
	score = 0; // スコア初期化
	startTime = GetNowCount();
	elapsedTime = 0;
	oldTimeScore = 0;
}

void Game::Score_Update()
{
	if (gameOver || gameClear)return;

	elapsedTime = GetNowCount() - startTime;

	int newTimeScore = elapsedTime / SCORE_TIME_DIVISOR;// 0.01秒ごとに+1

	score += newTimeScore - oldTimeScore;

	oldTimeScore = newTimeScore;
}

void Game::Result_Draw()const
{
	// ゲームオーバー表示 
	if (gameOver)
	{
		DrawString(SCREEN_WIDTH / 2 - GAMEOVER_TEXT_OFFSET_X, SCREEN_HEIGHT / 2 - GAMEOVER_TEXT_OFFSET_Y, "GAME OVER", RED);
		DrawString(SCREEN_WIDTH / 2 - GAMEINFO_TEXT_OFFSET_X, SCREEN_HEIGHT / 2 + GAMEINFO_TEXT_OFFSET_Y, "R: Restart ESC: Exit", GRAY);
	}
	// ゲームクリア表示 
	if(gameClear)
	{
		DrawString(SCREEN_WIDTH / 2 - GAMEOVER_TEXT_OFFSET_X, SCREEN_HEIGHT / 2 - GAMEOVER_TEXT_OFFSET_Y, "GAME CLEAR!", YELLOW);
		DrawString(SCREEN_WIDTH / 2 - GAMEINFO_TEXT_OFFSET_X, SCREEN_HEIGHT / 2 + GAMEINFO_TEXT_OFFSET_Y, "R: Restart ESC: Exit", GRAY);
	}
	SetFontSize(DEFAULT_SIZE);
}

void Game::Score_Draw()
{
	DrawFormatString(SCORE_X, SCORE_Y, WHITE, "SCORE %d ", score); // スコア表示
	SetFontSize(DEFAULT_SIZE);
}
