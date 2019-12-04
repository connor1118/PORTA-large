#include "main.h"

Motor rightTower(19, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);
Motor rightTower1(17, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);
Motor leftTower(11, MOTOR_GEARSET_36, 0, MOTOR_ENCODER_DEGREES);
Motor leftTower1(13, MOTOR_GEARSET_36, 0, MOTOR_ENCODER_DEGREES);

static int target = 0;

void towers(int power)
{
  rightTower.move_velocity(power);
  leftTower.move_velocity(power);
  rightTower1.move_velocity(power);
  leftTower1.move_velocity(power);
}
void towersSet(int pos)
{
  rightTower.move_relative(pos, 100);
  leftTower.move_relative(pos, 100);
}
void resetTowers()
{
  rightTower.tare_position();
  leftTower.tare_position();
  rightTower1.tare_position();
  leftTower1.tare_position();
}

bool lifting()
{
  static int count = 0;
  static int last = 0;
  static int lastTarget = 0;

  int curr = abs(rightTower.get_position());
  int thresh = 5;
  int target1 = target;

  if(abs(last-curr) < thresh)
    count++;
  else
    count = 0;

  if(target1 != lastTarget)
    count = 0;

  lastTarget = target1;
  last = curr;

  //not driving if we haven't moved
  if(count > 6)
    return false;
  else
    return true;
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
    rightTower1.move_velocity(rightPower);
    leftTower1.move_velocity(leftPower);
  //___int64_t_defined  straight(speed);
    lastError = error;
  //  printf("%d\n", error);
    delay(20);

}

void expand(int height)
{
  resetTowers();

  int left  = leftTower.get_position();
  int right = rightTower.get_position();
  int pos = (abs(left)+abs(right))/2;

  int dir;
  if(height > 0)
  dir = 1;
  if(height < 0)
  dir = -1;
  
  int power = 50*dir;

  rightTower.move_velocity(power);
  leftTower.move_velocity(power);
  rightTower1.move_velocity(power);
  leftTower1.move_velocity(power);

  while(pos < abs(height))
    delay(20);

/*
  float Kp = 0.8;
  target = height;
  int error = 0;
  do
  {
    int pos = rightTower.get_position();
    int error = target-pos;

    int power = (Kp*error);

    if(power > 50)
      power = 50;
    if(power < -50)
      power = -50;

    rightTower.move_velocity(power);
    leftTower.move_velocity(power);
    rightTower1.move_velocity(power);
    leftTower1.move_velocity(power);
  }
  while(lifting());
  resetTowers();*/
}
