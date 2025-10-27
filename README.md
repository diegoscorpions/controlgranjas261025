# 🌾 ControlGranjas261025

**Sistema de Control Inteligente para Granjas basado en ESP32-S3**

| Plataforma Soportada | ESP32-S3 |
|---------------------|----------|
| ESP-IDF Version     | v5.3+    |
| Lenguaje           | C        |

## 📋 Descripción del Proyecto

ControlGranjas261025 es un sistema de automatización para granjas que utiliza el microcontrolador ESP32-S3 para controlar y monitorear diversos aspectos de una granja de manera inteligente y eficiente.

### 🎯 Características Principales

- **Control de Bombas de Agua**: Automatización del sistema de riego
- **Monitoreo de Sensores**: Lectura de sensores de humedad, temperatura y otros parámetros
- **Interfaz PCF8574**: Expansión de E/O mediante I2C
- **Configuración de Pines Flexible**: Sistema configurable de asignación de pines
- **Control Remoto**: Capacidades de conectividad WiFi integradas

## 🛠️ Hardware Requerido

- **ESP32-S3** (placa de desarrollo)
- **PCF8574** (Expansor de E/O I2C)
- **Sensores** (humedad, temperatura, etc.)
- **Relés** para control de bombas y actuadores
- **Fuente de alimentación** adecuada

## 📁 Estructura del Proyecto

```
ControlGranjas261025/
├── CMakeLists.txt                 # Configuración principal de compilación
├── README.md                      # Este archivo
├── .gitignore                     # Archivos excluidos del control de versiones
├── main/                          # Código fuente principal
│   ├── CMakeLists.txt            # Configuración de compilación del main
│   ├── main.c                    # Función principal de la aplicación
│   ├── pcf8574.c                 # Driver para PCF8574
│   ├── pcf8574.h                 # Header del driver PCF8574
│   ├── configpines.c             # Configuración de pines GPIO
│   └── configpines.h             # Header de configuración de pines
├── documentacion/                 # Documentación del proyecto
│   ├── CONFIGURACION_PINES.md    # Documentación detallada de pines
│   └── GIT_GITHUB_INSTRUCCIONES.md # Guía de Git y GitHub
└── .devcontainer/                # Configuración para VS Code Dev Containers
```

## 🚀 Cómo Compilar y Usar

### Prerrequisitos

1. **ESP-IDF v5.3 o superior** instalado
2. **Toolchain** configurado para ESP32-S3
3. **VS Code** con extensión ESP-IDF (recomendado)

### Configuración del Entorno

```bash
# Configurar ESP-IDF (Windows PowerShell)
C:\Users\diego\.espressif\esp-adf\esp-idf\export.ps1

# Verificar configuración
idf.py --version
```

### Compilación

```bash
# Limpiar proyecto (si es necesario)
idf.py fullclean

# Compilar proyecto
idf.py build

# Flashear al ESP32-S3
idf.py flash

# Monitorear salida serial
idf.py monitor
```

### Configuración

```bash
# Abrir configuración del proyecto
idf.py menuconfig
```

## 🔧 Configuración de Hardware

### Conexiones PCF8574 (I2C)

| PCF8574 Pin | ESP32-S3 Pin | Función |
|-------------|--------------|---------|
| VCC         | 3.3V         | Alimentación |
| GND         | GND          | Tierra |
| SDA         | GPIO 8       | Datos I2C |
| SCL         | GPIO 9       | Reloj I2C |

### Configuración de Pines GPIO

Ver archivo: [`documentacion/CONFIGURACION_PINES.md`](documentacion/CONFIGURACION_PINES.md)

## 📚 Documentación

- **[Configuración de Pines](documentacion/CONFIGURACION_PINES.md)**: Detalles completos de la asignación de pines
- **[Guía Git/GitHub](documentacion/GIT_GITHUB_INSTRUCCIONES.md)**: Instrucciones para control de versiones

## 🐛 Solución de Problemas

### Error de Compilación
```bash
# Limpiar y recompilar
idf.py fullclean
idf.py build
```

### Error de Flasheo
```bash
# Verificar puerto y baudrate
idf.py -p COM3 flash

# Si persiste el error, presionar BOOT en la placa durante el flasheo
```

### Error de I2C
- Verificar conexiones SDA/SCL
- Comprobar pull-ups (4.7kΩ recomendado)
- Verificar dirección I2C del PCF8574

## 🔄 Control de Versiones

Este proyecto utiliza Git para control de versiones. Ver [`documentacion/GIT_GITHUB_INSTRUCCIONES.md`](documentacion/GIT_GITHUB_INSTRUCCIONES.md) para comandos detallados.

### Workflow básico:
```bash
git add .
git commit -m "Descripción del cambio"
git push
```

## 📈 Próximas Funcionalidades

- [ ] Interfaz web para control remoto
- [ ] Integración con sensores adicionales
- [ ] Sistema de alertas por WiFi
- [ ] Base de datos para logging
- [ ] Aplicación móvil

## 👨‍💻 Autor

**Diego** - Desarrollo y mantenimiento

## 📄 Licencia

Este proyecto es de código abierto. Ver detalles de licencia en el repositorio.

## 🆘 Soporte

Para soporte técnico y consultas:
- Crear un [Issue en GitHub](https://github.com/diegoscorpions/controlgranjas261025/issues)
- Revisar la documentación en la carpeta [`documentacion/`](documentacion/)

---

⭐ Si este proyecto te resulta útil, ¡dale una estrella en GitHub!

**Proyecto ControlGranjas261025** - Sistema de Automatización Agrícola con ESP32-S3
