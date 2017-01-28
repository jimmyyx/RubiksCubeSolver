#pragma config(Motor,  motorA,          carm,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          marm,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          plat,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          cspin,         tmotorEV3_Medium, PIDControl, encoder)


const int sp = 50;
const int downTurn = 100;

void setMS (int mot, int speed){
	if (mot==1)
		motor[carm]=speed;
	else if (mot==2)
		motor[marm]=speed;
	else if (mot==3)
		motor[plat]=speed;
	else
		motor[cspin]=speed;
}

void reorientX(){
	setMS(2,-sp);
	while(nMotorEncoder[motorB]>-235)
	{}
	setMS(2,0);
	if (nMotorEncoder[motorB]>0){
		setMS(2,-sp);
		while (nMotorEncoder[motorB]>0)
		{}
		setMS(2,0);
	}
	else{
		setMS(2,sp);
		while (nMotorEncoder[motorB]<0)
		{}
		setMS(2,0);
	}
}



void resetArm(){
	//sets arm to rest position
	if (nMotorEncoder[motorB]>0){
		setMS(2,-sp);
		while (nMotorEncoder[motorB]>0)
		{}
		setMS(2,0);
	}
	else{
		setMS(2,sp);
		while (nMotorEncoder[motorB]<0)
		{}
		setMS(2,0);
	}
}

void holdCube(){
	//sets the arm down to hold the cube
	if (nMotorEncoder[motorB]<-100){
		setMS(2,sp);
		while (nMotorEncoder[motorB]<-135)
		{}
		setMS(2,0);
	}
	else{
		setMS(2,-sp);
		while (nMotorEncoder[motorB]>-135)
		{}
		setMS(2,0);
	}
}

void down (bool cw) {
	//turns the bottom motor 90 degrees
	int initEnc=nMotorEncoder[plat];
	if (0){
		motor[plat]=-downTurn;
		while (initEnc-nMotorEncoder[plat]<90)
		{}
		motor[plat]=0;
	}
	else{
		motor[plat]=downTurn;
		while (initEnc-nMotorEncoder[plat]>-90)
		{}
		motor[plat]=0;
	}
}

//void reorientY(){
//	resetArm();
//	down(1);
//	reorientX();
//	down(0);
//	resetArm();
//}

void checkerboard(){
	resetArm();
	holdCube();
	down(1);
	down(1);
	resetArm();
	reorientX();
	reorientX();
	holdCube();
	down(1);
	down(1);

	//resetArm();
	//reorientX();
	//holdCube();
	//down(1);
	//down(1);
	//resetArm();
	//reorientX();
	//reorientX();
	//holdCube();
	//down(1);
	//down(1);

	//resetArm();
	//reorientY();
	//holdCube();
	//down(1);
	//down(1);
	//resetArm();
	//reorientX();
	//reorientX();
	//holdCube();
	//down(1);
	//down(1);
}

task main()
{
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorA]=0;
	checkerboard();
}
