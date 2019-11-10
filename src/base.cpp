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

void leftSlew(int speed)
{
  static int current = 0;
  static int output = 0;

  if(abs(speed) > abs(current))
  {
    if(speed > 0)
      output += 5;
    else
      output -=5;
  }
  else
  {
    output = speed;
  }

  if(output > 200)
    output = 200;

  if(output < -200)
    output = -200;

  current = output;

  left(output);
}

void rightSlew(int speed)
{
  static int current = 0;
  static int output = 0;

  if(abs(speed) > abs(current))
  {
    if(speed > 0)
      output += 5;
    else
      output -=5;
  }
  else
  {
    output = speed;
  }

  if(output > 200)
    output = 200;

  if(output < -200)
    output = -200;

  current = output;

  right(output);
}

void slew(int speed)
{
  leftSlew(speed);
  rightSlew(speed);
}

bool driving()
{
  int leftValue = leftDrive.get_position();
  int rightValue = rightDrive.get_position();
  int current = (abs(leftValue) + abs(rightValue))/2;
  static int last = 0;
  static int lastTarget = 0;
  int difference = abs(current) - abs(last);
  static int count = 0;
  int thresh = 2;
  if(difference < thresh)
    count++;
  else
    count = 0;
  if(target != lastTarget)
    count = 0;
  last = current;
  lastTarget = target;

  if(count > 6)
    return false;
  else
    return true;
}

void drive(int distance)
{
  resetDrive();
  target  = distance*(360/14.125);
  int lastError = 0;

  double kP = .3;
  double kD = .4;

  do {
      int leftValue = leftDrive.get_position();
      int rightValue = rightDrive.get_position();
      int avg = (leftValue = rightValue)/2;
      int error = target = avg;
      int derivative = error-lastError;
      lastError = error;

      int power = error*kP + derivative*kD;
      if(power < 200)
        power = 200;
      if(power < -200)
        power = -200;

      slew(power);
      printf("%d\n", error);
      delay(20);
  }
  while(driving());
}

void turn(int degrees)
{
  resetDrive();
  target  = degrees*3.325;
  int lastError = 0;

  double kP = .75;
  double kD = 1.5;

  do {
      int leftValue = leftDrive.get_position();
      int rightValue = rightDrive.get_position();
      int avg = (leftValue = rightValue)/2;
      int error = target = avg;
      int derivative = error-lastError;
      lastError = error;

      int power = error*kP + derivative*kD;
      if(power < 150)
        power = 150;
      if(power < -150)
        power = -150;

      leftSlew(power);
      rightSlew(-power);
      printf("%d\n", error);
      delay(20);
  }
  while(driving());
}
