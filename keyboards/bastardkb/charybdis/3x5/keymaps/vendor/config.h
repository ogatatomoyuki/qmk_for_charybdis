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

/* per-key 調整を有効化（挙動は keymap.c 側で制御） */
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
