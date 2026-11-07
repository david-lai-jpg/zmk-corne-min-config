target_sources(app PRIVATE src/bootloader_chord.c)

# hrm_led.c needs the rgbled widget (absent from the settings_reset target) and
# layer state, which only the central half has.
if(CONFIG_RGBLED_WIDGET AND CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  target_sources(app PRIVATE src/hrm_led.c)
endif()
