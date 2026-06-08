#include "Goal.h" 
#include "Player.h"
#include "Background.h"
#include "Game.h" 
#include "Globals.h"

void Goal::Goal_Init() 
{ 
	goalGraph = LoadGraph("data/goal.png");  // ゴール画像の読み込み
} 

void Goal::Goal_Vec() const
{ 
	if (!gPlayer || !gGame || gGame->gameOver)return;

	float playerX = gPlayer->playerX;
	float playerY = gPlayer->playerY;
	int playerW = gPlayer->playerW;
	int playerH = gPlayer->playerH;
	
   // プレイヤー当たり判定、矩形同士の衝突判定（AABB） 
   if (playerX + playerW > goalX &&
	   playerX < goalX + goalW &&
	   playerY + playerH > goalY &&
	   playerY < goalY + goalH)
   { 
	   gGame->gameClear = TRUE; // 触れたらクリアフラグを立てる
	   StopSoundMem(bgmsound);// BGMを止める
   } 
} 

void Goal::Goal_Draw() 
{
	int cameraX = background ? background->cameraX : 0;
	// ゴール描画 
	DrawExtendGraph(goalX - cameraX, goalY, goalX - cameraX + goalW, goalY + goalH, goalGraph, TRUE);
} 

void Goal::Goal_End() 
{
	DeleteGraph(goalGraph); // ゴールハンドルの削除
}