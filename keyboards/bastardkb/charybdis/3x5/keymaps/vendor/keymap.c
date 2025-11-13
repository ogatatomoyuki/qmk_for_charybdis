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

// --- あなたのマクロ定義に合わせて（未定義ならここで定義） ---
#ifndef LCTL_Z
#    define LCTL_Z LCTL_T(KC_Z)   // Tap=Z / Hold=Ctrl
#endif
#ifndef LSFT_X
#    define LSFT_X LSFT_T(KC_X)   // Tap=X / Hold=Shift
#endif
#ifndef LALT_C
#    define LALT_C LALT_T(KC_C)   // Tap=C / Hold=Alt
#endif

// 対象キー（Mod-Tap かつ Tap側が Z/X/C）
static inline bool is_ZXCV_modtap(uint16_t keycode) {
    if (keycode == LCTL_Z || keycode == LSFT_X || keycode == LALT_C) return true;
    return (IS_QK_MOD_TAP(keycode) &&
           (GET_TAP_KC(keycode) == KC_Z ||
            GET_TAP_KC(keycode) == KC_X ||
            GET_TAP_KC(keycode) == KC_C));
}

/* 1) Z/X/C だけ TAPPING_TERM を長め（Tapしやすく） */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    if (is_ZXCV_modtap(keycode)) return 185;   // 目安: 175〜195ms（取りこぼすなら上げる）
    return TAPPING_TERM;
}

/* 2) Z/X/C だけ “次キーで即Hold確定” を無効（Tap維持） */
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    if (is_ZXCV_modtap(keycode)) return false;
    return true; // グローバル既定
}

/* 3) Z/X/C だけ Permissive Hold を無効（Hold寄せ弱め） */
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    if (is_ZXCV_modtap(keycode)) return false;
    return true;
}

/* 4) Z/X/C だけ 割り込みでもTapを維持（⌘/Ctrlを途中で押してもTapが崩れにくい） */
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    if (is_ZXCV_modtap(keycode)) return true;
    return false;
}

/* 5) Z/X/C だけ TAPPING_FORCE_HOLD を無効（他キー後に離してもTapを許容） */
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    if (is_ZXCV_modtap(keycode)) return false;
    return true;
}

