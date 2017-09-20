#include <iostream>
#include <conio.h>

using namespace std;

int main(){

	int num[10],n;

	cout<<"Enter Number of Elements (<11)\n";
	cin>>n;

	for(int i=0;i<n;i++){
		cout<<"Enter Element Number "<<i+1<<":\n";
		cin>>num[i];
	}

	cout<<"Square of the Numbers are:\n";
	for(int i=0;i<n;i++){
		cout<<"Square of "<<num[i]<<"="<<num[i]*num[i]<<"\n";
	}

	getch();
	return 0;
}