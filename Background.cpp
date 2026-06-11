#include "Background.h"
#include "Player.h"

void Background::Back_Init()
{
	backgroundGraph = LoadGraph("data/background.png"); // 背景画像の読み込み

	// 背景の初期位置とカメラ位置を初期化
	backgroundX = 0;
	cameraX = 0;
}

void Background::Camera_Update()
{
	// プレイヤーを基準にカメラを追従させる
	if (screenWidth > 0)
	{
		int px = player ? player->playerX : 0;

		// プレイヤーが画面の一定位置に来るようカメラを移動
		cameraX = px - (int)(screenWidth / CAMERA_POSITION_RATIO);

		// ステージ右端を超えないように制限
		int maxCameraX = max(0, STAGE_WIDTH - screenWidth);
		cameraX = min(cameraX, maxCameraX);

		// ステージ左端を超えないように制限
		if (cameraX < 0)
		{
			cameraX = 0;
		}
	}
}

void Background::Back_Loop()
{
	// 背景をループ表示するための描画位置を計算
	int mod = cameraX % screenWidth;

	// 負の値対策
	if (mod < 0) mod += screenWidth;

	// カメラ移動量に応じて背景をスクロール
	backgroundX = -mod;
}

void Background::Back_Draw()
{
	// 背景をループ描画する
	if (screenWidth > 0 && screenHeight > 0)
	{
		// 1枚目の背景を描画
		DrawExtendGraph(
			backgroundX,
			0,
			backgroundX + screenWidth, 
			screenHeight,
			backgroundGraph, 
			TRUE
		);

		// 画面の隙間を埋めるため2枚目の背景を描画
		if (backgroundX < 0)
		{
			DrawExtendGraph(
				backgroundX + screenWidth,
				BACKGROUND_Y,
				backgroundX + screenWidth * 2, 
				screenHeight,
				backgroundGraph, 
				TRUE);
		}
		else if (backgroundX > 0)
		{
			DrawExtendGraph(
				backgroundX - screenWidth,
				BACKGROUND_Y, 
				backgroundX, 
				screenHeight,
				backgroundGraph, 
				TRUE);
		}
	}
}

void Background::Back_End()
{
	DeleteGraph(backgroundGraph);  // 背景画像を解放
}
