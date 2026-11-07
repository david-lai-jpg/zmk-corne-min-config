# TODO

## In Progress

## Done

- 2026-11-07 NAV left-hand numpad: 2–5 → 7 8 9 0, 14–16 → 4 5 6, 26–28 → 1 2 3, 17 → `` ` `` (plain `&kp N*`/`GRAVE`, so Shift gives the symbols). README/AGENTS layer tables updated. Verified: 6 parsed layers × 42, SVGs redrawn, left/right/reset build, right UF2 byte-identical to HEAD. Left UF2 (includes the earlier NAV `-` and thumb swap) at /Users/david/Desktop/corne_min_left_with_studio.uf2. Not committed.

- 2026-11-07 NAV position 11 → `&kp MINUS`; thumb holds swapped (39 `&lyr_tap 3 ENTER` → FN, 41 `mouse_lt_enter` → `num_layer_hold` → NUMBER). Drawer labels, README/AGENTS thumb tables and README HRM-toggle hint (now position 39) updated; README firmware section notes keymap-only changes need only the left image. Verified: 6 parsed layers × 42, SVGs redrawn, left/right/reset build locally, right UF2 byte-identical to a HEAD build. Left UF2 copied to /Users/david/Desktop/corne_min_left_with_studio.uf2. Not committed.

- 2026-11-07 Home-row-mod toggle: NO HRM layer at index 1 (NUMBER→2, FN→3, MOUSELESS→4, NAV→5), `&tog 1` on FN position 13. Fixed stale drawer HRM labels (D/F/J/K) and README layer/thumb tables. Verified: 6 parsed layers × 42 bindings, SVGs redrawn, left (central, Studio) and right (peripheral) UF2s build locally, no display/underglow/pointing/encoder config. Added "Local firmware build" to AGENTS.md. Committed and pushed as 19188b0; CI build and draw passed.
- 2026-11-07 HRM off by default + LED blink: BASE is plain letters; layer 1 HRM holds the home-row mods (FN + A turns them on). `config/src/hrm_led.c` (central only) blinks the status LED yellow on / magenta off (orange impossible: 3 on/off GPIOs). `config/west.yml` pins corne-min-rgbled to fc827695 because hrm_led.c mirrors its private blink queue. Drawer: `LGUI` → Cmd icon (thumb 37). Verified: both halves build; user flashed the left half and confirmed the toggle and blinks work on hardware.
- 2026-11-07 Fixed CI link failure on 8c57aa1: `settings_reset` target lacks the rgbled widget, so `config/CMakeLists.txt` builds `hrm_led.c` only with `CONFIG_RGBLED_WIDGET AND CONFIG_ZMK_SPLIT_ROLE_CENTRAL`. Verified locally: reset, left (byte-identical to the flashed UF2), and right all build. AGENTS.md verification names all three targets.
