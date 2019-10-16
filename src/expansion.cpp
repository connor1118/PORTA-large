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
