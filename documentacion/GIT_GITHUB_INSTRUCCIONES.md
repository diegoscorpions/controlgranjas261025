# 📚 Guía de Git y GitHub para ControlGranjas261025

## 🎯 Información del Proyecto
- **Repositorio:** https://github.com/diegoscorpions/controlgranjas261025
- **Rama principal:** `main`
- **Usuario GitHub:** diegoscorpions

---

## 🚀 Comandos Básicos de Git

### ✅ Verificar estado del repositorio
```bash
git status
```
*Muestra qué archivos han cambiado y cuáles están listos para commit*

### ✅ Ver historial de commits
```bash
git log --oneline
```
*Muestra el historial de commits de forma resumida*

### ✅ Ver diferencias en archivos
```bash
git diff
git diff archivo.c  # Ver cambios en un archivo específico
```

---

## 📝 Workflow Diario de Desarrollo

### 1️⃣ Agregar cambios al área de staging
```bash
# Agregar archivos específicos
git add main/hello_world_main.c
git add main/configpines.c main/configpines.h

# Agregar todos los archivos modificados
git add .

# Agregar solo archivos .c y .h
git add *.c *.h
```

### 2️⃣ Hacer commit de los cambios
```bash
# Commit con mensaje descriptivo
git commit -m "Agregar funcionalidad de control de bombas"

# Commit con mensaje más detallado
git commit -m "Implementar lectura de sensores

- Agregar función para leer sensores de humedad
- Configurar pines GPIO para sensores
- Implementar filtros para lecturas estables"
```

### 3️⃣ Subir cambios a GitHub
```bash
# Subir a la rama main
git push

# Primera vez después de crear una nueva rama
git push -u origin nombre-rama
```

---

## 🌿 Trabajo con Ramas (Branches)

### ✅ Crear y cambiar a una nueva rama
```bash
# Crear rama para nueva funcionalidad
git checkout -b feature/sensor-humedad
git checkout -b feature/control-bombas
git checkout -b bugfix/correccion-pines

# Cambiar a una rama existente
git checkout main
git checkout feature/sensor-humedad
```

### ✅ Listar ramas
```bash
git branch          # Ramas locales
git branch -r       # Ramas remotas
git branch -a       # Todas las ramas
```

### ✅ Fusionar ramas
```bash
# Cambiar a main y fusionar la rama feature
git checkout main
git merge feature/sensor-humedad

# Subir los cambios fusionados
git push
```

### ✅ Eliminar ramas
```bash
# Eliminar rama local (después de fusionar)
git branch -d feature/sensor-humedad

# Eliminar rama remota
git push origin --delete feature/sensor-humedad
```

---

## 🔄 Sincronización con GitHub

### ✅ Descargar cambios del repositorio remoto
```bash
# Descargar y fusionar cambios
git pull

# Solo descargar sin fusionar
git fetch
```

### ✅ Ver información del repositorio remoto
```bash
git remote -v
git remote show origin
```

---

## 🛠️ Comandos de Mantenimiento

### ✅ Deshacer cambios
```bash
# Deshacer cambios en un archivo (antes de add)
git checkout -- main/hello_world_main.c

# Quitar archivo del área de staging
git reset main/hello_world_main.c

# Deshacer el último commit (mantiene cambios)
git reset --soft HEAD~1

# Deshacer el último commit (elimina cambios)
git reset --hard HEAD~1
```

### ✅ Ver información detallada
```bash
# Ver qué cambió en un commit específico
git show commit-hash

# Ver historial de un archivo
git log --follow main/hello_world_main.c
```

---

## 📋 Convenciones de Commits

### 🎯 Formato recomendado:
```
tipo: descripción breve

Descripción más detallada si es necesaria
```

### 🏷️ Tipos de commit:
- **feat:** Nueva funcionalidad
- **fix:** Corrección de errores
- **docs:** Cambios en documentación
- **style:** Cambios de formato (no afectan funcionalidad)
- **refactor:** Refactorización de código
- **test:** Agregar o modificar tests
- **chore:** Tareas de mantenimiento

