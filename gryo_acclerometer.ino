    /*
  GY-521 (MPU6050) 3-Axis Accelerometer-Gyroscope Sensor
  modified on 28 Sep 2020
  by Mohammad Reza Akbari @ Electropeak
  Home

  Based on Adafruit Example
*/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  //Serial.println("");
  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Temperature:");
  Serial.print(temp.temperature);
  Serial.print("\tx-acceleration:");
  Serial.print(a.acceleration.x);
  Serial.print("\ty-acceleration:");
  Serial.print(a.acceleration.y);
  Serial.print("\tz-acceleration:");
  Serial.print(a.acceleration.z);
  Serial.print("\tx-gyro:");
  Serial.print(g.gyro.x);
  Serial.print("\ty-gyro:");
  Serial.print(g.gyro.y);
  Serial.print("\tz-gyro:");
  Serial.println(g.gyro.z);

  delay(10);
  }
