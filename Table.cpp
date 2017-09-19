#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	int a;
	cout<<"Enter Number\n";
	cin>>a;

	for(int i=1;i<=10;i++){
		cout<<a<<" * "<<i<<" = "<<a*i<<"\n";
	}

	getch();
	return 0;
}