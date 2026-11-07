target_sources(app PRIVATE src/bootloader_chord.c)
target_sources_ifdef(CONFIG_ZMK_SPLIT_ROLE_CENTRAL app PRIVATE src/hrm_led.c)
