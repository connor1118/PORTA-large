#include "main.h"

Motor rightTower(20, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);
Motor leftTower(11, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

void towers(int power)
{
  rightTower.move_velocity(power);
  leftTower.move_velocity(power);
}

void expansionOP()
{
  int error = rightTower.get_position()-leftTower.get_position();
    printf("%d\n", error);
  if(controller.get_digital(DIGITAL_L1))
  {
    towers(200);
  }
  else if(controller.get_digital(DIGITAL_L2))
  {
    towers(-200);
  }
  else
  {
    towers(0);
  }
}
void expansionPID(int distance){
  float Kp = 1.5;
  float Ki = .25;
  float Kd = .5;

  int error = 0;
  int lastError = 0;
  float integral = 0;
  float derivative = 0;

  int rightPower = 0;
  int leftPower = 0;

  if(controller.get_digital(DIGITAL_L1))
  {
    distance++;
  }
  else if(controller.get_digital(DIGITAL_L2))
  {
    distance--;
  }
  else
  {
    towers(0);
  }

  int ls = leftTower.get_position();
  int rs = rightTower.get_position();

  do
  {
   error = ls-rs;
    integral = integral + error;
    if(ls == distance)
      integral = 0;
    derivative = error - lastError;

    rightPower = leftPower + (error * Kp) + (integral * Ki) + (derivative * Kd);

    rightTower.move_velocity(rightPower);
    leftTower.move_velocity(leftPower);
  //___int64_t_defined  straight(speed);
    lastError = error;
    printf("%d\n", error);
    delay(20);
  }
  while(ls < distance);
}
