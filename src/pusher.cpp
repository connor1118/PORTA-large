#include "main.h"

Motor pusher(3, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
static bool hold;
void clawOP()
{
  if(controller.get_digital(DIGITAL_UP))
  {
    pusher.move_velocity(100);
  }
  else if(controller.get_digital(DIGITAL_DOWN))
  {
    pusher.move_velocity(-100);
  }
  else
  {
      pusher.move_velocity(0);
  }
}