### 📝 Ejemplos:
```bash
git commit -m "feat: agregar control de bomba de agua"
git commit -m "fix: corregir lectura de sensor PCF8574"
git commit -m "docs: actualizar documentación de pines"
git commit -m "refactor: mejorar estructura de funciones de sensores"
```

---

## 🚨 Comandos de Emergencia

### ⚠️ Si cometiste un error y necesitas volver atrás:
```bash
# Ver commits recientes
git log --oneline -10

# Volver a un commit específico (CUIDADO: elimina commits posteriores)
git reset --hard commit-hash

# Crear commit que deshace cambios (más seguro)
git revert commit-hash
```

### ⚠️ Si hay conflictos al hacer merge:
```bash
# Ver archivos con conflictos
git status

# Después de resolver conflictos manualmente:
git add archivo-resuelto.c
git commit -m "Resolver conflictos en archivo-resuelto.c"
```

---

## 📂 Archivos a Ignorar (.gitignore)

### Crear archivo .gitignore para ESP32:
```bash
# Archivos de compilación
build/
sdkconfig.old
.vscode/
*.o
*.a
*.so

# Archivos temporales
*~
.DS_Store
Thumbs.db

# Archivos de depuración
*.log
*.tmp
```

---

## 🔗 Comandos Específicos del Proyecto

### ✅ Configuración inicial (solo una vez):
```bash
git config user.name "Diego Scorpions"
git config user.email "tu-email@ejemplo.com"
```

### ✅ Clonar el repositorio en otra máquina:
```bash
git clone https://github.com/diegoscorpions/controlgranjas261025.git
cd controlgranjas261025
```

### ✅ Workflow típico para ControlGranjas261025:
```bash
# 1. Verificar estado
git status

# 2. Agregar cambios en código ESP32
git add main/
git add CMakeLists.txt
git add sdkconfig

# 3. Commit con descripción clara
git commit -m "feat: implementar control automático de riego"

# 4. Subir a GitHub
git push
```

---

## 🛠️ Solución de Problemas Comunes

### ⚠️ Error: "The source directory does not exist" (CMake)
Si aparece un error como "The source directory 'C:/Users/diego/PantallaGranjas261025' does not exist":

```bash
# 1. Eliminar directorio build completamente
Remove-Item -Recurse -Force build

# 2. Configurar entorno ESP-IDF
C:\Users\diego\.espressif\esp-adf\esp-idf\export.ps1

# 3. Limpiar y reconstruir
idf.py fullclean
idf.py build
```

**Causa:** Referencias a nombres anteriores del proyecto en archivos de configuración.
**Solución:** Limpiar build cache y verificar que no hay referencias al nombre anterior.

### ⚠️ Error: "idf.py no se reconoce"
```bash
# Configurar entorno ESP-IDF antes de usar idf.py
C:\Users\diego\.espressif\esp-adf\esp-idf\export.ps1
```

### ⚠️ Configuración ESP-IDF en cada sesión
```bash
# Siempre ejecutar antes de trabajar con ESP-IDF
C:\Users\diego\.espressif\esp-adf\esp-idf\export.ps1

# Verificar que funciona
idf.py --version
```

## 🆘 Recursos Adicionales

### 📖 Enlaces útiles:
- **Repositorio del proyecto:** https://github.com/diegoscorpions/controlgranjas261025
- **Documentación oficial de Git:** https://git-scm.com/docs
- **GitHub Desktop (interfaz gráfica):** https://desktop.github.com/

### 🎯 Atajos útiles:
```bash
# Ver estado rápido
git status -s

# Commit rápido de todos los cambios
git commit -am "mensaje del commit"

# Ver diferencias de forma resumida
git diff --stat
```

---

## 📅 Checklist Diario

- [ ] `git status` - Verificar qué archivos cambiaron
- [ ] `git add .` - Agregar cambios al staging
- [ ] `git commit -m "mensaje descriptivo"` - Hacer commit
- [ ] `git push` - Subir cambios a GitHub
- [ ] Verificar en GitHub que los cambios se subieron correctamente

---

**💡 Consejo:** Guarda este archivo y mantenlo actualizado con nuevos comandos que vayas aprendiendo durante el desarrollo del proyecto ControlGranjas261025.