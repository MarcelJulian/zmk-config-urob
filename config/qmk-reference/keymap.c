// Copyright 2023 QMK Community
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// ---------- TAP DANCE ----------
#define ACTION_TAP_DANCE_FN_ADVANCED_USER(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, user_user_data) \
        { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = (void*)user_user_data, }

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum tap_dances {
    DOUBLE_DOT_COMMA,
    KEY_2HOLD_ENT_NUM_FUN,
    LAYER_LOCK_QWERTY,
    LAYER_LOCK_NAV,
    LAYER_LOCK_BUTTON,
    LAYER_LOCK_MEDIA,
    LAYER_LOCK_NUM,
    // LAYER_LOCK_SYM,
    LAYER_LOCK_FUN,
    LAYER_LOCK_QWERTY_TAP
};

typedef struct {
    int layer_code;
} td_layer_data_t;

typedef struct {
    uint16_t keycode;
    int layer_code_1;
    int layer_code_2;
} td_key_2hold_t;

// ---------- AUTO SHIFT ---------
// Retro shift needs this function to work
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    if(IS_RETRO(keycode)) return true;
    return false;
}

// ----------- GENERAL -----------
enum layers {
  _QWERTY,
  _NAV,
  _BUTTON,
  _MEDIA,
  _NUM,
//   _SYM,
  _FUN,
  _QWERTY_TAP
};

// -------- HOME ROW MODS --------
#define HGUI_A LGUI_T(KC_A)
#define HALT_S LALT_T(KC_S)
#define HCTL_D LCTL_T(KC_D)
#define HSFT_F LSFT_T(KC_F)
#define HSFT_J LSFT_T(KC_J)
#define HCTL_K LCTL_T(KC_K)
#define HALT_L LALT_T(KC_L)
#define HGUI_SCL LGUI_T(KC_SCLN)
#define HRAL_X RALT_T(KC_X)
#define HRAL_DOT RALT_T(KC_DOT)

// -------- LAYER TOGGLES --------
// #define LBTN_Z LT(_BUTTON,KC_Z)
// #define LBTN_SLS LT(_BUTTON,KC_SLSH)
#define LNF_ENT TD(KEY_2HOLD_ENT_NUM_FUN)
#define LNAV_SPC LT(_NAV,KC_SPC)
#define LMED_TAB LT(_MEDIA,KC_TAB)
#define LNUM_ENT LT(_NUM,KC_ENT)
// #define LNUM_BSP LT(_NUM,KC_BSPC)
#define LFUN_DEL LT(_FUN,KC_DEL)

// --------- USER MACROS ---------
#define UM_RDO LCTL(KC_Y)
#define UM_UND LCTL(KC_Z)
#define UM_CUT LCTL(KC_X)
#define UM_CPY LCTL(KC_C)
#define UM_PST LCTL(KC_V)

// --------- LAYER LOCK ----------
#define LCK_QWE TD(LAYER_LOCK_QWERTY)
#define LCK_NAV TD(LAYER_LOCK_NAV)
#define LCK_BTN TD(LAYER_LOCK_BUTTON)
#define LCK_MED TD(LAYER_LOCK_MEDIA)
#define LCK_NUM TD(LAYER_LOCK_NUM)
// #define LCK_SYM TD(LAYER_LOCK_SYM)
#define LCK_FUN TD(LAYER_LOCK_FUN)
#define LCK_TAP TD(LAYER_LOCK_QWERTY_TAP)

// ------------ OTHERS -----------
#define DBL_D_C TD(DOUBLE_DOT_COMMA)
#define MIC_TOGG KC_F24

