#include "MPU6050Sensor.h"

MPU6050Sensor::MPU6050Sensor(){
  //TODO
}

void MPU6050Sensor::setup() {

  Wire.begin();
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void MPU6050Sensor::refreshData() {

  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS,14,true);  // request a total of 14 registers  String AX = String(mpu6050.getAccX());

  acx = Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  acy = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  acz = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  tmp = Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  gyx = Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  gyy = Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  gyz = Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

geometry_msgs::Vector3 MPU6050Sensor::getTranslation(){

  geometry_msgs::Vector3 translation;
  // -3298,    -535,     763,      80,     -20,      44
  translation.x = (acx-3298) / 16384.0;
  translation.y = (acy-535) / 16384.0;
  translation.z = (acz+763) / 16384.0;

  return translation;
}

geometry_msgs::Quaternion MPU6050Sensor::getRotation(){

  geometry_msgs::Quaternion rotation;

  gyx = (gyx+80) / 131.0;
  gyy = (gyy-20) / 131.0;
  gyz = (gyz+44) / 131.0;

  double cy = cos(gyz * 0.5);
  double sy = sin(gyz * 0.5);
  double cp = cos(gyy * 0.5);
  double sp = sin(gyy * 0.5);
  double cr = cos(gyx * 0.5);
  double sr = sin(gyx * 0.5);

  rotation.w = cy * cp * cr + sy * sp * sr;
  rotation.x = cy * cp * sr - sy * sp * cr;
  rotation.y = sy * cp * sr + cy * sp * cr;
  rotation.z = sy * cp * cr - cy * sp * sr;

  return rotation;
}
