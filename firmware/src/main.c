#include <esp_flash.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <esp_event.h>

#include "led_strip.h"
#include "wifi.h"
#include "nbe_i2c.h"
#include "fc.h"

led_strip_t *strip;

void set_pixel(uint8_t pixel, uint8_t r, uint8_t g, uint8_t b) {
        strip->set_pixel(strip, pixel, r / 4, g / 4, b / 4);
        strip->refresh(strip, 1000);
}

void app_main() {
    esp_event_loop_create_default();
    esp_timer_early_init();
    nvs_flash_init();
    init_wifi();

    // nbe_i2c_t nbe_i2c;
    // nbe_i2c_init(&nbe_i2c, 0, 16, 17, 100000);
    // while (1) {
    //     for (uint8_t i = 0; i < 255; i++) {
    //         printf("address %d\n", i);
    //         nbe_i2c_start_write(&nbe_i2c, i, NULL, NULL);
    //         nbe_i2c_commit(&nbe_i2c);
    //         while(nbe_i2c_is_busy(&nbe_i2c)) {}
    //     }
    //     vTaskDelay(1000);
    //     printf("spammed\n");
    // }

    strip = led_strip_init(0, 2, 2);
    while(1) {
        vTaskDelay(1000);
        printf("update\n");
        set_pixel(0, MAGENTA);
        set_pixel(1, YELLOW);
    }
}