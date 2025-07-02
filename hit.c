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