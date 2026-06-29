#include "Block.h"
#include "Player.h"
#include "Background.h"
#include "Globals.h"
#include "Config.h"

void Block::Block_Init() // ブロック初期化
{
	blockGraph = LoadGraph("Resource/image/block.png"); // ブロック画像の読み込み
}

void Block::Block_Setup() // 足場配置
{
	// 各足場の位置とサイズを設定
	blocks =
	{
		// x座標, y座標, サイズ
		{300, GROUND_Y - 60, 120, 60},
		{520, GROUND_Y - 140, 120, 30},
		{760, GROUND_Y - 220, 120, 30},
		{1050, GROUND_Y - 80, 80, 80},
		{1300, GROUND_Y - 160, 160, 30},
		{1600, GROUND_Y - 60, 220, 60},
		{440, GROUND_Y - 100, 60, 30},
		{920, GROUND_Y - 180, 100, 30},
		{1850, GROUND_Y - 140, 120, 30},
		{2100, GROUND_Y - 60, 200, 60},
		{2400, GROUND_Y - 130, 200, 50},
		{2700, GROUND_Y - 170, 230, 40},
		{3100, GROUND_Y - 80, 130, 40},
		{3400, GROUND_Y - 180, 150, 40},
		{3700, GROUND_Y - 80, 130, 40},
		{4000, GROUND_Y - 190, 100, 30},
		{4200, GROUND_Y - 50, 140, 60}
	};
}

void Block::Block_Vec() // ブロックとの当たり判定
{
	if (gPlayer)
	{
		// 毎フレーム接地状態をリセットし、
		// 衝突時のみ再びTRUEにする
		gPlayer->isGround = FALSE;
	}
	if (!gPlayer) return;// プレイヤーが存在しない場合は処理しない
	// 前フレームと現在フレームの座標を取得
	float prevX = gPlayer->prevX;
	float prevY = gPlayer->prevY;
	float playerX = gPlayer->playerX;
	float playerY = gPlayer->playerY;
	// プレイヤーサイズを取得
	int playerW = gPlayer->playerW;
	int playerH = gPlayer->playerH;
	// 全ブロックとの衝突判定
	for (const Block& b : blocks)
	{
		// AABB（矩形同士）の当たり判定
		if (playerX + playerW > b.x &&
			playerX < b.x + b.w &&
			playerY + playerH > b.y &&
			playerY < b.y + b.h)
		{
			// 上からブロックに着地した場合
			if (prevY + playerH <= b.y)
			{
				// プレイヤーをブロック上に配置
				gPlayer->playerY = b.y - playerH;
				gPlayer->prevY = gPlayer->playerY;
				gPlayer->jumpPower = 0;                // 落下速度をリセット
				gPlayer->isGround = TRUE;              // 接地状態にする
				gPlayer->coyoteCounter = COYOTE_TIME;  // コヨーテタイムを開始
			}
			// 下からブロックにぶつかった場合
			else if (prevY >= b.y + b.h)
			{
				gPlayer->playerY = b.y + b.h;
				gPlayer->jumpPower = 0; // 上昇を停止
			}
			// 左側からブロックにぶつかった場合
			else if (prevX + playerW <= b.x)
			{
				gPlayer->playerX = b.x - playerW;
			}
			// 右側からブロックにぶつかった場合
			else if (prevX >= b.x + b.w)
			{
				gPlayer->playerX = b.x + b.w;
			}
		}
	}
}

void Block::Block_Draw()// ブロック（足場）描画 
{
	// カメラ位置を取得
	int cameraX = gBackground ? gBackground->cameraX : 0;
	for (const Block& b : blocks)
	{
		// カメラ位置を考慮した描画座標
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

void Block::Block_End() // 終了処理
{
	DeleteGraph(blockGraph); // ブロック画像の解放
}
