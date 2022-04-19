#pragma config(Sensor, dgtl1,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,         sensorQuadEncoder)
#pragma config(Motor,  port10,           rightMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  port1,           leftMotor,     tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/*----------------------------------------------------------------------------------------------------*\
|*                              - Forward for Distance with Encoders -                                *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to move forward for 5 rotations of the left shaft encoder.       *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" model, but may not be needed for all robot configurations.                      *|
|*    2)  Whichever encoder is being used for feedback should be cleared just before it starts        *|
|*        counting by using the "SensorValue(encoder) = 0;".  This helps ensure consistancy.          *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor   - Port 2    rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor   - Port 3    leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital - Port 1,2  rightEncoder        VEX Shaft Encoder     Right side                        *|
|*    Digital - Port 3,4  leftEncoder         VEX Shaft Encoder     Left side                         *|
\*----------------------------------------------------------------------------------------------------*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
void Clear()
{
	//Clear Encoders
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
}
void Forward(float x)//where x is inches
{
	Clear(); //Clear shaft encoders
	while(SensorValue[rightEncoder] < (x/8.64)*360) //Convert inches into degrees per wheel
	{
		motor[rightMotor] = 127;
		motor[leftMotor] = 127;
	}
}
void PointTurnRight(float x) //where x is the degrees
{
	Clear(); //Clear shaft encoders
	while(SensorValue[leftEncoder] < ((39.27*(x/360)*360)/8.64)) //Convert degrees into wheel turn counts(degrees per wheel)
	{
		motor[rightMotor] = -127;
		motor[leftMotor] = 127;
	}
}
void Square()
{
	Clear(); //Clear shaft encoders
	for (int x = 0; x < 4; x++) //Repeat 4 times to form square
	{
		Forward(18);
		PointTurnRight(100); //normally I would pass in 90 degrees,but the robot has issues so I have to compensate
	}
}
void pointTurnLeft(float x) //were x is the degrees
{
	Clear(); //Clear shaft encoders
	while(SensorValue[rightEncoder] < ((39.27*(x/360)*360)/8.64)) //Converting degrees into wheel turn counts (degrees per wheel)
	{
		motor[rightMotor] = 127;
		motor[leftMotor] = -127;
	}
}
void backward(float x) //were x is inches
{
	Clear(); //Clear shaft encoders
	while(SensorValue[rightEncoder] > -1*((x/8.64)*360)) //converting inches into negative degrees of rotation because BCKWDS
	{
		motor[leftMotor] = -127;
		motor[rightMotor] = -127;
	}
}
void Stop() //moving motors backwards at min speed for 1 sec to cause abrupt stop
{
	Clear();
	motor[leftMotor] = -1;
	motor[rightMotor] = -1;
	wait1Msec(1000);
}
task main()
{
	wait1Msec(2000);  // 2 Second Delay
	Clear(); //Clear Shaft Encoder Values
	Forward(12); //forward for 1ft
	Stop(); //Pause between instructions for clarity
	Square(); //do the sqaure
	motor[leftMotor] = -1;
	motor[rightMotor] = 1;
	wait1Msec(1000); //Pause between instructions for clarity (can't use stop func because the wheels are moving in opposite directions)
	Forward(5); //forward 5"
	Stop(); //Pause between instructions for clarity
	pointTurnLeft(45); //left 45 degrees
	motor[leftMotor] = 1;
	motor[rightMotor] = -1;
	wait1Msec(1000); //Pause between instructions for clarity (can't use stop func because the wheels are moving in opposite directions)
	backward(20); //backward 20"
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
