#pragma once

// ----------- GENERAL ----------- 
#define USB_POLLING_INTERVAL_MS 1 
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

// --------- AUTO SHIFT ---------- 
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define RETRO_SHIFT

// Sets number of taps for TT() to change layer
// #define TAPPING_TOGGLE 2

// -------- TAPPING TERM --------- 
// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 300
#define TAPPING_TERM_PER_KEY

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

// The default 5ms seems too quick. Trying out 40 ms for more reliability.
#define DEBOUNCE 15

#define PERMISSIVE_HOLD
#define MASTER_RIGHT