#include "Motor3.h"

void Motor3::Initialise()
{
	InitPWM();

	StopMotor();
	SetOcrValue(0);

}

void Motor3::InitPWM()
{
	OUTPUT(DD_F3);
	OUTPUT(DD_B3);

	OUTPUT(DD_PWM3);

	PWM_TCCRA3	|=  ( 1 << PWM_3COM1 ) | ( 1 << PWM_3WGM1 );														//
	PWM_TCCRB3	|=  ( 1 << PWM_3WGM2 ) | ( 1 << PWM_3WGM3 ) | ( 1 << PWM_3CS1);									//PRESCALAR 8
	PWM_ICR3		 =         ICR_TOP3;
}

void Motor3::SetForwardDirection()
{
	SET		(DD_F3);
	CLEAR	(DD_B3);

}
void Motor3::SetReverseDirection()
{
	CLEAR	(DD_F3);
	SET		(DD_B3);

}

void Motor3::StopMotor()
{
	CLEAR	(DD_F3);
	CLEAR	(DD_B3);

	PWM_OCR3 = 0;
}


void Motor3::SetOcrValue(int Ocr)
{
     if (Ocr > 0)
        SetForwardDirection();
	if( Ocr >= MAX_VALUE3)
		Ocr = MAX_VALUE3;
	if( Ocr < 0)
	{
        Ocr = -Ocr;
        SetReverseDirection();
	}

	PWM_OCR3	= Ocr;
}

