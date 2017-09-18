#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	int a;

	cout<<"1.Pizza\n2.Burger\n3.Coke\n";
	cout<<"Enter your Choice\n";
	cin>>a;

	switch(a){

		case 1:
		cout<<"You Chose Pizza\n";
		break;

		case 2:
		cout<<"You Chose Burger\n";
		break;

		case 3:
		cout<<"You Chose Coke\n";
		break;

		default:
		cout<<"Sorry Wrong Choice\n";
		break;
	}

	getch();
	return 0;
}