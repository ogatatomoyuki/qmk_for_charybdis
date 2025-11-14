#include QMK_KEYBOARD_H

// ── Layers ─────────────────────────────────────────────
enum layers {
    _BASE = 0,
    _NAV,        // 1: Navigation / Edit
    _MOUSE,      // 2: Mouse / Wheel
    _NUMSYM,     // 3: Numbers / Symbols
};

// ── Convenience macros ─────────────────────────────────
#define LCTL_Z   LCTL_T(KC_Z)
#define LSFT_X   LSFT_T(KC_X)
#define LALT_C   LALT_T(KC_C)
#define LGUI_V   LGUI_T(KC_V)
#define RSH_ENT  RSFT_T(KC_ENT)

// 親指LT（Tapで言語切替、Holdでレイヤ）
#define LT1_LNG2 LT(_NAV,    KC_LNG2)
#define LT2_LNG1 LT(_MOUSE,  KC_LNG1)
#define LT3_BSPC LT(_NUMSYM, KC_BSPC)

// ── Keymaps ────────────────────────────────────────────
// LAYOUT_charybdis_3x5: 左3段×5列(15) + 右3段×5列(15) + 親指(合計5) = 35 キー
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Layer 0: Base
 * Q   W   E   R   T      |   Y   U   I   O   P
 * A   S   D   F   G      |   H   J   K   L   -
 * CtZ SfX AlC GuV  G     |   N   M   ,   .  RSft(Ent)
 *   LT1   LGUI_SPC  LT2  |  LT3   ___
 */
[_BASE] = LAYOUT_charybdis_3x5(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,     KC_MINS,
    LCTL_Z,  LSFT_X,  LALT_C,  LGUI_V,  KC_G,            KC_N,    KC_M,    KC_COMM, KC_DOT,   RSH_ENT,
    /* thumbs (5 keys total) */  LT1_LNG2, LGUI_T(KC_SPC), LT2_LNG1,        LT3_BSPC, KC_NO
),

/* Layer 1: Nav / Edit
 * Esc ___ ___ ___ F4     |  Home PgUp End ___ ___
 * LCt LSh LAl LGu ___    |  Left Down Up Right ___
 *  Z   X   C   V  ___    |  {    [    }    ]   ___
 *   ___     Space  Tab   |  ___   ___
 */
[_NAV] = LAYOUT_charybdis_3x5(
    KC_ESC,  KC_NO,   KC_NO,   KC_NO,   KC_F4,           KC_HOME, KC_PGUP, KC_END,  KC_NO,   KC_NO,
    KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, KC_NO,           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_NO,           KC_LCBR, KC_LBRC, KC_RCBR, KC_RBRC, KC_NO,
    /* thumbs */       KC_NO,  KC_SPC,  KC_TAB,           KC_NO,   KC_NO
),

/* Layer 2: Mouse / Wheel
 * ___ ___ ___ ___ ___    |  ___  WhUp WhDn WhRt Vol+
 * ___ ___ ___ ___ ___    |  M1   M2   M3   MS_U Vol-
 * ___ ___ ___ ___ ___    |  MS_L MS_D MS_R ___  ___
 *   ___     ___    ___   |  ___   ___
 */
[_MOUSE] = LAYOUT_charybdis_3x5(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,           KC_NO,   KC_WH_U, KC_WH_D, KC_WH_R, KC_VOLU,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,           KC_BTN1, KC_BTN2, KC_BTN3, KC_MS_U, KC_VOLD,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,           KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,   KC_NO,
    /* thumbs */       KC_NO,  KC_NO,   KC_NO,            KC_NO,   KC_NO
),

/* Layer 3: Numbers / Symbols
 * !1  @2  #3  $4  %5     |  ^6  &7  *8  (9  )0
 * ___ ___ ___ ___ ___    |  |   \   ~   ;   "
 * ___ ___ ___ ___ ___    |  <   ,   >   .   ?
 *   ___     ___    ___   |  ___   ___
 */
[_NUMSYM] = LAYOUT_charybdis_3x5(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,           KC_PIPE, KC_BSLS, KC_TILD, KC_SCLN, KC_DQUO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,           KC_LABK, KC_COMM, KC_RABK, KC_DOT,  KC_QUES,
    /* thumbs */       KC_NO,  KC_NO,   KC_NO,            KC_NO,   KC_NO
),
};


