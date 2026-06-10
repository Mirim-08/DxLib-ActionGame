#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"
#include "Background.h"
#include "Game.h"
#include "Globals.h"
#include "Goal.h"
#include "Config.h"
#include "Title.h"

// BGMハンドル 
int bgmsound = -1;
bool bgmStarted = FALSE;
// 現在のカウントを取得する
int time = 0;
Title* gTitle = nullptr;

// プロトタイプ宣言
void Game_Init();
void Game_Update();
void Game_Draw();
void Game_End();

void Game_Init()
{ 
	if (bgmsound >= 0)
	{
		StopSoundMem(bgmsound);
		DeleteSoundMem(bgmsound);
		bgmsound = -1;
	}

	// フラグをリセット
	bgmStarted = FALSE; 
	gPlayer = new Player();
	gBackground = new Background();
	gEnemy = new Enemy();
	gBlock = new Block();
	gGame = new Game();
	gGoal = new Goal();

	//ポインタの相互参照を設定
	gPlayer->background = gBackground;
	gBackground->player = gPlayer;
	gEnemy->player = gPlayer;
	gEnemy->background = gBackground;
	gEnemy->game = gGame;
	gBlock->player = gPlayer;
	gBlock->background = gBackground;
	gGame->background = gBackground;
	gGoal->player = gPlayer; 
	gGoal->background = gBackground; 
	gGoal->game = gGame;

	// スコアの初期化
	gGame->Score_Init();
	// プレイヤーの初期化
	gPlayer->Player_Init(); 
	// 敵の初期化
	gEnemy->Enemy_Init();
	// ブロックの初期化
	gBlock->Block_Init();
	// 背景の初期化
	gBackground->Back_Init(); 
	// ゴールの初期化
	gGoal->Goal_Init();
	// 敵の配置
	gEnemy->Enemy_Setup();
	// ブロックの配置
	gBlock->Block_Setup();
	// BGMの読み込み
	bgmsound = LoadSoundMem("sound/field.mp3"); // BGMの読み込み
}

void Game_Update()
{
	int gameOver = gGame ? gGame->gameOver : FALSE; 
	int gameClear = gGame ? gGame->gameClear : FALSE;

	if (!bgmStarted && bgmsound >= 0)
	{
		PlaySoundMem(bgmsound, DX_PLAYTYPE_BACK, TRUE);
		bgmStarted = TRUE;
	}

	// ゲームオーバー、ゲームクリア時はRキーでリスタート 
	if (gameOver || gameClear)
	{
		if (CheckHitKey(KEY_INPUT_R))
		{
			Game_End();
			Game_Init();
		}
		return;
	}

	// カメラ追従（プレイヤーが画面左付近に来るようにする） 
	gBackground->Camera_Update();
	// 背景の描画位置（ループ） 
	gBackground->Back_Loop();
	// エネミー更新
	gEnemy->Enemy_Update();
	// プレイヤーの動き
	gPlayer->Player_Move(); 
	// プレイヤーの当たり判定
	gPlayer->Player_Vec(); 
	// ブロックの当たり判定
	gBlock->Block_Vec(); 
	// 敵の当たり判定
	gEnemy->Enemy_Vec();
	// ゴールの当たり判定
	gGoal->Goal_Vec();
}

void Game_Draw()
{
	// 背景
	gBackground->Back_Draw();
	// ブロック
	gBlock->Block_Draw();
	// ゴール
	gGoal->Goal_Draw();
	// プレイヤー
	gPlayer->Player_Draw();
	// 敵
	gEnemy->Enemy_Draw();
	// スコア
	gGame->Score_Draw();
	// ゲームクリア、ゲームオーバー
	gGame->Result_Draw();
}

void Game_End()
  { // 読み込んだハンドルを削除
	if (gPlayer)
	{
		gPlayer->Player_End();
		delete gPlayer;
		gPlayer = nullptr;
	}

	if (gEnemy)
	{
		gEnemy->Enemy_End();
		delete gEnemy;
		gEnemy = nullptr;
	}

	if (gBackground)
	{
		gBackground->Back_End();
		delete gBackground;
		gBackground = nullptr;
	}

	if (gBlock)
	{
		gBlock->Block_End();
		delete gBlock;
		gBlock = nullptr;
	}

	if (gGoal)
	{
		gGoal->Goal_End();
		delete gGoal;
		gGoal = nullptr;
	}

	if (gGame)
	{
		delete gGame;
		gGame = nullptr;
	}

	if (bgmsound >= 0)
	{
		DeleteSoundMem(bgmsound);
	}

	if (gTitle)
	{
		delete gTitle;
		gTitle = nullptr;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動 
	ChangeWindowMode(true);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);
	// DXライブラリ初期化処理 
	if (DxLib_Init() == -1)
	{
		return -1; // エラーが起きたら直ちに終了 
	}
	// 描画先画面を裏画面にセット 
	SetDrawScreen(DX_SCREEN_BACK);
	// タイトル画面の作成
	gTitle = new Title();
	gTitle->Title_Init();
	bool gameStarted = FALSE;
	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (!gameStarted)
		{
			// タイトル画面
			gTitle->Title_Update();
			ClearDrawScreen();
			gTitle->Title_Draw();
			ScreenFlip();

			if (gTitle->isStarted)
			{
				gameStarted = TRUE;
				Game_Init(); // ゲーム初期化
				time = GetNowCount();
			}
		}
		else
		{
			// 更新処理 
			Game_Update();
			// 画面を初期化する 
			ClearDrawScreen();
			// 描画処理
			Game_Draw();
			//0.1秒ごとにスコアを1増やす
			gGame->Update_Score();
			// 裏画面の内容を表画面に反映させる 
			ScreenFlip();
			// １７ミリ秒(約秒間６０フレームだった時の１フレームあたりの経過時間)
			while (GetNowCount() - time < FRAME_TIME_MS)
			{
			}
			time = GetNowCount();
		}
	}
	Game_End(); // 終了処理
	// DXライブラリ使用の終了処理 
	DxLib_End();
	// ソフトの終了 
	return 0;
}
