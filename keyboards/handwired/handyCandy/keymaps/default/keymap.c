/* Copyright 2018 Jack Humbert
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

#include "handyCandy.h"

enum layers {
  _BL = 0,
  _SL,
  _GM,
  _LeftS,
  _RightS,
  _RS
};

static uint8_t ctrl_tracker;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BL] = LAYOUT(
  KC_GESC,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_DEL, KC_BSPC,KC_P7,  KC_P8,  KC_P9,  KC_PAST, \
   KC_TAB,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_QUOT,   KC_ENT,    KC_P4,  KC_P5,  KC_P6,  KC_PMNS, \
     KC_LSPO,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT,  KC_RSPC, KC_UP,  KC_P1,  KC_P2,  KC_P3,  KC_PPLS, \
   CTL_T(KC_LBRC),KC_LGUI,KC_LALT,LT(_LeftS, KC_SPC), LT(_RightS, KC_SPC), KC_SCLN,LT(_RS,KC_RBRC),KC_LEFT,KC_DOWN,KC_RGHT,KC_P0,  KC_PDOT,KC_PENT ),

[_SL] = LAYOUT(
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_EQL, _______,_______,_______,_______,_______, \
   _______, _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_SCLN,   _______,   _______,_______,_______,_______, \
     _______,   _______,_______,_______,_______,_______,_______,_______,_______,_______,_______, _______, _______,_______,_______,_______, \
   _______,  _______,  _______,        _______,            _______,      _______, _______,_______,_______,_______,_______,_______,_______),

[_GM] = LAYOUT(
  _______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, _______,_______,_______,_______, \
   _______, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,      _______,   _______,_______,_______,_______, \
     _______,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_QUOT, _______, _______,_______,_______,_______, \
   _______,  _______,  _______,        _______,            _______,      _______, _______,_______,_______,_______,_______,_______,_______),


[_LeftS] = LAYOUT(
  DF(_BL),KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LBRC,KC_RBRC,KC_UNDS,KC_PLUS,KC_NLCK,_______,_______,KC_VOLU, \
   KC_CAPS, _______,_______,_______,_______,_______,_______,_______,_______,KC_COLN,KC_DQUO,   KC_PIPE,   _______,_______,_______,KC_VOLD, \
     _______,   _______,_______,_______,_______,_______,_______,_______,_______,_______,RSFT_T(KC_QUES), KC_PGUP, _______,_______,_______,KC_PEQL, \
   _______,  _______,  _______,        _______,            _______,      KC_APP,  _______,KC_HOME,KC_PGDN,KC_END, _______,_______,_______ ),

[_RightS] = LAYOUT(
  DF(_SL),KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, _______,_______,_______,_______, \
   _______, _______,_______,_______,_______,_______,_______,_______,_______,KC_SCLN,KC_QUOT,   KC_BSLS,   _______,_______,_______,_______, \
     _______,   _______,_______,_______,_______,_______,_______,_______,_______,_______,RSFT_T(KC_SLSH), _______, _______,_______,_______,_______, \
   _______,  _______,  _______,        KC_BSPC,            _______,      _______, _______,_______,_______,_______,_______,_______,_______),

[_RS] = LAYOUT(
  RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
   DF(_GM), _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,   _______,_______,_______,_______, \
     _______,   _______,_______,_______,_______,_______,_______,_______,_______,_______,_______, _______, _______,_______,_______,_______, \
   _______,  _______,  _______,        _______,            _______,      _______, _______,_______,_______,_______,_______,_______,_______),
};





bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (get_highest_layer(layer_state) == _LeftS) {
    if (record->event.pressed) {
      if (get_highest_layer(layer_state) != layer_switch_get_layer(record->event.key)) {
        SEND_STRING(SS_DOWN(X_LCTRL));
        ctrl_tracker++;
      }
      // when keycode MODCTRT is pressed
    } else {
      // when keycode MODCTRT is released
      if (get_highest_layer(layer_state) != layer_switch_get_layer(record->event.key)) {
        ctrl_tracker--;
        if (!ctrl_tracker){
          SEND_STRING(SS_UP(X_LCTRL));
        }
      }
    }
  }
  return true;
};

layer_state_t layer_state_set_user(layer_state_t state) {
  if (ctrl_tracker > 0) {
    SEND_STRING(SS_UP(X_LCTRL));
    ctrl_tracker = 0;
  }
  return state;
}