#include "kb.h"

enum planck_layers {
  _BASE,
  _FAST,
  _PLAY,
  _REW,
  _KEY4,
  _ENC,
  _SIDE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = KEYMAP(
		LT(_REW, KC_A), LT(_PLAY, KC_B), LT(_FAST, KC_C), LT(_KEY4, KC_D), LT(_ENC, KC_E))

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
    	if (clockwise) {
            tap_code16(KC_AUDIO_VOL_UP);
        } else {
            tap_code16(KC_AUDIO_VOL_DOWN);
        }
	    
    }
}