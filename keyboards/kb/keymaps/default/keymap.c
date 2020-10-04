#include "kb.h"
#include "analog.h"

enum planck_layers {
  _BASE = 0,
  _FAST,
  _PLAY,
  _REW,
  _KEY4,
  _ENC,
  _SIDE,
  _SPEED
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = KEYMAP(
		LT(_REW, KC_MPRV), LT(_PLAY, KC_MPLY), LT(_FAST, KC_MNXT), LT(_KEY4, KC_WAKE), LT(_ENC, KC_MUTE)),

	[_FAST] = KEYMAP(
		KC_TRNS, KC_CALC, KC_TRNS, KC_PWR, KC_TRNS),

	[_PLAY] = KEYMAP(
		LT(_SPEED, KC_PGDN), MO(_SIDE), KC_PGUP, KC_SLEP, DF(_PLAY)),

	[_REW] = KEYMAP(
		KC_WBAK, KC_WREF, KC_TRNS, KC_WFWD, KC_TRNS),

	[_KEY4] = KEYMAP(
		RGB_RMOD, RGB_TOG, RGB_MOD, KC_TRNS, KC_TRNS),

	[_ENC] = KEYMAP(
		RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_SIDE] = KEYMAP(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(_BASE)),

    [_SPEED] = KEYMAP(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
    	switch(biton32(layer_state)) {
	    case _REW:
        	if (clockwise) {
	            rgblight_increase_hue();
	        } else {
	            rgblight_decrease_hue();
	        }
	       break;
	   case _PLAY:
        	if (clockwise) {
	            tap_code16(KC_WH_D);
	        } else {
	            tap_code16(KC_WH_U);
	        }
	       break;
	    case _FAST:
        	if (clockwise) {
	            rgblight_increase_sat();
	        } else {
	            rgblight_decrease_sat();
	        }
	       break;
	   	case _KEY4:
        	if (clockwise) {
	            rgblight_increase_val();
	        } else {
	            rgblight_decrease_val();
	        }
	       break;
        case _SIDE:
            if (clockwise) {
                tap_code16(KC_WH_R);
            } else {
                tap_code16(KC_WH_L);
            }
            break;
        case _SPEED:
            if (clockwise) {
                rgblight_increase_speed();
            } else {
                rgblight_decrease_speed();
            }
           break;
        default:
            if (clockwise) {
                tap_code16(KC_AUDIO_VOL_UP);
            } else {
                tap_code16(KC_AUDIO_VOL_DOWN);
            }
            break;
        }
    }
}

uint8_t divisor = 0;

void slider(void) {
    if (divisor++) { // only run the slider function 1/256 times it's called
        return;
    }
    rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), analogReadPin(SLIDER_PIN)>>2);
}

void matrix_scan_user(void) {
    slider();
}