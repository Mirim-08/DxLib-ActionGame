#pragma once

class Player;
class Background;
class Game;
class Enemy;
class Block;
class Goal;
class Title;

//==================================================
// グローバルオブジェクト宣言
// 各クラスを他のファイルから参照するために使用
//==================================================
extern Player* gPlayer;         // プレイヤー管理クラス
extern Background* gBackground; // 背景・カメラ管理クラス
extern Game* gGame;             // ゲーム状態管理クラス
extern Enemy* gEnemy;           // 敵管理クラス
extern Block* gBlock;           // 足場（ブロック）管理クラス
extern Goal* gGoal;             // ゴール管理クラス
extern Title* gTitle;           // タイトル画面管理クラス

extern int bgmSound;  // BGMハンドル
extern int overSound; // ゲームオーバー音バンドル