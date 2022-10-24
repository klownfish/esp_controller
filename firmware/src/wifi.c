#include <esp_wifi.h>

wifi_config_t wifi_config = {
    .sta = {
        .ssid = "NCSpeople2",
        .password = "peopleNCS",
        .scan_method = WIFI_ALL_CHANNEL_SCAN,
        .bssid_set = 0,
        .channel = 0,
        .listen_interval = 0,
        .pmf_cfg = {
            .required = 0
        },
        .rm_enabled = 1,
        .btm_enabled = 1,
    },
};

void wifi_disconnected_handler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {
    esp_wifi_connect(); // a failed connect sends a disconnected event
    printf("connection no\n");
}

void got_ip_handler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {
    printf("connection yes :)\n");
}


void init_wifi() {
    esp_netif_init();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    wifi_init_config.wifi_task_core_id = 1;
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_set_country_code("SE", true));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_connect());
    esp_wifi_set_ps(WIFI_PS_NONE);

    esp_event_handler_instance_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, wifi_disconnected_handler, NULL, NULL);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, got_ip_handler, NULL, NULL);    
}