#include "main.h"

Motor leftDrive(1, MOTOR_GEARSET_18, 0,  MOTOR_ENCODER_DEGREES);
Motor leftDrive1(2, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

Motor rightDrive(9, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);
Motor rightDrive1(10, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

void left(int speed)
{
  leftDrive.move_velocity(speed);
  leftDrive1.move_velocity(speed);
}

void right(int speed)
{
  rightDrive.move_velocity(speed);
  rightDrive1.move_velocity(speed);
}

void driveOP()
{
  int L = controller.get_analog(ANALOG_LEFT_Y);
  int R = controller.get_analog(ANALOG_RIGHT_Y);
//for slower turns
 /*if((L > 10 && R < -10) || (L < -10 && R > 10))
  {
    leftDrive.move(L*.7);
    leftDrive1.move(L*.7);
    rightDrive.move(R*.7);
    rightDrive1.move(R*.7);
  }
  else
  {*/
      leftDrive.move(L);
      leftDrive1.move(L);
      rightDrive.move(R);
      rightDrive1.move(R);
  //}
}
void drive(int speed)
{
  left(speed);
  right(speed);
}
