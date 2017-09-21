#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	float a[10];
	int n;
	cout<<"Enter Number of Students(<11)\n";
	cin>>n;

	for(int i=0;i<n;i++){
		cout<<"Enter Marks of Student "<<i+1<<": ";
		cin>>a[i];
	}

	float total=0,avg;

	for(int i=0;i<n;i++){
		total=total+a[i];
	}

	avg=total/n;
	
	cout<<"Average Marks = "<avg;

	getch();
	return 0;
}