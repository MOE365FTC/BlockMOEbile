#pragma systemFile



//conversion of encoder tics to inches
//114.6 motor tics = 1 inch

const int encoderTicsPerInch = 114.6;

//list of prototypes
void clearEncoders();
void startForward(int speed);
void startBackward(int speed);
void stopDrive();
void moveForwardInches(int speed, int inches);
void moveBackwardInches(int speed, int inches);


void clearEncoders(){
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;
}

void startForward(int speed){
	motor[rightDrive] = speed;
	motor[leftDrive] = speed;
}

void startBackward(int speed){
	motor[rightDrive] = -speed;
	motor[leftDrive] = -speed;
}

void stopDrive(){
	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
}

// Turning code located in pidturn.h

void moveForwardInches(int speed, int inches){
	clearEncoders();

	while(nMotorEncoder[rightDrive] <= encoderTicsPerInch*inches){
		startForward(speed);
	}
}

void moveBackwardInches(int speed, int inches){
	clearEncoders();

	while(nMotorEncoder[rightDrive] <= encoderTicsPerInch*inches){

		startBackward(inches);
	}

}



//a const that motor tics times the number of inches

//114.6 motor tics = 1 inch
