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

//==================================================
// グローバル変数
//==================================================
bool bgmStarted = FALSE; // BGM再生済みフラグ
int time = 0;            // フレーム制御用時間
Title* gTitle = nullptr; // タイトル画面管理クラス

//==================================================
// 関数プロトタイプ宣言
//==================================================
void Game_Init();
void Game_Update();
void Game_Draw();
void Game_End();

//==================================================
// ゲーム初期化
//==================================================
void Game_Init()
{
	// 以前のBGMが残っている場合は停止して解放
	if (bgmSound >= 0)
	{
		StopSoundMem(bgmSound);
		DeleteSoundMem(bgmSound);
		bgmSound = -1;
	}

	// BGM再生フラグをリセット
	bgmStarted = FALSE;

	// 各ゲームオブジェクト生成
	gPlayer = new Player();
	gBackground = new Background();
	gEnemy = new Enemy();
	gBlock = new Block();
	gGame = new Game();
	gGoal = new Goal();

	// オブジェクト同士の参照を設定
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

	// 各クラス初期化
	gPlayer->Player_Init();
	gEnemy->Enemy_Init();
	gBlock->Block_Init();
	gBackground->Back_Init();
	gGoal->Goal_Init();

	// ステージデータ設定
	gEnemy->Enemy_Setup();
	gBlock->Block_Setup();

	// BGMの読み込み
	bgmSound = LoadSoundMem("Resource/sound/field.mp3"); // BGMの読み込み
}

//==================================================
// ゲーム更新処理
//==================================================
void Game_Update()
{
	// ゲーム状態取得
	int gameOver = gGame ? gGame->gameOver : FALSE;
	int gameClear = gGame ? gGame->gameClear : FALSE;

	// BGMを一度だけ再生
	if (!bgmStarted && bgmSound >= 0)
	{
		PlaySoundMem(bgmSound, DX_PLAYTYPE_BACK, TRUE);
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

	// カメラ更新
	gBackground->Camera_Update();

	// 背景スクロール更新
	gBackground->Back_Loop();

	// 敵の移動更新
	gEnemy->Enemy_Update();

	// プレイヤー更新
	gPlayer->Player_Move();
	gPlayer->Player_Vec();

	// 衝突判定
	gBlock->Block_Vec();
	gEnemy->Enemy_Vec();
	gGoal->Goal_Vec();
}

//==================================================
// 描画処理
//==================================================
void Game_Draw()
{
	// 描画順
	// 背景 → ブロック → ゴール → プレイヤー → 敵 → UI

	gBackground->Back_Draw(); // 背景
	gBlock->Block_Draw();     // ブロック
	gGoal->Goal_Draw();       // ゴール
	gPlayer->Player_Draw();   // プレイヤー
	gEnemy->Enemy_Draw();     // 敵

	gGame->UI_Draw();      // スコア
	gGame->Result_Draw();     // ゲームオーバー・クリア表示
}

//==================================================
// 終了処理
//==================================================
void Game_End()
{
	// プレイヤー解放
	if (gPlayer)
	{
		gPlayer->Player_End();
		delete gPlayer;
		gPlayer = nullptr;
	}

	// 敵解放
	if (gEnemy)
	{
		gEnemy->Enemy_End();
		delete gEnemy;
		gEnemy = nullptr;
	}

	// 背景解放
	if (gBackground)
	{
		gBackground->Back_End();
		delete gBackground;
		gBackground = nullptr;
	}

	// ブロック解放
	if (gBlock)
	{
		gBlock->Block_End();
		delete gBlock;
		gBlock = nullptr;
	}

	// ゴール解放
	if (gGoal)
	{
		gGoal->Goal_End();
		delete gGoal;
		gGoal = nullptr;
	}

	// ゲーム管理クラス解放
	if (gGame)
	{
		delete gGame;
		gGame = nullptr;
	}

	// BGM解放
	if (bgmSound >= 0)
	{
		DeleteSoundMem(bgmSound);
	}

	// タイトル画面解放
	if (gTitle)
	{
		delete gTitle;
		gTitle = nullptr;
	}
}

//==================================================
// エントリーポイント
//==================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウモード設定
	ChangeWindowMode(TRUE);

	// 画面設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

	// DxLib初期化
	if (DxLib_Init() == -1)
	{
		return -1; // エラーが起きたら直ちに終了 
	}

	// 描画先を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	// タイトル画面生成
	gTitle = new Title();
	gTitle->Title_Init();

	bool gameStarted = FALSE;

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// タイトル画面表示中
		if (!gameStarted)
		{
			gTitle->Title_Update();

			ClearDrawScreen();
			gTitle->Title_Draw();
			ScreenFlip();

			// Enterキーでゲーム開始
			if (gTitle->isStarted)
			{
				gameStarted = TRUE;
				Game_Init();
				time = GetNowCount();
			}
		}
		// ゲームプレイ中
		else
		{
			// 更新処理 
			Game_Update();

			// 画面クリア
			ClearDrawScreen();

			// 描画処理
			Game_Draw();

			// スコア更新
			gGame->Score_Update();

			// 裏画面を表画面へ反映
			ScreenFlip();

			// 60FPS固定
			while (GetNowCount() - time < FRAME_TIME_MS)
			{
			}
			time = GetNowCount();
		}
	}

	// ゲーム終了処理
	Game_End();

	// DxLib終了処理
	DxLib_End();


	return 0;
}
