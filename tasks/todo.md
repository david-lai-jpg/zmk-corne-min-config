# TODO

## In Progress

## Done

- 2026-11-07 Home-row-mod toggle: NO HRM layer at index 1 (NUMBER→2, FN→3, MOUSELESS→4, NAV→5), `&tog 1` on FN position 13. Fixed stale drawer HRM labels (D/F/J/K) and README layer/thumb tables. Verified: 6 parsed layers × 42 bindings, SVGs redrawn, left (central, Studio) and right (peripheral) UF2s build locally, no display/underglow/pointing/encoder config. Added "Local firmware build" to AGENTS.md. Committed and pushed as 19188b0; CI build and draw passed.
- 2026-11-07 HRM off by default + LED blink: BASE is plain letters; layer 1 HRM holds the home-row mods (FN + A turns them on). `config/src/hrm_led.c` (central only) blinks the status LED yellow on / magenta off (orange impossible: 3 on/off GPIOs). `config/west.yml` pins corne-min-rgbled to fc827695 because hrm_led.c mirrors its private blink queue. Drawer: `LGUI` → Cmd icon (thumb 37). Verified: both halves build; user flashed the left half and confirmed the toggle and blinks work on hardware.
