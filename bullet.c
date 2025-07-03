#include "system.h"
#include <math.h>



Bullet bullets[MAX_BULLETS]; // 弾の配列
int bullet_count = 0; // 弾の数

Bullet enemy_bullets[MAX_BULLETS]; //敵の弾の配列
int enemy_bullet_count = 0;

void InitBullets() {
    // 弾の初期化処理
    SDL_Texture* bullet_texture = IMG_LoadTexture(game_info.render, "./image/nomal_bullet.png"); // 弾のテクスチャ
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].x = 0;
        bullets[i].y = 0;
        bullets[i].width = 25; // 弾の幅
        bullets[i].height = 25; // 弾の高さ
        bullets[i].speed = 3; // 弾の移動速度
        bullets[i].texture = bullet_texture;
        if (bullets[i].texture == NULL) {
            PrintError(SDL_GetError());
        }
        bullets[i].move = (Move){false, false, false, false, false}; // 移動状態を初期化
    }

    //敵の弾の初期化
    SDL_Texture* enemy_bullet_texture = IMG_LoadTexture(game_info.render, "./image/nomal_bullet_enemy.png"); //敵の弾のテクスチャ
    for (int i = 0; i < MAX_BULLETS; i++) {
        enemy_bullets[i].x = -999;
        enemy_bullets[i].y = -999;
        enemy_bullets[i].width = 15; // 弾の幅
        enemy_bullets[i].height = 15; // 弾の高さ
        enemy_bullets[i].speed = 3; // 弾の移動速度
        enemy_bullets[i].texture = enemy_bullet_texture;
        if (bullets[i].texture == NULL) {
            PrintError(SDL_GetError());
        }
        bullets[i].move = (Move){false, false, false, false, false}; // 移動状態を初期化
    }


}

void shootNomalBullet() {
    if (player.move.shoot && bullet_count < MAX_BULLETS && shoot_interval % SHOOT_INTERVAL == 0) {
        consumeMagicpoint(player.bullet_type);
        if (!player.move.shoot) return;  // MP不足でキャンセルされたら以降スキップ
        float base_angle = -MY_PI / 2; 
        // 弾を撃つ処理
        bullets[bullet_count].angle = base_angle;
        bullets[bullet_count].x = player.x + player.width / 2 - bullets[bullet_count].width / 2;
        bullets[bullet_count].y = player.y;
        bullet_count++;
        shoot_interval = 1; // 弾を撃ったので間隔をリセット
    }
    else if (player.move.shoot && shoot_interval % SHOOT_INTERVAL != 0) {
        shoot_interval++; // 弾を撃つ間隔を調整
    }
    for (int i = 0; i < bullet_count; i++) {
        bullets[i].y -= bullets[i].speed; // 弾を上に移動
        if (bullets[i].y < 0) {
            // 画面外に出た弾は削除
            for (int j = i; j < bullet_count - 1; j++) {
                bullets[j] = bullets[j + 1];
            }
            bullet_count--;
            i--; // インデックスを調整
        }
    }
}


void shootWaveBullet() {
    if (player.move.shoot && bullet_count + WAVE_BULLET_MAX <= MAX_BULLETS && shoot_interval >= SHOOT_INTERVAL) {
    consumeMagicpoint(player.bullet_type);
    if (!player.move.shoot) return;  // MP不足でキャンセルされたら以降スキップ
        float base_angle = -MY_PI / 2;  // 真上（270度）
        float spread = MY_PI / 12;       // 扇の広がり（±11.25度）
    for (int i = -2; i <= 2; i++) {
        float angle = base_angle + i * spread;

            Bullet* b = &bullets[bullet_count++];
            b->x = player.x + player.width / 2 - 12;
            b->y = player.y;
            b->width = 25;
            b->height = 25;
            b->speed = 3;
            b->angle = angle;
            b->texture = bullets->texture;
        }
        shoot_interval = 0;
    } else {
        shoot_interval++;
    }
    for (int i = 0; i < bullet_count; i++) {
        bullets[i].x += cos(bullets[i].angle) * bullets[i].speed;
        bullets[i].y += sin(bullets[i].angle) * bullets[i].speed;

        if (bullets[i].y < -bullets[i].height || bullets[i].x < -bullets[i].width || bullets[i].x > WD_Width) {
            // 画面外に出たら削除
            for (int j = i; j < bullet_count - 1; j++) {
                bullets[j] = bullets[j + 1];
            }
            bullet_count--;
            i--;
        }
    }
}


void enemyShootBullets() {
    for (int i = 0; i < MAX_ENEMY; i++) {
        Enemy* e = &enemiy_crows[i];

        if (e->cooldown_timer > 0) {
            e->cooldown_timer--;
            continue;
        }

        if (e->shoot_timer > 0) {
            e->shoot_timer--;
            continue;
        }

        if (e->health <= 0) {
            e->health = 0;
            continue;
        }
        if (enemy_bullet_count < MAX_BULLETS) {
            Bullet* b = &enemy_bullets[enemy_bullet_count++];
            b->x = e->x + e->width / 2 - 5;
            b->y = e->y + e->height;
            b->width = 20;
            b->height = 20;
            b->speed = 1;
            b->angle = MY_PI / 2;  // 真下に発射
            b->texture = enemy_bullets->texture;
        }

        e->shoot_count++;

        if (e->shoot_count >= 3) {
            e->shoot_count = 0;
            e->cooldown_timer = 180; // 60フレーム = 約1秒の間隔
        } else {
            e->shoot_timer = 10; // 10フレームごとに1発
        }
    }

    //弾を打つ処理
    for (int i = 0; i < enemy_bullet_count; i++) {
        enemy_bullets[i].x += cos(enemy_bullets[i].angle) * enemy_bullets[i].speed;
        enemy_bullets[i].y += sin(enemy_bullets[i].angle) * enemy_bullets[i].speed;

        if (enemy_bullets[i].y > PLAY_WD_Height) {
            // 画面外なら削除
            for (int j = i; j < enemy_bullet_count - 1; j++) {
                enemy_bullets[j] = enemy_bullets[j + 1];
            }
            enemy_bullet_count--;
            i--;
        }
    }
}