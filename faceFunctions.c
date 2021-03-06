#pragma config(Motor,  motorA,          carm,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          marm,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          plat,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          cspin,         tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//code to turn faces

int colRef[] = {0, 1, 2, -1}; 

void U(int x)
{
	reorientX(2);
	holdCube();
	turnDown(x, 1);
	resetArm();
	reorientX(2);
}

void D(int x){
	holdCube();
	turnDown(x,1);
	resetArm();
}

int L(int x){
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

int R(int x){
	turnDown(colRef[(col+3)%4],0); // face correction
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm();
	turnDown(-2,0);
	reorientX(1);
	return 3; // orange always faces marm after moving R
}

int F(int x){
	turnDown(colRef[col], 0); // face correction
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm();
	turnDown(-2,0);
	reorientX(1);
	return 2;
}

int B(int x, int col){
	turnDown(colRef[(col+2)%4],0); // face correction
	reorientX(1);
	holdCube();
	turnDown(x,1);
	resetArm();
	turnDown(2,0);
	reorientX(1);
	return 0; // green always faces marm after moving B
}

task main()
{

}
