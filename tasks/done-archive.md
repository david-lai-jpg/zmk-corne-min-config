# Done Archive

## 2026-08-05

- [x] Audit this Corne Min repo, the `zmk-new_corne` reference, and the upstream Corne Min module/hardware.
- [x] Port all shared layer bindings for a standard split build, excluding displays, encoders, joystick, pointing, underglow, and dongle behavior.
- [x] Implement and verify `AGENTS.md`, `README.md`, `KEY_POSITIONS.svg`, and Keymap Drawer outputs.
- [x] Build the left, right, and settings-reset UF2 targets locally.

## 2026-08-07

- Audited the Corne Min board/module and the `zmk-new_corne` reference configuration.
- Ported the five-layer keymap to the Corne Min's 42-key standard split layout.
- Removed dongle/Prospector build targets, shield files, and manifest dependency.
- Added the board configuration, repository guidance, README, and Keymap Drawer artifacts.
- Built and verified the left, right, and settings-reset firmware locally.
- Visually inspected the generated key-position and full-keymap diagrams.
- Added and locally built per-half bootloader chords for positions `0` + `38` and `11` + `39`.
