#include "main.h"

Motor claw(3, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

void clawOP()
{
  bool hold;
  if(controller.get_digital(DIGITAL_R1))
  {
    hold = 1;
    claw.move_velocity(200);
  }
  else if(controller.get_digital(DIGITAL_R2))
  {
    hold = 0;
    claw.move_velocity(-200);
  }
  else
  {
    if(hold == 0)
      claw.move_velocity(0);
    else
      claw.move_velocity(5);
  }
}
