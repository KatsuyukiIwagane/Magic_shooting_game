#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <math.h>
#define WD_Width 720 // ウィンドウの幅
#define WD_Height 960 // ウィンドウの高さ
#define PLAY_WD_Width 520 //プレイウィンドウの幅
#define PLAY_WD_Height 960 //プレイウィンドウの高さ

#define SHOOT_INTERVAL 0.3 // 弾を撃つ間隔
#define MAX_BULLETS 255 // 最大弾数
#define WAVE_BULLET_MAX 5

#define PLAYER_WIDTH 50 // プレイヤーの幅
#define PLAYER_HEIGHT 50 // プレイヤーの高さ
#define PLAYER_HEALTH 3 // プレイヤーの初期ライフ
#define PLAYER_MAGIC 600 // プレイヤーの初期魔力
#define PLAYER_BASE_SPEED 120 // プレイヤーの移動速度

#define MAX_ENEMY 50 //最大敵数
#define ENEMY_WIDTH 50 // 敵の幅
#define ENEMY_HEIGHT 50 // 敵の高さ
#define ENEMY_HEALTH 3 // 敵のライフ
#define ENEMY_BASE_SPEED 60 // 敵の移動速度

#define MAX_SPELL_LENGTH 32 // 最大スペルの長さ


#define MY_PI 3.141592653589793

 TTF_Font* main_font; // メインフォント

//メインメニューの選択肢
typedef enum {
    MENU_NONE,
    MENU_START,
    MENU_CONTINUE,
    MENU_QUIT
}MenuSelection;

//スペルの種類
typedef enum {
    SPELL_NONE,
    SPELL_HEAL,
    SPELL_ELIMINATION
} SpellType;

//スペルの入力状態
typedef struct {
    char buffer[MAX_SPELL_LENGTH];
    int length;
} SpellInput;

//スペルの状態
typedef struct {
    const char* name;
    bool activated;
} SpellStatus;

#define SPELL_COUNT 2
extern SpellStatus spell_list[SPELL_COUNT];

extern SpellInput current_spell; // 現在のスペル入力状態

//敵の種類
typedef enum {
    ENEMY_CROW, //烏
    ENEMY_TYPE_COUNT //敵の種類数
}EnemyType;


//弾の種類
typedef enum {
    BULLET_NOMAL, //直線攻撃
    BULLET_WAVE //波状攻撃
} BulletType;

//ゲームの情報
typedef struct {
    SDL_Window* window;
    SDL_Renderer* render;
    SDL_Texture* background; // 背景画像
} Game;

typedef struct {
    SDL_Texture* health_icon;
    SDL_Texture* magic_icon;
}UI;

typedef struct {
    bool up; // 上に移動
    bool down; // 下に移動
    bool left; // 左に移動
    bool right; // 右に移動
    bool shoot; // 弾を撃つ
} Move;

typedef struct {
    float x, y; // 弾の位置
    int width, height; // 弾の幅と高さ
    int speed; // 弾の移動速度
    float angle;
    SDL_Texture* texture; // 弾の画像
    Move move; // 弾の移動状態
} Bullet;

//敵の情報
typedef struct {
    float x, y;
    int width, height; // 敵の幅と高さ
    int health; // 敵のライフ
    int speed; // 敵の移動速度
    int direction; // 敵の方向
    float shoot_timer; // 次の発射までのカウント
    int shoot_count; // 連続で撃った弾数
    float cooldown_timer; // クールダウン時間
    SDL_Texture* texture; // 敵の画像
    Move move; // 移動状態
} Enemy;

typedef struct {
    int x, y;
    int width, height; // 敵の幅と高さ
    int health; // 敵のライフ
    int magic; // 敵の魔力
    int speed; // 敵の移動速度
    SDL_Texture* texture; // 敵の画像
    Move move; // 移動状態
} Boss;

