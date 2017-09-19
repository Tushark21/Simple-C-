#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	int a,b;

	cout<<"Enter 1st Number\n";
	cin>>a;
	
	cout<<"Enter 2nd Number\n";
	cin>>b;

	cout<<"Numbers Before Swapping\n";
	cout<<a<<","<<b<<"\n";

	int temp=b;
	b=a;
	a=temp;

	cout<<"Numbers After Swapping\n";
	cout<<a<<","<<b;
	
	getch();
	return 0;
}