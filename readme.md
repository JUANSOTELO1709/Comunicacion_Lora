### Comunicacion transmision


3 EJEMPLOS DE TRANSMISOR CON 
LORA E32


# Proyecto 1: PRUEBA_LORA
## Lectura de configuración del módulo LoRa E32 con Arduino

Este proyecto tiene como objetivo inicializar el módulo **LoRa E32** y leer su configuración mediante un Arduino y la librería `LoRa_E32`. Se utiliza la comunicación serial por software (SoftwareSerial) para establecer el enlace entre el Arduino y el módulo LoRa.

## 📦 Requisitos

- Arduino Uno, Nano, o similar
- Módulo LoRa E32 (como el E32-915T20D o similar)
- Librería `LoRa_E32` de `xreef`
- Cables Dupont
- Conexiones adecuadas de energía para el módulo (3.3V o 5V según la versión)

## 🔌 Diagrama de conexión

| Arduino | Módulo LoRa E32 |
|--------|------------------|
| Pin 10 (TX) | RX |
| Pin 11 (RX) | TX |
| 3.3V o 5V    | VCC |
| GND          | GND |
| (opcional) D2 | M0 |
| (opcional) D3 | M1 |

> **Nota:** El módulo E32 debe estar en **modo de configuración** para poder leer o escribir parámetros. Esto se logra ajustando los pines M0 y M1 a nivel lógico ALTO o BAJO según el modo deseado. En este ejemplo, se asume que el módulo ya está en modo correcto para lectura de configuración.

## 🧰 Librerías necesarias

Instalar la librería `LoRa_E32` de xreef desde el Administrador de Librerías de Arduino.

## 📄 Descripción del código

Este programa realiza lo siguiente:

1. Inicializa la comunicación Serial con el PC y con el módulo LoRa mediante `SoftwareSerial`.
2. Intenta detectar el módulo E32.
3. Si es exitoso, obtiene su configuración interna.
4. Muestra por el monitor serie los siguientes parámetros:
   - Dirección alta y baja del módulo (ADDH y ADDL)
   - Canal de comunicación (CHAN)
   - Velocidad del aire (Air Data Rate)
   - Velocidad UART
   - Paridad UART
   - Corrección de errores (FEC)
   - Modo de transmisión fija (Fixed Transmission)

## ▶️ Ejecución

1. Sube el código al Arduino.
2. Abre el Monitor Serial a 9600 baudios.
3. Observa la información leída del módulo LoRa.

## 📌 Ejemplo de salida esperada
   -Iniciando prueba de conexión...
   
   -Módulo E32 detectado correctamente.
   
   -Obteniendo configuración...

-Configuración del módulo E32:


-Dirección HIGH (ADDH): 0


-Dirección LOW (ADDL): 1

-Canal (CHAN): 23

-Velocidad del aire (Air Data Rate): 2

-Velocidad UART (UART Baud Rate): 3

-Paridad UART (UART Parity): 0

-Corrección de errores (FEC): 1

-Modo de transmisión fija (Fixed Transmission): 0

-Configuración obtenida exitosamente.


