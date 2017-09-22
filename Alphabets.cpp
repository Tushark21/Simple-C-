#include <iostream>
#include <conio.h>

using namespace std;

int main(){
	
	char alpha='A';
	
	cout<<"Alphabets in Upper Case:\n";
	while(alpha<'A'+26){
		cout<<alpha<<",";
		alpha++;
	}

	cout<<"\nAlphabets in Lower Case:\n";
	alpha='a';
	while(alpha<'a'+26){
		cout<<alpha<<",";
		alpha++;
	}

	getch();
	return 0;
}