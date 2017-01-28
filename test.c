const int sp=25;
const int stahp=500;
task main()
{
	//from brick side
motor[motorA]=sp;//platform ccw
wait1Msec(stahp);
motor[motorA]=0;

motor[motorB]=sp;// arm cw
wait1Msec(stahp);
motor[motorB]=0;

motor[motorC]=sp;//colour arm ccw
wait1Msec(stahp);
motor[motorC]=0;
wait1Msec(10000);



}
