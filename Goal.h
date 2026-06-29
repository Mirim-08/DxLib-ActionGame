#pragma once
#include "DxLib.h"

class Player;
class Background;
class Game;

// ゴールオブジェクトを管理するクラス
class Goal
{
public:
	Player* player = nullptr;         // プレイヤークラスへの参照
	Background* background = nullptr; // 背景クラスへの参照
	Game* game = nullptr;             // ゲーム管理クラスへの参照

	int goalGraph = -1;  // ゴール画像のハンドル
	int clearSound = -1; // クリア音のハンドル

	void Goal_Init();     // ゴール画像の読み込み
	void Goal_Draw();     // ゴールの描画
	void Goal_Vec()const; // プレイヤーとの当たり判定
	void Goal_End();      // 終了処理
private:
	// ゴールの位置とサイズ
	int goalX = 4550; // X座標
	int goalY = 440;  // Y座標
	int goalW = 150;  // 幅
	int goalH = 150;  // 高さ
};
