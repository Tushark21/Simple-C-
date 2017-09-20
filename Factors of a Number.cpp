#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	int num;
	cout<<"Enter Number\n";
	cin>>num;

	int counter=num;

	while(counter>0){
		if(num%counter==0){
			cout<<counter<<",";
		}
		counter--;
	}

	getch();
	return 0;
}