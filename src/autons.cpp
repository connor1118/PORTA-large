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
  intake(200);
  drive(12);
  delay(500);
  intake(0);
  drive(12);
  expand(75, 0);
  drive(6);
  intake(200);
  expand(10, 1);
  delay(5500);
  drive(4);
  expand(0, 1);
  delay(1000);
  intake(0);
  drive(-12);
  turn(90);
  intake(200);
  drive(24);
  delay(500);
  intake(0);
  drive(-6);
  turn(30);
  drive(16);
  push(0);
  expand(5, 0);
  delay(500);
  drive(-24);
  push(1);
  turn(-122);
  expand(0, 0);
  intake(200);
  drive(23);
  delay(500);
  intake(0);
  drive(-4);
  expand(65, 0);
  drive(8);
  intake(-200);
  delay(1000);
  intake(0);
  drive(-6);
  expand(0, 0);
  delay(2000);
  drive(-42);
  drive(-5);
  delay(500);
  drive(18);
  turn(-90);
  intake(200);
  drive(20);
  delay(500);
  intake(0);
  drive(-4);
  expand(85, 0);
  drive(5);
  intake(-200);
  delay(1000);
  intake(0);
  drive(-6);
  expand(0, 0);
  delay(2000);
}

 void oldred()
 {
   intake(200);
   drive(12);
   intake(0);
   drive(12);
   expand(75, 0);
   drive(6);
   intake(200);
   expand(10, 1);
   delay(5500);
   drive(4);
   expand(0, 1);
   delay(1000);
   intake(0);
   drive(-12);
   turn(90);
   intake(200);
   drive(24);
   delay(500);
   intake(0);
   drive(-6);
   turn(30);
   drive(16);
   push(0);
   expand(5, 0);
   delay(500);
   drive(-24);
   push(1);
   expand(0, 0);
 }

 void red()
 {
   intake(200);
   drive(12);
   intake(0);
   drive(12);
   expand(75, 0);
   drive(6);
   intake(200);
   expand(10, 1);
   delay(5500);
   drive(4);
   expand(0, 1);
   delay(1000);
   intake(0);
   drive(-12);
   turn(90);
   intake(200);
   drive(24);
   delay(500);
   intake(0);
   drive(-6);
   turn(30);
   drive(16);
   push(0);
   expand(5, 0);
   delay(500);
   drive(-24);
   push(1);
   expand(0, 0);
 }

 void blue()
 {
   intake(200);
   drive(12);
   delay(1000);
   intake(0);
   drive(12);
   expand(75, 0);
   drive(7);
   intake(200);
   expand(10, 1);
   delay(3500);
   expand(0, 1);
   drive(4);
  // expand(0, 1);
   delay(1000);
   intake(0);
   drive(-13);
   turn(-90);
   intake(200);
   drive(24);
   delay(500);
   //intake(0);
   drive(-6);

   turn(90);
   drive(-20);
   drive(-6);
   delay(500);
   drive(34);
   turn(86);
   drive(55);

   /*turn(155);
   drive(32);
   turn(20);
   drive(50);*/
   turn(25);

   drive(56);
   move(-50);
   delay(200);
   move(0);
  // delay(500);
   //drive(-2);
   intake(0);
   push(0);
   intake(-25);
  // expand(25, 0);
   drive(1);
   delay(500);
   drive(-24);
   push(1);
   expand(0, 0);
 }
