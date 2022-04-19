/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SPLIT_TRANSPORT_MIRROR  //need this for below
// #define SPLIT_WPM_ENABLE
// #define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_OLED_ENABLE 

//#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200

#define COMBO_STRICT_TIMER

#ifdef RGBLIGHT_ENABLE
    #undef RGBLIGHT_ANIMATIONS
    #undef RGBLIGHT_EFFECT_BREATHING
    #undef RGBLIGHT_EFFECT_RAINBOW_MOOD
    #undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #undef RGBLIGHT_EFFECT_SNAKE
    #undef RGBLIGHT_EFFECT_KNIGHT
    #undef RGBLIGHT_EFFECT_CHRISTMAS
    #undef RGBLIGHT_EFFECT_STATIC_GRADIENT
    #undef RGBLIGHT_EFFECT_RGB_TEST
    #undef RGBLIGHT_EFFECT_ALTERNATING
    #undef RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 10
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
#define OLED_BRIGHTNESS 15
#define OLED_TIMEOUT 60000

#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { B5 }

#define COMBO_COUNT 10



//reducing size

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT //layer limit to 8

#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT

#define TAPPING_FORCE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

#define WPM_SAMPLE_SECONDS 2