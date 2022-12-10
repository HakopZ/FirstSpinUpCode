#pragma once 
#include "main.h"

inline void SetIntake(int power)
{
    intake.move(power);
}

inline void Toggle_Intake(bool toggle)
{   
    SetIntake(toggle ? 127 : 0);
}

inline bool moveRoller = false;
inline void DoRoller()
{
    int counter = 0;
    while(true)
    {
        if(moveRoller)
        {
            SetIntake(127);
            if(counter > 500)
            {
                SetIntake(0);
                moveRoller = false;
            }
        }
        pros::delay(10);
    }
}

inline pros::Task rollerTask(DoRoller);