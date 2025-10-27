/*
 * =================================================================
 * ARCHIVO DE CABECERA PARA MANEJO DE EXPANSORES PCF8574/PCF8575
 * =================================================================
 * 
 * 
 * Dispositivos instalados:
 * - PCF8574: Expansor de 8 bits (1 byte)
 * - PCF8575: Expansor de 16 bits (2 bytes)
 * - DS3231: Reloj de tiempo real (no implementado de momento)
 * 
 */

#ifndef PCF8574_H              
#define PCF8574_H              

/* =================================================================
 * ARCHIVOS DE CABECERA INCLUIDOS
 * ================================================================= */

#include "configpines.h"       // Incluye definiciones de pines GPIO (SDA, SCL)

#include "driver/i2c_master.h" // API I2C master de ESP-IDF v5.4
                              // Proporciona: i2c_master_bus_add_device(), i2c_master_receive(), etc.

#include "esp_err.h"          // Tipos de error estándar de ESP-IDF
                              // Proporciona: esp_err_t, ESP_OK, ESP_FAIL, etc.

/* =================================================================
 * CONFIGURACIÓN DEL BUS I2C
 * =================================================================
 * Configuramos el bus I2C 
 */

/* Puerto I2C a utilizar */
#define I2C_MASTER_NUM I2C_NUM_0          // puerto principal I2C del ESP32

/* Velocidad de comunicación */          
#define I2C_MASTER_FREQ_HZ 100000         // Frecuencia: 100 kHz (velocidad estándar I2C)
                                         

/* Configuración de buffers (no se están usando en esta version de ESP-IDF) */       
#define I2C_MASTER_TX_BUF_DISABLE 0       
#define I2C_MASTER_RX_BUF_DISABLE 0      

/* Timeout de error comunicaciones */       
#define I2C_MASTER_TIMEOUT_MS 1000        // Tiempo máximo de espera: 1000ms (1 segundo)
                                        

/* =================================================================
 * DIRECCIONES I2C DE DISPOSITIVOS
 * =================================================================
 * Direcciones de 7 bits de los dispositivos en el bus I2C
 */

/* Expansores de E/S */
#define PCF8574_ADDR    0x20              // Dirección del PCF8574 (8 bits)
                                         

#define PCF8575_ADDR    0x27             // Dirección del PCF8575 (16 bits)  
                                         

/* Reloj de tiempo real (para uso futuro) */
#define DS3231_ADDR     0x68              // Dirección fija del DS3231 RTC


/* =================================================================
 * DECLARACIONES DE FUNCIONES PÚBLICAS
 * =================================================================
 */

/* ==================== FUNCIÓN DE INICIALIZACIÓN ==================== */


esp_err_t inicializaI2C(void);                      /* Inicializar bus I2C */

/* ==================== FUNCIONES DE LECTURA DE EXPANSORES ==================== */


esp_err_t leer_pcf8574(uint8_t addr, uint8_t *data);     // CORREGIDO: esp_err_t


esp_err_t leer_pcf8575(uint8_t addr, uint16_t *data);    // CORREGIDO: esp_err_t


void leerExpansor(int numExpansor);


void leerExpansores(void);



#endif // PCF8574_H              

/*
 * =================================================================
 * EJEMPLO DE USO TÍPICO
 * =================================================================
 * 
 * #include "pcf8574.h"
 * 
 * void app_main(void) {
 *     // Inicializar I2C
 *     if (inicializaI2C() != ESP_OK) {
 *         printf("Error inicializando I2C\n");
 *         return;
 *     }
 * 
 *     // Leer expansor específico
 *     uint8_t estado_pcf8574;
 *     if (leer_pcf8574(PCF8574_ADDR, &estado_pcf8574) == ESP_OK) {
 *         printf("PCF8574 estado: 0x%02X\n", estado_pcf8574);
 *     }
 * 
 *     // Leer todos los expansores
 *     leerExpansores();
 * }
 */