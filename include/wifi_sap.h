#ifndef WIFI_SAP_H
#define WIFI_SAP_H

#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

void wifi_init_sap(void);

#ifdef __cplusplus
}
#endif

#endif // WIFI_SAP_H