#include <SoftwareSerial.h>
#include "LoRa_E32.h"

// Definir pines de conexión del LoRa (TX y RX)
#define TX_PIN 11  // Pin TX del módulo LoRa (conectado a RX del Arduino)
#define RX_PIN 10  // Pin RX del módulo LoRa (conectado a TX del Arduino)

// Crear SoftwareSerial para la comunicación con el módulo LoRa
SoftwareSerial LoRaSerial(RX_PIN, TX_PIN);

// Crear objeto LoRa con SoftwareSerial
LoRa_E32 lora(&LoRaSerial);

void setup() {
    Serial.begin(9600);
    LoRaSerial.begin(9600); // Inicializar la comunicación con el LoRa

    Serial.println("Iniciando prueba de conexión...");

    if (lora.begin()) {
        Serial.println("Módulo E32 detectado correctamente.");
    } else {
        Serial.println("Error al inicializar el módulo LoRa.");
        while (1);
    }

    // Leer configuración del módulo
    Serial.println("Obteniendo configuración...");
    ResponseStructContainer c = lora.getConfiguration();

    // Verificar si se pudo obtener la configuración
    if (c.status.code != 1) {
        Serial.println("Error al obtener la configuración del módulo.");
        return;
    }

    // Extraer los parámetros del módulo
    Configuration configuration = *(Configuration*) c.data;

    Serial.println("Configuración del módulo E32:");
    Serial.print("Dirección HIGH (ADDH): ");
    Serial.println(configuration.ADDH, HEX);
    Serial.print("Dirección LOW (ADDL): ");
    Serial.println(configuration.ADDL, HEX);
    Serial.print("Canal (CHAN): ");
    Serial.println(configuration.CHAN, DEC);
    Serial.print("Velocidad del aire (Air Data Rate): ");
    Serial.println(configuration.SPED.airDataRate, DEC);
    Serial.print("Velocidad UART (UART Baud Rate): ");
    Serial.println(configuration.SPED.uartBaudRate, DEC);
    Serial.print("Paridad UART (UART Parity): ");
    Serial.println(configuration.SPED.uartParity, DEC);
    Serial.print("Corrección de errores (FEC): ");
    Serial.println(configuration.OPTION.fec, DEC);
    Serial.print("Modo de transmisión fija (Fixed Transmission): ");
    Serial.println(configuration.OPTION.fixedTransmission, DEC);

    Serial.println("Configuración obtenida exitosamente.");
}

void loop() {
    // No es necesario ejecutar nada en el loop
}
