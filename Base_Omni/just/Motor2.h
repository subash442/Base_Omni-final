#ifndef MOTOR2_H
#define MOTOR2_H

#include "headers.h"

    #define ICR_TOP2    249
     #define MAX_VALUE2 249
     #define MIN_VALUE2 0







    #define DD_F2 H,6
    #define DD_B2 B,4

    #define DD_PWM2			B,5
    #define PWM_TCCRA2		TCCR1A
    #define PWM_TCCRB2		TCCR1B
    #define PWM_ICR2			ICR1
    #define PWM_OCR2			OCR1A

    #define PWM_2COM0		COM1A0
    #define PWM_2COM1		COM1A1

    #define PWM_2WGM0		WGM10
    #define PWM_2WGM1		WGM11
    #define PWM_2WGM2		WGM12
    #define PWM_2WGM3		WGM13
    #define PWM_2CS0			CS10
    #define PWM_2CS1			CS11
    #define PWM_2CS2			CS12


class Motor2
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

#endif // MOTOR2_H
