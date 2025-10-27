#include "pcf8574.h"                    // Incluye definiciones propias del módulo
#include "driver/i2c_master.h"          // API I2C de ESP-IDF v5.4
#include "esp_log.h"                    // Sistema de logging
#include "esp_err.h"                    // Códigos de error
#include "freertos/FreeRTOS.h"          // Núcleo del RTOS
#include "freertos/task.h"              // Funciones de tareas (delays)

static const char* TAG = "Expansores PCF8574";  // Tag para los logs
static i2c_master_bus_handle_t bus_handle;       // Handle global del bus I2C

esp_err_t inicializaI2C(void){
    ESP_LOGI(TAG, "🔧 Iniciando I2C...");       // Log informativo

    i2c_master_bus_config_t i2c_mst_config = {  // Estructura de configuración I2C
        .clk_source = I2C_CLK_SRC_DEFAULT,      // Reloj por defecto del sistema
        .i2c_port = I2C_MASTER_NUM,             // Puerto I2C (I2C_NUM_0)
        .scl_io_num = SCL,                      // Pin GPIO para clock (SCL)
        .sda_io_num = SDA,                      // Pin GPIO para datos (SDA)
        .glitch_ignore_cnt = 7,                 // Filtro anti-ruido (7 ciclos)
        .flags.enable_internal_pullup = true,  // Activar resistencias pull-up internas
    };

    esp_err_t ret = i2c_new_master_bus(&i2c_mst_config, &bus_handle);  // Crear bus I2C
    if (ret != ESP_OK) {                                               // Si hay error
        ESP_LOGE(TAG, "❌ Error creando bus I2C: %s", esp_err_to_name(ret));  // Log error
        return ret;                             // Retornar código de error
    }

    ESP_LOGI(TAG, "✅ I2C inicializado OK");                          // Confirmar éxito
    ESP_LOGI(TAG, "📌 SDA: GPIO_%d, SCL: GPIO_%d", SDA, SCL);         // Mostrar pines usados
    return ret;                                 // Retornar ESP_OK
}

esp_err_t leer_pcf8574(uint8_t addr, uint8_t *data) {
    i2c_device_config_t dev_cfg = {             // Configuración del dispositivo PCF8574
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,  // Dirección de 7 bits
        .device_address = addr,                 // Dirección I2C del PCF8574
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,     // Velocidad de comunicación (100kHz)
    };

    i2c_master_dev_handle_t dev_handle;         // Handle del dispositivo
    esp_err_t ret = i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle);  // Añadir dispositivo al bus
    if (ret != ESP_OK) {                        // Si falla la adición
        ESP_LOGE(TAG, "❌ Error añadiendo dispositivo 0x%02X", addr);  // Log error
        return ret;                             // Retornar error
    }

    ret = i2c_master_receive(dev_handle, data, 1, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));  // Leer 1 byte del PCF8574
    
    if (ret == ESP_OK) {                        // Si la lectura fue exitosa
        ESP_LOGI(TAG, "📥 PCF8574 (0x%02X): 0x%02X (0b%08b)", addr, *data, *data);  // Mostrar datos en hex y binario
    } else {                                    // Si hubo error en la lectura
        ESP_LOGE(TAG, "❌ Error leyendo PCF8574 0x%02X: %s", addr, esp_err_to_name(ret));  // Log error
    }

    i2c_master_bus_rm_device(dev_handle);       // Remover dispositivo del bus (limpiar recursos)
    return ret;                                 // Retornar resultado de la operación
}

esp_err_t leer_pcf8575(uint8_t addr, uint16_t *data) {
    i2c_device_config_t dev_cfg = {             // Configuración del dispositivo PCF8575
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,  // Dirección de 7 bits
        .device_address = addr,                 // Dirección I2C del PCF8575
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,     // Velocidad de comunicación
    };

    i2c_master_dev_handle_t dev_handle;         // Handle del dispositivo
    esp_err_t ret = i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle);  // Añadir dispositivo al bus
    if (ret != ESP_OK) {                        // Si falla la adición
        ESP_LOGE(TAG, "❌ Error añadiendo dispositivo 0x%02X", addr);  // Log error
        return ret;                             // Retornar error
    }

    uint8_t buffer[2];                          // Buffer para 2 bytes del PCF8575
    ret = i2c_master_receive(dev_handle, buffer, 2, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));  // Leer 2 bytes
    
    if (ret == ESP_OK) {                        // Si la lectura fue exitosa
        *data = (buffer[1] << 8) | buffer[0];   // Combinar bytes: byte alto<<8 + byte bajo
        ESP_LOGI(TAG, "📥 PCF8575 (0x%02X): 0x%04X (0b%016b)", addr, *data, *data);  // Mostrar datos 16-bit
    } else {                                    // Si hubo error
        ESP_LOGE(TAG, "❌ Error leyendo PCF8575 0x%02X: %s", addr, esp_err_to_name(ret));  // Log error
    }

    i2c_master_bus_rm_device(dev_handle);       // Limpiar recursos
    return ret;                                 // Retornar resultado
}

void leerExpansor(int numExpansor){
    ESP_LOGI(TAG, "📖 Leyendo expansor %d...", numExpansor);  // Log del expansor a leer
    
    switch(numExpansor) {                       // Seleccionar tipo de expansor según número
        case 0: {                               // Expansor 0 = PCF8574
            uint8_t data8;                      // Variable para datos de 8 bits
            if (leer_pcf8574(PCF8574_ADDR, &data8) == ESP_OK) {  // Leer PCF8574 en dirección 0x20
                ESP_LOGI(TAG, "🔍 Expansor 0 (PCF8574): 8 pines = 0x%02X", data8);  // Mostrar estado general
                
                for(int pin = 0; pin < 8; pin++) {              // Recorrer cada pin (0-7)
                    bool estado = (data8 >> pin) & 0x01;        // Extraer bit del pin: desplazar y enmascarar
                    ESP_LOGI(TAG, "  📌 Pin %d: %s", pin, estado ? "HIGH" : "LOW");  // Mostrar estado del pin
                }
            }
            break;                              // Salir del case 0
        }
        
        case 1: {                               // Expansor 1 = PCF8575
            uint16_t data16;                    // Variable para datos de 16 bits
            if (leer_pcf8575(PCF8575_ADDR, &data16) == ESP_OK) {  // Leer PCF8575 en dirección 0x21
                ESP_LOGI(TAG, "🔍 Expansor 1 (PCF8575): 16 pines = 0x%04X", data16);  // Estado general
                
                for(int pin = 0; pin < 16; pin++) {             // Recorrer cada pin (0-15)
                    bool estado = (data16 >> pin) & 0x01;       // Extraer bit del pin
                    ESP_LOGI(TAG, "  📌 Pin %d: %s", pin, estado ? "HIGH" : "LOW");  // Estado del pin
                }
            }
            break;                              // Salir del case 1
        }
        
        default:                                // Número de expansor inválido
            ESP_LOGW(TAG, "⚠️ Número de expansor inválido: %d (solo 0-1)", numExpansor);  // Warning
            break;                              // Salir del default
    }
}

void leerExpansores(void){
    ESP_LOGI(TAG, "📖 === Leyendo todos los expansores ===");  // Log inicio secuencia
    for(int i = 0; i < 2; i++){             // Bucle para 2 expansores (0 y 1)
        leerExpansor(i);                    // Leer expansor i
        vTaskDelay(pdMS_TO_TICKS(100));     // Pausa de 100ms entre lecturas
    }
    ESP_LOGI(TAG, "✅ Lectura completa");   // Log fin secuencia
}