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
- `config/corne_min.json` — physical 42-key geometry used for local rendering.
- `KEY_POSITIONS.svg` — canonical position-number map (`0`–`41`).
- `keymap-drawer/corne_min.svg` — canonical visual keymap.

Always consult both SVGs before changing a position named by number.

## Layer architecture

| Index | Name | Purpose |
| ---: | --- | --- |
| 0 | BASE | QWERTY and home-row modifiers |
| 1 | NUMBER | Numbers and navigation |
| 2 | FN | Function keys, navigation, and Bluetooth |
| 3 | MOUSELESS | Keyboard-driven shortcuts/navigation |
| 4 | SYMBOLS | Symbols and navigation |

BASE position `41` uses `&mouse_lt_enter 0 0`: tap toggles MOUSELESS and sends Right Option; hold activates FN. In MOUSELESS, the same position exits the layer on tap and activates SYMBOLS on hold.

## Keymap Drawer

After every keymap or layout change, regenerate all visual artifacts:

```sh
keymap -c keymap_drawer.config.yaml parse -z config/corne_min.keymap -o keymap-drawer/corne_min.yaml
keymap -c keymap_drawer.config.yaml draw -j config/corne_min.json keymap-drawer/corne_min.yaml -o keymap-drawer/corne_min.svg
keymap -c keymap_drawer.config.yaml draw -j config/corne_min.json keymap-drawer/key_positions.yaml -o KEY_POSITIONS.svg
```

Add custom binding labels to `keymap_drawer.config.yaml` when automatic parsing is unclear. Do not leave generated YAML/SVG files stale.

## Verification

For keymap changes, require:

1. all five parsed layers contain exactly 42 bindings;
2. regenerated SVGs exist and render the Corne Min geometry;
3. both standard split firmware targets build;
4. no dongle, display, encoder, joystick, pointing, or underglow settings enter the build.
