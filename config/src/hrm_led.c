#include <zephyr/kernel.h>

#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>

// Blink the status LED once when the HRM layer is toggled: yellow when home-row
// mods turn on, magenta when they turn off. The LED is three on/off GPIOs, so
// orange is not possible; yellow (red + green) is the nearest color.
#define HRM_LAYER 1 // hrm_layer in corne_min.keymap
#define COLOR_YELLOW 3
#define COLOR_MAGENTA 5
#define BLINK_MS 300

// Mirrors the private struct blink_item and the global led_msgq in the
// rgbled widget's src/widget.c. config/west.yml pins that module to a commit so
// this layout cannot change underneath us.
struct blink_item {
    uint8_t color;
    uint16_t duration_ms;
    uint16_t sleep_ms;
};

extern struct k_msgq led_msgq;

static int hrm_led_listener(const zmk_event_t *event) {
    const struct zmk_layer_state_changed *layer_event = as_zmk_layer_state_changed(event);

    if (!layer_event || layer_event->layer != HRM_LAYER) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    struct blink_item blink = {
        .color = layer_event->state ? COLOR_YELLOW : COLOR_MAGENTA,
        .duration_ms = BLINK_MS,
    };
    k_msgq_put(&led_msgq, &blink, K_NO_WAIT);
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(hrm_led, hrm_led_listener);
ZMK_SUBSCRIPTION(hrm_led, zmk_layer_state_changed);
