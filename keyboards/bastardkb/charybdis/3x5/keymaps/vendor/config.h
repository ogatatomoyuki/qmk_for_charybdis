/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 7
#endif // VIA_ENABLE

#ifndef __arm__
/* Disable unused features. */
#    define NO_ACTION_ONESHOT
#endif // __arm__

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE

#pragma once

/* --- Tap / Hold 判定まわり --- */
#define TAPPING_TERM 75                 // Tap/Hold の閾値(ms)
#define PERMISSIVE_HOLD                 // 先に別キーが押されたら Hold を優先
#define HOLD_ON_OTHER_KEY_PRESS         // MT押下中に次キーで即Hold確定
/* #define RETRO_TAPPING */             // OFF（救済Tapなし）

/* --- クイックタップ --- */
#define QUICK_TAP_TERM 65               // 超短タップは即Tap確定(ms)

/* --- tap_code 系 --- */
#define TAP_CODE_DELAY 15               // 押下-離上の間隔(ms)

/* --- Shift(MT) の取りこぼし対策 --- */
#define TAP_HOLD_CAPS_DELAY 15          // Shift-MTで大文字化に猶予(ms)

/* --- Tapping Toggle (TT) --- */
#define TAPPING_TOGGLE 0                // 無効化（0）
/* #define CHORDAL_HOLD */              // OFF（複数MT同時でも特別扱いなし）
/* Flow Tap: 0（デフォルト） -> 追加定義不要 */

