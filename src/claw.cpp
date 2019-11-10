#include "main.h"

Motor claw(3, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
static bool hold;
void clawOP()
{
  if(controller.get_digital(DIGITAL_R1))
  {
    hold = 1;
    claw.move_velocity(100);
  }
  else if(controller.get_digital(DIGITAL_R2))
  {
    hold = 0;
    claw.move_velocity(-100);
  }
  else
  {
    if(hold == 0)
      claw.move_velocity(0);
    else
      claw.move_velocity(10);
  }
}
