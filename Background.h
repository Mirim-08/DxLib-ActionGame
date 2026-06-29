#pragma once
#include "DxLib.h"
#include "Config.h"

class Player;

// 背景描画とカメラ制御を管理するクラス
class Background
{
public:
	Player* player = nullptr; // プレイヤーへの参照（カメラ追従に使用）

	int backgroundGraph = -1; // 背景画像のハンドル

	int screenWidth = SCREEN_WIDTH;   // 画面の横幅
	int screenHeight = SCREEN_HEIGHT; // 画面の縦幅
	int backgroundX = 0;              // 背景画像の描画X座標

	// カメラ関連
	int cameraX = 0; // ワールド座標上のカメラ位置

	void Back_Init();      // 背景の初期化
	void Camera_Update();  // カメラ位置の更新
	void Back_Loop();      // 背景のループ位置計算
	void Back_Draw();      // 背景の描画
	void Back_End();       // 終了処理
};
