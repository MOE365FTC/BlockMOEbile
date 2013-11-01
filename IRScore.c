#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyro,           sensorAnalogInactive)
#pragma config(Sensor, S3,     IR,             sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,      ,             tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "hitechnic-irseeker-v2.h"
#include "libraries/gyro.h"
#include "libraries/pidturn.h"
#include "libraries/library.h"

GYRO g_Gyro;
PIDTURN g_PidTurn;

const int MIN_TURN_POWER = 22;
const float TURN_KP = 0.85;//Default was 0.9
const float TURN_TOLERANCE = 0.3;

void initializeRobot(){
	GyroInit(g_Gyro, gyro, 0);
	PidTurnInit(g_PidTurn, leftDrive, rightDrive, MIN_TURN_POWER, g_Gyro, TURN_KP, TURN_TOLERANCE);
	return;
}

task main()
{
	initializeRobot();

	waitForStart(); // Wait for the beginning of autonomous phase.
	//Align against bottom wall, with right edge of right wheels on left edge of third tile (6ft from right wall).
	moveForwardInches(75, 1, true, LEFTENCODER);
	turn(g_PidTurn,-45);
	while(HTIRS2readACDir(IR) != 5){
		startForward(50);
	}
	stopDrive();
	while (true)
	{}
}
