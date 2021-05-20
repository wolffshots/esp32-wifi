# esp32-wifi

this component constitutes some wrappers for the example wifi connections from esp-idf

## how to use project

1. run ```git submodule add git@github.com:wolffshots/esp32-wifi.git components/esp32-wifi``` in your main project
2. configuration of this component is required to choose one of the two modes and set the ssid, password and other wifi settings
    1. `station mode` - this is when the esp32 acts as a client on another wifi network and receives an ip and is accessible through that network
    2. `softap mode` - this is when the esp32 acts as a router and broadcasts its own wifi network
3. `#include "wifi_sta.h"` or `#include "wifi_sap.h"` should give you access to the wifi station or wifi soft ap parts of this component respectively.

a typical use case would look like the following if you support both modes:
```c
#include "sdkconfig.h"
#ifdef CONFIG_ESP_ENABLE_WIFI_STA
#include "wifi_sta.h"
#endif
#ifdef CONFIG_ESP_ENABLE_WIFI_SOFTAP
#include "wifi_sap.h"
#endif
// function definitions and other imports
void app_main(void)
{
    // start of your main method code
#if defined(CONFIG_ESP_ENABLE_WIFI) && defined(CONFIG_ESP_ENABLE_WIFI_STA)
    wifi_init_sta();
#endif
#if defined(CONFIG_ESP_ENABLE_WIFI) && defined(CONFIG_ESP_ENABLE_WIFI_SOFTAP)
    wifi_init_sap();
#endif
    // rest of your main method code
}
```

if the above steps don't work then you may need to run ```git submodule init components/esp32-wifi``` 
and then ```git submodule update --remote --recursive``` in your main project



## folder contents

the component **esp32-wifi** contains two source files in C language [wifi_sta.c](wifi_sta.c) and [wifi_sap.c](wifi_sap.c). the files are located in root folder.

esp-idf projects are build using cmake. the project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both). 

below is short explanation of remaining files in the project folder.

```
├── include                     header file directory
│   ├── wifi_sap.h              the header file which describes functions for setting up wifi in softap mode
│   └── wifi_sta.h              the header file which describes functions for setting up wifi in station mode
├── .gitignore                  describes what files and folders git should ignore
├── CMakeLists.txt              base project cmake file (describes dependencies, include dir and src dir)
├── component.mk                component make file
├── Kconfig.projbuild           kconfig description file to add build time vars
├── LICENSE.md                  MIT license file
├── README.md                   this file
├── wifi_sap.c                  src file to define how the esp is set up in softap mode
└── wifi_sta.c                  src file to define how the esp is set up in station mode
```

for more information on structure and contents of esp-idf projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the esp-idf programming guide.

## license

the code in this project is licensed under the MIT license - see LICENSE for details.

# helpful commands
- ```git submodule update --remote --recursive``` - updates the checked out modules to the most recent commit to their main branch

# todo

 - [x] nothing for now