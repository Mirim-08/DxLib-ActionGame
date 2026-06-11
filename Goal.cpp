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
	// プレイヤーまたはゲームが存在しない場合、
	// またはゲームオーバー中は判定しない
	if (!gPlayer || !gGame || gGame->gameOver)return;

	// プレイヤー情報を取得
	float playerX = gPlayer->playerX;
	float playerY = gPlayer->playerY;
	int playerW = gPlayer->playerW;
	int playerH = gPlayer->playerH;
	
	// ゴールとプレイヤーのAABB衝突判定
   if (playerX + playerW > goalX &&
	   playerX < goalX + goalW &&
	   playerY + playerH > goalY &&
	   playerY < goalY + goalH)
   { 
	   // ゴールに到達したらゲームクリア
	   gGame->gameClear = TRUE;

	   // BGMを停止
	   StopSoundMem(bgmsound);
   } 
} 

void Goal::Goal_Draw() 
{
	// カメラ位置を取得
	int cameraX = background ? background->cameraX : 0;

	// カメラ位置を考慮してゴールを描画
	DrawExtendGraph(
		goalX - cameraX,
		goalY, 
		goalX - cameraX + goalW, 
		goalY + goalH, 
		goalGraph,
		TRUE
	);
} 

void Goal::Goal_End() 
{
	DeleteGraph(goalGraph); // ゴール画像を解放
}