#ifndef CONFIG_PINES_H
#define CONFIG_PINES_H

#include "driver/gpio.h"
#include "esp_err.h"

/* Declaracion de pines para comunicaciones I2C y SPI
   Este ESP32 es el SPI esclavo de la pantalla TFT
 */

#define SDA GPIO_NUM_8
#define SCL GPIO_NUM_9
#define CS GPIO_NUM_10
#define MOSI GPIO_NUM_11
#define SCLK GPIO_NUM_12
#define MISO GPIO_NUM_13



/* Declaracion de pines de relés */
#define salida0 GPIO_NUM_15
#define salida1 GPIO_NUM_16
#define salida2 GPIO_NUM_17
#define salida3 GPIO_NUM_18



/* No se declaran pines de entrada, puesto que todos están dispuestos en expansores I2C. */

/* Funciones para manejo de los pines de salida de relés. */
esp_err_t configurar_pines_salida(void);
void encenderPinesSalida(void);
void apagarPinesSalida(void);
void encenderPinSalida(int pin);
void apagarPinSalida(int pin);


#endif // CONFIG_PINES_H

