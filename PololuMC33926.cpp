#include "PololuMC33926.h"


// Constructor
#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(_SAM3XA_)
MC33926::MC33926(int DIR1,int DIR2, int PWM, int SF)
{
	DIR1_ = DIR1;
	DIR2_ = DIR2;
	PWM_ = PWM;
	SF_ = SF;
}
#else
MC33926::MC33926(int DIR1,int DIR2, int PWM, int SF, int FB)
{
	DIR1_ = DIR1;
	DIR2_ = DIR2;
	PWM_ = PWM;
	SF_ = SF;
	FB_ = FB;
}
#endif

void MC33926::init()
{
	//Initializes the pins
	pinMode(DIR1_,OUTPUT);
	pinMode(DIR2_,OUTPUT);
	pinMode(PWM_,OUTPUT);
	pinMode(SF_,INPUT);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
	analogWriteFrequency(PWM_, 11718);
	analogWriteResolution(8);
	#endif
	#if !defined(__MK20DX128__) || !defined(__MK20DX256__) || !defined(_SAM3XA_)
	pinMode(FB_,INPUT);
	#endif
}


void MC33926::set_pwm(int desired_pwm)
{
	// Sets the pwm value.  Will take negative pwm values.
	if (desired_pwm < 0)
	{
		digitalWrite(DIR1_,LOW);
		digitalWrite(DIR2_,HIGH);
		if (desired_pwm < -255)
			desired_pwm = -255;
		analogWrite(PWM_,-1*desired_pwm);
	}
	else
  	{
		digitalWrite(DIR2_,LOW);
		digitalWrite(DIR1_,HIGH);
		if (desired_pwm > 255)
			desired_pwm = 255;
		analogWrite(PWM_,desired_pwm);
	}
}

bool MC33926::fault()
{
	// Checks if there is a fault
	return !digitalRead(SF_); //Flip logic
}

#if !defined(__MK20DX128__) || !defined(__MK20DX256__) || !defined(_SAM3XA_)
float MC33926::motor_current()
{
	// 5V / 10bit resolution / 0.525V/A = 0.0093006 A/count
	return analogRead(FB_) * 0.0093006; //[Amps]
}
#endif

