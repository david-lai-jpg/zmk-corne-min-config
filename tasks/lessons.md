# Lessons Learned

<!-- Genuinely useful discoveries for future sessions -->

- Eyelash Corne has 48 positions, but Corne Min uses the standard 42-key Corne geometry. Porting requires dropping Eyelash positions `6`, `19`–`21`, and `34`–`35`, then renumbering each later row/thumb cluster; compare generated layer arrays after mapping rather than copying numeric hold-trigger lists unchanged.
- `rgbled_adapter` drives the Corne Min's built-in GPIO status LED for battery/connectivity. It is separate from a display or RGB underglow and remains valid on the no-display standard split.
