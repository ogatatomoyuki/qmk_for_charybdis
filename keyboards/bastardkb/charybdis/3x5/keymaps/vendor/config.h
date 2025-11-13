#pragma once

/* ===== Charybdis向け Tap/Hold 調整（タップ寄りバランス） =====
   目的: Atreusでは快適だった超短TTを緩め、Tap取りこぼしを解消
*/

/* 基本のTap/Hold境界 */
#define TAPPING_TERM 100              // 75ms→大幅延長：Tap判定の余裕を作る

/* Hold寄り/ショートカット安定化 */
#define PERMISSIVE_HOLD               // 先に別キーでHold寄り（ローリング入力の安定）
#define HOLD_ON_OTHER_KEY_PRESS       // 次キーで即Hold確定（ショトカ強め・必要なら外してTap寄りへ）

/* Tap救済（離しが遅れてもTapにする） */
//#define RETRO_TAPPING                 // Atreus比で“遅離し”が増える想定→救済ON

/* 連打・超短タップの扱い */
#define QUICK_TAP_TERM 80            // 65→100ms：素早い単打は確実にTapへ
#define TAP_CODE_DELAY 10             // tap_codeの押下-離上間隔

/* Shift(MT)の取りこぼし対策 */
#define TAP_HOLD_CAPS_DELAY 60        // 15→60ms：大文字・記号抜けを抑制

/* 複数Mod同時（Ctrl+Shift+Z等）の安定化 */
#define CHORDAL_HOLD                  // 複合修飾でHold優先に

/* 不使用設定（明示） */
#define TAPPING_TOGGLE 0              // 連打でトグル無効
/* Flow Tap = 0（定義不要） */

/* ─ ヒント ─
   ・まだTapが出にくければ: TAPPING_TERMを +10〜20ms, あるいは HOLD_ON_OTHER_KEY_PRESS をコメントアウト
   ・ショートカットが落ちるなら: QUICK_TAP_TERM を -5〜10ms, または TAPPING_TERM を +10ms
*/

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
