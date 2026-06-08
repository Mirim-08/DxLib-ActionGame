#include "Title.h"
#include "Config.h"

void Title::Title_Init()
{
	isStarted = FALSE;
}

void Title::Title_Update()
{
	// Enterキーでゲーム開始
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		isStarted = TRUE;
	}
}

void Title::Title_Draw()
{
	// 背景色を黒で塗りつぶし
	DrawBox(BACK_X, BACK_Y, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK, TRUE);

	// タイトル
	SetFontSize(TITLE_FONT_SIZE);
	DrawString(SCREEN_WIDTH / 2 - TITLE_OFFSET_X, SCREEN_HEIGHT / 2 - TITLE_OFFSET_Y, "GAME TITLE", YELLOW);

	// スタート案内
	SetFontSize(START_FONT_SIZE);
	DrawString(SCREEN_WIDTH / 2 - TITLE_OFFSET_X, SCREEN_HEIGHT / 2 + ENTER_OFFSET_Y, "Press ENTER to Start", WHITE);

	// 操作説明
	SetFontSize(HELP_FONT_SIZE);
	DrawString(CTRL_W, SCREEN_HEIGHT - 100, "A/D: Move Left/Right", GRAY);
	DrawString(CTRL_W, SCREEN_HEIGHT - 60, "SPACE: Jump", GRAY);
	DrawString(CTRL_W, SCREEN_HEIGHT - 20, "ESC: Exit", GRAY);

	SetFontSize(DEFAULT_SIZE); // フォントサイズをリセット
}
