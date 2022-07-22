#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define QWERTY DF(_QWERTY)
#define DVORAK DF(_DVORAK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------.    ,-------|   N  |   M  |   ,  |   .  |   /  | Enter|
 * |------+------+------+------+------+------|   |   |    |  ESC  |------+------+------+------+------+------|
 * |LCtrl | LAlt | LAlt| Lgui | RAISE |      |-------|    |-------|      | LOWER| Left | Down |  Up  | Right|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Space \  |RAISE | RGUI | RAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,       KC_R,    KC_T,                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,       KC_F,    KC_G,                   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,       KC_V,    KC_B,                   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  KC_LCTL, KC_LALT, KC_LALT, KC_LGUI,   RAISE, _______, KC_PIPE,  KC_ESC, _______, LOWER,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
                             KC_LALT, KC_LGUI,   LOWER, KC_SPC,  KC_SPC,  RAISE,   KC_RALT, KC_RGUI \
),
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | TAB  |   "  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   A  |   O  |   E  |   U  |   I  |                    |   D  |   H  |   T  |   N  |   S  |  ?   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   :  |   Q  |   J  |   K  |   X  |-------.    ,-------|   B  |   M  |   W  |   V  |   Z  | Enter|
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LCtrl |   Z  |   X  |   C  |      |      |-------|    |-------|      |      | Left | Down |  Up  | Right|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Space \  |RAISE | RGUI | RAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_DVORAK] = LAYOUT( \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT , \
  KC_LCTL, KC_LALT, KC_LALT, KC_LGUI,   RAISE, _______, KC_PIPE,  KC_ESC, _______, LOWER,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
                             KC_LALT, KC_LGUI,   LOWER, KC_SPC,  KC_SPC,  RAISE,   KC_RALT, KC_RGUI \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   ~  |  !   |   @  |  #   |   $  |   %  |                    |   ^  |   &  |  *   |   (  |   )  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Del |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  _   |  +   |  {   |   }  |   |  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Shift|  F7  |  F8  |  F9  |  F10 | F11  |-------.    ,-------|      |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------|  F12  |    |  F12  |------+------+------+------+------+------|
 * | Ms3  |      |      |      |      |      |-------|    |-------|      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    _______, S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______, \
  KC_BTN3, _______, _______, _______, _______, _______,  KC_F12,  KC_F12, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, \
                             _______, _______, _______, _______, _______, _______, _______, _______ \
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |  1   |   2  |  3   |   4  |   5  |                    |   6  |   7  |  8   |   9  |   0  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Del |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  -   |  =   |  [   |   ]  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Shift|  F7  |  F8  |  F9  |  F10 | F11  |-------.    ,-------|      |ISO # |ISO / | PgUp | PgDn |      |
 * |------+------+------+------+------+------|  F12  |    |  F12  |------+------+------+------+------+------|
 * | Ms3  |      |      |      |      |      |-------|    |-------|      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______, \
  KC_BTN3, _______, _______, _______, _______, _______,  KC_F12,  KC_F12, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, \
                             _______, _______, _______, _______, _______, _______, _______, _______ \
),
/* ADJUST
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ |                    | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|                    |AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|-------.    ,-------|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_ADJUST] = LAYOUT( \
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI,                   RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL , \
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM,                   AG_SWAP, QWERTY,  DVORAK,   _______, _______,  _______, \
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,                     MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, \
                               _______, _______, _______, _______, _______, _______, _______, _______ \
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
