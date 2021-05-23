/*
 * MIT License
 *
 * Copyright (c) 2021 wolffshots
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * A note on the copyright line: https://www.copyright.gov/title17/92chap4.html#408
 */

/**
 * @file wifi_sap.c
 * @brief implementation for wrapper component to set up wifi in softap mode
 */

#include "wifi_sap.h"

static const char *TAG = CONFIG_WIFI_STA_LOG_TAG;

#if defined(CONFIG_ESP_WIFI_SSID_SOFTAP) && defined(CONFIG_ESP_WIFI_PASSWORD_SOFTAP) && defined(CONFIG_ESP_WIFI_CHANNEL_SOFTAP) && defined(CONFIG_ESP_MAX_STA_CONN_SOFTAP)
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED)
    {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
        ESP_LOGI(TAG, "station " MACSTR " join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
    {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
        ESP_LOGI(TAG, "station " MACSTR " leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}
#endif
void wifi_init_softap(void)
{
#if defined(CONFIG_ESP_WIFI_SSID_SOFTAP) && defined(CONFIG_ESP_WIFI_PASSWORD_SOFTAP) && defined(CONFIG_ESP_WIFI_CHANNEL_SOFTAP) && defined(CONFIG_ESP_MAX_STA_CONN_SOFTAP)
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = CONFIG_ESP_WIFI_SSID_SOFTAP,
            .ssid_len = strlen(CONFIG_ESP_WIFI_SSID_SOFTAP),
            .channel = CONFIG_ESP_WIFI_CHANNEL_SOFTAP,
            .password = CONFIG_ESP_WIFI_PASSWORD_SOFTAP,
            .max_connection = CONFIG_ESP_MAX_STA_CONN_SOFTAP,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK},
    };
    if (strlen(CONFIG_ESP_WIFI_PASSWORD_SOFTAP) == 0)
    {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID: %s, password: %s%s*** channel:%d",
             CONFIG_ESP_WIFI_SSID_SOFTAP, CONFIG_ESP_WIFI_PASSWORD_SOFTAP[0], CONFIG_ESP_WIFI_PASSWORD_SOFTAP[1], CONFIG_ESP_WIFI_CHANNEL_SOFTAP);
#endif
}

void wifi_init_sap(void)
{
    ESP_LOGI(TAG, "wifi softap!");
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    wifi_init_softap();
}