#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_COLOR_DEPTH = 32;
const int FRAME_TIME_MS = 17;  // 約60FPS
const int STAGE_WIDTH = 4900;

// エネミー
const int ENEMY_SPEED = 2;
const int ENEMY_SIZE = 40;
const int RIGHT = 1;
const int LEFT = -1;
const int ENEMY_CENTER_X = 0;
const int ENEMY_CENTER_Y = 0;
const float ENEMY_SCALE = 0.65f;
const float ANGLE = 0.0f;
const int ENEMY_JUMP_BOUNCE = 15;
const int ENEMY_KILL_SCORE = 1000;
const int ENEMY_HIT_OFFSET = 8;
const int ENEMY_GROUND_CHECK_OFFSET = 10;

const float GROUND_Y = 510.0f;
const int BACKGROUND_Y = 0;

// スコア
const int SCORE_X = 0;
const int SCORE_Y = 0;
const int SCORE_TIME_DIVISOR = 10;  // 0.01秒ごとに+1

// カラー
const int WHITE = 0xffffff;
const int YELLOW = 0xffff00;
const int GRAY = 0xcccccc;
const int RED = 0xFF0000;
const int BLACK = 0x000000;

// タイトル
const int CTRL_W = 50;
const int BACK_X = 0;
const int BACK_Y = 0;

// プレイヤー
const float PLAYER_SPEED_NORMAL = 5.0f;
const float PLAYER_SPEED_RUN = 7.0f;
const int PLAYER_JUMP_POWER = 20;
const float GRAVITY = 1.0f;
const float DEAD_ACCELERATION = 0.8f;

// カメラ
const float CAMERA_POSITION_RATIO = 4.5f;

// ゴール
const int PLAYER_DEATH_VELOCITY = -20;  // 敵に当たった時の上向き速度

// UI表示位置 
const int GAMEOVER_TEXT_OFFSET_X = 110;    // ゲームオーバー、クリアテキストのX軸
const int GAMEOVER_TEXT_OFFSET_Y = 20;     // ゲームオーバー、クリアテキストのY軸
const int GAMEINFO_TEXT_OFFSET_X = 200;    // ゲーム情報テキストのX軸
const int GAMEINFO_TEXT_OFFSET_Y = 20;     // ゲーム情報テキストのY軸

// タイトル
const int TITLE_OFFSET_X = 200;
const int TITLE_OFFSET_Y = 150;
const int ENTER_OFFSET_Y = 100;

// フォントサイズ
const int DEFAULT_SIZE = 30;
const int TITLE_FONT_SIZE = 80;
const int START_FONT_SIZE = 40;
const int HELP_FONT_SIZE = 25;
