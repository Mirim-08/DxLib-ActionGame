#pragma once
#include "DxLib.h"
#include <vector>

class Player;
class Background;
class Game;

// 敵キャラクターの管理クラス
class Enemy
{
public:
	Player* player = nullptr;          // プレイヤーへの参照
	Background* background = nullptr;  // 背景への参照
	Game* game = nullptr;              // ゲーム管理クラスへの参照

	int enemyGraph = -1;  // エネミー画像のハンドル
	int stompSound = -1;  // 踏みつけ音のハンドル

	float x = 0.0f; // X座標
	float y = 0.0f; // Y座標
	int w = 0;      // 幅
	int h = 0;      // 高さ

	int Speed = 0;       // 移動速度
	int leftBound = 0;   // 左側の移動限界
	int rightBound = 0;  // 右側の移動限界

	int Direction = 0;   // 移動方向（RIGHT または LEFT）
	bool Active = TRUE;  // 敵が存在しているか

	std::vector<Enemy> enemies; // ステージ内の全敵を管理する配列
	Enemy() = default;          // デフォルトコンストラクタ
	// 敵生成用コンストラクタ
	Enemy(
		float _x,
		float _y,
		int _w,
		int _h,
		int _speed,
		int _leftBound,
		int _rightBound,
		int _Direction,
		bool _Active
	)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		Speed = _speed;
		leftBound = _leftBound;
		rightBound = _rightBound;
		Direction = _Direction;
		Active = _Active;
	}

	void Enemy_Init();   // 敵画像・効果音の読み込み
	void Enemy_Update(); // 敵の移動更新
	void Enemy_Setup();  // 敵の配置設定
	void Enemy_Vec();    // プレイヤーとの当たり判定
	void Enemy_Draw();   // 敵の描画
	void Enemy_End();    // 終了処理
};
