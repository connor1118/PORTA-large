#include "main.h"

Motor leftDrive(1, MOTOR_GEARSET_18, 0,  MOTOR_ENCODER_DEGREES);
Motor leftDrive1(2, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

Motor rightDrive(9, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);
Motor rightDrive1(10, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

static int target = 0;

void resetDrive()
{
  leftDrive.tare_position();
  leftDrive1.tare_position();
  rightDrive.tare_position();
  rightDrive1.tare_position();
}

void left(int speed)
{
  leftDrive.move_velocity(speed);
  leftDrive1.move_velocity(speed);
}

void right(int speed)
{
  rightDrive.move_velocity(speed);
  rightDrive1.move_velocity(speed);
}

void driveOP()
{
  int L = controller.get_analog(ANALOG_LEFT_Y);
  int R = controller.get_analog(ANALOG_RIGHT_Y);
//for slower turns
 /*if((L > 10 && R < -10) || (L < -10 && R > 10))
  {
    leftDrive.move(L*.7);
    leftDrive1.move(L*.7);
    rightDrive.move(R*.7);
    rightDrive1.move(R*.7);
  }
  else
  {*/
      leftDrive.move(L);
      leftDrive1.move(L);
      rightDrive.move(R);
      rightDrive1.move(R);
  //}
}

void leftSlew(int slewSpeed)
{
  int step;
  static int speed = 0;
  if(abs(speed) < abs(slewSpeed))
  {
    step = 5;
  }
  else
  {
    step = 256;
  }
  if(speed < slewSpeed - step)
  {
    speed += step;
  }
  else if(speed > slewSpeed + step)
  {
    speed -= step;
  }
  else
  {
    speed = slewSpeed;
  }

   left(speed);
}

void rightSlew(int slewSpeed)
{
  int step;
  static int speed = 0;
  if(abs(speed) < abs(slewSpeed))
  {
    step = 5;
  }
  else
  {
    step = 256;
  }
  if(speed < slewSpeed - step)
  {
    speed += step;
  }
  else if(speed > slewSpeed + step)
  {
    speed -= step;
  }
  else
  {
    speed = slewSpeed;
  }

   right(speed);
}


void slew(int speed)
{
  leftSlew(speed);
  rightSlew(speed);
}

bool driving()
{
  static int count = 0;
  static int last = 0;
  static int lastTarget = 0;

  int leftPos = leftDrive.get_position();
  int rightPos = rightDrive.get_position();

  int curr = (abs(leftPos) + abs(rightPos))/2;
  int thresh = 2;
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
  if(count > 10)
    return false;
  else
    return true;
}

void drive(int distance)
{
  resetDrive();
  target  = distance*(360/14.125);
  int lastError = 0;
  int sp = target;

  double kP = .4;
  double kD = .3;

  do {
      int leftValue = leftDrive.get_position();
      int rightValue = rightDrive.get_position();
      int curr = leftValue;

      int error = sp - curr;
      int derivative = error-lastError;
      lastError = error;

      int power = error*kP + derivative*kD;

      if(power > 200)
        power = 200;
      if(power < -200)
        power = -200;

      slew(power);
      printf("%d\n", error);
      delay(20);
  }
  while(driving());
  resetDrive();
  left(0);
  right(0);
}

void turn(int degrees)
{
  resetDrive();
  target  = degrees*3.85;
  int lastError = 0;
  int goal = target;

  double kP = .9;
  double kD = 2.9;

  do {
      int leftValue = leftDrive.get_position();
      int rightValue = rightDrive1.get_position();
      int avg = (rightValue - leftValue)/2;

      int error = goal - avg;
      int derivative = error-lastError;
      lastError = error;

      int power = error*kP + derivative*kD;

      if(power > 100)
        power = 100;
      if(power < -100)
        power = -100;

      leftSlew(-power);
      rightSlew(power);
      printf("%d\n", error);
      delay(20);
  }
  while(driving());
  resetDrive();
}
