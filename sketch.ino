#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// -------- MATRIX --------
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 5

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// -------- MPU --------
Adafruit_MPU6050 mpu;

float posX = 3.5;
float posY = 3.5;

void setup() {
  Serial.begin(115200);

  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 8);
  mx.clear();

  Wire.begin();  // nutzt 21 (SDA) und 22 (SCL)

  if (!mpu.begin()) {
    Serial.println("MPU6050 nicht gefunden!");
    while (1);
  }

  Serial.println("MPU6050 bereit!");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float x = a.acceleration.x;
  float y = a.acceleration.y;

  // Geschwindigkeit einstellen
  posX += x * 0.02;
  posY += y * 0.02;

  posX = constrain(posX, 0, 7);
  posY = constrain(posY, 0, 7);

  mx.clear();
  mx.setPoint((int)posY, (int)posX, true);

  delay(40);
}