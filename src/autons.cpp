#include "autons.hpp"
#include "main.h"
#include "pros/llemu.hpp"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 115; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 100;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void tune()
{

  chassis.set_slew_min_power(60, 60);
  chassis.set_slew_distance(5, 5);
  chassis.set_pid_constants(&chassis.headingPID, 5, 0, 9, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.25, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.25, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 3.39, 0.002, 31, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}
void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void straight_test()
{
  chassis.set_tank(50, 50);
  pros::delay(3000);
  chassis.set_tank(0, 0);
  
}

void tune_turn()
{
  tune();
  chassis.set_turn_pid(176, TURN_SPEED);
  chassis.wait_drive();
  
  pros::lcd::print(6, "GYRO: %f", chassis.turnPID.error);
}
void tune_drive()
{
  tune_turn();
  /*tune();
  chassis.set_drive_pid(48, DRIVE_SPEED, true);
  pros::lcd::print(1, "Before Moving Left: %f", chassis.leftPID.error);
  pros::lcd::print(2, "Before Moving Right: %f", chassis.rightPID.error);
  chassis.wait_drive();

  chassis.set_drive_pid(-48, DRIVE_SPEED, true);
  pros::lcd::print(4, "Before Moving Left: %f", chassis.leftPID.error);
  pros::lcd::print(5, "Before Moving Right: %f", chassis.rightPID.error);
  pros::lcd::print(6, "GYRO: %f", chassis.get_gyro());
  chassis.wait_drive();*/
  
    //straight_test();
  /*pros::lcd::print(3, "After Moving Left: %f", chassis.leftPID.error);
  pros::lcd::print(4, "AFter Moving Right: %f", chassis.rightPID.error);
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
  pros::lcd::print(5, "Done Left: %f", chassis.leftPID.error);
  pros::lcd::print(6, "Done Right: %f", chassis.rightPID.error);
  */
}

