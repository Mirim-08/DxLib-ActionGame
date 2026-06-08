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

	GetGraphSize(playerGraph, &playerW, &playerH);
}

void Player::Player_Move()
{
	moveFlag = FALSE; //動いているかどうかのフラグをリセット
	prevX = playerX; // 前フレームのX座標を保存
	prevY = playerY; // 前フレームのY座標を保存

	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{ // 押したら早くなる 
		Speed = PLAYER_SPEED_RUN;
	}
	else
	{ // 押されてなかったら遅くなる 
		Speed = PLAYER_SPEED_NORMAL;
	}

	// 右を押していたら右に進む 
	if (CheckHitKey(KEY_INPUT_D))
	{
		playerX += Speed; Reverse = FALSE;
		moveFlag = TRUE;
	}
	// 左を押していたら左に進む 
	if (CheckHitKey(KEY_INPUT_A))
	{
		playerX -= Speed; Reverse = TRUE;
		moveFlag = TRUE;
	}

	if (moveFlag == TRUE) // 動いたかどうか
	{
		if (CheckSoundMem(walksound) == 0)
		{
			PlaySoundMem(walksound, DX_PLAYTYPE_BACK, TRUE); // 歩行音を鳴らす
		}
	}
}

void Player::Player_Vec()
{
	// コヨーテタイムのカウンターをデクリメント
	if (coyoteCounter > 0)
	{
		coyoteCounter--;
	}

	isGround = FALSE; // 地面にいるかどうか

	bool nowSpace = CheckHitKey(KEY_INPUT_SPACE); //　スペースキー

	if (nowSpace == TRUE && prevSpace == FALSE) 
	{ // 地面・ブロック上のみ 
		if (isGround == TRUE || coyoteCounter > 0)
		{ 
			jumpPower = PLAYER_JUMP_POWER;
			jumpFlag = TRUE; 
			coyoteCounter = 0; // コヨーテタイムを消費
		} 
	}

	prevSpace = nowSpace; // 前フレームのスペースキーの状態を保存

	if (jumpFlag == TRUE) // ジャンプフラグが立っているとき
	{
		PlaySoundMem(jumpsound, DX_PLAYTYPE_BACK, TRUE); // ジャンプ音を鳴らす
		jumpFlag = FALSE; 
	}

	playerY -= jumpPower; 
	jumpPower -= GRAVITY;

	if (background) 
	{ 
		if (playerY >= GROUND_Y) 
		{ 
			playerY = GROUND_Y;
			// 地面にいる状態
			isGround = TRUE;
			// コヨーテタイムをセット
			coyoteCounter = COYOTE_TIME;
		} 
	}
	else 
	{ 
		if (playerY >= GROUND_Y)
		{
			// 地面のY座標
			playerY = GROUND_Y;
			// 地面にいる状態
			isGround = TRUE;
			// コヨーテタイムをセット
			coyoteCounter = COYOTE_TIME;
		} 
	}
}

void Player::Player_Draw()
{
	int cameraX = gBackground ? gBackground->cameraX : 0; // カメラのX座標を取得

	DrawReverseGraph(playerX - cameraX, playerY, playerGraph, TRUE, Reverse); // プレイヤーを描画
}

void Player::Player_End()
{
	DeleteGraph(playerGraph); // プレイヤーハンドルの削除
	DeleteSoundMem(walksound); // 歩行音の削除
	DeleteSoundMem(jumpsound); // ジャンプ音の削除
}

