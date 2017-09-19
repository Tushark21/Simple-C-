#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	int num;
	cout<<"Enter Number\n";
	cin>>num;

	int rev=0;

	while(num>0){
		rev=rev*10 + num%10;
		num=num/10;
	}

	cout<<rev;

	getch();
	return 0;
}