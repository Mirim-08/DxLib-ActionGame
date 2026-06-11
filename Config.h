#pragma once
//==================================================
// 画面設定
//==================================================
const int SCREEN_WIDTH = 1280;     // 画面幅
const int SCREEN_HEIGHT = 720;     // 画面高さ
const int SCREEN_COLOR_DEPTH = 32; // 色深度
const int FRAME_TIME_MS = 17;      // 約60FPS
const int STAGE_WIDTH = 4900;      // ステージ全体の横幅

//==================================================
// エネミー設定
//==================================================
const int ENEMY_SPEED = 2;                  // 敵の移動速度
const int ENEMY_SIZE = 40;                  // 敵のサイズ
const int RIGHT = 1;                        // 右方向
const int LEFT = -1;                        // 左方向
const int ENEMY_CENTER_X = 0;               // 回転・反転時の中心X座標
const int ENEMY_CENTER_Y = 0;               // 回転・反転時の中心Y座標
const float ENEMY_SCALE = 0.65f;            // 敵画像の拡大率
const float ANGLE = 0.0f;                   // 描画角度
const int ENEMY_JUMP_BOUNCE = 15;           // 敵を踏んだ時の跳ね返り力
const int ENEMY_KILL_SCORE = 1000;          // 敵撃破時の加算スコア
const int ENEMY_HIT_OFFSET = 8;             // 当たり判定縮小用オフセット
const int ENEMY_GROUND_CHECK_OFFSET = 10;   // 上から踏んだ判定用オフセット

//==================================================
// ステージ設定
//==================================================
const float GROUND_Y = 510.0f; // 地面のY座標
const int BACKGROUND_Y = 0;    // 背景描画位置

//==================================================
// スコア設定
//==================================================
const int SCORE_X = 0;              // スコア表示X座標
const int SCORE_Y = 0;              // スコア表示Y座標
const int SCORE_TIME_DIVISOR = 10;  // 経過時間によるスコア加算間隔

//==================================================
// カラー定義
//==================================================
const int WHITE = 0xffffff;  // 白
const int YELLOW = 0xffff00; // 黄色
const int GRAY = 0xcccccc;   // グレー
const int RED = 0xFF0000;    // 赤
const int BLACK = 0x000000;  // 黒

//==================================================
// タイトル画面設定
//==================================================
const int CTRL_W = 50; // 操作説明の表示位置X
const int BACK_X = 0;  // 背景描画開始X
const int BACK_Y = 0;  // 背景描画開始Y

//==================================================
// プレイヤー設定
//==================================================
const float PLAYER_SPEED_NORMAL = 5.0f; // 通常移動速度
const float PLAYER_SPEED_RUN = 7.0f;    // ダッシュ速度
const int PLAYER_JUMP_POWER = 20;       // ジャンプ初速
const float GRAVITY = 1.0f;             // 重力加速度
const float DEAD_ACCELERATION = 0.8f;   // 死亡時の落下加速度

//==================================================
// カメラ設定
//==================================================
const float CAMERA_POSITION_RATIO = 4.5f; // プレイヤーの表示位置比率

//==================================================
// UI表示位置
//==================================================
const int GAMEOVER_TEXT_OFFSET_X = 110;   // GAME OVER表示位置X
const int GAMEOVER_TEXT_OFFSET_Y = 20;    // GAME OVER表示位置Y
const int GAMEINFO_TEXT_OFFSET_X = 200;   // 操作説明表示位置X
const int GAMEINFO_TEXT_OFFSET_Y = 20;    // 操作説明表示位置Y

//==================================================
// タイトル画面UI
//==================================================
const int TITLE_OFFSET_X = 200; // タイトル表示位置X
const int TITLE_OFFSET_Y = 150; // タイトル表示位置Y
const int ENTER_OFFSET_Y = 100; // ENTER案内表示位置Y

//==================================================
// フォント設定
//==================================================
const int DEFAULT_SIZE = 30;    // 通常フォントサイズ
const int TITLE_FONT_SIZE = 80; // タイトル文字サイズ
const int START_FONT_SIZE = 40; // スタート案内文字サイズ
const int HELP_FONT_SIZE = 25;  // 操作説明文字サイズ
