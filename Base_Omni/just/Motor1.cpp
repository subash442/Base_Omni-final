#include "Motor1.h"

void Motor1::Initialise()
{
	InitPWM();

	StopMotor();
	SetOcrValue(0);

}

void Motor1::InitPWM()
{
	OUTPUT(DD_F1);
	OUTPUT(DD_B1);

	OUTPUT(DD_PWM1);

	PWM_TCCRA1	|=  ( 1 << PWM_1COM1 ) | ( 1 << PWM_1WGM1 );														//
	PWM_TCCRB1	|=  ( 1 << PWM_1WGM2 ) | ( 1 << PWM_1WGM3 ) | ( 1 << PWM_1CS1);									//PRESCALAR 8
	PWM_ICR1		 =         ICR_TOP1;
}

void Motor1::SetForwardDirection()
{
	SET		(DD_F1);
	CLEAR	(DD_B1);

}
void Motor1::SetReverseDirection()
{
	CLEAR	(DD_F1);
	SET		(DD_B1);

}

void Motor1::StopMotor()
{
	CLEAR	(DD_F1);
	CLEAR	(DD_B1);

	PWM_OCR1 = 0;
}


void Motor1::SetOcrValue(int Ocr)
{
    if (Ocr > 0)
        SetForwardDirection();
	if( Ocr >= MAX_VALUE1)
		Ocr = MAX_VALUE1;
	if( Ocr < 0)
	{
        Ocr = -Ocr;
        SetReverseDirection();
	}

	PWM_OCR1	= Ocr;
}
