# Lessons Learned

<!-- Genuinely useful discoveries for future sessions -->

- Eyelash Corne has 48 positions, but Corne Min uses the standard 42-key Corne geometry. Porting requires dropping Eyelash positions `6`, `19`–`21`, and `34`–`35`, then renumbering each later row/thumb cluster; compare generated layer arrays after mapping rather than copying numeric hold-trigger lists unchanged.
- `rgbled_adapter` drives the Corne Min's built-in GPIO status LED for battery/connectivity. It is separate from a display or RGB underglow and remains valid on the no-display standard split.
- ZMK v0.3 combo invocations hard-code their event source as local, so a reset/bootloader combo always reboots the central half even when its positions are on the peripheral. Per-half bootloader chords must observe locally scanned `zmk_position_state_changed` events on each half instead.
- ZMK's media transport and volume consumer usages work broadly across macOS and Windows. Display-brightness consumer usages are also cross-platform, but the host/display driver decides whether they act; built-in laptop displays are more reliable than external monitors.
- On this Mac, the GNU Arm toolchain for local ZMK builds is `/Applications/ArmGNUToolchain/15.2.rel1/arm-none-eabi` (GCC 15.2 builds ZMK v0.3 / Zephyr 3.5 cleanly, checked 2026-11-07). Local build steps are in `AGENTS.md` → Local firmware build.
