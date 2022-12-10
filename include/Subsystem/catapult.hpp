#pragma once 
#include "Subsystem/catapult.hpp"
#include "main.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "setup.hpp"
inline bool Firing = false;
inline bool GiveUp = false;

inline void FireCatapult(void*)
{
    int counter = 0;
    
    pros::delay(2000);
    while(true)
    {
        
        if(Firing)
        {
            catapult.move(-127);
            counter += 10;
            if(counter > 1000)
            {
                Firing = false;
                counter = 0;
            }
            GiveUp = false;
        }
        else 
        {
            if(catapult_limit.get_value() == 0 && !GiveUp)
            {
                catapult.move(-127);
            }
            else 
            {
                GiveUp = true;
                catapult.move(0);    
            }
        }
        pros::delay(ez::util::DELAY_TIME);
    }
}

inline pros::Task cataTask(FireCatapult);
