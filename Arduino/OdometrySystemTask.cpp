#include "OdometrySystemTask.h"

char base_link[] = "/base_link";
char odom[] = "/odom";

/* START SINGLETON */
static OdometrySystemTask* OdometrySystemTask::instance = 0;

OdometrySystemTask::OdometrySystemTask(){
  nh.initNode();
  broadcaster.init(nh);

  //mpu6050Sensor = new MPU6050Sensor();
}

static OdometrySystemTask* OdometrySystemTask::getInstanceOf(){
  if (instance == 0) {
    instance = new OdometrySystemTask();
  }
  return instance;
}
/* END SINGLETON */

void OdometrySystemTask::init(int period){
  Task::init(period);
}

void OdometrySystemTask::tick(){

  mpu6050Sensor->refreshData();

  /*// tf odom->base_link
  t.header.frame_id = odom;
  t.child_frame_id = base_link;

  t.transform.translation.x = mpu6050Sensor->getAccX();
  t.transform.translation.y = mpu6050Sensor->getAccY();
  t.transform.translation.z = mpu6050Sensor->getAccZ();

  t.transform.rotation.x = mpu6050Sensor->getRotX();
  t.transform.rotation.y = mpu6050Sensor->getRotY();
  t.transform.rotation.z = mpu6050Sensor->getRotZ();
  t.transform.rotation.w = 1.0;

  t.header.stamp = nh.now();

  t.transform.rotation = tf::createQuaternionFromYaw(theta);
  t.header.stamp = nh.now();*/

  broadcaster.sendTransform(t);
  nh.spinOnce();
}
