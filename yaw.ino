#include <Wire.h>
const int MPU6050_ADDR = 0x68;
const int ACCEL_ZOUT_H = 0x3F;
const int GYRO_ZOUT_H = 0x47;
const int PWR_MGMT_1 = 0x6B;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(PWR_MGMT_1);
    Wire.write(0x00);
    Wire.endTransmission();
}

void loop() {
    int16_t az = readMPU6050Data(ACCEL_ZOUT_H);
    int16_t gz = readMPU6050Data(GYRO_ZOUT_H);
    
    Serial.print("Z-axis acceleration:\t");
    Serial.print(az);
    Serial.print("\tZ-axis gyroscope:\t");
    Serial.println(gz);
    delay(100);
}

int16_t readMPU6050Data(int regAddr) {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(regAddr);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, 2, true);  
    int16_t highByte = Wire.read();
    int16_t lowByte = Wire.read();   
    return (highByte << 8) | lowByte;
}
