#include "Block.h"
#include "Player.h"
#include "Background.h"
#include "Globals.h"
#include "Config.h"

void Block::Block_Init()
{
	blockGraph = LoadGraph("data/block.png"); // ブロック画像の読み込み
}

void Block::Block_Setup() // 足場配置
{
	int groundY = GROUND_Y;

	blocks =
	{
		{300, groundY - 60, 120, 60},
		{520, groundY - 140, 120, 30},
		{760, groundY - 220, 120, 30},
		{1050, groundY - 80, 80, 80},
		{1300, groundY - 160, 160, 30},
		{1600, groundY - 60, 220, 60},
		{440, groundY - 100, 60, 30},
		{920, groundY - 180, 100, 30},
		{1850, groundY - 140, 120, 30},
		{2100, groundY - 60, 200, 60},
		{2400, groundY - 130, 200, 50},
		{2700, groundY - 170, 230, 40},
		{3100, groundY - 80, 130, 40},
		{3400, groundY - 180, 150, 40},
		{3700, groundY - 80, 130, 40},
		{4000, groundY - 190, 100, 30},
		{4200, groundY - 50, 140, 60}
	};
}

void Block::Block_Vec() // 当たり判定
{
	if (gPlayer)
	{
		gPlayer->isGround = false; // 地面にいるかどうかのフラグをリセット
	}

	if (!gPlayer) return;

	float prevX = gPlayer->prevX;
	float prevY = gPlayer->prevY;
	float playerX = gPlayer->playerX;
	float playerY = gPlayer->playerY;
	int playerW = gPlayer->playerW;
	int playerH = gPlayer->playerH;

	// 全ブロックとの衝突判定
	for (const Block& b : blocks)
	{
		// AABB衝突判定
		if (playerX + playerW > b.x &&
			playerX < b.x + b.w &&
			playerY + playerH > b.y &&
			playerY < b.y + b.h)
		{
			// 上から着地
			if (prevY + playerH <= b.y)
			{
				gPlayer->playerY = b.y - playerH;
				gPlayer->prevY = gPlayer->playerY;

				gPlayer->jumpFlag = FALSE; //　ジャンプフラグ

				gPlayer->jumpPower = 0;

				gPlayer->isGround = TRUE; // 地面にいるフラグを立てる
				// コヨーテタイムをセット
				gPlayer->coyoteCounter = gPlayer->COYOTE_TIME;
			}
			// 下からぶつかる
			else if (prevY >= b.y + b.h)
			{
				gPlayer->playerY = b.y + b.h;
				gPlayer->jumpPower = 0;
			}
			// 左からぶつかる
			else if (prevX + playerW <= b.x)
			{
				gPlayer->playerX = b.x - playerW;
			}
			// 右からぶつかる
			else if (prevX >= b.x + b.w)
			{
				gPlayer->playerX = b.x + b.w;
			}
		}
	}
}

void Block::Block_Draw()// ブロック（足場）描画 
{
	int cameraX = gBackground ? gBackground->cameraX : 0;

	for (const Block& b : blocks)
	{
		int sx = b.x - cameraX;

		DrawExtendGraph(
			sx, 
			b.y, 
			sx + b.w, 
			b.y + b.h,
			blockGraph, 
			FALSE
		);
	}
}

void Block::Block_End() // 終了
{
	DeleteGraph(blockGraph); // ブロックハンドルの削除
}
