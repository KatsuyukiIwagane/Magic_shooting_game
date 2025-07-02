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
    switch (player.bullet_type) {
    case BULLET_NOMAL:
        shootNomalBullet();
        break;
    case BULLET_WAVE:
        shootWaveBullet();
        break;
    default:
        break;
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