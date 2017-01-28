/*
solveCube.c
Authors: Jimmy Xu, Henry Xu, Brandon Johnson, Dominic Tung
Date: November 24, 2016

This program takes input from moveTranscriber.cpp and applies a set of moves
to the cube while keeping track of the time elasped to solve the cube.

The EV3 will stop when the ts touch sensor is pressed or when the ultrasonic
sensor does not detect a cube.

It will start from where it left off when the touch sensor is pressed again and
the ultrasonic sensor detects a cube.
*/

//EV3 Sensor and Motor definitions, allows us to use more user-friendly names
#pragma config(Sensor, S1, ts, sensorEV3_Touch)
#pragma config(Sensor, S2, us, sensorEV3_Ultrasonic)
#pragma config(Sensor, S3, colourChange, sensorEV3_Touch)
#pragma config(Sensor, S4, csens, sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Motor, motorA, carm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorB, marm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, plat, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorD, cspin, tmotorEV3_Medium, PIDControl, encoder)

/*
ts is the left touch sensor
us is the ultrasonic sensor
colourChange is the right touch sensor
csens is the colour sensor
carm is the motor that controls the arm holding the colour sensor
marm is the "main arm" or the arm that reorients and holds the cube
plat is the spinning platform on which the cube rests
cspin is the motor that spins the colour sensor

Notes:
The gear ratio is 1 turn of motor to 3 turns of platform
The cube must be placed with green centre facing marm and white centre up
*/

// various constants used to move the cube
const int sp =60; // speed at which main arm turns
const int turnSpeed=100; // speed at which platform turns
const int holdAngle=295; // encoder count that platform turns when marm is down
const int noHoldAngle=310; // encoder count that platform turns when marm is up
// ideal angles and speeds determined through testing of values
int colRef[] = {0, 1, 2, -1}; 
/* This array represents the turns needed to reorient the cube from any position with
white facing up. The index represents the face currently facing marm, with 
green 0, red 1, blue 2 and orange 3. The amount of turns needed to turn to a face
can be computed with this array and the current colour facing marm.
These values were determined with a 'truth table' included in the report
*/

void resetArm(){
	// written by Jimmy Xu
	//puts arm back to rest position from any position
	//turns the arm in the direction needed until it reaches rest position
	if (nMotorEncoder[marm]<0){
		motor[marm]=sp;
		while (nMotorEncoder[marm]<0);
		motor[marm]=0;
	}
	else{
		motor[marm]=-sp;
		while (nMotorEncoder[marm]>0);
		motor[marm]=0;
	}
}

//safety detection function
void isSafe (int touch, int dist){
	// written by Jimmy Xu
	// if ts is pressed or us does not detect a cube then everything stops
	if (touch||dist>20){
		while(SensorValue[ts]==1);
		// waits until user presses ts and us detects a cube before restarting
		while(SensorValue[ts]==0||SensorValue[us]>20);
		// resets marm to rest position
		resetArm();
	}
}

void holdCube(){
	// written by Jimmy Xu
	// sets the arm down to hold the cube
	// turns marm in the direction needed until it is holding the cube
	if (nMotorEncoder[marm]<-100){
		motor[marm]=sp;
		while (nMotorEncoder[marm]<-165)
		{}
		motor[marm]=0;
	}
	else{
		motor[marm]=-sp;
		while (nMotorEncoder[marm]>-165)
		{}
		motor[marm]=0;
	}
	isSafe(SensorValue[ts], SensorValue[us]); // checks safety function
}

void reorientX(int n){
	// Written by Brandon Johnson
	// reorients along x-axis
	// marm goes forwards and then backwards, resulting in a reoriented cube
	for(int i=0;i<n;i++){
		// this loop reorients the cube n times. It saves a little time as marm does not need to return to rest before reorienting again
		motor[marm]=-sp;
		while(nMotorEncoder[marm]>-240);
		motor[marm]=sp;
		while (nMotorEncoder[marm]<-90);
		wait1Msec(100);
	}
	motor[marm]=sp;
	while (nMotorEncoder[marm]<0);
	motor[marm]=0;
	isSafe(SensorValue[ts], SensorValue[us]); // checks safety function
}

void turnDown(int x, bool hold){
	// written by Dominic Tung
	// turns the platform, x is number of 90 degree turns, hold is whether or not marm is down
	// sign of x represents the direction, i.e. a negative value would turn ccw, pos cw
	int initEnc=nMotorEncoder[plat]; // remembers the original encoder value of plat
	if (x>0)
		motor[plat]=turnSpeed;
	else
		motor[plat]=-turnSpeed;
	// turns plat in appropriate direction
	if (hold)
		while (fabs(initEnc-nMotorEncoder[plat])<fabs(holdAngle*x));
	else
		while (fabs(initEnc-nMotorEncoder[plat])<fabs(noHoldAngle*x));
	motor[plat]=0;
	// plat overshoots the "perfect 90 degree angle" to mitigate error
	if (x>0)
		motor[plat]=-turnSpeed;
	else
		motor[plat]=turnSpeed;
	// reverses motor to minimize error
	while (fabs(initEnc-nMotorEncoder[plat])>fabs(90*3*x));
	motor[plat]=0;
	wait1Msec(125);
	isSafe(SensorValue[ts], SensorValue[us]); // checks safety function
}

//face turns

// c does not change when turning U or D, thus they are void functions
void U(int x){ // turns the white face
	// written by Jimmy Xu
	// reorients, turns the white face the appropriate amount and reorients again
	reorientX(2);
	holdCube();
	turnDown(x, 1);
	resetArm();
	reorientX(2);
}

void D(int x){ // turns the yellow face
	// written by Jimmy Xu
	// holds the cube and turns the yellow face
	holdCube();
	turnDown(x,1);
	resetArm();
}

// c changes to various numbers when turning L, R, B or F, thus they return integers
int L(int x, int col){ // turns the orange face
	// written by Jimmy Xu
	turnDown(colRef[(col+1)%4],0); // correction for current colour facing marm
	// turns the cube until 1 reorientX will place the orange face on plat
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm();
	turnDown(2,0);
	reorientX(1);
	return 1; // red always faces marm after moving L
}

int R(int x, int col){ // turns the red face
	// written by Jimmy Xu
	turnDown(colRef[(col+3)%4],0); // face correction
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm();
	turnDown(-2,0);
	reorientX(1);
	return 3; // orange always faces marm after moving R
}

int B(int x, int col){ // turns the blue face
	// written by Jimmy Xu
	turnDown(colRef[(col+2)%4],0); // face correction
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm();
	turnDown(2,0);
	reorientX(1);
	return 0; // green always faces marm after moving B

}

int F(int x, int col){ // turns the green face
	// written by Jimmy Xu
	turnDown(colRef[col], 0); // face correction
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm();
	turnDown(-2,0);
	reorientX(1);
	return 2; // blue always faces marm after moving F
}


task main(){
	int c=0; // ranges from 0 to 3, optimizes movement
	// represents the colour currently facing marm with white always up
	// green=0. red=1, blue=2, orange=3

	while(SensorValue[ts]==0||SensorValue[us]>20);
	// waits for ts to be pressed and us to sense cube before starting
	ClearTimer(T1); // starts timer

	//copy and paste output from moveTranscriber.cpp below

	
	// displays solve time on screen and waits for ts to be pressed before ending
	float solveTime=time1[T1]/1000.0;
	displayString(0,"%f",solveTime);
	while (SensorValue[ts]==0);
}
