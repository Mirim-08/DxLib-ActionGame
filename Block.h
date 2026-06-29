#pragma once
#include "DxLib.h"
#include <vector>

class Player;
class Background;

// 足場（ブロック）の管理クラス
class Block
{
public:
	Player* player = nullptr;         // プレイヤーへの参照
	Background* background = nullptr; // 背景への参照

	int blockGraph = -1; // ブロック画像のハンドル

	// ブロックの位置・サイズ情報
	int x = 0;      // X座標
	float y = 0.0f; // Y座標
	int w = 0;      // 幅
	int h = 0;      // 高さ

	std::vector<Block> blocks; // ステージ内の全ブロックを格納
	Block() = default;         // デフォルトコンストラクタ
	// ブロック生成用コンストラクタ
	Block(int _x, float _y, int _w, int _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

	void Block_Init();   // ブロック画像の読み込み
	void Block_Setup();  // ブロック配置の設定
	void Block_Vec();    // プレイヤーとの当たり判定
	void Block_Draw();   // ブロックの描画
	void Block_End();    // 終了処理
};
