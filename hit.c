#include "system.h"


void HitBoss() {
    // ボスに弾が当たったかどうかをチェック
    for (int i = 0; i < bullet_count; i++) {
        if (bullets[i].x < black.x + black.width &&
            bullets[i].x + bullets[i].width > black.x &&
            bullets[i].y < black.y + black.height &&
            bullets[i].y + bullets[i].height > black.y) {
            // 弾がボスに当たった場合の処理
            black.health -= 1; // ボスのライフを減らす
            // 弾を削除
            for (int j = i; j < bullet_count - 1; j++) {
                bullets[j] = bullets[j + 1];
            }
            bullet_count--;
            i--; // インデックスを調整
        }
    }
    // ボスのライフが0以下になった場合の処理
    if (black.health <= 0) {
        // ボスを倒した場合の処理
        black.health = 0; // ライフを0に設定
        // ボスの画像を非表示にするなどの処理を追加
        boss_appear = false; // ボスが出現していない状態にする
        printf("Boss defeated!\n");
    }
}

void HitEnemy() {
    for (int i = 0; i < bullet_count; i++) {
        for (int j = 0; j < MAX_ENEMY; j++) {
            // すでに死んでる敵はスキップ
            if (enemiy_crows[j].health <= 0) continue;

            // 当たり判定
            if (bullets[i].x < enemiy_crows[j].x + enemiy_crows[j].width &&
                bullets[i].x + bullets[i].width > enemiy_crows[j].x &&
                bullets[i].y < enemiy_crows[j].y + enemiy_crows[j].height &&
                bullets[i].y + bullets[i].height > enemiy_crows[j].y) {
                
                // ライフ減少
                enemiy_crows[j].health--;

                if (enemiy_crows[j].health <= 0)
                    enemiy_crows[j].texture = NULL;

                // 弾を削除
                for (int k = i; k < bullet_count - 1; k++) {
                    bullets[k] = bullets[k + 1];
                }
                bullet_count--;
                i--; // 弾のインデックス調整
                break; // 同じ弾で複数体に当たらないよう抜ける
            }
        }
    }
}

void HitPlayer() {
    // プレイヤーの当たり判定中心6x6（中心3pxずつ広がる）
    int hitbox_size = 6;
    int px = player.x + player.width / 2 - hitbox_size / 2;
    int py = player.y + player.height / 2 - hitbox_size / 2;

    SDL_Rect player_hitbox = {
        px,
        py,
        hitbox_size,
        hitbox_size
    };

    for (int i = 0; i < enemy_bullet_count; i++) {
        SDL_Rect bullet_rect = {
            enemy_bullets[i].x,
            enemy_bullets[i].y,
            enemy_bullets[i].width,
            enemy_bullets[i].height
        };

        // 衝突判定
        if (SDL_HasIntersection(&player_hitbox, &bullet_rect)) {
            player.health--;

            // 敵弾を削除
            for (int j = i; j < enemy_bullet_count - 1; j++) {
                enemy_bullets[j] = enemy_bullets[j + 1];
            }
            enemy_bullet_count--;
            i--;  // 弾を1つ減らしたのでインデックスを戻す

            // プレイヤーのライフが0以下なら処理
            if (player.health <= 0) {
                player.health = 0;
                player.gameover = true;
                player.x = -990;
                player.y = -990;
            }
        }
    }
}