#pragma config(Motor,  motorA,          carm,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          marm,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          plat,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          cspin,         tmotorEV3_Medium, PIDControl, encoder)

const int sp=25;

void setMS (int mot, int speed){
	if (mot==1)
		motor[motorA]=speed;
	else if (mot==2)
		motor[motorB]=speed;
	else if (mot==3)
		motor[motorC]=speed;
	else
		motor[motorD]=speed;
}

task main()
{
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
