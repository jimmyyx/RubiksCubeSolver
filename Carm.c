
#pragma config(Motor,  motorA,          carm,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          marm,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          plat,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          cspin,         tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard

task main()
{

	motor[carm]=15;
	while(nMotorEncoder[carm]<30)
	{}
	wait1Msec(200);
	motor[carm]=15;
	while(nMotorEncoder[carm]<30)
	{}
	motor[carm]=0;
	wait1Msec(500);

							//scanning
		for(int r=1; r<8; r++)
		{
			wait1Msec(100);
			motor[cspin]=-5;
			while(nMotorEncoder[cspin]>-45*r)
			{}
			motor[cspin]=0;

		}
	motor[cspin]=20;
	while(nMotorEncoder[cspin]<0)
	{}
	motor[cspin]=0;
	motor[carm]=-10;
	while(nMotorEncoder[carm]>5)
	{}
	motor[carm]=0;

}
