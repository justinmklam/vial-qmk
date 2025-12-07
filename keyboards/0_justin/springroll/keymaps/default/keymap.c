// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
      * │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │
      * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
      * │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │
      * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
      * │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │
      * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
      * │Ctl│GUI│Bsp│Spc│Del│   │Ent│Alt│App│Ctl│
      * └───┴───┴───┴───┴───┘   └───┴───┴───┴───┘
      */
    [0] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_LCTL,          KC_BSPC, KC_SPC,  KC_DEL,           KC_ENT,  KC_RALT, KC_APP,  KC_RCTL
    )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default"), false);
            break;
        case 1:
            oled_write_P(PSTR("FN"), false);
            break;
        case 2:
            oled_write_P(PSTR("ADJ"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR(" NUM") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR(" CAP") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR(" SCR") : PSTR("    "), false);

    // WPM counter
    oled_write_P(PSTR("\nWPM: "), false);
#ifdef WPM_ENABLE
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
#else
    oled_write_P(PSTR("N/A"), false);
#endif

    return false;
}
#endif
