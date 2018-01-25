/*
 * Joydata.h
 *
 * Created: 10/12/2017 7:11:34 PM
 *  Author: Subash Timilsina
 */ 

#ifndef WHEEL_H
#define WHEEL_H



/*#incli*/

#include "PID.h"
#include "Motor.h"
#include "uart.h"
#include "Encoder.h"


//#define PI           3.141592
#define MAX_RPM		   700							//In RPM	
//#define Duty_cycle     15                           //In percentage
//#define ROBOT_RPM      ((MAX_RPM*Duty_cycle)/100)      //In RPM
//#define Wheel_Radius 0.067                        //In meter
//#define MAX_VEL      MAX_RPM/(2*PI*Wheel_Radius)  //In m/s



class Wheel
{
     private:
	 
	// uint8_t button1;
	 signed char x_target,y_target;//yaw;
	 uint16_t robot_rpm;
	 float velocity_motor[4];
	 int velocity_robot[4];
     int ocr_motor[4];
        Motor m[4];
		PID p[4];

    public:
	
       
        void init();
		void reset_robvel();
        void get_joystick_data();
        void calculate_wheel_velocity();
        void update_wheel_velocity();
		void reset_data();
};

#endif // WHEEL_H
