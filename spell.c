#include "system.h"

SpellInput current_spell = {"", 0};

SpellStatus spell_list[SPELL_COUNT] = {
    {"heal_hitpoints", false},
    {"elimination_enemies", false}
};

void HandleSpellInput(const SDL_Event* event){
    if (event->type == SDL_KEYDOWN) {
        SDL_Keycode key = event->key.keysym.sym;

        // バックスペース対応
        if (key == SDLK_BACKSPACE && current_spell.length > 0) {
            current_spell.length--;
            current_spell.buffer[current_spell.length] = '\0';
            return;
        }

        // アルファベット入力のみ受け付け
        if (current_spell.length < MAX_SPELL_LENGTH - 1 &&
            key >= SDLK_a && key <= SDLK_z) {
            current_spell.buffer[current_spell.length++] = (char)key;
            current_spell.buffer[current_spell.length] = '\0';
        }

        // スペル実行（Enter）
        if (key == SDLK_RETURN) {
            SpellType spell = MatchSpell(current_spell.buffer);
            ExecuteSpell(spell);

            // バッファをクリア
            current_spell.length = 0;
            current_spell.buffer[0] = '\0';
        }
    }
}

SpellType MatchSpell(const char* input) {
    if (strcmp(input, "healhitpoints") == 0) return SPELL_HEAL;
    if (strcmp(input, "eliminationenemies") == 0) return SPELL_ELIMINATION;
    return SPELL_NONE;
}

void ExecuteSpell(SpellType spell) {
    switch (spell) {
        case SPELL_HEAL:
                player.health += 1;
                spell_list[0].activated = true;
            break;

        case SPELL_ELIMINATION:
            for (int i = 0; i < MAX_ENEMY; i++) {
                if (enemiy_crows[i].health > 0) {
                    enemiy_crows[i].health = 0;
                    enemiy_crows[i].x = -999; // 画面外に移動
                    enemiy_crows[i].y = -999; // 画面外に移
                }
            }
            spell_list[1].activated = true;
            break;

        default:
            break;
    }
    current_spell.length = 0;
    current_spell.buffer[0] = '\0';
}