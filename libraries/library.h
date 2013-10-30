#pragma systemFile

#define LEFTENCODER false
#define RIGHTENCODER true

//conversion of encoder tics to inches
//114.6 motor tics = 1 inch

const float encoderTicsPerInch = 114.6;

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

void moveForwardInches(int speed, int inches, bool isReversed = false, bool encoder = RIGHTENCODER){
	clearEncoders();
	int ticsToMove = encoderTicsPerInch * inches;
	int encoderPosition = 0;

	if(encoder == RIGHTENCODER) while(encoderPosition<= ticsToMove){
		encoderPosition = nMotorEncoder[rightDrive];
		if(isReversed) encoderPosition = -encoderPosition;
		startForward(speed);
	}
	else while(encoderPosition<= ticsToMove){
		encoderPosition = nMotorEncoder[leftDrive];
		if(isReversed) encoderPosition = -encoderPosition;
		startForward(speed);
	}

}

void moveBackwardInches(int speed, int inches, bool isReversed = false, bool encoder = RIGHTENCODER){
	clearEncoders();

	if(encoder == RIGHTENCODER) while(encoderPosition<= ticsToMove){
		encoderPosition = nMotorEncoder[rightDrive];
		if(isReversed) encoderPosition = -encoderPosition;
		startBackward(speed);
	}
	else while(encoderPosition<= ticsToMove){
		encoderPosition = nMotorEncoder[leftDrive];
		if(isReversed) encoderPosition = -encoderPosition;
		startBackward(speed);
	}
}



//a const that motor tics times the number of inches

//114.6 motor tics = 1 inch
