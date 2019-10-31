#include "main.h"

Motor leftFunnel(4, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor rightFunnel(8, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

void funnels(int speed)
{
  leftFunnel.move_velocity(speed);
  rightFunnel.move_velocity(speed);
}

void funnelOP()
{
  static int set = 1;
  static bool pressed;
  if(controller.get_digital(DIGITAL_A))
  {
      if(set < 4 && !pressed)
      {
        pressed = 1;
        set++;
      }
      else if(!pressed)
      {
        pressed = 1;
        set = 1;
      }
  }
  else
    pressed = 0;

  printf("%d\n", set);
  if(set==1)
    funnels(0);
  if(set==2)
    funnels(200);
  if(set==3)
    funnels(0);
  if(set==4)
    funnels(-200);
}
