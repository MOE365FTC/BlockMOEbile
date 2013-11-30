#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     arm,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     bucket,        tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    dumper,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//This TeleOp program is designed ONLY for use leading up to and on the competition at Oxford on 11/16/13.

//In future competitions, we will use Emma's (currently WIP) TeleOp program, which will feature:
// -a new control scheme
// -scaling to allow for more precise speed control
// -whatever else Emma decides to add
// -most importantly, a great learning experience




#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

//The rightDrive encoder is correct, but the leftDrive encoder is backwards.
//The lift encoder is backwards.
//I believe that the arm encoder is correct


void initializeRobot()
{
	servo[dumper] = 110; //Get the autonomous block dumper out of the way vertically for TeleOp.
	return;
}


task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase

	while (true)
	{
		getJoystickSettings(joystick); //Refresh the joystick status
		//Drive Code

		int DriveLowerThreshold = 15;             //The minimum drive speed.
		int DriveUpperThreshold = 75;             //Default maximum drive speed.

<<<<<<< HEAD
		if(joy1Btn(8)) DriveUpperThreshold = 100; //If button 8 (bottom right trigger) on the primary driver's joystick is held down, set the maximum drive speed to 100. (Speed boost)

     	int rightPower = joystick.joy1_y2;        //Set rightPower to its proper joystick value.
		int leftPower = joystick.joy1_y1;         //Set leftPower to its proper joystick value.

		if (abs(rightPower)> DriveUpperThreshold) //If the power set by the right joystick is above the max drive speed, set the right power to whatever the max drive speed is.
=======
		if(joy1Btn(8)) DriveUpperThreshold = 100; //If button 8 (bottom right trigger) on the primary driver's joystick is held down,
			//set the maximum drive speed to 100. (Speed boost)

		int rightPower = joystick.joy1_y2;      //Set rightPower to its proper joystick value.
		int leftPower = joystick.joy1_y1;         //Set leftPower to its proper joystick value.

		if (abs(rightPower)> DriveUpperThreshold) //If the power set by the right joystick is above the max drive speed,
			//set the right power to whatever the max drive speed is.
>>>>>>> 62619061a704262a1ee1b2c6e23f0bd03ddfdc6b
		{
			if (rightPower < 0) rightPower = DriveUpperThreshold * -1; //If rightPower is negative, keep it negative as it is set to the max drive speed.
			else  rightPower = DriveUpperThreshold;                    //If rightPower is positive, we can just set it to the max speed.
		}

		if(abs(leftPower) > DriveUpperThreshold) //If the power set by the left joystick is above the max drive speed,
			//set the left power to whatever the max drive speed is.
		{
			if (leftPower < 0) leftPower = DriveUpperThreshold*-1;     //If leftPower is negative, keep it negative as it is set to the max drive speed.
			else leftPower= DriveUpperThreshold;                       //If leftPower is positive, we can just set it to the max speed.
		}

		if(abs(rightPower) < DriveLowerThreshold)   //If the power set by the right joystick is below the threshold, set the right power to zero.
		{
			rightPower = 0;
		}
		if(abs(leftPower) < DriveLowerThreshold)   //If the power set by the left joystick is below the threshold, set the left power to zero.
		{
			leftPower = 0;
		}

		motor[rightDrive] = rightPower;  //Apply the final rightPower to the physical right drive.
		motor[leftDrive] = leftPower;    //Apply the final leftPower to the physical left drive.


		if(abs(joystick.joy2_y2)>30){    //If the right joystick on the secondary controller is above 30 in either direction:
			if(joystick.joy2_y2 > 30){   //If the joystick is pushed up, raise the lift.
				if(joy2Btn(6)) motor[lift] = 100;
				else motor[lift] = 70;
			}
			else{                        //If the joystick is pushed down, lower the lift slowly.
				if(joy2Btn(6)) motor[lift] = -45;
				else motor[lift] = -30;
			}
		}
		else{                            //If the right joystick on the secondary controller is not above 30 in either direction, stop the lift.
			motor[lift] = 0;
		}


		if(abs(joystick.joy2_y1)>30){  //If the left joystick on the secondary controller is above 30 in either direction:
			if(joy2Btn(5)){            //If the left shoulder button on the secondary controller is pressed:
				motor[arm] = joystick.joy2_y1*45/abs(joystick.joy2_y1); //Move the arm in the direction dictated by the controller at a preprogrammed, boosted speed.
				//Right now, the "boost" speed is the same as the normal speed.
			}
			else{                      //If the left shoulder button is not pressed:
				motor[arm] = joystick.joy2_y1*20/abs(joystick.joy2_y1); //Move the arm in the direction dictated by the controller at the normal preprogrammed speed.
			}
		}
		else{  //If the left joystick on the secondary controller is not above 30 in either direction, stop the arm.
			motor[arm] = 0;
		}

<<<<<<< HEAD
		if(joystick.joy2_TopHat == 4){        //If the D-Pad is pressed downwards, move the bucket backwards.
			motor[bucket] = -40;
		}
		else if(joystick.joy2_TopHat == 0){  //If the D-Pad is pressed upwards, move the bucket forwards.
			motor[bucket] = 40;
		}
		else{                                //If the D-Pad is pressed in any other direction, stop the bucket.
			motor[bucket] = 0;
		}
=======
			//This section controls the Bucket w/ Btn 4,
			//Note:TopHat is the large circuler button with 4 arrows
			if(joystick.joy2_TopHat == 4){        //If the D-Pad is pressed downwards, move the bucket backwards.
				if(joy2Btn(5)) motor[bucket] = -30;
				else motor[bucket] = -20;
			}
			else if(joystick.joy2_TopHat == 0){  //If the D-Pad is pressed upwards, move the bucket forwards.
				if(joy2Btn(5)) motor[bucket] = 30;
				else motor[bucket] = 20;
			}
			else{                                //If the D-Pad is pressed in any other direction, stop the bucket.
				motor[bucket] = 0;
			}
>>>>>>> 62619061a704262a1ee1b2c6e23f0bd03ddfdc6b


		}
	}
