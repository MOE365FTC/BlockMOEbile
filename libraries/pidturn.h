#ifndef _PIDTURN_H
#define _PIDTURN_H

#pragma systemFile

typedef struct
{
    tMotor leftMotor;
    tMotor rightMotor;
    int    minTurnPower;// Minimum turn power
    GYRO  *gyro;        // The gyro to be used for turning
    float  Kp;          // Proportion constant for turning
    float  tolerance;   // Turn tolernace
    float  angle;       // Absolute turn angle
    bool   enabled;     // PID turn is enabled or not
} PIDTURN;

void PidTurnInit(
    PIDTURN &pidTurn,
    tMotor leftMotor,
    tMotor rightMotor,
    int minTurnPower,
    GYRO &gyro,
    float Kp,
    float tolerance)
{
    pidTurn.leftMotor = leftMotor;
    pidTurn.rightMotor = rightMotor;
    pidTurn.minTurnPower = abs(minTurnPower);
    pidTurn.gyro = &gyro;
    pidTurn.Kp = Kp;
    pidTurn.tolerance = tolerance;
    pidTurn.angle = 0;
    pidTurn.enabled = false;
}

void PidTurnSetTarget(PIDTURN &pidTurn, float angle)
{
    pidTurn.angle = GyroGetHeading(*pidTurn.gyro) + angle;
    pidTurn.enabled = true;
}

bool PidTurnTask(PIDTURN &pidTurn)
{
    if (pidTurn.enabled)
    {
        float error = pidTurn.angle - GyroGetHeading(*pidTurn.gyro);

        nxtDisplayCenteredTextLine(6,"%d", error);
        if (abs(error) > pidTurn.tolerance)
        {
            int turnPower = BOUND((int)(pidTurn.Kp*error), -100, 100);
            if (abs(turnPower) < pidTurn.minTurnPower)
            {
                turnPower = (turnPower < 0)?
                                -pidTurn.minTurnPower:
                                 pidTurn.minTurnPower;
            }
            nxtDisplayCenteredTextLine(4, "%d", turnPower);
            motor[pidTurn.leftMotor] = turnPower;
            motor[pidTurn.rightMotor] = -turnPower;
        }
        else
        {
            motor[pidTurn.leftMotor] = 0;
            motor[pidTurn.rightMotor] = 0;
            pidTurn.enabled = false;
        }
    }

    return pidTurn.enabled;
}

void turn(PIDTURN &pidTurn, float degrees){
	GyroReset(*pidTurn.gyro);
	PidTurnSetTarget(pidTurn, degrees);
	while(pidTurn.enabled){
		GyroTask(*pidTurn.gyro);
		PidTurnTask(pidTurn);
		wait1Msec(20);
	}
}


#endif  //ifndef _PIDTURN_H
