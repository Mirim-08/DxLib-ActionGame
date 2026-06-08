#pragma once
#include "DxLib.h"

class Player; 
class Background; 
class Game; 

class Goal 
{ 
public: 
	Player* player = nullptr;
	Background* background = nullptr;
	Game* game = nullptr;

	int goalGraph = -1; // ゴールハンドル

	void Goal_Init(); // 初期化
	void Goal_Draw(); // 描画
	void Goal_Vec()const;  // 当たり判定
	void Goal_End();  // 終了処理
private:
	int goalX = 4550;// X座標
	int goalY = 440;// Y座標
	int goalW = 150;// 幅
	int goalH = 150;// 高さ
};

