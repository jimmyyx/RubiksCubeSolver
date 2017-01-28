#pragma config(Motor,  motorA,          carm,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          marm,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          plat,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          cspin,         tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
The gear ratio is 1 turn of motor to 3 turns of platform
*/



const int sp =60;
const int turnSpeed=100;
const int holdAngle=295;
const int noHoldAngle=310;
const int [] colRef={0,-1,2,1};

void resetArm(){
	//puts arm back to rest position from any position
	if (nMotorEncoder[marm]<0){
		motor[marm]=sp;
		while (nMotorEncoder[marm]<0)
		{}
		motor[marm]=0;
	}
	else{
		motor[marm]=-sp;
		while (nMotorEncoder[marm]>0)
		{}
		motor[marm]=0;
	}
}

void holdCube(){
	//sets the arm down to hold the cube
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
}

void reorientX(int n){
	//reorients along x-axis, only one direction
	for(int i=0;i<n;i++){
		motor[marm]=-sp;
		while(nMotorEncoder[marm]>-260);
		motor[marm]=sp;
		while (nMotorEncoder[marm]<-90);
	}
	motor[marm]=sp;
	while (nMotorEncoder[marm]<0);
	motor[marm]=0;
}

void turnDown(int x, bool hold){
	//turns the platform, x is direction, hold is whether or not marm is down
	int initEnc=nMotorEncoder[plat];
	if (x>0)
		motor[plat]=turnSpeed;
	else
		motor[plat]=-turnSpeed;

	if (hold)
		while (fabs(initEnc-nMotorEncoder[plat])<fabs(holdAngle*x));
	else
		while (fabs(initEnc-nMotorEncoder[plat])<fabs(noHoldAngle*x));

	motor[plat]=0;
	if (x>0)
		motor[plat]=-turnSpeed;
	else
		motor[plat]=turnSpeed;
	while (fabs(initEnc-nMotorEncoder[plat])>fabs(90*3*x));
	motor[plat]=0;
	wait1Msec(125);

}

//face turns

void U(int x){ // turns the white face
	reorientX(2);
	holdCube();
	turnDown(x, 1);
	resetArm();
	reorientX(2);
}

void D(int x){ // turns the yellow face
	holdCube();
	turnDown(x,1);
	resetArm();
}

int L(int x, int col){ // turns the orange face
	turnDown(colRef[(col+3)%4],0);
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm();
	turnDown(2,0);
	reorientX(1);
	resetArm();
	turnDown(1,0);
	return 1;
}

int R(int x, int col){ // turns the red face
	turnDown(colRef[(col+1)%4],0);
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm();
	turnDown(2,0);
	reorientX(1);
	resetArm();
	turnDown(-1,0);
	return 3;
}

int B(int x, int col){ // turns the blue face

	turnDown(colRef[(col+2)%4],0);
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm(1);
	turnDown(2,0);
	reorientX(1);
	return 0;

}

int F(int x, int col){ // turns the green face
	turnDown(colRef[col], 0);
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm();
	turnDown(2,0);
	reorientX(1);
	return 2;
}

task main()
{
	int c=0; // ranges from 0 to 3, optimizes movement
	//copy and paste output from moveTranscriber.cpp below



}
