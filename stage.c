#include "system.h"

void LoadStageScript(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        PrintError("ステージスクリプトが開けません");
        return;
    }

    char line[128];
    fgets(line, sizeof(line), fp); // ヘッダスキップ

    stage_event_count = 0;
    while (fgets(line, sizeof(line), fp)) {
        double time;
        int x, y;
        char type_str[32];
        sscanf(line, "%lf,%[^,],%d,%d", &time, type_str, &x, &y);

        EnemyType type = ENEMY_CROW; // TODO: 他の敵にも対応

        stage_events[stage_event_count++] = (StageEvent){time, type, x, y};
    }

    fclose(fp);
}