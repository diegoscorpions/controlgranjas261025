# 🐰 ControlGranjas261025

**Sistema Automático de Alimentación para Conejos basado en ESP32-S3**

| Plataforma Soportada | ESP32-S3 |
|---------------------|----------|
| ESP-IDF Version     | v5.3+    |
| Lenguaje           | C        |
| Aplicación         | Alimentación Automática de Conejos |

## 📋 Descripción del Proyecto

ControlGranjas261025 es un sistema automático de alimentación para conejos que utiliza el microcontrolador ESP32-S3 para controlar motores de sinfín que transportan alimento desde tolvas hasta comederos de manera inteligente y segura.

### 🎯 Funcionalidad Principal

**Sistema de Alimentación Automática:**
- **Motores de Sinfín**: Cada salida controla un motor que mueve un sinfín para transportar comida
- **Transporte de Alimento**: Desplaza la comida desde la tolva hasta el comedero
- **Control Inteligente**: Sistema de sensores para detectar niveles y condiciones
- **Seguridad Integrada**: Múltiples sistemas de protección y alarmas

### 🔧 Componentes del Sistema

#### **Actuadores:**
- **Motores de Sinfín**: Transporte automático de alimento desde tolva a comedero

#### **Sensores de Entrada:**
- **Sensor de Tolva (Acopio)**: Detecta presencia de alimento en la tolva
- **Sensor Comedero Lleno**: Detecta cuando el comedero está lleno
- **Sensor de Paleta (Emergencia)**: Alarma por rebase del nivel del comedero
- **Sensor Térmico**: Protección térmica del sistema
- **Modo Manual/Automático**: Selección de modo de operación

#### **Sistemas de Seguridad:**
- **Timeout de 5 minutos**: Para el sistema si no se activa sensor de comedero lleno
- **Parada por tolva vacía**: El sistema se detiene si no hay material
- **Parada por emergencia de paleta**: Se detiene si se activa el sensor de paleta
- **Protección térmica**: Parada automática por salto térmico

## � Lógica de Control del Sistema

### **Ciclo Normal de Alimentación:**

1. **Inicio del Ciclo**: 
   - Verificación de condiciones iniciales (tolva con material, sin alarmas)
   - Activación del motor de sinfín correspondiente

2. **Transporte de Alimento**:
   - El motor mueve el sinfín para transportar comida desde la tolva
   - Monitoreo continuo de sensores de seguridad

3. **Finalización del Ciclo**:
   - **Condición Normal**: Se para cuando se activa el sensor de "comedero lleno"
   - **Timeout**: Se para automáticamente después de 5 minutos si no se llena el comedero

### **Condiciones de Parada de Emergencia:**

| Condición | Sensor | Acción | Alarma |
|-----------|--------|--------|---------|
| **Tolva Vacía** | Sensor de Tolva | ⏹️ Parada Inmediata | 🚨 Sí |
| **Emergencia Paleta** | Sensor de Paleta | ⏹️ Parada Inmediata | 🚨 Sí |
| **Protección Térmica** | Sensor Térmico | ⏹️ Parada Inmediata | 🚨 Sí |
| **Timeout 5 min** | Temporizador | ⏹️ Parada Automática | 🚨 Sí |
| **Comedero Lleno** | Sensor Comedero | ✅ Parada Normal | ❌ No |

### **Modos de Operación:**

- **🔄 Modo Automático**: Funcionamiento autónomo según programación
- **🕹️ Modo Manual**: Control manual del operador

## �🛠️ Hardware Requerido

### **Componentes Principales:**
- **ESP32-S3** (placa de desarrollo)
- **PCF8574** (Expansor de E/O I2C)
- **Motores de Sinfín** (para transporte de alimento)
- **Relés de Potencia** (control de motores)

### **Sensores:**
- **Sensores de Nivel** (tolva y comedero)
- **Sensor de Paleta** (emergencia por rebase)
- **Sensor Térmico** (protección térmica)
- **Selectores Manual/Automático**

### **Sistema de Alimentación:**
- **Tolvas de Almacenamiento** (con sensores de acopio)
- **Comederos** (con sensores de nivel)
- **Sinfines de Transporte** (accionados por motores)

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

## 📊 Especificaciones Técnicas

### **Entradas del Sistema (Sensores):**
| Entrada | Función | Tipo | Acción |
|---------|---------|------|---------|
| **Tolva** | Detección de material en tolva | Digital | Parada si vacía |
| **Comedero Lleno** | Nivel óptimo de comedero | Digital | Parada normal |
| **Emergencia Paleta** | Rebase de nivel crítico | Digital | Parada de emergencia |
| **Salto Térmico** | Protección térmica | Digital | Parada de emergencia |
| **Manual** | Selector de modo manual | Digital | Cambio de modo |
| **Automático** | Selector de modo automático | Digital | Cambio de modo |

### **Salidas del Sistema (Actuadores):**
| Salida | Función | Tipo | Control |
|--------|---------|------|---------|
| **Motor Sinfín 1-N** | Transporte de alimento | Relé/Digital | ON/OFF por comedero |
| **Alarma Visual** | Indicación de estado/error | Digital | Según condición |
| **Alarma Sonora** | Notificación de emergencia | Digital | En condiciones de alarma |

### **Parámetros de Configuración:**
- **Timeout de Alimentación**: 5 minutos máximo por ciclo
- **Número de Comederos**: Configurable (1-N salidas)
- **Frecuencia de Monitoreo**: Tiempo real continuo
- **Modo por Defecto**: Automático

## 🚨 Sistema de Alarmas

### **Alarmas Críticas (Parada Inmediata):**
- 🔴 **Tolva Vacía**: Sin material para alimentar
- 🔴 **Emergencia Paleta**: Rebase crítico del comedero
- 🔴 **Protección Térmica**: Sobrecalentamiento del sistema
- 🔴 **Timeout**: Motor funcionando >5 min sin llenar comedero

### **Estados de Operación:**
- 🟢 **Normal**: Sistema funcionando correctamente
- 🟡 **Alimentando**: Motor en funcionamiento
- 🔴 **Alarma**: Condición de emergencia detectada
- ⚪ **Parado**: Sistema detenido (manual o por alarma)

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

### **Fase 1 - Sistema Básico (Actual):**
- [x] Control de motores de sinfín
- [x] Monitoreo de sensores de seguridad
- [x] Sistema de alarmas por emergencias
- [x] Timeout de protección (5 minutos)
- [x] Modo manual/automático

### **Fase 2 - Mejoras Planificadas:**
- [ ] Interfaz web para monitoreo remoto
- [ ] Programación de horarios de alimentación
- [ ] Registro histórico de alimentaciones
- [ ] Notificaciones vía WiFi/SMS
- [ ] Control multi-granja

### **Fase 3 - Funcionalidades Avanzadas:**
- [ ] Integración con sensores de peso
- [ ] Control de raciones por animal
- [ ] Análisis predictivo de consumo
- [ ] Aplicación móvil
- [ ] Integración IoT completa

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

**Proyecto ControlGranjas261025** - Sistema Automático de Alimentación para Conejos con ESP32-S3  
*Automatización inteligente para granjas cunícolas con seguridad integrada*
