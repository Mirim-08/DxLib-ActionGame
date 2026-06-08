#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Game.h"
#include "Globals.h"
#include "Config.h"

void Enemy::Enemy_Init() // エネミー初期化
{
    enemyGraph = LoadGraph("data/enemy.png"); // エネミー画像の読み込み
	hitsound = LoadSoundMem("sound/hit.mp3"); // ヒットサウンドの読み込み
}

void Enemy::Enemy_Update() // 更新
{
	for (auto& e : enemies)
	{
		if (!e.active) continue;// 左右に動く

		e.x += e.speed * e.direction;

		if (e.x <= e.leftBound)
		{
			e.x = e.leftBound;
			e.direction = RIGHT;
		}

		if (e.x + e.w >= e.rightBound)
		{
			e.x = e.rightBound - e.w;
			e.direction = LEFT;
		}
	}
}


void  Enemy::Enemy_Setup() // エネミー配置
{
	std::vector<Enemy> enemyList
	{
		{x = 330,  y = GROUND_Y - 100, w = ENEMY_SIZE, h = ENEMY_SIZE, speed = ENEMY_SPEED, leftBound = 300,  rightBound = 410,  direction = RIGHT, active = true},
	    {x = 540,  y = GROUND_Y - 180, w = ENEMY_SIZE, h = ENEMY_SIZE, speed = ENEMY_SPEED, leftBound = 520,  rightBound = 620,  direction = LEFT , active = true},
	    {x = 780,  y = GROUND_Y - 260, w = ENEMY_SIZE, h = ENEMY_SIZE, speed = ENEMY_SPEED, leftBound = 760,  rightBound = 860,  direction = RIGHT, active = true},
	    {x = 1320, y = GROUND_Y - 200, w = ENEMY_SIZE, h = ENEMY_SIZE, speed = ENEMY_SPEED, leftBound = 1300, rightBound = 1420, direction = LEFT , active = true},
	    {x = 1880, y = GROUND_Y - 180, w = ENEMY_SIZE, h = ENEMY_SIZE, speed = ENEMY_SPEED, leftBound = 1850, rightBound = 1950, direction = RIGHT, active = true},
	    {x = 2420, y = GROUND_Y - 170, w = ENEMY_SIZE, h = ENEMY_SIZE, speed = ENEMY_SPEED, leftBound = 2400, rightBound = 2600, direction = LEFT , active = true},
	    {x = 2720, y = GROUND_Y - 210, w = ENEMY_SIZE, h = ENEMY_SIZE, speed = ENEMY_SPEED, leftBound = 2700, rightBound = 2950, direction = RIGHT, active = true},
	    {x = 3420, y = GROUND_Y - 220, w = ENEMY_SIZE, h = ENEMY_SIZE, speed = ENEMY_SPEED, leftBound = 3400, rightBound = 3550, direction = LEFT , active = true},
	    {x = 4020, y = GROUND_Y - 230, w = ENEMY_SIZE, h = ENEMY_SIZE, speed = ENEMY_SPEED, leftBound = 4000, rightBound = 4100, direction = LEFT , active = true},
	};
	enemies = enemyList;

	for (Enemy& e : enemies)
	{
		e.player = gPlayer;
		e.background = gBackground;
		e.game = gGame;
	}
}

void Enemy::Enemy_Vec() // 当たり判定
{
	if (!gPlayer) return; // プレイヤーが存在しない場合は処理しない

	float prevY = gPlayer->prevY;
	float jumpPower = gPlayer->jumpPower;
	float playerX = gPlayer->playerX;
	float playerY = gPlayer->playerY;
	int playerW = gPlayer->playerW;
	int playerH = gPlayer->playerH;

	for (Enemy& e : enemies)
	{
		if (!e.active) continue; // 非アクティブなら処理スキップ

		// 矩形同士の衝突判定（AABB）
		if (playerX < e.x + e.w - ENEMY_HIT_OFFSET &&
			playerX + playerW > e.x + ENEMY_HIT_OFFSET &&
			playerY < e.y + e.h &&
			playerY + playerH > e.y)
		{
			PlaySoundMem(hitsound, DX_PLAYTYPE_BACK); // ヒット音を再生

			// プレイヤーがジャンプしていて、敵の上から落下している場合
			if (jumpPower <= 0 && prevY + playerH <= e.y + ENEMY_GROUND_CHECK_OFFSET)
			{
				e.active = FALSE;

				gPlayer->jumpPower = ENEMY_JUMP_BOUNCE;
				gGame->score += ENEMY_KILL_SCORE;
			}
			else
			{
				gGame->gameOver = TRUE; // ゲームオーバー
				StopSoundMem(bgmsound); // BGMを止める
			}
		}
	}
}

void Enemy::Enemy_Draw()// エネミー描画
{
	int cameraX = gBackground ? gBackground->cameraX : 0;

	for (const Enemy& e : enemies)
	{
		if (!e.active) continue;

		int ex = e.x - cameraX;

		DrawRotaGraph2(
			ex,
			e.y,
			ENEMY_CENTER_X,
			ENEMY_CENTER_Y,
			ENEMY_SCALE,
			ANGLE,
			enemyGraph,
			TRUE,
			e.direction == LEFT
		);
	}
}

void Enemy::Enemy_End() // 終了
{
	DeleteGraph(enemyGraph); // 敵ハンドルを削除
	DeleteSoundMem(hitsound); // ヒット音ハンドルを削除
}
