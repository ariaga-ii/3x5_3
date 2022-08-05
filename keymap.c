#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_ENABLE
static uint32_t oled_timer = 0;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.   
enum layers {
  _QWERTY,
  _NAV,
  _SYM
};

enum {
  TD_Q_TAB,
  TD_A_ESC,
  TD_SPC_CLN,
  TD_SCLN_CLN,
  TD_SLSH_Q
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_A_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_ESC),
  [TD_SPC_CLN] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_COLON),
  [TD_SCLN_CLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLON),
  [TD_SLSH_Q] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES)
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NAV,
  SYM,
  COLON,
  UPDIR
};

#define KC_LGESC LGUI_T(KC_ESC)
#define KC_ALT_TAB RALT_T(KC_TAB) 
#define KC_SPC_CLN TD(TD_SPC_CLN)
#define KC_ENT_CTL RCTL_T(KC_ENT)
#define KC_SYM_DEL LT(2, KC_BSPC)
#define KC_ADJ_DEL LT(3, KC_BSPC)
#define KC_A_ESC TD(TD_A_ESC)

#define L_THMB_0 KC_LSFT
#define L_THMB_2 LGUI_T(KC_ESC)

#define R_THMB_0 KC_ALT_TAB
#define R_THMB_2 KC_SPC_CLN



/*
  //┌────┬────┬────┬────┬────┐              ┌────┬────┬────┬────┬────┐
     GRV , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  ,MINS,
  //├────┼────┼────┼────┼────┤              ├────┼────┼────┼────┼────┤
     LCDQ,SYMS,NUMD,ARWF, G  ,                H  , J  , K  , L  ,RCQU,
  //├────┼────┼────┼────┼────┤              ├────┼────┼────┼────┼────┤
     LSPO, X  , C  , V  , B  ,                N  , M  ,COMM,DOT ,RSPC,
  //├────┼────┼────┼────┼────╱────╱    ╲────╲────┼────┼────┼────┼────┤
                   LHAO,LOBO,BSPC,       SPC ,ROBC,RHAC
  //             ╱────╱────╱────╱        ╲────╲────╲────╲
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3(
    KC_Q,  KC_W,  KC_E,                KC_R, KC_T,                                KC_Y,         KC_U,         KC_I,      KC_O,     KC_P, 
    KC_A,  KC_S, LCTL_T(KC_D), LALT_T(KC_F), KC_G,                                KC_H, RALT_T(KC_J), RCTL_T(KC_K),      KC_L,  KC_QUOT,
    KC_Z,  KC_X,  KC_C,                KC_V, KC_B,                                KC_N,         KC_M,      KC_COMM,    KC_DOT,   KC_ENT,
                                   L_THMB_0,  NAV, L_THMB_2,    KC_SPC, LT(2, KC_BSPC),     R_THMB_0 
  ),

  [_NAV] = LAYOUT_split_3x5_3(
    LCAG(KC_T), KC_7,         KC_8,         KC_9, KC_PLUS,                       KC_SLSH,           KC_7,      KC_8,      KC_9,  KC_0,
    KC_ASTR,    KC_4, LCTL_T(KC_5), LALT_T(KC_6), KC_MINS,                        KC_LEFT,        KC_DOWN,     KC_UP,  KC_RIGHT,  KC_NO,
    KC_0,       KC_1,        KC_2,          KC_3,  KC_EQL,                         KC_HOME,        KC_PGDN,   KC_PGUP,    KC_END,  KC_NO,
                                    L_THMB_0,     NAV,  L_THMB_2,  R_THMB_2,   KC_BSPC,       R_THMB_0 
  ),

  /* SYMBOL LAYER 
    KC_QUOT, KC_LABK, KC_RABK, KC_DQUO, KC_DOT ,
    KC_EXLM, KC_MINS, KC_PLUS, KC_EQL , KC_HASH,
    KC_CIRC, KC_SLSH, KC_ASTR, KC_BSLS, UPDIR,

                      KC_AMPR, SCOPE  , KC_LBRC, KC_RBRC, KC_PERC, 
                      KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES,
                      KC_TILD, KC_DLR , KC_LCBR, KC_RCBR, KC_AT  ,
   * */
  [_SYM] = LAYOUT_split_3x5_3(
    KC_QUOT,  KC_LABK,  KC_RABK,  KC_DQUO,   KC_DOT,                            KC_AMPR,  KC_SCLN,  KC_LBRC, KC_RBRC, KC_PERC,
    KC_EXLM,  KC_MINS,  KC_PLUS,   KC_EQL, LALT(KC_3),                           KC_PIPE,  KC_COLN,  KC_LPRN, KC_RPRN, KC_QUES,
    KC_GRV,   KC_SLSH,  KC_ASTR,  KC_BSLS,   UPDIR,                             KC_UNDS,   KC_DLR,  KC_LCBR, KC_RCBR, KC_AT,
                                 L_THMB_0,   KC_NO,  L_THMB_2,     R_THMB_2, KC_SYM_DEL,  R_THMB_0 
  )
};


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM SYM_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM NAV_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    /* static const char PROGMEM adjust_layer[] = { */
    /*     0x20, 0x9d, 0x9e, 0x9f, 0x20, */
    /*     0x20, 0xbd, 0xbe, 0xbf, 0x20, */
    /*     0x20, 0xdd, 0xde, 0xdf, 0x20, 0}; */
    /* if(layer_state_is(_ADJUST)) { */
    /*     oled_write_P(adjust_layer, false); */
    /* } else  */
    if(layer_state_is(_NAV)) {
        oled_write_P(NAV_layer, false);
    } else if(layer_state_is(_SYM)) {
        oled_write_P(SYM_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void suspend_power_down_user() {
    oled_off();
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    if (timer_elapsed32(oled_timer) > 30000) {
      oled_off();
      return;
    } else {
      oled_on();
    }
  }
  if (is_keyboard_master()) {
    render_status_main(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_status_secondary();
  }
}


#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
        oled_timer = timer_read32();
#endif
    // set_timelog();
  }

  switch (keycode) {
    case NAV:
      if (record->event.pressed) {
        layer_on(_NAV);
      } else {
        layer_off(_NAV);
      }
      return false;
    case SYM:
      if (record->event.pressed) {
        layer_on(_SYM);
      } else {
        layer_off(_SYM);
      }
      return false;
    case COLON:
      if (record->event.pressed) {
        SEND_STRING(":");
      }
      return false;

    case UPDIR:
      if (record->event.pressed) {
        SEND_STRING("../");
      }
      return false;

    case (LT(1, KC_TAB)):
      if (!record->tap.count && record->event.pressed) {
        tap_code16(S(KC_TAB));
        return false;
      } else if (record->event.pressed) {
        layer_on(_NAV);
      } else {
        layer_off(_NAV);
      }
      return false;


  }
  return true;
}

