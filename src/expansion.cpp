#include "main.h"

Motor rightTower(20, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);
Motor leftTower(11, MOTOR_GEARSET_36, 0, MOTOR_ENCODER_DEGREES);

void towers(int power)
{
  rightTower.move_velocity(power);
  leftTower.move_velocity(power);
}
void towersSet(int pos)
{
  rightTower.move_relative(pos, 100);
  leftTower.move_relative(pos, 100);
}

void expansionOP1()
{
  static int set;
  if(controller.get_digital(DIGITAL_L1))
  {
    set++;
  }
  else if(controller.get_digital(DIGITAL_L2))
  {
    set--;
  }
  printf("%d\n", set);
  towersSet(set);
}

void expansionOP2()
{
  int error = rightTower.get_position()-leftTower.get_position();
  //  printf("%d\n", error);
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
void expansionOP(){
  int power;
  if(controller.get_digital(DIGITAL_L1))
  {
    power=50;
  }
  else if(controller.get_digital(DIGITAL_L2))
  {
    power=-50;
  }
  else
  {
    power=0;
  }

  float Kp = 0.8;
  float Ki = 0.05;
  float Kd = 0.025;

  int error = 0;
  int lastError = 0;
  float integral = 0;
  float derivative = 0;

  int rightPower = 0;
  int leftPower = power;

  int ls = leftTower.get_position();
  int rs = rightTower.get_position();

   error = ls-rs;
    integral = integral + error;

    derivative = error - lastError;

    if(abs(ls - rs) < 2 || abs(ls-rs) > 30)
    integral = 0;

    rightPower = leftPower + (error * Kp) + (integral * Ki) + (derivative * Kd);

    rightTower.move_velocity(rightPower);
    leftTower.move_velocity(leftPower);
  //___int64_t_defined  straight(speed);
    lastError = error;
  //  printf("%d\n", error);
    delay(20);

}
