set(COMPONENT_ADD_INCLUDEDIRS include)
set(COMPONENT_SRCS "wifi_sta.c" "wifi_sap.c")
set(COMPONENT_PRIV_REQUIRES "spi_flash" "nvs_flash")
register_component()
