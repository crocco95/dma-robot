#ifndef __ODOMETRY_SYSTEM_TASK__
#define __ODOMETRY_SYSTEM_TASK__

  /* START LIBRARIES */
  #include "Arduino.h"
  #include "Task.h"
  #include "MPU6050Sensor.h"

  #include <ros.h>
  #include <ros/time.h>
  #include <tf/tf.h>
  #include <tf/transform_broadcaster.h>
  /* END LIBRARIES */

  class OdometrySystemTask : public Task {

    public:
      static OdometrySystemTask* getInstanceOf(); // Method to get singleton istance or create one if it
                      // does not exists
      void init(int period);

    private:
      static OdometrySystemTask* instance; //Istance

      MPU6050Sensor* mpu6050Sensor;

      ros::NodeHandle  nh;

      geometry_msgs::TransformStamped t;
      tf::TransformBroadcaster broadcaster;

      double x;
      double y;
      double theta;

      OdometrySystemTask(); //Costructor
      void tick();
  };

#endif
