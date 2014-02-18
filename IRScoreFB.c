#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyro,           sensorAnalogInactive)
#pragma config(Sensor, S3,     IR,             sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     arm,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     bucket,        tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    dumper,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    flagMount,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    flagRaiser,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "hitechnic-irseeker-v2.h" //includes irseeker drivers
#include "gyro.h"//include gyro drivers
#include "pidturn.h"//includes pidturns
#include "main.h"//includes main library
#include "delay.h"//includes delay library

GYRO g_Gyro;
PIDTURN g_PidTurn;

const int MIN_TURN_POWER = 45;
const float TURN_KP = 0.85;//Default was 0.9
const float TURN_TOLERANCE = 0.3;

void initializeRobot(){
	servo[dumper] = 233;
	servo[flagMount] = 17;
	return;
}

task main()
{
int timeToWait = requestTimeToWait();
	initializeRobot();

	waitForStart(); // Wait for the beginning of autonomous phase.
	//Align against bottom wall, with left edge of left wheels on left edge of third tile (6ft from right wall).
	GyroInit(g_Gyro, gyro, 0);
	PidTurnInit(g_PidTurn, leftDrive, rightDrive, MIN_TURN_POWER, g_Gyro, TURN_KP, TURN_TOLERANCE);
	countdown(timeToWait);
	moveForwardInches(50, 1, false, LEFTENCODER); //away from wall
	turn(g_PidTurn, 44); //turn to parallel with buckets
	clearEncoders(); //clears encoder for the next step
	const int totalTics = 7770; //total tics from before IR to end-- DONT CHANGE!
	while(HTIRS2readACDir(IR) != 4){ //finds the beacon
		if(nMotorEncoder[rightDrive] >= totalTics-500) break;
		startForward(27);
		nxtDisplayCenteredTextLine(6,"%d",nMotorEncoder[leftDrive]);
		//if(nNxtButtonPressed==ORANGE_BUTTON)while(true){};
	}
	wait1Msec(500);
	if(nMotorEncoder[rightDrive] >= 4000){
		moveBackwardInchesNoReset(30, 5, false, LEFTENCODER);
	}
	else{
		//moveForwardInchesNoReset(40, 28, false, LEFTENCODER);
	}
	nxtDisplayCenteredTextLine(1,"%d",nMotorEncoder[leftDrive]);
	stopDrive();//stops robot
	servo[dumper] = 30;//dumps the block
	motor[lift]= 50;//starts the lift up
	wait1Msec(700);
	motor[lift]= 0;//stops lift
	servo[dumper] = 255;//resets servo
	wait1Msec(330);
	int ticsToMove = nMotorEncoder[rightDrive] + 90;
	moveBackwardTics(90, ticsToMove, false, RIGHTENCODER); //reverse back to start
	turn(g_PidTurn, 85,60); //turn backwards to go towards ramp
	moveBackwardInches(90, 44, false, RIGHTENCODER); //forwards towards ramp
	turn(g_PidTurn, 95, 60); //turn to face away from ramp
	moveBackwardInches(90, 47, false, RIGHTENCODER);//onto ramp
	while (true)
	{}
}