// Main keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,             KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,             KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MINS,
        KC_LSFT , KC_A   , HALT_S , HCTL_D , HSFT_F , KC_G   ,             KC_H   , HSFT_J , HCTL_K , HALT_L ,HGUI_SCL, KC_QUOT,
        KC_LCTL , KC_Z   , HRAL_X , KC_C   , KC_V   , KC_B   ,             KC_N   , KC_M   , KC_COMM,HRAL_DOT, KC_SLSH, KC_BSLS,
                          MIC_TOGG, KC_LGUI,                                                 KC_GRV , KC_EQL ,
                                         LNF_ENT,LNAV_SPC,                     KC_BSPC ,LNUM_ENT,
                                            SH_MON ,LMED_TAB,             LFUN_DEL, SH_MON ,
                                            KC_ESC , KC_BSPC,              QK_BOOT,MIC_TOGG
    ),

    [_NAV] = LAYOUT_5x6(
         _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
         _______, _______, LCK_TAP, _______, LCK_QWE, _______,             KC_INS , KC_HOME, KC_UP  , KC_END , KC_PGUP, _______, 
         _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,             CW_TOGG, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
         _______, _______, KC_ALGR, LCK_NUM, LCK_NAV, _______,             UM_RDO , UM_PST , UM_CPY , UM_CUT , UM_UND , _______,
                           _______, _______,                                                 _______, _______,
                                         _______, _______,                      KC_BSPC, KC_ENT ,
                                             _______, _______,              KC_DEL, _______,
                                             _______, _______,             _______, _______

    ),

    [_MEDIA] = LAYOUT_5x6(
         _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
         _______, _______, LCK_TAP, _______, LCK_QWE, _______,             _______, _______, KC_VOLU, _______, _______, _______,
         _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,             _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______,
         _______, _______, KC_ALGR, LCK_FUN, LCK_MED, _______,             _______, _______, _______, _______, _______, _______,
                           _______, _______,                                                 _______, _______,
                                         _______, _______,                      KC_MPLY, KC_MSTP,
                                             _______, _______,             KC_MUTE, _______,
                                             _______, _______,             _______, _______
    ),

    [_NUM] = LAYOUT_5x6(
         _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
         _______, KC_LBRC, KC_7   , KC_8   , KC_9   , KC_RBRC,             _______, LCK_QWE, _______, LCK_TAP, _______, _______,
         KC_GRV , KC_SCLN, KC_4   , KC_5   , KC_6   , KC_EQL ,             _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,
         KC_BSLS, KC_SLSH, KC_1   , KC_2   , KC_3   , KC_MINS,             _______, LCK_NUM, LCK_NAV, KC_ALGR, _______, _______,
                           DBL_D_C, KC_0   ,                                                 _______, _______,
                                         KC_ESC , KC_SPC ,                      _______, _______,
                                             _______, KC_TAB ,             _______, _______,
                                             _______, _______,             _______, _______
    ),

    // [_SYM] = LAYOUT_5x6(
    //      _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
    //      _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
    //      _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
    //      _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
    //                        _______, _______,                                                 _______, _______,
    //                                      _______, _______,                      _______, _______,
    //                                          _______, _______,             _______, _______,
    //                                          _______, _______,             _______, _______
    // ),

    [_FUN] = LAYOUT_5x6(
         _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
         _______, KC_F12 , KC_F7  , KC_F8  , KC_F9  , KC_PSCR,             _______, LCK_QWE, _______, LCK_TAP, _______, _______,
         _______, KC_F11 , KC_F4  , KC_F5  , KC_F6  , KC_SCRL,             _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,
         _______, KC_F10 , KC_F1  , KC_F2  , KC_F3  , KC_PAUS,             _______, LCK_FUN, LCK_MED, KC_ALGR, _______, _______,
                           _______, _______,                                                 _______, _______,
                                         KC_ESC , KC_SPC ,                      _______, _______,
                                             _______, KC_TAB ,             _______, _______,
                                             _______, _______,             _______, _______
    ),

    [_QWERTY_TAP] = LAYOUT_5x6(
        AS_TOGG , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,             KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , LCK_QWE,
        KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,             KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MINS,
        KC_LSFT , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,             KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LCTL , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,             KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_BSLS,
                           KC_LBRC, KC_RBRC,                                                 KC_GRV , KC_EQL ,
                                         KC_ESC , KC_SPC ,                      KC_BSPC, KC_ENT ,
                                             SH_TOGG, KC_TAB ,             KC_DEL ,SH_TOGG,
                                             KC_ENT , KC_BSPC,             QK_BOOT, _______
    ),

    // [_Empty] = LAYOUT_5x6(
    //      _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
    //      _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
    //      _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
    //      _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
    //                        _______, _______,                                                 _______, _______,
    //                                      _______, _______,                      _______, _______,
                                            //  _______, _______,             _______, _______,
                                            //  _______, _______,             _______, _______
    // )

};

