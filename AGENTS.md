# Corne Min ZMK Configuration

## Hardware contract

- Target a standard two-half split: `corne_min_left` is central and `corne_min_right` is peripheral.
- Do not add Prospector/dongle targets or peripheral-role overrides for both halves.
- This 42-key board has no display, encoder, joystick, pointing device, or RGB underglow.
- The built-in RGB status LED is supported by the existing `rgbled_adapter` shield; it is not an underglow or display feature.
- The active board definition comes from the `corne-min` branch of `MechboardsLTD/zmk-module`.

## Canonical files

- `config/corne_min.keymap` — source of truth for bindings and behaviors.
- `config/corne_min.conf` — source of truth for ZMK feature configuration.
- `config/src/bootloader_chord.c` — per-half local bootloader chord handling.
- `config/src/hrm_led.c` — status LED blink when the HRM layer toggles (left half only).
- `config/corne_min.json` — physical 42-key geometry used for local rendering.
- `KEY_POSITIONS.svg` — canonical position-number map (`0`–`41`).
- `keymap-drawer/corne_min.svg` — canonical visual keymap.

Always consult both SVGs before changing a position named by number.

Positions `0` + `38` enter the left bootloader; positions `11` + `39` enter the right bootloader after a 750 ms hold. Keep this as a local position-event listener: ZMK combo reset behaviors always execute on the central half.

## Layer architecture

| Index | Name | Purpose |
| ---: | --- | --- |
| 0 | BASE | QWERTY, plain home row (home-row modifiers off) |
| 1 | HRM | Home-row modifiers; toggled by `&tog 1` on FN position `13` |
| 2 | NUMBER | Number row `1`–`0`; symbols via Shift |
| 3 | FN | Function keys `F1`–`F12` and Bluetooth |
| 4 | MOUSELESS | Keyboard-driven shortcuts/navigation |
| 5 | NAV | Arrow cluster, Home/End, Page Up/Down (right); numpad `1`–`0` and `` ` `` (left) |

HRM must stay directly above BASE. ZMK checks the highest active layer first, so a higher index would cover the FN media keys and the NAV arrows on the same home-row positions. Home-row mods are off at power-on by design: a layer toggle is not saved, so they turn off again after a restart or a wake from sleep. Toggling HRM blinks the left status LED once: yellow when it turns on, magenta when it turns off (`config/src/hrm_led.c`, central only). The LED is three on/off GPIOs, so only 7 colors exist; orange is not possible. `hrm_led.c` mirrors the rgbled module's private `struct blink_item` and `led_msgq`, so `config/west.yml` pins that module to a commit; re-check the struct before moving the pin.

There is no symbols layer. Every symbol it held is `Shift` + a number on NUMBER, so the layer was removed rather than duplicated. Brackets stay on `lbrc_morph`/`rbrc_morph` at position `18`/`30`.

The arrow cluster is pinned to `↑`=`I`, `←↓→`=`J`/`K`/`L` to mirror the Mouseless app's movement keys. Never relocate it, and never place a conflicting binding on those positions in NAV.

### Thumb behaviors

| Position | Tap | Hold |
| ---: | --- | --- |
| `39` | `ENTER` | FN |
| `40` | `BSPC` | NAV |
| `41` | toggle MOUSELESS + Right Option | NUMBER |

`lyr_tap` drives positions `39` and `40`. Its `quick-tap-ms = <250>` is load-bearing: tap-then-hold within that window repeats the tap key instead of engaging the layer, which is what makes held backspace work on position `40`. Do not remove it.

In MOUSELESS, position `41` exits the layer on tap and activates NAV on hold.

## Keymap Drawer

Redraw locally after **every** keymap or layout change, in the same turn as the edit. The `draw.yml` workflow also redraws on push, but that is a backstop — never rely on it, because the user confirms layout changes by looking at the local SVG before anything is pushed.

```sh
keymap -c keymap_drawer.config.yaml parse -z config/corne_min.keymap -o keymap-drawer/corne_min.yaml
keymap -c keymap_drawer.config.yaml draw -j config/corne_min.json keymap-drawer/corne_min.yaml -o keymap-drawer/corne_min.svg
keymap -c keymap_drawer.config.yaml draw -j config/corne_min.json keymap-drawer/key_positions.yaml -o KEY_POSITIONS.svg
```

Renaming or deleting a behavior silently breaks `raw_binding_map` in `keymap_drawer.config.yaml`. Those keys match the binding text verbatim, so a stale entry does not error — it just stops applying and the key renders with a wrong or default label. Grep that file for every behavior name touched, and re-run the draw after fixing it.

Add custom binding labels to `keymap_drawer.config.yaml` when automatic parsing is unclear. Do not leave generated YAML/SVG files stale.

To eyeball the result without a browser, `rsvg-convert -w 1500 keymap-drawer/corne_min.svg -o /tmp/k.png`. Icon keys (arrows, Tab, Ctrl, Space) render blank in that PNG because `rsvg-convert` does not follow `<use href="#…">` into nested `<svg>` defs. That is a rasterizer limitation, not a keymap fault — confirm those keys with `href="#mdi:…"` greps instead of assuming a regression.

## Verification

For keymap changes, require:

1. all six parsed layers contain exactly 42 bindings;
2. every keycode resolves against `zmk/app/include/dt-bindings/zmk/keys.h`, and every `&label` resolves to a ZMK builtin or a local definition;
3. SVGs regenerated locally in the same turn as the edit, with no stale `raw_binding_map` entries left behind;
4. all three `build.yaml` targets build: left, right, and `settings_reset`;
5. no dongle, display, encoder, joystick, pointing, or underglow settings enter the build.

### Local firmware build

The repo root is a west workspace (`zmk/`, `zephyr/`, `modules/` are git-ignored). Limit it to the modules this nRF52 build needs before `west update`, so it fetches about 1 GB instead of every Zephyr module: `west config manifest.project-filter -- "-.*,+zmk,+zephyr,+corne-min-rgbled,+corne-min-board,+hal_nordic,+cmsis,+nanopb,+zmk-studio-messages,+lvgl,+tinycrypt,+segger,+picolibc"` (stored in the untracked `.west/config`). West refuses `west update <name>` for imported modules; change the filter and run plain `west update` instead. Build with a GNU Arm toolchain (`ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb`, `GNUARMEMB_TOOLCHAIN_PATH=<toolchain>/arm-none-eabi`), mirroring `build.yaml`:

```sh
west build -p -s zmk/app -d <out>/left -b corne_min_left -S studio-rpc-usb-uart -- -DSHIELD=rgbled_adapter -DZMK_CONFIG="$PWD/config" -DCONFIG_ZMK_STUDIO=y -DCONFIG_ZMK_STUDIO_LOCKING=n -DCONFIG_ZMK_BLE_EXPERIMENTAL_CONN=y
west build -p -s zmk/app -d <out>/right -b corne_min_right -- -DSHIELD=rgbled_adapter -DZMK_CONFIG="$PWD/config" -DCONFIG_ZMK_BLE_EXPERIMENTAL_CONN=y
west build -p -s zmk/app -d <out>/reset -b corne_min_left -- -DSHIELD=settings_reset -DZMK_CONFIG="$PWD/config"
```
