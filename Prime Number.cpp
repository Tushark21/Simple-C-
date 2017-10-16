#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main(){
	
	int num;
	cout<<"Enter Number\n";
	cin>>num;

	int nf=0;
	int counter=sqrt(num);

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