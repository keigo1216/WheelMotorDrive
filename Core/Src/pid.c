#include "pid.h"

void pid_init(
  PID *pid,
  float cycle,
  float kp, float ki, float kd,
  float setpoint
) {

  pid->cycle = cycle;
  pid->kp = kp;
  pid->ki = ki;
  pid->kd = kd;
  pid->setpoint = setpoint;
  pid->integral=0;
  pid->last_error=0;
}

float pid_iter(
  PID *pid,
  float input
) {

  float error = pid->setpoint - input;
  pid->integral += error*(pid->cycle);

  if ((pid->ki)*(pid->integral) > 40) {
      pid->integral = 40 / (pid->ki);
  }
  if ((pid->ki)*(pid->integral) < -40) {
      pid->integral = -40 / (pid->ki);
  }

  float derivative = (error - pid->last_error) / (pid->cycle);
  float output = (pid->kp)*error + (pid->ki)*(pid->integral) + (pid->kd)*derivative;

  // update last error
  pid->last_error = error;

  return output;
}

float pid_reset_setpoint(
  PID *pid,
  float setpoint
){
  pid->setpoint=setpoint;
  pid->integral = 0;
  pid->last_error = 0;
}
