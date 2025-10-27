#include "configpines.h"
#include "esp_log.h"

int pines_salida[4] = {salida0, salida1, salida2, salida3};

static const char* TAG =  "Configuracion Pines";

/* Estructura de configuración de pines gpio de salida */
gpio_config_t configuracionPines = {
    .pin_bit_mask = (1ULL << 0),   //máscara de bits para los pines a configurar
    .mode = GPIO_MODE_OUTPUT,               //modo de los pines (entrada/salida)
    .pull_up_en = GPIO_PULLUP_DISABLE,      //deshabilitar resistencia pull-up
    .pull_down_en = GPIO_PULLDOWN_DISABLE,  //deshabilitar resistencia pull-down
    .intr_type = GPIO_INTR_DISABLE          //deshabilitar interrupciones
};



esp_err_t configurar_pines_salida(void){

    configuracionPines.pin_bit_mask = (1ULL << salida0) | 
                                      (1ULL << salida1) | 
                                      (1ULL << salida2) | 
                                      (1ULL << salida3);
    
    esp_err_t ret = gpio_config(&configuracionPines);

    if(ret == ESP_OK){
        ESP_LOGI(TAG, "Realizada correctamente");
    }
    else {
        ESP_LOGE(TAG, "erroneo");
    }

    apagarPinesSalida();
    return ret;
}

void apagarPinesSalida(){
    gpio_set_level(salida0, 0);
    gpio_set_level(salida1, 0);
    gpio_set_level(salida2, 0);
    gpio_set_level(salida3, 0);
}

void apagarPinSalida(int pin){
    gpio_set_level(pines_salida[pin], 0);
}

void encenderPinesSalida(){
    gpio_set_level(salida0, 1);
    gpio_set_level(salida1, 1);
    gpio_set_level(salida2, 1);
    gpio_set_level(salida3, 1);
}

void encenderPinSalida(int pin){
    gpio_set_level(pines_salida[pin], 1);
}