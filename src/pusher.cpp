#include "main.h"

Motor pusher(4, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);
static bool hold;
void pusherOP()
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

void push(bool in)
{
  if(in)
  {
    pusher.move_absolute(0, 100);
    while(!(pusher.get_position()>-5 && pusher.get_position()<5))
      delay(20);
  }
  else
  {
    pusher.move_absolute(1500, 100);
    while(!(pusher.get_position()>1495 && pusher.get_position()<1505))
      delay(20);
  }

}
