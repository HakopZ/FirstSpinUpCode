#include "main.h"
#include "Subsystem/catapult.hpp"
#include "Subsystem/intake.hpp"
#include "pros/misc.h"
#include "setup.hpp"



void initialize() {
  // Print our branding over your terminal :D
  cataTask.suspend();
  rollerTask.suspend();
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.
  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("Drive Tune", tune_drive),
  });

  catapult.set_brake_mode(MOTOR_BRAKE_HOLD);
  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();

}



void disabled() {}


void competition_initialize() {}



void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

//  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
  tune_drive();
}




void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  bool intakeToggle = false;
  cataTask.resume();
  rollerTask.resume();
  while (true) {

    if (master.get_digital_new_press(DIGITAL_L1)) intakeToggle = !intakeToggle;
    if (master.get_digital_new_press(DIGITAL_R2)) Firing = true;
    if (master.get_digital_new_press(DIGITAL_DOWN)) 
    {
      moveRoller = true; 
    }
    if (master.get_digital_new_press(DIGITAL_R1))
    {
      endgame.set_value(1);
    }
    chassis.tank(); 
    if(master.get_digital(DIGITAL_L2))
    {
      SetIntake(-127);
    }
    else if(GiveUp) 
    {
      Toggle_Intake(intakeToggle);
    }
    else 
    {
      Toggle_Intake(false);
    }
    
    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
