#include "Player.h"
#include "Background.h"
#include "Globals.h"
#include "Game.h"
#include "Config.h"

void Player::Player_Init()
{
	playerGraph = LoadGraph("data/player.png"); //　プレイヤー画像の読み込み
	walksound = LoadSoundMem("sound/Walk.mp3"); // 歩行音の読み込み
	jumpsound = LoadSoundMem("sound/jump.mp3"); // ジャンプ音の読み込み

	GetGraphSize(
		playerGraph,
		&playerW,
		&playerH
	);  // プレイヤー画像のサイズを取得
}

void Player::Player_Move()
{
	moveFlag = FALSE; // 移動状態をリセット
	prevX = playerX; // 前フレームのX座標を保存
	prevY = playerY; // 前フレームのY座標を保存

	// Shiftキーでダッシュ速度に切り替える
	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{
		Speed = PLAYER_SPEED_RUN;
	}
	else
	{ 
		Speed = PLAYER_SPEED_NORMAL;
	}

	// Dキーで右移動
	if (CheckHitKey(KEY_INPUT_D))
	{
		playerX += Speed; Reverse = FALSE;
		moveFlag = TRUE;
	}
	// Aキーで左移動
	if (CheckHitKey(KEY_INPUT_A))
	{
		playerX -= Speed; Reverse = TRUE;
		moveFlag = TRUE;
	}

	// 移動中のみ歩行音を再生
	if (moveFlag == TRUE)
	{
		if (CheckSoundMem(walksound) == 0)
		{
			PlaySoundMem(walksound, DX_PLAYTYPE_BACK, TRUE); // 歩行音再生
		}
	}
}

void Player::Player_Vec()
{
	// コヨーテタイムの残りフレーム数を減らす
	if (coyoteCounter > 0)
	{
		coyoteCounter--;
	}

	bool nowSpace = CheckHitKey(KEY_INPUT_SPACE); // 現在のスペースキー状態

	// スペースキーを押した瞬間のみジャンプ判定
	if (nowSpace == TRUE && prevSpace == FALSE) 
	{
		// 接地中またはコヨーテタイム中ならジャンプ可能
		if (isGround == TRUE || coyoteCounter > 0)
		{ 
			jumpPower = PLAYER_JUMP_POWER;// 初速を設定
			jumpFlag = TRUE;             // ジャンプ開始フラグ
			coyoteCounter = 0;          // コヨーテタイムを消費
		} 
	}

	prevSpace = nowSpace; // 前フレームのスペースキーの状態を保存

	isGround = FALSE;// 接地状態をリセット

	// ジャンプ開始時に効果音を再生
	if (jumpFlag == TRUE) 
	{
		PlaySoundMem(jumpsound, DX_PLAYTYPE_BACK, TRUE); // ジャンプ音を鳴らす
		jumpFlag = FALSE; 
	}

	// ジャンプ・落下処理
	playerY -= jumpPower; // 現在のジャンプ力分だけY座標を上方向へ移動する
	jumpPower -= GRAVITY; // 重力によって速度を変化させる

	// 地面との当たり判定
	if (playerY >= GROUND_Y)
	{
		playerY = GROUND_Y;          // 地面位置に補正
		jumpPower = 0;               // ジャンプ力をリセット
		isGround = TRUE;             // 地面にいる状態
		coyoteCounter = COYOTE_TIME; // コヨーテタイム開始
	}
	
}

void Player::Player_Draw()
{
	// カメラのX座標を取得
	int cameraX = gBackground ? gBackground->cameraX : 0;
	// プレイヤーを向きに応じて反転描画
	DrawReverseGraph(
		playerX - cameraX,
		playerY, 
		playerGraph,
		TRUE, 
		Reverse
	);
}

void Player::Player_End()
{
	DeleteGraph(playerGraph); // プレイヤー画像の解放
	DeleteSoundMem(walksound); // 歩行音の解放
	DeleteSoundMem(jumpsound); // ジャンプ音の解放
}