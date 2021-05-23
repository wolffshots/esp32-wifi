#include "wifi_shared.h"
#include "esp_wifi.h"

void wifi_shared_deinit(void)
{
    esp_wifi_deinit();
}