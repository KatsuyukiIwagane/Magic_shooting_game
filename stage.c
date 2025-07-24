#include "system.h"

StageEvent stage_events[MAX_STAGE_EVENTS];  // 例: ステージイベント最大256個まで
int stage_event_count = 0;
int current_frame = 0;

void LoadStageScript(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        PrintError("ステージスクリプトが開けません");
        return;
    }

    char line[128];
    fgets(line, sizeof(line), fp); // ヘッダ行スキップ

    stage_event_count = 0;
    while (fgets(line, sizeof(line), fp)) {
        int frame, x, y;
        char type_str[32];
        sscanf(line, "%d,%[^,],%d,%d", &frame, type_str, &x, &y);

        EnemyType type = ENEMY_CROW; // TODO: 他の敵にも対応
        stage_events[stage_event_count++] = (StageEvent){frame, type, x, y};
    }
    fclose(fp);
}
