/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "configpines.h"
#include "pcf8574.h"

void app_main(void)
{
    configurar_pines_salida();
    inicializaI2C();  // AÑADIDO
    
    while(1){
        /* encenderPinesSalida();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        apagarPinesSalida();
        vTaskDelay(1000 / portTICK_PERIOD_MS); */
        
        // CAMBIADO: Usar función que ya tienes
        leerExpansores();  // Esta función ya maneja todo
        vTaskDelay(200 / portTICK_PERIOD_MS);  // Esperar 400 ms antes de la siguiente lectura
    }
}
