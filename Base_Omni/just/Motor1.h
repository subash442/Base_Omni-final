#ifndef MOTOR1_H
#define MOTOR1_H



	#include "headers.h"

     #define ICR_TOP1   249
     #define MAX_VALUE1 249
     #define MIN_VALUE1 0







    #define DD_F1 H,4
    #define DD_B1 H,3

    #define DD_PWM1			E,3
    #define PWM_TCCRA1		TCCR3A
    #define PWM_TCCRB1		TCCR3B
    #define PWM_ICR1			ICR3
    #define PWM_OCR1			OCR3A

    #define PWM_1COM0		COM3A0
    #define PWM_1COM1		COM3A1

    #define PWM_1WGM0		WGM30
    #define PWM_1WGM1		WGM31
    #define PWM_1WGM2		WGM32
    #define PWM_1WGM3		WGM33
    #define PWM_1CS0			CS30
    #define PWM_1CS1			CS31
    #define PWM_1CS2			CS32


class Motor1
{

     private:

     public:
        void Initialise();

        void InitPWM();

        void SetForwardDirection();
        void SetReverseDirection();
        void StopMotor();
        void SetOcrValue(int x);
};

#endif // MOTOR1_H