// ───────────────────────────────────────────────
// Per-key hooks
// - Z / X / C の Mod-Tap → Tap 寄り（今まで通り）
// - すべての Layer-Tap (LT) → Hold を強めてレイヤーを素早く・確実に上げる
// ───────────────────────────────────────────────

// 既に上の方で定義しているはずですが、念のため保険
#ifndef LCTL_Z
#    define LCTL_Z LCTL_T(KC_Z)
#endif
#ifndef LSFT_X
#    define LSFT_X LSFT_T(KC_X)
#endif
#ifndef LALT_C
#    define LALT_C LALT_T(KC_C)
#endif

// 親指の Layer-Tap キー（あなたのレイアウト）
#ifndef LT1_LNG2
#    define LT1_LNG2 LT(_NAV, KC_LNG2)
#endif
#ifndef LT2_LNG1
#    define LT2_LNG1 LT(_MOUSE, KC_LNG1)
#endif
#ifndef LT3_BSPC
#    define LT3_BSPC LT(_NUMSYM, KC_BSPC)
#endif

// Mod-Tap から Tap側のキーコードを取り出す（GET_TAP_KCを使わない安全版）
static inline uint16_t tap_keycode_from_modtap(uint16_t keycode) {
    if ((keycode & QK_MOD_TAP) == QK_MOD_TAP) {
        return keycode & 0xFF;   // 下位8bitが Tap
    }
    return KC_NO;
}

// Z / X / C の Mod-Tap 判定
static inline bool is_ZXC_modtap(uint16_t keycode) {
    if (keycode == LCTL_Z || keycode == LSFT_X || keycode == LALT_C) {
        return true;
    }
    uint16_t tapkc = tap_keycode_from_modtap(keycode);
    return (tapkc == KC_Z || tapkc == KC_X || tapkc == KC_C);
}

// すべての Layer-Tap 判定（親指LT + それ以外のLTも含める）
static inline bool is_layer_tap_key(uint16_t keycode) {
    if (keycode == LT1_LNG2 || keycode == LT2_LNG1 || keycode == LT3_BSPC) {
        return true;
    }
    // 一般的な LT() マクロ（QK_LAYER_TAP）も拾う
    return ((keycode & QK_LAYER_TAP) == QK_LAYER_TAP);
}

/* 1) TAPPING_TERM: Z/X/C →長め（Tap優先）、Layer-Tap →短め（Hold優先） */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    if (is_ZXC_modtap(keycode)) {
        return 220;        // 既存設定：Tap落ち防止（必要なら今使っている値に合わせてOK）
    }
    if (is_layer_tap_key(keycode)) {
        return 120;        // Layer-Tap は素早く Hold 判定にする
    }
    return TAPPING_TERM;   // その他はグローバル設定
}

/* 2) HOLD_ON_OTHER_KEY_PRESS: Layer-Tap だけ「次キーで即Hold確定」にする */
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    if (is_ZXC_modtap(keycode)) {
        // Z/X/Cは今まで通り Tap 寄りの挙動を維持したければ false
        return false;
    }
    if (is_layer_tap_key(keycode)) {
        // Layer-Tap: 次のキーを押した瞬間に Hold 確定 → レイヤーがすぐ上がる
        return true;
    }
    return true;   // その他はグローバルの挙動（おそらく true 相当）
}

/* 3) PERMISSIVE_HOLD: Layer-Tap だけ Hold 優先 */
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    if (is_ZXC_modtap(keycode)) {
        // Z/X/C は Tap優先なので false
        return false;
    }
    if (is_layer_tap_key(keycode)) {
        // Layer-Tap は Hold 優先 → ローリングでもレイヤーが上がりやすい
        return true;
    }
    return true;   // その他はグローバルの挙動
}

/* 4) TAPPING_FORCE_HOLD: Layer-Tap だけ ON
   → 他のキーを巻き込んだら、Tap(KC_LANG1/2, BSPC)には戻らないようにする */
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    if (is_ZXC_modtap(keycode)) {
        // Z/X/C は他キーを巻き込んでも Tap に落としたいので false
        return false;
    }
    if (is_layer_tap_key(keycode)) {
        // Layer-Tap は一度コンボに使われたら、確実にレイヤーキーとして動いてほしい
        return true;
    }
    return false;  // その他はグローバル（未定義=OFF）で問題ない
}



