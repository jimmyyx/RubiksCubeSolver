const int sp =25;

void setMS (char mot, int speed){
	if (mot==1)
		motor[motorA]=speed;
	else if (mot==2)
		motor[motorB]=speed;
	else if (mot==3)
		motor[motorC]=speed;
	else
		motor[motorD]=speed;
}

void reorientX(){
	setMS(2,sp);
	while(nMotorEncoder[motorB]<225)
	{}// pull the cube back
	setMS(2,-sp);
	while (nMotorEncoder[motorB]>90)
	{}//pushes it forwards
	setMS(2,0);
}

void holdCube(){
	//sets the arm down to hold the cube
	if (nMotorEncoder[motorB]<100){
		setMS(2,sp);
		while (nMotorEncoder[motorB]<100)
		{}
		setMS(2,0);
	}
	else{
		setMS(2,-sp);
		while (nMotorEncoder[motorB]>100)
		{}
		setMS(2,0);
	}
}

void resetArm(){
	//sets arm to rest position
	setMS(2,-sp);
	while (nMotorEncoder[motorB]>0)
	{}
	setMS(2,0);
}

void down (bool cw) {
	//turns the bottom motor 90 degrees
	if (cw){
		setMS(1,sp);
		while (nMotorEncoder[motorA]<90)
		{}
		setMS(1,0);
	}
	else{
		setMS(1,-sp);
		while (nMotorEncoder[motorA]<90)
		{}
		setMS(1,0);
	}
}

void reorientY(){
	resetArm();
	down(1);
	reorientX();
	down(0);
	resetArm();
}

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

	resetArm();
	reorientX();
	holdCube();
	down(1);
	down(1);
	resetArm();
	reorientX();
	reorientX();
	holdCube();
	down(1);
	down(1);

	resetArm();
	reorientY();
	holdCube();
	down(1);
	down(1);
	resetArm();
	reorientX();
	reorientX();
	holdCube();
	down(1);
	down(1);
}

task main()
{
	checkerboard();
}
