#include <esp_flash.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <esp_event.h>
#include <driver/rmt.h>
//what a dumb way of configuring
#include "led_strip.h"

#include "wifi.h"

led_strip_handle_t strip;

void app_main() {
    esp_event_loop_create_default();
    esp_timer_early_init();
    nvs_flash_init();
    init_wifi();

    led_strip_config_t strip_config = {
        .max_leds = 2,
        .strip_gpio_num = 2
    };
    led_strip_rmt_config_t strip_rmt_config = {
        .resolution_hz = 0
    };

    led_strip_new_rmt_device(&strip_config, &strip_rmt_config, &strip);
    led_strip_set_pixel(strip, 0, 255, 255, 255);
    led_strip_set_pixel(strip, 1, 0, 0, 255);
    led_strip_refresh(strip);
}