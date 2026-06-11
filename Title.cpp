#include "Title.h"
#include "Config.h"

void Title::Title_Init()
{
	isStarted = FALSE; // タイトル画面表示中はゲーム未開始状態にする
}

void Title::Title_Update()
{
	// Enterキーが押されたらゲーム開始
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		isStarted = TRUE;
	}
}

void Title::Title_Draw()
{
	// 背景を黒色で塗りつぶす
	DrawBox(BACK_X, BACK_Y, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK, TRUE);

	// ゲームタイトルを表示
	SetFontSize(TITLE_FONT_SIZE);
	DrawString(
		SCREEN_WIDTH / 2 - TITLE_OFFSET_X, 
		SCREEN_HEIGHT / 2 - TITLE_OFFSET_Y,
		"2D ACTION",
		YELLOW
	);

	// ゲーム開始案内を表示
	SetFontSize(START_FONT_SIZE);
	DrawString(
		SCREEN_WIDTH / 2 - TITLE_OFFSET_X, 
		SCREEN_HEIGHT / 2 + ENTER_OFFSET_Y, 
		"Press ENTER to Start",
		WHITE
	);

	// 操作説明を表示
	SetFontSize(HELP_FONT_SIZE);

	// 左右移動
	DrawString(
		CTRL_W, 
		SCREEN_HEIGHT - 100, 
		"A/D: Move Left/Right", 
		GRAY
	);

	// ジャンプ
	DrawString(
		CTRL_W, 
		SCREEN_HEIGHT - 60,
		"SPACE: Jump",
		GRAY
	);

	// ゲーム終了
	DrawString(
		CTRL_W, 
		SCREEN_HEIGHT - 20,
		"ESC: Exit",
		GRAY
	);

	// 他の画面へ影響しないようフォントサイズを初期値に戻す
	SetFontSize(DEFAULT_SIZE);
}
