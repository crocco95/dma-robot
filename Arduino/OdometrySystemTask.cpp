#include "OdometrySystemTask.h"

char base_link[] = "/base_link";
char odom[] = "/odom";

/* START SINGLETON */
static OdometrySystemTask* OdometrySystemTask::instance = 0;

OdometrySystemTask::OdometrySystemTask(){
  nh.initNode();
  broadcaster.init(nh);

  mpu6050Sensor = new MPU6050Sensor();
  mpu6050Sensor->setup();
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

  t.header.frame_id = odom;
  t.child_frame_id = base_link;

  t.transform.translation = mpu6050Sensor->getTranslation();
  t.transform.rotation = mpu6050Sensor->getRotation();

  t.header.stamp = nh.now();

  broadcaster.sendTransform(t);
  nh.spinOnce();
}
