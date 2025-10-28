#ifndef __PID_H__
#define __PID_H__

#include <stdint.h>
#include <stdio.h>

typedef struct PID {
  float cycle;
  float kp, ki, kd;
  float setpoint;
  float last_e_n;
  float last_p_n;
  float last_u_n;
} PID;

void pid_init(
  PID *pid,
  float cycle,
  float kp, float ki, float kd,
  float setpoint
);

float pid_iter(
  PID *pid,
  float input
);

float pid_reset_setpoint(
  PID *pid,
  float setpoint
);

#endif	// __PID_H__
