#ifndef MOTOR4_H
#define MOTOR4_H


#include "headers.h"

     #define ICR_TOP4   249
     #define MAX_VALUE4 249
     #define MIN_VALUE4 0







    #define DD_F4 E,4
    #define DD_B4 E,5

    #define DD_PWM4			B,7
    #define PWM_TCCRA4		TCCR1A
    #define PWM_TCCRB4		TCCR1B
    #define PWM_ICR4			ICR1
    #define PWM_OCR4			OCR1C

    #define PWM_4COM0		COM1C0
    #define PWM_4COM1		COM1C1

    #define PWM_4WGM0		WGM10
    #define PWM_4WGM1		WGM11
    #define PWM_4WGM2		WGM12
    #define PWM_4WGM3		WGM13
    #define PWM_4CS0			CS10
    #define PWM_4CS1			CS11
    #define PWM_4CS2			CS12


class Motor4
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
#endif // MOTOR4_H
