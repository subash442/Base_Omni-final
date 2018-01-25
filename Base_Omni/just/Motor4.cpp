#include "Motor4.h"

void Motor4::Initialise()
{
	InitPWM();

	StopMotor();
	SetOcrValue(0);

}

void Motor4::InitPWM()
{
	OUTPUT(DD_F4);
	OUTPUT(DD_B4);

	OUTPUT(DD_PWM4);

	PWM_TCCRA4	|=  ( 1 << PWM_4COM1 ) | ( 1 << PWM_4WGM1 );														//
	PWM_TCCRB4	|=  ( 1 << PWM_4WGM2 ) | ( 1 << PWM_4WGM3 ) | ( 1 << PWM_4CS1);									//PRESCALAR 8
	PWM_ICR4	 =         ICR_TOP4;
}

void Motor4::SetForwardDirection()
{
	SET		(DD_F4);
	CLEAR	(DD_B4);

}
void Motor4::SetReverseDirection()
{
	CLEAR	(DD_F4);
	SET		(DD_B4);

}

void Motor4::StopMotor()
{
	CLEAR	(DD_F4);
	CLEAR	(DD_B4);

	PWM_OCR4 = 0;
}


void Motor4::SetOcrValue(int Ocr)
{
     if (Ocr > 0)
        SetForwardDirection();
	if( Ocr >= MAX_VALUE4)
		Ocr = MAX_VALUE4;
	if( Ocr < 0)
	{
        Ocr = -Ocr;
        SetReverseDirection();
	}

	PWM_OCR4	= Ocr;
}

