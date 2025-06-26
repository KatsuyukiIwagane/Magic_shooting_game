#include "system.h"

void UpdateOblects() {
    // オブジェクトの更新処理をここに実装
    // 例: 敵の位置更新、プレイヤーの状態更新など
    // 現在は何も実装していないが、必要に応じて追加すること
    UpdatePlayer();
    UpdateEnemies();
    UpdateBullets();
    UpdateUI();
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
    // 弾の更新処理をここに実装
    // 例: 弾の位置や状態の更新
}

void UpdateUI() {
    // UIの更新処理をここに実装
    // 例: スコアやライフの表示更新など
    // 現在は何も実装していないが、必要に応じて追加すること
}