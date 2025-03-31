#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Arduino.h"
#include "LoRa_E32.h"
#include <SoftwareSerial.h>

// Inicializar los sensores y LoRa
Adafruit_BME280 bme;
SoftwareSerial mySerial(11, 10);
LoRa_E32 e32ttl(&mySerial, 5, 7, 8);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(100);

  // Inicializar el BME280
  if (!bme.begin(0x76)) {
    Serial.println("Error al inicializar el BME280");
    while (1);
  }

  // Inicializar LoRa
  e32ttl.begin();
  Serial.println("Sensores y LoRa listos");
}

void loop() {
  // Leer datos del BME280
  float temp = bme.readTemperature();
  float presion = bme.readPressure() / 100.0; // Convertir a hPa
  float humedad = bme.readHumidity();

  // Crear mensaje para transmitir
  String mensaje = "Temp: " + String(temp, 1) + "C, Pres: " + String(presion, 0) + "hPa, Hum: " + String(humedad, 0) + "%";

  // Enviar mensaje mediante LoRa
  ResponseStatus rs = e32ttl.sendFixedMessage(0, 3, 0x04, mensaje);

  // Mostrar datos en el monitor serie
  Serial.println("Enviando: ");
  Serial.println(mensaje);
  Serial.println(rs.getResponseDescription());

  delay(500); // Leer cada medio segundo
}