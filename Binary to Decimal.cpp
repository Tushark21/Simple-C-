#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main()
{

int m=1;
while(m==1){
	long int a,f,e,d=1,n=-1;
	cout<<"Enter Binary Number\n";
	cin>>a;

	e=a;
	while(a!=0){
		e=a%2;
 		n++;
 		f=e*(pow(2,n));
 		d=f*10+d;
 		a=a/10;
	}
	cout<<"Decimal Number is "<<d/10<<"\n";;

	cout<<"Enter 1 to try Again\n        OR\nAny other Number key to Exit\n";
	cin>>m;
}

}
//K21