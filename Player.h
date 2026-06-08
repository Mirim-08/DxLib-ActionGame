#pragma once
#include "DxLib.h"

class Background;

class Player
{
public:
	Background* background = nullptr;

	int playerGraph = -1; // プレイヤーハンドル
	int walksound = -1; // 歩行音ハンドル
	int jumpsound = -1; // ジャンプ音ハンドル

	float playerX = 100.0f; // X座標
	float playerY = 100.0f; // Y座標
	int playerW = 0; // 幅
	int playerH = 0; // 高さ
	float Speed = 0.0f; // スピード
	bool moveFlag = FALSE; // 動いているかのフラグ
	bool hitFlag = FALSE; // 当たっているかのフラグ
	bool Reverse = FALSE; // 反転フラグ
	float prevX = 0.0f;
	float prevY = 0.0f;
	float jumpPower = 0.0f; // ジャンプ力
	bool isGround = TRUE; // 地面にいるかどうか
	bool jumpFlag = FALSE; // ジャンプしているかのフラグ
	bool prevSpace = FALSE; // 前フレームのスペースキーの状態

	int coyoteCounter = 0;  // コヨーテタイムカウンター
	const int COYOTE_TIME = 6; // コヨーテタイムの長さ（フレーム数）

	void Player_Init(); //初期化
	void Player_Move(); // 動き
	void Player_Draw(); //描画
	void Player_Vec(); //当たり判定
	void Player_End(); // 終了
};
