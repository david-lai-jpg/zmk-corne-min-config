#include <zephyr/kernel.h>
#include <zephyr/sys/atomic.h>
#include <zephyr/sys/reboot.h>

#include <dt-bindings/zmk/reset.h>
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>

#define BOOTLOADER_HOLD_MS 750
#define FIRST_KEY_BIT 0
#define SECOND_KEY_BIT 1
#define BOTH_KEYS_MASK (BIT(FIRST_KEY_BIT) | BIT(SECOND_KEY_BIT))

#if IS_ENABLED(CONFIG_BOARD_CORNE_MIN_LEFT)
#define FIRST_KEY_POSITION 0
#define SECOND_KEY_POSITION 38
#elif IS_ENABLED(CONFIG_BOARD_CORNE_MIN_RIGHT)
#define FIRST_KEY_POSITION 11
#define SECOND_KEY_POSITION 39
#else
#error "Bootloader chords require a Corne Min half"
#endif

static atomic_t pressed_keys;

static void enter_bootloader(struct k_work *work) {
    ARG_UNUSED(work);

    if ((atomic_get(&pressed_keys) & BOTH_KEYS_MASK) == BOTH_KEYS_MASK) {
        sys_reboot(RST_UF2);
    }
}

K_WORK_DELAYABLE_DEFINE(bootloader_work, enter_bootloader);

static int bootloader_chord_listener(const zmk_event_t *event) {
    const struct zmk_position_state_changed *position_event =
        as_zmk_position_state_changed(event);

    if (!position_event || position_event->source != ZMK_POSITION_STATE_CHANGE_SOURCE_LOCAL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    int key_bit;
    if (position_event->position == FIRST_KEY_POSITION) {
        key_bit = FIRST_KEY_BIT;
    } else if (position_event->position == SECOND_KEY_POSITION) {
        key_bit = SECOND_KEY_BIT;
    } else {
        return ZMK_EV_EVENT_BUBBLE;
    }

    if (position_event->state) {
        atomic_set_bit(&pressed_keys, key_bit);
    } else {
        atomic_clear_bit(&pressed_keys, key_bit);
    }

    if ((atomic_get(&pressed_keys) & BOTH_KEYS_MASK) == BOTH_KEYS_MASK) {
        k_work_reschedule(&bootloader_work, K_MSEC(BOOTLOADER_HOLD_MS));
    } else {
        k_work_cancel_delayable(&bootloader_work);
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(bootloader_chord, bootloader_chord_listener);
ZMK_SUBSCRIPTION(bootloader_chord, zmk_position_state_changed);
