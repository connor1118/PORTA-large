#include "main.h"

Motor leftIntake(5, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor rightIntake(6, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

void intakes(int speed)
{
  leftIntake.move_velocity(speed);
  rightIntake.move_velocity(speed);
}

void intakeOP()
{
  static int set = 1;
  static bool pressed;
  if(controller.get_digital(DIGITAL_R1))
  {
    intakes(200);
  }
  else if(controller.get_digital(DIGITAL_R2))
  {
    intakes(-150);
  }
  else
  {
    intakes(0);
  }
}
