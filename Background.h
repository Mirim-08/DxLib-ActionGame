#pragma once
#include "DxLib.h"
#include "Config.h"

class Player;

class Background
{
public:
	Player* player = nullptr;

	int backgroundGraph = -1; // 背景ハンドル

	int screenWidth = SCREEN_WIDTH; // 画面の幅
    int screenHeight = SCREEN_HEIGHT; // 画面の高さ
	int backgroundX = 0; // 背景のX座標 
	
	// カメラ（画面）関連 
	int cameraX = 0; // カメラのワールドX（この分だけ左へずらして描画）

	void Back_Init(); // 初期化	
	void Camera_Update(); // カメラ
	void Back_Loop(); // 背景ループ
	void Back_Draw(); // 描画
	void Back_End(); // 終了
};
