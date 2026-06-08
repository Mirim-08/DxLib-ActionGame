#pragma once
#include "DxLib.h"
#include <vector>

class Player;
class Background;
class Game;

class Enemy
{
public:
	Player* player = nullptr;
	Background* background = nullptr;
	Game* game = nullptr;

	int enemyGraph = -1; // エネミーハンドル
	int hitsound = -1; // ヒット音ハンドル

	int x = 0; // X座標
	int y = 0; // Y座標
	int w = 0; //  幅
	int h = 0; // 高さ
	int speed = 0; // スピード
	int leftBound = 0; // 左移動距離
	int rightBound = 0; // 右移動距離
	int direction = 0; // 反対向きにする
	bool active = TRUE; // 存在するか

	std::vector<Enemy> enemies;

	Enemy() = default;

	Enemy(int _x, int _y, int _w, int _h, int _speed, int _leftBound, int _rightBound, int _direction, bool _active)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		speed = _speed;
		leftBound = _leftBound;
		rightBound = _rightBound;
		direction = _direction;
		active = _active;
	}

	void Enemy_Init();   // 初期化
	void Enemy_Update(); // 更新
	void Enemy_Setup();    // 配列
	void Enemy_Vec();    // 当たり判定
	void Enemy_Draw();   // 描画
	void Enemy_End();    // 終了
};


