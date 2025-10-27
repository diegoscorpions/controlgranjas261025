idf_component_register(SRCS "pcf8574.c" "configpines.c" "main.c" "pcf8574.c"
                    PRIV_REQUIRES spi_flash esp_driver_gpio esp_driver_i2c
                    INCLUDE_DIRS "")
