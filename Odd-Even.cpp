#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	int a;
	cout<<"Enter Number\n";
	cin>>a;

	if(a%2==0){
		cout<<a<<" is Even\n";
	}

	else{
		cout<<a<<" is Odd\n";
	}
	
	getch();
	return 0;
}