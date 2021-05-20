#ifndef WIFI_STA_H
#define WIFI_STA_H

// main stuff
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#ifdef __cplusplus
extern "C" {
#endif

void wifi_init_sta(void);

#ifdef __cplusplus
}
#endif

#endif // WIFI_STA_H