//プレイヤーの情報
typedef struct {
    float x, y;
    int width, height; // プレイヤーの幅と高さ
    int health; // プレイヤーのライフ
    int magic; // プレイヤーの魔力
    bool mp_short; //プレイヤーが魔力不足かどうか
    bool gameover;
    int speed; // プレイヤーの移動速度
    SDL_Texture* texture; // プレイヤーの画像
    Move move; // 移動状態
    BulletType bullet_type; //弾のタイプ
} Player;

typedef struct {
    double time_sec;  // 出現時間（秒単位）
    EnemyType type;
    int x, y;
} StageEvent;

extern Game game_info; // ゲームの情報
extern Player player; // プレイヤーの情報
extern Boss black; // ボス(黒色)の情報
extern Enemy enemiy_crows[MAX_ENEMY]; //敵(烏)の情報

extern float background_scroll_y;
extern const int background_scroll_speed;

extern Bullet bullets[MAX_BULLETS]; // 弾の配列
extern int bullet_count; // 弾の数
extern Bullet enemy_bullets[MAX_BULLETS]; //敵の弾の配列
extern int enemy_bullet_count; //敵の弾の数

extern bool boss_appear; // ボスが出現するかどうかのフラグ

extern float shoot_timer; // 弾を撃つ間隔

#define MAX_STAGE_EVENTS 1024
extern StageEvent stage_events[MAX_STAGE_EVENTS];
extern int stage_event_count;
extern int current_frame;

extern SDL_Texture* enemy_textures[ENEMY_TYPE_COUNT];

extern int InitWindow(const char *bg_file);
extern void InitPlayer(); // プレイヤーの初期化
extern void InitEnemies(); // 敵の初期化
extern void InitBoss(); // ボスの初期化
extern void InitBullets(); // 弾の初期化
extern void InitUI(); //UI画像の初期化
extern void InitEnemyTextures(); // 敵のテクスチャを初期化
extern void InitFonts(); // フォントの初期化

extern int PrintError(const char* str);
extern void HandleInput(SDL_Event* event);
extern void UpdateOblects();
extern void RenderFrame(double deltaTime); // 全画面の描画

extern void DrawBackground(double deltaTime); // 背景画像の描画
extern void DrawEnemies(); // 敵の描画
extern void DrawPlayer(); // プレイヤーの描画
extern void DrawBullets(); // 弾の描画
extern void DrawUI(); // UIの描画
extern void DrawBoss(); // ボスの描画
extern void DrawSubUI(); // サブUIの描画
extern void DrawSpellInput(); // スペル入力の描画
extern void DrawSpellList(SDL_Renderer* renderer); // スペルリストの描画

extern void UpdateOblects(double deltaTime); // オブジェクトの更新
extern void UpdatePlayer(double deltaTime); // プレイヤーの更新
extern void UpdateEnemies(double deltaTime); // 敵の更新
extern void UpdateBullets(double deltaTime); // 弾の更新
extern void UpdateUI(); // UIの更新
extern void UpdateBoss(double deltaTime); // ボスの更新
extern void UpdateSubUI(); // サブUIの更新
extern void UpdateStage(double deltaTime);

extern void HitEnemy(); // 敵にヒットした時の処理
extern void HitBoss(); // ボスにヒットした時の処理
extern void HitPlayer(); // プレイヤーにヒットした時の処理

extern void shootNomalBullet(double deltaTime);
extern void shootWaveBullet(double deltaTime);
extern void enemyShootBullets(double deltaTime);

extern void consumeMagicpoint(BulletType type);

extern void DrawMPErrorMessage();
extern void DrawGameOver();

extern void HandleSpellInput(const SDL_Event* event);
extern SpellType MatchSpell(const char* input);
extern void ExecuteSpell(SpellType spell);

MenuSelection ShowStartMenu();

extern void LoadStageScript(const char* filename);
extern int current_frame;


extern void BossAction(double deltaTime); // ボスの行動を更新





#endif