#include "Background.h"
#include "Player.h"

void Background::Back_Init()
{
	backgroundGraph = LoadGraph("data/background.png"); // 背景画像の読み込み

	// 画面サイズを取得して背景の表示サイズを設定（オプション）
	backgroundX = 0;
	cameraX = 0;
}

void Background::Camera_Update()
{
	// カメラ追従（プレイヤーが画面左付近に来るようにする） 
	if (screenWidth > 0)
	{
		int px = player ? player->playerX : 0;
		cameraX = px - (int)(screenWidth / CAMERA_POSITION_RATIO);

		int maxCameraX = max(0, STAGE_WIDTH - screenWidth);
		cameraX = min(cameraX, maxCameraX);

		if (cameraX < 0)
		{
			cameraX = 0;
		}
	}
}

void Background::Back_Loop()
{
	// 背景の描画位置（ループ） 
	int mod = cameraX % screenWidth;
	if (mod < 0) mod += screenWidth;
	backgroundX = -mod;
}

void Background::Back_Draw()
{
	// 背景を描画（スクロールのため2枚描画、サイズを変更して描画） 
	if (screenWidth > 0 && screenHeight > 0)
	{
		// 1枚目の背景（拡大・縮小して描画） 
		DrawExtendGraph(backgroundX, 0, backgroundX + screenWidth, screenHeight, backgroundGraph, TRUE);
		// 2枚目の背景（ループ用） 
		if (backgroundX < 0)
		{
			DrawExtendGraph(backgroundX + screenWidth, BACKGROUND_Y, backgroundX + screenWidth * 2, screenHeight, backgroundGraph, TRUE);
		}
		else if (backgroundX > 0)
		{
			DrawExtendGraph(backgroundX - screenWidth, BACKGROUND_Y, backgroundX, screenHeight, backgroundGraph, TRUE);
		}
	}
}

void Background::Back_End()
{
	DeleteGraph(backgroundGraph); // 背景ハンドルの削除
}
