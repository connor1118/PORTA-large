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
int prevError = 0;
int sp = distance;

double kp = .31;
double kd = 0.5;

do
{
  int ls = leftTower.get_position();
  int rs = rightTower.get_position();

  int error = rs-ls;
  int derivative = error - prevError;
  prevError = error;
  int speed = error*kp + derivative*kd;

  if(speed > 100)
  {
    speed = 100;
  }
  if(speed < -100)
  {
    speed = -100;
  }

  rightTower.move_velocity(speed);
  leftTower.move_velocity(speed);
//___int64_t_defined  straight(speed);
  printf("%d\n", error);
  delay(20);
}
while(isDriving());
}
