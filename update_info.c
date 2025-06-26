#include "system.h"

int shoot_interval = 0; // 弾を撃った回数
void UpdateOblects() {
    // オブジェクトの更新処理をここに実装
    // 例: 敵の位置更新、プレイヤーの状態更新など
    // 現在は何も実装していないが、必要に応じて追加すること
    UpdatePlayer();
    UpdateEnemies();
    UpdateBullets();
    UpdateUI();
    UpdateSubUI(); // サブUIの更新
}


void UpdatePlayer() {
    if (player.move.up) 
        player.y -= player.speed; // 上に移動
    if (player.move.down) 
        player.y += player.speed; // 下に移動
    if (player.move.left) 
        player.x -= player.speed; // 左に移動
    if (player.move.right) 
        player.x += player.speed; // 右に移動
}

void UpdateEnemies() {
    // 敵の更新処理をここに実装
    // 例: 敵の位置や状態の更新
}

void UpdateBullets() {
    if (player.move.shoot && bullet_count < MAX_BULLETS && shoot_interval % SHOOT_INTERVAL == 0) {
        // 弾を撃つ処理
        nomal_bullets[bullet_count].x = player.x + player.width / 2 - nomal_bullets[bullet_count].width / 2;
        nomal_bullets[bullet_count].y = player.y;
        bullet_count++;
        shoot_interval = 1; // 弾を撃ったので間隔をリセット
    }
    else if (player.move.shoot && shoot_interval % SHOOT_INTERVAL != 0) {
        shoot_interval++; // 弾を撃つ間隔を調整
    }
    for (int i = 0; i < bullet_count; i++) {
        nomal_bullets[i].y -= nomal_bullets[i].speed; // 弾を上に移動
        if (nomal_bullets[i].y < 0) {
            // 画面外に出た弾は削除
            for (int j = i; j < bullet_count - 1; j++) {
                nomal_bullets[j] = nomal_bullets[j + 1];
            }
            bullet_count--;
            i--; // インデックスを調整
        }
    }
    HitBoss(); // ボスに弾が当たったかどうかをチェック
}

void UpdateUI() {
    // UIの更新処理をここに実装
    // 例: スコアやライフの表示更新など
    // 現在は何も実装していないが、必要に応じて追加すること
}

void UpdateSubUI() {
    // サブUIの更新処理をここに実装
    // 例: プレイヤーのライフや魔力の表示更新など
    // 現在は何も実装していないが、必要に応じて追加すること
}