const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{5, 6}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}},
  {{5, 7}, {4, 7}, {3, 7}, {2, 7}, {1, 7}, {0, 7}},
  {{5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8}},
  {{5, 9}, {4, 9}, {3, 9}, {2, 9}, {1, 9}, {0, 9}},
  {{5, 10}, {4, 10}, {3, 10}, {2, 10}, {1, 10}, {0, 10}},
  {{5, 11}, {4, 11}, {3, 11}, {2, 11}, {1, 11}, {0, 11}},
  {{5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
  {{5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
  {{5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
  {{5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
  {{5, 4}, {4, 4}, {3, 4}, {2, 4}},
  {{5, 5}, {4, 5}, {3, 5}, {2, 5}},
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HGUI_A:
            return TAPPING_TERM + 100;
        default:
            return TAPPING_TERM;
    }
}

// -------- TAP DANCE IMPL -------

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (!state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
        }
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_fin_key_2hold(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    uint16_t keycode = ((td_key_2hold_t*)user_data)->keycode;
    int layer_code_1 = ((td_key_2hold_t*)user_data)->layer_code_1;
    int layer_code_2 = ((td_key_2hold_t*)user_data)->layer_code_2;

    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(keycode);
            break;
        case TD_SINGLE_HOLD:
            layer_on(layer_code_1);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            layer_on(layer_code_2);
            break;
        default:
            break;
    }
}

void ql_res_key_2hold(tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((td_key_2hold_t*)user_data)->keycode;
    int layer_code_1 = ((td_key_2hold_t*)user_data)->layer_code_1;
    int layer_code_2 = ((td_key_2hold_t*)user_data)->layer_code_2;

    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(keycode); break;
        // If the key was held down and now is released then switch off the layer
        case TD_SINGLE_HOLD: layer_off(layer_code_1); break;
        case TD_DOUBLE_HOLD: layer_off(layer_code_2); break;
        default: break;
    }

    ql_tap_state.state = TD_NONE;
}

// Toggles layer on double tap
void ql_fin_layer_lock(tap_dance_state_t *state, void *user_data) {
    int layer_code = ((td_layer_data_t*)user_data)->layer_code;

    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << layer_code); \
    }
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [DOUBLE_DOT_COMMA] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMM),
    [KEY_2HOLD_ENT_NUM_FUN] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, ql_fin_key_2hold, ql_res_key_2hold, &((td_key_2hold_t){KC_ENT, _NUM, _FUN})),
    [LAYER_LOCK_QWERTY] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, ql_fin_layer_lock, NULL, &((td_layer_data_t){_QWERTY})),
    [LAYER_LOCK_NAV] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, ql_fin_layer_lock, NULL, &((td_layer_data_t){_NAV})),
    [LAYER_LOCK_BUTTON] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, ql_fin_layer_lock, NULL, &((td_layer_data_t){_BUTTON})),
    [LAYER_LOCK_MEDIA] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, ql_fin_layer_lock, NULL, &((td_layer_data_t){_MEDIA})),
    [LAYER_LOCK_NUM] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, ql_fin_layer_lock, NULL, &((td_layer_data_t){_NUM})),
    // [LAYER_LOCK_SYM] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, ql_fin_layer_lock, NULL, &((td_layer_data_t){_SYM})),
    [LAYER_LOCK_FUN] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, ql_fin_layer_lock, NULL, &((td_layer_data_t){_FUN})),
    [LAYER_LOCK_QWERTY_TAP] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, ql_fin_layer_lock, NULL, &((td_layer_data_t){_QWERTY_TAP})),
};
