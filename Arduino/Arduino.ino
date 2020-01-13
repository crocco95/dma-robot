/* START LIBRARIES */
#include "Scheduler.h"
#include "OdometrySystemTask.h"
/* END LIBRARIES */

/* START GLOBAL VARS */
Scheduler sched(5);
/* END GLOBAL VARS */

void setup() {

  Serial.begin(57600); //Setup Serial
  sched.init(5);  //Setup scheduler

  OdometrySystemTask* odomTask = OdometrySystemTask::getInstanceOf();
  odomTask->init(1);
  sched.addTask(odomTask);
}

void loop(){
  sched.schedule();
}
