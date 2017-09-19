#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	int a,fact=1;
	cout<<"Enter Number\n";
	cin>>a;

	for(int i=2;i<=a;i++){
		fact=fact*i;
	}
	cout<<"Factorial of "<<a<<"="<<fact;

	getch();
	return 0;
}