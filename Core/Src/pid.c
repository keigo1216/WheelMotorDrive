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
  pid->last_e_n = 0;
  pid->last_p_n = 0;
  pid->last_u_n = 0;
}

float pid_iter(
  PID *pid,
  float input
) {
  float e_n = pid->setpoint - input;
  float p_n = e_n - pid->last_e_n;
  float d_n = p_n - pid->last_p_n;
  float delta_u_n_delta_t = pid->kp*p_n + pid->ki*e_n*pid->cycle + pid->kd*d_n;
  float u_n = pid->last_u_n + delta_u_n_delta_t;

  if (u_n > 90) u_n = 90.0;
  if (0 <= u_n && u_n <= 10) u_n = 10.0;
  if (u_n < -90) u_n = -90.0;
  if (-10 <= u_n && u_n < 0) u_n = -10.0;

  pid->last_e_n = e_n;
  pid->last_p_n = p_n;
  pid->last_u_n = u_n;

  return u_n;
//  return output;
}

float pid_reset_setpoint(
  PID *pid,
  float setpoint
){
  pid->setpoint=setpoint;
//  pid->last_e_n = 0;
//  pid->last_p_n = 0;
//  pid->last_u_n = 0;
}
