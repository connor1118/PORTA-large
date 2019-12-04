#include "main.h"

okapi::MotorGroup left({1,2});
okapi::MotorGroup right({9,10});


void reset()
{
  left.tarePosition();
  right.tarePosition();
  left.setReversed(false);
  right.setReversed(true);
}
void reverse()
{
  left.setReversed(true);
  right.setReversed(false);
}

auto baseController = okapi::ChassisControllerFactory::create(
  left, right,
  okapi::IterativePosPIDController::Gains{0.001, 0, 0.0001},//kP, kI, kD
  okapi::IterativePosPIDController::Gains{0.000, 0, 0.0000},
  okapi::IterativePosPIDController::Gains{0.001, 0, 0.0001},
  okapi::AbstractMotor::gearset::green,
  {4.25_in, 15.5_in}
);

auto profileController = okapi::AsyncControllerFactory::motionProfile(
  1.0,  // Maximum linear velocity of the Chassis in m/s
  2.0,  // Maximum linear acceleration of the Chassis in m/s/s
  10.0, // Maximum linear jerk of the Chassis in m/s/s/s
  baseController // Chassis Controller
);

void pathsInit(){
  profileController.generatePath(
    {
      okapi::Point{0_ft, 0_ft, 0_deg},
      okapi::Point{3_ft, 3_ft, 0_deg}
    },
    "A"
  );
  profileController.generatePath(
    {
      okapi::Point{0_ft, 0_ft, 0_deg},
      okapi::Point{1_ft, 3_ft, 0_deg}
    },
    "B"
  );
}
 void test()
 {
   //drive(48);
   //turn(90);
   expand(50);
   //push(0);
  // profileController.setTarget("B");
   //profileController.waitUntilSettled();
 }

void skills()
{

}

 void red()
 {
   intake(200);
   drive(24);
   expand(75);
   drive(4);
   expand(0);
   delay(4500);
   intake(0);
   drive(-6);
   turn(118);
   drive(32);
   push(0);
   expand(5);
   drive(-24);
 }
