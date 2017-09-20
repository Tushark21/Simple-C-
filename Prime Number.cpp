#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	int num;
	cout<<"Enter Number\n";
	cin>>num;

	int counter=num-1,nf=0;

	while(counter>1){
		if(num%counter==0){
			nf++;
		}
		counter--;
	}

	if(nf==0 && num>1){
		cout<<num<<" is a Prime Number\n";
	}

	else{
		cout<<num<<" is not a Prime Number\n";
	}

	getch();
	return 0;
}