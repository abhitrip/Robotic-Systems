#ifndef MOTOR
#define MOTOR

void motor_init(float t);
void motor_clockwise();
void motor_anticlockwise();
int motor_rotate();
int scan_at_head();

#endif