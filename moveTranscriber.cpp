//This program takes in a set of moves from rubiksolve.com and outputs them into a format that is copy and pasted into solveCube.c
//Jimmy Xu

#include <iostream>

using namespace std;

int main(){
	string move="";
	while (cin>>move){ // gets console input and outputs the appropriate function
		if (move.at(0)=='U'){
			if (move.length()==2)
				cout<<"U(1);";
			else if (move=="U',")
				cout<<"U(-1);";
			else if (move=="U2,")
				cout<<"U(2);";
		} else if (move.at(0)=='D'){
			if (move.length()==2)
				cout<<"D(1);";
			else if (move=="D',")
				cout<<"D(-1);";
			else if (move=="D2,")
				cout<<"D(2);";
		} else if (move.at(0)=='F'){
			if (move.length()==2)
				cout<<"c=F(1,c);";
			else if (move=="F',")
				cout<<"c=F(-1,c);";
			else if (move=="F2,")
				cout<<"c=F(2,c);";
		} else if (move.at(0)=='B'){
			if (move.length()==2)
				cout<<"c=B(1,c);";
			else if (move=="B',")
				cout<<"c=B(-1,c);";
			else if (move=="B2,")
				cout<<"c=B(2,c);";
		}  else if (move.at(0)=='L'){
			if (move.length()==2)
				cout<<"c=L(1,c);";
			else if (move=="L',")
				cout<<"c=L(-1,c);";
			else if (move=="L2,")
				cout<<"c=L(2,c);";
		} else if (move.at(0)=='R'){
			if (move.length()==2)
				cout<<"c=R(1,c);";
			else if (move=="R',")
				cout<<"c=R(-1,c);";
			else if (move=="R2,")
				cout<<"c=R(2,c);";
		}
		cout<<endl; // spaces out the output
	}
	return 0;
}
