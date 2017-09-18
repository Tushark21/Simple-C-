#include<iostream>
#include<conio.h>

using namespace std;

int main(){
	
	int c;
	float a,b,res;

		cout<<"1.Addition\n2.Substraction\n3.Multiplication\n4.Division\n";
		cin>>c;
		
		if(c>0 && c<5){
			cout<<"Enter 1st Number\n";
			cin>>a;

			cout<<"Enter 2nd Number\n";
			cin>>b;
		}

		switch (c){
			case 1:
				res=a+b;
				cout<<"Sum="<<res;
			break;

			case 2:
				res=a-b;
				cout<<"Difference="<<res;
			break;

			case 3:
				res=a*b;
				cout<<"Multiplication="<<res;
			break;

			case 4:
				res=a/b;
				cout<<"Division="<<res;
			break;

			default:
				cout<<"Wrong Choice";
			break;
		}

	getch();
}