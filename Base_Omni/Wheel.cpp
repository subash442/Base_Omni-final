/*
 * Joydata.h
 *
 * Created: 10/12/2017 7:11:34 PM
 *  Author: Subash Timilsina
 */ 

#include "Wheel.h"

extern signed char rcvdata[8];
Encoder e[4];
volatile bool pidflag = false;
volatile uint8_t count = 0;

void Wheel::init()
{
	
	robot_rpm = 50;
	for(int i=0;i<4;i++)
	{
		velocity_motor[i] = 0;
		velocity_robot[i] = 0;
		m[i].Initialise(i+1);
		e[i].Initialise(i+1);
		p[i].Set_Pid(0,0,0);
		//p[i].Set_Pid(0,0,0);
	}
	
	reset_data();	
}

void Wheel::get_joystick_data()
{
	if (rcvdata[0]==32)			//emergency button start
	{
		for(uint8_t i=0;i<4;i++)
		{
			p[i].Set_SP(0);
			m[i].SetOcrValue(0);
		}
	}

	if (rcvdata[0] == 1)		// a and b
	{
		p[0].Dcr_P();
		if (p[0].Get_P()<0.01)
		p[0].Set_P(0);
	}

	else if (rcvdata[0] == 2)			
		p[0].Inc_P();		
				
	else if (rcvdata[0] == 4)
	{
		p[0].Dcr_D();
		if (p[0].Get_D()<0.01)
		p[0].Set_D(0);
	}
	else if (rcvdata[0] == 8)		//y and x
		p[0].Inc_D();

	else if (rcvdata[0]==16)			//button left and right
		{
			//p[0].Inc_I();
			robot_rpm +=5;
			
		}

	
		if (rcvdata[1]==1)
		{
			//p[0].Dcr_I();
			//if (p[0].Get_D()<0.001)
			//p[0].Set_D(0);
			robot_rpm -=5;
			
		}
		if (robot_rpm > 300) robot_rpm = 300;
		else if (robot_rpm < 0) robot_rpm = 0;

		else if (rcvdata[1]==2)
		{
			UART3Transmit('\n');
			UART3TransmitData(p[0].Get_P()*1000);
			UART3Transmit(' ');
			UART3TransmitData(p[0].Get_I()*1000);
			UART3Transmit(' ');
			UART3TransmitData(p[0].Get_D()*100);
			UART3Transmit('\n');
		}
		else if (rcvdata[1]==4)
			p[0].Set_Pid(0,0,0);

		for(uint8_t i = 1; i<4 ;i++)
		{
			p[i].Set_Pid(p[0].Get_P(),p[0].Get_I(),p[0].Get_D());
		}

		//Control of robot

		if(rcvdata[1]==8)
			 velocity_robot[0] = robot_rpm;
		if (rcvdata[1]==16)
			velocity_robot[0] =  -robot_rpm;
		if(rcvdata[1]==32)
			velocity_robot[1] = robot_rpm;
		if (rcvdata[1]==64)
			velocity_robot[1] = -robot_rpm;

   //x_target = rcvdata[2];
   //y_target = rcvdata[3];
   //yaw = rcvdata[4];
 //
	//if (robot_rpm>600) robot_rpm =600;
	//if (robot_rpm<=0) robot_rpm = 0;
	//
	//velocity_robot[0] = (x_target/50.0)*robot_rpm;
	//velocity_robot[1] = (-y_target/53.0)*robot_rpm;
	//velocity_robot[2] = (yaw/50.0)*robot_rpm;
	
}

void Wheel::calculate_wheel_velocity()
{
	float coupling_matrix[4][3] = {{-0.707,0.707,1},{-0.707,-0.707,1},{0.707,-0.707,1},{0.707,0.707,1}};
    for(int i=0;i<4;i++)
    {
        velocity_motor[i] = 0;
        for(int j=0;j<3;j++)
        {
             velocity_motor[i] += velocity_robot[j] * coupling_matrix[i][j];
        }
		
    }
	
    for(int i=0;i<4;i++)
    {
        //ocr_motor[i] = ((249.0*velocity_motor[i])/(MAX_RPM));//multiply by icr_top value
		ocr_motor[i] = velocity_motor[i]*PPR/3000.0;
		velocity_robot[i] = 0;
		p[i].Set_SP(ocr_motor[i]);
    }
	  
}

void Wheel::update_wheel_velocity()
{
	if(pidflag)
	{
		for(int i = 0; i<4 ; i++)
		{
			m[i].SetOcrValue(p[i].Compute(e[i].Get_Speed()));
			//UART0TransmitData(ocr_motor[i]);
			//UART0Transmit(' ');
			//UART0TransmitData(e[i].Get_Speed());
			//UART0Transmit(' ');
		}
		//UART0TransmitString("\r\n");
		pidflag = false;
	}
	if (count >= 3)
	{
	  //UART3TransmitData(20);
	  //UART3Transmit(' ');
	  //UART3TransmitData(-20);
	  //UART3Transmit(' ');
	  //UART3TransmitData(ocr_motor[0]);
	  //UART3Transmit(' ');
	  //UART3TransmitData(e[0].Get_Speed());
	  //UART3TransmitString("\r\n");
	  count = 0;
	 }	  

	 UART3TransmitData(rcvdata[0]);
	 UART3Transmit(' ');
	 UART3TransmitData(rcvdata[1]);
	 UART3Transmit('\n')	 ;
}
	

void Wheel::reset_data()
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		rcvdata[i] = 0;
	}
}


ISR(INT_VECT1)
{
	if(bit_is_set(ENCODER1_CHAPORTPIN,ENCODER1_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
	e[0].incCount();
	}
	else
	e[0].dcrCount();

}

ISR(INT_VECT2)
{
	if(bit_is_set(ENCODER2_CHAPORTPIN,ENCODER2_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
	e[1].incCount();
	}
	else
	e[1].dcrCount();


}
ISR(INT_VECT3)
{
	if(bit_is_set(ENCODER3_CHAPORTPIN,ENCODER3_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
	e[2].incCount();
	}
	else
	e[2].dcrCount();

}

ISR(INT_VECT4)
{
	if(bit_is_set(ENCODER4_CHAPORTPIN,ENCODER4_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
	e[3].incCount();
	}
	else
	e[3].dcrCount();

}


ISR(TIMER1_COMPA_vect)
{
	e[0].Calc_Speed();
	e[1].Calc_Speed();
	e[2].Calc_Speed();
	e[3].Calc_Speed();
	count++;
	pidflag = true;
}