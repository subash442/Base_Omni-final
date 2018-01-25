/*
 * encoder-test.cpp
 *
 * Created: 10/15/2017 5:55:45 PM
 * Author : Subash Timilsina
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Encoder.h"
#include "uart.h"
#include "Motor.h"
#include "PID.h"

#define MOTOR_RPM	700.0	

extern signed char rcvdata[8];
Encoder e1(2);//,e2(2),e3(3),e4(4);

//int GetMotorOCR(int rpm)
//{
	//return((249.0/MOTOR_RPM)*rpm);
//}

int main(void)
{
   initUART2();
   initUART0();
   //UART0TransmitString("Hello..\n\r");
	Motor m1;
	PID pid;
	int temp;
	pid.Set_Pid(0,0,0);
	m1.Initialise(2);
	int dat;
	int spoint = 0;
	m1.StopMotor();
	e1.Initialise();
	//e2.Initialise();
	//e3.Initialise();
	//e4.Initialise();
    while (1) 
    {	
		
		dat = spoint
		if (rcvdata[1]==64)
		spoint +=50;
		if (rcvdata[1]==32)
		spoint -=50;
		if (rcvdata[1]==1)
		{
			pid.Set_SP(0);
			m1.SetOcrValue(0);
		}
		
		//if (spoint>700)	spoint = 700;
		
		
		pid.Set_SP(spoint);
		//m1.SetOcrValue(spoint*(249.0/MOTOR_RPM));
	
			temp = pid.Compute(e1.Get_count_time());
			m1.SetOcrValue((249.0/PPR)*temp);
			if (rcvdata[0] == 1)
			{
				pid.Dcr_P();
 					if (pid.Get_P()<=0.1)
 					pid.Set_P(0);
			}
			else if (rcvdata[0] == 2)
			pid.Inc_P();
			else if (rcvdata[0] == 4)
			{
				pid.Dcr_D();
 					if (pid.Get_D()<=0.1)
 					pid.Set_D(0);
			}
			else if (rcvdata[0] == 8)
			pid.Inc_D();
			
			
			//UART0TransmitString("P: ");
			UART0TransmitData(pid.Get_P()*100);
			UART0Transmit('\t');
			
			//UART0TransmitString("I: ");
			//UART0TransmitData(pid.Get_I()*100);
			//UART0Transmit('\t');
			//
			//UART0TransmitString("D: ");
			UART0TransmitData(pid.Get_D()*100);
			UART0Transmit('\t');
			
			
			UART0TransmitData(spoint);
			UART0Transmit('\t');
			UART0TransmitData(e1.Get_motorRPM());
			UART0TransmitString("\n\r");
			
	
		
    }
}


ISR(INT_VECT2)
{
	if(bit_is_set(ENCODER2_CHAPORTPIN,ENCODER2_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
		e1.incCount();
	}
	else
	e1.dcrCount();
	
}


//ISR(INT_VECT1)
//{
	//if(bit_is_set(ENCODER1_CHAPORTPIN,ENCODER1_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
		//e1.incCount();
	//}
	//else
	//e1.dcrCount();
	//
//}
//
//ISR(INT_VECT2)
//{
	//if(bit_is_set(ENCODER2_CHAPORTPIN,ENCODER2_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
		//e2.incCount();		
	//}
	//else 
		//e2.dcrCount();
	//
//}
//ISR(INT_VECT3)
//{
	//if(bit_is_set(ENCODER3_CHAPORTPIN,ENCODER3_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
		//e3.incCount();
	//}
	//else
	//e3.dcrCount();
//}
//
//ISR(INT_VECT4)
//{
	//if(bit_is_set(ENCODER4_CHAPORTPIN,ENCODER4_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
		//e4.incCount();
	//}
	//else
	//e4.dcrCount();
//}


ISR(TIMER1_COMPA_vect)
{
	e1.Calculate_RPM();
	e1.Calc_Speed();	
}