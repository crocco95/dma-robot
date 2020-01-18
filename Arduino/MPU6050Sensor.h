#ifndef __MPU6050SENSOR__
#define __MPU6050SENSOR__

#define MPU_ADDRESS 0x68  // I2C address of the MPU-6050

#include <math.h>
#include <ros.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Quaternion.h>
#include <Wire.h>

class MPU6050Sensor{

  public:
    MPU6050Sensor();
    void setup();
    void refreshData();
    geometry_msgs::Vector3 getTranslation();
    geometry_msgs::Quaternion getRotation();

  private:

    int16_t acx,acy,acz,tmp,gyx,gyy,gyz;
    long publisher_timer;
};
#endif
