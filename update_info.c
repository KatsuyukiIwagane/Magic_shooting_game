#include "system.h"

float shoot_timer = 0; // 弾を撃った回数
double current_time = 0.0;
StageEvent stage_events[MAX_STAGE_EVENTS];
int stage_event_count = 0; 

void UpdateOblects(double deltaTime) {
    // オブジェクトの更新処理をここに実装
    // 敵の位置更新、プレイヤーの状態更新など
    UpdatePlayer(deltaTime);
    UpdateEnemies(deltaTime);
    UpdateBullets(deltaTime);
    UpdateUI(deltaTime);
    UpdateSubUI(deltaTime); // サブUIの更新
    UpdateBoss(deltaTime); // ボスの更新
}


void UpdatePlayer(double deltaTime) {
    //プレイエリア内のみでプレイヤーは移動可能
    if (player.move.up && player.y > 0) 
        player.y -= player.speed * deltaTime; // 上に移動
    if (player.move.down && player.y < PLAY_WD_Height - player.height) 
        player.y += player.speed * deltaTime; // 下に移動
    if (player.move.left && player.x > 0) 
        player.x -= player.speed * deltaTime; // 左に移動
    if (player.move.right && player.x < PLAY_WD_Width - player.width) 
        player.x += player.speed * deltaTime; // 右に移動
}

void UpdateEnemies(double deltaTime) {
    // 敵の更新処理をここに実装
    // 敵の位置や状態の更新
    //仮置きTODO: まともな移動処理にしてね

    for (int i = 0; i < MAX_ENEMY; i++) {
        if (enemiy_crows[i].health <= 0) continue;

        enemiy_crows[i].x += enemiy_crows[i].direction * enemiy_crows[i].speed * deltaTime;
        enemiy_crows[i].y += enemiy_crows[i].speed * deltaTime;

        //完成版ではKILL
        if (enemiy_crows[i].y > PLAY_WD_Height){
            enemiy_crows[i].health = 0;
            enemiy_crows[i].x = -999;
            enemiy_crows[i].y = -999;
            enemiy_crows[i].cooldown_timer = 0;
            enemiy_crows[i].shoot_timer = 0;
            enemiy_crows[i].shoot_count = 0;
            enemiy_crows[i].direction = 1; // 方向を初期化
            continue; // 画面外に出た敵は更新しない
        }

        // 画面の端に当たったら反転
        if (enemiy_crows[i].x <= 0 || enemiy_crows[i].x + enemiy_crows[i].width >= PLAY_WD_Width)
            enemiy_crows[i].direction *= -1;
            
    }
}

void UpdateBullets(double deltaTime) {
    switch (player.bullet_type) {
    case BULLET_NOMAL:
        shootNomalBullet(deltaTime);
        break;
    case BULLET_WAVE:
        shootWaveBullet(deltaTime);
        break;
    default:
        break;
    }
    HitEnemy(); //敵に弾が当たったかどうかチェック
    HitBoss(); // ボスに弾が当たったかどうかをチェック

    //敵の弾打ち処理
    enemyShootBullets(deltaTime);

    HitPlayer();
}

void UpdateStage(double deltaTime) {
    // 経過時間を加算
    current_time += deltaTime;

    // 時間ベースでイベントを処理
    while (stage_event_count > 0 && stage_events[0].time_sec <= current_time) {
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
                enemiy_crows[i].direction = rand() % 2 == 0 ? 1 : -1;
                enemiy_crows[i].shoot_timer = 0;
                enemiy_crows[i].shoot_count = 0;
                enemiy_crows[i].cooldown_timer = 0;
                spawned = true;
                break;
            }
        }

        if (!spawned) {
            printf("警告: 敵スロット不足で出現できません (time: %.2f 秒)\n", ev.time_sec);
        }

        // イベントを前詰め
        for (int i = 1; i < stage_event_count; i++) {
            stage_events[i - 1] = stage_events[i];
        }
        stage_event_count--;
    }
}

void UpdateBoss(double deltaTime) {
    if (!boss_appear) return; // ボスが出現していない場合は何もしない

    BossAction(deltaTime); // ボスの行動を更新
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