#include <iostream>

using namespace std;

int main(){

	int a,b,c;

	cout<<"Enter 1st Number\n";
	cin>>a;

	cout<<"Enter 2nd Number\n";
	cin>>b;

	cout<<"Enter 3rd Number\n";
	cin>>c;


	if(a>b && a>c){
		cout<<a<<" is Maximum";
	}

	if(b>a && b>c){
		cout<<b<<" is Maximum";
	}

	if(c>b && c>a){
		cout<<c<<" is Maximum";
	}
	return 0;
}