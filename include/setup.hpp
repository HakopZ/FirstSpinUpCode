#pragma once
#include "api.h"
#include "EZ-Template/api.hpp"
#include "pros/adi.hpp"

inline pros::Motor intake(19);
inline pros::Motor catapult(15);
inline pros::ADIDigitalOut endgame(1);
inline pros::ADIButton catapult_limit(8);
// Chassis constructor
inline Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-20, 17, -16}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{14, -13, 12}

  // IMU Port
  ,1

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  // (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.5
);          