#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <process.h>

using namespace std;

int main()
{

int y=1;
while(y==1){
	int a,b=0,c=1,d;
	float x=0.0,n=0.1;

	cout<<"Enter Decimal Number\n";
	cin>>a;

	while(a!=0){
 		b=a%2;
 		n=n*10;
 		x=(x/10)+b;

  		if(a%2==0){
   			a=a/2;
  		}

  		else{
   			a=(a-1)/2;
  		}
	}

	x=x*n;
	d=x;
	cout<<"Binary Number is "<<d;

	cout<<"\n\nEnter 1 to use it again\n          or\npress any other number key to Exit\n";
	cin>>y;
}

getch();
return 0;
}
//K21