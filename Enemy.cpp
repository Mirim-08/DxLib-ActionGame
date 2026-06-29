#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Game.h"
#include "Globals.h"
#include "Config.h"

void Enemy::Enemy_Init() // エネミー初期化
{
	enemyGraph = LoadGraph("Resource/image/enemy.png");       // エネミー画像の読み込み
	overSound = LoadSoundMem("Resource/sound/gameover.mp3"); // ゲームオーバー音の読み込み
	stompSound = LoadSoundMem("Resource/sound/stomp.mp3");   // 踏みつけ音の読み込み
}

void Enemy::Enemy_Update() // エネミー更新
{
	for (Enemy& e : enemies)
	{
		if (!e.Active) continue;      // 非アクティブな敵は処理しない
		e.x += e.Speed * e.Direction; // 向いている方向へ移動
		// 左端に到達したら右向きに反転
		if (e.x <= e.leftBound)
		{
			e.x = e.leftBound;
			e.Direction = RIGHT;
		}
		// 右端に到達したら左向きに反転
		if (e.x + e.w >= e.rightBound)
		{
			e.x = e.rightBound - e.w;
			e.Direction = LEFT;
		}
	}
}


void  Enemy::Enemy_Setup() // エネミー配置
{
	std::vector<Enemy> enemyList
	{
		// x座標, y座標, サイズ, 移動速度, 移動範囲, 初期向き
		{330,  GROUND_Y - 100, ENEMY_SIZE, ENEMY_SIZE, ENEMY_SPEED, 300,  410,  RIGHT, TRUE},
		{540,  GROUND_Y - 180, ENEMY_SIZE, ENEMY_SIZE, ENEMY_SPEED, 520,  620,  LEFT , TRUE},
		{780,  GROUND_Y - 260, ENEMY_SIZE, ENEMY_SIZE, ENEMY_SPEED, 760,  860,  RIGHT, TRUE},
		{1320, GROUND_Y - 200, ENEMY_SIZE, ENEMY_SIZE, ENEMY_SPEED, 1300, 1420, LEFT , TRUE},
		{1880, GROUND_Y - 180, ENEMY_SIZE, ENEMY_SIZE, ENEMY_SPEED, 1850, 1950, RIGHT, TRUE},
		{2420, GROUND_Y - 170, ENEMY_SIZE, ENEMY_SIZE, ENEMY_SPEED, 2400, 2600, LEFT , TRUE},
		{2720, GROUND_Y - 210, ENEMY_SIZE, ENEMY_SIZE, ENEMY_SPEED, 2700, 2950, RIGHT, TRUE},
		{3420, GROUND_Y - 220, ENEMY_SIZE, ENEMY_SIZE, ENEMY_SPEED, 3400, 3550, LEFT , TRUE},
		{4020, GROUND_Y - 230, ENEMY_SIZE, ENEMY_SIZE, ENEMY_SPEED, 4000, 4100, LEFT , TRUE},
	};
	enemies = enemyList;
	// 各敵に必要なオブジェクトへの参照を設定
	for (Enemy& e : enemies)
	{
		e.player = gPlayer;
		e.background = gBackground;
		e.game = gGame;
	}
}

void Enemy::Enemy_Vec() // プレイヤーとの当たり判定
{
	if (!gPlayer) return; // プレイヤーが存在しない場合は処理しない
	// プレイヤー情報を取得
	float prevY = gPlayer->prevY;
	float jumpPower = gPlayer->jumpPower;
	float playerX = gPlayer->playerX;
	float playerY = gPlayer->playerY;
	int playerW = gPlayer->playerW;
	int playerH = gPlayer->playerH;
	for (Enemy& e : enemies)
	{
		if (!e.Active) continue; // 倒された敵は判定しない
		// AABBによる矩形同士の衝突判定
		if (playerX < e.x + e.w - ENEMY_HIT_OFFSET &&
			playerX + playerW > e.x + ENEMY_HIT_OFFSET &&
			playerY < e.y + e.h &&
			playerY + playerH > e.y)
		{
			if (jumpPower <= 0 &&
				prevY + playerH <= e.y + ENEMY_GROUND_CHECK_OFFSET)
			{
				// 敵を踏んだ
				PlaySoundMem(stompSound, DX_PLAYTYPE_BACK);
				e.Active = FALSE;
				gPlayer->jumpPower = ENEMY_JUMP_BOUNCE;
				gGame->Score += ENEMY_KILL_SCORE;
			}
			else
			{
				// 敵にぶつかった
				PlaySoundMem(overSound, DX_PLAYTYPE_BACK);
				gGame->gameOver = TRUE;
				StopSoundMem(bgmSound);
			}
		}
	}
}

void Enemy::Enemy_Draw()// エネミー描画
{
	int cameraX = gBackground ? gBackground->cameraX : 0;
	for (const Enemy& e : enemies)
	{
		if (!e.Active) continue;// 非表示の敵は描画しない
		// カメラ位置を考慮した描画座標
		int ex = e.x - cameraX;
		// 向きに応じて反転描画
		DrawRotaGraph2(
			ex,
			e.y,
			ENEMY_CENTER_X,
			ENEMY_CENTER_Y,
			ENEMY_SCALE,
			ANGLE,
			enemyGraph,
			TRUE,
			e.Direction == LEFT
		);
	}
}

void Enemy::Enemy_End() // 終了処理
{
	DeleteGraph(enemyGraph);    // エネミー画像を解放
	DeleteSoundMem(overSound);  // ヒット音を解放
	DeleteSoundMem(stompSound); // 踏みつけ音を解放
}
