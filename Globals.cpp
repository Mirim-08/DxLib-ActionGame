#include "Globals.h"
#include "Player.h"
#include "Background.h"
#include "Game.h"
#include "Enemy.h"
#include "Block.h"
#include "Goal.h"
#include "Title.h"

//==================================================
// グローバルオブジェクトの実体定義
// 各クラスから共有して利用する
//==================================================

Player* gPlayer = nullptr;         // プレイヤー管理オブジェクト
Background* gBackground = nullptr; // 背景・カメラ管理オブジェクト
Game* gGame = nullptr;             // ゲーム状態管理オブジェクト
Enemy* gEnemy = nullptr;           // 足場（ブロック）管理オブジェクト
Block* gBlock = nullptr;           // ゴール管理オブジェクト
Goal* gGoal = nullptr;             // タイトル画面管理オブジェクト

int bgmsound = -1; // BGMサウンドハンドル