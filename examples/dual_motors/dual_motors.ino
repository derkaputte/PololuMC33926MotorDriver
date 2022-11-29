#include "PololuMC33926.h"

// // NOTE: Pins are for Teensy 3.X
// MC33926 left_motor(2,3,5,4);
// MC33926 right_motor(12,11,10,9);


// NOTE: Pins are for MEGA on Ardumower Board v1.2
//   EN, DIR1, PWM, SF, FB
MC33926 left_motor(37,31,5,25,A1);
MC33926 right_motor(37,33,3,27,A0);

void setup()
{
  left_motor.init();
  right_motor.init();
}

void loop()
{
  if(!left_motor.fault()  || !right_motor.fault() )
  {
    for (int x = 0; x < 256;x++)
    {
      left_motor.set_pwm(x);
      right_motor.set_pwm(-x);
      delay(25);
    }
  }
}

