#include "system.h"

int shoot_interval = 0; // 弾を撃った回数
void UpdateOblects() {
    // オブジェクトの更新処理をここに実装
    // 敵の位置更新、プレイヤーの状態更新など
    UpdatePlayer();
    UpdateEnemies();
    UpdateBullets();
    UpdateUI();
    UpdateSubUI(); // サブUIの更新
}


void UpdatePlayer() {
    //プレイエリア内のみでプレイヤーは移動可能
    if (player.move.up && player.y > 0) 
        player.y -= player.speed; // 上に移動
    if (player.move.down && player.y < PLAY_WD_Height - player.height) 
        player.y += player.speed; // 下に移動
    if (player.move.left && player.x > 0) 
        player.x -= player.speed; // 左に移動
    if (player.move.right && player.x < PLAY_WD_Width - player.width) 
        player.x += player.speed; // 右に移動
}

void UpdateEnemies() {
    // 敵の更新処理をここに実装
    // 敵の位置や状態の更新
    //仮置きTODO: まともな移動処理にしてね

    for (int i = 0; i < MAX_ENEMY; i++) {
        if (enemiy_crows[i].health <= 0) continue;

        enemiy_crows[i].x += enemiy_crows[i].direction * enemiy_crows[i].speed;
        enemiy_crows[i].y += enemiy_crows[i].speed;

        //完成版ではKILL
        if (enemiy_crows[i].y > PLAY_WD_Height)
            enemiy_crows[i].health = 0; // 画面外に出たら敵を消す

        // 画面の端に当たったら反転
        if (enemiy_crows[i].x <= 0 || enemiy_crows[i].x + enemiy_crows[i].width >= PLAY_WD_Width)
            enemiy_crows[i].direction *= -1;
            
    }
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
    HitEnemy(); //敵に弾が当たったかどうかチェック
    HitBoss(); // ボスに弾が当たったかどうかをチェック

    //敵の弾打ち処理
    enemyShootBullets();

    HitPlayer();
}

void UpdateStage() {
    while (stage_event_count > 0 && stage_events[0].frame <= current_frame) {
        StageEvent ev = stage_events[0];

        bool spawned = false;
        for (int i = 0; i < MAX_ENEMY; i++) {
            if (enemiy_crows[i].health <= 0) {
                enemiy_crows[i].x = ev.x;
                enemiy_crows[i].y = ev.y;
                enemiy_crows[i].health = ENEMY_HEALTH;
                enemiy_crows[i].width = ENEMY_WIDTH;
                enemiy_crows[i].height = ENEMY_HEIGHT;
                enemiy_crows[i].speed = ENEMY_BASE_SPEED;
                enemiy_crows[i].texture = enemy_textures[ev.type];
                enemiy_crows[i].direction = rand() % 2 == 0 ? 1 : -1; // ランダムな方向
                enemiy_crows[i].shoot_timer = 0;
                enemiy_crows[i].shoot_count = 0;
                enemiy_crows[i].cooldown_timer = 0;
                spawned = true;
                break;
            }
        }

        // 敵を出せなかった（MAX_ENEMY 全部埋まってた）→警告だけ出す
        if (!spawned) {
            printf("警告: 敵スロット不足で出現できません (frame: %d)\n", ev.frame);
        }

        // イベントを前詰め
        for (int i = 1; i < stage_event_count; i++) {
            stage_events[i - 1] = stage_events[i];
        }
        stage_event_count--;
    }

    current_frame++;
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