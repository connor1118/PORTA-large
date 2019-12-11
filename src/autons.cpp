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
  okapi::IterativePosPIDController::Gains{0.1, 0, 0.07},//kP, kI, kD
  okapi::IterativePosPIDController::Gains{0.001, 0, 0.0001},
  okapi::IterativePosPIDController::Gains{0.9, 0, 2.9},
  okapi::AbstractMotor::gearset::green,
  {4.25_in, 15_in}
);

auto profileController = okapi::AsyncControllerFactory::motionProfile(
  0.6,  // Maximum linear velocity of the Chassis in m/s
  0.8,  // Maximum linear acceleration of the Chassis in m/s/s
  0.6, // Maximum linear jerk of the Chassis in m/s/s/s
  baseController // Chassis Controller
);

void pathsInit(){
  profileController.generatePath(
    {
      okapi::Point{0_ft, 0_ft, 0_deg},
      okapi::Point{3_ft, 3_ft, 90_deg}
    },
    "A"
  );
  profileController.generatePath(
    {
      okapi::Point{0_ft, 0_ft, 0_deg},
      okapi::Point{-2_ft, 2_ft, 0_deg}
    },
    "B"
  );
  profileController.generatePath(
    {
      okapi::Point{0_ft, 0_ft, 0_deg},
      okapi::Point{2_ft, -1_ft, 90_deg}
    },
    "C"
  );
}
 void test()
 {
   //drive(48);
   //turn(90);
  // expand(50);
   //push(0);
   reverse();
   profileController.setTarget("C");
   reset();
   //profileController.waitUntilSettled();
 }

void skills()
{

}

 void red()
 {
   intake(200);
   drive(12);
   intake(0);
   drive(12);
   expand(75);
   drive(6);
   intake(200);
   expand(10);
   delay(5500);
   drive(4);
   expand(0);
   delay(1000);
   intake(0);
   drive(-12);
   turn(90);
   intake(200);
   drive(28);
   intake(0);
   drive(-8);
   turn(25);
   drive(14);
   push(0);
   expand(5);
   delay(500);
   drive(-24);
   push(1);
   expand(0);
 }

 void blue()
 {
   intake(200);
   drive(12);
   intake(0);
   drive(12);
   expand(75);
   drive(6);
   intake(200);
   expand(10);
   delay(5500);
   drive(4);
   expand(0);
   delay(3000);
   intake(0);
   drive(-9);
   turn(-118);
   drive(36);
   push(0);
   expand(5);
   drive(-24);
   push(1);
 }
