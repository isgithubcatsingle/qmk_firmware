/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

#include "bongo.h" 
#include "tako.h" 


char wpm_str[10];


// Tap Dance - declarations -----------------------------------------------------------------------------------------------------
enum {
    SCAPS,  //caps lockc
    QDQUO,  //quotation 
    TESC,   //escape
    // REND,   //RIGHT END
    NUM,    //tg layer 1 
};

// //Triple Dance END - need to come before definition
// void dance_right (qk_tap_dance_state_t *state, void *user_data) {
//     if (state->count == 1) {
//         tap_code(KC_RIGHT);
//     // } else if (state->count == 2) {
//     //     tap_code (KC_RIGHT);
//     } else if (state->count == 3) {
//         tap_code(KC_END);                                
//     } else {
//         reset_tap_dance (state);
//     }
// }

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [SCAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [QDQUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [TESC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),
    // [REND] = ACTION_TAP_DANCE_FN (dance_right),
    [NUM] = ACTION_TAP_DANCE_DOUBLE(MO(1), MO(1)),
};


//keymap ---------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,TD(QDQUO),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    TD(TESC),     KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,   KC_O,   KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    TD(SCAPS),    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL,  MO(1), KC_BSPC,     KC_SPC,  MO(2), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_UP,  KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    TD(SCAPS), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_DOWN, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+---***--|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL, KC_TRNS, KC_SPC,     KC_SPC, XXXXXXX, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,  KC_GRV, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    TD(SCAPS), XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, KC_RGUI,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, TG(3), KC_BSPC,     KC_SPC, KC_TRNS, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    TD(SCAPS), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      RGB_M_P, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_LCTL,    TG(3), KC_BSPC,     KC_SPC, XXXXXXX, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )

};

//OLED---------------------------------------------------------------------------------------------------------------------

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_270;  // flips the display 180 degrees 
  }
  else {
    return OLED_ROTATION_270;
        }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("\n\nLAYER\n"), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Deflt     "), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Numbr  *  "), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Symbl *** "), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Settn*****"), false);
            break;
    }
}

void oled_render_wpm(void) {
    oled_write_P(PSTR("\n|WPM| "), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
}

void oled_caps(void) {
    led_t led_state = host_keyboard_led_state();  // caps lock stuff, prints CAPS on new line if caps led is on
    oled_write_P(led_state.caps_lock ? PSTR("\n CAP ") : PSTR("\n  "), false);
   }


bool oled_task_user(void) { 

if (is_keyboard_master()) {
    oled_write_P(PSTR("\n\nCORNERev.2"), false);
    oled_write_P(PSTR("\ncolmk\n"), false);
    oled_caps();
    draw_tako();
     } 
     else {
    oled_render_layer_state();
    oled_render_wpm();          
    draw_bongo(true);
     }

    return false;
}




#endif 

// encoder------------------------------------------------------------------------------------------
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint16_t index, bool clockwise) {
    if (index == 0) {
        // copy paste
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    }
    else if (index == 1) {
        // 
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
     return false;
}
#endif // ENCODER_ENABLE------------------------------------------------------------------------------------------



//combo------------------------------------------------------------------------------------------

enum combo_events {
    worddel
};

const uint16_t PROGMEM leftspace[] = {KC_V, KC_BSPC, COMBO_END}; //somehow whatever is in first dont seem to work
const uint16_t PROGMEM leftenter[] = {KC_D, KC_BSPC, COMBO_END};

const uint16_t PROGMEM copy[] = {KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM paste[] = {KC_D, KC_V, COMBO_END};
const uint16_t PROGMEM cut[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM undo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM redo[] = {KC_Z, KC_R, COMBO_END};
const uint16_t PROGMEM save[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM find[] = {KC_F, KC_P, COMBO_END};

const uint16_t PROGMEM worddelete[] = {KC_BSPC, KC_SPC, COMBO_END};



combo_t key_combos[COMBO_COUNT] = {
    COMBO(leftspace, KC_SPC), 
    COMBO(leftenter, KC_ENT), 

    COMBO(copy, LCTL(KC_C)), 
    COMBO(paste, LCTL(KC_V)), 
    COMBO(cut, LCTL(KC_X)), 
    COMBO(undo, LCTL(KC_Z)), 
    COMBO(redo, LCTL(KC_Y)), 
    COMBO(save, LCTL(KC_S)), 
    COMBO(find, LCTL(KC_F)), 



  [worddel] = COMBO_ACTION(worddelete)
};

/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    // case EM_EMAIL:
    //   if (pressed) {
    //     SEND_STRING("john.doe@example.com");
    //   }
    //   break;
    case worddel:
      if (pressed) {
        tap_code16(LCTL(KC_LEFT));
        tap_code16(LCTL(LSFT(KC_RIGHT)));
        tap_code16(KC_BSPC);
      }
      break;
  }
}

//------------------------------------------------------------------------------------------

// Macro --------repeating keycode script (custum keycode) that starts a behavior with keypress and repeats until keypress


//  bool spam_enter;
// uint16_t spam_timer = false;
// uint16_t spam_interval = 1000; // (1000ms == 1s)

// enum custom_keycodes {
//   KC_EEEE = SAFE_RANGE
// };

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//   case KC_EEEE: // Toggle's if we hit "ENTER" or "BACKSPACE" to input macros
//     if (record->event.pressed) { 
//       spam_enter ^= 1; 
//       spam_timer = timer_read();
//     }
//     return false;
//   }
//   return true;
// } 

// void matrix_scan_user(void) {
//   if (spam_enter && timer_elapsed(spam_timer) >= spam_interval) {
//      spam_timer = timer_read();
//      SEND_STRING(SS_TAP(X_ENTER));
//   }
// }
