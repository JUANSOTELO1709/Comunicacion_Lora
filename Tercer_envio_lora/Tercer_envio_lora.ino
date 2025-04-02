#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include "LoRa_E32.h"
#include <SoftwareSerial.h>

// Inicializar los sensores y LoRa
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;
SoftwareSerial mySerial(10, 11); // RX, TX
LoRa_E32 e32ttl(&mySerial, 5, 7, 8); // M0, M1, AUX

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(100);

  // Inicializar el BME280
  if (!bme.begin(0x76)) {
    Serial.println("Error: BME280 no detectado");
    while (1);
  }

  // Inicializar el MPU6050
  if (!mpu.begin()) {
    Serial.println("Error: MPU6050 no detectado");
    while (1);
  }

  // Configuración del MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Inicializar LoRa
  e32ttl.begin();
  Serial.println("Sensores y LoRa listos");
}

void loop() {
  // Leer datos del BME280
  float temp = bme.readTemperature();
  float presion = bme.readPressure() / 100.0; // Convertir a hPa
  float humedad = bme.readHumidity();

  // Leer datos del MPU6050
  sensors_event_t accel, gyro, tempEvent;
  mpu.getEvent(&accel, &gyro, &tempEvent);

  // Crear mensaje corto para evitar sobrepasar el límite del LoRa
  String mensaje = String(temp, 1) + "," + 
                   String(presion, 0) + "," + 
                   String(humedad, 0) + "," + 
                   String(accel.acceleration.x, 1) + "," + 
                   String(accel.acceleration.y, 1) + "," + 
                   String(accel.acceleration.z, 1) + "," + 
                   String(gyro.gyro.x, 1) + "," + 
                   String(gyro.gyro.y, 1) + "," + 
                   String(gyro.gyro.z, 1);

  // Enviar mensaje mediante LoRa
  ResponseStatus rs = e32ttl.sendMessage(mensaje);

  // Mostrar datos en el monitor serie
  Serial.println("Enviando por LoRa:");
  Serial.println(mensaje);
  Serial.print("Estado de transmisión: ");
  Serial.println(rs.getResponseDescription());

  delay(50); // Esperar 1 segundo entre lecturas
}
