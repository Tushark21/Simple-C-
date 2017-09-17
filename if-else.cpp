#include <iostream>

using namespace std;

int main(){
	
	int age;
	cout<<"Enter Your Age\n";
	cin>>age;

	if(age<17){
		cout<<"You are not Eligible for voting.";
	}

	else{
		cout<<"You are Eligible for voting.";
	}

	return 0;
}