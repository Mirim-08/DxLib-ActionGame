#pragma once
#include "DxLib.h"
#include <vector>

class Player;
class Background;

class Block
{
public:
	Player* player = nullptr;
	Background* background = nullptr;

	int blockGraph = -1; // ブロックハンドル

	int x = 0; // X座標
	int y = 0; // Y座標
	int w = 0; // 幅
	int h = 0; // 高さ

	Block() = default;

	Block(int _x, int _y, int _w, int _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

	std::vector<Block> blocks;

	void Block_Init(); // 初期化
	void Block_Setup();    // 配列
	void Block_Vec();  // 当たり判定
	void Block_Draw(); // 描画
	void Block_End();  // 終了
};

