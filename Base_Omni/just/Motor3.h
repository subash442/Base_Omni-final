#ifndef MOTOR3_H
#define MOTOR3_H


#include "headers.h"

    #define ICR_TOP3    249
     #define MAX_VALUE3 249
     #define MIN_VALUE3 0







    #define DD_F3 H,5
    #define DD_B3 G,5

    #define DD_PWM3			B,6
    #define PWM_TCCRA3		TCCR1A
    #define PWM_TCCRB3		TCCR1B
    #define PWM_ICR3			ICR1
    #define PWM_OCR3			OCR1B

    #define PWM_3COM0		COM1B0
    #define PWM_3COM1		COM1B1

    #define PWM_3WGM0		WGM10
    #define PWM_3WGM1		WGM11
    #define PWM_3WGM2		WGM12
    #define PWM_3WGM3		WGM13
    #define PWM_3CS0			CS10
    #define PWM_3CS1			CS11
    #define PWM_3CS2			CS12


class Motor3
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
#endif // MOTOR3_H
