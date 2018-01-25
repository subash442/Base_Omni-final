#include "Motor2.h"

void Motor2::Initialise()
{
	InitPWM();

	StopMotor();
	SetOcrValue(0);

}

void Motor2::InitPWM()
{
	OUTPUT(DD_F2);
	OUTPUT(DD_B2);

	OUTPUT(DD_PWM2);

	PWM_TCCRA2	|=  ( 1 << PWM_2COM1 ) | ( 1 << PWM_2WGM1 );														//
	PWM_TCCRB2	|=  ( 1 << PWM_2WGM2 ) | ( 1 << PWM_2WGM3 ) | ( 1 << PWM_2CS1);									//PRESCALAR 8
	PWM_ICR2		 =         ICR_TOP2;
}

void Motor2::SetForwardDirection()
{
	SET		(DD_F2);
	CLEAR	(DD_B2);

}
void Motor2::SetReverseDirection()
{
	CLEAR	(DD_F2);
	SET		(DD_B2);

}

void Motor2::StopMotor()
{
	CLEAR	(DD_F2);
	CLEAR	(DD_B2);

	PWM_OCR2 = 0;
}


void Motor2::SetOcrValue(int Ocr)
{


	 if (Ocr > 0)
        SetForwardDirection();
	if( Ocr >= MAX_VALUE2)
		Ocr = MAX_VALUE2;
	if( Ocr < 0)
	{
        Ocr = -Ocr;
        SetReverseDirection();
	}

	PWM_OCR2	= Ocr;
}
